#pragma once

namespace simo
{
namespace shapes
{

/*!
 * @brief geometry dimension type is (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
 *
 * @since 0.0.1
 */
enum class DimensionType
{
    XY   = 1,
    XYZ  = 2,
    XYM  = 3,
    XYZM = 4
};

/*!
 * @brief geometry types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
 *
 * @since 0.0.1
 */
enum class GeometryType
{
    GEOMETRY           = 0,
    POINT              = 1,
    LINESTRING         = 2,
    POLYGON            = 3,
    MULTIPOINT         = 4,
    MULTILINESTRING    = 5,
    MULTIPOLYGON       = 6,
    GEOMETRYCOLLECTION = 7,
    CIRCULARSTRING     = 8,
    COMPOUNDCURVE      = 9,
    CURVEPOLYGON       = 10,
    MULTICURVE         = 11,
    MULTISURFACE       = 12,
    CURVE              = 13,
    SURFACE            = 14,
    POLYHEDRALSURFACE  = 15,
    TIN                = 16
};

/*!
 * @brief element type for the geometry
 *
 * @since 0.0.1
 */
enum class ElementType
{
    POINT      = 1,
    LINESTRING = 2,
    POLYGON    = 3
};

/*!
 * @brief geometry detailed types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
 *
 * @since 0.0.1
 */
enum class GeometryDetailedType
{
    GEOMETRY             = 0,
    POINT                = 1,
    LINESTRING           = 2,
    POLYGON              = 3,
    MULTIPOINT           = 4,
    MULTILINESTRING      = 5,
    MULTIPOLYGON         = 6,
    GEOMETRYCOLLECTION   = 7,
    CIRCULARSTRING       = 8,
    COMPOUNDCURVE        = 9,
    CURVEPOLYGON         = 10,
    MULTICURVE           = 11,
    MULTISURFACE         = 12,
    CURVE                = 13,
    SURFACE              = 14,
    POLYHEDRALSURFACE    = 15,
    TIN                  = 16,
    GEOMETRYZ            = 1000,
    POINTZ               = 1001,
    LINESTRINGZ          = 1002,
    POLYGONZ             = 1003,
    MULTIPOINTZ          = 1004,
    MULTILINESTRINGZ     = 1005,
    MULTIPOLYGONZ        = 1006,
    GEOMETRYCOLLECTIONZ  = 1007,
    CIRCULARSTRINGZ      = 1008,
    COMPOUNDCURVEZ       = 1009,
    CURVEPOLYGONZ        = 1010,
    MULTICURVEZ          = 1011,
    MULTISURFACEZ        = 1012,
    CURVEZ               = 1013,
    SURFACEZ             = 1014,
    POLYHEDRALSURFACEZ   = 1015,
    TINZ                 = 1016,
    GEOMETRYM            = 2000,
    POINTM               = 2001,
    LINESTRINGM          = 2002,
    POLYGONM             = 2003,
    MULTIPOINTM          = 2004,
    MULTILINESTRINGM     = 2005,
    MULTIPOLYGONM        = 2006,
    GEOMETRYCOLLECTIONM  = 2007,
    CIRCULARSTRINGM      = 2008,
    COMPOUNDCURVEM       = 2009,
    CURVEPOLYGONM        = 2010,
    MULTICURVEM          = 2011,
    MULTISURFACEM        = 2012,
    CURVEM               = 2013,
    SURFACEM             = 2014,
    POLYHEDRALSURFACEM   = 2015,
    TINM                 = 2016,
    GEOMETRYZM           = 3000,
    POINTZM              = 3001,
    LINESTRINGZM         = 3002,
    POLYGONZM            = 3003,
    MULTIPOINTZM         = 3004,
    MULTILINESTRINGZM    = 3005,
    MULTIPOLYGONZM       = 3006,
    GEOMETRYCOLLECTIONZM = 3007,
    CIRCULARSTRINGZM     = 3008,
    COMPOUNDCURVEZM      = 3009,
    CURVEPOLYGONZM       = 3010,
    MULTICURVEZM         = 3011,
    MULTISURFACEZM       = 3012,
    CURVEZM              = 3013,
    SURFACEZM            = 3014,
    POLYHEDRALSURFACEZM  = 3015,
    TINZM                = 3016
};

/*!
 * @brief returns the dimension type given a geometry detailed type
 * @param detailed_type the detailed type
 * @return the dimension type
 *
 * @since 0.0.1
 */
DimensionType get_dim(GeometryDetailedType detailed_type) noexcept
{
    int value = static_cast<int>(detailed_type);
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
 * @brief returns the number of dimensions given a geometry detailed type
 * @param detailed_type the geometry detailed type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(GeometryDetailedType detailed_type) noexcept
{
    return get_ndim(get_dim(detailed_type));
}

/*!
 * @brief returns a geometry detailed type given the geometry type and dimension type
 * @param geom_type the geometry type
 * @param dim_type the dimension type
 * @return a geometry detailed type
 *
 * @since 0.0.1
 */
GeometryDetailedType get_geom_detailed_type(GeometryType geom_type, DimensionType dim_type) noexcept
{
    switch (dim_type)
    {
        case DimensionType::XY:
        {
            switch (geom_type)
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
            switch (geom_type)
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
            switch (geom_type)
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
            switch (geom_type)
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
}

/*!
 * @brief returns a geometry type given the geometry detailed type
 * @param geom_detailed_type the geometry detailed type
 * @return a geometry type
 *
 * @since 0.0.1
 */
GeometryType get_geom_type(GeometryDetailedType geom_detailed_type)
{
    switch(geom_detailed_type)
    {
        case GeometryDetailedType::GEOMETRY:
        case GeometryDetailedType::GEOMETRYZ:
        case GeometryDetailedType::GEOMETRYM:
        case GeometryDetailedType::GEOMETRYZM:
            return GeometryType::GEOMETRY;
        case GeometryDetailedType::POINT:
        case GeometryDetailedType::POINTZ:
        case GeometryDetailedType::POINTM:
        case GeometryDetailedType::POINTZM:
            return GeometryType::POINT;
        case GeometryDetailedType::MULTIPOINT:
        case GeometryDetailedType::MULTIPOINTZ:
        case GeometryDetailedType::MULTIPOINTM:
        case GeometryDetailedType::MULTIPOINTZM:
            return GeometryType::POINT;
        case GeometryDetailedType::LINESTRING:
        case GeometryDetailedType::LINESTRINGZ:
        case GeometryDetailedType::LINESTRINGM:
        case GeometryDetailedType::LINESTRINGZM:
            return GeometryType::LINESTRING;
        case GeometryDetailedType::MULTILINESTRING:
        case GeometryDetailedType::MULTILINESTRINGZ:
        case GeometryDetailedType::MULTILINESTRINGM:
        case GeometryDetailedType::MULTILINESTRINGZM:
            return GeometryType::MULTILINESTRING;
        case GeometryDetailedType::POLYGON:
        case GeometryDetailedType::POLYGONZ:
        case GeometryDetailedType::POLYGONM:
        case GeometryDetailedType::POLYGONZM:
            return GeometryType::POLYGON;
        case GeometryDetailedType::MULTIPOLYGON:
        case GeometryDetailedType::MULTIPOLYGONZ:
        case GeometryDetailedType::MULTIPOLYGONM:
        case GeometryDetailedType::MULTIPOLYGONZM:
            return GeometryType::POLYGON;
        case GeometryDetailedType::GEOMETRYCOLLECTION:
        case GeometryDetailedType::GEOMETRYCOLLECTIONZ:
        case GeometryDetailedType::GEOMETRYCOLLECTIONM:
        case GeometryDetailedType::GEOMETRYCOLLECTIONZM:
            return GeometryType::GEOMETRYCOLLECTION;
        case GeometryDetailedType::CIRCULARSTRING:
        case GeometryDetailedType::CIRCULARSTRINGZ:
        case GeometryDetailedType::CIRCULARSTRINGM:
        case GeometryDetailedType::CIRCULARSTRINGZM:
            return GeometryType::CIRCULARSTRING;
        case GeometryDetailedType::COMPOUNDCURVE:
        case GeometryDetailedType::COMPOUNDCURVEZ:
        case GeometryDetailedType::COMPOUNDCURVEM:
        case GeometryDetailedType::COMPOUNDCURVEZM:
            return GeometryType::COMPOUNDCURVE;
        case GeometryDetailedType::CURVEPOLYGON:
        case GeometryDetailedType::CURVEPOLYGONZ:
        case GeometryDetailedType::CURVEPOLYGONM:
        case GeometryDetailedType::CURVEPOLYGONZM:
            return GeometryType::CURVEPOLYGON;
        case GeometryDetailedType::MULTICURVE:
        case GeometryDetailedType::MULTICURVEZ:
        case GeometryDetailedType::MULTICURVEM:
        case GeometryDetailedType::MULTICURVEZM:
            return GeometryType::MULTICURVE;
        case GeometryDetailedType::MULTISURFACE:
        case GeometryDetailedType::MULTISURFACEZ:
        case GeometryDetailedType::MULTISURFACEM:
        case GeometryDetailedType::MULTISURFACEZM:
            return GeometryType::MULTISURFACE;
        case GeometryDetailedType::CURVE:
        case GeometryDetailedType::CURVEZ:
        case GeometryDetailedType::CURVEM:
        case GeometryDetailedType::CURVEZM:
            return GeometryType::CURVE;
        case GeometryDetailedType::SURFACE:
        case GeometryDetailedType::SURFACEZ:
        case GeometryDetailedType::SURFACEM:
        case GeometryDetailedType::SURFACEZM:
            return GeometryType::SURFACE;
        case GeometryDetailedType::POLYHEDRALSURFACE:
        case GeometryDetailedType::POLYHEDRALSURFACEZ:
        case GeometryDetailedType::POLYHEDRALSURFACEM:
        case GeometryDetailedType::POLYHEDRALSURFACEZM:
            return GeometryType::POLYHEDRALSURFACE;
        case GeometryDetailedType::TIN:
        case GeometryDetailedType::TINZ:
        case GeometryDetailedType::TINM:
        case GeometryDetailedType::TINZM:
            return GeometryType::TIN;
    }
}

}  // namespace shapes
}  // namespace simo