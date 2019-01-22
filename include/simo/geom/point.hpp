#pragma once

#include <simo/geom/geometry.hpp>

class Point : virtual public Geometry
{
  public:
    double x, y, z;

    Point()
        : x(0), y(0), z(0), m_dimension(2) {}

    Point(double x, double y)
        : x(x), y(y), z(0), m_dimension(2) {}

    Point(double x, double y, double z)
        : x(x), y(y), z(z), m_dimension(3) {}

    Point(std::initializer_list<double> coordinates)
    {
        if (coordinates.size() > 3 || coordinates.size() < 2)
        {
            throw std::invalid_argument("invalid coordinates");
        }

        if (coordinates.size() == 2)
        {
            x           = *coordinates.begin();
            y           = *(coordinates.begin() + 1);
            z           = 0;
            m_dimension = 2;
        }
        else if (coordinates.size() == 3)
        {
            x           = *coordinates.begin();
            y           = *(coordinates.begin() + 1);
            z           = *(coordinates.begin() + 2);
            m_dimension = 3;
        }
    }

    GeometryType geom_type() const override { return GeometryType::POINT; }

    std::string geom_type_str() const override { return "POINT"; }

    int8_t dimension() const override { return m_dimension; }

    std::unique_ptr<Envelope> envelope() override { return nullptr; }

    bool is_empty() const override { return false; }

    bool is_simple() const override { return false; }

    bool is_closed() const override { return false; }

    bool equals(const Geometry& geom) const override { return false; }

    bool touches(const Geometry& geom) const override { return false; }

    bool contains(const Geometry& geom) const override { return false; }

    bool within(const Geometry& geom) const override { return false; }

    bool disjoint(const Geometry& geom) const override { return false; }

    bool crosses(const Geometry& geom) const override { return false; }

    bool overlaps(const Geometry& geom) const override { return false; }

    bool intersects(const Geometry& geom) const override { return false; }

    bool relate(const Geometry& geom, const std::string& overlap_matrix) const override { return false; }

    double distance(const Geometry& geom) const override { return 0; }

    std::unique_ptr<Geometry> buffer(double distance) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry> convex_hull() const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry> set_intersection(const Geometry& other) const override
    {
        return std::unique_ptr<Geometry>();
    }

    std::unique_ptr<Geometry>
    set_union(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry> set_difference(const Geometry& other) const override
    {
        return std::unique_ptr<Geometry>();
    }

    std::unique_ptr<Geometry> set_symmetric_difference(const Geometry& other) const override
    {
        return std::unique_ptr<Geometry>();
    }

  private:
    int8_t m_dimension;
};
