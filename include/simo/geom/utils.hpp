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
 * @brief Returns the dimension type given a geometry type
 *
 * @param geom_type the geometry type
 * @return the dimension type
 *
 * @since 0.0.1
 */
dimension_type get_dim(geometry_type geom_type) noexcept
{
    int value = static_cast<int>(geom_type);
    if (value >= 1000 and value < 2000)
    {
        return dimension_type::XYZ;
    }
    if (value >= 2000 and value < 3000)
    {
        return dimension_type::XYM;
    }
    if (value >= 3000)
    {
        return dimension_type::XYZM;
    }
    return dimension_type::XY;
}

/*!
 * @brief Returns the dimension type given the number of dimensions
 *
 * @param ndim the number of dimensions
 * @return the dimension type
 *
 * @since 0.0.1
 */
dimension_type get_dim(int8_t ndim) noexcept
{
    switch (ndim)
    {
        case 3:
            return dimension_type::XYZ;
        case 4:
            return dimension_type::XYZM;
        default:
            return dimension_type::XY;
    }
}

/*!
 * @brief Returns the number of dimensions given a dimension type
 *
 * @param dim_type the dimension type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(dimension_type dim_type) noexcept
{
    switch (dim_type)
    {
        case dimension_type::XYZM:
            return 4;
        case dimension_type::XYZ:
        case dimension_type::XYM:
            return 3;
        case dimension_type::XY:
            return 2;
    }
}

/*!
 * @brief Returns the number of dimensions given a geometry type
 *
 * @param geom_type the geometry type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(geometry_type geom_type) noexcept
{
    return get_ndim(get_dim(geom_type));
}

/*!
 * @brief Returns a geometry type given the geometry type
 *
 * @param geom_type the geometry type
 * @return a geometry type
 *
 * @since 0.0.1
 */
geometry_type get_geom_type(geometry_type geom_type) noexcept
{
    switch (geom_type)
    {
        case geometry_type::GEOMETRY:
        case geometry_type::GEOMETRYZ:
        case geometry_type::GEOMETRYM:
        case geometry_type::GEOMETRYZM:
            return geometry_type::GEOMETRY;
        case geometry_type::POINT:
        case geometry_type::POINTZ:
        case geometry_type::POINTM:
        case geometry_type::POINTZM:
            return geometry_type::POINT;
        case geometry_type::MULTIPOINT:
        case geometry_type::MULTIPOINTZ:
        case geometry_type::MULTIPOINTM:
        case geometry_type::MULTIPOINTZM:
            return geometry_type::MULTIPOINT;
        case geometry_type::LINESTRING:
        case geometry_type::LINESTRINGZ:
        case geometry_type::LINESTRINGM:
        case geometry_type::LINESTRINGZM:
            return geometry_type::LINESTRING;
        case geometry_type::MULTILINESTRING:
        case geometry_type::MULTILINESTRINGZ:
        case geometry_type::MULTILINESTRINGM:
        case geometry_type::MULTILINESTRINGZM:
            return geometry_type::MULTILINESTRING;
        case geometry_type::POLYGON:
        case geometry_type::POLYGONZ:
        case geometry_type::POLYGONM:
        case geometry_type::POLYGONZM:
            return geometry_type::POLYGON;
        case geometry_type::MULTIPOLYGON:
        case geometry_type::MULTIPOLYGONZ:
        case geometry_type::MULTIPOLYGONM:
        case geometry_type::MULTIPOLYGONZM:
            return geometry_type::MULTIPOLYGON;
        case geometry_type::GEOMETRYCOLLECTION:
        case geometry_type::GEOMETRYCOLLECTIONZ:
        case geometry_type::GEOMETRYCOLLECTIONM:
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return geometry_type::GEOMETRYCOLLECTION;
        case geometry_type::CIRCULARSTRING:
        case geometry_type::CIRCULARSTRINGZ:
        case geometry_type::CIRCULARSTRINGM:
        case geometry_type::CIRCULARSTRINGZM:
            return geometry_type::CIRCULARSTRING;
        case geometry_type::COMPOUNDCURVE:
        case geometry_type::COMPOUNDCURVEZ:
        case geometry_type::COMPOUNDCURVEM:
        case geometry_type::COMPOUNDCURVEZM:
            return geometry_type::COMPOUNDCURVE;
        case geometry_type::CURVEPOLYGON:
        case geometry_type::CURVEPOLYGONZ:
        case geometry_type::CURVEPOLYGONM:
        case geometry_type::CURVEPOLYGONZM:
            return geometry_type::CURVEPOLYGON;
        case geometry_type::MULTICURVE:
        case geometry_type::MULTICURVEZ:
        case geometry_type::MULTICURVEM:
        case geometry_type::MULTICURVEZM:
            return geometry_type::MULTICURVE;
        case geometry_type::MULTISURFACE:
        case geometry_type::MULTISURFACEZ:
        case geometry_type::MULTISURFACEM:
        case geometry_type::MULTISURFACEZM:
            return geometry_type::MULTISURFACE;
        case geometry_type::CURVE:
        case geometry_type::CURVEZ:
        case geometry_type::CURVEM:
        case geometry_type::CURVEZM:
            return geometry_type::CURVE;
        case geometry_type::SURFACE:
        case geometry_type::SURFACEZ:
        case geometry_type::SURFACEM:
        case geometry_type::SURFACEZM:
            return geometry_type::SURFACE;
        case geometry_type::POLYHEDRALSURFACE:
        case geometry_type::POLYHEDRALSURFACEZ:
        case geometry_type::POLYHEDRALSURFACEM:
        case geometry_type::POLYHEDRALSURFACEZM:
            return geometry_type::POLYHEDRALSURFACE;
        case geometry_type::TIN:
        case geometry_type::TINZ:
        case geometry_type::TINM:
        case geometry_type::TINZM:
            return geometry_type::TIN;
    }
}

/*!
 * @brief Returns a geometry type with dimension given the geometry type and the dimension type
 *
 * @param geom_type the geometry type
 * @param dim_type the dimension type
 * @return a geometry type
 *
 * @since 0.0.1
 */
geometry_type get_geom_type_dim(geometry_type geom_type, dimension_type dim_type) noexcept
{
    auto geom_type_ = get_geom_type(geom_type);
    switch (dim_type)
    {
        case dimension_type::XY:
        {
            return geom_type_;
        }
        case dimension_type::XYZ:
        {
            switch (geom_type_)
            {
                case geometry_type::POINT:
                    return geometry_type::POINTZ;
                case geometry_type::LINESTRING:
                    return geometry_type::LINESTRINGZ;
                case geometry_type::POLYGON:
                    return geometry_type::POLYGONZ;
                case geometry_type::MULTIPOINT:
                    return geometry_type::MULTIPOINTZ;
                case geometry_type::MULTILINESTRING:
                    return geometry_type::MULTILINESTRINGZ;
                case geometry_type::MULTIPOLYGON:
                    return geometry_type::MULTIPOLYGONZ;
                case geometry_type::GEOMETRYCOLLECTION:
                    return geometry_type::GEOMETRYCOLLECTIONZ;
                case geometry_type::CIRCULARSTRING:
                    return geometry_type::CIRCULARSTRINGZ;
                case geometry_type::COMPOUNDCURVE:
                    return geometry_type::COMPOUNDCURVEZ;
                case geometry_type::CURVEPOLYGON:
                    return geometry_type::CURVEPOLYGONZ;
                case geometry_type::MULTICURVE:
                    return geometry_type::MULTICURVEZ;
                case geometry_type::MULTISURFACE:
                    return geometry_type::MULTISURFACEZ;
                case geometry_type::CURVE:
                    return geometry_type::CURVEZ;
                case geometry_type::SURFACE:
                    return geometry_type::SURFACEZ;
                case geometry_type::POLYHEDRALSURFACE:
                    return geometry_type::POLYHEDRALSURFACEZ;
                case geometry_type::TIN:
                    return geometry_type::TINZ;
                default:
                    return geometry_type::GEOMETRYZ;
            }
        }
        case dimension_type::XYM:
        {
            switch (geom_type_)
            {
                case geometry_type::POINT:
                    return geometry_type::POINTM;
                case geometry_type::LINESTRING:
                    return geometry_type::LINESTRINGM;
                case geometry_type::POLYGON:
                    return geometry_type::POLYGONM;
                case geometry_type::MULTIPOINT:
                    return geometry_type::MULTIPOINTM;
                case geometry_type::MULTILINESTRING:
                    return geometry_type::MULTILINESTRINGM;
                case geometry_type::MULTIPOLYGON:
                    return geometry_type::MULTIPOLYGONM;
                case geometry_type::GEOMETRYCOLLECTION:
                    return geometry_type::GEOMETRYCOLLECTIONM;
                case geometry_type::CIRCULARSTRING:
                    return geometry_type::CIRCULARSTRINGM;
                case geometry_type::COMPOUNDCURVE:
                    return geometry_type::COMPOUNDCURVEM;
                case geometry_type::CURVEPOLYGON:
                    return geometry_type::CURVEPOLYGONM;
                case geometry_type::MULTICURVE:
                    return geometry_type::MULTICURVEM;
                case geometry_type::MULTISURFACE:
                    return geometry_type::MULTISURFACEM;
                case geometry_type::CURVE:
                    return geometry_type::CURVEM;
                case geometry_type::SURFACE:
                    return geometry_type::SURFACEM;
                case geometry_type::POLYHEDRALSURFACE:
                    return geometry_type::POLYHEDRALSURFACEM;
                case geometry_type::TIN:
                    return geometry_type::TINM;
                default:
                    return geometry_type::GEOMETRYM;
            }
        }
        case dimension_type::XYZM:
        {
            switch (geom_type_)
            {
                case geometry_type::POINT:
                    return geometry_type::POINTZM;
                case geometry_type::LINESTRING:
                    return geometry_type::LINESTRINGZM;
                case geometry_type::POLYGON:
                    return geometry_type::POLYGONZM;
                case geometry_type::MULTIPOINT:
                    return geometry_type::MULTIPOINTZM;
                case geometry_type::MULTILINESTRING:
                    return geometry_type::MULTILINESTRINGZM;
                case geometry_type::MULTIPOLYGON:
                    return geometry_type::MULTIPOLYGONZM;
                case geometry_type::GEOMETRYCOLLECTION:
                    return geometry_type::GEOMETRYCOLLECTIONZM;
                case geometry_type::CIRCULARSTRING:
                    return geometry_type::CIRCULARSTRINGZM;
                case geometry_type::COMPOUNDCURVE:
                    return geometry_type::COMPOUNDCURVEZM;
                case geometry_type::CURVEPOLYGON:
                    return geometry_type::CURVEPOLYGONZM;
                case geometry_type::MULTICURVE:
                    return geometry_type::MULTICURVEZM;
                case geometry_type::MULTISURFACE:
                    return geometry_type::MULTISURFACEZM;
                case geometry_type::CURVE:
                    return geometry_type::CURVEZM;
                case geometry_type::SURFACE:
                    return geometry_type::SURFACEZM;
                case geometry_type::POLYHEDRALSURFACE:
                    return geometry_type::POLYHEDRALSURFACEZM;
                case geometry_type::TIN:
                    return geometry_type::TINZM;
                default:
                    return geometry_type::GEOMETRYZM;
            }
        }
    }
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a Point, otherwise false
 *
 * @since 0.0.1
 */
bool is_point(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::POINT or geom_type == geometry_type::POINTZ or geom_type == geometry_type::POINTM or geom_type == geometry_type::POINTZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a MultiPoint, otherwise false
 *
 * @since 0.0.1
 */
bool is_multipoint(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::MULTIPOINT or geom_type == geometry_type::MULTIPOINTZ or geom_type == geometry_type::MULTIPOINTM or geom_type == geometry_type::MULTIPOINTZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a LineString, otherwise false
 *
 * @since 0.0.1
 */
bool is_linestring(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::LINESTRING or geom_type == geometry_type::LINESTRINGZ or geom_type == geometry_type::LINESTRINGM or geom_type == geometry_type::LINESTRINGZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a MultiLineString, otherwise false
 *
 * @since 0.0.1
 */
bool is_multilinestring(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::MULTILINESTRING or geom_type == geometry_type::MULTILINESTRINGZ or geom_type == geometry_type::MULTILINESTRINGM or geom_type == geometry_type::MULTILINESTRINGZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a Polygon, otherwise false
 *
 * @since 0.0.1
 */
bool is_polygon(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::POLYGON or geom_type == geometry_type::POLYGONZ or geom_type == geometry_type::POLYGONM or geom_type == geometry_type::POLYGONZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a MultiPolygon, otherwise false
 *
 * @since 0.0.1
 */
bool is_multipolygon(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::MULTIPOLYGON or geom_type == geometry_type::MULTIPOLYGONZ or geom_type == geometry_type::MULTIPOLYGONM or geom_type == geometry_type::MULTIPOLYGONZM;
}

}  // namespace utils
}  // namespace shapes
}  // namespace simo