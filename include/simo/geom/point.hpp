#pragma once

#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <type_traits>
#include <simo/geom/geometry.hpp>

class point_t
{
  public:
    double x, y, z;

    point_t()
    {
        this->x           = 0;
        this->y           = 0;
        this->z           = 0;
        this->m_dimension = 2;
    }

    template <
        typename T,  //real type
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    point_t(std::initializer_list<T> list)
    {
        if (list.size() == 2)
        {
            this->x           = *list.begin();
            this->y           = *(list.begin() + 1);
            this->z           = 0;
            this->m_dimension = 2;
        }
        else if (list.size() == 3)
        {
            this->x           = *list.begin();
            this->y           = *(list.begin() + 1);
            this->z           = *(list.begin() + 2);
            this->m_dimension = 3;
        }
    }

    GeometryType geom_type() const
    {
        return GeometryType::POINT;
    }

    std::string geom_type_str() const
    {
        return "POINT";
    }

    int8_t dimension() const
    {
        return m_dimension;
    }
    //
    //    std::unique_ptr<Envelope> envelope_()
    //    {
    //        return nullptr;
    //    }

    //    bool is_empty() const override { return false; }
    //
    //    bool is_simple() const override { return false; }
    //
    //    bool is_closed() const override { return false; }
    //
    //    bool equals(const Geometry& geom) const override { return false; }
    //
    //    bool touches(const Geometry& geom) const override { return false; }
    //
    //    bool contains(const Geometry& geom) const override { return false; }
    //
    //    bool within(const Geometry& geom) const override { return false; }
    //
    //    bool disjoint(const Geometry& geom) const override { return false; }
    //
    //    bool crosses(const Geometry& geom) const override { return false; }
    //
    //    bool overlaps(const Geometry& geom) const override { return false; }
    //
    //    bool intersects(const Geometry& geom) const override { return false; }
    //
    //    bool relate(const Geometry& geom, const std::string& overlap_matrix) const override { return false; }
    //
    //    double distance(const Geometry& geom) const override { return 0; }
    //
    //    std::unique_ptr<Geometry> buffer(double distance) const override { return std::unique_ptr<Geometry>(); }
    //
    //    std::unique_ptr<Geometry> convex_hull() const override { return std::unique_ptr<Geometry>(); }
    //
    //    std::unique_ptr<Geometry> set_intersection(const Geometry& other) const override
    //    {
    //        return std::unique_ptr<Geometry>();
    //    }
    //
    //    std::unique_ptr<Geometry>
    //    set_union(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }
    //
    //    std::unique_ptr<Geometry> set_difference(const Geometry& other) const override
    //    {
    //        return std::unique_ptr<Geometry>();
    //    }
    //
    //    std::unique_ptr<Geometry> set_symmetric_difference(const Geometry& other) const override
    //    {
    //        return std::unique_ptr<Geometry>();
    //    }

  private:
    int8_t m_dimension;
};

typedef Geometry<point_t> Point;
