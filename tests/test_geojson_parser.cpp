#include <catch/catch.hpp>
#include <simo/io/geojson_parser.hpp>
#include <sstream>

using namespace simo::shapes::io;

TEST_CASE("GeoJSON Parser - Basic Types")
{
    SECTION("parse null")
    {
        auto val = geojson_parser::parse("null");
        REQUIRE(val.is_null());
    }

    SECTION("parse string")
    {
        auto val = geojson_parser::parse("\"hello\"");
        REQUIRE(val.is_string());
        REQUIRE(val.as_string() == "hello");
    }

    SECTION("parse number - integer")
    {
        auto val = geojson_parser::parse("42");
        REQUIRE(val.is_number());
        REQUIRE(val.as_number() == 42.0);
    }

    SECTION("parse number - float")
    {
        auto val = geojson_parser::parse("3.14159");
        REQUIRE(val.is_number());
        REQUIRE(val.as_number() == Approx(3.14159));
    }

    SECTION("parse number - negative")
    {
        auto val = geojson_parser::parse("-123.456");
        REQUIRE(val.is_number());
        REQUIRE(val.as_number() == Approx(-123.456));
    }

    SECTION("parse number - scientific notation")
    {
        auto val = geojson_parser::parse("1.5e10");
        REQUIRE(val.is_number());
        REQUIRE(val.as_number() == Approx(1.5e10));
    }

    SECTION("parse array - empty")
    {
        auto val = geojson_parser::parse("[]");
        REQUIRE(val.is_array());
        REQUIRE(val.size() == 0);
        REQUIRE(val.empty());
    }

    SECTION("parse array - numbers")
    {
        auto val = geojson_parser::parse("[1, 2, 3, 4, 5]");
        REQUIRE(val.is_array());
        REQUIRE(val.size() == 5);
        REQUIRE(val[0].as_number() == 1.0);
        REQUIRE(val[4].as_number() == 5.0);
    }

    SECTION("parse array - mixed types")
    {
        auto val = geojson_parser::parse("[1, \"test\", null, 3.14]");
        REQUIRE(val.is_array());
        REQUIRE(val.size() == 4);
        REQUIRE(val[0].is_number());
        REQUIRE(val[1].is_string());
        REQUIRE(val[2].is_null());
        REQUIRE(val[3].is_number());
    }

    SECTION("parse object - empty")
    {
        auto val = geojson_parser::parse("{}");
        REQUIRE(val.is_object());
        REQUIRE(val.size() == 0);
        REQUIRE(val.empty());
    }

    SECTION("parse object - simple")
    {
        auto val = geojson_parser::parse(R"({"name": "test", "value": 42})");
        REQUIRE(val.is_object());
        REQUIRE(val.size() == 2);
        REQUIRE(val.at("name").as_string() == "test");
        REQUIRE(val.at("value").as_number() == 42.0);
    }

    SECTION("parse nested object")
    {
        auto val = geojson_parser::parse(R"({"outer": {"inner": "value"}})");
        REQUIRE(val.is_object());
        REQUIRE(val.at("outer").is_object());
        REQUIRE(val.at("outer").at("inner").as_string() == "value");
    }
}

TEST_CASE("GeoJSON Parser - String Escaping")
{
    SECTION("escaped quotes")
    {
        auto val = geojson_parser::parse(R"("hello \"world\"")");
        REQUIRE(val.as_string() == "hello \"world\"");
    }

    SECTION("escaped backslash")
    {
        auto val = geojson_parser::parse(R"("path\\to\\file")");
        REQUIRE(val.as_string() == "path\\to\\file");
    }

    SECTION("escaped newline")
    {
        auto val = geojson_parser::parse(R"("line1\nline2")");
        REQUIRE(val.as_string() == "line1\nline2");
    }

    SECTION("escaped tab")
    {
        auto val = geojson_parser::parse(R"("col1\tcol2")");
        REQUIRE(val.as_string() == "col1\tcol2");
    }
}

TEST_CASE("GeoJSON Parser - Coordinate Arrays")
{
    SECTION("2D coordinates")
    {
        auto val = geojson_parser::parse("[1.0, 2.0]");
        auto coords = val.as_double_array();
        REQUIRE(coords.size() == 2);
        REQUIRE(coords[0] == 1.0);
        REQUIRE(coords[1] == 2.0);
    }

    SECTION("3D coordinates")
    {
        auto val = geojson_parser::parse("[1.5, 2.5, 3.5]");
        auto coords = val.as_double_array();
        REQUIRE(coords.size() == 3);
        REQUIRE(coords[0] == Approx(1.5));
        REQUIRE(coords[1] == Approx(2.5));
        REQUIRE(coords[2] == Approx(3.5));
    }

    SECTION("nested coordinate arrays")
    {
        auto val = geojson_parser::parse("[[1, 2], [3, 4], [5, 6]]");
        REQUIRE(val.is_array());
        REQUIRE(val.size() == 3);
        auto first = val[0].as_double_array();
        REQUIRE(first.size() == 2);
        REQUIRE(first[0] == 1.0);
        REQUIRE(first[1] == 2.0);
    }
}

TEST_CASE("GeoJSON Parser - Point Geometry")
{
    SECTION("simple 2D point")
    {
        auto val = geojson_parser::parse(R"({"type": "Point", "coordinates": [1.0, 2.0]})");
        REQUIRE(val.is_object());
        REQUIRE(val.at("type").as_string() == "Point");
        auto coords = val.at("coordinates").as_double_array();
        REQUIRE(coords.size() == 2);
        REQUIRE(coords[0] == 1.0);
        REQUIRE(coords[1] == 2.0);
    }

    SECTION("3D point")
    {
        auto val = geojson_parser::parse(R"({"type": "Point", "coordinates": [1.0, 2.0, 3.0]})");
        auto coords = val.at("coordinates").as_double_array();
        REQUIRE(coords.size() == 3);
        REQUIRE(coords[2] == 3.0);
    }
}

TEST_CASE("GeoJSON Parser - LineString Geometry")
{
    SECTION("simple linestring")
    {
        auto val = geojson_parser::parse(R"({
            "type": "LineString",
            "coordinates": [[0, 0], [1, 1], [2, 0]]
        })");
        REQUIRE(val.at("type").as_string() == "LineString");
        const auto& coords = val.at("coordinates");
        REQUIRE(coords.is_array());
        REQUIRE(coords.size() == 3);
    }
}

TEST_CASE("GeoJSON Parser - Polygon Geometry")
{
    SECTION("simple polygon")
    {
        auto val = geojson_parser::parse(R"({
            "type": "Polygon",
            "coordinates": [
                [[0, 0], [4, 0], [4, 3], [0, 3], [0, 0]]
            ]
        })");
        REQUIRE(val.at("type").as_string() == "Polygon");
        const auto& rings = val.at("coordinates");
        REQUIRE(rings.is_array());
        REQUIRE(rings.size() == 1);  // One ring (exterior)
    }

    SECTION("polygon with hole")
    {
        auto val = geojson_parser::parse(R"({
            "type": "Polygon",
            "coordinates": [
                [[0, 0], [10, 0], [10, 10], [0, 10], [0, 0]],
                [[2, 2], [8, 2], [8, 8], [2, 8], [2, 2]]
            ]
        })");
        const auto& rings = val.at("coordinates");
        REQUIRE(rings.size() == 2);  // Exterior + one hole
    }
}

TEST_CASE("GeoJSON Parser - Whitespace Handling")
{
    SECTION("extra whitespace")
    {
        auto val = geojson_parser::parse("  {  \"key\"  :  \"value\"  }  ");
        REQUIRE(val.is_object());
        REQUIRE(val.at("key").as_string() == "value");
    }

    SECTION("no whitespace")
    {
        auto val = geojson_parser::parse(R"({"key":"value"})");
        REQUIRE(val.at("key").as_string() == "value");
    }
}

TEST_CASE("GeoJSON Parser - Error Handling")
{
    SECTION("empty string")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse(""), geojson_parse_error);
    }

    SECTION("invalid JSON - missing closing brace")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("{\"key\": \"value\""), geojson_parse_error);
    }

    SECTION("invalid JSON - missing closing bracket")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("[1, 2, 3"), geojson_parse_error);
    }

    SECTION("invalid JSON - trailing comma")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("[1, 2, 3,]"), geojson_parse_error);
    }

    SECTION("invalid JSON - missing colon")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("{\"key\" \"value\"}"), geojson_parse_error);
    }

    SECTION("invalid number")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("123."), geojson_parse_error);
    }

    SECTION("unterminated string")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("\"hello"), geojson_parse_error);
    }

    SECTION("unexpected character")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("@"), geojson_parse_error);
    }

    SECTION("extra characters after JSON")
    {
        REQUIRE_THROWS_AS(geojson_parser::parse("42 extra"), geojson_parse_error);
    }
}

TEST_CASE("GeoJSON Parser - Access Methods")
{
    SECTION("has_key")
    {
        auto val = geojson_parser::parse(R"({"key": "value"})");
        REQUIRE(val.has_key("key"));
        REQUIRE(!val.has_key("missing"));
    }

    SECTION("at() with missing key throws")
    {
        auto val = geojson_parser::parse(R"({"key": "value"})");
        REQUIRE_THROWS_AS(val.at("missing"), std::out_of_range);
    }

    SECTION("array index out of range")
    {
        auto val = geojson_parser::parse("[1, 2, 3]");
        REQUIRE_THROWS_AS(val[10], std::out_of_range);
    }

    SECTION("as_string on non-string throws")
    {
        auto val = geojson_parser::parse("42");
        REQUIRE_THROWS_AS(val.as_string(), geojson_parse_error);
    }

    SECTION("as_number on non-number throws")
    {
        auto val = geojson_parser::parse("\"text\"");
        REQUIRE_THROWS_AS(val.as_number(), geojson_parse_error);
    }

    SECTION("as_double_array with non-number elements")
    {
        auto val = geojson_parser::parse("[1, \"text\", 3]");
        REQUIRE_THROWS_AS(val.as_double_array(), geojson_parse_error);
    }
}

TEST_CASE("GeoJSON Parser - Real-World GeoJSON")
{
    SECTION("complete Point feature")
    {
        auto json = R"({
            "type": "Point",
            "coordinates": [100.0, 0.5]
        })";
        auto val = geojson_parser::parse(json);
        REQUIRE(val.at("type").as_string() == "Point");
        auto coords = val.at("coordinates").as_double_array();
        REQUIRE(coords[0] == 100.0);
        REQUIRE(coords[1] == 0.5);
    }

    SECTION("MultiPoint geometry")
    {
        auto json = R"({
            "type": "MultiPoint",
            "coordinates": [[100.0, 0.0], [101.0, 1.0]]
        })";
        auto val = geojson_parser::parse(json);
        REQUIRE(val.at("type").as_string() == "MultiPoint");
        const auto& coords = val.at("coordinates");
        REQUIRE(coords.size() == 2);
    }
}
