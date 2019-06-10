#pragma once

#include <ciso646>
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
class geometry
{
  public:
    geometry()
        : m_geom_type(geometry_type::GEOMETRY)
    {
    }

    geometry(const point_t<T>& p)
        : m_point(new point_t<T>(p)), m_geom_type(geometry_type::POINT)
    {
    }

    geometry(const point_z_t<T>& p)
        : m_point_z(new point_z_t<T>(p)), m_geom_type(geometry_type::POINTZ)
    {
    }

    geometry(const point_m_t<T>& p)
        : m_point_m(new point_m_t<T>(p)), m_geom_type(geometry_type::POINTM)
    {
    }

    geometry(const point_zm_t<T>& p)
        : m_point_zm(new point_zm_t<T>(p)), m_geom_type(geometry_type::POINTZM)
    {
    }

    ~geometry()
    {
        switch (m_geom_type)
        {
            case geometry_type::POINT:
            {
                delete m_point;
                m_point = nullptr;
                std::cout << "DELETE POINT" << std::endl;
                break;
            }
            case geometry_type::POINTZ:
            {
                delete m_point_z;
                m_point_z = nullptr;
                std::cout << "DELETE POINT Z" << std::endl;
                break;
            }
            case geometry_type::POINTM:
            {
                delete m_point_m;
                m_point_m = nullptr;
                std::cout << "DELETE POINT M" << std::endl;
                break;
            }
            case geometry_type::POINTZM:
            {
                delete m_point_zm;
                m_point_zm = nullptr;
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
    ReturnType* get();

    template <>
    point_t<T>* get()
    {
        return get_point();
    }

    template <>
    point_z_t<T>* get()
    {
        return get_point_z();
    }

    template <>
    point_m_t<T>* get()
    {
        return get_point_m();
    }

    template <>
    point_zm_t<T>* get()
    {
        return get_point_zm();
    }

    //

    bool is_point()
    {
        return m_geom_type == geometry_type::POINT;
    }

    bool is_point_z()
    {
        return m_geom_type == geometry_type::POINTZ;
    }

    bool is_point_m()
    {
        return m_geom_type == geometry_type::POINTM;
    }

    bool is_point_zm()
    {
        return m_geom_type == geometry_type::POINTZM;
    }

  private:
    /// @private
    point_t<T>* get_point()
    {
        assert(m_geom_type == geometry_type::POINT);
        return m_point;
    }

    /// @private
    point_z_t<T>* get_point_z()
    {
        assert(m_geom_type == geometry_type::POINTZ);
        return m_point_z;
    }

    /// @private
    point_m_t<T>* get_point_m()
    {
        assert(m_geom_type == geometry_type::POINTM);
        return m_point_m;
    }

    /// @private
    point_zm_t<T>* get_point_zm()
    {
        assert(m_geom_type == geometry_type::POINTZM);
        return m_point_zm;
    }

    geometry_type m_geom_type;

    union
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
        //multipolygon<T>* m_multipolygon;
        //multipolygon_z<T>* m_multipolygon_z;
        //multipolygon_m<T>* m_multipolygon_m;
        //multipolygon_zm<T>* m_multipolygon_zm;
    };
};

using Geometry = geometry<double>;

}  // namespace shapes
}  // namespace simo