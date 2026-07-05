#pragma once

#include <ciso646>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <limits>
#include <type_traits>
#include <vector>
#include <simo/geom/geometry.hpp>

namespace simo
{
namespace shapes
{
namespace io
{
namespace detail
{

template <typename T>
class wkb_reader
{
  public:
    wkb_reader(const std::uint8_t* data, std::size_t size)
        : data_(data), size_(size), offset_(0) {}

    geometry_t<T> read()
    {
        auto geometry = read_geometry();
        if (offset_ != size_)
        {
            throw exceptions::parse_error("unexpected trailing WKB bytes");
        }
        return geometry;
    }

  private:
    const std::uint8_t* data_;
    std::size_t size_;
    std::size_t offset_;

    /// maximum nesting depth for geometry collections, guards against stack overflow
    static constexpr int MAX_DEPTH = 128;
    int depth_ = 0;

    struct depth_guard
    {
        explicit depth_guard(int& depth)
            : depth_(depth)
        {
            if (++depth_ > MAX_DEPTH)
            {
                throw exceptions::parse_error("WKB nesting too deep");
            }
        }

        ~depth_guard()
        {
            --depth_;
        }

        depth_guard(const depth_guard&) = delete;
        depth_guard& operator=(const depth_guard&) = delete;

      private:
        int& depth_;
    };

    void require(std::size_t count) const
    {
        if (size_ - offset_ < count)
        {
            throw exceptions::parse_error("truncated WKB");
        }
    }

    std::uint8_t read_u8()
    {
        require(1);
        return data_[offset_++];
    }

    std::uint32_t read_u32(bool little_endian)
    {
        require(4);
        std::uint32_t value = 0;
        if (little_endian)
        {
            for (int i = 0; i < 4; ++i)
            {
                value |= static_cast<std::uint32_t>(data_[offset_ + static_cast<std::size_t>(i)]) << (i * 8);
            }
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                value = (value << 8) | static_cast<std::uint32_t>(data_[offset_ + static_cast<std::size_t>(i)]);
            }
        }
        offset_ += 4;
        return value;
    }

    std::uint64_t read_u64(bool little_endian)
    {
        require(8);
        std::uint64_t value = 0;
        if (little_endian)
        {
            for (int i = 0; i < 8; ++i)
            {
                value |= static_cast<std::uint64_t>(data_[offset_ + static_cast<std::size_t>(i)]) << (i * 8);
            }
        }
        else
        {
            for (int i = 0; i < 8; ++i)
            {
                value = (value << 8) | static_cast<std::uint64_t>(data_[offset_ + static_cast<std::size_t>(i)]);
            }
        }
        offset_ += 8;
        return value;
    }

    double read_double(bool little_endian)
    {
        const auto bits = read_u64(little_endian);
        double value = 0.0;
        std::memcpy(&value, &bits, sizeof(value));
        return value;
    }

    /// reads an element count and validates it against the remaining input before any
    /// reserve call, so a crafted small buffer cannot trigger a huge allocation
    std::uint32_t read_count(bool little_endian, std::size_t min_element_bytes)
    {
        const auto count = read_u32(little_endian);
        if (static_cast<std::size_t>(count) > (size_ - offset_) / min_element_bytes)
        {
            throw exceptions::parse_error("truncated WKB");
        }
        return count;
    }

    geometry_type decode_type(std::uint32_t type_id) const
    {
        const auto base = type_id % 1000;
        if (base < 1 or base > 7)
        {
            throw exceptions::parse_error("unsupported WKB geometry type");
        }

        if (type_id >= 1 and type_id <= 7)
        {
            return static_cast<geometry_type>(type_id);
        }
        if (type_id >= 1001 and type_id <= 1007)
        {
            return static_cast<geometry_type>(type_id);
        }
        if (type_id >= 2001 and type_id <= 2007)
        {
            return static_cast<geometry_type>(type_id);
        }
        if (type_id >= 3001 and type_id <= 3007)
        {
            return static_cast<geometry_type>(type_id);
        }

        throw exceptions::parse_error("unsupported WKB geometry type");
    }

    template <typename PointType>
    static PointType make_point(const double* c, std::integral_constant<std::size_t, 2>)
    {
        using coord_type = typename PointType::coord_type;
        return PointType(static_cast<coord_type>(c[0]), static_cast<coord_type>(c[1]));
    }

    template <typename PointType>
    static PointType make_point(const double* c, std::integral_constant<std::size_t, 3>)
    {
        using coord_type = typename PointType::coord_type;
        return PointType(static_cast<coord_type>(c[0]), static_cast<coord_type>(c[1]), static_cast<coord_type>(c[2]));
    }

    template <typename PointType>
    static PointType make_point(const double* c, std::integral_constant<std::size_t, 4>)
    {
        using coord_type = typename PointType::coord_type;
        return PointType(static_cast<coord_type>(c[0]), static_cast<coord_type>(c[1]), static_cast<coord_type>(c[2]), static_cast<coord_type>(c[3]));
    }

    template <typename PointType>
    PointType read_point_coordinates(bool little_endian)
    {
        double coords[PointType::N];
        bool all_nan = true;
        for (std::size_t i = 0; i < PointType::N; ++i)
        {
            coords[i] = read_double(little_endian);
            all_nan   = all_nan and std::isnan(coords[i]);
        }

        if (all_nan)
        {
            return PointType();
        }
        return make_point<PointType>(coords, std::integral_constant<std::size_t, PointType::N>{});
    }

    template <typename LineStringType>
    LineStringType read_linestring_coordinates(bool little_endian)
    {
        using point_type = typename LineStringType::point_type;

        const auto count = read_count(little_endian, point_type::N * 8);
        LineStringType res;
        res.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            res.emplace_back(read_point_coordinates<point_type>(little_endian));
        }
        return res;
    }

    template <typename PolygonType>
    PolygonType read_polygon_coordinates(bool little_endian)
    {
        using ring_type = typename PolygonType::value_type;

        const auto count = read_count(little_endian, 4);
        PolygonType res;
        res.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            res.emplace_back(read_linestring_coordinates<ring_type>(little_endian));
        }
        return res;
    }

    /// reads a child geometry header and returns the child byte order, the child is
    /// parsed as its concrete type with no geometry_t wrapper in between
    bool read_child_header(geometry_type expected_type)
    {
        const auto order = read_u8();
        if (order != 0 and order != 1)
        {
            throw exceptions::parse_error("invalid WKB byte order");
        }
        const bool little_endian = order == 1;
        if (decode_type(read_u32(little_endian)) != expected_type)
        {
            throw exceptions::parse_error("unexpected WKB child geometry type");
        }
        return little_endian;
    }

    template <typename MultiType>
    MultiType read_multi_points(bool little_endian, geometry_type expected_type)
    {
        using point_type = typename MultiType::value_type;

        const auto count = read_count(little_endian, 5 + point_type::N * 8);
        MultiType res;
        res.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            const bool child_little_endian = read_child_header(expected_type);
            res.emplace_back(read_point_coordinates<point_type>(child_little_endian));
        }
        return res;
    }

    template <typename MultiType>
    MultiType read_multi_linestrings(bool little_endian, geometry_type expected_type)
    {
        using linestring_type = typename MultiType::value_type;

        const auto count = read_count(little_endian, 9);
        MultiType res;
        res.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            const bool child_little_endian = read_child_header(expected_type);
            res.emplace_back(read_linestring_coordinates<linestring_type>(child_little_endian));
        }
        return res;
    }

    template <typename MultiType>
    MultiType read_multi_polygons(bool little_endian, geometry_type expected_type)
    {
        using polygon_type = typename MultiType::value_type;

        const auto count = read_count(little_endian, 9);
        MultiType res;
        res.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            const bool child_little_endian = read_child_header(expected_type);
            res.emplace_back(read_polygon_coordinates<polygon_type>(child_little_endian));
        }
        return res;
    }

    template <typename CollectionType>
    CollectionType read_collection_children(bool little_endian)
    {
        const auto count = read_count(little_endian, 5);
        CollectionType res;
        res.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            res.emplace_back(read_geometry());
        }
        return res;
    }

    geometry_t<T> read_geometry()
    {
        depth_guard guard(depth_);

        const auto order = read_u8();
        if (order != 0 and order != 1)
        {
            throw exceptions::parse_error("invalid WKB byte order");
        }
        const bool little_endian = order == 1;
        const auto geom_type = decode_type(read_u32(little_endian));

        switch (geom_type)
        {
            case geometry_type::POINT:
                return geometry_t<T>(read_point_coordinates<point_t<T>>(little_endian));
            case geometry_type::POINTZ:
                return geometry_t<T>(read_point_coordinates<point_z_t<T>>(little_endian));
            case geometry_type::POINTM:
                return geometry_t<T>(read_point_coordinates<point_m_t<T>>(little_endian));
            case geometry_type::POINTZM:
                return geometry_t<T>(read_point_coordinates<point_zm_t<T>>(little_endian));

            case geometry_type::LINESTRING:
                return geometry_t<T>(read_linestring_coordinates<linestring_t<T>>(little_endian));
            case geometry_type::LINESTRINGZ:
                return geometry_t<T>(read_linestring_coordinates<linestring_z_t<T>>(little_endian));
            case geometry_type::LINESTRINGM:
                return geometry_t<T>(read_linestring_coordinates<linestring_m_t<T>>(little_endian));
            case geometry_type::LINESTRINGZM:
                return geometry_t<T>(read_linestring_coordinates<linestring_zm_t<T>>(little_endian));

            case geometry_type::POLYGON:
                return geometry_t<T>(read_polygon_coordinates<polygon_t<T>>(little_endian));
            case geometry_type::POLYGONZ:
                return geometry_t<T>(read_polygon_coordinates<polygon_z_t<T>>(little_endian));
            case geometry_type::POLYGONM:
                return geometry_t<T>(read_polygon_coordinates<polygon_m_t<T>>(little_endian));
            case geometry_type::POLYGONZM:
                return geometry_t<T>(read_polygon_coordinates<polygon_zm_t<T>>(little_endian));

            case geometry_type::MULTIPOINT:
                return geometry_t<T>(read_multi_points<multipoint_t<T>>(little_endian, geometry_type::POINT));
            case geometry_type::MULTIPOINTZ:
                return geometry_t<T>(read_multi_points<multipoint_z_t<T>>(little_endian, geometry_type::POINTZ));
            case geometry_type::MULTIPOINTM:
                return geometry_t<T>(read_multi_points<multipoint_m_t<T>>(little_endian, geometry_type::POINTM));
            case geometry_type::MULTIPOINTZM:
                return geometry_t<T>(read_multi_points<multipoint_zm_t<T>>(little_endian, geometry_type::POINTZM));

            case geometry_type::MULTILINESTRING:
                return geometry_t<T>(read_multi_linestrings<multilinestring_t<T>>(little_endian, geometry_type::LINESTRING));
            case geometry_type::MULTILINESTRINGZ:
                return geometry_t<T>(read_multi_linestrings<multilinestring_z_t<T>>(little_endian, geometry_type::LINESTRINGZ));
            case geometry_type::MULTILINESTRINGM:
                return geometry_t<T>(read_multi_linestrings<multilinestring_m_t<T>>(little_endian, geometry_type::LINESTRINGM));
            case geometry_type::MULTILINESTRINGZM:
                return geometry_t<T>(read_multi_linestrings<multilinestring_zm_t<T>>(little_endian, geometry_type::LINESTRINGZM));

            case geometry_type::MULTIPOLYGON:
                return geometry_t<T>(read_multi_polygons<multipolygon_t<T>>(little_endian, geometry_type::POLYGON));
            case geometry_type::MULTIPOLYGONZ:
                return geometry_t<T>(read_multi_polygons<multipolygon_z_t<T>>(little_endian, geometry_type::POLYGONZ));
            case geometry_type::MULTIPOLYGONM:
                return geometry_t<T>(read_multi_polygons<multipolygon_m_t<T>>(little_endian, geometry_type::POLYGONM));
            case geometry_type::MULTIPOLYGONZM:
                return geometry_t<T>(read_multi_polygons<multipolygon_zm_t<T>>(little_endian, geometry_type::POLYGONZM));

            case geometry_type::GEOMETRYCOLLECTION:
                return geometry_t<T>(read_collection_children<geometrycollection_t<T>>(little_endian));
            case geometry_type::GEOMETRYCOLLECTIONZ:
                return geometry_t<T>(read_collection_children<geometrycollection_z_t<T>>(little_endian));
            case geometry_type::GEOMETRYCOLLECTIONM:
                return geometry_t<T>(read_collection_children<geometrycollection_m_t<T>>(little_endian));
            case geometry_type::GEOMETRYCOLLECTIONZM:
                return geometry_t<T>(read_collection_children<geometrycollection_zm_t<T>>(little_endian));

            default:
                throw exceptions::parse_error("unsupported WKB geometry type");
        }
    }
};

template <typename T>
geometry_t<T> read_wkb(const std::uint8_t* data, std::size_t size)
{
    return wkb_reader<T>(data, size).read();
}

template <typename T, typename Iterator>
geometry_t<T> read_wkb(Iterator first, Iterator last)
{
    std::vector<std::uint8_t> bytes;
    bytes.reserve(static_cast<std::size_t>(std::distance(first, last)));
    for (auto it = first; it != last; ++it)
    {
        bytes.push_back(static_cast<std::uint8_t>(*it));
    }
    return read_wkb<T>(bytes.data(), bytes.size());
}

}  // namespace detail
}  // namespace io
}  // namespace shapes
}  // namespace simo
