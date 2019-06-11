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
    geometry_t() {
        std::cout << "DEFAULT CONSTRUCTOR" << std::endl;
    }

    // copy constructor:
    geometry_t(const geometry_t& other)
    {
        std::cout << "COPY CONSTRUCTOR" << std::endl;
        m_geom_type = other.point()->geom_type();
        switch (other.geom_type())
        {
            case geometry_type::POINT:
            {
                m_value = geom_value(*other.point());
                break;
            }
            case geometry_type::POINTZ:
            {
                m_value = geom_value(*other.point_z());
                break;
            }
            case geometry_type::POINTM:
            {
                m_value = geom_value(*other.point_m());
                break;
            }
            case geometry_type::POINTZM:
            {
                m_value = geom_value(*other.point_zm());
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

    friend void swap(geometry_t& lhs, geometry_t& rhs) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        swap(lhs.m_value, rhs.m_value);
        swap(lhs.m_geom_type, rhs.m_geom_type);
    }

    explicit geometry_t(const point_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINT)
    {

    }

    explicit geometry_t(const point_z_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINTZ)
    {

    }

    explicit geometry_t(const point_m_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINTM)
    {
    }

    explicit geometry_t(const point_zm_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINTZM)
    {
    }

    ~geometry_t()
    {
        switch (m_geom_type)
        {
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
        if (is_basic_point<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(point());
        }
        if (is_basic_point_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(point_z());
        }
        if (is_basic_point_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(point_m());
        }
        if (is_basic_point_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(point_zm());
        }
        return nullptr;
    }

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

    point_t<T>* point()
    {
        assert(is_point());
        return m_value.m_point;
    }

    point_z_t<T>* point_z()
    {
        assert(is_point_z());
        return m_value.m_point_z;
    }

    point_m_t<T>* point_m()
    {
        assert(is_point_m());
        return m_value.m_point_m;
    }

    point_zm_t<T>* point_zm()
    {
        assert(is_point_zm());
        return m_value.m_point_zm;
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
    };

    geom_value m_value = {};
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
    static geometry_t<T> from_json_(const std::string& json)
    {
        return {};
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        switch (m_geom_type)
        {
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
        return {};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        switch (m_geom_type)
        {
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
            default:
            {
                return "";
            }
        }
    }
};

using Geometry = geometry_t<double>;

}  // namespace shapes
}  // namespace simo