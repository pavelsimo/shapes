/*
         __
   _____/ /_  ____ _____  ___  _____
  / ___/ __ \/ __ `/ __ \/ _ \/ ___/
 (__  ) / / / /_/ / /_/ /  __(__  )
/____/_/ /_/\__,_/ .___/\___/____/
                /_/

MIT License

Copyright (c) 2019 Pavel Simó

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
#ifndef SIMO_SHAPES_H
#define SIMO_SHAPES_H

#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#ifndef _MSC_VER
#    define NOEXCEPT NOEXCEPT
#else
#    define NOEXCEPT
#endif

namespace simo
{
namespace shapes
{

class Point;
class MultiPoint;
class LineString;
class MultiLineString;
class Polygon;
class MultiPolygon;
class GeometryCollection;

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

enum class DimensionType
{
    XY   = 2,
    XYZ  = 3,
    XYZM = 4
};

class Geometry
{
  public:
    Geometry() = default;

    virtual ~Geometry() = default;

    virtual GeometryType geom_type() const NOEXCEPT = 0;

    virtual std::string geom_type_str() const NOEXCEPT = 0;

    virtual int8_t dimension() const = 0;

    //===========================
    // Geometry Creation
    //===========================

    virtual std::string to_geojson() const { return ""; }

    static std::unique_ptr<Geometry> from_geojson(const std::string& json) { return nullptr; }

    virtual std::string to_wkt() const { return ""; }

    static std::unique_ptr<Geometry> from_wkt(const std::string& json) { return nullptr; }

    virtual std::string to_wkb() const { return ""; }

    static std::unique_ptr<Geometry> from_wkb(const std::string& json) { return nullptr; }

    //===========================
    // Geometry Characteristics
    //===========================

    virtual bool is_empty() const = 0;

    virtual bool is_simple() const = 0;

    virtual bool is_closed() const = 0;

    //===========================
    // Relational Operators
    //===========================

    /// Tests if this geometry is ‘spatially equal’ to another geometry.
    virtual bool equals(const Geometry& geom) const = 0;

    /// Tests if this geometry ‘spatially touches’ another geometry.
    virtual bool touches(const Geometry& geom) const = 0;

    /// Tests if this geometry ‘spatially contains’ another geometry.
    virtual bool contains(const Geometry& geom) const = 0;

    /// Tests if this geometry is ‘spatially within’ another geometry.
    virtual bool within(const Geometry& geom) const = 0;

    /// Tests if this geometry is ‘spatially disjoint’ from another geometry.
    virtual bool disjoint(const Geometry& geom) const = 0;

    /// Tests if this geometry ‘spatially crosses’ another geometry.
    virtual bool crosses(const Geometry& geom) const = 0;

    /// Tests if this geometry ‘spatially overlaps’ another geometry.
    virtual bool overlaps(const Geometry& geom) const = 0;

    /// Tests if this geometry ‘spatially intersects’ another geometry.
    virtual bool intersects(const Geometry& geom) const = 0;

    /// Tests if this geometry is spatially related to anotherGeometry,
    virtual bool relate(const Geometry& geom, const std::string& overlap_matrix) const = 0;

    //===========================
    // Spatial Analysis
    //===========================

    /// Returns the shortest distance between any two points in the two
    /// geometries.
    /// Calculations are in the Spatial Reference System of this geometry.
    virtual double distance(const Geometry& geom) const = 0;

    /// Returns a geometry that represents all points whose distance from this
    /// geometry is less than or equal to distance.
    /// Calculations are in the Spatial Reference System of this geometry.
    virtual std::unique_ptr<Geometry> buffer(double distance) const = 0;

    /// Returns a geometry that represents the convex hull of this geometry.
    virtual std::unique_ptr<Geometry> convex_hull() const = 0;

    /// Returns a geometry that represents the point set intersection of the
    /// source geometry with anotherGeometry.
    virtual std::unique_ptr<Geometry> set_intersection(const Geometry& other) const = 0;

    /// Returns a geometry that represents the point set union of the source
    /// geometry with anotherGeometry.
    virtual std::unique_ptr<Geometry> set_union(const Geometry& other) const = 0;

    /// Geometry Difference(Geometry anotherGeometry)—Returns a geometry that
    /// represents the point set difference of the source geometry with
    /// anotherGeometry.
    virtual std::unique_ptr<Geometry> set_difference(const Geometry& other) const = 0;

    /// Geometry SymmetricDifference(Geometry anotherGeometry)—Returns a geometry
    /// that represents the point set symmetric difference of the source geometry
    /// with anotherGeometry.
    virtual std::unique_ptr<Geometry> set_symmetric_difference(const Geometry& other) const = 0;
};

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

    std::unique_ptr<Geometry> set_union(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

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

    GeometryType geom_type() const NOEXCEPT override { return GeometryType::MULTIPOINT; }

    std::string geom_type_str() const NOEXCEPT override { return "MultiPoint"; }

    int8_t dimension() const override { return 0; }

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

    std::unique_ptr<Geometry> set_intersection(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry> set_union(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry> set_difference(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

    std::unique_ptr<Geometry> set_symmetric_difference(const Geometry& other) const override { return std::unique_ptr<Geometry>(); }

  private:
    std::vector<Point> m_points;
};

//
//    class LineString : virtual public Geometry {
//    public:
//        GeometryType geom_type() const NOEXCEPT override {
//            return GeometryType::LINESTRING;
//        }
//
//        std::string geom_type_str() const NOEXCEPT override {
//            return "LineString";
//        }
//    };
//
//    class MultiLineString : virtual public Geometry {
//    public:
//        GeometryType geom_type() const NOEXCEPT override {
//            return GeometryType::MULTILINESTRING;
//        }
//
//        std::string geom_type_str() const NOEXCEPT override {
//            return "MultiLineString";
//        }
//    };
//
//    class Polygon : virtual public Geometry {
//    public:
//        GeometryType geom_type() const NOEXCEPT override {
//            return GeometryType::POLYGON;
//        }
//
//        std::string geom_type_str() const NOEXCEPT override {
//            return "Polygon";
//        }
//    };
//
//    class MultiPolygon : virtual public Geometry {
//    public:
//        GeometryType geom_type() const NOEXCEPT override {
//            return GeometryType::MULTIPOLYGON;
//        }
//
//        std::string geom_type_str() const NOEXCEPT override {
//            return "MultiPolygon";
//        }
//    };

}  // namespace shapes
}  // namespace simo

#endif  // SIMO_SHAPES_H
