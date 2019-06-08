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
            CHECK(mp.dim() == dimension_type::XY);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINT);
            CHECK(mp.tagged_text() == "MultiPoint");
        }

        SECTION("xy - points vector")
        {

            std::vector<Point> points = {{1.0, 2.0}, {-3.0, -4.0}};
            MultiPoint mp(points.begin(), points.end());
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XY);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINT);
            CHECK(mp.tagged_text() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - points vector")
        {
            std::vector<PointZ> points = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            MultiPointZ mp(points.begin(), points.end());
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XYZ);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINTZ);
            CHECK(mp.tagged_text() == "MultiPoint");
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
            std::vector<PointM> points = {{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            MultiPointM mp(points.begin(), points.end());
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XYM);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINTM);
            CHECK(mp.tagged_text() == "MultiPoint");
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
            std::vector<PointZM> points = {{1.0, 2.0, 3.0, 1.5}, {-4.0, -5.0, -6.0, 1.5}};
            MultiPointZM mp(points.begin(), points.end());
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XYZM);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINTZM);
            CHECK(mp.tagged_text() == "MultiPoint");
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
            auto mp = MultiPoint{{1.0, 2.0}, {-3.0, -4.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XY);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINT);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINT);
            CHECK(mp.tagged_text() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -3.0);
            CHECK(p2.y == -4.0);
        }

        SECTION("xyz - initializer list")
        {
            auto mp = MultiPointZ{{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XYZ);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINTZ);
            CHECK(mp.tagged_text() == "MultiPoint");
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
            auto mp = MultiPointM{{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XYM);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINTM);
            CHECK(mp.tagged_text() == "MultiPoint");
            const auto& p1 = mp[0];
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.m == 3.0);
            const auto& p2 = mp[1];
            CHECK(p2.x == -4.0);
            CHECK(p2.y == -5.0);
            CHECK(p2.m == -6.0);
        }

        SECTION("xyzm - initializer list")
        {
            auto mp = MultiPointZM{{1.0, 2.0, 3.0, 4.0}, {-5.0, -6.0, -7.0, -8.0}};
            CHECK(!mp.empty());
            CHECK(mp.dim() == dimension_type::XYZM);
            CHECK(mp.geom_type() == geometry_type::MULTIPOINTZM);
            CHECK(mp.tagged_text() == "MultiPoint");
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
                auto mp          = MultiPointZ::from_json(json);
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
                std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0],[4.0,5.0,6.0]]})";
                auto mp          = MultiPointM::from_json(json);
                auto& p1         = mp[0];
                auto& p2         = mp[1];
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.m == 3.0);
                CHECK(p2.x == 4.0);
                CHECK(p2.y == 5.0);
                CHECK(p2.m == 6.0);
            }

            SECTION("xyzm - from json")
            {
                std::string json = R"({"type":"MultiPoint","coordinates":[[1.0,2.0,3.0,-10.0],[4.0,5.0,6.0,-10.0]]})";
                auto mp          = MultiPointZM::from_json(json);
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
                CHECK(mp.geom_type() == geometry_type::MULTIPOINT);
                CHECK(mp.dim() == dimension_type::XY);
                const auto& p1 = mp[0];
                CHECK(p1.x == 1.4);
                CHECK(p1.y == 2.3);
                const auto& p2 = mp[1];
                CHECK(p2.x == 3.2);
                CHECK(p2.y == 4.1);
            }

            SECTION("xyz - from wkt")
            {
                auto mp = MultiPointZ::from_wkt("MULTIPOINTZ((1.4 2.3 1), (3.2 4.1 2))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type() == geometry_type::MULTIPOINTZ);
                CHECK(mp.dim() == dimension_type::XYZ);
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
                auto mp = MultiPointM::from_wkt("MULTIPOINTM((1.4 2.3 1), (3.2 4.1 2))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type() == geometry_type::MULTIPOINTM);
                CHECK(mp.dim() == dimension_type::XYM);
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
                auto mp = MultiPointZM::from_wkt("MULTIPOINTZM((1.4 2.3 1 1), (3.2 4.1 2 2))");
                CHECK(not mp.empty());
                CHECK(mp.geom_type() == geometry_type::MULTIPOINTZM);
                CHECK(mp.dim() == dimension_type::XYZM);
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
                    CHECK(mp.geom_type() == geometry_type::MULTIPOINT);
                    CHECK(mp.dim() == dimension_type::XY);
                }

                SECTION("empty - xyz")
                {
                    auto mp = MultiPointZ::from_wkt("MULTIPOINT Z EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type() == geometry_type::MULTIPOINTZ);
                    CHECK(mp.dim() == dimension_type::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto mp = MultiPointM::from_wkt("MULTIPOINT M EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type() == geometry_type::MULTIPOINTM);
                    CHECK(mp.dim() == dimension_type::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto mp = MultiPointZM::from_wkt("MULTIPOINT ZM EMPTY");
                    CHECK(mp.empty());
                    CHECK(mp.geom_type() == geometry_type::MULTIPOINTZM);
                    CHECK(mp.dim() == dimension_type::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(MultiPointZM::from_wkt("MultiPointZM((1.4 2.3 1 1), (3.2 4.1 2 2))"));
                CHECK_NOTHROW(MultiPointZM::from_wkt("multipointzm((1.4 2.3 1 1), (3.2 4.1 2 2))"));
                CHECK_NOTHROW(MultiPointZ::from_wkt("MultiPointZ((1.4 2.3 1), (3.2 4.1 2))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MultiPoint((1.4 2.3), (3.2 4.1))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT ((10 40), (40 30), (20 20), (30 10))"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT (10 40, 40 30, 20 20, 30 10)"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT Z (10 40 -10, 40 30 -10, 20 20 -10, 30 10 -10)"));
                CHECK_NOTHROW(MultiPoint::from_wkt("MULTIPOINT (10.00232 40.32412, 40.11241 30.429017, 20.43754 20.4323, 30.75534 10.234234)"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(MultiPointZM::from_wkt("MultiPointZM((1.4 2.3), (3.2 4.1))"));
                CHECK_THROWS(MultiPointZM::from_wkt("MultiPointZM((1.4 2.3 1), (3.2 4.1 2))"));
                CHECK_THROWS(MultiPointZM::from_wkt("MultiPointZM((1.4 2.3, 1.3)"));
                CHECK_THROWS(MultiPointZM::from_wkt("MultiPointZM((1.4 2.3, 1.3"));
                CHECK_THROWS(MultiPointZM::from_wkt("MultiPointZM((1.4.3 2.3.3 1.1.1 1.1.1), (3.2.1 4.1.1 2.2.1 2.2.3))"));
                /// @todo add more tests
            }
        }

        SECTION("polyline")
        {
            SECTION("xy - from polyline")
            {
                //                std::string polyline = "_p~iF~ps|U_ulLnnqC_mqNvxq`@";
                //                auto mp              = MultiPoint::from_polyline(polyline);
                //                CHECK(mp.wkt() == "MULTIPOINT((-120.2 38.5),(-120.95 40.7),(-126.453 43.252))");
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                auto mp = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1,2],[3,4]]})");
            }

            SECTION("xyz - to json")
            {
                auto mp = MultiPointZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1,2,3],[4,5,6]]})");
            }

            SECTION("xym - to json")
            {
                auto mp = MultiPointM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1,2,3],[4,5,6]]})");
            }

            SECTION("xyzm - to json")
            {
                auto mp = MultiPointZM{{1.0, 2.0, 3.0, -10.0}, {4.0, 5.0, 6.0, -10.0}};
                CHECK(mp.json() == R"({"type":"MultiPoint","coordinates":[[1,2,3,-10],[4,5,6,-10]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                auto mp = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
                CHECK(mp.wkt() == R"(MULTIPOINT((1 2),(3 4)))");
            }

            SECTION("xyz - to wkt")
            {
                auto mp = MultiPointZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(mp.wkt() == R"(MULTIPOINTZ((1 2 3),(4 5 6)))");
            }

            SECTION("xym - to wkt")
            {
                auto mp = MultiPointM{{1.0, 2.0, 3.0}, {-4.0, -5.0, -6.0}};
                CHECK(mp.wkt() == R"(MULTIPOINTM((1 2 3),(-4 -5 -6)))");
            }

            SECTION("xyzm - to wkt")
            {
                auto mp = MultiPointZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                CHECK(mp.wkt() == R"(MULTIPOINTZM((1 2 3 4),(5 6 7 8)))");
            }
        }

        SECTION("polyline")
        {
            SECTION("xy - to polyline")
            {
                MultiPoint mp = {{-120.2, 38.5}, {-120.95, 40.7}, {-126.453, 43.252}};
                CHECK(mp.polyline() == "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
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
                auto mp1 = MultiPointZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                auto mp2 = MultiPointZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(mp1 == mp2);
            }

            SECTION("xym - equal to")
            {
                auto mp1 = MultiPointM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                auto mp2 = MultiPointM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
                CHECK(mp1 == mp2);
            }

            SECTION("xyzm - equal to")
            {
                auto mp1 = MultiPointZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto mp2 = MultiPointZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
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
                auto mp1 = MultiPointZ{{1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}};
                auto mp2 = MultiPointZ{{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}};
                CHECK(mp1 != mp2);
            }

            SECTION("xym - not equal to")
            {
                auto mp1 = MultiPointM{{1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}};
                auto mp2 = MultiPointM{{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}};
                CHECK(mp1 != mp2);
            }

            SECTION("xyzm - not equal to")
            {
                auto mp1 = MultiPointZM{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
                auto mp2 = MultiPointZM{{1.0, 2.0, 3.0, 4.0}, {8.0, 7.0, 6.0, 5.0}};
                CHECK(mp1 != mp2);
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                auto mp  = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type() == geometry_type::POINT);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type() == geometry_type::POINT);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
            }

            SECTION("xyz - index operator")
            {
                auto mp  = MultiPointZ{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type() == geometry_type::POINTZ);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == -1.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type() == geometry_type::POINTZ);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == -2.0);

                auto& p3 = mp[2];
                CHECK(p3.geom_type() == geometry_type::POINTZ);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.z == -3.0);
            }

            SECTION("xym - index operator")
            {
                auto mp  = MultiPointM{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type() == geometry_type::POINTM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.m == -1.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type() == geometry_type::POINTM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.m == -2.0);

                auto& p3 = mp[2];
                CHECK(p3.geom_type() == geometry_type::POINTM);
                CHECK(p3.x == 5.0);
                CHECK(p3.y == 6.0);
                CHECK(p3.m == -3.0);
            }

            SECTION("xyzm - index operator")
            {
                auto mp  = MultiPointZM{{1.0, 2.0, 3.0, -1.0}, {3.0, 4.0, 5.0, -2.0}, {5.0, 6.0, 7.0, -3.0}};
                auto& p1 = mp[0];
                CHECK(p1.geom_type() == geometry_type::POINTZM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -1.0);

                auto& p2 = mp[1];
                CHECK(p2.geom_type() == geometry_type::POINTZM);
                CHECK(p2.x == 3.0);
                CHECK(p2.y == 4.0);
                CHECK(p2.z == 5.0);
                CHECK(p2.m == -2.0);

                auto& p3 = mp[2];
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
            auto mp     = MultiPoint{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
            auto coords = mp.xy();
            CHECK(mp.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }

        SECTION("xyz - coords")
        {
            auto mp     = MultiPointZ{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
            auto coords = mp.xy();
            CHECK(mp.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }

        SECTION("xym - coords")
        {
            auto mp     = MultiPointM{{1.0, 2.0, -1.0}, {3.0, 4.0, -2.0}, {5.0, 6.0, -3.0}};
            auto coords = mp.xy();
            CHECK(mp.size() == coords.size());
            CHECK(std::get<0>(coords[0]) == 1.0);
            CHECK(std::get<1>(coords[0]) == 2.0);
            CHECK(std::get<0>(coords[1]) == 3.0);
            CHECK(std::get<1>(coords[1]) == 4.0);
            CHECK(std::get<0>(coords[2]) == 5.0);
            CHECK(std::get<1>(coords[2]) == 6.0);
        }

        SECTION("xyzm - coords")
        {
            auto mp     = MultiPointZM{{1.0, 2.0, -1.0, -10.0}, {3.0, 4.0, -2.0, -20.0}, {5.0, 6.0, -3.0, -30.0}};
            auto coords = mp.xy();
            CHECK(mp.size() == coords.size());
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
            auto mp = MultiPointZ{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
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
            auto mp = MultiPointM{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
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
            auto mp = MultiPointZM{{1.0, 2.0, 3.0, -1.0}, {4.0, 5.0, 6.0, -2.0}, {7.0, 8.0, 9.0, -3.0}};
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
        auto mp  = MultiPoint{{1.0, 2.0}, {3.0, 4.0}};
        bounds b = mp.bounds();
        CHECK(b.maxx == 3.0);
        CHECK(b.maxy == 4.0);
        CHECK(b.minx == 1.0);
        CHECK(b.miny == 2.0);
    }
}
