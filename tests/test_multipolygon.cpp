#include <ciso646>
#include <vector>
#include <catch2/catch_amalgamated.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPolygon")
{
    SECTION("constructors")
    {
        SECTION("empty")
        {
            MultiPolygon mpg;
            CHECK(mpg.empty());
            CHECK(mpg.dim() == dimension_type::XY);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGON);
            CHECK(mpg.tagged_text() == "MultiPolygon");
        }

        SECTION("xy - polygon vector")
        {
            std::vector<Polygon> polygons = {
                Polygon{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}, {1.0, 2.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}, {11.0, 12.0}}},
                Polygon{
                    {{100.0, 200.0}, {4.0, 5.0}, {7.0, 8.0}, {100.0, 200.0}},
                    {{1100.0, 1200.0}, {1300.0, 1400.0}, {1600.0, 1700.0}, {1100.0, 1200.0}}}};

            MultiPolygon mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XY);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGON);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
        }

        SECTION("xyz - polygon vector")
        {
            std::vector<PolygonZ> polygons = {
                PolygonZ{
                    {{1.0, 2.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {1.0, 2.0, -1.0}},
                    {{11.0, 12.0, -1.0}, {13.0, 14.0, -1.0}, {16.0, 17.0, -1.0}, {11.0, 12.0, -1.0}}},
                PolygonZ{
                    {{100.0, 200.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {100.0, 200.0, -1.0}},
                    {{1100.0, 1200.0, -1.0}, {1300.0, 1400.0, -1.0}, {1600.0, 1700.0, -1.0}, {1100.0, 1200.0, -1.0}}}};

            MultiPolygonZ mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYZ);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZ);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].z == -1.0);
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
            CHECK(mpg[1][0][0].z == -1.0);
        }

        SECTION("xym - polygon vector")
        {
            std::vector<PolygonM> polygons = {
                PolygonM{
                    {{1.0, 2.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {1.0, 2.0, -1.0}},
                    {{11.0, 12.0, -1.0}, {13.0, 14.0, -1.0}, {16.0, 17.0, -1.0}, {11.0, 12.0, -1.0}}},
                PolygonM{
                    {{100.0, 200.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {100.0, 200.0, -1.0}},
                    {{1100.0, 1200.0, -1.0}, {1300.0, 1400.0, -1.0}, {1600.0, 1700.0, -1.0}, {1100.0, 1200.0, -1.0}}}};

            MultiPolygonM mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYM);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONM);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].m == -1.0);
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
            CHECK(mpg[1][0][0].m == -1.0);
        }

        SECTION("xyzm - initializer list")
        {
            auto mpg = MultiPolygonZM{
                PolygonZM{
                    {{1.0, 2.0, -1.0, 5.0}, {4.0, 5.0, -1.0, 5.0}, {7.0, 8.0, -1.0, 5.0}},
                    {{11.0, 12.0, -1.0, 5.0}, {13.0, 14.0, -1.0, 5.0}, {16.0, 17.0, -1.0, 5.0}}},
                PolygonZM{
                    {{1.0, 2.0, -1.0, 5.0}, {4.0, 5.0, -1.0, 5.0}, {7.0, 8.0, -1.0, 5.0}},
                    {{11.0, 12.0, -1.0, 5.0}, {13.0, 14.0, -1.0, 5.0}, {16.0, 17.0, -1.0, 5.0}}}};

            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYZM);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZM);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].z == -1.0);
            CHECK(mpg[0][0][0].m == 5.0);
            CHECK(mpg[1][1][2].x == 16.0);
            CHECK(mpg[1][1][2].y == 17.0);
            CHECK(mpg[1][1][2].z == -1.0);
            CHECK(mpg[1][1][2].m == 5.0);
            CHECK(mpg[1][1][2].geom_type() == geometry_type::POINTZM);
        }
    }

    SECTION("from_... methods")
    {
        SECTION("wkt")
        {
            SECTION("xy - from wkt")
            {
                auto mpg = MultiPolygon::from_wkt(R"(MULTIPOLYGON (((40 40, 20 45, 45 30, 40 40)),((20 35, 10 30, 10 10, 30 5, 45 20, 20 35),(30 20, 20 15, 20 25, 30 20))))");
                CHECK(mpg.size() == 3);
                CHECK(mpg.dim() == dimension_type::XY);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGON);
                CHECK(mpg[0][0][0].x == 40.0);
                CHECK(mpg[0][0][0].y == 40.0);
                CHECK(mpg[1][0][0].x == 20.0);
                CHECK(mpg[1][0][0].y == 35.0);
            }

            SECTION("xyz - from wkt")
            {
                auto mpg = MultiPolygonZ::from_wkt(R"(MULTIPOLYGON Z (((40 40 1, 20 45 2, 45 30 3, 40 40 4)),((20 35 1, 10 30 2, 10 10 3, 30 5 4, 45 20 5, 20 35 6),(30 20 1, 20 15 2, 20 25 3, 30 20 4))))");
                CHECK(mpg.size() == 3);
                CHECK(mpg.dim() == dimension_type::XYZ);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZ);
                CHECK(mpg[0][0][0].x == 40.0);
                CHECK(mpg[0][0][0].y == 40.0);
                CHECK(mpg[0][0][0].z == 1.0);
                CHECK(mpg[1][0][0].x == 20.0);
                CHECK(mpg[1][0][0].y == 35.0);
                CHECK(mpg[1][0][0].z == 1.0);
            }

            SECTION("xym - from wkt")
            {
                auto mpg = MultiPolygonM::from_wkt(R"(MULTIPOLYGON M (((40 40 1, 20 45 2, 45 30 3, 40 40 4)),((20 35 1, 10 30 2, 10 10 3, 30 5 4, 45 20 5, 20 35 6),(30 20 1, 20 15 2, 20 25 3, 30 20 4))))");
                CHECK(mpg.size() == 3);
                CHECK(mpg.dim() == dimension_type::XYM);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONM);
                CHECK(mpg[0][0][0].x == 40.0);
                CHECK(mpg[0][0][0].y == 40.0);
                CHECK(mpg[0][0][0].m == 1.0);
                CHECK(mpg[1][0][0].x == 20.0);
                CHECK(mpg[1][0][0].y == 35.0);
                CHECK(mpg[1][0][0].m == 1.0);
            }

            SECTION("xyzm - from wkt")
            {
                auto mpg = MultiPolygonZM::from_wkt(R"(MULTIPOLYGON ZM (((40 40 1 -1, 20 45 2 -2, 45 30 3 -3, 40 40 4 -4)),((20 35 1 -1, 10 30 2 -2, 10 10 3 -3, 30 5 4 -4, 45 20 5 -5, 20 35 6 -6),(30 20 1 -1, 20 15 2 -2, 20 25 3 -3, 30 20 4 -4))))");
                CHECK(mpg.size() == 3);
                CHECK(mpg.dim() == dimension_type::XYZM);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZM);
                CHECK(mpg[0][0][0].x == 40.0);
                CHECK(mpg[0][0][0].y == 40.0);
                CHECK(mpg[0][0][0].z == 1.0);
                CHECK(mpg[0][0][0].m == -1.0);
                CHECK(mpg[1][0][0].x == 20.0);
                CHECK(mpg[1][0][0].y == 35.0);
                CHECK(mpg[1][0][0].z == 1.0);
                CHECK(mpg[1][0][0].m == -1.0);
            }
        }

        SECTION("json")
        {
            SECTION("xy - from json")
            {
                std::string json = R"({"type":"MultiPolygon","coordinates":[[[[10,35],[20,20],[10,40]]],[[[40,40],[30,30],[40,20],[30,5]]]]})";
                auto mpg         = MultiPolygon::from_json(json);
                CHECK(mpg.size() == 2);
                CHECK(mpg.dim() == dimension_type::XY);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGON);
                CHECK(mpg[0][0][0].x == 10.0);
                CHECK(mpg[0][0][0].y == 35.0);
                CHECK(mpg[1][0][3].x == 30.0);
                CHECK(mpg[1][0][3].y == 5.0);
            }

            SECTION("xyz - from json")
            {
                std::string json = R"({"type":"MultiPolygon","coordinates":[[[[10,35,-10],[20,20,-10],[10,40,-10]]],[[[40,40,-20],[30,30,-20],[40,20,-20],[30,5,-20]]]]})";
                auto mpg         = MultiPolygonZ::from_json(json);
                CHECK(mpg.size() == 2);
                CHECK(mpg.dim() == dimension_type::XYZ);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZ);
                CHECK(mpg[0][0][0].x == 10.0);
                CHECK(mpg[0][0][0].y == 35.0);
                CHECK(mpg[0][0][0].z == -10.0);
                CHECK(mpg[1][0][3].x == 30.0);
                CHECK(mpg[1][0][3].y == 5.0);
                CHECK(mpg[1][0][3].z == -20.0);
            }

            SECTION("xyzm - from json")
            {
                std::string json = R"({"type":"MultiPolygon","coordinates":[[[[10,35,-10,-5],[20,20,-10,-5],[10,40,-10,-5]]],[[[40,40,-20,-4000],[30,30,-20,-4000],[40,20,-20,-4000],[30,5,-20,-4000]]]]})";
                auto mpg         = MultiPolygonZM::from_json(json);
                CHECK(mpg.size() == 2);
                CHECK(mpg.dim() == dimension_type::XYZM);
                CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZM);
                CHECK(mpg[0][0][0].x == 10.0);
                CHECK(mpg[0][0][0].y == 35.0);
                CHECK(mpg[0][0][0].z == -10.0);
                CHECK(mpg[0][0][0].m == -5.0);
                CHECK(mpg[1][0][3].x == 30.0);
                CHECK(mpg[1][0][3].y == 5.0);
                CHECK(mpg[1][0][3].z == -20.0);
                CHECK(mpg[1][0][3].m == -4000.0);
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                auto mpg = MultiPolygon{
                    Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}, {1.0, 2.0}}},
                    Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}, {11.0, 12.0}}}};
                CHECK(mpg.json() == R"({"type":"MultiPolygon","coordinates":[[[[1,2],[4,5],[7,8],[1,2]]],[[[11,12],[13,14],[16,17],[11,12]]]]})");
            }

            SECTION("xyzm - to json")
            {
                auto mpg = MultiPolygonZM{
                    PolygonZM{{{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}}},
                    PolygonZM{{{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}}};
                CHECK(mpg.json() == R"({"type":"MultiPolygon","coordinates":[[[[1,2,3,-1.5],[4,5,6,-2.5],[7,8,9,-3.5]]],[[[11,12,13,-10.5],[13,14,15,-11.5],[16,17,18,-12.5]]]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                auto mpg = MultiPolygon{
                    Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}, {1.0, 2.0}}},
                    Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}, {11.0, 12.0}}}};
                CHECK(mpg.wkt() == "MULTIPOLYGON(((1 2,4 5,7 8,1 2)),((11 12,13 14,16 17,11 12)))");
            }

            SECTION("xyzm - to wkt")
            {
                auto mpg = MultiPolygonZM{
                    PolygonZM{{{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}}},
                    PolygonZM{{{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}}};
                CHECK(mpg.wkt() == "MULTIPOLYGONZM(((1 2 3 -1.5,4 5 6 -2.5,7 8 9 -3.5)),((11 12 13 -10.5,13 14 15 -11.5,16 17 18 -12.5)))");
            }
        }
    }

    SECTION("operators")
    {
        SECTION("equal to - operator")
        {
            auto mpg1 = MultiPolygon{
                Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}}},
                Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}}};
            auto mpg2 = MultiPolygon{
                Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}}},
                Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}}};
            CHECK(mpg1 == mpg2);
        }

        SECTION("not equal to - operator")
        {
            auto mpg1 = MultiPolygon{
                Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}}},
                Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}}};
            auto mpg2 = MultiPolygon{
                Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}}},
                Polygon{{{11.0, 12.0}, {13.0, 14.0}, {20.0, 17.0}}}};
            CHECK(mpg1 != mpg2);
        }
    }

    SECTION("index operator")
    {
        SECTION("xy - index operator")
        {
            auto mpg = MultiPolygon{
                Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}}},
                Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}}};
            auto& p1 = mpg[0][0][0];
            CHECK(p1.geom_type() == geometry_type::POINT);
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);

            auto& p2 = mpg[1][0][2];
            CHECK(p2.geom_type() == geometry_type::POINT);
            CHECK(p2.x == 16.0);
            CHECK(p2.y == 17.0);
        }

        SECTION("xyzm - index operator")
        {
            auto mpg = MultiPolygonZM{
                PolygonZM{{{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}}},
                PolygonZM{{{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}}};
            auto& p1 = mpg[0][0][0];
            CHECK(p1.geom_type() == geometry_type::POINTZM);
            CHECK(p1.x == 1.0);
            CHECK(p1.y == 2.0);
            CHECK(p1.z == 3.0);
            CHECK(p1.m == -1.5);

            auto& p2 = mpg[1][0][2];
            CHECK(p2.geom_type() == geometry_type::POINTZM);
            CHECK(p2.x == 16.0);
            CHECK(p2.y == 17.0);
            CHECK(p2.z == 18.0);
            CHECK(p2.m == -12.5);
        }
    }

    SECTION("coords")
    {
        auto flatten = [](const auto& multipolygon) {
            std::vector<std::vector<double>> coords;
            for (const auto& polygon : multipolygon)
            {
                for (const auto& ring : polygon)
                {
                    for (const auto& point : ring)
                    {
                        coords.emplace_back(point.begin(), point.end());
                    }
                }
            }
            return coords;
        };

        SECTION("xy - coords")
        {
            auto mpg = MultiPolygon{
                Polygon{{{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}}},
                Polygon{{{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}}};
            auto coords = flatten(mpg);
            CHECK(coords.size() == 6);
            CHECK(coords[0].size() == 2);
            CHECK(coords[0][0] == 1.0);
            CHECK(coords[0][1] == 2.0);
            CHECK(coords[5][0] == 16.0);
            CHECK(coords[5][1] == 17.0);
        }

        SECTION("xyzm - coords")
        {
            auto mpg = MultiPolygonZM{
                PolygonZM{{{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}}},
                PolygonZM{{{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}}};
            auto coords = flatten(mpg);
            CHECK(coords.size() == 6);
            CHECK(coords[0].size() == 4);
            CHECK(coords[0][0] == 1.0);
            CHECK(coords[0][1] == 2.0);
            CHECK(coords[0][2] == 3.0);
            CHECK(coords[0][3] == -1.5);
            CHECK(coords[5][0] == 16.0);
            CHECK(coords[5][1] == 17.0);
            CHECK(coords[5][2] == 18.0);
            CHECK(coords[5][3] == -12.5);
        }
    }
}
