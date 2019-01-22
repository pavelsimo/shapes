#pragma once

#include <simo/geom/geometry.hpp>

class MultiPoint : virtual public Geometry
{
  public:
    MultiPoint(std::initializer_list<Point> points)
        : m_points(points) {}

    MultiPoint(std::initializer_list<std::initializer_list<double>> list)
    {
        for (const auto& coordinates : list)
        {
            m_points.emplace_back(Point(coordinates));
        }
    }

    explicit MultiPoint(std::vector<Point> points)
        : m_points(std::move(points)) {}

    typedef std::vector<Point>::iterator iterator;
    typedef std::vector<Point>::const_iterator const_iterator;

    iterator begin() { return m_points.begin(); }

    const_iterator begin() const { return m_points.begin(); }

    iterator end() { return m_points.end(); }

    const_iterator end() const { return m_points.end(); }

    GeometryType geom_type() const override { return GeometryType::MULTIPOINT; }

    std::string geom_type_str() const override { return "MultiPoint"; }

    int8_t dimension() const override { return 0; }

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

    std::unique_ptr<Geometry>
    set_intersection(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry>
    set_union(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry>
    set_difference(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry>
    set_symmetric_difference(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

  private:
    std::vector<Point> m_points;
};
