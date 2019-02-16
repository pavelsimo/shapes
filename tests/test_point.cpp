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
        auto p      = Point{1, 2};
        p.precision = 1;
        CHECK(p.json() == R"({"type":"Point","coordinates":[1.0,2.0]})");
    }

    SECTION("3d point - to json")
    {
        auto p      = Point{1, 2, 3};
        p.precision = 1;
        CHECK(p.json() == R"({"type":"Point","coordinates":[1.0,2.0,3.0]})");
    }

    SECTION("2d point - to wkt")
    {
        Point p     = {1.0, 2.0};
        p.precision = 1;
        CHECK(p.wkt() == "POINT (1.0 2.0)");
    }

    SECTION("3d point - to wkt")
    {
        Point p     = {1.0, 2.0, 3.0};
        p.precision = 1;
        CHECK(p.wkt() == "POINT Z (1.0 2.0 3.0)");
    }

    SECTION("4d point - to wkt")
    {
        Point p     = {1.0, 2.0, 3.0, 4.0};
        p.precision = 1;
        CHECK(p.wkt() == "POINT ZM (1.0 2.0 3.0 4.0)");
    }

    SECTION("point - from wkt")
    {
        struct test_case
        {
            std::string wkt;
            double x = 0;
            double y = 0;
            double z = 0;
            double m = 0;
            GeometryDetailedType detailed_type;
            DimensionType dimension;
        };

        std::vector<test_case> test_cases = {
            {"POINT(1 2)", 1.0, 2.0, 0, 0, GeometryDetailedType::POINT, DimensionType::XY},
            {"POINT (1 2)", 1.0, 2.0, 0, 0, GeometryDetailedType::POINT, DimensionType::XY},
            {"POINTM(1 2 4)", 1.0, 2.0, 0, 4.0, GeometryDetailedType::POINTM, DimensionType::XYM},
            {"POINT M(1 2 4)", 1.0, 2.0, 0, 4.0, GeometryDetailedType::POINTM, DimensionType::XYM},
            {"POINT M (1 2 4)", 1.0, 2.0, 0, 4.0, GeometryDetailedType::POINTM, DimensionType::XYM},
            {"POINTZ(1 2 3)", 1.0, 2.0, 3.0, 0, GeometryDetailedType::POINTZ, DimensionType::XYZ},
            {"POINT Z(1 2 3)", 1.0, 2.0, 3.0, 0, GeometryDetailedType::POINTZ, DimensionType::XYZ},
            {"POINT Z (1 2 3)", 1.0, 2.0, 3.0, 0, GeometryDetailedType::POINTZ, DimensionType::XYZ},
            {"POINTZM(1 2 3 4)", 1.0, 2.0, 3.0, 4.0, GeometryDetailedType::POINTZM, DimensionType::XYZM},
            {"POINT ZM(1 2 3 4)", 1.0, 2.0, 3.0, 4.0, GeometryDetailedType::POINTZM, DimensionType::XYZM},
            {"POINT ZM (1 2 3 4)", 1.0, 2.0, 3.0, 4.0, GeometryDetailedType::POINTZM, DimensionType::XYZM},
        };

        for (auto test_case : test_cases)
        {
            CAPTURE(test_case.wkt);
            CAPTURE(test_case.x);
            CAPTURE(test_case.y);
            CAPTURE(test_case.z);
            CAPTURE(test_case.m);

            auto p = Point::from_wkt(test_case.wkt);
            CHECK(p.x == test_case.x);
            CHECK(p.y == test_case.y);
            CHECK(p.z == test_case.z);
            CHECK(p.m == test_case.m);
            CHECK(p.detailed_type() == test_case.detailed_type);
            CHECK(p.dimension == test_case.dimension);
        }
    }

    SECTION("invalid point wkt")
    {
        CHECK_THROWS(Point::from_wkt("POINT"));
        CHECK_THROWS(Point::from_wkt("POINT ()"));
        CHECK_THROWS(Point::from_wkt("POINT (1)"));
        CHECK_THROWS(Point::from_wkt("POINT (1 2 3)"));
        CHECK_THROWS(Point::from_wkt("POINT (1 2 3 4)"));
        CHECK_THROWS(Point::from_wkt("POINT Z"));
        CHECK_THROWS(Point::from_wkt("POINT Z ()"));
        CHECK_THROWS(Point::from_wkt("POINT Z (1)"));
        CHECK_THROWS(Point::from_wkt("POINT Z (1 2)"));
        CHECK_THROWS(Point::from_wkt("POINT Z (1 2 3 4)"));
        CHECK_THROWS(Point::from_wkt("POINT M"));
        CHECK_THROWS(Point::from_wkt("POINT M ()"));
        CHECK_THROWS(Point::from_wkt("POINT M (1)"));
        CHECK_THROWS(Point::from_wkt("POINT M (1 2)"));
        CHECK_THROWS(Point::from_wkt("POINT M (1 2 3 4)"));
        CHECK_THROWS(Point::from_wkt("POINT ZM"));
        CHECK_THROWS(Point::from_wkt("POINT ZM ()"));
        CHECK_THROWS(Point::from_wkt("POINT ZM (1)"));
        CHECK_THROWS(Point::from_wkt("POINT ZM (1 2)"));
        CHECK_THROWS(Point::from_wkt("POINT ZM (1 2 3)"));
        CHECK_THROWS(Point::from_wkt("POINT ZM (1 2 3 4 5)"));
    }

    SECTION("3d point - from wkt")
    {
        auto p = Point::from_wkt("POINT Z (1 2 3)");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.z == 3.0);
        CHECK(p.detailed_type() == GeometryDetailedType::POINTZ);
    }

    SECTION("4d point - from wkt")
    {
        auto p = Point::from_wkt("POINT ZM (1 2 3 4)");
        CHECK(p.x == 1.0);
        CHECK(p.y == 2.0);
        CHECK(p.z == 3.0);
        CHECK(p.m == 4.0);
        CHECK(p.detailed_type() == GeometryDetailedType::POINTZM);
    }

    SECTION("empty point - from wkt")
    {
        auto p = Point::from_wkt("POINT EMPTY");
        CHECK(p.x == 0);
        CHECK(p.y == 0);
        CHECK(p.z == 0);
        CHECK(p.m == 0);
        CHECK(p.detailed_type() == GeometryDetailedType::POINT);
        CHECK(p.dimension == DimensionType::XY);
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
