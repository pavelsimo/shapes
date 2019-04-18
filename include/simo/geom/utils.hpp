#pragma once

#include <ciso646>
#include <simo/geom/types.hpp>

namespace simo
{
namespace shapes
{
namespace utils
{

/*!
 * @brief returns the dimension type given a geometry type
 * @param geom_type the geometry type
 * @return the dimension type
 *
 * @since 0.0.1
 */
DimensionType get_dim(GeometryType geom_type) noexcept
{
    int value = static_cast<int>(geom_type);
    if (value >= 1000 and value < 2000)
    {
        return DimensionType::XYZ;
    }
    if (value >= 2000 and value < 3000)
    {
        return DimensionType::XYM;
    }
    if (value >= 3000)
    {
        return DimensionType::XYZM;
    }
    return DimensionType::XY;
}

/*!
 * @brief returns the number of dimensions given a dimension type
 * @param dim_type the dimension type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(DimensionType dim_type) noexcept
{
    switch (dim_type)
    {
        case DimensionType::XYZM:
            return 4;
        case DimensionType::XYZ:
            // fall through
        case DimensionType::XYM:
            return 3;
        case DimensionType::XY:
            return 2;
    }
}

/*!
 * @brief returns the number of dimensions given a geometry type
 * @param geom_type the geometry type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(GeometryType geom_type) noexcept
{
    return get_ndim(get_dim(geom_type));
}


/*!
 * @brief returns a geometry type given the geometry type
 * @param geom_type the geometry type
 * @return a geometry type
 *
 * @since 0.0.1
 */
GeometryType get_geom_type(GeometryType geom_type)
{
    switch (geom_type)
    {
        case GeometryType::GEOMETRY:
        case GeometryType::GEOMETRYZ:
        case GeometryType::GEOMETRYM:
        case GeometryType::GEOMETRYZM:
            return GeometryType::GEOMETRY;
        case GeometryType::POINT:
        case GeometryType::POINTZ:
        case GeometryType::POINTM:
        case GeometryType::POINTZM:
            return GeometryType::POINT;
        case GeometryType::MULTIPOINT:
        case GeometryType::MULTIPOINTZ:
        case GeometryType::MULTIPOINTM:
        case GeometryType::MULTIPOINTZM:
            return GeometryType::MULTIPOINT;
        case GeometryType::LINESTRING:
        case GeometryType::LINESTRINGZ:
        case GeometryType::LINESTRINGM:
        case GeometryType::LINESTRINGZM:
            return GeometryType::LINESTRING;
        case GeometryType::MULTILINESTRING:
        case GeometryType::MULTILINESTRINGZ:
        case GeometryType::MULTILINESTRINGM:
        case GeometryType::MULTILINESTRINGZM:
            return GeometryType::MULTILINESTRING;
        case GeometryType::POLYGON:
        case GeometryType::POLYGONZ:
        case GeometryType::POLYGONM:
        case GeometryType::POLYGONZM:
            return GeometryType::POLYGON;
        case GeometryType::MULTIPOLYGON:
        case GeometryType::MULTIPOLYGONZ:
        case GeometryType::MULTIPOLYGONM:
        case GeometryType::MULTIPOLYGONZM:
            return GeometryType::MULTIPOLYGON;
        case GeometryType::GEOMETRYCOLLECTION:
        case GeometryType::GEOMETRYCOLLECTIONZ:
        case GeometryType::GEOMETRYCOLLECTIONM:
        case GeometryType::GEOMETRYCOLLECTIONZM:
            return GeometryType::GEOMETRYCOLLECTION;
        case GeometryType::CIRCULARSTRING:
        case GeometryType::CIRCULARSTRINGZ:
        case GeometryType::CIRCULARSTRINGM:
        case GeometryType::CIRCULARSTRINGZM:
            return GeometryType::CIRCULARSTRING;
        case GeometryType::COMPOUNDCURVE:
        case GeometryType::COMPOUNDCURVEZ:
        case GeometryType::COMPOUNDCURVEM:
        case GeometryType::COMPOUNDCURVEZM:
            return GeometryType::COMPOUNDCURVE;
        case GeometryType::CURVEPOLYGON:
        case GeometryType::CURVEPOLYGONZ:
        case GeometryType::CURVEPOLYGONM:
        case GeometryType::CURVEPOLYGONZM:
            return GeometryType::CURVEPOLYGON;
        case GeometryType::MULTICURVE:
        case GeometryType::MULTICURVEZ:
        case GeometryType::MULTICURVEM:
        case GeometryType::MULTICURVEZM:
            return GeometryType::MULTICURVE;
        case GeometryType::MULTISURFACE:
        case GeometryType::MULTISURFACEZ:
        case GeometryType::MULTISURFACEM:
        case GeometryType::MULTISURFACEZM:
            return GeometryType::MULTISURFACE;
        case GeometryType::CURVE:
        case GeometryType::CURVEZ:
        case GeometryType::CURVEM:
        case GeometryType::CURVEZM:
            return GeometryType::CURVE;
        case GeometryType::SURFACE:
        case GeometryType::SURFACEZ:
        case GeometryType::SURFACEM:
        case GeometryType::SURFACEZM:
            return GeometryType::SURFACE;
        case GeometryType::POLYHEDRALSURFACE:
        case GeometryType::POLYHEDRALSURFACEZ:
        case GeometryType::POLYHEDRALSURFACEM:
        case GeometryType::POLYHEDRALSURFACEZM:
            return GeometryType::POLYHEDRALSURFACE;
        case GeometryType::TIN:
        case GeometryType::TINZ:
        case GeometryType::TINM:
        case GeometryType::TINZM:
            return GeometryType::TIN;
    }
}

/*!
 * @brief returns a geometry type with dimension given the geometry type and the dimension type
 * @param geom_type the geometry type
 * @param dim_type the dimension type
 * @return a geometry type
 *
 * @since 0.0.1
 */
GeometryType get_geom_type_dim(GeometryType geom_type, DimensionType dim_type) noexcept
{
    auto geom_type_ = get_geom_type(geom_type);
    switch (dim_type)
    {
        case DimensionType::XY:
        {
            return geom_type_;
        }
        case DimensionType::XYZ:
        {
            switch (geom_type_)
            {
                case GeometryType::POINT:
                    return GeometryType::POINTZ;
                case GeometryType::LINESTRING:
                    return GeometryType::LINESTRINGZ;
                case GeometryType::POLYGON:
                    return GeometryType::POLYGONZ;
                case GeometryType::MULTIPOINT:
                    return GeometryType::MULTIPOINTZ;
                case GeometryType::MULTILINESTRING:
                    return GeometryType::MULTILINESTRINGZ;
                case GeometryType::MULTIPOLYGON:
                    return GeometryType::MULTIPOLYGONZ;
                case GeometryType::GEOMETRYCOLLECTION:
                    return GeometryType::GEOMETRYCOLLECTIONZ;
                case GeometryType::CIRCULARSTRING:
                    return GeometryType::CIRCULARSTRINGZ;
                case GeometryType::COMPOUNDCURVE:
                    return GeometryType::COMPOUNDCURVEZ;
                case GeometryType::CURVEPOLYGON:
                    return GeometryType::CURVEPOLYGONZ;
                case GeometryType::MULTICURVE:
                    return GeometryType::MULTICURVEZ;
                case GeometryType::MULTISURFACE:
                    return GeometryType::MULTISURFACEZ;
                case GeometryType::CURVE:
                    return GeometryType::CURVEZ;
                case GeometryType::SURFACE:
                    return GeometryType::SURFACEZ;
                case GeometryType::POLYHEDRALSURFACE:
                    return GeometryType::POLYHEDRALSURFACEZ;
                case GeometryType::TIN:
                    return GeometryType::TINZ;
                default:
                    return GeometryType::GEOMETRYZ;
            }
        }
        case DimensionType::XYM:
        {
            switch (geom_type_)
            {
                case GeometryType::POINT:
                    return GeometryType::POINTM;
                case GeometryType::LINESTRING:
                    return GeometryType::LINESTRINGM;
                case GeometryType::POLYGON:
                    return GeometryType::POLYGONM;
                case GeometryType::MULTIPOINT:
                    return GeometryType::MULTIPOINTM;
                case GeometryType::MULTILINESTRING:
                    return GeometryType::MULTILINESTRINGM;
                case GeometryType::MULTIPOLYGON:
                    return GeometryType::MULTIPOLYGONM;
                case GeometryType::GEOMETRYCOLLECTION:
                    return GeometryType::GEOMETRYCOLLECTIONM;
                case GeometryType::CIRCULARSTRING:
                    return GeometryType::CIRCULARSTRINGM;
                case GeometryType::COMPOUNDCURVE:
                    return GeometryType::COMPOUNDCURVEM;
                case GeometryType::CURVEPOLYGON:
                    return GeometryType::CURVEPOLYGONM;
                case GeometryType::MULTICURVE:
                    return GeometryType::MULTICURVEM;
                case GeometryType::MULTISURFACE:
                    return GeometryType::MULTISURFACEM;
                case GeometryType::CURVE:
                    return GeometryType::CURVEM;
                case GeometryType::SURFACE:
                    return GeometryType::SURFACEM;
                case GeometryType::POLYHEDRALSURFACE:
                    return GeometryType::POLYHEDRALSURFACEM;
                case GeometryType::TIN:
                    return GeometryType::TINM;
                default:
                    return GeometryType::GEOMETRYM;
            }
        }
        case DimensionType::XYZM:
        {
            switch (geom_type_)
            {
                case GeometryType::POINT:
                    return GeometryType::POINTZM;
                case GeometryType::LINESTRING:
                    return GeometryType::LINESTRINGZM;
                case GeometryType::POLYGON:
                    return GeometryType::POLYGONZM;
                case GeometryType::MULTIPOINT:
                    return GeometryType::MULTIPOINTZM;
                case GeometryType::MULTILINESTRING:
                    return GeometryType::MULTILINESTRINGZM;
                case GeometryType::MULTIPOLYGON:
                    return GeometryType::MULTIPOLYGONZM;
                case GeometryType::GEOMETRYCOLLECTION:
                    return GeometryType::GEOMETRYCOLLECTIONZM;
                case GeometryType::CIRCULARSTRING:
                    return GeometryType::CIRCULARSTRINGZM;
                case GeometryType::COMPOUNDCURVE:
                    return GeometryType::COMPOUNDCURVEZM;
                case GeometryType::CURVEPOLYGON:
                    return GeometryType::CURVEPOLYGONZM;
                case GeometryType::MULTICURVE:
                    return GeometryType::MULTICURVEZM;
                case GeometryType::MULTISURFACE:
                    return GeometryType::MULTISURFACEZM;
                case GeometryType::CURVE:
                    return GeometryType::CURVEZM;
                case GeometryType::SURFACE:
                    return GeometryType::SURFACEZM;
                case GeometryType::POLYHEDRALSURFACE:
                    return GeometryType::POLYHEDRALSURFACEZM;
                case GeometryType::TIN:
                    return GeometryType::TINZM;
                default:
                    return GeometryType::GEOMETRYZM;
            }
        }
    }
}

/*!
 * @param geom_type the geometry type
 * @return returns true if the geometry type is a Point, otherwise false
 *
 * @since 0.0.1
 */
bool is_point(GeometryType geom_type)
{
    return geom_type == GeometryType::POINT or geom_type == GeometryType::POINTZ or geom_type == GeometryType::POINTM or geom_type == GeometryType::POINTZM;
}

/*!
 * @param geom_type the geometry type
 * @return returns true if the geometry type is a MultiPoint, otherwise false
 *
 * @since 0.0.1
 */
bool is_multipoint(GeometryType geom_type)
{
    return geom_type == GeometryType::MULTIPOINT or geom_type == GeometryType::MULTIPOINTZ or geom_type == GeometryType::MULTIPOINTM or geom_type == GeometryType::MULTIPOINTZM;
}

/*!
 * @param geom_type the geometry type
 * @return returns true if the geometry type is a LineString, otherwise false
 *
 * @since 0.0.1
 */
bool is_linestring(GeometryType geom_type)
{
    return geom_type == GeometryType::LINESTRING or geom_type == GeometryType::LINESTRINGZ or geom_type == GeometryType::LINESTRINGM or geom_type == GeometryType::LINESTRINGZM;
}

/*!
 * @param geom_type the geometry type
 * @return returns true if the geometry type is a MultiLineString, otherwise false
 *
 * @since 0.0.1
 */
bool is_multilinestring(GeometryType geom_type)
{
    return geom_type == GeometryType::MULTILINESTRING or geom_type == GeometryType::MULTILINESTRINGZ or geom_type == GeometryType::MULTILINESTRINGM or geom_type == GeometryType::MULTILINESTRINGZM;
}

/*!
 * @param geom_type the geometry type
 * @return returns true if the geometry type is a Polygon, otherwise false
 *
 * @since 0.0.1
 */
bool is_polygon(GeometryType geom_type)
{
    return geom_type == GeometryType::POLYGON or geom_type == GeometryType::POLYGONZ or geom_type == GeometryType::POLYGONM or geom_type == GeometryType::POLYGONZM;
}

/*!
 * @param geom_type the geometry type
 * @return returns true if the geometry type is a MultiPolygon, otherwise false
 *
 * @since 0.0.1
 */
bool is_multipolygon(GeometryType geom_type)
{
    return geom_type == GeometryType::MULTIPOLYGON or geom_type == GeometryType::MULTIPOLYGONZ or geom_type == GeometryType::MULTIPOLYGONM or geom_type == GeometryType::MULTIPOLYGONZM;
}

}  // namespace utils
}  // namespace shapes
}  // namespace simo