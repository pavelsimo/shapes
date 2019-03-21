#pragma once

#include <ciso646>
#include <vector>
#include <memory>
#include <simo/shapes_fwd.hpp>
#include <simo/geom/bounds.hpp>
#include <simo/geom/types.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief abstract class for all geometries
 * @tparam T the geometry type (e.g. Point, Polygon, LineString)
 *
 * @since 0.0.1
 */
template <typename T>
class BaseGeometry
{
  public:
    /// serialization precision
    int8_t precision = 1;

    /// a spatial reference identifier (SRID) is a unique identifier associated with a specific coordinate system
    int32_t srid = -1;

    /// the geometry bounds
    Bounds bounds{};

    /// the dimension type is either (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
    DimensionType dim = DimensionType::XY;

    /*!
     * @brief returns the geometry type (e.g. GeometryType::Point, GeometryType::MultiPoint)
     * @return the geometry type
     *
     * @since 0.0.1
     */
    GeometryType type() const
    {
        return static_cast<const T*>(this)->type_();
    }

    /*!
     * @brief returns the geometry detailed type (e.g. GeometryType::PointZ, GeometryType::MultiPointZM)
     * @return the geometry detailed type
     *
     * @since 0.0.1
     */
    GeometryDetailedType detailed_type() const
    {
        auto type = static_cast<const T*>(this)->type_();
        switch (dim)
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

    /*!
     * @brief returns the geometry type as a string (e.g. Point, LineString)
     * @return the geometry type as a string
     *
     * @since 0.0.1
     */
    std::string type_str() const
    {
        return static_cast<const T*>(this)->type_str_();
    }

    /*!
     * @brief returns true if the geometry is empty
     * @return true if the the geometry is empty, otherwise false
     *
     * @since 0.0.1
     */
    bool empty() const
    {
        return static_cast<const T*>(this)->empty_();
    }

    /*!
     * @brief returns the geometry size
     * @return the size of the geometry
     *
     * @since 0.0.1
     */
    size_t size() const
    {
        return static_cast<const T*>(this)->size_();
    }

    /*!
     * @brief returns the geometry (x, y) coordinates as a tuple
     * @return a vector of (x, y) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double>> xy() const
    {
        return static_cast<const T*>(this)->xy_();
    }

    /*!
     * @brief returns the geometry (x, y, z) coordinates as a tuple
     * @return a vector of (x, y, z) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double, double>> xyz() const
    {
        return static_cast<const T*>(this)->xyz_();
    }

    /*!
     * @brief returns the geometry (x, y, m) coordinates as a tuple
     * @return a vector of (x, y, m) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double, double>> xym() const
    {
        return static_cast<const T*>(this)->xym_();
    }

    /*!
     * @brief returns the geometry (x, y, z, m) coordinates as a tuple
     * @return a vector of (x, y, z, m) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double, double, double>> xyzm() const
    {
        return static_cast<const T*>(this)->xyzm_();
    }

    /*!
     * @brief whether the geometry has z-coordinate
     * @return true if the geometry has z-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    bool has_z() const
    {
        return dim == DimensionType::XYZ or dim == DimensionType::XYZM;
    }

    /*!
     * @brief whether the geometry has m-coordinate
     * @return true if the geometry has m-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    bool has_m() const
    {
        return dim == DimensionType::XYM or dim == DimensionType::XYZM;
    }

    /*!
     * @brief whether the geometry is closed
     * @return true if the geometry is closed, otherwise false
     *
     * @since 0.0.1
     */
    bool is_closed() const
    {
        return static_cast<const T*>(this)->is_closed_();
    }

    /*!
     * @brief returns the number of dimensions of the geometry
     * @return the number of dimensions
     *
     * @note the number of dimensions is (x, y) = 2, (x, y, z) = 3, (x, y, m) = 3 and (x, y, z, m) = 4
     *
     * @since 0.0.1
     */
    int8_t ndim() const
    {
        switch (dim)
        {
            case DimensionType::XYZM:
                return 4;
            case DimensionType::XYZ:
                // fall through
            case DimensionType::XYM:
                return 3;
            default:
                return 2;
        }
    }
};

/*!
 * @brief the geometry type
 *
 * @since 0.0.1
 */
typedef union Geometry
{
    Point* point;                             ///< Point value
    MultiPoint* multipoint;                   ///< MultiPoint value
    LineString* linestring;                   ///< LineString value
    MultiLineString* multilinestring;         ///< MultiLineString value
    Polygon* polygon;                         ///< Polygon value
    MultiPolygon* multipolygon;               ///< MultiPolygon value
    GeometryCollection* geometrycollection;   ///< GeometryCollection value
} Geometry;

}  // namespace shapes
}  // namespace simo