#pragma once

#include <algorithm>
#include <ciso646>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <simo/geom/detail/geometry.hpp>
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
    geometry_t()
    {
        std::cout << "DEFAULT CONSTRUCTOR" << std::endl;
    }

    // copy constructor:
    geometry_t(const geometry_t& other)
    {
        std::cout << "COPY CONSTRUCTOR" << std::endl;
        m_geom_type = other.geom_type();
        switch (other.geom_type())
        {
                // point

            case geometry_type::POINT:
            {
                m_value = geom_value(*other.m_value.m_point);
                break;
            }
            case geometry_type::POINTZ:
            {
                m_value = geom_value(*other.m_value.m_point_z);
                break;
            }
            case geometry_type::POINTM:
            {
                m_value = geom_value(*other.m_value.m_point_m);
                break;
            }
            case geometry_type::POINTZM:
            {
                m_value = geom_value(*other.m_value.m_point_zm);
                break;
            }

                // multipoint

            case geometry_type::MULTIPOINT:
            {
                m_value = geom_value(*other.m_value.m_multipoint);
                break;
            }
            case geometry_type::MULTIPOINTZ:
            {
                m_value = geom_value(*other.m_value.m_multipoint_z);
                break;
            }
            case geometry_type::MULTIPOINTM:
            {
                m_value = geom_value(*other.m_value.m_multipoint_m);
                break;
            }
            case geometry_type::MULTIPOINTZM:
            {
                m_value = geom_value(*other.m_value.m_multipoint_zm);
                break;
            }

                // linestring

            case geometry_type::LINESTRING:
            {
                m_value = geom_value(*other.m_value.m_linestring);
                break;
            }
            case geometry_type::LINESTRINGZ:
            {
                m_value = geom_value(*other.m_value.m_linestring_z);
                break;
            }
            case geometry_type::LINESTRINGM:
            {
                m_value = geom_value(*other.m_value.m_linestring_m);
                break;
            }
            case geometry_type::LINESTRINGZM:
            {
                m_value = geom_value(*other.m_value.m_linestring_zm);
                break;
            }

                // multilinestring

            case geometry_type::MULTILINESTRING:
            {
                m_value = geom_value(*other.m_value.m_multilinestring);
                break;
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                m_value = geom_value(*other.m_value.m_multilinestring_z);
                break;
            }
            case geometry_type::MULTILINESTRINGM:
            {
                m_value = geom_value(*other.m_value.m_multilinestring_m);
                break;
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                m_value = geom_value(*other.m_value.m_multilinestring_zm);
                break;
            }

                // polygon

            case geometry_type::POLYGON:
            {
                m_value = geom_value(*other.m_value.m_polygon);
                break;
            }
            case geometry_type::POLYGONZ:
            {
                m_value = geom_value(*other.m_value.m_polygon_z);
                break;
            }
            case geometry_type::POLYGONM:
            {
                m_value = geom_value(*other.m_value.m_polygon_m);
                break;
            }
            case geometry_type::POLYGONZM:
            {
                m_value = geom_value(*other.m_value.m_polygon_zm);
                break;
            }

                // multipolygon

            case geometry_type::MULTIPOLYGON:
            {
                m_value = geom_value(*other.m_value.m_multipolygon);
                break;
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                m_value = geom_value(*other.m_value.m_multipolygon_z);
                break;
            }
            case geometry_type::MULTIPOLYGONM:
            {
                m_value = geom_value(*other.m_value.m_multipolygon_m);
                break;
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                m_value = geom_value(*other.m_value.m_multipolygon_zm);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTION:
            {
                copy_geometrycollection_(other);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONZ:
            {
                copy_geometrycollection_z_(other);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONM:
            {
                copy_geometrycollection_m_(other);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                copy_geometrycollection_zm_(other);
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
        std::cout << "COPY ASSIGNMENT" << std::endl;
        geometry_t temp(other);
        swap(*this, temp);
        return *this;
    }

    // move constructor
    geometry_t(geometry_t&& other) noexcept
        : geometry_t()
    {
        std::cout << "MOVE CONSTRUCTOR" << std::endl;
        swap(*this, other);
    }

    friend void swap(geometry_t& lhs, geometry_t& rhs)  // nothrow
    {
        using std::swap;
        swap(lhs.m_value, rhs.m_value);
        swap(lhs.m_geom_type, rhs.m_geom_type);
        swap(lhs.m_geometrycollection, rhs.m_geometrycollection);
        swap(lhs.m_geometrycollection_z, rhs.m_geometrycollection_z);
        swap(lhs.m_geometrycollection_m, rhs.m_geometrycollection_m);
        swap(lhs.m_geometrycollection_zm, rhs.m_geometrycollection_zm);
    }

    // point

    explicit geometry_t(const point_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINT)
    {
    }

    explicit geometry_t(const point_z_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINTZ)
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

    explicit geometry_t(const multipoint_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINT)
    {
    }

    explicit geometry_t(const multipoint_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINTZ)
    {
    }

    explicit geometry_t(const multipoint_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINTM)
    {
    }

    explicit geometry_t(const multipoint_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINTZM)
    {
    }

    // linestring

    explicit geometry_t(const linestring_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRING)
    {
    }

    explicit geometry_t(const linestring_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRINGZ)
    {
    }

    explicit geometry_t(const linestring_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRINGM)
    {
    }

    explicit geometry_t(const linestring_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRINGZM)
    {
    }

    // multilinestring

    explicit geometry_t(const multilinestring_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRING)
    {
    }

    explicit geometry_t(const multilinestring_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRINGZ)
    {
    }

    explicit geometry_t(const multilinestring_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRINGM)
    {
    }

    explicit geometry_t(const multilinestring_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRINGZM)
    {
    }

    // polygon

    explicit geometry_t(const polygon_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGON)
    {
    }

    explicit geometry_t(const polygon_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGONZ)
    {
    }

    explicit geometry_t(const polygon_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGONM)
    {
    }

    explicit geometry_t(const polygon_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGONZM)
    {
    }

    // multipolygon

    explicit geometry_t(const multipolygon_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGON)
    {
    }

    explicit geometry_t(const multipolygon_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGONZ)
    {
    }

    explicit geometry_t(const multipolygon_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGONM)
    {
    }

    explicit geometry_t(const multipolygon_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGONZM)
    {
    }

    explicit geometry_t(const geometrycollection_t<T>& value);

    explicit geometry_t(const geometrycollection_z_t<T>& value);

    explicit geometry_t(const geometrycollection_m_t<T>& value);

    explicit geometry_t(const geometrycollection_zm_t<T>& value);

    ~geometry_t()
    {
        switch (m_geom_type)
        {
                // point

            case geometry_type::POINT:
            {
                delete m_value.m_point;
                m_value.m_point = nullptr;
                std::cout << "DELETE POINT" << std::endl;
                break;
            }
            case geometry_type::POINTZ:
            {
                delete m_value.m_point_z;
                m_value.m_point_z = nullptr;
                std::cout << "DELETE POINT Z" << std::endl;
                break;
            }
            case geometry_type::POINTM:
            {
                delete m_value.m_point_m;
                m_value.m_point_m = nullptr;
                std::cout << "DELETE POINT M" << std::endl;
                break;
            }
            case geometry_type::POINTZM:
            {
                delete m_value.m_point_zm;
                m_value.m_point_zm = nullptr;
                std::cout << "DELETE POINT ZM" << std::endl;
                break;
            }

                // multipoint

            case geometry_type::MULTIPOINT:
            {
                delete m_value.m_multipoint;
                m_value.m_multipoint = nullptr;
                std::cout << "DELETE MULTIPOINT" << std::endl;
                break;
            }
            case geometry_type::MULTIPOINTZ:
            {
                delete m_value.m_multipoint_z;
                m_value.m_multipoint_z = nullptr;
                std::cout << "DELETE MULTIPOINT Z" << std::endl;
                break;
            }
            case geometry_type::MULTIPOINTM:
            {
                delete m_value.m_multipoint_m;
                m_value.m_multipoint_m = nullptr;
                std::cout << "DELETE MULTIPOINT M" << std::endl;
                break;
            }
            case geometry_type::MULTIPOINTZM:
            {
                delete m_value.m_multipoint_zm;
                m_value.m_multipoint_zm = nullptr;
                std::cout << "DELETE MULTIPOINT ZM" << std::endl;
                break;
            }

                // linestring

            case geometry_type::LINESTRING:
            {
                delete m_value.m_linestring;
                m_value.m_linestring = nullptr;
                std::cout << "DELETE LINESTRING" << std::endl;
                break;
            }
            case geometry_type::LINESTRINGZ:
            {
                delete m_value.m_linestring_z;
                m_value.m_linestring_z = nullptr;
                std::cout << "DELETE LINESTRING Z" << std::endl;
                break;
            }
            case geometry_type::LINESTRINGM:
            {
                delete m_value.m_linestring_m;
                m_value.m_linestring_m = nullptr;
                std::cout << "DELETE LINESTRING M" << std::endl;
                break;
            }
            case geometry_type::LINESTRINGZM:
            {
                delete m_value.m_linestring_zm;
                m_value.m_linestring_zm = nullptr;
                std::cout << "DELETE LINESTRING ZM" << std::endl;
                break;
            }

                // multilinestring

            case geometry_type::MULTILINESTRING:
            {
                delete m_value.m_multilinestring;
                m_value.m_multilinestring = nullptr;
                std::cout << "DELETE MULTILINESTRING" << std::endl;
                break;
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                delete m_value.m_multilinestring_z;
                m_value.m_multilinestring_z = nullptr;
                std::cout << "DELETE MULTILINESTRING Z" << std::endl;
                break;
            }
            case geometry_type::MULTILINESTRINGM:
            {
                delete m_value.m_multilinestring_m;
                m_value.m_multilinestring_m = nullptr;
                std::cout << "DELETE MULTILINESTRING M" << std::endl;
                break;
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                delete m_value.m_multilinestring_zm;
                m_value.m_multilinestring_zm = nullptr;
                std::cout << "DELETE MULTILINESTRING ZM" << std::endl;
                break;
            }

                // polygon

            case geometry_type::POLYGON:
            {
                delete m_value.m_polygon;
                m_value.m_polygon = nullptr;
                std::cout << "DELETE POLYGON" << std::endl;
                break;
            }
            case geometry_type::POLYGONZ:
            {
                delete m_value.m_polygon_z;
                m_value.m_polygon_z = nullptr;
                std::cout << "DELETE POLYGON Z" << std::endl;
                break;
            }
            case geometry_type::POLYGONM:
            {
                delete m_value.m_polygon_m;
                m_value.m_polygon_m = nullptr;
                std::cout << "DELETE POLYGON M" << std::endl;
                break;
            }
            case geometry_type::POLYGONZM:
            {
                delete m_value.m_polygon_zm;
                m_value.m_polygon_zm = nullptr;
                std::cout << "DELETE POLYGON ZM" << std::endl;
                break;
            }

                // multipolygon

            case geometry_type::MULTIPOLYGON:
            {
                delete m_value.m_multipolygon;
                m_value.m_multipolygon = nullptr;
                std::cout << "DELETE MULTIPOLYGON" << std::endl;
                break;
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                delete m_value.m_multipolygon_z;
                m_value.m_multipolygon_z = nullptr;
                std::cout << "DELETE MULTIPOLYGON Z" << std::endl;
                break;
            }
            case geometry_type::MULTIPOLYGONM:
            {
                delete m_value.m_multipolygon_m;
                m_value.m_multipolygon_m = nullptr;
                std::cout << "DELETE MULTIPOLYGON M" << std::endl;
                break;
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                delete m_value.m_multipolygon_zm;
                m_value.m_multipolygon_zm = nullptr;
                std::cout << "DELETE MULTIPOLYGON ZM" << std::endl;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    // getters

    template <typename ReturnType>
    ReturnType* get()
    {
        // point

        if (is_basic_point<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point());
        }
        if (is_basic_point_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point_z());
        }
        if (is_basic_point_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point_m());
        }
        if (is_basic_point_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point_zm());
        }

        // multipoint

        if (is_basic_multipoint<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint());
        }
        if (is_basic_multipoint_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint_z());
        }
        if (is_basic_multipoint_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint_m());
        }
        if (is_basic_multipoint_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint_zm());
        }

        // linestring

        if (is_basic_linestring<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring());
        }
        if (is_basic_linestring_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring_z());
        }
        if (is_basic_linestring_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring_m());
        }
        if (is_basic_linestring_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring_zm());
        }

        // multilinestring

        if (is_basic_multilinestring<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring());
        }
        if (is_basic_multilinestring_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring_z());
        }
        if (is_basic_multilinestring_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring_m());
        }
        if (is_basic_multilinestring_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring_zm());
        }

        // polygon

        if (is_basic_polygon<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon());
        }
        if (is_basic_polygon_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon_z());
        }
        if (is_basic_polygon_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon_m());
        }
        if (is_basic_polygon_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon_zm());
        }

        // multipolygon

        if (is_basic_multipolygon<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon());
        }
        if (is_basic_multipolygon_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon_z());
        }
        if (is_basic_multipolygon_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon_m());
        }
        if (is_basic_multipolygon_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon_zm());
        }

        // geometrycollection

        if (is_basic_geometrycollection<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection());
        }
        if (is_basic_geometrycollection_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection_z());
        }
        if (is_basic_geometrycollection_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection_m());
        }
        if (is_basic_geometrycollection_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection_zm());
        }

        return nullptr;
    }

    // point

    inline bool is_point()
    {
        return m_geom_type == geometry_type::POINT;
    }

    inline bool is_point_z()
    {
        return m_geom_type == geometry_type::POINTZ;
    }

    inline bool is_point_m()
    {
        return m_geom_type == geometry_type::POINTM;
    }

    inline bool is_point_zm()
    {
        return m_geom_type == geometry_type::POINTZM;
    }

    // multipoint

    inline bool is_multipoint()
    {
        return m_geom_type == geometry_type::MULTIPOINT;
    }

    inline bool is_multipoint_z()
    {
        return m_geom_type == geometry_type::MULTIPOINTZ;
    }

    inline bool is_multipoint_m()
    {
        return m_geom_type == geometry_type::MULTIPOINTM;
    }

    inline bool is_multipoint_zm()
    {
        return m_geom_type == geometry_type::MULTIPOINTZM;
    }

    // linestring

    inline bool is_linestring()
    {
        return m_geom_type == geometry_type::LINESTRING;
    }

    inline bool is_linestring_z()
    {
        return m_geom_type == geometry_type::LINESTRINGZ;
    }

    inline bool is_linestring_m()
    {
        return m_geom_type == geometry_type::LINESTRINGM;
    }

    inline bool is_linestring_zm()
    {
        return m_geom_type == geometry_type::LINESTRINGZM;
    }

    // multilinestring

    inline bool is_multilinestring()
    {
        return m_geom_type == geometry_type::MULTILINESTRING;
    }

    inline bool is_multilinestring_z()
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZ;
    }

    inline bool is_multilinestring_m()
    {
        return m_geom_type == geometry_type::MULTILINESTRINGM;
    }

    inline bool is_multilinestring_zm()
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZM;
    }

    // polygon

    inline bool is_polygon()
    {
        return m_geom_type == geometry_type::POLYGON;
    }

    inline bool is_polygon_z()
    {
        return m_geom_type == geometry_type::POLYGONZ;
    }

    inline bool is_polygon_m()
    {
        return m_geom_type == geometry_type::POLYGONM;
    }

    inline bool is_polygon_zm()
    {
        return m_geom_type == geometry_type::POLYGONZM;
    }

    // multipolygon

    inline bool is_multipolygon()
    {
        return m_geom_type == geometry_type::MULTIPOLYGON;
    }

    inline bool is_multipolygon_z()
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZ;
    }

    inline bool is_multipolygon_m()
    {
        return m_geom_type == geometry_type::MULTIPOLYGONM;
    }

    inline bool is_multipolygon_zm()
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZM;
    }

    // geometrycollection

    inline bool is_geometrycollection()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTION;
    }

    inline bool is_geometrycollection_z()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZ;
    }

    inline bool is_geometrycollection_m()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONM;
    }

    inline bool is_geometrycollection_zm()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZM;
    }

    // point

    point_t<T>* get_point()
    {
        assert(is_point());
        return m_value.m_point;
    }

    const point_t<T>* get_point() const
    {
        assert(m_geom_type == geometry_type::POINT);
        return m_value.m_point;
    }

    point_z_t<T>* get_point_z()
    {
        assert(is_point_z());
        return m_value.m_point_z;
    }

    const point_z_t<T>* get_point_z() const
    {
        assert(m_geom_type == geometry_type::POINTZ);
        return m_value.m_point_z;
    }

    point_m_t<T>* get_point_m()
    {
        assert(is_point_m());
        return m_value.m_point_m;
    }

    const point_m_t<T>* get_point_m() const
    {
        assert(m_geom_type == geometry_type::POINTM);
        return m_value.m_point_m;
    }

    point_zm_t<T>* get_point_zm()
    {
        assert(is_point_zm());
        return m_value.m_point_zm;
    }

    const point_zm_t<T>* get_point_zm() const
    {
        assert(m_geom_type == geometry_type::POINTZM);
        return m_value.m_point_zm;
    }

    // multipoint

    multipoint_t<T>* get_multipoint()
    {
        assert(is_multipoint());
        return m_value.m_multipoint;
    }

    const multipoint_t<T>* get_multipoint() const
    {
        assert(m_geom_type == geometry_type::MULTIPOINT);
        return m_value.m_multipoint;
    }

    multipoint_z_t<T>* get_multipoint_z()
    {
        assert(is_multipoint_z());
        return m_value.m_multipoint_z;
    }

    const multipoint_z_t<T>* get_multipoint_z() const
    {
        assert(m_geom_type == geometry_type::MULTIPOINTZ);
        return m_value.m_multipoint_z;
    }

    multipoint_m_t<T>* get_multipoint_m()
    {
        assert(is_multipoint_m());
        return m_value.m_multipoint_m;
    }

    const multipoint_m_t<T>* get_multipoint_m() const
    {
        assert(m_geom_type == geometry_type::MULTIPOINTM);
        return m_value.m_multipoint_m;
    }

    multipoint_zm_t<T>* get_multipoint_zm()
    {
        assert(is_multipoint_zm());
        return m_value.m_multipoint_zm;
    }

    const multipoint_zm_t<T>* get_multipoint_zm() const
    {
        assert(m_geom_type == geometry_type::MULTIPOINTZM);
        return m_value.m_multipoint_zm;
    }

    // linestring

    linestring_t<T>* get_linestring()
    {
        assert(is_linestring());
        return m_value.m_linestring;
    }

    const linestring_t<T>* get_linestring() const
    {
        assert(m_geom_type == geometry_type::LINESTRING);
        return m_value.m_linestring;
    }

    linestring_z_t<T>* get_linestring_z()
    {
        assert(is_linestring_z());
        return m_value.m_linestring_z;
    }

    const linestring_z_t<T>* get_linestring_z() const
    {
        assert(m_geom_type == geometry_type::LINESTRINGZ);
        return m_value.m_linestring_z;
    }

    linestring_m_t<T>* get_linestring_m()
    {
        assert(is_linestring_m());
        return m_value.m_linestring_m;
    }

    const linestring_m_t<T>* get_linestring_m() const
    {
        assert(m_geom_type == geometry_type::LINESTRINGM);
        return m_value.m_linestring_m;
    }

    linestring_zm_t<T>* get_linestring_zm()
    {
        assert(is_linestring_zm());
        return m_value.m_linestring_zm;
    }

    const linestring_zm_t<T>* get_linestring_zm() const
    {
        assert(m_geom_type == geometry_type::LINESTRINGZM);
        return m_value.m_linestring_zm;
    }

    // multilinestring

    multilinestring_t<T>* get_multilinestring()
    {
        assert(is_multilinestring());
        return m_value.m_multilinestring;
    }

    const multilinestring_t<T>* get_multilinestring() const
    {
        assert(m_geom_type == geometry_type::MULTILINESTRING);
        return m_value.m_multilinestring;
    }

    multilinestring_z_t<T>* get_multilinestring_z()
    {
        assert(is_multilinestring_z());
        return m_value.m_multilinestring_z;
    }

    const multilinestring_z_t<T>* get_multilinestring_z() const
    {
        assert(m_geom_type == geometry_type::MULTILINESTRINGZ);
        return m_value.m_multilinestring_z;
    }

    multilinestring_m_t<T>* get_multilinestring_m()
    {
        assert(is_multilinestring_m());
        return m_value.m_multilinestring_m;
    }

    const multilinestring_m_t<T>* get_multilinestring_m() const
    {
        assert(m_geom_type == geometry_type::MULTILINESTRINGM);
        return m_value.m_multilinestring_m;
    }

    multilinestring_zm_t<T>* get_multilinestring_zm()
    {
        assert(is_multilinestring_zm());
        return m_value.m_multilinestring_zm;
    }

    const multilinestring_zm_t<T>* get_multilinestring_zm() const
    {
        assert(m_geom_type == geometry_type::MULTILINESTRINGZM);
        return m_value.m_multilinestring_zm;
    }

    // polygon

    polygon_t<T>* get_polygon()
    {
        assert(is_polygon());
        return m_value.m_polygon;
    }

    const polygon_t<T>* get_polygon() const
    {
        assert(m_geom_type == geometry_type::POLYGON);
        return m_value.m_polygon;
    }

    polygon_z_t<T>* get_polygon_z()
    {
        assert(is_polygon_z());
        return m_value.m_polygon_z;
    }

    const polygon_z_t<T>* get_polygon_z() const
    {
        assert(m_geom_type == geometry_type::POLYGONZ);
        return m_value.m_polygon_z;
    }

    polygon_m_t<T>* get_polygon_m()
    {
        assert(is_polygon_m());
        return m_value.m_polygon_m;
    }

    const polygon_m_t<T>* get_polygon_m() const
    {
        assert(m_geom_type == geometry_type::POLYGONM);
        return m_value.m_polygon_m;
    }

    polygon_zm_t<T>* get_polygon_zm()
    {
        assert(is_polygon_zm());
        return m_value.m_polygon_zm;
    }

    const polygon_zm_t<T>* get_polygon_zm() const
    {
        assert(m_geom_type == geometry_type::POLYGONZM);
        return m_value.m_polygon_zm;
    }

    // multipolygon

    multipolygon_t<T>* get_multipolygon()
    {
        assert(is_multipolygon());
        return m_value.m_multipolygon;
    }

    const multipolygon_t<T>* get_multipolygon() const
    {
        assert(m_geom_type == geometry_type::MULTIPOLYGON);
        return m_value.m_multipolygon;
    }

    multipolygon_z_t<T>* get_multipolygon_z()
    {
        assert(is_multipolygon_z());
        return m_value.m_multipolygon_z;
    }

    const multipolygon_z_t<T>* get_multipolygon_z() const
    {
        assert(m_geom_type == geometry_type::MULTIPOLYGONZ);
        return m_value.m_multipolygon_z;
    }

    multipolygon_m_t<T>* get_multipolygon_m()
    {
        assert(is_multipolygon_m());
        return m_value.m_multipolygon_m;
    }

    const multipolygon_m_t<T>* get_multipolygon_m() const
    {
        assert(m_geom_type == geometry_type::MULTIPOLYGONM);
        return m_value.m_multipolygon_m;
    }

    multipolygon_zm_t<T>* get_multipolygon_zm()
    {
        assert(is_multipolygon_zm());
        return m_value.m_multipolygon_zm;
    }

    const multipolygon_zm_t<T>* get_multipolygon_zm() const
    {
        assert(m_geom_type == geometry_type::MULTIPOLYGONZM);
        return m_value.m_multipolygon_zm;
    }

    // geometrycollection

    geometrycollection_t<T>* get_geometrycollection();

    const geometrycollection_t<T>* get_geometrycollection() const;

    geometrycollection_z_t<T>* get_geometrycollection_z();

    const geometrycollection_z_t<T>* get_geometrycollection_z() const;

    geometrycollection_m_t<T>* get_geometrycollection_m();

    const geometrycollection_m_t<T>* get_geometrycollection_m() const;

    geometrycollection_zm_t<T>* get_geometrycollection_zm();

    const geometrycollection_zm_t<T>* get_geometrycollection_zm() const;

  private:
    /// for allow basic_geometry to access basic_point_zm private members
    friend class basic_geometry<geometry_t<T>>;

    void copy_geometrycollection_(const geometry_t<T>& other);
    void copy_geometrycollection_z_(const geometry_t<T>& other);
    void copy_geometrycollection_m_(const geometry_t<T>& other);
    void copy_geometrycollection_zm_(const geometry_t<T>& other);

    static bool is_geometrycollection_wkt_(const std::string& wkt);
    static geometry_type geometrycollection_type_from_wkt_(const std::string& wkt);
    static geometry_t<T> from_geometrycollection_wkt_(const std::string& wkt);
    std::string geometrycollection_json_(std::int32_t precision) const;
    std::string geometrycollection_wkt_(std::int32_t precision) const;

    union geom_value
    {
        point_t<T>* m_point;
        point_z_t<T>* m_point_z;
        point_m_t<T>* m_point_m;
        point_zm_t<T>* m_point_zm;
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

        // default constructor
        geom_value() = default;

        // point

        explicit geom_value(const point_t<T>& p)
            : m_point(new point_t<T>(p))
        {
        }

        explicit geom_value(const point_z_t<T>& p)
            : m_point_z(new point_z_t<T>(p))
        {
        }

        explicit geom_value(const point_m_t<T>& p)
            : m_point_m(new point_m_t<T>(p))
        {
        }

        explicit geom_value(const point_zm_t<T>& p)
            : m_point_zm(new point_zm_t<T>(p))
        {
        }

        // multipoint

        explicit geom_value(const multipoint_t<T>& p)
            : m_multipoint(new multipoint_t<T>(p))
        {
        }

        explicit geom_value(const multipoint_z_t<T>& p)
            : m_multipoint_z(new multipoint_z_t<T>(p))
        {
        }

        explicit geom_value(const multipoint_m_t<T>& p)
            : m_multipoint_m(new multipoint_m_t<T>(p))
        {
        }

        explicit geom_value(const multipoint_zm_t<T>& p)
            : m_multipoint_zm(new multipoint_zm_t<T>(p))
        {
        }

        // linestring

        explicit geom_value(const linestring_t<T>& p)
            : m_linestring(new linestring_t<T>(p))
        {
        }

        explicit geom_value(const linestring_z_t<T>& p)
            : m_linestring_z(new linestring_z_t<T>(p))
        {
        }

        explicit geom_value(const linestring_m_t<T>& p)
            : m_linestring_m(new linestring_m_t<T>(p))
        {
        }

        explicit geom_value(const linestring_zm_t<T>& p)
            : m_linestring_zm(new linestring_zm_t<T>(p))
        {
        }

        // multilinestring

        explicit geom_value(const multilinestring_t<T>& p)
            : m_multilinestring(new multilinestring_t<T>(p))
        {
        }

        explicit geom_value(const multilinestring_z_t<T>& p)
            : m_multilinestring_z(new multilinestring_z_t<T>(p))
        {
        }

        explicit geom_value(const multilinestring_m_t<T>& p)
            : m_multilinestring_m(new multilinestring_m_t<T>(p))
        {
        }

        explicit geom_value(const multilinestring_zm_t<T>& p)
            : m_multilinestring_zm(new multilinestring_zm_t<T>(p))
        {
        }

        // polygon

        explicit geom_value(const polygon_t<T>& p)
            : m_polygon(new polygon_t<T>(p))
        {
        }

        explicit geom_value(const polygon_z_t<T>& p)
            : m_polygon_z(new polygon_z_t<T>(p))
        {
        }

        explicit geom_value(const polygon_m_t<T>& p)
            : m_polygon_m(new polygon_m_t<T>(p))
        {
        }

        explicit geom_value(const polygon_zm_t<T>& p)
            : m_polygon_zm(new polygon_zm_t<T>(p))
        {
        }

        // multipolygon

        explicit geom_value(const multipolygon_t<T>& p)
            : m_multipolygon(new multipolygon_t<T>(p))
        {
        }

        explicit geom_value(const multipolygon_z_t<T>& p)
            : m_multipolygon_z(new multipolygon_z_t<T>(p))
        {
        }

        explicit geom_value(const multipolygon_m_t<T>& p)
            : m_multipolygon_m(new multipolygon_m_t<T>(p))
        {
        }

        explicit geom_value(const multipolygon_zm_t<T>& p)
            : m_multipolygon_zm(new multipolygon_zm_t<T>(p))
        {
        }
    };

    geom_value m_value        = {};
    geometry_type m_geom_type = geometry_type::GEOMETRY;
    std::shared_ptr<geometrycollection_t<T>> m_geometrycollection;
    std::shared_ptr<geometrycollection_z_t<T>> m_geometrycollection_z;
    std::shared_ptr<geometrycollection_m_t<T>> m_geometrycollection_m;
    std::shared_ptr<geometrycollection_zm_t<T>> m_geometrycollection_zm;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return m_geom_type;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Geometry";
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        return dimension_type::XY;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        return 2;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        return {};
    }

    /// @private
    bool has_z_() const noexcept
    {
        return true;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return true;
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
        switch (m_geom_type)
        {
            // point
            case geometry_type::POINT:
            {
                return m_value.m_point->json(precision);
            }
            case geometry_type::POINTZ:
            {
                return m_value.m_point_z->json(precision);
            }
            case geometry_type::POINTM:
            {
                return m_value.m_point_m->json(precision);
            }
            case geometry_type::POINTZM:
            {
                return m_value.m_point_zm->json(precision);
            }

            // multipoint
            case geometry_type::MULTIPOINT:
            {
                return m_value.m_multipoint->json(precision);
            }
            case geometry_type::MULTIPOINTZ:
            {
                return m_value.m_multipoint_z->json(precision);
            }
            case geometry_type::MULTIPOINTM:
            {
                return m_value.m_multipoint_m->json(precision);
            }
            case geometry_type::MULTIPOINTZM:
            {
                return m_value.m_multipoint_zm->json(precision);
            }

            // linestring
            case geometry_type::LINESTRING:
            {
                return m_value.m_linestring->json(precision);
            }
            case geometry_type::LINESTRINGZ:
            {
                return m_value.m_linestring_z->json(precision);
            }
            case geometry_type::LINESTRINGM:
            {
                return m_value.m_linestring_m->json(precision);
            }
            case geometry_type::LINESTRINGZM:
            {
                return m_value.m_linestring_zm->json(precision);
            }

            // multilinestring
            case geometry_type::MULTILINESTRING:
            {
                return m_value.m_multilinestring->json(precision);
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                return m_value.m_multilinestring_z->json(precision);
            }
            case geometry_type::MULTILINESTRINGM:
            {
                return m_value.m_multilinestring_m->json(precision);
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                return m_value.m_multilinestring_zm->json(precision);
            }

            // polygon
            case geometry_type::POLYGON:
            {
                return m_value.m_polygon->json(precision);
            }
            case geometry_type::POLYGONZ:
            {
                return m_value.m_polygon_z->json(precision);
            }
            case geometry_type::POLYGONM:
            {
                return m_value.m_polygon_m->json(precision);
            }
            case geometry_type::POLYGONZM:
            {
                return m_value.m_polygon_zm->json(precision);
            }

            // multipolygon
            case geometry_type::MULTIPOLYGON:
            {
                return m_value.m_multipolygon->json(precision);
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                return m_value.m_multipolygon_z->json(precision);
            }
            case geometry_type::MULTIPOLYGONM:
            {
                return m_value.m_multipolygon_m->json(precision);
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                return m_value.m_multipolygon_zm->json(precision);
            }
            case geometry_type::GEOMETRYCOLLECTION:
            case geometry_type::GEOMETRYCOLLECTIONZ:
            case geometry_type::GEOMETRYCOLLECTIONM:
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                return geometrycollection_json_(precision);
            }
            default:
            {
                return "";
            }
        }
    }

    // wkt

    /// @private
    static geometry_t<T> from_wkt_(const std::string& wkt)
    {
        if (is_geometrycollection_wkt_(wkt))
        {
            return from_geometrycollection_wkt_(wkt);
        }

        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        switch (data.geom_type)
        {
            case geometry_type::POINT:
                return geometry_t<T>(point_t<T>::from_wkt(wkt));
            case geometry_type::POINTZ:
                return geometry_t<T>(point_z_t<T>::from_wkt(wkt));
            case geometry_type::POINTM:
                return geometry_t<T>(point_m_t<T>::from_wkt(wkt));
            case geometry_type::POINTZM:
                return geometry_t<T>(point_zm_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINT:
                return geometry_t<T>(multipoint_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINTZ:
                return geometry_t<T>(multipoint_z_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINTM:
                return geometry_t<T>(multipoint_m_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINTZM:
                return geometry_t<T>(multipoint_zm_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRING:
                return geometry_t<T>(linestring_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRINGZ:
                return geometry_t<T>(linestring_z_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRINGM:
                return geometry_t<T>(linestring_m_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRINGZM:
                return geometry_t<T>(linestring_zm_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRING:
                return geometry_t<T>(multilinestring_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRINGZ:
                return geometry_t<T>(multilinestring_z_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRINGM:
                return geometry_t<T>(multilinestring_m_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRINGZM:
                return geometry_t<T>(multilinestring_zm_t<T>::from_wkt(wkt));
            case geometry_type::POLYGON:
                return geometry_t<T>(polygon_t<T>::from_wkt(wkt));
            case geometry_type::POLYGONZ:
                return geometry_t<T>(polygon_z_t<T>::from_wkt(wkt));
            case geometry_type::POLYGONM:
                return geometry_t<T>(polygon_m_t<T>::from_wkt(wkt));
            case geometry_type::POLYGONZM:
                return geometry_t<T>(polygon_zm_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGON:
                return geometry_t<T>(multipolygon_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGONZ:
                return geometry_t<T>(multipolygon_z_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGONM:
                return geometry_t<T>(multipolygon_m_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGONZM:
                return geometry_t<T>(multipolygon_zm_t<T>::from_wkt(wkt));
            default:
            {
                throw exceptions::parse_error("invalid wkt string");
            }
        }
        return {};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        switch (m_geom_type)
        {
            // point
            case geometry_type::POINT:
            {
                return m_value.m_point->wkt(precision);
            }
            case geometry_type::POINTZ:
            {
                return m_value.m_point_z->wkt(precision);
            }
            case geometry_type::POINTM:
            {
                return m_value.m_point_m->wkt(precision);
            }
            case geometry_type::POINTZM:
            {
                return m_value.m_point_zm->wkt(precision);
            }

            // multipoint
            case geometry_type::MULTIPOINT:
            {
                return m_value.m_multipoint->wkt(precision);
            }
            case geometry_type::MULTIPOINTZ:
            {
                return m_value.m_multipoint_z->wkt(precision);
            }
            case geometry_type::MULTIPOINTM:
            {
                return m_value.m_multipoint_m->wkt(precision);
            }
            case geometry_type::MULTIPOINTZM:
            {
                return m_value.m_multipoint_zm->wkt(precision);
            }

            // linestring
            case geometry_type::LINESTRING:
            {
                return m_value.m_linestring->wkt(precision);
            }
            case geometry_type::LINESTRINGZ:
            {
                return m_value.m_linestring_z->wkt(precision);
            }
            case geometry_type::LINESTRINGM:
            {
                return m_value.m_linestring_m->wkt(precision);
            }
            case geometry_type::LINESTRINGZM:
            {
                return m_value.m_linestring_zm->wkt(precision);
            }

            // multilinestring
            case geometry_type::MULTILINESTRING:
            {
                return m_value.m_multilinestring->wkt(precision);
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                return m_value.m_multilinestring_z->wkt(precision);
            }
            case geometry_type::MULTILINESTRINGM:
            {
                return m_value.m_multilinestring_m->wkt(precision);
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                return m_value.m_multilinestring_zm->wkt(precision);
            }

            // polygon
            case geometry_type::POLYGON:
            {
                return m_value.m_polygon->wkt(precision);
            }
            case geometry_type::POLYGONZ:
            {
                return m_value.m_polygon_z->wkt(precision);
            }
            case geometry_type::POLYGONM:
            {
                return m_value.m_polygon_m->wkt(precision);
            }
            case geometry_type::POLYGONZM:
            {
                return m_value.m_polygon_zm->wkt(precision);
            }

            // multipolygon
            case geometry_type::MULTIPOLYGON:
            {
                return m_value.m_multipolygon->wkt(precision);
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                return m_value.m_multipolygon_z->wkt(precision);
            }
            case geometry_type::MULTIPOLYGONM:
            {
                return m_value.m_multipolygon_m->wkt(precision);
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                return m_value.m_multipolygon_zm->wkt(precision);
            }
            case geometry_type::GEOMETRYCOLLECTION:
            case geometry_type::GEOMETRYCOLLECTIONZ:
            case geometry_type::GEOMETRYCOLLECTIONM:
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                return geometrycollection_wkt_(precision);
            }
            default:
            {
                return "";
            }
        }
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

    static std::string compact_upper(const std::string& text)
    {
        std::string res;
        res.reserve(text.size());
        for (char c : text)
        {
            if (std::isspace(static_cast<unsigned char>(c)))
            {
                continue;
            }
            res.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
        }
        return res;
    }

    static geometry_type parse_collection_type(const std::string& wkt)
    {
        const auto compact = compact_upper(wkt);
        if (compact.find("GEOMETRYCOLLECTIONZM") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTIONZM;
        }
        if (compact.find("GEOMETRYCOLLECTIONZ") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTIONZ;
        }
        if (compact.find("GEOMETRYCOLLECTIONM") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTIONM;
        }
        if (compact.find("GEOMETRYCOLLECTION") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTION;
        }
        throw exceptions::parse_error("invalid geometry collection wkt string");
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
            const auto compact = compact_upper(text);
            if (compact.find("EMPTY") != std::string::npos)
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
        std::stringstream ss;
        ss << "{\"type\":\"GeometryCollection\",\"geometries\":[";
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << (*this)[i].json(precision);
        }
        ss << "]}";
        return ss.str();
    }

    static basic_geometrycollection<T, GeometryType, AllocatorType> from_wkt_(const std::string& wkt)
    {
        const auto parsed_type = parse_collection_type(wkt);
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
        std::stringstream ss;
        ss << "GEOMETRYCOLLECTION";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        if (this->empty())
        {
            ss << " EMPTY";
            return ss.str();
        }

        ss << "(";
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << (*this)[i].wkt(precision);
        }
        ss << ")";
        return ss.str();
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
geometry_t<T>::geometry_t(const geometrycollection_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTION),
      m_geometrycollection(new geometrycollection_t<T>(value))
{
}

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_z_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONZ),
      m_geometrycollection_z(new geometrycollection_z_t<T>(value))
{
}

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_m_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONM),
      m_geometrycollection_m(new geometrycollection_m_t<T>(value))
{
}

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_zm_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONZM),
      m_geometrycollection_zm(new geometrycollection_zm_t<T>(value))
{
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection)
    {
        m_geometrycollection.reset(new geometrycollection_t<T>(*other.m_geometrycollection));
    }
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_z_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection_z)
    {
        m_geometrycollection_z.reset(new geometrycollection_z_t<T>(*other.m_geometrycollection_z));
    }
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_m_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection_m)
    {
        m_geometrycollection_m.reset(new geometrycollection_m_t<T>(*other.m_geometrycollection_m));
    }
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_zm_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection_zm)
    {
        m_geometrycollection_zm.reset(new geometrycollection_zm_t<T>(*other.m_geometrycollection_zm));
    }
}

template <typename T>
bool geometry_t<T>::is_geometrycollection_wkt_(const std::string& wkt)
{
    std::string compact;
    compact.reserve(wkt.size());
    for (char c : wkt)
    {
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            continue;
        }
        compact.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    return compact.find("GEOMETRYCOLLECTION") == 0;
}

template <typename T>
geometry_type geometry_t<T>::geometrycollection_type_from_wkt_(const std::string& wkt)
{
    std::string compact;
    compact.reserve(wkt.size());
    for (char c : wkt)
    {
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            continue;
        }
        compact.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    if (compact.find("GEOMETRYCOLLECTIONZM") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTIONZM;
    }
    if (compact.find("GEOMETRYCOLLECTIONZ") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTIONZ;
    }
    if (compact.find("GEOMETRYCOLLECTIONM") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTIONM;
    }
    if (compact.find("GEOMETRYCOLLECTION") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTION;
    }
    throw exceptions::parse_error("invalid geometry collection wkt string");
}

template <typename T>
geometry_t<T> geometry_t<T>::from_geometrycollection_wkt_(const std::string& wkt)
{
    switch (geometrycollection_type_from_wkt_(wkt))
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

template <typename T>
std::string geometry_t<T>::geometrycollection_json_(std::int32_t precision) const
{
    switch (m_geom_type)
    {
        case geometry_type::GEOMETRYCOLLECTION:
            return m_geometrycollection->json(precision);
        case geometry_type::GEOMETRYCOLLECTIONZ:
            return m_geometrycollection_z->json(precision);
        case geometry_type::GEOMETRYCOLLECTIONM:
            return m_geometrycollection_m->json(precision);
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return m_geometrycollection_zm->json(precision);
        default:
            return "";
    }
}

template <typename T>
std::string geometry_t<T>::geometrycollection_wkt_(std::int32_t precision) const
{
    switch (m_geom_type)
    {
        case geometry_type::GEOMETRYCOLLECTION:
            return m_geometrycollection->wkt(precision);
        case geometry_type::GEOMETRYCOLLECTIONZ:
            return m_geometrycollection_z->wkt(precision);
        case geometry_type::GEOMETRYCOLLECTIONM:
            return m_geometrycollection_m->wkt(precision);
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return m_geometrycollection_zm->wkt(precision);
        default:
            return "";
    }
}

template <typename T>
geometrycollection_t<T>* geometry_t<T>::get_geometrycollection()
{
    assert(is_geometrycollection());
    return m_geometrycollection.get();
}

template <typename T>
const geometrycollection_t<T>* geometry_t<T>::get_geometrycollection() const
{
    assert(m_geom_type == geometry_type::GEOMETRYCOLLECTION);
    return m_geometrycollection.get();
}

template <typename T>
geometrycollection_z_t<T>* geometry_t<T>::get_geometrycollection_z()
{
    assert(is_geometrycollection_z());
    return m_geometrycollection_z.get();
}

template <typename T>
const geometrycollection_z_t<T>* geometry_t<T>::get_geometrycollection_z() const
{
    assert(m_geom_type == geometry_type::GEOMETRYCOLLECTIONZ);
    return m_geometrycollection_z.get();
}

template <typename T>
geometrycollection_m_t<T>* geometry_t<T>::get_geometrycollection_m()
{
    assert(is_geometrycollection_m());
    return m_geometrycollection_m.get();
}

template <typename T>
const geometrycollection_m_t<T>* geometry_t<T>::get_geometrycollection_m() const
{
    assert(m_geom_type == geometry_type::GEOMETRYCOLLECTIONM);
    return m_geometrycollection_m.get();
}

template <typename T>
geometrycollection_zm_t<T>* geometry_t<T>::get_geometrycollection_zm()
{
    assert(is_geometrycollection_zm());
    return m_geometrycollection_zm.get();
}

template <typename T>
const geometrycollection_zm_t<T>* geometry_t<T>::get_geometrycollection_zm() const
{
    assert(m_geom_type == geometry_type::GEOMETRYCOLLECTIONZM);
    return m_geometrycollection_zm.get();
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
