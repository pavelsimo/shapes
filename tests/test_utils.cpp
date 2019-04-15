#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Utils")
{
    SECTION("get_dim()")
    {
        CHECK(utils::get_dim(GeometryDetailedType::POINT) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::POINTZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::POINTM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::POINTZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOINT) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOINTZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOINTM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOINTZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryDetailedType::LINESTRING) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::LINESTRINGZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::LINESTRINGM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::LINESTRINGZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryDetailedType::MULTILINESTRING) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::MULTILINESTRINGZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::MULTILINESTRINGM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::MULTILINESTRINGZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryDetailedType::POLYGON) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::POLYGONZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::POLYGONM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::POLYGONZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOLYGON) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOLYGONZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOLYGONM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::MULTIPOLYGONZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryDetailedType::GEOMETRYCOLLECTION) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryDetailedType::GEOMETRYCOLLECTIONZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryDetailedType::GEOMETRYCOLLECTIONM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryDetailedType::GEOMETRYCOLLECTIONZM) == DimensionType::XYZM);
    }

    SECTION("get_ndim() - dimension type")
    {
        CHECK(utils::get_ndim(DimensionType::XY) == 2);
        CHECK(utils::get_ndim(DimensionType::XYZ) == 3);
        CHECK(utils::get_ndim(DimensionType::XYM) == 3);
        CHECK(utils::get_ndim(DimensionType::XYZM) == 4);
    }

    SECTION("get_ndim() - geometry_detailed_type")
    {
        CHECK(utils::get_ndim(GeometryDetailedType::POINT) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::POINTZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::POINTM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::POINTZM) == 4);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOINT) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOINTZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOINTM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOINTZM) == 4);
        CHECK(utils::get_ndim(GeometryDetailedType::LINESTRING) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::LINESTRINGZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::LINESTRINGM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::LINESTRINGZM) == 4);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTILINESTRING) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTILINESTRINGZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTILINESTRINGM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTILINESTRINGZM) == 4);
        CHECK(utils::get_ndim(GeometryDetailedType::POLYGON) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::POLYGONZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::POLYGONM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::POLYGONZM) == 4);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOLYGON) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOLYGONZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOLYGONM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::MULTIPOLYGONZM) == 4);
        CHECK(utils::get_ndim(GeometryDetailedType::GEOMETRYCOLLECTION) == 2);
        CHECK(utils::get_ndim(GeometryDetailedType::GEOMETRYCOLLECTIONZ) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::GEOMETRYCOLLECTIONM) == 3);
        CHECK(utils::get_ndim(GeometryDetailedType::GEOMETRYCOLLECTIONZM) == 4);
    }

    SECTION("get_geom_detailed_type()")
    {
        CHECK(utils::get_geom_detailed_type(GeometryType::POINT, DimensionType::XY) == GeometryDetailedType::POINT);
        CHECK(utils::get_geom_detailed_type(GeometryType::POINT, DimensionType::XYZ) == GeometryDetailedType::POINTZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::POINT, DimensionType::XYM) == GeometryDetailedType::POINTM);
        CHECK(utils::get_geom_detailed_type(GeometryType::POINT, DimensionType::XYZM) == GeometryDetailedType::POINTZM);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOINT, DimensionType::XY) == GeometryDetailedType::MULTIPOINT);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOINT, DimensionType::XYZ) == GeometryDetailedType::MULTIPOINTZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOINT, DimensionType::XYM) == GeometryDetailedType::MULTIPOINTM);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOINT, DimensionType::XYZM) == GeometryDetailedType::MULTIPOINTZM);
        CHECK(utils::get_geom_detailed_type(GeometryType::LINESTRING, DimensionType::XY) == GeometryDetailedType::LINESTRING);
        CHECK(utils::get_geom_detailed_type(GeometryType::LINESTRING, DimensionType::XYZ) == GeometryDetailedType::LINESTRINGZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::LINESTRING, DimensionType::XYM) == GeometryDetailedType::LINESTRINGM);
        CHECK(utils::get_geom_detailed_type(GeometryType::LINESTRING, DimensionType::XYZM) == GeometryDetailedType::LINESTRINGZM);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTILINESTRING, DimensionType::XY) == GeometryDetailedType::MULTILINESTRING);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTILINESTRING, DimensionType::XYZ) == GeometryDetailedType::MULTILINESTRINGZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTILINESTRING, DimensionType::XYM) == GeometryDetailedType::MULTILINESTRINGM);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTILINESTRING, DimensionType::XYZM) == GeometryDetailedType::MULTILINESTRINGZM);
        CHECK(utils::get_geom_detailed_type(GeometryType::POLYGON, DimensionType::XY) == GeometryDetailedType::POLYGON);
        CHECK(utils::get_geom_detailed_type(GeometryType::POLYGON, DimensionType::XYZ) == GeometryDetailedType::POLYGONZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::POLYGON, DimensionType::XYM) == GeometryDetailedType::POLYGONM);
        CHECK(utils::get_geom_detailed_type(GeometryType::POLYGON, DimensionType::XYZM) == GeometryDetailedType::POLYGONZM);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOLYGON, DimensionType::XY) == GeometryDetailedType::MULTIPOLYGON);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOLYGON, DimensionType::XYZ) == GeometryDetailedType::MULTIPOLYGONZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOLYGON, DimensionType::XYM) == GeometryDetailedType::MULTIPOLYGONM);
        CHECK(utils::get_geom_detailed_type(GeometryType::MULTIPOLYGON, DimensionType::XYZM) == GeometryDetailedType::MULTIPOLYGONZM);
        CHECK(utils::get_geom_detailed_type(GeometryType::GEOMETRYCOLLECTION, DimensionType::XY) == GeometryDetailedType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_detailed_type(GeometryType::GEOMETRYCOLLECTION, DimensionType::XYZ) == GeometryDetailedType::GEOMETRYCOLLECTIONZ);
        CHECK(utils::get_geom_detailed_type(GeometryType::GEOMETRYCOLLECTION, DimensionType::XYM) == GeometryDetailedType::GEOMETRYCOLLECTIONM);
        CHECK(utils::get_geom_detailed_type(GeometryType::GEOMETRYCOLLECTION, DimensionType::XYZM) == GeometryDetailedType::GEOMETRYCOLLECTIONZM);
    }

    SECTION("get_geom_type()")
    {
        CHECK(utils::get_geom_type(GeometryDetailedType::POINT) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::POINTZ) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::POINTM) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::POINTZM) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOINT) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOINTZ) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOINTM) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOINTZM) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryDetailedType::LINESTRING) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::LINESTRINGZ) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::LINESTRINGM) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::LINESTRINGZM) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTILINESTRING) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTILINESTRINGZ) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTILINESTRINGM) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTILINESTRINGZM) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryDetailedType::POLYGON) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::POLYGONZ) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::POLYGONM) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::POLYGONZM) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOLYGON) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOLYGONZ) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOLYGONM) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::MULTIPOLYGONZM) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryDetailedType::GEOMETRYCOLLECTION) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(GeometryDetailedType::GEOMETRYCOLLECTIONZ) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(GeometryDetailedType::GEOMETRYCOLLECTIONM) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(GeometryDetailedType::GEOMETRYCOLLECTIONZM) == GeometryType::GEOMETRYCOLLECTION);
    }

    SECTION("is_point()")
    {
        CHECK(utils::is_point(GeometryType::POINT));
        CHECK(utils::is_point(GeometryDetailedType::POINT));
        CHECK(utils::is_point(GeometryDetailedType::POINTZ));
        CHECK(utils::is_point(GeometryDetailedType::POINTM));
        CHECK(utils::is_point(GeometryDetailedType::POINTZM));
        CHECK(not utils::is_point(GeometryType::MULTIPOINT));
        CHECK(not utils::is_point(GeometryType::LINESTRING));
        CHECK(not utils::is_point(GeometryType::MULTILINESTRING));
        CHECK(not utils::is_point(GeometryType::POLYGON));
        CHECK(not utils::is_point(GeometryType::MULTIPOLYGON));
        CHECK(not utils::is_point(GeometryType::GEOMETRYCOLLECTION));
    }

    SECTION("is_multipoint()")
    {
        CHECK(utils::is_multipoint(GeometryType::MULTIPOINT));
        CHECK(utils::is_multipoint(GeometryDetailedType::MULTIPOINT));
        CHECK(utils::is_multipoint(GeometryDetailedType::MULTIPOINTZ));
        CHECK(utils::is_multipoint(GeometryDetailedType::MULTIPOINTM));
        CHECK(utils::is_multipoint(GeometryDetailedType::MULTIPOINTZM));
        CHECK(not utils::is_multipoint(GeometryType::POINT));
        CHECK(not utils::is_multipoint(GeometryType::LINESTRING));
        CHECK(not utils::is_multipoint(GeometryType::MULTILINESTRING));
        CHECK(not utils::is_multipoint(GeometryType::POLYGON));
        CHECK(not utils::is_multipoint(GeometryType::MULTIPOLYGON));
        CHECK(not utils::is_multipoint(GeometryType::GEOMETRYCOLLECTION));
    }

    SECTION("is_linestring()")
    {
        CHECK(utils::is_linestring(GeometryType::LINESTRING));
        CHECK(utils::is_linestring(GeometryDetailedType::LINESTRING));
        CHECK(utils::is_linestring(GeometryDetailedType::LINESTRINGZ));
        CHECK(utils::is_linestring(GeometryDetailedType::LINESTRINGM));
        CHECK(utils::is_linestring(GeometryDetailedType::LINESTRINGZM));
        CHECK(not utils::is_linestring(GeometryType::POINT));
        CHECK(not utils::is_linestring(GeometryType::MULTIPOINT));
        CHECK(not utils::is_linestring(GeometryType::MULTILINESTRING));
        CHECK(not utils::is_linestring(GeometryType::POLYGON));
        CHECK(not utils::is_linestring(GeometryType::MULTIPOLYGON));
        CHECK(not utils::is_linestring(GeometryType::GEOMETRYCOLLECTION));
    }

    SECTION("is_multilinestring()")
    {
        CHECK(utils::is_multilinestring(GeometryType::MULTILINESTRING));
        CHECK(utils::is_multilinestring(GeometryDetailedType::MULTILINESTRING));
        CHECK(utils::is_multilinestring(GeometryDetailedType::MULTILINESTRINGZ));
        CHECK(utils::is_multilinestring(GeometryDetailedType::MULTILINESTRINGM));
        CHECK(utils::is_multilinestring(GeometryDetailedType::MULTILINESTRINGZM));
        CHECK(not utils::is_multilinestring(GeometryType::POINT));
        CHECK(not utils::is_multilinestring(GeometryType::MULTIPOINT));
        CHECK(not utils::is_multilinestring(GeometryType::LINESTRING));
        CHECK(not utils::is_multilinestring(GeometryType::POLYGON));
        CHECK(not utils::is_multilinestring(GeometryType::MULTIPOLYGON));
        CHECK(not utils::is_multilinestring(GeometryType::GEOMETRYCOLLECTION));
    }

    SECTION("is_polygon()")
    {
        CHECK(utils::is_polygon(GeometryType::POLYGON));
        CHECK(utils::is_polygon(GeometryDetailedType::POLYGON));
        CHECK(utils::is_polygon(GeometryDetailedType::POLYGONZ));
        CHECK(utils::is_polygon(GeometryDetailedType::POLYGONM));
        CHECK(utils::is_polygon(GeometryDetailedType::POLYGONZM));
        CHECK(not utils::is_polygon(GeometryType::POINT));
        CHECK(not utils::is_polygon(GeometryType::MULTIPOINT));
        CHECK(not utils::is_polygon(GeometryType::LINESTRING));
        CHECK(not utils::is_polygon(GeometryType::MULTILINESTRING));
        CHECK(not utils::is_polygon(GeometryType::MULTIPOLYGON));
        CHECK(not utils::is_polygon(GeometryType::GEOMETRYCOLLECTION));
    }

    SECTION("is_multipolygon()")
    {
        CHECK(utils::is_multipolygon(GeometryType::MULTIPOLYGON));
        CHECK(utils::is_multipolygon(GeometryDetailedType::MULTIPOLYGON));
        CHECK(utils::is_multipolygon(GeometryDetailedType::MULTIPOLYGONZ));
        CHECK(utils::is_multipolygon(GeometryDetailedType::MULTIPOLYGONM));
        CHECK(utils::is_multipolygon(GeometryDetailedType::MULTIPOLYGONZM));
        CHECK(not utils::is_multipolygon(GeometryType::POINT));
        CHECK(not utils::is_multipolygon(GeometryType::MULTIPOINT));
        CHECK(not utils::is_multipolygon(GeometryType::LINESTRING));
        CHECK(not utils::is_multipolygon(GeometryType::MULTILINESTRING));
        CHECK(not utils::is_multipolygon(GeometryType::POLYGON));
        CHECK(not utils::is_multipolygon(GeometryType::GEOMETRYCOLLECTION));
    }
}