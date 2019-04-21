#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPoint")
{
    SECTION("constructors")
    {
        SECTION("empty")
        {
            MultiPoint mp;
            CHECK(mp.empty());
            CHECK(mp.dim == DimensionType::XY);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_str() == "MultiPoint");
        }

        SECTION("xy - points vector")
        {
            std::vector<Point> points;
            points.emplace_back(1.0, 2.0);
            points.emplace_back(-3.0, -4.0);
            MultiPoint mp(points);
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XY);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - points vector")
        {
            std::vector<Point> points;
            points.emplace_back(1.0, 2.0, 3.0);
            points.emplace_back(-4.0, -5.0, -6.0);
            MultiPoint mp(points);
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XYZ);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZ);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.z == -6.0);
        }

        SECTION("xym - points vector")
        {
            std::vector<Point> points;
            points.push_back(Point::from_xym(1.0, 2.0, 3.0));
            points.push_back(Point::from_xym(-4.0, -5.0, -6.0));
            MultiPoint mp(points);
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XYM);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTM);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.m == 3.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.m == -6.0);
        }

        SECTION("xyzm - points vector")
        {
            std::vector<Point> points;
            points.emplace_back(1.0, 2.0, 3.0, 1.5);
            points.emplace_back(-4.0, -5.0, -6.0, 1.5);
            MultiPoint mp(points);
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XYZM);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZM);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            CHECK(p1.m == 1.5);
            const auto& p2 = mp[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.z == -6.0);
            CHECK(p1.m == 1.5);
        }

        SECTION("xy - initializer list")
        {
            MultiPoint mp = {{1.0, 2.0}, {-3.0, -4.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XY);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - initializer list")
        {
            MultiPoint mp = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XYZ);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZ);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            const auto& p2 = mp[1];
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
            MultiPoint mp = {{1.0, 2.0, 3.0, 4.0}, {-5.0, -6.0, -7.0, -8.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim == DimensionType::XYZM);
            CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
            CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZM);
            CHECK(mp.geom_type_str() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            CHECK(p1.m == 4.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -5.0);
            CHECK(p2.y == -6.0);
            CHECK(p2.z == -7.0);
            CHECK(p2.m == -8.0);
        }

        SECTION("throws - initializer list")
        {
            // invalid points
            CHECK_THROWS(MultiPoint{{1, 2, 3, 4, 5}});
            CHECK_THROWS(MultiPoint{{1}});

            // point mismatch
            CHECK_THROWS(MultiPoint{{1, 2}, {1, 2, 3}});
            CHECK_THROWS(MultiPoint{{1, 2}, {1, 2, 3, 4}});
            CHECK_THROWS(MultiPoint{{1, 2, 3}, {1, 2}});
            CHECK_THROWS(MultiPoint{{1, 2, 3}, {1, 2, 3, 4}});
            CHECK_THROWS(MultiPoint{{1, 2, 3, 4}, {1, 2}});
            CHECK_THROWS(MultiPoint{{1, 2, 3, 4}, {1, 2, 3}});
        }
    }

    SECTION("from_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - from json")
            {
                std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0],[3.0,4.0]]})";
                auto mp          = MultiPoint::from_json(json);
                auto& p1         = mp[0];
                auto& p2         = mp[1];
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
            }

            SECTION("xyz - from json")
            {
                std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})";
                auto mp          = MultiPoint::from_json(json);
                auto& p1         = mp[0];
                auto& p2         = mp[1];
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
                std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0,-10.0],[4.0,5.0,6.0,-10.0]]})";
                auto mp          = MultiPoint::from_json(json);
                auto& p1         = mp[0];
                auto& p2         = mp[1];
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
                auto mp = MultiPoint::from_wkt("MULTIPOINT((1.4 2.3), (3.2 4.1))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINT);
                CHECK(mp.dim == DimensionType::XY);
                const auto& p1 = mp[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                const auto& p2 = mp[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
            }

            SECTION("xyz - from wkt")
            {
                auto mp = MultiPoint::from_wkt("MULTIPOINTZ((1.4 2.3 1), (3.2 4.1 2))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZ);
                CHECK(mp.dim == DimensionType::XYZ);
                const auto& p1 = mp[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                CHECK(p1.z == 1);
                const auto& p2 = mp[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
                CHECK(p2.z == 2);
            }

            SECTION("xym - from wkt")
            {
                auto mp = MultiPoint::from_wkt("MULTIPOINTM((1.4 2.3 1), (3.2 4.1 2))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTM);
                CHECK(mp.dim == DimensionType::XYM);
                const auto& p1 = mp[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                CHECK(p1.m == 1);
                const auto& p2 = mp[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
                CHECK(p2.m == 2);
            }

            SECTION("xyzm - from wkt")
            {
                auto mp = MultiPoint::from_wkt("MULTIPOINTZM((1.4 2.3 1 1), (3.2 4.1 2 2))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZM);
                CHECK(mp.dim == DimensionType::XYZM);
                const auto& p1 = mp[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                CHECK(p1.z == 1);
                CHECK(p1.m == 1);
                const auto& p2 = mp[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
                CHECK(p2.z == 2);
                CHECK(p2.m == 2);
            }

            SECTION("empty - from wkt")
            {
                SECTION("empty - xy")
                {
                    auto mp = MultiPoint::from_wkt("MULTIPOINT EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINT);
                    CHECK(mp.dim == DimensionType::XY);
                }

                SECTION("empty - xyz")
                {
                    auto mp = MultiPoint::from_wkt("MULTIPOINT Z EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZ);
                    CHECK(mp.dim == DimensionType::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto mp = MultiPoint::from_wkt("MULTIPOINT M EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTM);
                    CHECK(mp.dim == DimensionType::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto mp = MultiPoint::from_wkt("MULTIPOINT ZM EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type_dim() == GeometryType::MULTIPOINTZM);
                    CHECK(mp.dim == DimensionType::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(MultiPoint::from_wkt("MultiPointZM((1.4 2.3 1 1), (3.2 4.1 2 2))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("multipointzm((1.4 2.3 1 1), (3.2 4.1 2 2))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MultiPointZ((1.4 2.3 1), (3.2 4.1 2))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MultiPoint((1.4 2.3), (3.2 4.1))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT ((10 40), (40 30), (20 20), (30 10))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT (10 40, 40 30, 20 20, 30 10)"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT Z (10 40 -10, 40 30 -10, 20 20 -10, 30 10 -10)"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT (10.00232 40.32412, 40.11241 30.429017, 20.43754 20.4323, 30.75534 10.234234)"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(MultiPoint::from_wkt("MultiPointZM((1.4 2.3), (3.2 4.1))"));
                CHECK_THROWS(MultiPoint::from_wkt("MultiPointZM((1.4 2.3 1), (3.2 4.1 2))"));
                CHECK_THROWS(MultiPoint::from_wkt("MultiPointZM((1.4 2.3, 1.3)"));
                CHECK_THROWS(MultiPoint::from_wkt("MultiPointZM((1.4 2.3, 1.3"));
                CHECK_THROWS(MultiPoint::from_wkt("MultiPointZM((1.4.3 2.3.3 1.1.1 1.1.1), (3.2.1 4.1.1 2.2.1 2.2.3))"));
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                MultiPoint mp = {{1.0, 2.0}, {3.0, 4.0}};
                mp.precision  = 1;
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1.0,2.0],[3.0,4.0]]})");
            }

            SECTION("xyz - to json")
            {
                MultiPoint mp = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                mp.precision  = 1;
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})");
            }

            SECTION("xym - to json")
            {
                // not supported
            }

            SECTION("xyzm - to json")
            {
                MultiPoint mp = {{1.0, 2.0, 3.0, -10.0}, {4.0, 5.0, 6.0, -10.0}};
                mp.precision  = 1;
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0,-10.0],[4.0,5.0,6.0,-10.0]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                MultiPoint mp = {{1.0, 2.0}, {3.0, 4.0}};
                mp.precision  = 1;
                CHECK(mp.wkt() == R"(MULTIPOINT((1.0 2.0),(3.0 4.0)))");
            }

            SECTION("xyz - to wkt")
            {
                MultiPoint mp = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                mp.precision  = 1;
                CHECK(mp.wkt() == R"(MULTIPOINTZ((1.0 2.0 3.0),(4.0 5.0 6.0)))");
            }

            SECTION("xym - to wkt")
            {
                std::vector<Point> points;
                points.push_back(Point::from_xym(1.0, 2.0, 3.0));
                points.push_back(Point::from_xym(-4.0, -5.0, -6.0));
                MultiPoint mp(points);
                CHECK(mp.wkt() == R"(MULTIPOINTM((1.0 2.0 3.0),(-4.0 -5.0 -6.0)))");
            }

            SECTION("xyzm - to wkt")
            {
                MultiPoint mp = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                mp.precision  = 1;
                CHECK(mp.wkt() == R"(MULTIPOINTZM((1.0 2.0 3.0 4.0),(5.0 6.0 7.0 8.0)))");
            }
        }
    }

    SECTION("operators")
    {
        SECTION("equal to - operator")
        {
            SECTION("xy - equal to")
            {
                auto mp1 = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
                auto mp2 = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
                CHECK(mp1 == mp2);
            }

            SECTION("xyz - equal to")
            {
                auto mp1 = MultiPoint{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                auto mp2 = MultiPoint{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(mp1 == mp2);
            }

            SECTION("xym - equal to")
            {
                std::vector<Point> pts1;
                pts1.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts1.push_back(Point::from_xym(4.0, 5.0, 6.0));
                auto mp1 = MultiPoint(pts1);

                std::vector<Point> pts2;
                pts2.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts2.push_back(Point::from_xym(4.0, 5.0, 6.0));
                auto mp2 = MultiPoint(pts2);
                CHECK(mp1 == mp2);
            }

            SECTION("xyzm - equal to")
            {
                auto mp1 = MultiPoint{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto mp2 = MultiPoint{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                CHECK(mp1 == mp2);
            }
        }

        SECTION("not equal to - operator")
        {
            SECTION("xy - not equal to")
            {
                auto mp1 = MultiPoint{{1.0, 2.0}, {1.0, 2.0}};
                auto mp2 = MultiPoint{{1.0, 2.0}, {2.0, 1.0}};
                CHECK(mp1 != mp2);
            }

            SECTION("xyz - not equal to")
            {
                auto mp1 = MultiPoint{{1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}};
                auto mp2 = MultiPoint{{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}};
                CHECK(mp1 != mp2);
            }

            SECTION("xym - not equal to")
            {
                std::vector<Point> pts1;
                pts1.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts1.push_back(Point::from_xym(4.0, 5.0, 6.0));
                auto mp1 = MultiPoint(pts1);
                std::vector<Point> pts2;
                pts2.push_back(Point::from_xym(1.0, 2.0, 3.0));
                pts2.push_back(Point::from_xym(6.0, 5.0, 4.0));
                auto mp2 = MultiPoint(pts2);
                CHECK(mp1 != mp2);
            }

            SECTION("xyzm - not equal to")
            {
                auto mp1 = MultiPoint{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto mp2 = MultiPoint{{1.0, 2.0, 3.0, 4.0}, {8.0, 7.0, 6.0, 5.0}};
                CHECK(mp1 != mp2);
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                auto mp  = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINT);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINT);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
            }

            SECTION("xyz - index operator")
            {
                auto mp  = MultiPoint{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == -1.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == -2.0);

                auto& p3 = mp[2];
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
                auto mp = MultiPoint(pts);

                auto& p1 = mp[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.m == -1.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINTM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.m == -2.0);

                auto& p3 = mp[2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTM);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.m == -3.0);
            }

            SECTION("xyzm - index operator")
            {
                auto mp  = MultiPoint{{1.0, 2.0, 3.0, -1.0}, {3.0, 4.0, 5.0, -2.0}, {5.0, 6.0, 7.0, -3.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -1.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == 5.0);
                CHECK(p2.m == -2.0);

                auto& p3 = mp[2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.z == 7.0);
                CHECK(p3.m == -3.0);
            }
        }
    }

    SECTION("coordinates tuples")
    {
        SECTION("xy - tuples")
        {
            auto mp     = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
            auto coords = mp.xy();
            CHECK(mp.size() == coords.size());

            double x, y;
            std::tie(x, y) = coords[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            std::tie(x, y) = coords[1];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            std::tie(x, y) = coords[2];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
        }

        SECTION("xyz - tuples")
        {
            auto mp     = MultiPoint{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
            auto coords = mp.xyz();
            CHECK(mp.size() == coords.size());

            double x, y, z;
            std::tie(x, y, z) = coords[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == -1.0);
            std::tie(x, y, z) = coords[1];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            CHECK(z == -2.0);
            std::tie(x, y, z) = coords[2];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
            CHECK(z == -3.0);
        }

        SECTION("xym - tuples")
        {
            std::vector<Point> pts1;
            pts1.push_back(Point::from_xym(1.0, 2.0, -1.0));
            pts1.push_back(Point::from_xym(3.0, 4.0, -2.0));
            pts1.push_back(Point::from_xym(5.0, 6.0, -3.0));
            auto mp     = MultiPoint(pts1);
            auto coords = mp.xym();
            CHECK(mp.size() == coords.size());

            double x, y, m;
            std::tie(x, y, m) = coords[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(m == -1.0);
            std::tie(x, y, m) = coords[1];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            CHECK(m == -2.0);
            std::tie(x, y, m) = coords[2];
            CHECK(x == 5.0);
            CHECK(y == 6.0);
            CHECK(m == -3.0);
        }

        SECTION("xyzm - tuples")
        {
            auto mp     = MultiPoint{{1.0, 2.0, -1.0, -10.0}, {3.0, 4.0, -2.0, -20.0}, {5.0, 6.0, -3.0, -30.0}};
            auto coords = mp.xyzm();
            CHECK(mp.size() == coords.size());

            double x, y, z, m;
            std::tie(x, y, z, m) = coords[0];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == -1.0);
            CHECK(m == -10.0);
            std::tie(x, y, z, m) = coords[1];
            CHECK(x == 3.0);
            CHECK(y == 4.0);
            CHECK(z == -2.0);
            CHECK(m == -20.0);
            std::tie(x, y, z, m) = coords[2];
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
            auto mp = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
            int n   = 0;
            for (const auto& p : mp)
            {
                CHECK(p.x != 0);
                CHECK(p.y != 0);
                ++n;
            }
            CHECK(n == 3);
        }

        SECTION("xyz - for each")
        {
            auto mp = MultiPoint{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
            int n   = 0;
            for (const auto& p : mp)
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
            auto mp = MultiPoint(pts);
            int n   = 0;
            for (const auto& p : mp)
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
            auto mp = MultiPoint{{1.0, 2.0, 3.0, -1.0}, {4.0, 5.0, 6.0, -2.0}, {7.0, 8.0, 9.0, -3.0}};
            int n   = 0;
            for (const auto& p : mp)
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
        auto mp = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
        CHECK(mp.bounds.maxx == 3.0);
        CHECK(mp.bounds.maxy == 4.0);
        CHECK(mp.bounds.minx == 1.0);
        CHECK(mp.bounds.miny == 2.0);
    }
}
