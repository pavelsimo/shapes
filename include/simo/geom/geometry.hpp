#pragma once

#include <vector>
#include <memory>
#include <simo/shapes_fwd.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/// geometry dimension type is (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
enum class DimensionType
{
    XY = 1,
    XYZ = 2,
    XYM = 3,
    XYZM = 4
};

/// geometry types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
enum class GeometryType
{
    GEOMETRY = 0,
    POINT = 1,
    LINESTRING = 2,
    POLYGON = 3,
    MULTIPOINT = 4,
    MULTILINESTRING = 5,
    MULTIPOLYGON = 6,
    GEOMETRYCOLLECTION = 7,
    CIRCULARSTRING = 8,
    COMPOUNDCURVE = 9,
    CURVEPOLYGON = 10,
    MULTICURVE = 11,
    MULTISURFACE = 12,
    CURVE = 13,
    SURFACE = 14,
    POLYHEDRALSURFACE = 15,
    TIN = 16
};

/// geometry detailed types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
enum class GeometryDetailedType
{
    GEOMETRY = 0,
    POINT = 1,
    LINESTRING = 2,
    POLYGON = 3,
    MULTIPOINT = 4,
    MULTILINESTRING = 5,
    MULTIPOLYGON = 6,
    GEOMETRYCOLLECTION = 7,
    CIRCULARSTRING = 8,
    COMPOUNDCURVE = 9,
    CURVEPOLYGON = 10,
    MULTICURVE = 11,
    MULTISURFACE = 12,
    CURVE = 13,
    SURFACE = 14,
    POLYHEDRALSURFACE = 15,
    TIN = 16,
    GEOMETRYZ = 1000,
    POINTZ = 1001,
    LINESTRINGZ = 1002,
    POLYGONZ = 1003,
    MULTIPOINTZ = 1004,
    MULTILINESTRINGZ = 1005,
    MULTIPOLYGONZ = 1006,
    GEOMETRYCOLLECTIONZ = 1007,
    CIRCULARSTRINGZ = 1008,
    COMPOUNDCURVEZ = 1009,
    CURVEPOLYGONZ = 1010,
    MULTICURVEZ = 1011,
    MULTISURFACEZ = 1012,
    CURVEZ = 1013,
    SURFACEZ = 1014,
    POLYHEDRALSURFACEZ = 1015,
    TINZ = 1016,
    GEOMETRYM = 2000,
    POINTM = 2001,
    LINESTRINGM = 2002,
    POLYGONM = 2003,
    MULTIPOINTM = 2004,
    MULTILINESTRINGM = 2005,
    MULTIPOLYGONM = 2006,
    GEOMETRYCOLLECTIONM = 2007,
    CIRCULARSTRINGM = 2008,
    COMPOUNDCURVEM = 2009,
    CURVEPOLYGONM = 2010,
    MULTICURVEM = 2011,
    MULTISURFACEM = 2012,
    CURVEM = 2013,
    SURFACEM = 2014,
    POLYHEDRALSURFACEM = 2015,
    TINM = 2016,
    GEOMETRYZM = 3000,
    POINTZM = 3001,
    LINESTRINGZM = 3002,
    POLYGONZM = 3003,
    MULTIPOINTZM = 3004,
    MULTILINESTRINGZM = 3005,
    MULTIPOLYGONZM = 3006,
    GEOMETRYCOLLECTIONZM = 3007,
    CIRCULARSTRINGZM = 3008,
    COMPOUNDCURVEZM = 3009,
    CURVEPOLYGONZM = 3010,
    MULTICURVEZM  = 3011,
    MULTISURFACEZM = 3012,
    CURVEZM = 3013,
    SURFACEZM = 3014,
    POLYHEDRALSURFACEZM = 3015,
    TINZM = 3016
};

/// geometry interface
class Geometry
{
  public:
    /*!
     * @brief returns the geometry type (e.g. GeometryType::Point, GeometryType::MultiPoint)
     * @return the geometry type
     *
     * @since 0.0.1
     */
    virtual GeometryType type() const = 0;

    /*!
     * @brief returns the geometry detailed type (e.g. GeometryType::PointZ, GeometryType::MultiPointZM)
     * @return the geometry detailed type
     *
     * @since 0.0.1
     */
    virtual GeometryDetailedType detailed_type() const = 0;

    /*!
     * @brief returns the geometry type as a string (e.g. Point, LineString)
     * @return the geometry type as a string
     *
     * @since 0.0.1
     */
    virtual std::string type_str() const = 0;

    /*!
     * @brief returns true if the geometry is empty
     * @return true if the the geometry is empty, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool empty() const = 0;

    /*!
     * @brief returns the geometry size
     * @return the size of the geometry
     *
     * @since 0.0.1
     */
    virtual size_t size() const = 0;

    /*!
     * @brief returns the dimension type of the geometry
     * @return the dimension type
     *
     * @note the dimension type is (x, y), (x, y, z), (x, y, m) and (x, y, z, m)
     *
     * @since 0.0.1
     */
    virtual DimensionType get_dimension() const = 0;

    /*!
     * @brief returns the number of dimensions of the geometry
     * @return the number of dimensions
     *
     * @note the number of dimensions is (x, y) = 2, (x, y, z) = 3, (x, y, m) = 3 and (x, y, z, m) = 4
     *
     * @since 0.0.1
     */
    virtual int8_t get_num_dimension() const = 0;

    /*!
     * @brief returns the geometry bounds
     * @return the geometry bounds
     *
     * @since 0.0.1
     */
    virtual Bounds get_bounds() const = 0;

    /*!
     * @brief returns a clone of the given geometry
     * @return a geometry clone
     *
     * @since 0.0.1
     */
    virtual std::unique_ptr<Geometry> clone() = 0;

    /*!
     * @brief returns the geometry (x, y) coordinates as a tuple
     * @return a vector of (x, y) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double>> xy() const = 0;

    /*!
     * @brief returns the geometry (x, y, z) coordinates as a tuple
     * @return a vector of (x, y, z) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double, double>> xyz() const = 0;

    /*!
     * @brief returns the geometry (x, y, m) coordinates as a tuple
     * @return a vector of (x, y, m) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double, double>> xym() const = 0;

    /*!
     * @brief returns the geometry (x, y, z, m) coordinates as a tuple
     * @return a vector of (x, y, z, m) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double, double, double>> xyzm() const = 0;

    /*!
     * @brief whether the geometry has z-coordinate
     * @return true if the geometry has z-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool has_z() const = 0;

    /*!
     * @brief whether the geometry has m-coordinate
     * @return true if the geometry has m-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool has_m() const = 0;
};

/// basic geometry type
template <typename Derived>
class BasicGeometry : public Geometry
{
  public:
    /// serialization precision
    int8_t precision = 1;

    /// a spatial reference identifier (SRID) is a unique identifier associated with a specific coordinate system
    int32_t srid = -1;

    /// geometry bounds
    Bounds bounds;

    /// the dimension type (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
    DimensionType dimension;

    GeometryType type() const override
    {
        return static_cast<const Derived*>(this)->type_();
    }

    GeometryDetailedType detailed_type() const override
    {
        auto type = static_cast<const Derived*>(this)->type_();
        switch (dimension)
        {
            case DimensionType::XY:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRY;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINT;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRING;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGON;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINT;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRING;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGON;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTION;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRING;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVE;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGON;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVE;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACE;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVE;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACE;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACE;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TIN;
                }
            }
            case DimensionType::XYZ:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRYZ;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINTZ;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRINGZ;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGONZ;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINTZ;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRINGZ;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGONZ;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTIONZ;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRINGZ;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVEZ;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGONZ;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVEZ;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACEZ;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVEZ;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACEZ;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACEZ;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TINZ;
                }
            }
            case DimensionType::XYM:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRYM;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINTM;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRINGM;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGONM;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINTM;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRINGM;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGONM;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTIONM;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRINGM;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVEM;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGONM;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVEM;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACEM;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVEM;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACEM;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACEM;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TINM;
                }
            }
            case DimensionType::XYZM:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRYZM;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINTZM;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRINGZM;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGONZM;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINTZM;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRINGZM;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGONZM;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTIONZM;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRINGZM;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVEZM;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGONZM;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVEZM;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACEZM;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVEZM;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACEZM;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACEZM;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TINZM;
                }
            }
        }
        return GeometryDetailedType::GEOMETRY;
    }

    std::string type_str() const override
    {
        return static_cast<const Derived*>(this)->type_str_();
    }

    bool empty() const override
    {
        return static_cast<const Derived*>(this)->empty_();
    }

    size_t size() const override
    {
        return static_cast<const Derived*>(this)->size_();
    }

    std::unique_ptr<Geometry> clone() override
    {
        return std::unique_ptr<Derived>(new Derived(*static_cast<Derived*>(this)));
    };

    std::vector<std::tuple<double, double>> xy() const override
    {
        return static_cast<const Derived*>(this)->xy_();
    }

    std::vector<std::tuple<double, double, double>> xyz() const override
    {
        return static_cast<const Derived*>(this)->xyz_();
    }

    std::vector<std::tuple<double, double, double>> xym() const override
    {
        return static_cast<const Derived*>(this)->xym_();
    }

    std::vector<std::tuple<double, double, double, double>> xyzm() const override
    {
        return static_cast<const Derived*>(this)->xyzm_();
    }

    DimensionType get_dimension() const override
    {
        return dimension;
    }

    Bounds get_bounds() const override
    {
        return bounds;
    }

    bool has_z() const override
    {
        return dimension == DimensionType::XYZ or dimension == DimensionType::XYZM;
    }

    bool has_m() const override
    {
        return dimension == DimensionType::XYM or dimension == DimensionType::XYZM;
    }

    int8_t get_num_dimension() const override
    {
        switch (dimension)
        {
            case DimensionType::XY:
                return 2;
            case DimensionType::XYZ:
            case DimensionType::XYM:
                return 3;
            default:
                return 4;
        }
    }
};

}  // namespace shapes
}  // namespace simo