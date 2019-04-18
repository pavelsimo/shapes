#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Utils")
{
    SECTION("get_dim()")
    {
        CHECK(utils::get_dim(GeometryType::POINT) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::POINTZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::POINTM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::POINTZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryType::MULTIPOINT) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::MULTIPOINTZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::MULTIPOINTM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::MULTIPOINTZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryType::LINESTRING) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::LINESTRINGZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::LINESTRINGM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::LINESTRINGZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryType::MULTILINESTRING) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::MULTILINESTRINGZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::MULTILINESTRINGM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::MULTILINESTRINGZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryType::POLYGON) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::POLYGONZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::POLYGONM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::POLYGONZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryType::MULTIPOLYGON) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::MULTIPOLYGONZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::MULTIPOLYGONM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::MULTIPOLYGONZM) == DimensionType::XYZM);
        CHECK(utils::get_dim(GeometryType::GEOMETRYCOLLECTION) == DimensionType::XY);
        CHECK(utils::get_dim(GeometryType::GEOMETRYCOLLECTIONZ) == DimensionType::XYZ);
        CHECK(utils::get_dim(GeometryType::GEOMETRYCOLLECTIONM) == DimensionType::XYM);
        CHECK(utils::get_dim(GeometryType::GEOMETRYCOLLECTIONZM) == DimensionType::XYZM);
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
        CHECK(utils::get_ndim(GeometryType::POINT) == 2);
        CHECK(utils::get_ndim(GeometryType::POINTZ) == 3);
        CHECK(utils::get_ndim(GeometryType::POINTM) == 3);
        CHECK(utils::get_ndim(GeometryType::POINTZM) == 4);
        CHECK(utils::get_ndim(GeometryType::MULTIPOINT) == 2);
        CHECK(utils::get_ndim(GeometryType::MULTIPOINTZ) == 3);
        CHECK(utils::get_ndim(GeometryType::MULTIPOINTM) == 3);
        CHECK(utils::get_ndim(GeometryType::MULTIPOINTZM) == 4);
        CHECK(utils::get_ndim(GeometryType::LINESTRING) == 2);
        CHECK(utils::get_ndim(GeometryType::LINESTRINGZ) == 3);
        CHECK(utils::get_ndim(GeometryType::LINESTRINGM) == 3);
        CHECK(utils::get_ndim(GeometryType::LINESTRINGZM) == 4);
        CHECK(utils::get_ndim(GeometryType::MULTILINESTRING) == 2);
        CHECK(utils::get_ndim(GeometryType::MULTILINESTRINGZ) == 3);
        CHECK(utils::get_ndim(GeometryType::MULTILINESTRINGM) == 3);
        CHECK(utils::get_ndim(GeometryType::MULTILINESTRINGZM) == 4);
        CHECK(utils::get_ndim(GeometryType::POLYGON) == 2);
        CHECK(utils::get_ndim(GeometryType::POLYGONZ) == 3);
        CHECK(utils::get_ndim(GeometryType::POLYGONM) == 3);
        CHECK(utils::get_ndim(GeometryType::POLYGONZM) == 4);
        CHECK(utils::get_ndim(GeometryType::MULTIPOLYGON) == 2);
        CHECK(utils::get_ndim(GeometryType::MULTIPOLYGONZ) == 3);
        CHECK(utils::get_ndim(GeometryType::MULTIPOLYGONM) == 3);
        CHECK(utils::get_ndim(GeometryType::MULTIPOLYGONZM) == 4);
        CHECK(utils::get_ndim(GeometryType::GEOMETRYCOLLECTION) == 2);
        CHECK(utils::get_ndim(GeometryType::GEOMETRYCOLLECTIONZ) == 3);
        CHECK(utils::get_ndim(GeometryType::GEOMETRYCOLLECTIONM) == 3);
        CHECK(utils::get_ndim(GeometryType::GEOMETRYCOLLECTIONZM) == 4);
    }

    SECTION("get_geom_type_dim()")
    {
        CHECK(utils::get_geom_type_dim(GeometryType::POINT, DimensionType::XY) == GeometryType::POINT);
        CHECK(utils::get_geom_type_dim(GeometryType::POINT, DimensionType::XYZ) == GeometryType::POINTZ);
        CHECK(utils::get_geom_type_dim(GeometryType::POINT, DimensionType::XYM) == GeometryType::POINTM);
        CHECK(utils::get_geom_type_dim(GeometryType::POINT, DimensionType::XYZM) == GeometryType::POINTZM);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOINT, DimensionType::XY) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOINT, DimensionType::XYZ) == GeometryType::MULTIPOINTZ);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOINT, DimensionType::XYM) == GeometryType::MULTIPOINTM);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOINT, DimensionType::XYZM) == GeometryType::MULTIPOINTZM);
        CHECK(utils::get_geom_type_dim(GeometryType::LINESTRING, DimensionType::XY) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type_dim(GeometryType::LINESTRING, DimensionType::XYZ) == GeometryType::LINESTRINGZ);
        CHECK(utils::get_geom_type_dim(GeometryType::LINESTRING, DimensionType::XYM) == GeometryType::LINESTRINGM);
        CHECK(utils::get_geom_type_dim(GeometryType::LINESTRING, DimensionType::XYZM) == GeometryType::LINESTRINGZM);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTILINESTRING, DimensionType::XY) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTILINESTRING, DimensionType::XYZ) == GeometryType::MULTILINESTRINGZ);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTILINESTRING, DimensionType::XYM) == GeometryType::MULTILINESTRINGM);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTILINESTRING, DimensionType::XYZM) == GeometryType::MULTILINESTRINGZM);
        CHECK(utils::get_geom_type_dim(GeometryType::POLYGON, DimensionType::XY) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type_dim(GeometryType::POLYGON, DimensionType::XYZ) == GeometryType::POLYGONZ);
        CHECK(utils::get_geom_type_dim(GeometryType::POLYGON, DimensionType::XYM) == GeometryType::POLYGONM);
        CHECK(utils::get_geom_type_dim(GeometryType::POLYGON, DimensionType::XYZM) == GeometryType::POLYGONZM);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOLYGON, DimensionType::XY) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOLYGON, DimensionType::XYZ) == GeometryType::MULTIPOLYGONZ);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOLYGON, DimensionType::XYM) == GeometryType::MULTIPOLYGONM);
        CHECK(utils::get_geom_type_dim(GeometryType::MULTIPOLYGON, DimensionType::XYZM) == GeometryType::MULTIPOLYGONZM);
        CHECK(utils::get_geom_type_dim(GeometryType::GEOMETRYCOLLECTION, DimensionType::XY) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type_dim(GeometryType::GEOMETRYCOLLECTION, DimensionType::XYZ) == GeometryType::GEOMETRYCOLLECTIONZ);
        CHECK(utils::get_geom_type_dim(GeometryType::GEOMETRYCOLLECTION, DimensionType::XYM) == GeometryType::GEOMETRYCOLLECTIONM);
        CHECK(utils::get_geom_type_dim(GeometryType::GEOMETRYCOLLECTION, DimensionType::XYZM) == GeometryType::GEOMETRYCOLLECTIONZM);
    }

    SECTION("get_geom_type()")
    {
        CHECK(utils::get_geom_type(GeometryType::POINT) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryType::POINTZ) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryType::POINTM) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryType::POINTZM) == GeometryType::POINT);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOINT) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOINTZ) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOINTM) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOINTZM) == GeometryType::MULTIPOINT);
        CHECK(utils::get_geom_type(GeometryType::LINESTRING) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryType::LINESTRINGZ) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryType::LINESTRINGM) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryType::LINESTRINGZM) == GeometryType::LINESTRING);
        CHECK(utils::get_geom_type(GeometryType::MULTILINESTRING) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryType::MULTILINESTRINGZ) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryType::MULTILINESTRINGM) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryType::MULTILINESTRINGZM) == GeometryType::MULTILINESTRING);
        CHECK(utils::get_geom_type(GeometryType::POLYGON) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryType::POLYGONZ) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryType::POLYGONM) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryType::POLYGONZM) == GeometryType::POLYGON);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOLYGON) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOLYGONZ) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOLYGONM) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryType::MULTIPOLYGONZM) == GeometryType::MULTIPOLYGON);
        CHECK(utils::get_geom_type(GeometryType::GEOMETRYCOLLECTION) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(GeometryType::GEOMETRYCOLLECTIONZ) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(GeometryType::GEOMETRYCOLLECTIONM) == GeometryType::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(GeometryType::GEOMETRYCOLLECTIONZM) == GeometryType::GEOMETRYCOLLECTION);
    }

    SECTION("is_point()")
    {
        CHECK(utils::is_point(GeometryType::POINT));
        CHECK(utils::is_point(GeometryType::POINT));
        CHECK(utils::is_point(GeometryType::POINTZ));
        CHECK(utils::is_point(GeometryType::POINTM));
        CHECK(utils::is_point(GeometryType::POINTZM));
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
        CHECK(utils::is_multipoint(GeometryType::MULTIPOINT));
        CHECK(utils::is_multipoint(GeometryType::MULTIPOINTZ));
        CHECK(utils::is_multipoint(GeometryType::MULTIPOINTM));
        CHECK(utils::is_multipoint(GeometryType::MULTIPOINTZM));
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
        CHECK(utils::is_linestring(GeometryType::LINESTRING));
        CHECK(utils::is_linestring(GeometryType::LINESTRINGZ));
        CHECK(utils::is_linestring(GeometryType::LINESTRINGM));
        CHECK(utils::is_linestring(GeometryType::LINESTRINGZM));
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
        CHECK(utils::is_multilinestring(GeometryType::MULTILINESTRING));
        CHECK(utils::is_multilinestring(GeometryType::MULTILINESTRINGZ));
        CHECK(utils::is_multilinestring(GeometryType::MULTILINESTRINGM));
        CHECK(utils::is_multilinestring(GeometryType::MULTILINESTRINGZM));
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
        CHECK(utils::is_polygon(GeometryType::POLYGON));
        CHECK(utils::is_polygon(GeometryType::POLYGONZ));
        CHECK(utils::is_polygon(GeometryType::POLYGONM));
        CHECK(utils::is_polygon(GeometryType::POLYGONZM));
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
        CHECK(utils::is_multipolygon(GeometryType::MULTIPOLYGON));
        CHECK(utils::is_multipolygon(GeometryType::MULTIPOLYGONZ));
        CHECK(utils::is_multipolygon(GeometryType::MULTIPOLYGONM));
        CHECK(utils::is_multipolygon(GeometryType::MULTIPOLYGONZM));
        CHECK(not utils::is_multipolygon(GeometryType::POINT));
        CHECK(not utils::is_multipolygon(GeometryType::MULTIPOINT));
        CHECK(not utils::is_multipolygon(GeometryType::LINESTRING));
        CHECK(not utils::is_multipolygon(GeometryType::MULTILINESTRING));
        CHECK(not utils::is_multipolygon(GeometryType::POLYGON));
        CHECK(not utils::is_multipolygon(GeometryType::GEOMETRYCOLLECTION));
    }
}