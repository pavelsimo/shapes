/*
         __
   _____/ /_  ____ _____  ___  _____
  / ___/ __ \/ __ `/ __ \/ _ \/ ___/
 (__  ) / / / /_/ / /_/ /  __(__  )
/____/_/ /_/\__,_/ .___/\___/____/
                /_/

MIT License

Copyright (c) 2019 Pavel Simo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef SIMO_SHAPES_HPP
#define SIMO_SHAPES_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace simo
{
namespace shapes
{

// #include <simo/shapes_fwd.hpp>


#include <type_traits>

class point_t;

class multipoint_t;

class linestring_t;

class multilinestring_t;

class polygon_t;

class multipolygon_t;

class geometrycollection_t;

//class Envelope;

// #include <simo/geom/geometry.hpp>


#include <vector>
#include <memory>
// #include <simo/shapes_fwd.hpp>


enum class GeometryType
{
    GEOMETRY        = 0,
    POINT           = 1,
    CURVE           = 2,
    LINESTRING      = 3,
    SURFACE         = 4,
    POLYGON         = 5,
    COLLECTION      = 6,
    MULTIPOINT      = 7,
    MULTICURVE      = 8,
    MULTILINESTRING = 9,
    MULTISURFACE    = 10,
    MULTIPOLYGON    = 11
};

template <typename Base>
class Geometry : public Base
{
  public:
    Geometry()
        : Base()
    {}

    template <typename T>
    Geometry(std::initializer_list<T> params)
        : Base(params)
    {}

    template <typename T>
    Geometry(std::initializer_list<std::initializer_list<T>> params)
        : Base(params)
    {}

    template <typename T>
    Geometry(std::vector<T> rhs)
        : Base(std::move(rhs))
    {}

    template <typename T>
    Geometry(std::vector<std::vector<T>> rhs)
        : Base(std::move(rhs))
    {}

    GeometryType geom_type()
    {
        return Base::geom_type();
    }

    std::string geom_type_str()
    {
        return Base::geom_type_str();
    }

    virtual int8_t dimension()
    {
        return Base::dimension();
    }

    //    std::unique_ptr<Envelope> envelope()
    //    {
    //        return this->envelope_();
    //    }

    //===========================
    // Geometry Creation
    //===========================

    //    virtual std::string to_geojson() const { return ""; }
    //
    //    static std::unique_ptr<Geometry> from_geojson(const std::string& json) { return nullptr; }
    //
    //    virtual std::string to_wkt() const { return ""; }
    //
    //    static std::unique_ptr<Geometry> from_wkt(const std::string& json) { return nullptr; }
    //
    //    virtual std::string to_wkb() const { return ""; }
    //
    //    static std::unique_ptr<Geometry> from_wkb(const std::string& json) { return nullptr; }

    //===========================
    // Geometry Characteristics
    //===========================

    //    virtual bool is_empty() const = 0;
    //
    //    virtual bool is_simple() const = 0;
    //
    //    virtual bool is_closed() const = 0;

    //===========================
    // Relational Operators
    //===========================
    //
    //    /// Tests if this geometry is ?spatially equal? to another geometry.
    //    virtual bool equals(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry ?spatially touches? another geometry.
    //    virtual bool touches(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry ?spatially contains? another geometry.
    //    virtual bool contains(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry is ?spatially within? another geometry.
    //    virtual bool within(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry is ?spatially disjoint? from another geometry.
    //    virtual bool disjoint(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry ?spatially crosses? another geometry.
    //    virtual bool crosses(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry ?spatially overlaps? another geometry.
    //    virtual bool overlaps(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry ?spatially intersects? another geometry.
    //    virtual bool intersects(const Geometry& geom) const = 0;
    //
    //    /// Tests if this geometry is spatially related to anotherGeometry,
    //    virtual bool relate(const Geometry& geom, const std::string& overlap_matrix) const = 0;

    //===========================
    // Spatial Analysis
    //===========================
    //
    //    /// Returns the shortest distance between any two points in the two
    //    /// geometries.
    //    /// Calculations are in the Spatial Reference System of this geometry.
    //    virtual double distance(const Geometry& geom) const = 0;
    //
    //    /// Returns a geometry that represents all points whose distance from this
    //    /// geometry is less than or equal to distance.
    //    /// Calculations are in the Spatial Reference System of this geometry.
    //    virtual std::unique_ptr<Geometry> buffer(double distance) const = 0;
    //
    //    /// Returns a geometry that represents the convex hull of this geometry.
    //    virtual std::unique_ptr<Geometry> convex_hull() const = 0;
    //
    //    /// Returns a geometry that represents the point set intersection of the
    //    /// source geometry with anotherGeometry.
    //    virtual std::unique_ptr<Geometry> set_intersection(const Geometry& other) const = 0;
    //
    //    /// Returns a geometry that represents the point set union of the source
    //    /// geometry with anotherGeometry.
    //    virtual std::unique_ptr<Geometry> set_union(const Geometry& other) const = 0;
    //
    //    /// Geometry Difference(Geometry anotherGeometry)?Returns a geometry that
    //    /// represents the point set difference of the source geometry with
    //    /// anotherGeometry.
    //    virtual std::unique_ptr<Geometry> set_difference(const Geometry& other) const = 0;
    //
    //    /// Geometry SymmetricDifference(Geometry anotherGeometry)?Returns a geometry
    //    /// that represents the point set symmetric difference of the source geometry
    //    /// with anotherGeometry.
    //    virtual std::unique_ptr<Geometry> set_symmetric_difference(const Geometry& other) const = 0;
};

// #include <simo/geom/point.hpp>


#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <type_traits>
// #include <simo/geom/geometry.hpp>


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

// #include <simo/geom/envelope.hpp>


#include <algorithm>
// #include <simo/geom/point.hpp>

//
//class Envelope
//{
//  public:
//    Envelope(double minx, double maxx, double miny, double maxy)
//        : m_min(Point(minx, miny)), m_max(Point(maxx, maxy))
//    {
//    }
//
//    Envelope& extend(double x, double y)
//    {
//        m_min.x = std::min(x, m_min.x);
//        m_max.x = std::max(x, m_max.x);
//        m_min.y = std::min(y, m_min.y);
//        m_max.y = std::max(y, m_max.y);
//        return *this;
//    }
//
//    Point center() const { return {(m_min.x + m_max.x) / 2, (m_min.y + m_max.y) / 2}; }
//
//    Point bottom_left() const { return {m_min.x, m_max.y}; }
//
//    Point top_right() const { return {m_max.x, m_min.y}; }
//
//    Point top_left() const { return m_min; }
//
//    Point bottom_right() const { return m_max; }
//
//    Point min() const { return m_min; }
//
//    Point max() const { return m_max; }
//
//    bool contains(const Point& other) const
//    {
//        return (other.x >= m_min.x) && (other.x <= m_max.x) && (other.y >= m_min.y) && (other.y <= m_max.y);
//    }
//
//    bool contains(const Envelope& other) { return contains(other.min()) && contains(other.max()); }
//
//    bool intersects(const Envelope& other)
//    {
//        auto min  = m_min;
//        auto max  = m_max;
//        auto min2 = other.min();
//        auto max2 = other.max();
//        return (max2.x >= min.x) && (min2.x <= max.x) && (max2.y >= min.y) && (min2.y <= max.y);
//    }
//
//    bool overlaps(const Envelope& other)
//    {
//        auto min  = m_min;
//        auto max  = m_max;
//        auto min2 = other.min();
//        auto max2 = other.max();
//        return (max2.x > min.x) && (min2.x < max.x) && (max2.y > min.y) && (min2.y < max.y);
//    }
//
//  private:
//    Point m_min;
//    Point m_max;
//};

// #include <simo/geom/multipoint.hpp>


#include <vector>
// #include <simo/geom/geometry.hpp>

// #include <simo/geom/point.hpp>


class multipoint_t
{
  public:
    multipoint_t() = default;

    template <
        typename T,  //real type
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    multipoint_t(std::initializer_list<std::initializer_list<T>> list)
    {
        for (const auto& coords : list)
        {
            m_points.emplace_back(coords);
        }
    }

    typedef std::vector<Point>::iterator iterator;
    typedef std::vector<Point>::const_iterator const_iterator;

    iterator begin()
    {
        return m_points.begin();
    }

    const_iterator begin() const
    {
        return m_points.begin();
    }

    iterator end()
    {
        return m_points.end();
    }

    const_iterator end() const
    {
        return m_points.end();
    }

    GeometryType geom_type() const
    {
        return GeometryType::MULTIPOINT;
    }

    std::string geom_type_str() const
    {
        return "MULTIPOINT";
    }

    int8_t dimension() const
    {
        return 0;
    }

    Point at(size_t pos)
    {
        return m_points.at(pos);
    }

    Point operator[] (size_t pos)
    {
        return m_points[pos];
    }
    //
    //    std::unique_ptr<Envelope> envelope() override { return nullptr; }
    //
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
    //    std::unique_ptr<Geometry>
    //    set_intersection(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }
    //
    //    std::unique_ptr<Geometry>
    //    set_union(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }
    //
    //    std::unique_ptr<Geometry>
    //    set_difference(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }
    //
    //    std::unique_ptr<Geometry>
    //    set_symmetric_difference(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

  private:
    std::vector<Point> m_points;
};

typedef Geometry<multipoint_t> MultiPoint;

}  // namespace shapes
}  // namespace simo

#endif  // SIMO_SHAPES_HPP
