#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("LineString")
{
    SECTION("constructors")
    {
        SECTION("empty")
        {
            LineString ls;
            CHECK(ls.empty());
            CHECK(ls.dim() == dimension_type::XY);
            CHECK(ls.geom_type() == geometry_type::LINESTRING);
            CHECK(ls.tagged_text() == "LineString");
        }

        SECTION("xy - points vector")
        {
            std::vector<Point> points = {{1.0, 2.0}, {-3.0, -4.0}};
            auto ls                   = LineString(points.begin(), points.end());
            CHECK(not ls.empty());
            CHECK(ls.dim() == dimension_type::XY);
            CHECK(ls.geom_type() == geometry_type::LINESTRING);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - points vector")
        {
            std::vector<PointZ> points = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            auto ls                    = LineStringZ(points.begin(), points.end());
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XYZ);
            CHECK(ls.geom_type() == geometry_type::LINESTRINGZ);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.z == -6.0);
        }

        SECTION("xym - points vector")
        {
            std::vector<PointM> points = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            auto ls                    = LineStringM(points.begin(), points.end());
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XYM);
            CHECK(ls.geom_type() == geometry_type::LINESTRINGM);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.m == 3.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.m == -6.0);
        }

        SECTION("xyzm - points vector")
        {
            std::vector<PointZM> points = {{1.0, 2.0, 3.0, 1.5}, {-4.0, -5.0, -6.0, 1.5}};
            auto ls                     = LineStringZM(points.begin(), points.end());
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XYZM);
            CHECK(ls.geom_type() == geometry_type::LINESTRINGZM);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            CHECK(p1.m == 1.5);
            const auto& p2 = ls[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.z == -6.0);
            CHECK(p1.m == 1.5);
        }

        SECTION("xy - initializer list")
        {
            LineString ls = {{1.0, 2.0}, {-3.0, -4.0}};
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XY);
            CHECK(ls.geom_type() == geometry_type::LINESTRING);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - initializer list")
        {
            LineStringZ ls = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XYZ);
            CHECK(ls.geom_type() == geometry_type::LINESTRINGZ);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.z == -6.0);
        }

        SECTION("xym - initializer list")
        {
            LineStringM ls = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XYM);
            CHECK(ls.geom_type() == geometry_type::LINESTRINGM);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.m == 3.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.m == -6.0);
        }

        SECTION("xyzm - initializer list")
        {
            LineStringZM ls = {{1.0, 2.0, 3.0, 4.0}, {-5.0, -6.0, -7.0, -8.0}};
            CHECK(!ls.empty());
            CHECK(ls.dim() == dimension_type::XYZM);
            CHECK(ls.geom_type() == geometry_type::LINESTRINGZM);
            CHECK(ls.tagged_text() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            CHECK(p1.m == 4.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -5.0);
            CHECK(p2.y == -6.0);
            CHECK(p2.z == -7.0);
            CHECK(p2.m == -8.0);
        }
    }

    SECTION("from_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - from json")
            {
                std::string json = R"({"type":"LineString","coordinates":[[1.0,2.0],[3.0,4.0]]})";
                auto ls          = LineString::from_json(json);
                auto& p1         = ls[0];
                auto& p2         = ls[1];
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
            }

            SECTION("xyz - from json")
            {
                std::string json = R"({"type":"LineString","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})";
                auto ls          = LineStringZ::from_json(json);
                auto& p1         = ls[0];
                auto& p2         = ls[1];
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p2.x == 4.0);
                CHECK(p2.y == 5.0);
                CHECK(p2.z == 6.0);
            }

            SECTION("xym - from json")
            {
                std::string json = R"({"type":"LineString","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})";
                auto ls          = LineStringM::from_json(json);
                auto& p1         = ls[0];
                auto& p2         = ls[1];
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.m == 3.0);
                CHECK(p2.x == 4.0);
                CHECK(p2.y == 5.0);
                CHECK(p2.m == 6.0);
            }

            SECTION("xyzm - from json")
            {
                std::string json = R"({"type":"LineString","coordinates":[[1.0,2.0,3.0,-10.0],[4.0,5.0,6.0,-10.0]]})";
                auto ls          = LineStringZM::from_json(json);
                auto& p1         = ls[0];
                auto& p2         = ls[1];
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -10.0);
                CHECK(p2.x == 4.0);
                CHECK(p2.y == 5.0);
                CHECK(p2.z == 6.0);
                CHECK(p2.m == -10.0);
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - from wkt")
            {
                auto ls = LineString::from_wkt("LINESTRING(1.4 2.3, 3.2 4.1)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type() == geometry_type::LINESTRING);
                CHECK(ls.dim() == dimension_type::XY);
                const auto& p1 = ls[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                const auto& p2 = ls[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
            }

            SECTION("xyz - from wkt")
            {
                auto ls = LineStringZ::from_wkt("LINESTRINGZ(1.4 2.3 1, 3.2 4.1 2)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type() == geometry_type::LINESTRINGZ);
                CHECK(ls.dim() == dimension_type::XYZ);
                const auto& p1 = ls[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                CHECK(p1.z == 1);
                const auto& p2 = ls[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
                CHECK(p2.z == 2);
            }

            SECTION("xym - from wkt")
            {
                auto ls = LineStringM::from_wkt("LINESTRINGM(1.4 2.3 1, 3.2 4.1 2)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type() == geometry_type::LINESTRINGM);
                CHECK(ls.dim() == dimension_type::XYM);
                const auto& p1 = ls[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                CHECK(p1.m == 1);
                const auto& p2 = ls[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
                CHECK(p2.m == 2);
            }

            SECTION("xyzm - from wkt")
            {
                auto ls = LineStringZM::from_wkt("LINESTRINGZM(1.4 2.3 1 1, 3.2 4.1 2 2)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type() == geometry_type::LINESTRINGZM);
                CHECK(ls.dim() == dimension_type::XYZM);
                const auto& p1 = ls[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                CHECK(p1.z == 1);
                CHECK(p1.m == 1);
                const auto& p2 = ls[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
                CHECK(p2.z == 2);
                CHECK(p2.m == 2);
            }

            SECTION("empty - from wkt")
            {
                SECTION("empty - xy")
                {
                    auto ls = LineString::from_wkt("LINESTRING EMPTY");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type() == geometry_type::LINESTRING);
                    CHECK(ls.dim() == dimension_type::XY);
                }

                SECTION("empty - xyz")
                {
                    auto ls = LineStringZ::from_wkt("LINESTRING Z EMPTY");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type() == geometry_type::LINESTRINGZ);
                    CHECK(ls.dim() == dimension_type::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto ls = LineStringM::from_wkt("LINESTRING M EMPTY");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type() == geometry_type::LINESTRINGM);
                    CHECK(ls.dim() == dimension_type::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto ls = LineStringZM::from_wkt("LINESTRING ZM EMPTY");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type() == geometry_type::LINESTRINGZM);
                    CHECK(ls.dim() == dimension_type::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(LineStringZM::from_wkt("LineStringZM(1.4 2.3 1 1, 3.2 4.1 2 2)"));
                CHECK_NOTHROW(LineStringZM::from_wkt("lineStringzm(1.4 2.3 1 1, 3.2 4.1 2 2)"));
                CHECK_NOTHROW(LineStringZ::from_wkt("LineStringZ(1.4 2.3 1, 3.2 4.1 2)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString(1.4 2.3, 3.2 4.1)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString (10 40, 40 30, 20 20, 30 10)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString (10 40, 40 30, 20 20, 30 10)"));
                CHECK_NOTHROW(LineStringZ::from_wkt("LineString Z (10 40 -10, 40 30 -10, 20 20 -10, 30 10 -10)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString (10.00232 40.32412, 40.11241 30.429017, 20.43754 20.4323, 30.75534 10.234234)"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(LineStringZM::from_wkt("LineStringZM(1.4 2.3, 3.2 4.1)"));
                CHECK_THROWS(LineStringZM::from_wkt("LineStringZM(1.4 2.3 1, 3.2 4.1 2)"));
                CHECK_THROWS(LineStringZM::from_wkt("LineStringZM((1.4 2.3, 1.3)"));
                CHECK_THROWS(LineStringZM::from_wkt("LineStringZM((1.4 2.3, 1.3"));
                CHECK_THROWS(LineStringZM::from_wkt("LineStringZM(1.4.3 2.3.3 1.1.1 1.1.1, 3.2.1 4.1.1 2.2.1 2.2.3)"));
                /// @todo add more tests
            }
        }

        SECTION("polyline")
        {
            SECTION("xy - from polyline")
            {
                //                std::string polyline = "_p~iF~ps|U_ulLnnqC_mqNvxq`@";
                //                auto ls              = LineString::from_polyline(polyline);
                //                CHECK(ls.wkt() == "LINESTRING(-120.2 38.5,-120.95 40.7,-126.453 43.252)");
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                LineString ls = {{1.0, 2.0}, {3.0, 4.0}};
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1,2],[3,4]]})");
            }

            SECTION("xyz - to json")
            {
                LineStringZ ls = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1,2,3],[4,5,6]]})");
            }

            SECTION("xym - to json")
            {
                LineStringM ls = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1,2,3],[4,5,6]]})");
            }

            SECTION("xyzm - to json")
            {
                LineStringZM ls = {{1.0, 2.0, 3.0, -10.0}, {4.0, 5.0, 6.0, -10.0}};
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1,2,3,-10],[4,5,6,-10]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                LineString ls = {{1.0, 2.0}, {3.0, 4.0}};
                CHECK(ls.wkt() == R"(LINESTRING(1 2,3 4))");
            }

            SECTION("xyz - to wkt")
            {
                LineStringZ ls = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(ls.wkt() == R"(LINESTRINGZ(1 2 3,4 5 6))");
            }

            SECTION("xym - to wkt")
            {
                LineStringM ls = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
                CHECK(ls.wkt() == R"(LINESTRINGM(1 2 3,-4 -5 -6))");
            }

            SECTION("xyzm - to wkt")
            {
                LineStringZM ls = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                CHECK(ls.wkt() == R"(LINESTRINGZM(1 2 3 4,5 6 7 8))");
            }
        }

        SECTION("polyline")
        {
            SECTION("xy - to polyline")
            {
                LineString ls = {{-120.2, 38.5}, {-120.95, 40.7}, {-126.453, 43.252}};
                CHECK(ls.polyline() == "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
            }
        }
    }

    SECTION("operators")
    {
        SECTION("equal to - operator")
        {
            SECTION("xy - equal to")
            {
                auto ls1 = LineString{{1.0, 2.0}, {3.0, 4.0}};
                auto ls2 = LineString{{1.0, 2.0}, {3.0, 4.0}};
                CHECK(ls1 == ls2);
            }

            SECTION("xyz - equal to")
            {
                auto ls1 = LineStringZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                auto ls2 = LineStringZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(ls1 == ls2);
            }

            SECTION("xym - equal to")
            {
                auto ls1 = LineStringM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                auto ls2 = LineStringM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(ls1 == ls2);
            }

            SECTION("xyzm - equal to")
            {
                auto ls1 = LineStringZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto ls2 = LineStringZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                CHECK(ls1 == ls2);
            }
        }

        SECTION("not equal to - operator")
        {
            SECTION("xy - not equal to")
            {
                auto ls1 = LineString{{1.0, 2.0}, {4.0, 5.0}};
                auto ls2 = LineString{{1.0, 2.0}, {8.0, 10.0}};
                CHECK(ls1 != ls2);
            }

            SECTION("xyz - not equal to")
            {
                auto ls1 = LineStringZ{{1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}};
                auto ls2 = LineStringZ{{1.0, 2.0, 3.0}, {10.0, 20.0, 30.0}};
                CHECK(ls1 != ls2);
            }

            SECTION("xym - not equal to")
            {
                auto ls1 = LineStringZ{{1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}};
                auto ls2 = LineStringZ{{1.0, 2.0, 3.0}, {10.0, 20.0, 30.0}};
                CHECK(ls1 != ls2);
            }

            SECTION("xyzm - not equal to")
            {
                auto ls1 = LineStringZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto ls2 = LineStringZM{{1.0, 2.0, 3.0, 4.0}, {8.0, 7.0, 6.0, 5.0}};
                CHECK(ls1 != ls2);
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                auto ls  = LineString{{1.0, 2.0}, {3.0, 4.0}};
                auto& p1 = ls[0];
                CHECK(p1.geom_type() == geometry_type::POINT);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type() == geometry_type::POINT);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
            }

            SECTION("xyz - index operator")
            {
                auto ls  = LineStringZ{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
                auto& p1 = ls[0];
                CHECK(p1.geom_type() == geometry_type::POINTZ);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == -1.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type() == geometry_type::POINTZ);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == -2.0);

                auto& p3 = ls[2];
                CHECK(p3.geom_type() == geometry_type::POINTZ);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.z == -3.0);
            }

            SECTION("xym - index operator")
            {
                auto ls = LineStringM{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};

                auto& p1 = ls[0];
                CHECK(p1.geom_type() == geometry_type::POINTM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.m == -1.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type() == geometry_type::POINTM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.m == -2.0);

                auto& p3 = ls[2];
                CHECK(p3.geom_type() == geometry_type::POINTM);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.m == -3.0);
            }

            SECTION("xyzm - index operator")
            {
                auto ls  = LineStringZM{{1.0, 2.0, 3.0, -1.0}, {3.0, 4.0, 5.0, -2.0}, {5.0, 6.0, 7.0, -3.0}};
                auto& p1 = ls[0];
                CHECK(p1.geom_type() == geometry_type::POINTZM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -1.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type() == geometry_type::POINTZM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == 5.0);
                CHECK(p2.m == -2.0);

                auto& p3 = ls[2];
                CHECK(p3.geom_type() == geometry_type::POINTZM);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.z == 7.0);
                CHECK(p3.m == -3.0);
            }
        }
    }

    SECTION("coords")
    {
        SECTION("xy - coords")
        {
            auto ls     = LineString{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
            auto coords = ls.xy();
            CHECK(ls.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }

        SECTION("xyz - coords")
        {
            auto ls     = LineStringZ{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
            auto coords = ls.xy();
            CHECK(ls.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }

        SECTION("xym - coords")
        {
            auto ls     = LineStringM{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
            auto coords = ls.xy();
            CHECK(ls.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }

        SECTION("xyzm - coords")
        {
            auto ls     = LineStringZM{{1.0, 2.0, -1.0, -10.0}, {3.0, 4.0, -2.0, -20.0}, {5.0, 6.0, -3.0, -30.0}};
            auto coords = ls.xy();
            CHECK(ls.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }
    }

    SECTION("for each")
    {
        SECTION("xy - for each")
        {
            auto ls = LineString{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
            int n   = 0;
            for (const auto& p : ls)
            {
                CHECK(p.x != 0);
                CHECK(p.y != 0);
                ++n;
            }
            CHECK(n == 3);
        }

        SECTION("xyz - for each")
        {
            auto ls = LineStringZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
            int n   = 0;
            for (const auto& p : ls)
            {
                CHECK(p.x != 0);
                CHECK(p.y != 0);
                CHECK(p.z != 0);
                ++n;
            }
            CHECK(n == 3);
        }

        SECTION("xym - for each")
        {
            auto ls = LineStringM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
            int n   = 0;
            for (const auto& p : ls)
            {
                CHECK(p.x != 0);
                CHECK(p.y != 0);
                CHECK(p.m != 0);
                ++n;
            }
            CHECK(n == 3);
        }

        SECTION("xyzm - for each")
        {
            auto ls = LineStringZM{{1.0, 2.0, 3.0, -1.0}, {4.0, 5.0, 6.0, -2.0}, {7.0, 8.0, 9.0, -3.0}};
            int n   = 0;
            for (const auto& p : ls)
            {
                CHECK(p.x != 0);
                CHECK(p.y != 0);
                CHECK(p.z != 0);
                CHECK(p.m != 0);
                ++n;
            }
            CHECK(n == 3);
        }
    }

    SECTION("bounds")
    {
        auto ls = LineString{{1.0, 2.0}, {3.0, 4.0}};
        auto b  = ls.bounds();
        CHECK(b.maxx == 3.0);
        CHECK(b.maxy == 4.0);
        CHECK(b.minx == 1.0);
        CHECK(b.miny == 2.0);
    }
}
