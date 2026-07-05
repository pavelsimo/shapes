#pragma once

#include <algorithm>
#include <ciso646>
#include <cctype>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <simo/geom/detail/geometry.hpp>
#include <simo/geom/detail/wkt_util.hpp>
#include <simo/geom/point.hpp>
#include <simo/geom/multipoint.hpp>
#include <simo/geom/linestring.hpp>
#include <simo/geom/multilinestring.hpp>
#include <simo/geom/polygon.hpp>
#include <simo/geom/multipolygon.hpp>

namespace simo
{
namespace shapes
{

template <typename T>
class geometry_t;

template <typename T = double, geometry_type GeometryType = geometry_type::GEOMETRYCOLLECTION,
          typename AllocatorType = std::allocator<geometry_t<T>>>
class basic_geometrycollection;

template <class T = double>
using geometrycollection_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTION>;

template <class T = double>
using geometrycollection_z_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTIONZ>;

template <class T = double>
using geometrycollection_m_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTIONM>;

template <class T = double>
using geometrycollection_zm_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTIONZM>;

template <typename>
struct is_basic_geometrycollection;

template <typename>
struct is_basic_geometrycollection_z;

template <typename>
struct is_basic_geometrycollection_m;

template <typename>
struct is_basic_geometrycollection_zm;

namespace io
{
namespace detail
{

template <typename T>
geometry_t<T> geometry_from_geojson_value(const geojson_value& value);

template <typename T, geometry_type GeometryType, typename AllocatorType>
basic_geometrycollection<T, GeometryType, AllocatorType> geometrycollection_from_geojson_value(const geojson_value& value);

}  // namespace detail
}  // namespace io

template <typename T>
class geometry_t : public basic_geometry<geometry_t<T>>
{
  public:
    // default constructor
    geometry_t() = default;

    // copy constructor
    geometry_t(const geometry_t& other)
        : m_geom_type(other.m_geom_type)
    {
        switch (m_geom_type)
        {
            // point variants live inline in the union, a trivial copy suffices
            case geometry_type::POINT:
            case geometry_type::POINTZ:
            case geometry_type::POINTM:
            case geometry_type::POINTZM:
            {
                m_value = other.m_value;
                break;
            }
            case geometry_type::MULTIPOINT:
            {
                m_value.m_multipoint = new multipoint_t<T>(*other.m_value.m_multipoint);
                break;
            }
            case geometry_type::MULTIPOINTZ:
            {
                m_value.m_multipoint_z = new multipoint_z_t<T>(*other.m_value.m_multipoint_z);
                break;
            }
            case geometry_type::MULTIPOINTM:
            {
                m_value.m_multipoint_m = new multipoint_m_t<T>(*other.m_value.m_multipoint_m);
                break;
            }
            case geometry_type::MULTIPOINTZM:
            {
                m_value.m_multipoint_zm = new multipoint_zm_t<T>(*other.m_value.m_multipoint_zm);
                break;
            }
            case geometry_type::LINESTRING:
            {
                m_value.m_linestring = new linestring_t<T>(*other.m_value.m_linestring);
                break;
            }
            case geometry_type::LINESTRINGZ:
            {
                m_value.m_linestring_z = new linestring_z_t<T>(*other.m_value.m_linestring_z);
                break;
            }
            case geometry_type::LINESTRINGM:
            {
                m_value.m_linestring_m = new linestring_m_t<T>(*other.m_value.m_linestring_m);
                break;
            }
            case geometry_type::LINESTRINGZM:
            {
                m_value.m_linestring_zm = new linestring_zm_t<T>(*other.m_value.m_linestring_zm);
                break;
            }
            case geometry_type::MULTILINESTRING:
            {
                m_value.m_multilinestring = new multilinestring_t<T>(*other.m_value.m_multilinestring);
                break;
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                m_value.m_multilinestring_z = new multilinestring_z_t<T>(*other.m_value.m_multilinestring_z);
                break;
            }
            case geometry_type::MULTILINESTRINGM:
            {
                m_value.m_multilinestring_m = new multilinestring_m_t<T>(*other.m_value.m_multilinestring_m);
                break;
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                m_value.m_multilinestring_zm = new multilinestring_zm_t<T>(*other.m_value.m_multilinestring_zm);
                break;
            }
            case geometry_type::POLYGON:
            {
                m_value.m_polygon = new polygon_t<T>(*other.m_value.m_polygon);
                break;
            }
            case geometry_type::POLYGONZ:
            {
                m_value.m_polygon_z = new polygon_z_t<T>(*other.m_value.m_polygon_z);
                break;
            }
            case geometry_type::POLYGONM:
            {
                m_value.m_polygon_m = new polygon_m_t<T>(*other.m_value.m_polygon_m);
                break;
            }
            case geometry_type::POLYGONZM:
            {
                m_value.m_polygon_zm = new polygon_zm_t<T>(*other.m_value.m_polygon_zm);
                break;
            }
            case geometry_type::MULTIPOLYGON:
            {
                m_value.m_multipolygon = new multipolygon_t<T>(*other.m_value.m_multipolygon);
                break;
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                m_value.m_multipolygon_z = new multipolygon_z_t<T>(*other.m_value.m_multipolygon_z);
                break;
            }
            case geometry_type::MULTIPOLYGONM:
            {
                m_value.m_multipolygon_m = new multipolygon_m_t<T>(*other.m_value.m_multipolygon_m);
                break;
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                m_value.m_multipolygon_zm = new multipolygon_zm_t<T>(*other.m_value.m_multipolygon_zm);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTION:
            {
                m_value.m_geometrycollection = new geometrycollection_t<T>(*other.m_value.m_geometrycollection);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONZ:
            {
                m_value.m_geometrycollection_z = new geometrycollection_z_t<T>(*other.m_value.m_geometrycollection_z);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONM:
            {
                m_value.m_geometrycollection_m = new geometrycollection_m_t<T>(*other.m_value.m_geometrycollection_m);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                m_value.m_geometrycollection_zm = new geometrycollection_zm_t<T>(*other.m_value.m_geometrycollection_zm);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    // copy assignment
    geometry_t& operator=(const geometry_t& other)
    {
        geometry_t temp(other);
        swap(*this, temp);
        return *this;
    }

    // move constructor
    geometry_t(geometry_t&& other) noexcept
        : m_value(other.m_value), m_geom_type(other.m_geom_type)
    {
        other.m_value     = geom_value{};
        other.m_geom_type = geometry_type::GEOMETRY;
    }

    // move assignment
    geometry_t& operator=(geometry_t&& other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    friend void swap(geometry_t& lhs, geometry_t& rhs) noexcept
    {
        using std::swap;
        swap(lhs.m_value, rhs.m_value);
        swap(lhs.m_geom_type, rhs.m_geom_type);
    }

    // point

    explicit geometry_t(const point_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POINT)
    {
    }

    explicit geometry_t(const point_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POINTZ)
    {
    }

    explicit geometry_t(const point_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POINTM)
    {
    }

    explicit geometry_t(const point_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POINTZM)
    {
    }

    // multipoint

    explicit geometry_t(multipoint_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOINT)
    {
    }

    explicit geometry_t(multipoint_z_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOINTZ)
    {
    }

    explicit geometry_t(multipoint_m_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOINTM)
    {
    }

    explicit geometry_t(multipoint_zm_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOINTZM)
    {
    }

    // linestring

    explicit geometry_t(linestring_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::LINESTRING)
    {
    }

    explicit geometry_t(linestring_z_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::LINESTRINGZ)
    {
    }

    explicit geometry_t(linestring_m_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::LINESTRINGM)
    {
    }

    explicit geometry_t(linestring_zm_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::LINESTRINGZM)
    {
    }

    // multilinestring

    explicit geometry_t(multilinestring_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTILINESTRING)
    {
    }

    explicit geometry_t(multilinestring_z_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTILINESTRINGZ)
    {
    }

    explicit geometry_t(multilinestring_m_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTILINESTRINGM)
    {
    }

    explicit geometry_t(multilinestring_zm_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTILINESTRINGZM)
    {
    }

    // polygon

    explicit geometry_t(polygon_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::POLYGON)
    {
    }

    explicit geometry_t(polygon_z_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::POLYGONZ)
    {
    }

    explicit geometry_t(polygon_m_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::POLYGONM)
    {
    }

    explicit geometry_t(polygon_zm_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::POLYGONZM)
    {
    }

    // multipolygon

    explicit geometry_t(multipolygon_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOLYGON)
    {
    }

    explicit geometry_t(multipolygon_z_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOLYGONZ)
    {
    }

    explicit geometry_t(multipolygon_m_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOLYGONM)
    {
    }

    explicit geometry_t(multipolygon_zm_t<T> value)
        : m_value(std::move(value)), m_geom_type(geometry_type::MULTIPOLYGONZM)
    {
    }

    // geometrycollection

    explicit geometry_t(geometrycollection_t<T> value);

    explicit geometry_t(geometrycollection_z_t<T> value);

    explicit geometry_t(geometrycollection_m_t<T> value);

    explicit geometry_t(geometrycollection_zm_t<T> value);

    ~geometry_t();

    // getters

    template <typename ReturnType>
    ReturnType* get()
    {
        return get_impl_(static_cast<ReturnType*>(nullptr));
    }

    template <typename ReturnType>
    const ReturnType* get() const
    {
        return get_impl_(static_cast<const ReturnType*>(nullptr));
    }

    // point

    inline bool is_point() const noexcept
    {
        return m_geom_type == geometry_type::POINT;
    }

    inline bool is_point_z() const noexcept
    {
        return m_geom_type == geometry_type::POINTZ;
    }

    inline bool is_point_m() const noexcept
    {
        return m_geom_type == geometry_type::POINTM;
    }

    inline bool is_point_zm() const noexcept
    {
        return m_geom_type == geometry_type::POINTZM;
    }

    // multipoint

    inline bool is_multipoint() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINT;
    }

    inline bool is_multipoint_z() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTZ;
    }

    inline bool is_multipoint_m() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTM;
    }

    inline bool is_multipoint_zm() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTZM;
    }

    // linestring

    inline bool is_linestring() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRING;
    }

    inline bool is_linestring_z() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGZ;
    }

    inline bool is_linestring_m() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGM;
    }

    inline bool is_linestring_zm() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGZM;
    }

    // multilinestring

    inline bool is_multilinestring() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRING;
    }

    inline bool is_multilinestring_z() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZ;
    }

    inline bool is_multilinestring_m() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGM;
    }

    inline bool is_multilinestring_zm() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZM;
    }

    // polygon

    inline bool is_polygon() const noexcept
    {
        return m_geom_type == geometry_type::POLYGON;
    }

    inline bool is_polygon_z() const noexcept
    {
        return m_geom_type == geometry_type::POLYGONZ;
    }

    inline bool is_polygon_m() const noexcept
    {
        return m_geom_type == geometry_type::POLYGONM;
    }

    inline bool is_polygon_zm() const noexcept
    {
        return m_geom_type == geometry_type::POLYGONZM;
    }

    // multipolygon

    inline bool is_multipolygon() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGON;
    }

    inline bool is_multipolygon_z() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZ;
    }

    inline bool is_multipolygon_m() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONM;
    }

    inline bool is_multipolygon_zm() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZM;
    }

    // geometrycollection

    inline bool is_geometrycollection() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTION;
    }

    inline bool is_geometrycollection_z() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZ;
    }

    inline bool is_geometrycollection_m() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONM;
    }

    inline bool is_geometrycollection_zm() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZM;
    }

    // typed getters, they check the geometry type tag and return nullptr on mismatch

    point_t<T>* get_point() noexcept
    {
        return m_geom_type == geometry_type::POINT ? &m_value.m_point : nullptr;
    }

    const point_t<T>* get_point() const noexcept
    {
        return m_geom_type == geometry_type::POINT ? &m_value.m_point : nullptr;
    }

    point_z_t<T>* get_point_z() noexcept
    {
        return m_geom_type == geometry_type::POINTZ ? &m_value.m_point_z : nullptr;
    }

    const point_z_t<T>* get_point_z() const noexcept
    {
        return m_geom_type == geometry_type::POINTZ ? &m_value.m_point_z : nullptr;
    }

    point_m_t<T>* get_point_m() noexcept
    {
        return m_geom_type == geometry_type::POINTM ? &m_value.m_point_m : nullptr;
    }

    const point_m_t<T>* get_point_m() const noexcept
    {
        return m_geom_type == geometry_type::POINTM ? &m_value.m_point_m : nullptr;
    }

    point_zm_t<T>* get_point_zm() noexcept
    {
        return m_geom_type == geometry_type::POINTZM ? &m_value.m_point_zm : nullptr;
    }

    const point_zm_t<T>* get_point_zm() const noexcept
    {
        return m_geom_type == geometry_type::POINTZM ? &m_value.m_point_zm : nullptr;
    }

    multipoint_t<T>* get_multipoint() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINT ? m_value.m_multipoint : nullptr;
    }

    const multipoint_t<T>* get_multipoint() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINT ? m_value.m_multipoint : nullptr;
    }

    multipoint_z_t<T>* get_multipoint_z() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTZ ? m_value.m_multipoint_z : nullptr;
    }

    const multipoint_z_t<T>* get_multipoint_z() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTZ ? m_value.m_multipoint_z : nullptr;
    }

    multipoint_m_t<T>* get_multipoint_m() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTM ? m_value.m_multipoint_m : nullptr;
    }

    const multipoint_m_t<T>* get_multipoint_m() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTM ? m_value.m_multipoint_m : nullptr;
    }

    multipoint_zm_t<T>* get_multipoint_zm() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTZM ? m_value.m_multipoint_zm : nullptr;
    }

    const multipoint_zm_t<T>* get_multipoint_zm() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOINTZM ? m_value.m_multipoint_zm : nullptr;
    }

    linestring_t<T>* get_linestring() noexcept
    {
        return m_geom_type == geometry_type::LINESTRING ? m_value.m_linestring : nullptr;
    }

    const linestring_t<T>* get_linestring() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRING ? m_value.m_linestring : nullptr;
    }

    linestring_z_t<T>* get_linestring_z() noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGZ ? m_value.m_linestring_z : nullptr;
    }

    const linestring_z_t<T>* get_linestring_z() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGZ ? m_value.m_linestring_z : nullptr;
    }

    linestring_m_t<T>* get_linestring_m() noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGM ? m_value.m_linestring_m : nullptr;
    }

    const linestring_m_t<T>* get_linestring_m() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGM ? m_value.m_linestring_m : nullptr;
    }

    linestring_zm_t<T>* get_linestring_zm() noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGZM ? m_value.m_linestring_zm : nullptr;
    }

    const linestring_zm_t<T>* get_linestring_zm() const noexcept
    {
        return m_geom_type == geometry_type::LINESTRINGZM ? m_value.m_linestring_zm : nullptr;
    }

    multilinestring_t<T>* get_multilinestring() noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRING ? m_value.m_multilinestring : nullptr;
    }

    const multilinestring_t<T>* get_multilinestring() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRING ? m_value.m_multilinestring : nullptr;
    }

    multilinestring_z_t<T>* get_multilinestring_z() noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZ ? m_value.m_multilinestring_z : nullptr;
    }

    const multilinestring_z_t<T>* get_multilinestring_z() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZ ? m_value.m_multilinestring_z : nullptr;
    }

    multilinestring_m_t<T>* get_multilinestring_m() noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGM ? m_value.m_multilinestring_m : nullptr;
    }

    const multilinestring_m_t<T>* get_multilinestring_m() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGM ? m_value.m_multilinestring_m : nullptr;
    }

    multilinestring_zm_t<T>* get_multilinestring_zm() noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZM ? m_value.m_multilinestring_zm : nullptr;
    }

    const multilinestring_zm_t<T>* get_multilinestring_zm() const noexcept
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZM ? m_value.m_multilinestring_zm : nullptr;
    }

    polygon_t<T>* get_polygon() noexcept
    {
        return m_geom_type == geometry_type::POLYGON ? m_value.m_polygon : nullptr;
    }

    const polygon_t<T>* get_polygon() const noexcept
    {
        return m_geom_type == geometry_type::POLYGON ? m_value.m_polygon : nullptr;
    }

    polygon_z_t<T>* get_polygon_z() noexcept
    {
        return m_geom_type == geometry_type::POLYGONZ ? m_value.m_polygon_z : nullptr;
    }

    const polygon_z_t<T>* get_polygon_z() const noexcept
    {
        return m_geom_type == geometry_type::POLYGONZ ? m_value.m_polygon_z : nullptr;
    }

    polygon_m_t<T>* get_polygon_m() noexcept
    {
        return m_geom_type == geometry_type::POLYGONM ? m_value.m_polygon_m : nullptr;
    }

    const polygon_m_t<T>* get_polygon_m() const noexcept
    {
        return m_geom_type == geometry_type::POLYGONM ? m_value.m_polygon_m : nullptr;
    }

    polygon_zm_t<T>* get_polygon_zm() noexcept
    {
        return m_geom_type == geometry_type::POLYGONZM ? m_value.m_polygon_zm : nullptr;
    }

    const polygon_zm_t<T>* get_polygon_zm() const noexcept
    {
        return m_geom_type == geometry_type::POLYGONZM ? m_value.m_polygon_zm : nullptr;
    }

    multipolygon_t<T>* get_multipolygon() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGON ? m_value.m_multipolygon : nullptr;
    }

    const multipolygon_t<T>* get_multipolygon() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGON ? m_value.m_multipolygon : nullptr;
    }

    multipolygon_z_t<T>* get_multipolygon_z() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZ ? m_value.m_multipolygon_z : nullptr;
    }

    const multipolygon_z_t<T>* get_multipolygon_z() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZ ? m_value.m_multipolygon_z : nullptr;
    }

    multipolygon_m_t<T>* get_multipolygon_m() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONM ? m_value.m_multipolygon_m : nullptr;
    }

    const multipolygon_m_t<T>* get_multipolygon_m() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONM ? m_value.m_multipolygon_m : nullptr;
    }

    multipolygon_zm_t<T>* get_multipolygon_zm() noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZM ? m_value.m_multipolygon_zm : nullptr;
    }

    const multipolygon_zm_t<T>* get_multipolygon_zm() const noexcept
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZM ? m_value.m_multipolygon_zm : nullptr;
    }

    geometrycollection_t<T>* get_geometrycollection() noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTION ? m_value.m_geometrycollection : nullptr;
    }

    const geometrycollection_t<T>* get_geometrycollection() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTION ? m_value.m_geometrycollection : nullptr;
    }

    geometrycollection_z_t<T>* get_geometrycollection_z() noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZ ? m_value.m_geometrycollection_z : nullptr;
    }

    const geometrycollection_z_t<T>* get_geometrycollection_z() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZ ? m_value.m_geometrycollection_z : nullptr;
    }

    geometrycollection_m_t<T>* get_geometrycollection_m() noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONM ? m_value.m_geometrycollection_m : nullptr;
    }

    const geometrycollection_m_t<T>* get_geometrycollection_m() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONM ? m_value.m_geometrycollection_m : nullptr;
    }

    geometrycollection_zm_t<T>* get_geometrycollection_zm() noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZM ? m_value.m_geometrycollection_zm : nullptr;
    }

    const geometrycollection_zm_t<T>* get_geometrycollection_zm() const noexcept
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZM ? m_value.m_geometrycollection_zm : nullptr;
    }

  private:
    /// for allow basic_geometry to access basic_point_zm private members
    friend class basic_geometry<geometry_t<T>>;

    static geometry_t<T> from_geometrycollection_wkt_(const std::string& wkt);

    union geom_value
    {
        // point variants are stored inline, wrapping a point never allocates
        point_t<T> m_point;
        point_z_t<T> m_point_z;
        point_m_t<T> m_point_m;
        point_zm_t<T> m_point_zm;

        // containers are heap-allocated and owned through raw pointers,
        // released by the destructor switch on the geometry type tag
        multipoint_t<T>* m_multipoint;
        multipoint_z_t<T>* m_multipoint_z;
        multipoint_m_t<T>* m_multipoint_m;
        multipoint_zm_t<T>* m_multipoint_zm;
        linestring_t<T>* m_linestring;
        linestring_z_t<T>* m_linestring_z;
        linestring_m_t<T>* m_linestring_m;
        linestring_zm_t<T>* m_linestring_zm;
        multilinestring_t<T>* m_multilinestring;
        multilinestring_z_t<T>* m_multilinestring_z;
        multilinestring_m_t<T>* m_multilinestring_m;
        multilinestring_zm_t<T>* m_multilinestring_zm;
        polygon_t<T>* m_polygon;
        polygon_z_t<T>* m_polygon_z;
        polygon_m_t<T>* m_polygon_m;
        polygon_zm_t<T>* m_polygon_zm;
        multipolygon_t<T>* m_multipolygon;
        multipolygon_z_t<T>* m_multipolygon_z;
        multipolygon_m_t<T>* m_multipolygon_m;
        multipolygon_zm_t<T>* m_multipolygon_zm;
        geometrycollection_t<T>* m_geometrycollection;
        geometrycollection_z_t<T>* m_geometrycollection_z;
        geometrycollection_m_t<T>* m_geometrycollection_m;
        geometrycollection_zm_t<T>* m_geometrycollection_zm;

        // a defaulted constructor would be deleted because the point variants have
        // a non-trivial default constructor, activate an empty point instead
        geom_value()
            : m_point()
        {
        }

        // point

        explicit geom_value(const point_t<T>& p)
            : m_point(p)
        {
        }

        explicit geom_value(const point_z_t<T>& p)
            : m_point_z(p)
        {
        }

        explicit geom_value(const point_m_t<T>& p)
            : m_point_m(p)
        {
        }

        explicit geom_value(const point_zm_t<T>& p)
            : m_point_zm(p)
        {
        }

        // containers, taken by value and moved into the heap allocation

        explicit geom_value(multipoint_t<T> v)
            : m_multipoint(new multipoint_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipoint_z_t<T> v)
            : m_multipoint_z(new multipoint_z_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipoint_m_t<T> v)
            : m_multipoint_m(new multipoint_m_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipoint_zm_t<T> v)
            : m_multipoint_zm(new multipoint_zm_t<T>(std::move(v)))
        {
        }

        explicit geom_value(linestring_t<T> v)
            : m_linestring(new linestring_t<T>(std::move(v)))
        {
        }

        explicit geom_value(linestring_z_t<T> v)
            : m_linestring_z(new linestring_z_t<T>(std::move(v)))
        {
        }

        explicit geom_value(linestring_m_t<T> v)
            : m_linestring_m(new linestring_m_t<T>(std::move(v)))
        {
        }

        explicit geom_value(linestring_zm_t<T> v)
            : m_linestring_zm(new linestring_zm_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multilinestring_t<T> v)
            : m_multilinestring(new multilinestring_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multilinestring_z_t<T> v)
            : m_multilinestring_z(new multilinestring_z_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multilinestring_m_t<T> v)
            : m_multilinestring_m(new multilinestring_m_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multilinestring_zm_t<T> v)
            : m_multilinestring_zm(new multilinestring_zm_t<T>(std::move(v)))
        {
        }

        explicit geom_value(polygon_t<T> v)
            : m_polygon(new polygon_t<T>(std::move(v)))
        {
        }

        explicit geom_value(polygon_z_t<T> v)
            : m_polygon_z(new polygon_z_t<T>(std::move(v)))
        {
        }

        explicit geom_value(polygon_m_t<T> v)
            : m_polygon_m(new polygon_m_t<T>(std::move(v)))
        {
        }

        explicit geom_value(polygon_zm_t<T> v)
            : m_polygon_zm(new polygon_zm_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipolygon_t<T> v)
            : m_multipolygon(new multipolygon_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipolygon_z_t<T> v)
            : m_multipolygon_z(new multipolygon_z_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipolygon_m_t<T> v)
            : m_multipolygon_m(new multipolygon_m_t<T>(std::move(v)))
        {
        }

        explicit geom_value(multipolygon_zm_t<T> v)
            : m_multipolygon_zm(new multipolygon_zm_t<T>(std::move(v)))
        {
        }
    };

    geom_value m_value        = {};
    geometry_type m_geom_type = geometry_type::GEOMETRY;

    static_assert(std::is_trivially_copyable<point_t<T>>::value, "point_t must be trivially copyable for inline union storage");
    static_assert(std::is_trivially_copyable<point_z_t<T>>::value, "point_z_t must be trivially copyable for inline union storage");
    static_assert(std::is_trivially_copyable<point_m_t<T>>::value, "point_m_t must be trivially copyable for inline union storage");
    static_assert(std::is_trivially_copyable<point_zm_t<T>>::value, "point_zm_t must be trivially copyable for inline union storage");

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return m_geom_type;
    }

    /// @private
    template <typename Visitor>
    auto visit_(Visitor&& visitor) const -> decltype(visitor(std::declval<const point_t<T>&>()))
    {
        switch (m_geom_type)
        {
            case geometry_type::POINT:
                return visitor(m_value.m_point);
            case geometry_type::POINTZ:
                return visitor(m_value.m_point_z);
            case geometry_type::POINTM:
                return visitor(m_value.m_point_m);
            case geometry_type::POINTZM:
                return visitor(m_value.m_point_zm);
            case geometry_type::MULTIPOINT:
                return visitor(*m_value.m_multipoint);
            case geometry_type::MULTIPOINTZ:
                return visitor(*m_value.m_multipoint_z);
            case geometry_type::MULTIPOINTM:
                return visitor(*m_value.m_multipoint_m);
            case geometry_type::MULTIPOINTZM:
                return visitor(*m_value.m_multipoint_zm);
            case geometry_type::LINESTRING:
                return visitor(*m_value.m_linestring);
            case geometry_type::LINESTRINGZ:
                return visitor(*m_value.m_linestring_z);
            case geometry_type::LINESTRINGM:
                return visitor(*m_value.m_linestring_m);
            case geometry_type::LINESTRINGZM:
                return visitor(*m_value.m_linestring_zm);
            case geometry_type::MULTILINESTRING:
                return visitor(*m_value.m_multilinestring);
            case geometry_type::MULTILINESTRINGZ:
                return visitor(*m_value.m_multilinestring_z);
            case geometry_type::MULTILINESTRINGM:
                return visitor(*m_value.m_multilinestring_m);
            case geometry_type::MULTILINESTRINGZM:
                return visitor(*m_value.m_multilinestring_zm);
            case geometry_type::POLYGON:
                return visitor(*m_value.m_polygon);
            case geometry_type::POLYGONZ:
                return visitor(*m_value.m_polygon_z);
            case geometry_type::POLYGONM:
                return visitor(*m_value.m_polygon_m);
            case geometry_type::POLYGONZM:
                return visitor(*m_value.m_polygon_zm);
            case geometry_type::MULTIPOLYGON:
                return visitor(*m_value.m_multipolygon);
            case geometry_type::MULTIPOLYGONZ:
                return visitor(*m_value.m_multipolygon_z);
            case geometry_type::MULTIPOLYGONM:
                return visitor(*m_value.m_multipolygon_m);
            case geometry_type::MULTIPOLYGONZM:
                return visitor(*m_value.m_multipolygon_zm);
            case geometry_type::GEOMETRYCOLLECTION:
                return visitor(*m_value.m_geometrycollection);
            case geometry_type::GEOMETRYCOLLECTIONZ:
                return visitor(*m_value.m_geometrycollection_z);
            case geometry_type::GEOMETRYCOLLECTIONM:
                return visitor(*m_value.m_geometrycollection_m);
            case geometry_type::GEOMETRYCOLLECTIONZM:
                return visitor(*m_value.m_geometrycollection_zm);
            default:
                return visitor(m_value.m_point);
        }
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (m_geom_type == geometry_type::GEOMETRY)
        {
            return true;
        }
        return visit_([](const auto& g) { return g.is_closed(); });
    }

    /// @private
    void throw_for_invalid_() const
    {
        if (m_geom_type == geometry_type::GEOMETRY)
        {
            return;
        }
        visit_([](const auto& g) { g.throw_for_invalid(); });
    }

    /// @private
    bounds_t bounds_() const
    {
        if (m_geom_type == geometry_type::GEOMETRY)
        {
            return {};
        }
        return visit_([](const auto& g) { return g.bounds(); });
    }

    // tag dispatch for get<>, one overload per supported type

    point_t<T>* get_impl_(point_t<T>*) noexcept
    {
        return get_point();
    }

    const point_t<T>* get_impl_(const point_t<T>*) const noexcept
    {
        return get_point();
    }

    point_z_t<T>* get_impl_(point_z_t<T>*) noexcept
    {
        return get_point_z();
    }

    const point_z_t<T>* get_impl_(const point_z_t<T>*) const noexcept
    {
        return get_point_z();
    }

    point_m_t<T>* get_impl_(point_m_t<T>*) noexcept
    {
        return get_point_m();
    }

    const point_m_t<T>* get_impl_(const point_m_t<T>*) const noexcept
    {
        return get_point_m();
    }

    point_zm_t<T>* get_impl_(point_zm_t<T>*) noexcept
    {
        return get_point_zm();
    }

    const point_zm_t<T>* get_impl_(const point_zm_t<T>*) const noexcept
    {
        return get_point_zm();
    }

    multipoint_t<T>* get_impl_(multipoint_t<T>*) noexcept
    {
        return get_multipoint();
    }

    const multipoint_t<T>* get_impl_(const multipoint_t<T>*) const noexcept
    {
        return get_multipoint();
    }

    multipoint_z_t<T>* get_impl_(multipoint_z_t<T>*) noexcept
    {
        return get_multipoint_z();
    }

    const multipoint_z_t<T>* get_impl_(const multipoint_z_t<T>*) const noexcept
    {
        return get_multipoint_z();
    }

    multipoint_m_t<T>* get_impl_(multipoint_m_t<T>*) noexcept
    {
        return get_multipoint_m();
    }

    const multipoint_m_t<T>* get_impl_(const multipoint_m_t<T>*) const noexcept
    {
        return get_multipoint_m();
    }

    multipoint_zm_t<T>* get_impl_(multipoint_zm_t<T>*) noexcept
    {
        return get_multipoint_zm();
    }

    const multipoint_zm_t<T>* get_impl_(const multipoint_zm_t<T>*) const noexcept
    {
        return get_multipoint_zm();
    }

    linestring_t<T>* get_impl_(linestring_t<T>*) noexcept
    {
        return get_linestring();
    }

    const linestring_t<T>* get_impl_(const linestring_t<T>*) const noexcept
    {
        return get_linestring();
    }

    linestring_z_t<T>* get_impl_(linestring_z_t<T>*) noexcept
    {
        return get_linestring_z();
    }

    const linestring_z_t<T>* get_impl_(const linestring_z_t<T>*) const noexcept
    {
        return get_linestring_z();
    }

    linestring_m_t<T>* get_impl_(linestring_m_t<T>*) noexcept
    {
        return get_linestring_m();
    }

    const linestring_m_t<T>* get_impl_(const linestring_m_t<T>*) const noexcept
    {
        return get_linestring_m();
    }

    linestring_zm_t<T>* get_impl_(linestring_zm_t<T>*) noexcept
    {
        return get_linestring_zm();
    }

    const linestring_zm_t<T>* get_impl_(const linestring_zm_t<T>*) const noexcept
    {
        return get_linestring_zm();
    }

    multilinestring_t<T>* get_impl_(multilinestring_t<T>*) noexcept
    {
        return get_multilinestring();
    }

    const multilinestring_t<T>* get_impl_(const multilinestring_t<T>*) const noexcept
    {
        return get_multilinestring();
    }

    multilinestring_z_t<T>* get_impl_(multilinestring_z_t<T>*) noexcept
    {
        return get_multilinestring_z();
    }

    const multilinestring_z_t<T>* get_impl_(const multilinestring_z_t<T>*) const noexcept
    {
        return get_multilinestring_z();
    }

    multilinestring_m_t<T>* get_impl_(multilinestring_m_t<T>*) noexcept
    {
        return get_multilinestring_m();
    }

    const multilinestring_m_t<T>* get_impl_(const multilinestring_m_t<T>*) const noexcept
    {
        return get_multilinestring_m();
    }

    multilinestring_zm_t<T>* get_impl_(multilinestring_zm_t<T>*) noexcept
    {
        return get_multilinestring_zm();
    }

    const multilinestring_zm_t<T>* get_impl_(const multilinestring_zm_t<T>*) const noexcept
    {
        return get_multilinestring_zm();
    }

    polygon_t<T>* get_impl_(polygon_t<T>*) noexcept
    {
        return get_polygon();
    }

    const polygon_t<T>* get_impl_(const polygon_t<T>*) const noexcept
    {
        return get_polygon();
    }

    polygon_z_t<T>* get_impl_(polygon_z_t<T>*) noexcept
    {
        return get_polygon_z();
    }

    const polygon_z_t<T>* get_impl_(const polygon_z_t<T>*) const noexcept
    {
        return get_polygon_z();
    }

    polygon_m_t<T>* get_impl_(polygon_m_t<T>*) noexcept
    {
        return get_polygon_m();
    }

    const polygon_m_t<T>* get_impl_(const polygon_m_t<T>*) const noexcept
    {
        return get_polygon_m();
    }

    polygon_zm_t<T>* get_impl_(polygon_zm_t<T>*) noexcept
    {
        return get_polygon_zm();
    }

    const polygon_zm_t<T>* get_impl_(const polygon_zm_t<T>*) const noexcept
    {
        return get_polygon_zm();
    }

    multipolygon_t<T>* get_impl_(multipolygon_t<T>*) noexcept
    {
        return get_multipolygon();
    }

    const multipolygon_t<T>* get_impl_(const multipolygon_t<T>*) const noexcept
    {
        return get_multipolygon();
    }

    multipolygon_z_t<T>* get_impl_(multipolygon_z_t<T>*) noexcept
    {
        return get_multipolygon_z();
    }

    const multipolygon_z_t<T>* get_impl_(const multipolygon_z_t<T>*) const noexcept
    {
        return get_multipolygon_z();
    }

    multipolygon_m_t<T>* get_impl_(multipolygon_m_t<T>*) noexcept
    {
        return get_multipolygon_m();
    }

    const multipolygon_m_t<T>* get_impl_(const multipolygon_m_t<T>*) const noexcept
    {
        return get_multipolygon_m();
    }

    multipolygon_zm_t<T>* get_impl_(multipolygon_zm_t<T>*) noexcept
    {
        return get_multipolygon_zm();
    }

    const multipolygon_zm_t<T>* get_impl_(const multipolygon_zm_t<T>*) const noexcept
    {
        return get_multipolygon_zm();
    }

    geometrycollection_t<T>* get_impl_(geometrycollection_t<T>*) noexcept
    {
        return get_geometrycollection();
    }

    const geometrycollection_t<T>* get_impl_(const geometrycollection_t<T>*) const noexcept
    {
        return get_geometrycollection();
    }

    geometrycollection_z_t<T>* get_impl_(geometrycollection_z_t<T>*) noexcept
    {
        return get_geometrycollection_z();
    }

    const geometrycollection_z_t<T>* get_impl_(const geometrycollection_z_t<T>*) const noexcept
    {
        return get_geometrycollection_z();
    }

    geometrycollection_m_t<T>* get_impl_(geometrycollection_m_t<T>*) noexcept
    {
        return get_geometrycollection_m();
    }

    const geometrycollection_m_t<T>* get_impl_(const geometrycollection_m_t<T>*) const noexcept
    {
        return get_geometrycollection_m();
    }

    geometrycollection_zm_t<T>* get_impl_(geometrycollection_zm_t<T>*) noexcept
    {
        return get_geometrycollection_zm();
    }

    const geometrycollection_zm_t<T>* get_impl_(const geometrycollection_zm_t<T>*) const noexcept
    {
        return get_geometrycollection_zm();
    }

    // json

    /// @private
    static geometry_t<T> from_json_(const std::string& json)
    {
        try
        {
            auto j = io::geojson_parser::parse(json);
            return io::detail::geometry_from_geojson_value<T>(j);
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::string out;
        write_json_(out, precision);
        return out;
    }

    /// @private
    void write_json_(std::string& out, std::int32_t precision) const
    {
        if (m_geom_type == geometry_type::GEOMETRY)
        {
            return;
        }
        visit_([&out, precision](const auto& g) { g.write_json(out, precision); });
    }

    // wkt

    /// @private
    static geometry_t<T> from_wkt_(const std::string& wkt)
    {
        if (detail::wkt_starts_with_geometrycollection(wkt))
        {
            return from_geometrycollection_wkt_(wkt);
        }

        // a single parse provides the geometry type, the coordinates and the offsets,
        // the concrete geometry is built directly from them without re-parsing
        wkt_reader reader{};
        auto result        = reader.read(wkt);
        const auto& data   = result.data;
        const auto& coords = data.coords;
        switch (data.geom_type)
        {
            case geometry_type::POINT:
            {
                if (coords.empty())
                {
                    return geometry_t<T>(point_t<T>{});
                }
                return geometry_t<T>(point_t<T>{coords[0], coords[1]});
            }
            case geometry_type::POINTZ:
            {
                if (coords.empty())
                {
                    return geometry_t<T>(point_z_t<T>{});
                }
                return geometry_t<T>(point_z_t<T>{coords[0], coords[1], coords[2]});
            }
            case geometry_type::POINTM:
            {
                if (coords.empty())
                {
                    return geometry_t<T>(point_m_t<T>{});
                }
                return geometry_t<T>(point_m_t<T>{coords[0], coords[1], coords[2]});
            }
            case geometry_type::POINTZM:
            {
                if (coords.empty())
                {
                    return geometry_t<T>(point_zm_t<T>{});
                }
                return geometry_t<T>(point_zm_t<T>{coords[0], coords[1], coords[2], coords[3]});
            }
            case geometry_type::MULTIPOINT:
            {
                return geometry_t<T>(multipoint_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::MULTIPOINTZ:
            {
                return geometry_t<T>(multipoint_z_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::MULTIPOINTM:
            {
                return geometry_t<T>(multipoint_m_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::MULTIPOINTZM:
            {
                return geometry_t<T>(multipoint_zm_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::LINESTRING:
            {
                return geometry_t<T>(linestring_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::LINESTRINGZ:
            {
                return geometry_t<T>(linestring_z_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::LINESTRINGM:
            {
                return geometry_t<T>(linestring_m_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::LINESTRINGZM:
            {
                return geometry_t<T>(linestring_zm_t<T>(coords.begin(), coords.end()));
            }
            case geometry_type::MULTILINESTRING:
            {
                return geometry_t<T>(multilinestring_t<T>(coords.begin(), coords.end(),
                                                             data.line_offsets.begin(), data.line_offsets.end()));
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                return geometry_t<T>(multilinestring_z_t<T>(coords.begin(), coords.end(),
                                                             data.line_offsets.begin(), data.line_offsets.end()));
            }
            case geometry_type::MULTILINESTRINGM:
            {
                return geometry_t<T>(multilinestring_m_t<T>(coords.begin(), coords.end(),
                                                             data.line_offsets.begin(), data.line_offsets.end()));
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                return geometry_t<T>(multilinestring_zm_t<T>(coords.begin(), coords.end(),
                                                             data.line_offsets.begin(), data.line_offsets.end()));
            }
            case geometry_type::POLYGON:
            {
                polygon_t<T> polygon(coords.begin(), coords.end(),
                                        data.ring_offsets.begin(), data.ring_offsets.end());
                polygon.throw_for_invalid();
                return geometry_t<T>(std::move(polygon));
            }
            case geometry_type::POLYGONZ:
            {
                polygon_z_t<T> polygon(coords.begin(), coords.end(),
                                        data.ring_offsets.begin(), data.ring_offsets.end());
                polygon.throw_for_invalid();
                return geometry_t<T>(std::move(polygon));
            }
            case geometry_type::POLYGONM:
            {
                polygon_m_t<T> polygon(coords.begin(), coords.end(),
                                        data.ring_offsets.begin(), data.ring_offsets.end());
                polygon.throw_for_invalid();
                return geometry_t<T>(std::move(polygon));
            }
            case geometry_type::POLYGONZM:
            {
                polygon_zm_t<T> polygon(coords.begin(), coords.end(),
                                        data.ring_offsets.begin(), data.ring_offsets.end());
                polygon.throw_for_invalid();
                return geometry_t<T>(std::move(polygon));
            }
            case geometry_type::MULTIPOLYGON:
            {
                multipolygon_t<T> multipolygon(coords.begin(), coords.end(),
                                                  data.ring_offsets.begin(), data.ring_offsets.end(),
                                                  data.polygon_offsets.begin(), data.polygon_offsets.end());
                multipolygon.throw_for_invalid();
                return geometry_t<T>(std::move(multipolygon));
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                multipolygon_z_t<T> multipolygon(coords.begin(), coords.end(),
                                                  data.ring_offsets.begin(), data.ring_offsets.end(),
                                                  data.polygon_offsets.begin(), data.polygon_offsets.end());
                multipolygon.throw_for_invalid();
                return geometry_t<T>(std::move(multipolygon));
            }
            case geometry_type::MULTIPOLYGONM:
            {
                multipolygon_m_t<T> multipolygon(coords.begin(), coords.end(),
                                                  data.ring_offsets.begin(), data.ring_offsets.end(),
                                                  data.polygon_offsets.begin(), data.polygon_offsets.end());
                multipolygon.throw_for_invalid();
                return geometry_t<T>(std::move(multipolygon));
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                multipolygon_zm_t<T> multipolygon(coords.begin(), coords.end(),
                                                  data.ring_offsets.begin(), data.ring_offsets.end(),
                                                  data.polygon_offsets.begin(), data.polygon_offsets.end());
                multipolygon.throw_for_invalid();
                return geometry_t<T>(std::move(multipolygon));
            }
            default:
            {
                throw exceptions::parse_error("invalid wkt string");
            }
        }
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::string out;
        write_wkt_(out, precision);
        return out;
    }

    /// @private
    void write_wkt_(std::string& out, std::int32_t precision) const
    {
        if (m_geom_type == geometry_type::GEOMETRY)
        {
            return;
        }
        visit_([&out, precision](const auto& g) { g.write_wkt(out, precision); });
    }
};

template <typename T, geometry_type GeometryType, typename AllocatorType>
class basic_geometrycollection
    : public std::vector<geometry_t<T>, AllocatorType>,
      public basic_geometry<basic_geometrycollection<T, GeometryType, AllocatorType>>
{
  public:
    using base_type = std::vector<geometry_t<T>, AllocatorType>;

    basic_geometrycollection()
        : base_type() {}

    basic_geometrycollection(typename base_type::iterator first, typename base_type::iterator last)
        : base_type(first, last)
    {
    }

    basic_geometrycollection(typename base_type::const_iterator first, typename base_type::const_iterator last)
        : base_type(first, last)
    {
    }

    basic_geometrycollection(std::initializer_list<geometry_t<T>> init)
        : base_type(init.begin(), init.end()) {}

  private:
    friend class basic_geometry<basic_geometrycollection<T, GeometryType, AllocatorType>>;

    static std::string trim(const std::string& text)
    {
        auto begin = text.begin();
        while (begin != text.end() and std::isspace(static_cast<unsigned char>(*begin)))
        {
            ++begin;
        }

        auto end = text.end();
        while (end != begin and std::isspace(static_cast<unsigned char>(*(end - 1))))
        {
            --end;
        }

        return std::string(begin, end);
    }

    static std::vector<std::string> split_children(const std::string& text)
    {
        std::vector<std::string> res;
        int depth = 0;
        std::string current;
        for (char c : text)
        {
            if (c == ',' and depth == 0)
            {
                auto child = trim(current);
                if (child.empty())
                {
                    throw exceptions::parse_error("empty geometry collection child");
                }
                res.push_back(child);
                current.clear();
                continue;
            }

            if (c == '(')
            {
                ++depth;
            }
            else if (c == ')')
            {
                --depth;
                if (depth < 0)
                {
                    throw exceptions::parse_error("unbalanced geometry collection child");
                }
            }
            current.push_back(c);
        }

        if (depth != 0)
        {
            throw exceptions::parse_error("unbalanced geometry collection child");
        }

        auto child = trim(current);
        if (not child.empty())
        {
            res.push_back(child);
        }
        return res;
    }

    static std::string collection_body(const std::string& wkt)
    {
        const auto text = trim(wkt);
        const auto first_paren = text.find('(');
        if (first_paren == std::string::npos)
        {
            if (detail::wkt_contains_empty(text))
            {
                return "";
            }
            throw exceptions::parse_error("invalid geometry collection wkt string");
        }

        int depth = 0;
        for (size_t i = first_paren; i < text.size(); ++i)
        {
            if (text[i] == '(')
            {
                ++depth;
            }
            else if (text[i] == ')')
            {
                --depth;
                if (depth == 0)
                {
                    const auto tail = trim(text.substr(i + 1));
                    if (not tail.empty())
                    {
                        throw exceptions::parse_error("invalid geometry collection wkt string");
                    }
                    return text.substr(first_paren + 1, i - first_paren - 1);
                }
                if (depth < 0)
                {
                    throw exceptions::parse_error("invalid geometry collection wkt string");
                }
            }
        }

        throw exceptions::parse_error("invalid geometry collection wkt string");
    }

    geometry_type geom_type_() const noexcept
    {
        return GeometryType;
    }

    bool is_closed_() const noexcept
    {
        for (const auto& geom : *this)
        {
            if (not geom.is_closed())
            {
                return false;
            }
        }
        return true;
    }

    void throw_for_invalid_() const
    {
        for (const auto& geom : *this)
        {
            geom.throw_for_invalid();
        }
    }

    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& geom : *this)
        {
            res.extend(geom.bounds());
        }
        return res;
    }

    static basic_geometrycollection<T, GeometryType, AllocatorType> from_json_(const std::string& json)
    {
        try
        {
            auto j = io::geojson_parser::parse(json);
            return io::detail::geometrycollection_from_geojson_value<T, GeometryType, AllocatorType>(j);
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    std::string json_(std::int32_t precision = -1) const
    {
        std::string out;
        out.reserve(64 + this->size() * 64);
        write_json_(out, precision);
        return out;
    }

    /// @private
    void write_json_(std::string& out, std::int32_t precision) const
    {
        out += "{\"type\":\"GeometryCollection\",\"geometries\":[";
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (i > 0)
            {
                out += ',';
            }
            (*this)[i].write_json(out, precision);
        }
        out += "]}";
    }

    static basic_geometrycollection<T, GeometryType, AllocatorType> from_wkt_(const std::string& wkt)
    {
        const auto parsed_type = detail::wkt_collection_type(wkt);
        if (parsed_type != GeometryType)
        {
            throw exceptions::parse_error("invalid wkt string");
        }

        const auto body = trim(collection_body(wkt));
        if (body.empty())
        {
            return {};
        }

        auto children = split_children(body);
        basic_geometrycollection<T, GeometryType, AllocatorType> res;
        res.reserve(children.size());
        for (const auto& child : children)
        {
            res.emplace_back(geometry_t<T>::from_wkt(child));
        }
        return res;
    }

    std::string wkt_(std::int32_t precision = -1) const
    {
        std::string out;
        out.reserve(32 + this->size() * 64);
        write_wkt_(out, precision);
        return out;
    }

    /// @private
    void write_wkt_(std::string& out, std::int32_t precision) const
    {
        out += "GEOMETRYCOLLECTION";
        if (this->has_z())
        {
            out += 'Z';
        }
        if (this->has_m())
        {
            out += 'M';
        }
        if (this->empty())
        {
            out += " EMPTY";
            return;
        }

        out += '(';
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (i > 0)
            {
                out += ',';
            }
            (*this)[i].write_wkt(out, precision);
        }
        out += ')';
    }
};

namespace io
{
namespace detail
{

inline void require_geojson_object(const geojson_value& value)
{
    if (not value.is_object())
    {
        throw exceptions::parse_error("GeoJSON geometry must be an object");
    }
}

inline const geojson_value& require_geojson_member(const geojson_value& value, const std::string& key)
{
    require_geojson_object(value);
    if (not value.has_key(key))
    {
        throw exceptions::parse_error("GeoJSON object is missing '" + key + "'");
    }
    return value.at(key);
}

inline void update_geojson_dimension(int& dimension, int candidate)
{
    if (candidate != 2 and candidate != 3 and candidate != 4)
    {
        throw exceptions::parse_error("invalid coordinate count");
    }
    if (dimension == 0)
    {
        dimension = candidate;
        return;
    }
    if (dimension != candidate)
    {
        throw exceptions::parse_error("mixed coordinate dimensions");
    }
}

inline void scan_geojson_coordinate_dimensions(const geojson_value& value, int& dimension)
{
    if (not value.is_array())
    {
        throw exceptions::parse_error("coordinates must be an array");
    }
    if (value.empty())
    {
        return;
    }

    const auto& values = value.as_array();
    if (values[0].is_number())
    {
        for (const auto& coord : values)
        {
            if (not coord.is_number())
            {
                throw exceptions::parse_error("mixed coordinate values");
            }
        }
        update_geojson_dimension(dimension, static_cast<int>(values.size()));
        return;
    }

    for (const auto& child : values)
    {
        scan_geojson_coordinate_dimensions(child, dimension);
    }
}

inline int infer_geojson_dimension(const geojson_value& coordinates)
{
    int dimension = 0;
    scan_geojson_coordinate_dimensions(coordinates, dimension);
    return dimension == 0 ? 2 : dimension;
}

template <typename PointType>
PointType make_geojson_point(const geojson_value& value)
{
    auto values = value.as_double_array();
    if (values.empty())
    {
        return PointType();
    }
    if (values.size() != PointType::N)
    {
        throw exceptions::parse_error("invalid coordinate count");
    }

    std::vector<typename PointType::coord_type> coords;
    coords.reserve(values.size());
    for (auto coord : values)
    {
        coords.push_back(static_cast<typename PointType::coord_type>(coord));
    }
    return PointType(coords.begin(), coords.end());
}

template <typename LineStringType>
LineStringType make_geojson_linestring(const geojson_value& value)
{
    const auto& values = value.as_array();
    using point_type = typename LineStringType::point_type;

    std::vector<point_type> points;
    points.reserve(values.size());
    for (const auto& coord : values)
    {
        points.emplace_back(make_geojson_point<point_type>(coord));
    }
    return LineStringType(points.begin(), points.end());
}

template <typename PolygonType>
PolygonType make_geojson_polygon(const geojson_value& value)
{
    const auto& values = value.as_array();
    using ring_type = typename PolygonType::value_type;

    std::vector<ring_type> rings;
    rings.reserve(values.size());
    for (const auto& ring : values)
    {
        rings.emplace_back(make_geojson_linestring<ring_type>(ring));
    }
    return PolygonType(rings.begin(), rings.end());
}

template <typename MultiLineStringType>
MultiLineStringType make_geojson_multilinestring(const geojson_value& value)
{
    const auto& values = value.as_array();
    using linestring_type = typename MultiLineStringType::value_type;

    std::vector<linestring_type> linestrings;
    linestrings.reserve(values.size());
    for (const auto& linestring : values)
    {
        linestrings.emplace_back(make_geojson_linestring<linestring_type>(linestring));
    }
    return MultiLineStringType(linestrings.begin(), linestrings.end());
}

template <typename MultiPolygonType>
MultiPolygonType make_geojson_multipolygon(const geojson_value& value)
{
    const auto& values = value.as_array();
    using polygon_type = typename MultiPolygonType::polygon_type;

    std::vector<polygon_type> polygons;
    polygons.reserve(values.size());
    for (const auto& polygon : values)
    {
        polygons.emplace_back(make_geojson_polygon<polygon_type>(polygon));
    }
    return MultiPolygonType(polygons.begin(), polygons.end());
}

template <typename T>
geometry_t<T> point_from_geojson_coordinates(const geojson_value& coordinates, int dimension)
{
    switch (dimension)
    {
        case 2:
            return geometry_t<T>(make_geojson_point<point_t<T>>(coordinates));
        case 3:
            return geometry_t<T>(make_geojson_point<point_z_t<T>>(coordinates));
        case 4:
            return geometry_t<T>(make_geojson_point<point_zm_t<T>>(coordinates));
        default:
            throw exceptions::parse_error("invalid coordinate count");
    }
}

template <typename T>
geometry_t<T> multipoint_from_geojson_coordinates(const geojson_value& coordinates, int dimension)
{
    switch (dimension)
    {
        case 2:
            return geometry_t<T>(make_geojson_linestring<multipoint_t<T>>(coordinates));
        case 3:
            return geometry_t<T>(make_geojson_linestring<multipoint_z_t<T>>(coordinates));
        case 4:
            return geometry_t<T>(make_geojson_linestring<multipoint_zm_t<T>>(coordinates));
        default:
            throw exceptions::parse_error("invalid coordinate count");
    }
}

template <typename T>
geometry_t<T> linestring_from_geojson_coordinates(const geojson_value& coordinates, int dimension)
{
    switch (dimension)
    {
        case 2:
            return geometry_t<T>(make_geojson_linestring<linestring_t<T>>(coordinates));
        case 3:
            return geometry_t<T>(make_geojson_linestring<linestring_z_t<T>>(coordinates));
        case 4:
            return geometry_t<T>(make_geojson_linestring<linestring_zm_t<T>>(coordinates));
        default:
            throw exceptions::parse_error("invalid coordinate count");
    }
}

template <typename T>
geometry_t<T> multilinestring_from_geojson_coordinates(const geojson_value& coordinates, int dimension)
{
    switch (dimension)
    {
        case 2:
            return geometry_t<T>(make_geojson_multilinestring<multilinestring_t<T>>(coordinates));
        case 3:
            return geometry_t<T>(make_geojson_multilinestring<multilinestring_z_t<T>>(coordinates));
        case 4:
            return geometry_t<T>(make_geojson_multilinestring<multilinestring_zm_t<T>>(coordinates));
        default:
            throw exceptions::parse_error("invalid coordinate count");
    }
}

template <typename T>
geometry_t<T> polygon_from_geojson_coordinates(const geojson_value& coordinates, int dimension)
{
    switch (dimension)
    {
        case 2:
            return geometry_t<T>(make_geojson_polygon<polygon_t<T>>(coordinates));
        case 3:
            return geometry_t<T>(make_geojson_polygon<polygon_z_t<T>>(coordinates));
        case 4:
            return geometry_t<T>(make_geojson_polygon<polygon_zm_t<T>>(coordinates));
        default:
            throw exceptions::parse_error("invalid coordinate count");
    }
}

template <typename T>
geometry_t<T> multipolygon_from_geojson_coordinates(const geojson_value& coordinates, int dimension)
{
    switch (dimension)
    {
        case 2:
            return geometry_t<T>(make_geojson_multipolygon<multipolygon_t<T>>(coordinates));
        case 3:
            return geometry_t<T>(make_geojson_multipolygon<multipolygon_z_t<T>>(coordinates));
        case 4:
            return geometry_t<T>(make_geojson_multipolygon<multipolygon_zm_t<T>>(coordinates));
        default:
            throw exceptions::parse_error("invalid coordinate count");
    }
}

template <typename T, geometry_type GeometryType, typename AllocatorType>
basic_geometrycollection<T, GeometryType, AllocatorType> geometrycollection_from_geojson_value(const geojson_value& value)
{
    require_geojson_object(value);
    const auto geom_type = require_geojson_member(value, "type").as_string();
    if (geom_type != "GeometryCollection")
    {
        throw exceptions::parse_error("invalid geometry type: " + geom_type);
    }

    const auto& geometries = require_geojson_member(value, "geometries").as_array();
    basic_geometrycollection<T, GeometryType, AllocatorType> res;
    res.reserve(geometries.size());
    for (const auto& geometry : geometries)
    {
        if (geometry.is_null())
        {
            throw exceptions::parse_error("GeometryCollection contains null geometry");
        }
        res.emplace_back(geometry_from_geojson_value<T>(geometry));
    }
    return res;
}

template <typename T>
geometry_t<T> geometry_from_geojson_value(const geojson_value& value)
{
    require_geojson_object(value);
    const auto geom_type = require_geojson_member(value, "type").as_string();

    if (geom_type == "GeometryCollection")
    {
        return geometry_t<T>(geometrycollection_from_geojson_value<T, geometry_type::GEOMETRYCOLLECTION, std::allocator<geometry_t<T>>>(value));
    }

    const auto& coordinates = require_geojson_member(value, "coordinates");
    const auto dimension = infer_geojson_dimension(coordinates);

    if (geom_type == "Point")
    {
        return point_from_geojson_coordinates<T>(coordinates, dimension);
    }
    if (geom_type == "MultiPoint")
    {
        return multipoint_from_geojson_coordinates<T>(coordinates, dimension);
    }
    if (geom_type == "LineString")
    {
        return linestring_from_geojson_coordinates<T>(coordinates, dimension);
    }
    if (geom_type == "MultiLineString")
    {
        return multilinestring_from_geojson_coordinates<T>(coordinates, dimension);
    }
    if (geom_type == "Polygon")
    {
        return polygon_from_geojson_coordinates<T>(coordinates, dimension);
    }
    if (geom_type == "MultiPolygon")
    {
        return multipolygon_from_geojson_coordinates<T>(coordinates, dimension);
    }

    throw exceptions::parse_error("unsupported GeoJSON geometry type: " + geom_type);
}

}  // namespace detail
}  // namespace io

template <typename T>
geometry_t<T>::geometry_t(geometrycollection_t<T> value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTION)
{
    m_value.m_geometrycollection = new geometrycollection_t<T>(std::move(value));
}

template <typename T>
geometry_t<T>::geometry_t(geometrycollection_z_t<T> value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONZ)
{
    m_value.m_geometrycollection_z = new geometrycollection_z_t<T>(std::move(value));
}

template <typename T>
geometry_t<T>::geometry_t(geometrycollection_m_t<T> value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONM)
{
    m_value.m_geometrycollection_m = new geometrycollection_m_t<T>(std::move(value));
}

template <typename T>
geometry_t<T>::geometry_t(geometrycollection_zm_t<T> value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONZM)
{
    m_value.m_geometrycollection_zm = new geometrycollection_zm_t<T>(std::move(value));
}

template <typename T>
geometry_t<T>::~geometry_t()
{
    switch (m_geom_type)
    {
        // point variants are stored inline in the union, nothing to delete
        case geometry_type::MULTIPOINT:
            delete m_value.m_multipoint;
            break;
        case geometry_type::MULTIPOINTZ:
            delete m_value.m_multipoint_z;
            break;
        case geometry_type::MULTIPOINTM:
            delete m_value.m_multipoint_m;
            break;
        case geometry_type::MULTIPOINTZM:
            delete m_value.m_multipoint_zm;
            break;
        case geometry_type::LINESTRING:
            delete m_value.m_linestring;
            break;
        case geometry_type::LINESTRINGZ:
            delete m_value.m_linestring_z;
            break;
        case geometry_type::LINESTRINGM:
            delete m_value.m_linestring_m;
            break;
        case geometry_type::LINESTRINGZM:
            delete m_value.m_linestring_zm;
            break;
        case geometry_type::MULTILINESTRING:
            delete m_value.m_multilinestring;
            break;
        case geometry_type::MULTILINESTRINGZ:
            delete m_value.m_multilinestring_z;
            break;
        case geometry_type::MULTILINESTRINGM:
            delete m_value.m_multilinestring_m;
            break;
        case geometry_type::MULTILINESTRINGZM:
            delete m_value.m_multilinestring_zm;
            break;
        case geometry_type::POLYGON:
            delete m_value.m_polygon;
            break;
        case geometry_type::POLYGONZ:
            delete m_value.m_polygon_z;
            break;
        case geometry_type::POLYGONM:
            delete m_value.m_polygon_m;
            break;
        case geometry_type::POLYGONZM:
            delete m_value.m_polygon_zm;
            break;
        case geometry_type::MULTIPOLYGON:
            delete m_value.m_multipolygon;
            break;
        case geometry_type::MULTIPOLYGONZ:
            delete m_value.m_multipolygon_z;
            break;
        case geometry_type::MULTIPOLYGONM:
            delete m_value.m_multipolygon_m;
            break;
        case geometry_type::MULTIPOLYGONZM:
            delete m_value.m_multipolygon_zm;
            break;
        case geometry_type::GEOMETRYCOLLECTION:
            delete m_value.m_geometrycollection;
            break;
        case geometry_type::GEOMETRYCOLLECTIONZ:
            delete m_value.m_geometrycollection_z;
            break;
        case geometry_type::GEOMETRYCOLLECTIONM:
            delete m_value.m_geometrycollection_m;
            break;
        case geometry_type::GEOMETRYCOLLECTIONZM:
            delete m_value.m_geometrycollection_zm;
            break;
        default:
            break;
    }
}

template <typename T>
geometry_t<T> geometry_t<T>::from_geometrycollection_wkt_(const std::string& wkt)
{
    switch (detail::wkt_collection_type(wkt))
    {
        case geometry_type::GEOMETRYCOLLECTION:
            return geometry_t<T>(geometrycollection_t<T>::from_wkt(wkt));
        case geometry_type::GEOMETRYCOLLECTIONZ:
            return geometry_t<T>(geometrycollection_z_t<T>::from_wkt(wkt));
        case geometry_type::GEOMETRYCOLLECTIONM:
            return geometry_t<T>(geometrycollection_m_t<T>::from_wkt(wkt));
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return geometry_t<T>(geometrycollection_zm_t<T>::from_wkt(wkt));
        default:
            throw exceptions::parse_error("invalid geometry collection wkt string");
    }
}


template <typename>
struct is_basic_geometrycollection : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection<geometrycollection_t<T>> : std::true_type
{};

template <typename>
struct is_basic_geometrycollection_z : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection_z<geometrycollection_z_t<T>> : std::true_type
{};

template <typename>
struct is_basic_geometrycollection_m : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection_m<geometrycollection_m_t<T>> : std::true_type
{};

template <typename>
struct is_basic_geometrycollection_zm : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection_zm<geometrycollection_zm_t<T>> : std::true_type
{};

using geometrycollection    = geometrycollection_t<double>;
using geometrycollection_z  = geometrycollection_z_t<double>;
using geometrycollection_m  = geometrycollection_m_t<double>;
using geometrycollection_zm = geometrycollection_zm_t<double>;

using GeometryCollection   = geometrycollection_t<double>;
using GeometryCollectionZ  = geometrycollection_z_t<double>;
using GeometryCollectionM  = geometrycollection_m_t<double>;
using GeometryCollectionZM = geometrycollection_zm_t<double>;

using geometry = geometry_t<double>;
using Geometry = geometry_t<double>;

}  // namespace shapes
}  // namespace simo
