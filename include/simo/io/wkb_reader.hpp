#pragma once

#include <ciso646>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
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
    explicit wkb_reader(const std::vector<std::uint8_t>& bytes)
        : bytes_(bytes), offset_(0) {}

    geometry_t<T> read()
    {
        auto geometry = read_geometry();
        if (offset_ != bytes_.size())
        {
            throw exceptions::parse_error("unexpected trailing WKB bytes");
        }
        return geometry;
    }

  private:
    std::vector<std::uint8_t> bytes_;
    std::size_t offset_;

    void require(std::size_t count) const
    {
        if (bytes_.size() - offset_ < count)
        {
            throw exceptions::parse_error("truncated WKB");
        }
    }

    std::uint8_t read_u8()
    {
        require(1);
        return bytes_[offset_++];
    }

    std::uint32_t read_u32(bool little_endian)
    {
        require(4);
        std::uint32_t value = 0;
        if (little_endian)
        {
            for (int i = 0; i < 4; ++i)
            {
                value |= static_cast<std::uint32_t>(bytes_[offset_ + static_cast<std::size_t>(i)]) << (i * 8);
            }
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                value = (value << 8) | static_cast<std::uint32_t>(bytes_[offset_ + static_cast<std::size_t>(i)]);
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
                value |= static_cast<std::uint64_t>(bytes_[offset_ + static_cast<std::size_t>(i)]) << (i * 8);
            }
        }
        else
        {
            for (int i = 0; i < 8; ++i)
            {
                value = (value << 8) | static_cast<std::uint64_t>(bytes_[offset_ + static_cast<std::size_t>(i)]);
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
    PointType read_point_coordinates(bool little_endian)
    {
        std::vector<typename PointType::coord_type> coords;
        coords.reserve(PointType::N);

        bool all_nan = true;
        for (std::size_t i = 0; i < PointType::N; ++i)
        {
            const auto value = read_double(little_endian);
            all_nan = all_nan and std::isnan(value);
            coords.push_back(static_cast<typename PointType::coord_type>(value));
        }

        if (all_nan)
        {
            return PointType();
        }
        return PointType(coords.begin(), coords.end());
    }

    template <typename LineStringType>
    LineStringType read_linestring_coordinates(bool little_endian)
    {
        using point_type = typename LineStringType::point_type;

        const auto count = read_u32(little_endian);
        std::vector<point_type> points;
        points.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            points.emplace_back(read_point_coordinates<point_type>(little_endian));
        }
        return LineStringType(points.begin(), points.end());
    }

    template <typename PolygonType>
    PolygonType read_polygon_coordinates(bool little_endian)
    {
        using ring_type = typename PolygonType::value_type;

        const auto count = read_u32(little_endian);
        std::vector<ring_type> rings;
        rings.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            rings.emplace_back(read_linestring_coordinates<ring_type>(little_endian));
        }
        return PolygonType(rings.begin(), rings.end());
    }

    template <typename MultiType, typename ChildType>
    MultiType read_geometry_children(bool little_endian, geometry_type expected_type)
    {
        const auto count = read_u32(little_endian);
        std::vector<ChildType> children;
        children.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            auto child = read_geometry();
            if (child.geom_type() != expected_type)
            {
                throw exceptions::parse_error("unexpected WKB child geometry type");
            }
            children.emplace_back(*child.template get<ChildType>());
        }
        return MultiType(children.begin(), children.end());
    }

    template <typename CollectionType>
    CollectionType read_collection_children(bool little_endian)
    {
        const auto count = read_u32(little_endian);
        std::vector<geometry_t<T>> children;
        children.reserve(static_cast<std::size_t>(count));
        for (std::uint32_t i = 0; i < count; ++i)
        {
            children.emplace_back(read_geometry());
        }
        return CollectionType(children.begin(), children.end());
    }

    geometry_t<T> read_geometry()
    {
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
                return geometry_t<T>(read_geometry_children<multipoint_t<T>, point_t<T>>(little_endian, geometry_type::POINT));
            case geometry_type::MULTIPOINTZ:
                return geometry_t<T>(read_geometry_children<multipoint_z_t<T>, point_z_t<T>>(little_endian, geometry_type::POINTZ));
            case geometry_type::MULTIPOINTM:
                return geometry_t<T>(read_geometry_children<multipoint_m_t<T>, point_m_t<T>>(little_endian, geometry_type::POINTM));
            case geometry_type::MULTIPOINTZM:
                return geometry_t<T>(read_geometry_children<multipoint_zm_t<T>, point_zm_t<T>>(little_endian, geometry_type::POINTZM));

            case geometry_type::MULTILINESTRING:
                return geometry_t<T>(read_geometry_children<multilinestring_t<T>, linestring_t<T>>(little_endian, geometry_type::LINESTRING));
            case geometry_type::MULTILINESTRINGZ:
                return geometry_t<T>(read_geometry_children<multilinestring_z_t<T>, linestring_z_t<T>>(little_endian, geometry_type::LINESTRINGZ));
            case geometry_type::MULTILINESTRINGM:
                return geometry_t<T>(read_geometry_children<multilinestring_m_t<T>, linestring_m_t<T>>(little_endian, geometry_type::LINESTRINGM));
            case geometry_type::MULTILINESTRINGZM:
                return geometry_t<T>(read_geometry_children<multilinestring_zm_t<T>, linestring_zm_t<T>>(little_endian, geometry_type::LINESTRINGZM));

            case geometry_type::MULTIPOLYGON:
                return geometry_t<T>(read_geometry_children<multipolygon_t<T>, polygon_t<T>>(little_endian, geometry_type::POLYGON));
            case geometry_type::MULTIPOLYGONZ:
                return geometry_t<T>(read_geometry_children<multipolygon_z_t<T>, polygon_z_t<T>>(little_endian, geometry_type::POLYGONZ));
            case geometry_type::MULTIPOLYGONM:
                return geometry_t<T>(read_geometry_children<multipolygon_m_t<T>, polygon_m_t<T>>(little_endian, geometry_type::POLYGONM));
            case geometry_type::MULTIPOLYGONZM:
                return geometry_t<T>(read_geometry_children<multipolygon_zm_t<T>, polygon_zm_t<T>>(little_endian, geometry_type::POLYGONZM));

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

template <typename T, typename Iterator>
geometry_t<T> read_wkb(Iterator first, Iterator last)
{
    std::vector<std::uint8_t> bytes;
    for (auto it = first; it != last; ++it)
    {
        bytes.push_back(static_cast<std::uint8_t>(*it));
    }
    return wkb_reader<T>(bytes).read();
}

}  // namespace detail
}  // namespace io
}  // namespace shapes
}  // namespace simo
