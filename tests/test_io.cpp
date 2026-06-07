#include <ciso646>
#include <catch2/catch_amalgamated.hpp>
#include <simo/io/io.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("IO facade")
{
    SECTION("WKT facade delegates to generic geometry and members")
    {
        auto geom = from_wkt("POINT (1 2)");
        REQUIRE(geom.is_point());
        CHECK(to_wkt(geom) == "POINT (1 2)");
        CHECK(to_wkt(Point(3, 4)) == "POINT (3 4)");
    }

    SECTION("GeoJSON facade delegates to generic geometry and members")
    {
        auto geom = from_geojson(R"({"type":"Point","coordinates":[1,2]})");
        REQUIRE(geom.is_point());
        CHECK(to_geojson(geom) == R"({"type":"Point","coordinates":[1,2]})");
        CHECK(to_geojson(Point(3, 4)) == R"({"type":"Point","coordinates":[3,4]})");
    }
}

TEST_CASE("Generic GeoJSON parsing")
{
    SECTION("parses every raw geometry type")
    {
        CHECK(from_geojson(R"({"type":"Point","coordinates":[1,2]})").is_point());
        CHECK(from_geojson(R"({"type":"LineString","coordinates":[[0,0],[1,1]]})").is_linestring());
        CHECK(from_geojson(R"({"type":"Polygon","coordinates":[[[0,0],[1,0],[1,1],[0,0]]]})").is_polygon());
        CHECK(from_geojson(R"({"type":"MultiPoint","coordinates":[[0,0],[1,1]]})").is_multipoint());
        CHECK(from_geojson(R"({"type":"MultiLineString","coordinates":[[[0,0],[1,1]]]})").is_multilinestring());
        CHECK(from_geojson(R"({"type":"MultiPolygon","coordinates":[[[[0,0],[1,0],[1,1],[0,0]]]]})").is_multipolygon());
    }

    SECTION("infers Z and ZM dimensions")
    {
        auto point_z = from_geojson(R"({"type":"Point","coordinates":[1,2,3]})");
        REQUIRE(point_z.is_point_z());
        CHECK(point_z.wkt() == "POINT Z (1 2 3)");

        auto point_zm = from_geojson(R"({"type":"Point","coordinates":[1,2,3,4]})");
        REQUIRE(point_zm.is_point_zm());
        CHECK(point_zm.wkt() == "POINT ZM (1 2 3 4)");
    }

    SECTION("empty point defaults to XY")
    {
        auto geom = from_geojson(R"({"type":"Point","coordinates":[]})");
        REQUIRE(geom.is_point());
        REQUIRE(geom.get_point() != nullptr);
        CHECK(geom.get_point()->empty());
    }

    SECTION("parses nested GeometryCollection")
    {
        auto geom = from_geojson(R"({
            "type":"GeometryCollection",
            "geometries":[
                {"type":"Point","coordinates":[1,2]},
                {"type":"GeometryCollection","geometries":[{"type":"Point","coordinates":[3,4,5]}]}
            ]
        })");

        REQUIRE(geom.is_geometrycollection());
        auto collection = geom.get_geometrycollection();
        REQUIRE(collection != nullptr);
        REQUIRE(collection->size() == 2);
        CHECK((*collection)[0].is_point());
        REQUIRE((*collection)[1].is_geometrycollection());
        auto nested = (*collection)[1].get_geometrycollection();
        REQUIRE(nested != nullptr);
        REQUIRE(nested->size() == 1);
        CHECK((*nested)[0].is_point_z());
        CHECK(geom.json() == R"({"type":"GeometryCollection","geometries":[{"type":"Point","coordinates":[1,2]},{"type":"GeometryCollection","geometries":[{"type":"Point","coordinates":[3,4,5]}]}]})");
    }

    SECTION("rejects mixed dimensions and unknown types")
    {
        CHECK_THROWS_AS(from_geojson(R"({"type":"LineString","coordinates":[[0,0],[1,1,1]]})"), exceptions::parse_error);
        CHECK_THROWS_AS(from_geojson(R"({"type":"Triangle","coordinates":[[0,0],[1,1],[2,2]]})"), exceptions::parse_error);
    }

    SECTION("keeps type-specific mismatch behavior")
    {
        CHECK_THROWS_AS(Point::from_json(R"({"type":"LineString","coordinates":[[0,0],[1,1]]})"), exceptions::parse_error);
    }
}

TEST_CASE("GeoJSON Feature helpers")
{
    SECTION("parses a Feature geometry and ignores properties")
    {
        auto geom = from_geojson_feature(R"({
            "type":"Feature",
            "properties":{"name":"ignored"},
            "geometry":{"type":"Point","coordinates":[1,2]}
        })");
        REQUIRE(geom.is_point());
        CHECK(geom.wkt() == "POINT (1 2)");
    }

    SECTION("parses FeatureCollection in feature order")
    {
        auto geometries = from_geojson_feature_collection(R"({
            "type":"FeatureCollection",
            "features":[
                {"type":"Feature","properties":{},"geometry":{"type":"Point","coordinates":[1,2]}},
                {"type":"Feature","properties":{},"geometry":{"type":"LineString","coordinates":[[0,0],[1,1]]}}
            ]
        })");
        REQUIRE(geometries.size() == 2);
        CHECK(geometries[0].wkt() == "POINT (1 2)");
        CHECK(geometries[1].wkt() == "LINESTRING(0 0,1 1)");
    }

    SECTION("rejects missing and null Feature geometry")
    {
        CHECK_THROWS_AS(from_geojson_feature(R"({"type":"Feature","properties":{}})"), exceptions::parse_error);
        CHECK_THROWS_AS(from_geojson_feature(R"({"type":"Feature","properties":{},"geometry":null})"), exceptions::parse_error);
    }

    SECTION("raw geometry parser does not accept Feature as geometry")
    {
        CHECK_THROWS_AS(from_geojson(R"({"type":"Feature","geometry":{"type":"Point","coordinates":[1,2]},"properties":{}})"), exceptions::parse_error);
    }
}
