#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;


TEST_CASE("Point")
{
    SECTION("constructors")
    {
        SECTION("empty")
        {
            Point p;
            CHECK(p.x == 0);
            CHECK(p.y == 0);
            CHECK(p.dim == DimensionType::XY);
            CHECK(p.type() == GeometryType::POINT);
            CHECK(p.detailed_type() == GeometryDetailedType::POINT);
            CHECK(p.type_str() == "Point");
        }

        SECTION("xy - initializer list")
        {
            Point p = {1, 2};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 0);
            CHECK(p.dim == DimensionType::XY);
            CHECK(p.type() == GeometryType::POINT);
            CHECK(p.detailed_type() == GeometryDetailedType::POINT);
            CHECK(p.type_str() == "Point");
        }

        SECTION("xyz - initializer list")
        {
            Point p = {1, 2, 3};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 3);
            CHECK(p.dim == DimensionType::XYZ);
            CHECK(p.type() == GeometryType::POINT);
            CHECK(p.detailed_type() == GeometryDetailedType::POINTZ);
            CHECK(p.type_str() == "Point");
        }

        SECTION("xym - initializer list")
        {
            // not supported
        }

        SECTION("xyzm - initializer list")
        {
            Point p = {1, 2, 3, 4};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 3);
            CHECK(p.m == 4);
            CHECK(p.dim == DimensionType::XYZM);
            CHECK(p.type() == GeometryType::POINT);
            CHECK(p.detailed_type() == GeometryDetailedType::POINTZM);
            CHECK(p.type_str() == "Point");
        }

        SECTION("throws - initializer list")
        {
            CHECK_THROWS(Point{1, 2, 3, 4, 5});
            CHECK_THROWS(Point{1});
        }
    }

    SECTION("from_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - from json")
            {
                auto p = Point::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0]})");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.dim == DimensionType::XY);
                CHECK(p.type() == GeometryType::POINT);
                CHECK(p.detailed_type() == GeometryDetailedType::POINT);
                CHECK(p.type_str() == "Point");
            }

            SECTION("xyz - from json")
            {
                auto p = Point::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0, 3.0]})");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.dim == DimensionType::XYZ);
                CHECK(p.type() == GeometryType::POINT);
                CHECK(p.detailed_type() == GeometryDetailedType::POINTZ);
                CHECK(p.type_str() == "Point");
            }

            SECTION("xym - from json")
            {
                /// @todo (pavel) add test
            }

            SECTION("xyzm - from json")
            {
                /// @todo (pavel) add test
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - from wkt")
            {
                /// @todo (pavel) add test
            }

            SECTION("xyz - from wkt")
            {
                auto p = Point::from_wkt("POINT Z (1 2 3)");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.dim == DimensionType::XYZ);
                CHECK(p.type() == GeometryType::POINT);
                CHECK(p.detailed_type() == GeometryDetailedType::POINTZ);
                CHECK(p.type_str() == "Point");
            }

            SECTION("xyzm - from wkt")
            {
                auto p = Point::from_wkt("POINT ZM (1 2 3 4)");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.m == 4.0);
                CHECK(p.dim == DimensionType::XYZM);
                CHECK(p.type() == GeometryType::POINT);
                CHECK(p.detailed_type() == GeometryDetailedType::POINTZM);
                CHECK(p.type_str() == "Point");
            }

            SECTION("empty - from wkt")
            {
                auto p = Point::from_wkt("POINT EMPTY");
                CHECK(p.x == 0);
                CHECK(p.y == 0);
                CHECK(p.z == 0);
                CHECK(p.m == 0);
                CHECK(p.detailed_type() == GeometryDetailedType::POINT);
                CHECK(p.dim == DimensionType::XY);
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(Point::from_wkt("   POINT (1 2)  "));
                CHECK_NOTHROW(Point::from_wkt("   POINT (1          2)  "));
                CHECK_NOTHROW(Point::from_wkt("   POINT (    1          2    )  "));
                CHECK_NOTHROW(Point::from_wkt("   POINT Z (    1          2    3)  "));
                CHECK_NOTHROW(Point::from_wkt("   POINT     ZM     (    1          2    5       9)  "));
                CHECK_NOTHROW(Point::from_wkt("   POINTZM     (    1          2    5     2)  "));
            }

            SECTION("throws - from wkt")
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

            SECTION("misc - from wkt")
            {
                /// @todo (pavel) messy split this test
                struct test_case
                {
                    std::string wkt;
                    double x;
                    double y;
                    double z;
                    double m;
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
                    {"   POINT (1 2)  ", 1.0, 2.0, 0, 0, GeometryDetailedType::POINT, DimensionType::XY},
                    {"   POINT (1          2)  ", 1.0, 2.0, 0, 0, GeometryDetailedType::POINT, DimensionType::XY},
                    {"   POINT Z (    1          2    3)  ", 1.0, 2.0, 3.0, 0, GeometryDetailedType::POINTZ, DimensionType::XYZ},
                    {"   POINT     ZM     (    1          2    5       9)  ", 1.0, 2.0, 5.0, 9.0, GeometryDetailedType::POINTZM, DimensionType::XYZM},
                };

                for (const auto test_case : test_cases)
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
                    CHECK(p.dim == test_case.dimension);
                }
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                auto p      = Point{1, 2};
                p.precision = 1;
                CHECK(p.json() == R"({"type":"Point","coordinates":[1.0,2.0]})");
            }

            SECTION("xyz - to json")
            {
                auto p      = Point{1, 2, 3};
                p.precision = 1;
                CHECK(p.json() == R"({"type":"Point","coordinates":[1.0,2.0,3.0]})");
            }

            SECTION("xym - to json")
            {
                /// @todo (pavel) add test
            }

            SECTION("xyzm - to json")
            {
                /// @todo (pavel) add test
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                Point p     = {1.0, 2.0};
                p.precision = 1;
                CHECK(p.wkt() == "POINT (1.0 2.0)");
            }

            SECTION("xyz - to wkt")
            {
                Point p     = {1.0, 2.0, 3.0};
                p.precision = 1;
                CHECK(p.wkt() == "POINT Z (1.0 2.0 3.0)");
            }

            SECTION("xym - to wkt")
            {
                Point p     = Point::from_xym(1.0, 2.0, 3.0);
                p.precision = 1;
                CHECK(p.wkt() == "POINT M (1.0 2.0 3.0)");
            }

            SECTION("xyzm - to wkt")
            {
                Point p     = {1.0, 2.0, 3.0, 4.0};
                p.precision = 1;
                CHECK(p.wkt() == "POINT ZM (1.0 2.0 3.0 4.0)");
            }
        }
    }

    SECTION("index operator")
    {
        SECTION("xy - index operator")
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

        SECTION("xyz - index operator")
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

        SECTION("xym - index operator")
        {
            Point p = Point::from_xym(1, 2, 3);
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

        SECTION("xyzm - index operator")
        {
            Point p = {1, 2, 3, 4};
            CHECK(p[0] == 1.0);
            CHECK(p[1] == 2.0);
            CHECK(p[2] == 3.0);
            CHECK(p[3] == 4.0);
            CHECK(p.size() == 4);
            CHECK_THROWS(p[4]);
            size_t n = 0;
            for (size_t i = 0; i < p.size(); ++i)
            {
                n++;
            }
            CHECK(n == p.size());
        }
    }

    SECTION("coordinates tuples")
    {

        SECTION("xy - tuples")
        {
            Point p = {1.0, 2.0};
            double x, y;
            std::tie(x, y) = p.xy()[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
        }

        SECTION("xyz - tuples")
        {
            Point p = {1.0, 2.0, 3.0};
            double x, y, z;
            std::tie(x, y, z) = p.xyz()[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == 3.0);
        }

        SECTION("xym - tuples")
        {
            Point p = Point::from_xym(1.0, 2.0, 3.0);
            double x, y, m;
            std::tie(x, y, m) = p.xym()[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(m == 3.0);
        }

        SECTION("xyzm - tuples")
        {
            Point p = {1.0, 2.0, 3.0, 4.0};
            double x, y, z, m;
            std::tie(x, y, z, m) = p.xyzm()[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == 3.0);
            CHECK(m == 4.0);
        }
    }
}
