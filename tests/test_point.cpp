#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Point tests") {
    SECTION("geometry type") {
        Point p;
        CHECK(p.geom_type() == GeometryType::POINT);
        CHECK(p.geom_type_str() == "POINT");
    }

    SECTION("empty constructor") {
        Point p;
        CHECK(p.x == 0);
        CHECK(p.y == 0);
        CHECK(p.dimension() == 2);
    }

    SECTION("2d point constructor - initializer list") {
        Point p = {1, 2};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 0);
        CHECK(p.dimension() == 2);
    }

    SECTION("3d point constructor - initializer list") {
        Point p = {1, 2, 3};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
        CHECK(p.dimension() == 3);
    }

    SECTION("2d point - from json") {
        auto p = Point::from_json("{\"type\": \"Point\", \"coordinates\": [1.0, 2.0]}");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.dimension() == 2);
        CHECK(p.geom_type_str() == "POINT");
    }

    SECTION("3d point - from json") {
        auto p = Point::from_json("{\"type\": \"Point\", \"coordinates\": [1.0, 2.0, 3.0]}");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.z == 3.0);
        CHECK(p.dimension() == 3);
        CHECK(p.geom_type_str() == "POINT");
    }

    SECTION("2d point - to json") {
        auto p = Point{1, 2};
        CHECK(p.to_json() == "{\"coordinates\":[1.0,2.0],\"type\":\"Point\"}");
    }

    SECTION("3d point - to json") {
        auto p = Point{1, 2, 3};
        CHECK(p.to_json() == "{\"coordinates\":[1.0,2.0,3.0],\"type\":\"Point\"}");
    }
}
