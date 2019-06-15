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
            CHECK(p.dim() == dimension_type::XY);
            CHECK(p.geom_type() == geometry_type::POINT);
            CHECK(p.tagged_text() == "Point");
        }

        SECTION("xy - constructor")
        {
            Point p(1, 2);
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.dim() == dimension_type::XY);
            CHECK(p.geom_type() == geometry_type::POINT);
            CHECK(p.tagged_text() == "Point");
        }

        SECTION("xyz - constructor")
        {
            PointZ p(1, 2, 3);
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 3);
            CHECK(p.dim() == dimension_type::XYZ);
            CHECK(p.geom_type() == geometry_type::POINTZ);
            CHECK(p.tagged_text() == "Point Z");
        }

        SECTION("xym - constructor")
        {
            // not supported
        }

        SECTION("xyzm - constructor")
        {
            PointZM p(1, 2, 3, 4);
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 3);
            CHECK(p.m == 4);
            CHECK(p.dim() == dimension_type::XYZM);
            CHECK(p.geom_type() == geometry_type::POINTZM);
            CHECK(p.tagged_text() == "Point ZM");
        }

        SECTION("xy - initializer list")
        {
            auto p = Point{1, 2};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.dim() == dimension_type::XY);
            CHECK(p.geom_type() == geometry_type::POINT);
            CHECK(p.tagged_text() == "Point");
        }

        SECTION("xyz - initializer list")
        {
            auto p = PointZ{1, 2, 3};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 3);
            CHECK(p.dim() == dimension_type::XYZ);
            CHECK(p.geom_type() == geometry_type::POINTZ);
            CHECK(p.tagged_text() == "Point Z");
        }

        SECTION("xym - initializer list")
        {
            auto p = PointM{1, 2, 3};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.m == 3);
            CHECK(p.dim() == dimension_type::XYM);
            CHECK(p.geom_type() == geometry_type::POINTM);
            CHECK(p.tagged_text() == "Point M");
        }

        SECTION("xyzm - initializer list")
        {
            auto p = PointZM{1, 2, 3, 4};
            CHECK(p.x == 1);
            CHECK(p.y == 2);
            CHECK(p.z == 3);
            CHECK(p.m == 4);
            CHECK(p.dim() == dimension_type::XYZM);
            CHECK(p.geom_type() == geometry_type::POINTZM);
            CHECK(p.tagged_text() == "Point ZM");
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
                CHECK(p.dim() == dimension_type::XY);
                CHECK(p.geom_type() == geometry_type::POINT);
                CHECK(p.tagged_text() == "Point");
            }

            SECTION("xyz - from json")
            {
                auto p = PointZ::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0, 3.0]})");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.dim() == dimension_type::XYZ);
                CHECK(p.geom_type() == geometry_type::POINTZ);
                CHECK(p.tagged_text() == "Point Z");
            }

            SECTION("xym - from json")
            {
                auto p = PointM::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0, 3.0]})");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.m == 3.0);
                CHECK(p.dim() == dimension_type::XYM);
                CHECK(p.geom_type() == geometry_type::POINTM);
                CHECK(p.tagged_text() == "Point M");
            }

            SECTION("xyzm - from json")
            {
                auto p = PointZM::from_json(R"({"type": "Point", "coordinates": [1.0, 2.0, 3.0, 4.0]})");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.m == 4.0);
                CHECK(p.dim() == dimension_type::XYZM);
                CHECK(p.geom_type() == geometry_type::POINTZM);
                CHECK(p.tagged_text() == "Point ZM");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - from wkt")
            {
                auto p = Point::from_wkt("POINT (1 2)");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.dim() == dimension_type::XY);
                CHECK(p.geom_type() == geometry_type::POINT);
                CHECK(p.tagged_text() == "Point");
            }

            SECTION("xyz - from wkt")
            {
                auto p = PointZ::from_wkt("POINT Z (1 2 3)");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.dim() == dimension_type::XYZ);
                CHECK(p.geom_type() == geometry_type::POINTZ);
                CHECK(p.tagged_text() == "Point Z");
            }

            SECTION("xyzm - from wkt")
            {
                auto p = PointZM::from_wkt("POINT ZM (1 2 3 4)");
                CHECK(p.x == 1.0);
                CHECK(p.y == 2.0);
                CHECK(p.z == 3.0);
                CHECK(p.m == 4.0);
                CHECK(p.dim() == dimension_type::XYZM);
                CHECK(p.geom_type() == geometry_type::POINTZM);
                CHECK(p.tagged_text() == "Point ZM");
            }

            SECTION("empty - from wkt")
            {
                SECTION("empty - xy")
                {
                    auto p = Point::from_wkt("POINT EMPTY");
                    CHECK(p.x == 0);
                    CHECK(p.y == 0);
                    CHECK(p.geom_type() == geometry_type::POINT);
                    CHECK(p.dim() == dimension_type::XY);
                }

                SECTION("empty - xyz")
                {
                    auto p = PointZ::from_wkt("POINT Z EMPTY");
                    CHECK(p.x == 0);
                    CHECK(p.y == 0);
                    CHECK(p.z == 0);
                    CHECK(p.geom_type() == geometry_type::POINTZ);
                    CHECK(p.dim() == dimension_type::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto p = PointM::from_wkt("POINT M EMPTY");
                    CHECK(p.x == 0);
                    CHECK(p.y == 0);
                    CHECK(p.m == 0);
                    CHECK(p.geom_type() == geometry_type::POINTM);
                    CHECK(p.dim() == dimension_type::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto p = PointZM::from_wkt("POINT ZM EMPTY");
                    CHECK(p.x == 0);
                    CHECK(p.y == 0);
                    CHECK(p.z == 0);
                    CHECK(p.m == 0);
                    CHECK(p.geom_type() == geometry_type::POINTZM);
                    CHECK(p.dim() == dimension_type::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                // omit spaces
                CHECK_NOTHROW(Point::from_wkt("   POINT (1 2)  "));
                CHECK_NOTHROW(Point::from_wkt("   POINT (1          2)  "));
                CHECK_NOTHROW(Point::from_wkt("   POINT (    1          2    )  "));
                CHECK_NOTHROW(PointZ::from_wkt("   POINT Z (    1          2    3)  "));
                CHECK_NOTHROW(PointZM::from_wkt("   POINT     ZM     (    1          2    5       9)  "));
                CHECK_NOTHROW(PointZM::from_wkt("   POINTZM     (    1          2    5     2)  "));

                // wkt is case insensitive
                CHECK_NOTHROW(Point::from_wkt("Point(1 2)"));
                CHECK_NOTHROW(PointZ::from_wkt("PointZ(1 2 3)"));
                CHECK_NOTHROW(PointM::from_wkt("PointM(1 2 3)"));
                CHECK_NOTHROW(PointZM::from_wkt("PointZM(1 2 3 4)"));
                CHECK_NOTHROW(Point::from_wkt("point(1 2)"));
                CHECK_NOTHROW(PointZ::from_wkt("pointz(1 2 3)"));
                CHECK_NOTHROW(PointM::from_wkt("pointm(1 2 3)"));
                CHECK_NOTHROW(PointZM::from_wkt("pointzm(1 2 3 4)"));
                CHECK_NOTHROW(Point::from_wkt("Point Empty"));
                CHECK_NOTHROW(PointZ::from_wkt("Point Z Empty"));
                CHECK_NOTHROW(PointM::from_wkt("Point M Empty"));
                CHECK_NOTHROW(PointZM::from_wkt("Point ZM Empty"));
                CHECK_NOTHROW(Point::from_wkt("point empty"));
                CHECK_NOTHROW(PointZ::from_wkt("point z empty"));
                CHECK_NOTHROW(PointM::from_wkt("point m empty"));
                CHECK_NOTHROW(PointZM::from_wkt("point zm empty"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(Point::from_wkt("POINT"));
                CHECK_THROWS(Point::from_wkt("POINT ()"));
                CHECK_THROWS(Point::from_wkt("POINT (1)"));
                CHECK_THROWS(Point::from_wkt("POINT (1 2 3)"));
                CHECK_THROWS(Point::from_wkt("POINT (1 2 3 4)"));
                CHECK_THROWS(PointZ::from_wkt("POINT Z"));
                CHECK_THROWS(PointZ::from_wkt("POINT Z ()"));
                CHECK_THROWS(PointZ::from_wkt("POINT Z (1)"));
                CHECK_THROWS(PointZ::from_wkt("POINT Z (1 2)"));
                CHECK_THROWS(PointZ::from_wkt("POINT Z (1 2 3 4)"));
                CHECK_THROWS(PointM::from_wkt("POINT M"));
                CHECK_THROWS(PointM::from_wkt("POINT M ()"));
                CHECK_THROWS(PointM::from_wkt("POINT M (1)"));
                CHECK_THROWS(PointM::from_wkt("POINT M (1 2)"));
                CHECK_THROWS(PointM::from_wkt("POINT M (1 2 3 4)"));
                CHECK_THROWS(PointZM::from_wkt("POINT ZM"));
                CHECK_THROWS(PointZM::from_wkt("POINT ZM ()"));
                CHECK_THROWS(PointZM::from_wkt("POINT ZM (1)"));
                CHECK_THROWS(PointZM::from_wkt("POINT ZM (1 2)"));
                CHECK_THROWS(PointZM::from_wkt("POINT ZM (1 2 3)"));
                CHECK_THROWS(PointZM::from_wkt("POINT ZM (1 2 3 4 5)"));
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                auto p = Point{1, 2};
                CHECK(p.json() == R"({"type":"Point","coordinates":[1,2]})");
            }

            SECTION("xyz - to json")
            {
                auto p = PointZ{1, 2, 3};
                CHECK(p.json() == R"({"type":"Point","coordinates":[1,2,3]})");
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
                Point p = {1, 2};
                CHECK(p.wkt() == "POINT (1 2)");
            }

            SECTION("xyz - to wkt")
            {
                PointZ p = {1, 2, 3};
                CHECK(p.wkt() == "POINT Z (1 2 3)");
            }

            SECTION("xym - to wkt")
            {
                PointM p = {1, 2, 3};
                CHECK(p.wkt() == "POINT M (1 2 3)");
            }

            SECTION("xyzm - to wkt")
            {
                PointZM p = {1, 2, 3, 4};
                CHECK(p.wkt() == "POINT ZM (1 2 3 4)");
            }
        }
    }

    SECTION("operators")
    {
        SECTION("equal to - operator")
        {
            SECTION("xy - equal to")
            {
                Point p1 = {1.0, 2.0};
                Point p2 = {1.0, 2.0};
                CHECK(p1 == p2);
            }

            SECTION("xyz - equal to")
            {
                PointZ p1 = {1.0, 2.0, 3.0};
                PointZ p2 = {1.0, 2.0, 3.0};
                CHECK(p1 == p2);
            }

            SECTION("xym - equal to")
            {
                PointM p1 = {1, 2, 3};
                PointM p2 = {1, 2, 3};
                CHECK(p1 == p2);
            }

            SECTION("xyzm - equal to")
            {
                PointZM p1 = {1.0, 2.0, 3.0, 4.0};
                PointZM p2 = {1.0, 2.0, 3.0, 4.0};
                CHECK(p1 == p2);
            }
        }

        SECTION("not equal to - operator")
        {
            SECTION("xy - not equal to")
            {
                Point p1 = {1.0, 2.0};
                Point p2 = {2.0, 3.0};
                CHECK(p1 != p2);
            }

            SECTION("xyz - not equal to")
            {
                PointZ p1 = {1.0, 2.0, 7.0};
                PointZ p2 = {2.0, 3.0, 7.0};
                CHECK(p1 != p2);
            }

            SECTION("xym - not equal to")
            {
                PointM p1 = {1.0, 2.0, 7.0};
                PointM p2 = {2.0, 3.0, 7.0};
                CHECK(p1 != p2);
            }

            SECTION("xyzm - not equal to")
            {
                PointZM p1 = {1.0, 2.0, 3.0, 4.0};
                PointZM p2 = {2.0, 3.0, 4.0, 5.0};
                CHECK(p1 != p2);
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
                size_t n = 0;
                for (size_t i = 0; i < p.size(); ++i)
                {
                    n++;
                }
                CHECK(n == p.size());
            }

            SECTION("xyz - index operator")
            {
                PointZ p = {1, 2, 3};
                CHECK(p[0] == 1.0);
                CHECK(p[1] == 2.0);
                CHECK(p[2] == 3.0);
                CHECK(p.size() == 3);
                size_t n = 0;
                for (size_t i = 0; i < p.size(); ++i)
                {
                    n++;
                }
                CHECK(n == p.size());
            }

            SECTION("xym - index operator")
            {
                PointM p = {1, 2, 3};
                CHECK(p[0] == 1.0);
                CHECK(p[1] == 2.0);
                CHECK(p[2] == 3.0);
                CHECK(p.size() == 3);
                size_t n = 0;
                for (size_t i = 0; i < p.size(); ++i)
                {
                    n++;
                }
                CHECK(n == p.size());
            }

            SECTION("xyzm - index operator")
            {
                PointZM p = {1, 2, 3, 4};
                CHECK(p[0] == 1.0);
                CHECK(p[1] == 2.0);
                CHECK(p[2] == 3.0);
                CHECK(p[3] == 4.0);
                CHECK(p.size() == 4);
                size_t n = 0;
                for (size_t i = 0; i < p.size(); ++i)
                {
                    n++;
                }
                CHECK(n == p.size());
            }
        }
    }

    SECTION("sizeof")
    {
        CHECK(sizeof(point_t<double>) == 2 * sizeof(double));
        CHECK(sizeof(point_t<float>) == 2 * sizeof(float));
        CHECK(sizeof(point_t<int>) == 2 * sizeof(int));
        CHECK(sizeof(point_t<char>) == 2 * sizeof(char));
        CHECK(sizeof(point_z_t<double>) == 3 * sizeof(double));
        CHECK(sizeof(point_z_t<float>) == 3 * sizeof(float));
        CHECK(sizeof(point_z_t<int>) == 3 * sizeof(int));
        CHECK(sizeof(point_z_t<char>) == 3 * sizeof(char));
        CHECK(sizeof(point_m_t<double>) == 3 * sizeof(double));
        CHECK(sizeof(point_m_t<float>) == 3 * sizeof(float));
        CHECK(sizeof(point_m_t<int>) == 3 * sizeof(int));
        CHECK(sizeof(point_m_t<char>) == 3 * sizeof(char));
        CHECK(sizeof(point_zm_t<double>) == 4 * sizeof(double));
        CHECK(sizeof(point_zm_t<float>) == 4 * sizeof(float));
        CHECK(sizeof(point_zm_t<int>) == 4 * sizeof(int));
        CHECK(sizeof(point_zm_t<char>) == 4 * sizeof(char));
    }
}
