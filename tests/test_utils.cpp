#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Utils")
{
    SECTION("get_dim()")
    {
        CHECK(utils::get_dim(geometry_type::POINT) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::POINTZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::POINTM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::POINTZM) == dimension_type::XYZM);
        CHECK(utils::get_dim(geometry_type::MULTIPOINT) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::MULTIPOINTZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::MULTIPOINTM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::MULTIPOINTZM) == dimension_type::XYZM);
        CHECK(utils::get_dim(geometry_type::LINESTRING) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::LINESTRINGZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::LINESTRINGM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::LINESTRINGZM) == dimension_type::XYZM);
        CHECK(utils::get_dim(geometry_type::MULTILINESTRING) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::MULTILINESTRINGZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::MULTILINESTRINGM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::MULTILINESTRINGZM) == dimension_type::XYZM);
        CHECK(utils::get_dim(geometry_type::POLYGON) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::POLYGONZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::POLYGONM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::POLYGONZM) == dimension_type::XYZM);
        CHECK(utils::get_dim(geometry_type::MULTIPOLYGON) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::MULTIPOLYGONZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::MULTIPOLYGONM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::MULTIPOLYGONZM) == dimension_type::XYZM);
        CHECK(utils::get_dim(geometry_type::GEOMETRYCOLLECTION) == dimension_type::XY);
        CHECK(utils::get_dim(geometry_type::GEOMETRYCOLLECTIONZ) == dimension_type::XYZ);
        CHECK(utils::get_dim(geometry_type::GEOMETRYCOLLECTIONM) == dimension_type::XYM);
        CHECK(utils::get_dim(geometry_type::GEOMETRYCOLLECTIONZM) == dimension_type::XYZM);
    }

    SECTION("get_ndim() - dimension type")
    {
        CHECK(utils::get_ndim(dimension_type::XY) == 2);
        CHECK(utils::get_ndim(dimension_type::XYZ) == 3);
        CHECK(utils::get_ndim(dimension_type::XYM) == 3);
        CHECK(utils::get_ndim(dimension_type::XYZM) == 4);
    }

    SECTION("get_ndim() - geometry_detailed_type")
    {
        CHECK(utils::get_ndim(geometry_type::POINT) == 2);
        CHECK(utils::get_ndim(geometry_type::POINTZ) == 3);
        CHECK(utils::get_ndim(geometry_type::POINTM) == 3);
        CHECK(utils::get_ndim(geometry_type::POINTZM) == 4);
        CHECK(utils::get_ndim(geometry_type::MULTIPOINT) == 2);
        CHECK(utils::get_ndim(geometry_type::MULTIPOINTZ) == 3);
        CHECK(utils::get_ndim(geometry_type::MULTIPOINTM) == 3);
        CHECK(utils::get_ndim(geometry_type::MULTIPOINTZM) == 4);
        CHECK(utils::get_ndim(geometry_type::LINESTRING) == 2);
        CHECK(utils::get_ndim(geometry_type::LINESTRINGZ) == 3);
        CHECK(utils::get_ndim(geometry_type::LINESTRINGM) == 3);
        CHECK(utils::get_ndim(geometry_type::LINESTRINGZM) == 4);
        CHECK(utils::get_ndim(geometry_type::MULTILINESTRING) == 2);
        CHECK(utils::get_ndim(geometry_type::MULTILINESTRINGZ) == 3);
        CHECK(utils::get_ndim(geometry_type::MULTILINESTRINGM) == 3);
        CHECK(utils::get_ndim(geometry_type::MULTILINESTRINGZM) == 4);
        CHECK(utils::get_ndim(geometry_type::POLYGON) == 2);
        CHECK(utils::get_ndim(geometry_type::POLYGONZ) == 3);
        CHECK(utils::get_ndim(geometry_type::POLYGONM) == 3);
        CHECK(utils::get_ndim(geometry_type::POLYGONZM) == 4);
        CHECK(utils::get_ndim(geometry_type::MULTIPOLYGON) == 2);
        CHECK(utils::get_ndim(geometry_type::MULTIPOLYGONZ) == 3);
        CHECK(utils::get_ndim(geometry_type::MULTIPOLYGONM) == 3);
        CHECK(utils::get_ndim(geometry_type::MULTIPOLYGONZM) == 4);
        CHECK(utils::get_ndim(geometry_type::GEOMETRYCOLLECTION) == 2);
        CHECK(utils::get_ndim(geometry_type::GEOMETRYCOLLECTIONZ) == 3);
        CHECK(utils::get_ndim(geometry_type::GEOMETRYCOLLECTIONM) == 3);
        CHECK(utils::get_ndim(geometry_type::GEOMETRYCOLLECTIONZM) == 4);
    }

    SECTION("get_geom_type()")
    {
        CHECK(utils::get_geom_type(geometry_type::POINT) == geometry_type::POINT);
        CHECK(utils::get_geom_type(geometry_type::POINTZ) == geometry_type::POINT);
        CHECK(utils::get_geom_type(geometry_type::POINTM) == geometry_type::POINT);
        CHECK(utils::get_geom_type(geometry_type::POINTZM) == geometry_type::POINT);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOINT) == geometry_type::MULTIPOINT);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOINTZ) == geometry_type::MULTIPOINT);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOINTM) == geometry_type::MULTIPOINT);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOINTZM) == geometry_type::MULTIPOINT);
        CHECK(utils::get_geom_type(geometry_type::LINESTRING) == geometry_type::LINESTRING);
        CHECK(utils::get_geom_type(geometry_type::LINESTRINGZ) == geometry_type::LINESTRING);
        CHECK(utils::get_geom_type(geometry_type::LINESTRINGM) == geometry_type::LINESTRING);
        CHECK(utils::get_geom_type(geometry_type::LINESTRINGZM) == geometry_type::LINESTRING);
        CHECK(utils::get_geom_type(geometry_type::MULTILINESTRING) == geometry_type::MULTILINESTRING);
        CHECK(utils::get_geom_type(geometry_type::MULTILINESTRINGZ) == geometry_type::MULTILINESTRING);
        CHECK(utils::get_geom_type(geometry_type::MULTILINESTRINGM) == geometry_type::MULTILINESTRING);
        CHECK(utils::get_geom_type(geometry_type::MULTILINESTRINGZM) == geometry_type::MULTILINESTRING);
        CHECK(utils::get_geom_type(geometry_type::POLYGON) == geometry_type::POLYGON);
        CHECK(utils::get_geom_type(geometry_type::POLYGONZ) == geometry_type::POLYGON);
        CHECK(utils::get_geom_type(geometry_type::POLYGONM) == geometry_type::POLYGON);
        CHECK(utils::get_geom_type(geometry_type::POLYGONZM) == geometry_type::POLYGON);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOLYGON) == geometry_type::MULTIPOLYGON);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOLYGONZ) == geometry_type::MULTIPOLYGON);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOLYGONM) == geometry_type::MULTIPOLYGON);
        CHECK(utils::get_geom_type(geometry_type::MULTIPOLYGONZM) == geometry_type::MULTIPOLYGON);
        CHECK(utils::get_geom_type(geometry_type::GEOMETRYCOLLECTION) == geometry_type::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(geometry_type::GEOMETRYCOLLECTIONZ) == geometry_type::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(geometry_type::GEOMETRYCOLLECTIONM) == geometry_type::GEOMETRYCOLLECTION);
        CHECK(utils::get_geom_type(geometry_type::GEOMETRYCOLLECTIONZM) == geometry_type::GEOMETRYCOLLECTION);
    }

    SECTION("is_point()")
    {
        CHECK(utils::is_point(geometry_type::POINT));
        CHECK(utils::is_point(geometry_type::POINT));
        CHECK(utils::is_point(geometry_type::POINTZ));
        CHECK(utils::is_point(geometry_type::POINTM));
        CHECK(utils::is_point(geometry_type::POINTZM));
        CHECK(not utils::is_point(geometry_type::MULTIPOINT));
        CHECK(not utils::is_point(geometry_type::LINESTRING));
        CHECK(not utils::is_point(geometry_type::MULTILINESTRING));
        CHECK(not utils::is_point(geometry_type::POLYGON));
        CHECK(not utils::is_point(geometry_type::MULTIPOLYGON));
        CHECK(not utils::is_point(geometry_type::GEOMETRYCOLLECTION));
    }

    SECTION("is_multipoint()")
    {
        CHECK(utils::is_multipoint(geometry_type::MULTIPOINT));
        CHECK(utils::is_multipoint(geometry_type::MULTIPOINT));
        CHECK(utils::is_multipoint(geometry_type::MULTIPOINTZ));
        CHECK(utils::is_multipoint(geometry_type::MULTIPOINTM));
        CHECK(utils::is_multipoint(geometry_type::MULTIPOINTZM));
        CHECK(not utils::is_multipoint(geometry_type::POINT));
        CHECK(not utils::is_multipoint(geometry_type::LINESTRING));
        CHECK(not utils::is_multipoint(geometry_type::MULTILINESTRING));
        CHECK(not utils::is_multipoint(geometry_type::POLYGON));
        CHECK(not utils::is_multipoint(geometry_type::MULTIPOLYGON));
        CHECK(not utils::is_multipoint(geometry_type::GEOMETRYCOLLECTION));
    }

    SECTION("is_linestring()")
    {
        CHECK(utils::is_linestring(geometry_type::LINESTRING));
        CHECK(utils::is_linestring(geometry_type::LINESTRING));
        CHECK(utils::is_linestring(geometry_type::LINESTRINGZ));
        CHECK(utils::is_linestring(geometry_type::LINESTRINGM));
        CHECK(utils::is_linestring(geometry_type::LINESTRINGZM));
        CHECK(not utils::is_linestring(geometry_type::POINT));
        CHECK(not utils::is_linestring(geometry_type::MULTIPOINT));
        CHECK(not utils::is_linestring(geometry_type::MULTILINESTRING));
        CHECK(not utils::is_linestring(geometry_type::POLYGON));
        CHECK(not utils::is_linestring(geometry_type::MULTIPOLYGON));
        CHECK(not utils::is_linestring(geometry_type::GEOMETRYCOLLECTION));
    }

    SECTION("is_multilinestring()")
    {
        CHECK(utils::is_multilinestring(geometry_type::MULTILINESTRING));
        CHECK(utils::is_multilinestring(geometry_type::MULTILINESTRING));
        CHECK(utils::is_multilinestring(geometry_type::MULTILINESTRINGZ));
        CHECK(utils::is_multilinestring(geometry_type::MULTILINESTRINGM));
        CHECK(utils::is_multilinestring(geometry_type::MULTILINESTRINGZM));
        CHECK(not utils::is_multilinestring(geometry_type::POINT));
        CHECK(not utils::is_multilinestring(geometry_type::MULTIPOINT));
        CHECK(not utils::is_multilinestring(geometry_type::LINESTRING));
        CHECK(not utils::is_multilinestring(geometry_type::POLYGON));
        CHECK(not utils::is_multilinestring(geometry_type::MULTIPOLYGON));
        CHECK(not utils::is_multilinestring(geometry_type::GEOMETRYCOLLECTION));
    }

    SECTION("is_polygon()")
    {
        CHECK(utils::is_polygon(geometry_type::POLYGON));
        CHECK(utils::is_polygon(geometry_type::POLYGON));
        CHECK(utils::is_polygon(geometry_type::POLYGONZ));
        CHECK(utils::is_polygon(geometry_type::POLYGONM));
        CHECK(utils::is_polygon(geometry_type::POLYGONZM));
        CHECK(not utils::is_polygon(geometry_type::POINT));
        CHECK(not utils::is_polygon(geometry_type::MULTIPOINT));
        CHECK(not utils::is_polygon(geometry_type::LINESTRING));
        CHECK(not utils::is_polygon(geometry_type::MULTILINESTRING));
        CHECK(not utils::is_polygon(geometry_type::MULTIPOLYGON));
        CHECK(not utils::is_polygon(geometry_type::GEOMETRYCOLLECTION));
    }

    SECTION("is_multipolygon()")
    {
        CHECK(utils::is_multipolygon(geometry_type::MULTIPOLYGON));
        CHECK(utils::is_multipolygon(geometry_type::MULTIPOLYGON));
        CHECK(utils::is_multipolygon(geometry_type::MULTIPOLYGONZ));
        CHECK(utils::is_multipolygon(geometry_type::MULTIPOLYGONM));
        CHECK(utils::is_multipolygon(geometry_type::MULTIPOLYGONZM));
        CHECK(not utils::is_multipolygon(geometry_type::POINT));
        CHECK(not utils::is_multipolygon(geometry_type::MULTIPOINT));
        CHECK(not utils::is_multipolygon(geometry_type::LINESTRING));
        CHECK(not utils::is_multipolygon(geometry_type::MULTILINESTRING));
        CHECK(not utils::is_multipolygon(geometry_type::POLYGON));
        CHECK(not utils::is_multipolygon(geometry_type::GEOMETRYCOLLECTION));
    }
}