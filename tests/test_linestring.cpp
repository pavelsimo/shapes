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
            CHECK(ls.dim == DimensionType::XY);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_str() == "LineString");
        }

        SECTION("xy - points vector")
        {
            std::vector<Point> points;
            points.emplace_back(1.0, 2.0);
            points.emplace_back(-3.0, -4.0);
            LineString ls(points);
            CHECK(not ls.empty());
            CHECK(ls.dim == DimensionType::XY);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_str() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - points vector")
        {
            std::vector<Point> points;
            points.emplace_back(1.0, 2.0, 3.0);
            points.emplace_back(-4.0, -5.0, -6.0);
            LineString ls(points);
            CHECK(!ls.empty());
            CHECK(ls.dim == DimensionType::XYZ);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZ);
            CHECK(ls.geom_type_str() == "LineString");
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
            std::vector<Point> points;
            points.push_back(Point::from_xym(1.0, 2.0, 3.0));
            points.push_back(Point::from_xym(-4.0, -5.0, -6.0));
            LineString ls(points);
            CHECK(!ls.empty());
            CHECK(ls.dim == DimensionType::XYM);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGM);
            CHECK(ls.geom_type_str() == "LineString");
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
            std::vector<Point> points;
            points.emplace_back(1.0, 2.0, 3.0, 1.5);
            points.emplace_back(-4.0, -5.0, -6.0, 1.5);
            LineString ls(points);
            CHECK(!ls.empty());
            CHECK(ls.dim == DimensionType::XYZM);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZM);
            CHECK(ls.geom_type_str() == "LineString");
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
            CHECK(ls.dim == DimensionType::XY);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_str() == "LineString");
            const auto& p1 = ls[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = ls[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - initializer list")
        {
            LineString ls = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            CHECK(!ls.empty());
            CHECK(ls.dim == DimensionType::XYZ);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZ);
            CHECK(ls.geom_type_str() == "LineString");
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
            // not supported
        }

        SECTION("xyzm - initializer list")
        {
            LineString ls = {{1.0, 2.0, 3.0, 4.0}, {-5.0, -6.0, -7.0, -8.0}};
            CHECK(!ls.empty());
            CHECK(ls.dim == DimensionType::XYZM);
            CHECK(ls.geom_type() == GeometryType::LINESTRING);
            CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZM);
            CHECK(ls.geom_type_str() == "LineString");
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

        SECTION("throws - initializer list")
        {
            // invalid points
            CHECK_THROWS(LineString{{1, 2, 3, 4, 5}});
            CHECK_THROWS(LineString{{1}});

            // point mismatch
            CHECK_THROWS(LineString{{1, 2}, {1, 2, 3}});
            CHECK_THROWS(LineString{{1, 2}, {1, 2, 3, 4}});
            CHECK_THROWS(LineString{{1, 2, 3}, {1, 2}});
            CHECK_THROWS(LineString{{1, 2, 3}, {1, 2, 3, 4}});
            CHECK_THROWS(LineString{{1, 2, 3, 4}, {1, 2}});
            CHECK_THROWS(LineString{{1, 2, 3, 4}, {1, 2, 3}});
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
                auto ls          = LineString::from_json(json);
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
                // not supported
            }

            SECTION("xyzm - from json")
            {
                std::string json = R"({"type":"LineString","coordinates":[[1.0,2.0,3.0,-10.0],[4.0,5.0,6.0,-10.0]]})";
                auto ls          = LineString::from_json(json);
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
                CHECK(ls.geom_type_dim() == GeometryType::LINESTRING);
                CHECK(ls.dim == DimensionType::XY);
                const auto& p1 = ls[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                const auto& p2 = ls[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
            }

            SECTION("xyz - from wkt")
            {
                auto ls = LineString::from_wkt("LINESTRINGZ(1.4 2.3 1, 3.2 4.1 2)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZ);
                CHECK(ls.dim == DimensionType::XYZ);
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
                auto ls = LineString::from_wkt("LINESTRINGM(1.4 2.3 1, 3.2 4.1 2)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGM);
                CHECK(ls.dim == DimensionType::XYM);
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
                auto ls = LineString::from_wkt("LineStringZM(1.4 2.3 1 1, 3.2 4.1 2 2)");
                CHECK(not ls.empty());
                CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZM);
                CHECK(ls.dim == DimensionType::XYZM);
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
                    auto ls = LineString::from_wkt("LineString empty");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type_dim() == GeometryType::LINESTRING);
                    CHECK(ls.dim == DimensionType::XY);
                }

                SECTION("empty - xyz")
                {
                    auto ls = LineString::from_wkt("LineString Z empty");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZ);
                    CHECK(ls.dim == DimensionType::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto ls = LineString::from_wkt("LineString M empty");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGM);
                    CHECK(ls.dim == DimensionType::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto ls = LineString::from_wkt("LineString ZM empty");
                    CHECK(ls.empty());
                    CHECK(ls.geom_type_dim() == GeometryType::LINESTRINGZM);
                    CHECK(ls.dim == DimensionType::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(LineString::from_wkt("LineStringZM(1.4 2.3 1 1, 3.2 4.1 2 2)"));
                CHECK_NOTHROW(LineString::from_wkt("lineStringzm(1.4 2.3 1 1, 3.2 4.1 2 2)"));
                CHECK_NOTHROW(LineString::from_wkt("LineStringZ(1.4 2.3 1, 3.2 4.1 2)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString(1.4 2.3, 3.2 4.1)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString (10 40, 40 30, 20 20, 30 10)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString (10 40, 40 30, 20 20, 30 10)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString Z (10 40 -10, 40 30 -10, 20 20 -10, 30 10 -10)"));
                CHECK_NOTHROW(LineString::from_wkt("LineString (10.00232 40.32412, 40.11241 30.429017, 20.43754 20.4323, 30.75534 10.234234)"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(LineString::from_wkt("LineStringZM(1.4 2.3, 3.2 4.1)"));
                CHECK_THROWS(LineString::from_wkt("LineStringZM(1.4 2.3 1, 3.2 4.1 2)"));
                CHECK_THROWS(LineString::from_wkt("LineStringZM((1.4 2.3, 1.3)"));
                CHECK_THROWS(LineString::from_wkt("LineStringZM((1.4 2.3, 1.3"));
                CHECK_THROWS(LineString::from_wkt("LineStringZM(1.4.3 2.3.3 1.1.1 1.1.1, 3.2.1 4.1.1 2.2.1 2.2.3)"));
            }
        }

        SECTION("polyline")
        {
            SECTION("xy - from polyline")
            {
                std::string polyline = "_p~iF~ps|U_ulLnnqC_mqNvxq`@";
                auto ls              = LineString::from_polyline(polyline);
                ls.precision         = 5;
                CHECK(ls.wkt() == "LINESTRING(-120.20000 38.50000,-120.95000 40.70000,-126.45300 43.25200)");
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
                ls.precision  = 1;
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1.0,2.0],[3.0,4.0]]})");
            }

            SECTION("xyz - to json")
            {
                LineString ls = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                ls.precision  = 1;
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})");
            }

            SECTION("xym - to json")
            {
                // not supported
            }

            SECTION("xyzm - to json")
            {
                LineString ls = {{1.0, 2.0, 3.0, -10.0}, {4.0, 5.0, 6.0, -10.0}};
                ls.precision  = 1;
                CHECK(ls.json() == R"({"type":"LineString","coordinates":[[1.0,2.0,3.0,-10.0],[4.0,5.0,6.0,-10.0]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                LineString ls = {{1.0, 2.0}, {3.0, 4.0}};
                ls.precision  = 1;
                CHECK(ls.wkt() == R"(LINESTRING(1.0 2.0,3.0 4.0))");
            }

            SECTION("xyz - to wkt")
            {
                LineString ls = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                ls.precision  = 1;
                CHECK(ls.wkt() == R"(LINESTRINGZ(1.0 2.0 3.0,4.0 5.0 6.0))");
            }

            SECTION("xym - to wkt")
            {
                std::vector<Point> points;
                points.push_back(Point::from_xym(1.0, 2.0, 3.0));
                points.push_back(Point::from_xym(-4.0, -5.0, -6.0));
                LineString ls(points);
                CHECK(ls.wkt() == R"(LINESTRINGM(1.0 2.0 3.0,-4.0 -5.0 -6.0))");
            }

            SECTION("xyzm - to wkt")
            {
                LineString ls = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                ls.precision  = 1;
                CHECK(ls.wkt() == R"(LINESTRINGZM(1.0 2.0 3.0 4.0,5.0 6.0 7.0 8.0))");
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
                auto ls1 = LineString{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                auto ls2 = LineString{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(ls1 == ls2);
            }

            SECTION("xym - equal to")
            {
                std::vector<Point> pts1;
                pts1.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts1.push_back(Point::from_xym(4.0, 5.0, 6.0));
                auto ls1 = LineString(pts1);

                std::vector<Point> pts2;
                pts2.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts2.push_back(Point::from_xym(4.0, 5.0, 6.0));
                auto ls2 = LineString(pts2);
                CHECK(ls1 == ls2);
            }

            SECTION("xyzm - equal to")
            {
                auto ls1 = LineString{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto ls2 = LineString{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
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
                auto ls1 = LineString{{1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}};
                auto ls2 = LineString{{1.0, 2.0, 3.0}, {10.0, 20.0, 30.0}};
                CHECK(ls1 != ls2);
            }

            SECTION("xym - not equal to")
            {
                std::vector<Point> pts1;
                pts1.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts1.push_back(Point::from_xym(4.0, 5.0, 6.0));
                auto ls1 = LineString(pts1);
                std::vector<Point> pts2;
                pts2.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts2.push_back(Point::from_xym(6.0, 5.0, 4.0));
                auto ls2 = LineString(pts2);
                CHECK(ls1 != ls2);
            }

            SECTION("xyzm - not equal to")
            {
                auto ls1 = LineString{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto ls2 = LineString{{1.0, 2.0, 3.0, 4.0}, {8.0, 7.0, 6.0, 5.0}};
                CHECK(ls1 != ls2);
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                auto ls  = LineString{{1.0, 2.0}, {3.0, 4.0}};
                auto& p1 = ls[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINT);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINT);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
            }

            SECTION("xyz - index operator")
            {
                auto ls  = LineString{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
                auto& p1 = ls[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == -1.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == -2.0);

                auto& p3 = ls[2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.z == -3.0);
            }

            SECTION("xym - index operator")
            {
                std::vector<Point> pts;
                pts.push_back(Point::from_xym(1.0, 2.0, -1.0));
                pts.push_back(Point::from_xym(3.0, 4.0, -2.0));
                pts.push_back(Point::from_xym(5.0, 6.0, -3.0));
                auto ls = LineString(pts);

                auto& p1 = ls[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.m == -1.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINTM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.m == -2.0);

                auto& p3 = ls[2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTM);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.m == -3.0);
            }

            SECTION("xyzm - index operator")
            {
                auto ls  = LineString{{1.0, 2.0, 3.0, -1.0}, {3.0, 4.0, 5.0, -2.0}, {5.0, 6.0, 7.0, -3.0}};
                auto& p1 = ls[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -1.0);

                auto& p2 = ls[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == 5.0);
                CHECK(p2.m == -2.0);

                auto& p3 = ls[2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTZM);
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
            auto coords = ls.coords();
            CHECK(ls.size() == coords.size());

            double x, y;
            x = coords[0][0];
            y = coords[0][1];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            x = coords[1][0];
            y = coords[1][1];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            x = coords[2][0];
            y = coords[2][1];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
        }

        SECTION("xyz - coords")
        {
            auto ls     = LineString{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
            auto coords = ls.coords();
            CHECK(ls.size() == coords.size());

            double x, y, z;
            x = coords[0][0];
            y = coords[0][1];
            z = coords[0][2];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == -1.0);
            x = coords[1][0];
            y = coords[1][1];
            z = coords[1][2];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            CHECK(z == -2.0);
            x = coords[2][0];
            y = coords[2][1];
            z = coords[2][2];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
            CHECK(z == -3.0);
        }

        SECTION("xym - coords")
        {
            std::vector<Point> pts1;
            pts1.push_back(Point::from_xym(1.0, 2.0, -1.0));
            pts1.push_back(Point::from_xym(3.0, 4.0, -2.0));
            pts1.push_back(Point::from_xym(5.0, 6.0, -3.0));
            auto ls     = LineString(pts1);
            auto coords = ls.coords();
            CHECK(ls.size() == coords.size());

            double x, y, m;
            x = coords[0][0];
            y = coords[0][1];
            m = coords[0][2];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(m == -1.0);
            x = coords[1][0];
            y = coords[1][1];
            m = coords[1][2];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            CHECK(m == -2.0);
            x = coords[2][0];
            y = coords[2][1];
            m = coords[2][2];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
            CHECK(m == -3.0);
        }

        SECTION("xyzm - coords")
        {
            auto ls     = LineString{{1.0, 2.0, -1.0, -10.0}, {3.0, 4.0, -2.0, -20.0}, {5.0, 6.0, -3.0, -30.0}};
            auto coords = ls.coords();
            CHECK(ls.size() == coords.size());

            double x, y, z, m;
            x = coords[0][0];
            y = coords[0][1];
            z = coords[0][2];
            m = coords[0][3];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == -1.0);
            CHECK(m == -10.0);
            x = coords[1][0];
            y = coords[1][1];
            z = coords[1][2];
            m = coords[1][3];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            CHECK(z == -2.0);
            CHECK(m == -20.0);
            x = coords[2][0];
            y = coords[2][1];
            z = coords[2][2];
            m = coords[2][3];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
            CHECK(z == -3.0);
            CHECK(m == -30.0);
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
            auto ls = LineString{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
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
            std::vector<Point> pts;
            pts.push_back(Point::from_xym(1.0, 2.0, 3.0));
            pts.push_back(Point::from_xym(4.0, 5.0, 6.0));
            pts.push_back(Point::from_xym(7.0, 8.0, 9.0));
            auto ls = LineString(pts);
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
            auto ls = LineString{{1.0, 2.0, 3.0, -1.0}, {4.0, 5.0, 6.0, -2.0}, {7.0, 8.0, 9.0, -3.0}};
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
        CHECK(ls.bounds.maxx == 3.0);
        CHECK(ls.bounds.maxy == 4.0);
        CHECK(ls.bounds.minx == 1.0);
        CHECK(ls.bounds.miny == 2.0);
    }
}
