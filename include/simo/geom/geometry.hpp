#pragma once

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

    virtual GeometryType geom_type() const = 0;

    virtual std::string geom_type_str() const = 0;

    virtual int8_t dimension() const = 0;

    virtual std::unique_ptr<Envelope> envelope() = 0;

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

    /// Tests if this geometry is ?spatially equal? to another geometry.
    virtual bool equals(const Geometry& geom) const = 0;

    /// Tests if this geometry ?spatially touches? another geometry.
    virtual bool touches(const Geometry& geom) const = 0;

    /// Tests if this geometry ?spatially contains? another geometry.
    virtual bool contains(const Geometry& geom) const = 0;

    /// Tests if this geometry is ?spatially within? another geometry.
    virtual bool within(const Geometry& geom) const = 0;

    /// Tests if this geometry is ?spatially disjoint? from another geometry.
    virtual bool disjoint(const Geometry& geom) const = 0;

    /// Tests if this geometry ?spatially crosses? another geometry.
    virtual bool crosses(const Geometry& geom) const = 0;

    /// Tests if this geometry ?spatially overlaps? another geometry.
    virtual bool overlaps(const Geometry& geom) const = 0;

    /// Tests if this geometry ?spatially intersects? another geometry.
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

    /// Geometry Difference(Geometry anotherGeometry)?Returns a geometry that
    /// represents the point set difference of the source geometry with
    /// anotherGeometry.
    virtual std::unique_ptr<Geometry> set_difference(const Geometry& other) const = 0;

    /// Geometry SymmetricDifference(Geometry anotherGeometry)?Returns a geometry
    /// that represents the point set symmetric difference of the source geometry
    /// with anotherGeometry.
    virtual std::unique_ptr<Geometry> set_symmetric_difference(const Geometry& other) const = 0;
};
