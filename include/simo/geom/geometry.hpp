#pragma once

#include <ciso646>
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
        m_geom_type = other.point()->geom_type();
        switch (other.geom_type())
        {
                // point

            case geometry_type::POINT:
            {
                m_value = geom_value(*other.get_point());
                break;
            }
            case geometry_type::POINTZ:
            {
                m_value = geom_value(*other.get_point_z());
                break;
            }
            case geometry_type::POINTM:
            {
                m_value = geom_value(*other.get_point_m());
                break;
            }
            case geometry_type::POINTZM:
            {
                m_value = geom_value(*other.get_point_zm());
                break;
            }

                // multipoint

            case geometry_type::MULTIPOINT:
            {
                m_value = geom_value(*other.get_multipoint());
                break;
            }
            case geometry_type::MULTIPOINTZ:
            {
                m_value = geom_value(*other.get_multipoint_z());
                break;
            }
            case geometry_type::MULTIPOINTM:
            {
                m_value = geom_value(*other.get_multipoint_m());
                break;
            }
            case geometry_type::MULTIPOINTZM:
            {
                m_value = geom_value(*other.get_multipoint_zm());
                break;
            }

                // linestring

            case geometry_type::LINESTRING:
            {
                m_value = geom_value(*other.get_linestring());
                break;
            }
            case geometry_type::LINESTRINGZ:
            {
                m_value = geom_value(*other.get_linestring_z());
                break;
            }
            case geometry_type::LINESTRINGM:
            {
                m_value = geom_value(*other.get_linestring_m());
                break;
            }
            case geometry_type::LINESTRINGZM:
            {
                m_value = geom_value(*other.get_linestring_zm());
                break;
            }

                // multilinestring

            case geometry_type::MULTILINESTRING:
            {
                m_value = geom_value(*other.get_multilinestring());
                break;
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                m_value = geom_value(*other.get_multilinestring_z());
                break;
            }
            case geometry_type::MULTILINESTRINGM:
            {
                m_value = geom_value(*other.get_multilinestring_m());
                break;
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                m_value = geom_value(*other.get_multilinestring_zm());
                break;
            }

                // polygon

            case geometry_type::POLYGON:
            {
                m_value = geom_value(*other.get_polygon());
                break;
            }
            case geometry_type::POLYGONZ:
            {
                m_value = geom_value(*other.get_polygon_z());
                break;
            }
            case geometry_type::POLYGONM:
            {
                m_value = geom_value(*other.get_polygon_m());
                break;
            }
            case geometry_type::POLYGONZM:
            {
                m_value = geom_value(*other.get_polygon_zm());
                break;
            }

                // multipolygon

            case geometry_type::MULTIPOLYGON:
            {
                m_value = geom_value(*other.get_multipolygon());
                break;
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                m_value = geom_value(*other.get_multipolygon_z());
                break;
            }
            case geometry_type::MULTIPOLYGONM:
            {
                m_value = geom_value(*other.get_multipolygon_m());
                break;
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                m_value = geom_value(*other.get_multipolygon_zm());
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

    // point

    point_t<T>* get_point()
    {
        assert(is_point());
        return m_value.m_point;
    }

    point_z_t<T>* get_point_z()
    {
        assert(is_point_z());
        return m_value.m_point_z;
    }

    point_m_t<T>* get_point_m()
    {
        assert(is_point_m());
        return m_value.m_point_m;
    }

    point_zm_t<T>* get_point_zm()
    {
        assert(is_point_zm());
        return m_value.m_point_zm;
    }

    // multipoint

    multipoint_t<T>* get_multipoint()
    {
        assert(is_multipoint());
        return m_value.m_multipoint;
    }

    multipoint_z_t<T>* get_multipoint_z()
    {
        assert(is_multipoint_z());
        return m_value.m_multipoint_z;
    }

    multipoint_m_t<T>* get_multipoint_m()
    {
        assert(is_multipoint_m());
        return m_value.m_multipoint_m;
    }

    multipoint_zm_t<T>* get_multipoint_zm()
    {
        assert(is_multipoint_zm());
        return m_value.m_multipoint_zm;
    }

    // linestring

    linestring_t<T>* get_linestring()
    {
        assert(is_linestring());
        return m_value.m_linestring;
    }

    linestring_z_t<T>* get_linestring_z()
    {
        assert(is_linestring_z());
        return m_value.m_linestring_z;
    }

    linestring_m_t<T>* get_linestring_m()
    {
        assert(is_linestring_m());
        return m_value.m_linestring_m;
    }

    linestring_zm_t<T>* get_linestring_zm()
    {
        assert(is_linestring_zm());
        return m_value.m_linestring_zm;
    }

    // multilinestring

    multilinestring_t<T>* get_multilinestring()
    {
        assert(is_multilinestring());
        return m_value.m_multilinestring;
    }

    multilinestring_z_t<T>* get_multilinestring_z()
    {
        assert(is_multilinestring_z());
        return m_value.m_multilinestring_z;
    }

    multilinestring_m_t<T>* get_multilinestring_m()
    {
        assert(is_multilinestring_m());
        return m_value.m_multilinestring_m;
    }

    multilinestring_zm_t<T>* get_multilinestring_zm()
    {
        assert(is_multilinestring_zm());
        return m_value.m_multilinestring_zm;
    }

    // polygon

    polygon_t<T>* get_polygon()
    {
        assert(is_polygon());
        return m_value.m_polygon;
    }

    polygon_z_t<T>* get_polygon_z()
    {
        assert(is_polygon_z());
        return m_value.m_polygon_z;
    }

    polygon_m_t<T>* get_polygon_m()
    {
        assert(is_polygon_m());
        return m_value.m_polygon_m;
    }

    polygon_zm_t<T>* get_polygon_zm()
    {
        assert(is_polygon_zm());
        return m_value.m_polygon_zm;
    }

    // multipolygon

    multipolygon_t<T>* get_multipolygon()
    {
        assert(is_multipolygon());
        return m_value.m_multipolygon;
    }

    multipolygon_z_t<T>* get_multipolygon_z()
    {
        assert(is_multipolygon_z());
        return m_value.m_multipolygon_z;
    }

    multipolygon_m_t<T>* get_multipolygon_m()
    {
        assert(is_multipolygon_m());
        return m_value.m_multipolygon_m;
    }

    multipolygon_zm_t<T>* get_multipolygon_zm()
    {
        assert(is_multipolygon_zm());
        return m_value.m_multipolygon_zm;
    }

  private:
    /// for allow basic_geometry to access basic_point_zm private members
    friend class basic_geometry<geometry_t<T>>;

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
    static geometry_t<T> from_json_(const std::string& /*json*/)
    {
        geometry_t<T> res;
        return res;
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
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        switch (data.geom_type)
        {
            case geometry_type::POINT:
                return geometry_t<T>(point_t<T>(data.coords[0], data.coords[1]));
            case geometry_type::POINTZ:
                return geometry_t<T>(point_z_t<T>(data.coords[0], data.coords[1], data.coords[2]));
            case geometry_type::POINTM:
                return geometry_t<T>(point_m_t<T>(data.coords[0], data.coords[1], data.coords[2]));
            case geometry_type::POINTZM:
                return geometry_t<T>(point_zm_t<T>(data.coords[0], data.coords[1], data.coords[2], data.coords[3]));
            /// @todo (pavel) add multipoint
            /// @todo (pavel) add linestring
            /// @todo (pavel) add multilinestring
            /// @todo (pavel) add polygon
            /// @todo (pavel) add multipolygon
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
            default:
            {
                return "";
            }
        }
    }
};

using geometry = geometry_t<double>;
using Geometry = geometry_t<double>;

}  // namespace shapes
}  // namespace simo