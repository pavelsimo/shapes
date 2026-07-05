#pragma once

#include <ciso646>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>
#include <simo/geom/geometry.hpp>

namespace simo
{
namespace shapes
{

enum class byte_order
{
    native,
    little_endian,
    big_endian
};

struct wkb_options
{
    byte_order order = byte_order::native;
    int output_dimension = 0;
};

namespace io
{
namespace detail
{

enum class wkb_dimension_kind
{
    xy,
    z,
    m,
    zm
};

inline bool host_is_little_endian()
{
    const std::uint16_t value = 1;
    return *reinterpret_cast<const std::uint8_t*>(&value) == 1;
}

inline bool geometry_type_has_z(geometry_type type)
{
    const auto value = static_cast<int>(type);
    return (value >= 1000 and value < 2000) or value >= 3000;
}

inline bool geometry_type_has_m(geometry_type type)
{
    return static_cast<int>(type) >= 2000;
}

inline wkb_dimension_kind inferred_dimension_kind(geometry_type type)
{
    if (geometry_type_has_z(type) and geometry_type_has_m(type))
    {
        return wkb_dimension_kind::zm;
    }
    if (geometry_type_has_z(type))
    {
        return wkb_dimension_kind::z;
    }
    if (geometry_type_has_m(type))
    {
        return wkb_dimension_kind::m;
    }
    return wkb_dimension_kind::xy;
}

inline std::size_t dimension_size(wkb_dimension_kind kind)
{
    switch (kind)
    {
        case wkb_dimension_kind::zm:
            return 4;
        case wkb_dimension_kind::z:
        case wkb_dimension_kind::m:
            return 3;
        default:
            return 2;
    }
}

template <typename PointType>
double point_z_value(const PointType&)
{
    throw exceptions::parse_error("requested WKB Z coordinate is unavailable");
}

template <typename T, typename Enable>
double point_z_value(const basic_point_z<T, Enable>& point)
{
    return static_cast<double>(point.z);
}

template <typename T, typename Enable>
double point_z_value(const basic_point_zm<T, Enable>& point)
{
    return static_cast<double>(point.z);
}

template <typename PointType>
double point_m_value(const PointType&)
{
    throw exceptions::parse_error("requested WKB M coordinate is unavailable");
}

template <typename T, typename Enable>
double point_m_value(const basic_point_m<T, Enable>& point)
{
    return static_cast<double>(point.m);
}

template <typename T, typename Enable>
double point_m_value(const basic_point_zm<T, Enable>& point)
{
    return static_cast<double>(point.m);
}

class wkb_writer
{
  public:
    explicit wkb_writer(const wkb_options& options)
        : options_(options), little_endian_(resolve_byte_order(options.order)) {}

    template <typename T, typename Enable>
    void write_geometry(const basic_point<T, Enable>& point)
    {
        const auto kind = output_kind(point.geom_type());
        write_header(point.geom_type(), kind);
        write_position(point, kind);
    }

    template <typename T, typename Enable>
    void write_geometry(const basic_point_z<T, Enable>& point)
    {
        const auto kind = output_kind(point.geom_type());
        write_header(point.geom_type(), kind);
        write_position(point, kind);
    }

    template <typename T, typename Enable>
    void write_geometry(const basic_point_m<T, Enable>& point)
    {
        const auto kind = output_kind(point.geom_type());
        write_header(point.geom_type(), kind);
        write_position(point, kind);
    }

    template <typename T, typename Enable>
    void write_geometry(const basic_point_zm<T, Enable>& point)
    {
        const auto kind = output_kind(point.geom_type());
        write_header(point.geom_type(), kind);
        write_position(point, kind);
    }

    template <typename T, typename AllocatorType>
    void write_geometry(const basic_multipoint<T, AllocatorType>& multipoint)
    {
        const auto kind = output_kind(multipoint.geom_type());
        write_header(multipoint.geom_type(), kind);
        reserve_hint(4 + multipoint.size() * (5 + dimension_size(kind) * 8));
        write_count(multipoint.size());
        for (const auto& point : multipoint)
        {
            write_geometry(point);
        }
    }

    template <typename T, typename AllocatorType>
    void write_geometry(const basic_linestring<T, AllocatorType>& linestring)
    {
        const auto kind = output_kind(linestring.geom_type());
        write_header(linestring.geom_type(), kind);
        write_linestring_coordinates(linestring, kind);
    }

    template <typename T, typename AllocatorType>
    void write_geometry(const basic_multilinestring<T, AllocatorType>& multilinestring)
    {
        const auto kind = output_kind(multilinestring.geom_type());
        write_header(multilinestring.geom_type(), kind);
        reserve_hint(4 + multilinestring.size() * 9);
        write_count(multilinestring.size());
        for (const auto& linestring : multilinestring)
        {
            write_geometry(linestring);
        }
    }

    template <typename T, typename AllocatorType>
    void write_geometry(const basic_polygon<T, AllocatorType>& polygon)
    {
        const auto kind = output_kind(polygon.geom_type());
        write_header(polygon.geom_type(), kind);
        write_polygon_coordinates(polygon, kind);
    }

    template <typename T, typename AllocatorType>
    void write_geometry(const basic_multipolygon<T, AllocatorType>& multipolygon)
    {
        const auto kind = output_kind(multipolygon.geom_type());
        write_header(multipolygon.geom_type(), kind);
        reserve_hint(4 + multipolygon.size() * 9);
        write_count(multipolygon.size());
        for (const auto& polygon : multipolygon)
        {
            write_geometry(polygon);
        }
    }

    template <typename T, geometry_type GeometryType, typename AllocatorType>
    void write_geometry(const basic_geometrycollection<T, GeometryType, AllocatorType>& collection)
    {
        const auto kind = output_kind(collection.geom_type());
        write_header(collection.geom_type(), kind);
        reserve_hint(4 + collection.size() * 9);
        write_count(collection.size());
        for (const auto& geometry : collection)
        {
            write_geometry(geometry);
        }
    }

    template <typename T>
    void write_geometry(const geometry_t<T>& geometry)
    {
        switch (geometry.geom_type())
        {
            case geometry_type::POINT:
                write_geometry(*geometry.get_point());
                break;
            case geometry_type::POINTZ:
                write_geometry(*geometry.get_point_z());
                break;
            case geometry_type::POINTM:
                write_geometry(*geometry.get_point_m());
                break;
            case geometry_type::POINTZM:
                write_geometry(*geometry.get_point_zm());
                break;

            case geometry_type::MULTIPOINT:
                write_geometry(*geometry.get_multipoint());
                break;
            case geometry_type::MULTIPOINTZ:
                write_geometry(*geometry.get_multipoint_z());
                break;
            case geometry_type::MULTIPOINTM:
                write_geometry(*geometry.get_multipoint_m());
                break;
            case geometry_type::MULTIPOINTZM:
                write_geometry(*geometry.get_multipoint_zm());
                break;

            case geometry_type::LINESTRING:
                write_geometry(*geometry.get_linestring());
                break;
            case geometry_type::LINESTRINGZ:
                write_geometry(*geometry.get_linestring_z());
                break;
            case geometry_type::LINESTRINGM:
                write_geometry(*geometry.get_linestring_m());
                break;
            case geometry_type::LINESTRINGZM:
                write_geometry(*geometry.get_linestring_zm());
                break;

            case geometry_type::MULTILINESTRING:
                write_geometry(*geometry.get_multilinestring());
                break;
            case geometry_type::MULTILINESTRINGZ:
                write_geometry(*geometry.get_multilinestring_z());
                break;
            case geometry_type::MULTILINESTRINGM:
                write_geometry(*geometry.get_multilinestring_m());
                break;
            case geometry_type::MULTILINESTRINGZM:
                write_geometry(*geometry.get_multilinestring_zm());
                break;

            case geometry_type::POLYGON:
                write_geometry(*geometry.get_polygon());
                break;
            case geometry_type::POLYGONZ:
                write_geometry(*geometry.get_polygon_z());
                break;
            case geometry_type::POLYGONM:
                write_geometry(*geometry.get_polygon_m());
                break;
            case geometry_type::POLYGONZM:
                write_geometry(*geometry.get_polygon_zm());
                break;

            case geometry_type::MULTIPOLYGON:
                write_geometry(*geometry.get_multipolygon());
                break;
            case geometry_type::MULTIPOLYGONZ:
                write_geometry(*geometry.get_multipolygon_z());
                break;
            case geometry_type::MULTIPOLYGONM:
                write_geometry(*geometry.get_multipolygon_m());
                break;
            case geometry_type::MULTIPOLYGONZM:
                write_geometry(*geometry.get_multipolygon_zm());
                break;

            case geometry_type::GEOMETRYCOLLECTION:
                write_geometry(*geometry.get_geometrycollection());
                break;
            case geometry_type::GEOMETRYCOLLECTIONZ:
                write_geometry(*geometry.get_geometrycollection_z());
                break;
            case geometry_type::GEOMETRYCOLLECTIONM:
                write_geometry(*geometry.get_geometrycollection_m());
                break;
            case geometry_type::GEOMETRYCOLLECTIONZM:
                write_geometry(*geometry.get_geometrycollection_zm());
                break;

            default:
                throw exceptions::parse_error("unsupported WKB geometry type");
        }
    }

    std::vector<std::uint8_t> bytes() const
    {
        return bytes_;
    }

    /// moves the output buffer out of the writer, avoiding a copy
    std::vector<std::uint8_t> take()
    {
        return std::move(bytes_);
    }

    /// grows the output buffer capacity by the given number of bytes
    void reserve_hint(std::size_t additional)
    {
        bytes_.reserve(bytes_.size() + additional);
    }

  private:
    wkb_options options_;
    bool little_endian_;
    std::vector<std::uint8_t> bytes_;

    static bool resolve_byte_order(byte_order order)
    {
        switch (order)
        {
            case byte_order::little_endian:
                return true;
            case byte_order::big_endian:
                return false;
            default:
                return host_is_little_endian();
        }
    }

    wkb_dimension_kind output_kind(geometry_type type) const
    {
        switch (options_.output_dimension)
        {
            case 0:
                return inferred_dimension_kind(type);
            case 2:
                return wkb_dimension_kind::xy;
            case 3:
                if (geometry_type_has_z(type))
                {
                    return wkb_dimension_kind::z;
                }
                if (geometry_type_has_m(type))
                {
                    return wkb_dimension_kind::m;
                }
                throw exceptions::parse_error("requested WKB output dimension is unavailable");
            case 4:
                if (geometry_type_has_z(type) and geometry_type_has_m(type))
                {
                    return wkb_dimension_kind::zm;
                }
                throw exceptions::parse_error("requested WKB output dimension is unavailable");
            default:
                throw exceptions::parse_error("invalid WKB output dimension");
        }
    }

    std::uint32_t type_id(geometry_type type, wkb_dimension_kind kind) const
    {
        const auto base_type = utils::get_geom_type(type);
        const auto base = static_cast<std::uint32_t>(base_type);
        if (base < 1 or base > 7)
        {
            throw exceptions::parse_error("unsupported WKB geometry type");
        }

        switch (kind)
        {
            case wkb_dimension_kind::z:
                return 1000 + base;
            case wkb_dimension_kind::m:
                return 2000 + base;
            case wkb_dimension_kind::zm:
                return 3000 + base;
            default:
                return base;
        }
    }

    void write_header(geometry_type type, wkb_dimension_kind kind)
    {
        bytes_.push_back(little_endian_ ? 1 : 0);
        write_u32(type_id(type, kind));
    }

    void write_count(std::size_t count)
    {
        if (count > static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()))
        {
            throw exceptions::parse_error("WKB geometry count exceeds uint32 range");
        }
        write_u32(static_cast<std::uint32_t>(count));
    }

    void write_u32(std::uint32_t value)
    {
        if (little_endian_)
        {
            for (int i = 0; i < 4; ++i)
            {
                bytes_.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
            }
            return;
        }

        for (int i = 3; i >= 0; --i)
        {
            bytes_.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
        }
    }

    void write_u64(std::uint64_t value)
    {
        if (little_endian_)
        {
            for (int i = 0; i < 8; ++i)
            {
                bytes_.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
            }
            return;
        }

        for (int i = 7; i >= 0; --i)
        {
            bytes_.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
        }
    }

    void write_double(double value)
    {
        std::uint64_t bits = 0;
        std::memcpy(&bits, &value, sizeof(value));
        write_u64(bits);
    }

    template <typename PointType>
    void write_position(const PointType& point, wkb_dimension_kind kind)
    {
        if (point.empty())
        {
            const auto nan = std::numeric_limits<double>::quiet_NaN();
            for (std::size_t i = 0; i < dimension_size(kind); ++i)
            {
                write_double(nan);
            }
            return;
        }

        write_double(static_cast<double>(point.x));
        write_double(static_cast<double>(point.y));
        if (kind == wkb_dimension_kind::z)
        {
            write_double(point_z_value(point));
        }
        else if (kind == wkb_dimension_kind::m)
        {
            write_double(point_m_value(point));
        }
        else if (kind == wkb_dimension_kind::zm)
        {
            write_double(point_z_value(point));
            write_double(point_m_value(point));
        }
    }

    template <typename LineStringType>
    void write_linestring_coordinates(const LineStringType& linestring, wkb_dimension_kind kind)
    {
        reserve_hint(4 + linestring.size() * dimension_size(kind) * 8);
        write_count(linestring.size());
        for (const auto& point : linestring)
        {
            write_position(point, kind);
        }
    }

    template <typename PolygonType>
    void write_polygon_coordinates(const PolygonType& polygon, wkb_dimension_kind kind)
    {
        write_count(polygon.size());
        for (const auto& ring : polygon)
        {
            write_linestring_coordinates(ring, kind);
        }
    }
};

template <typename Geometry>
std::vector<std::uint8_t> write_wkb(const Geometry& geometry, const wkb_options& options)
{
    wkb_writer writer(options);
    writer.reserve_hint(64);
    writer.write_geometry(geometry);
    return writer.take();
}

}  // namespace detail
}  // namespace io
}  // namespace shapes
}  // namespace simo
