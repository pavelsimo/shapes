#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Point tests")
{
    SECTION("geometry type")
    {
        Point p;
        CHECK(p.type() == GeometryType::POINT);
        CHECK(p.type_str() == "Point");
    }

    SECTION("empty constructor")
    {
        Point p;
        CHECK(p.x == 0);
        CHECK(p.y == 0);
        CHECK(p.dimension == DimensionType::XY);
    }

    SECTION("2d point constructor - initializer list")
    {
        Point p = {1, 2};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 0);
        CHECK(p.dimension == DimensionType::XY);
    }

    SECTION("3d point constructor - initializer list")
    {
        Point p = {1, 2, 3};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
        CHECK(p.dimension == DimensionType::XYZ);
        CHECK(p.detailed_type() == GeometryDetailedType::POINTZ);
    }

    SECTION("2d point - from json")
    {
        auto p = Point::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0]})");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.dimension == DimensionType::XY);
        CHECK(p.type_str() == "Point");
    }

    SECTION("3d point - from json")
    {
        auto p = Point::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0, 3.0]})");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.z == 3.0);
        CHECK(p.dimension == DimensionType::XYZ);
        CHECK(p.detailed_type() == GeometryDetailedType::POINTZ);
        CHECK(p.type_str() == "Point");
    }

    SECTION("2d point - to json")
    {
        auto p = Point{1, 2};
        p.precision = 1;
        CHECK(p.json() == R"({"type":"Point","coordinates":[1.0,2.0]})");
    }

    SECTION("3d point - to json")
    {
        auto p = Point{1, 2, 3};
        p.precision = 1;
        CHECK(p.json() == R"({"type":"Point","coordinates":[1.0,2.0,3.0]})");
    }

    SECTION("2d point - to wkt")
    {
        Point p     = {1.0, 2.0};
        p.precision = 1;
        CHECK(p.wkt() == "POINT(1.0 2.0)");
    }

    SECTION("3d point - to wkt")
    {
        Point p     = {1.0, 2.0, 3.0};
        p.precision = 1;
        CHECK(p.wkt() == "POINTZ(1.0 2.0 3.0)");
    }

    SECTION("4d point - to wkt")
    {
        Point p     = {1.0, 2.0, 3.0, 4.0};
        p.precision = 1;
        CHECK(p.wkt() == "POINTZM(1.0 2.0 3.0 4.0)");
    }

    SECTION("2d point - from wkt")
    {
        auto p = Point::from_wkt("POINT(1 2)");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
    }

    SECTION("3d point - from wkt")
    {
        auto p = Point::from_wkt("POINTZ(1 2 3)");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.z == 3.0);
    }

    SECTION("4d point - from wkt")
    {
        auto p = Point::from_wkt("POINTZM(1 2 3 4)");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.z == 3.0);
        CHECK(p.m == 4.0);
        CHECK(p.detailed_type() == GeometryDetailedType::POINTZM);
    }

    SECTION("2d point index operator")
    {
        Point p = {1, 2};
        CHECK(p[0] == 1.0);
        CHECK(p[1] == 2.0);
        CHECK(p.size() == 2);
        CHECK_THROWS(p[2]);
        size_t n = 0;
        for (size_t i = 0; i < p.size(); ++i)
        {
            n++;
        }
        CHECK(n == p.size());
    }

    SECTION("3d point index operator")
    {
        Point p = {1, 2, 3};
        CHECK(p[0] == 1.0);
        CHECK(p[1] == 2.0);
        CHECK(p[2] == 3.0);
        CHECK(p.size() == 3);
        CHECK_THROWS(p[3]);
        size_t n = 0;
        for (size_t i = 0; i < p.size(); ++i)
        {
            n++;
        }
        CHECK(n == p.size());
    }

    SECTION("2d point - to tuples")
    {
        Point p = {1.0, 2.0};
        double x, y;
        std::tie(x, y) = p.xy()[0];
        CHECK(x == 1.0);
        CHECK(y == 2.0);
    }

    SECTION("3d point - to tuples")
    {
        Point p = {1.0, 2.0, 3.0};
        double x, y, z;
        std::tie(x, y, z) = p.xyz()[0];
        CHECK(x == 1.0);
        CHECK(y == 2.0);
        CHECK(z == 3.0);
    }
}
