#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPolygon")
{
    SECTION("constructors")
    {
        SECTION("empty")
        {
            MultiPolygon ml;
            CHECK(ml.empty());
            CHECK(ml.dim() == dimension_type::XY);
            CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
            CHECK(ml.tagged_text() == "MultiPolygon");
        }

        SECTION("xy - linearRing vector")
        {
            std::vector<Polygon> polygons = {
                {
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}, {1.0, 2.0}},         // exterior
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}, {11.0, 12.0}}  // interior #1
                },
                {
                    {{100.0, 200.0}, {4.0, 5.0}, {7.0, 8.0}, {100.0, 200.0}},                 // exterior
                    {{1100.0, 1200.0}, {1300.0, 1400.0}, {1600.0, 1700.0}, {1100.0, 1200.0}}  // interior #1
                }};

            MultiPolygon mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XY);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGON);
            CHECK(mpg.tagged_text() == "MultiPolygon");

            /// polygon 1 -> exterior -> point 1
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);

            /// polygon 2 -> exterior -> point 1
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
        }

        SECTION("xyz - linearRing vector")
        {
            std::vector<PolygonZ> polygons = {
                {
                    {{1.0, 2.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {1.0, 2.0, -1.0}},         // exterior
                    {{11.0, 12.0, -1.0}, {13.0, 14.0, -1.0}, {16.0, 17.0, -1.0}, {11.0, 12.0, -1.0}}  // interior #1
                },
                {
                    {{100.0, 200.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {100.0, 200.0, -1.0}},                 // exterior
                    {{1100.0, 1200.0, -1.0}, {1300.0, 1400.0, -1.0}, {1600.0, 1700.0, -1.0}, {1100.0, 1200.0, -1.0}}  // interior #1
                }};

            MultiPolygonZ mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYZ);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZ);

            /// polygon 1 -> exterior -> point 1
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].z == -1.0);

            /// polygon 2 -> exterior -> point 1
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
            CHECK(mpg[1][0][0].z == -1.0);
        }

        SECTION("xym - linearRing vector")
        {
            std::vector<PolygonM> polygons = {
                {
                    {{1.0, 2.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {1.0, 2.0, -1.0}},         // exterior
                    {{11.0, 12.0, -1.0}, {13.0, 14.0, -1.0}, {16.0, 17.0, -1.0}, {11.0, 12.0, -1.0}}  // interior #1
                },
                {
                    {{100.0, 200.0, -1.0}, {4.0, 5.0, -1.0}, {7.0, 8.0, -1.0}, {100.0, 200.0, -1.0}},                 // exterior
                    {{1100.0, 1200.0, -1.0}, {1300.0, 1400.0, -1.0}, {1600.0, 1700.0, -1.0}, {1100.0, 1200.0, -1.0}}  // interior #1
                }};

            MultiPolygonM mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYM);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONM);

            /// polygon 1 -> exterior -> point 1
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].m == -1.0);

            /// polygon 2 -> exterior -> point 1
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
            CHECK(mpg[1][0][0].m == -1.0);
        }

        SECTION("xyzm - linearRing vector")
        {
            std::vector<PolygonZM> polygons = {
                {
                    {{1.0, 2.0, -1.0, 5}, {4.0, 5.0, -1.0, 5}, {7.0, 8.0, -1.0, 5}, {1.0, 2.0, -1.0, 5}},         // exterior
                    {{11.0, 12.0, -1.0, 5}, {13.0, 14.0, -1.0, 5}, {16.0, 17.0, -1.0, 5}, {11.0, 12.0, -1.0, 5}}  // interior #1
                },
                {
                    {{100.0, 200.0, -1.0, 5}, {4.0, 5.0, -1.0, 5}, {7.0, 8.0, -1.0, 5}, {100.0, 200.0, -1.0, 5}},                 // exterior
                    {{1100.0, 1200.0, -1.0, 5}, {1300.0, 1400.0, -1.0, 5}, {1600.0, 1700.0, -1.0, 5}, {1100.0, 1200.0, -1.0, 5}}  // interior #1
                }};

            MultiPolygonZM mpg(polygons.begin(), polygons.end());
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYZM);
            CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONZM);

            /// polygon 1 -> exterior -> point 1
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].z == -1.0);
            CHECK(mpg[0][0][0].m == 5.0);

            /// polygon 2 -> exterior -> point 1
            CHECK(mpg[1][0][0].x == 100.0);
            CHECK(mpg[1][0][0].y == 200.0);
            CHECK(mpg[1][0][0].z == -1.0);
            CHECK(mpg[1][0][0].m == 5.0);
        }

        SECTION("xy - initializer list")
        {
            auto mpg = MultiPolygon{
                {
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},       // exterior
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}  // interior #1
                },
                {
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},       // exterior
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}  // interior #1
                }};
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XY);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[1][1][2].x == 16.0);
            CHECK(mpg[1][1][2].y == 17.0);
            CHECK(mpg[0].exterior().size() == 3);
            CHECK(mpg[0].interiors(0).size() == 3);
        }

        SECTION("xyz - initializer list")
        {
            auto mpg = MultiPolygonZ{
                {
                    {{1.0, 2.0, -1}, {4.0, 5.0, -1}, {7.0, 8.0, -1}},       // exterior
                    {{11.0, 12.0, -1}, {13.0, 14.0, -1}, {16.0, 17.0, -1}}  // interior #1
                },
                {
                    {{1.0, 2.0, -1}, {4.0, 5.0, -1}, {7.0, 8.0, -1}},       // exterior
                    {{11.0, 12.0, -1}, {13.0, 14.0, -1}, {16.0, 17.0, -1}}  // interior #1
                }};
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYZ);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].z == -1.0);
            CHECK(mpg[1][1][2].x == 16.0);
            CHECK(mpg[1][1][2].y == 17.0);
            CHECK(mpg[1][1][2].z == -1.0);
            CHECK(mpg[0].exterior().size() == 3);
            CHECK(mpg[0].interiors(0).size() == 3);
        }

        SECTION("xym - initializer list")
        {
            auto mpg = MultiPolygonM{
                {
                    {{1.0, 2.0, -1}, {4.0, 5.0, -1}, {7.0, 8.0, -1}},       // exterior
                    {{11.0, 12.0, -1}, {13.0, 14.0, -1}, {16.0, 17.0, -1}}  // interior #1
                },
                {
                    {{1.0, 2.0, -1}, {4.0, 5.0, -1}, {7.0, 8.0, -1}},       // exterior
                    {{11.0, 12.0, -1}, {13.0, 14.0, -1}, {16.0, 17.0, -1}}  // interior #1
                }};
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYM);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].m == -1.0);
            CHECK(mpg[1][1][2].x == 16.0);
            CHECK(mpg[1][1][2].y == 17.0);
            CHECK(mpg[1][1][2].m == -1.0);
            CHECK(mpg[0].exterior().size() == 3);
            CHECK(mpg[0].interiors(0).size() == 3);
        }

        SECTION("xyzm - initializer list")
        {
            auto mpg = MultiPolygonZM{
                {
                    {{1.0, 2.0, -1, 5}, {4.0, 5.0, -1, 5}, {7.0, 8.0, -1, 5}},       // exterior
                    {{11.0, 12.0, -1, 5}, {13.0, 14.0, -1, 5}, {16.0, 17.0, -1, 5}}  // interior #1
                },
                {
                    {{1.0, 2.0, -1, 5}, {4.0, 5.0, -1, 5}, {7.0, 8.0, -1, 5}},       // exterior
                    {{11.0, 12.0, -1, 5}, {13.0, 14.0, -1, 5}, {16.0, 17.0, -1, 5}}  // interior #1
                }};
            CHECK(mpg.size() == 2);
            CHECK(mpg.dim() == dimension_type::XYZM);
            CHECK(mpg[0][0][0].x == 1.0);
            CHECK(mpg[0][0][0].y == 2.0);
            CHECK(mpg[0][0][0].z == -1.0);
            CHECK(mpg[0][0][0].m == 5.0);
            CHECK(mpg[1][1][2].x == 16.0);
            CHECK(mpg[1][1][2].y == 17.0);
            CHECK(mpg[1][1][2].z == -1.0);
            CHECK(mpg[1][1][2].m == 5.0);
            CHECK(mpg[0].exterior().size() == 3);
            CHECK(mpg[0].interiors(0).size() == 3);

            for (const auto& polygon : mpg)
            {
                for (const auto& ring : polygon)
                {
                    for (const auto& p : ring)
                    {
                        CHECK(p.geom_type() == geometry_type::POINTZM);
                        for (const auto& coord: p)
                        {
                            std::cout << coord << " ";
                        }
                        std::cout << "\n";
                    }
                }
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
                    auto mpg = MultiPolygonZ::from_wkt(R"(MULTIPOLYGON M (((40 40 1, 20 45 2, 45 30 3, 40 40 4)),((20 35 1, 10 30 2, 10 10 3, 30 5 4, 45 20 5, 20 35 6),(30 20 1, 20 15 2, 20 25 3, 30 20 4))))");
                    CHECK(mpg.size() == 3);
                    CHECK(mpg.dim() == dimension_type::XYM);
                    CHECK(mpg.geom_type() == geometry_type::MULTIPOLYGONM);
                    CHECK(mpg[0][0][0].x == 40.0);
                    CHECK(mpg[0][0][0].y == 40.0);
                    CHECK(mpg[0][0][0].z == 1.0);
                    CHECK(mpg[1][0][0].x == 20.0);
                    CHECK(mpg[1][0][0].y == 35.0);
                    CHECK(mpg[1][0][0].z == 1.0);
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
//                    std::string json = R"({
//                                            "type": "MultiPolygon",
//                                                    "coordinates": [
//                                            [[10, 35], [20, 20], [10, 40]],
//                                            [[40, 40], [30, 30], [40, 20], [30, 5]]
//                                            ]
//                                        })";
//                    auto ml          = MultiPolygon::from_json(json);
//                    CHECK(ml.size() == 2);
//                    CHECK(ml.dim() == dimension_type::XY);
//                    CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
//                    CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
//                    CHECK(ml[0][0][0].x == 10.0);
//                    CHECK(ml[0][0][0].y == 35.0);
//                    CHECK(ml[0][1][3].x == 30.0);
//                    CHECK(ml[0][1][3].y == 5.0);
                }
            }
        }
    }

    //    SECTION("from_... methods")
    //    {
    //        SECTION("json")
    //        {
    //            SECTION("xy - from json")
    //            {
    //                std::string json = R"(
    //                                {
    //                                    "type": "MultiPolygon",
    //                                            "coordinates": [
    //                                    [[10, 35], [20, 20], [10, 40]],
    //                                    [[40, 40], [30, 30], [40, 20], [30, 5]]
    //                                    ]
    //                                }
    //                                )";
    //                auto ml          = MultiPolygon::from_json(json);
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XY);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
    //                CHECK(ml[0][0].x == 10.0);
    //                CHECK(ml[0][0].y == 35.0);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == 5.0);
    //            }
    //
    //            SECTION("xyz - from json")
    //            {
    //                std::string json = R"(
    //                                {
    //                                    "type": "MultiPolygon",
    //                                            "coordinates": [
    //                                    [[10, 35, -10], [20, 20, -10], [10, 40, -10]],
    //                                    [[40, 40, -20], [30, 30, -20], [40, 20, -20], [30, 5, -20]]
    //                                    ]
    //                                }
    //                                )";
    //                auto ml          = MultiPolygonZ::from_json(json);
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XYZ);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONZ);
    //                CHECK(ml[0][0].x == 10.0);
    //                CHECK(ml[0][0].y == 35.0);
    //                CHECK(ml[0][0].z == -10.0);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == 5.0);
    //                CHECK(ml[1][3].z == -20.0);
    //            }
    //
    //            SECTION("xym - from json")
    //            {
    //                // not supported
    //            }
    //
    //            SECTION("xyzm - from json")
    //            {
    //                std::string json = R"(
    //                                {
    //                                    "type": "MultiPolygon",
    //                                            "coordinates": [
    //                                    [[10, 35, -10, -5], [20, 20, -10, -5], [10, 40, -10, -5]],
    //                                    [[40, 40, -20, -4000], [30, 30, -20, -4000], [40, 20, -20, -4000], [30, 5, -20, -4000]]
    //                                    ]
    //                                }
    //                                )";
    //                auto ml          = MultiPolygonZM::from_json(json);
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XYZM);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONZM);
    //                CHECK(ml[0][0].x == 10.0);
    //                CHECK(ml[0][0].y == 35.0);
    //                CHECK(ml[0][0].z == -10.0);
    //                CHECK(ml[0][0].m == -5.0);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == 5.0);
    //                CHECK(ml[1][3].z == -20.0);
    //                CHECK(ml[1][3].m == -4000.0);
    //            }
    //        }
    //
    //        SECTION("wkt")
    //        {
    //            SECTION("xy - from wkt")
    //            {
    //                auto ml = MultiPolygon::from_wkt("MultiPolygon ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))");
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XY);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
    //                CHECK(ml[0][0].x == 10.0);
    //                CHECK(ml[0][0].y == 35.0);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == 10.0);
    //            }
    //
    //            SECTION("xyz - from wkt")
    //            {
    //                auto ml = MultiPolygonZ::from_wkt("MultiPolygon Z ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))");
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XYZ);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONZ);
    //                CHECK(ml[0][0].x == 10.0);
    //                CHECK(ml[0][0].y == 35.0);
    //                CHECK(ml[0][0].z == -10);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == 10.0);
    //                CHECK(ml[1][3].z == -3010.5);
    //            }
    //
    //            SECTION("xym - from wkt")
    //            {
    //                auto ml = MultiPolygonM::from_wkt("MultiPolygon M ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))");
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XYM);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONM);
    //                CHECK(ml[0][0].x == 10.0);
    //                CHECK(ml[0][0].y == 35.0);
    //                CHECK(ml[0][0].m == -10);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == 10.0);
    //                CHECK(ml[1][3].m == -3010.5);
    //            }
    //
    //            SECTION("xyzm - from wkt")
    //            {
    //                auto ml = MultiPolygonZM::from_wkt("MultiPolygon ZM ((-100 -50 -25 -5, 0.5 1.0 1.5 2.0, 1000 500 250 50), (40 40 40 40, 30 30 30 30, 40 20 20 20, 30 -10 -210 50))");
    //                CHECK(ml.size() == 2);
    //                CHECK(ml.dim() == dimension_type::XYZM);
    //                CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONZM);
    //                CHECK(ml[0][0].x == -100.0);
    //                CHECK(ml[0][0].y == -50.0);
    //                CHECK(ml[0][0].z == -25);
    //                CHECK(ml[0][0].m == -5);
    //                CHECK(ml[1][3].x == 30.0);
    //                CHECK(ml[1][3].y == -10.0);
    //                CHECK(ml[1][3].z == -210);
    //                CHECK(ml[1][3].m == 50);
    //            }
    //
    //            SECTION("empty - from wkt")
    //            {
    //                SECTION("empty - xy")
    //                {
    //                    auto ml = MultiPolygon::from_wkt("MultiPolygon EMPTY");
    //                    CHECK(ml.empty());
    //                    CHECK(ml.geom_type() == geometry_type::MULTIPOLYGON);
    //                    CHECK(ml.dim() == dimension_type::XY);
    //                }
    //
    //                SECTION("empty - xyz")
    //                {
    //                    auto ml = MultiPolygonZ::from_wkt("MultiPolygon Z EMPTY");
    //                    CHECK(ml.empty());
    //                    CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONZ);
    //                    CHECK(ml.dim() == dimension_type::XYZ);
    //                }
    //
    //                SECTION("empty - xym")
    //                {
    //                    auto ml = MultiPolygonM::from_wkt("MultiPolygon M EMPTY");
    //                    CHECK(ml.empty());
    //                    CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONM);
    //                    CHECK(ml.dim() == dimension_type::XYM);
    //                }
    //
    //                SECTION("empty - xyzm")
    //                {
    //                    auto ml = MultiPolygonZM::from_wkt("MultiPolygon ZM EMPTY");
    //                    CHECK(ml.empty());
    //                    CHECK(ml.geom_type() == geometry_type::MULTIPOLYGONZM);
    //                    CHECK(ml.dim() == dimension_type::XYZM);
    //                }
    //            }
    //
    //            SECTION("no throw - from wkt")
    //            {
    //                CHECK_NOTHROW(MultiPolygonM::from_wkt("multiPolygon m ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
    //                CHECK_NOTHROW(MultiPolygonZ::from_wkt("multiPolygon z ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
    //                /// @todo add tests
    //            }
    //
    //            SECTION("throws - from wkt")
    //            {
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon ((10 35, 20 20, 10 40"));
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon ZM ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon ((10 35, 20 20, 10 40)))"));
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon Z ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))"));
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon ZM ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))"));
    //                CHECK_THROWS(MultiPolygon::from_wkt("MultiPolygon M ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))"));
    //                /// @todo add tests
    //            }
    //        }
    //    }
    //
    //    SECTION("to_... methods")
    //    {
    //        SECTION("json")
    //        {
    //            SECTION("xy - to json")
    //            {
    //                auto ml = MultiPolygon{
    //                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //                CHECK(ml.json() == R"({"type":"MultiPolygon","coordinates":[[[1,2],[4,5],[7,8]],[[11,12],[13,14],[16,17]]]})");
    //            }
    //
    //            SECTION("xyz - to json")
    //            {
    //                auto ml = MultiPolygonZ{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                CHECK(ml.json() == R"({"type":"MultiPolygon","coordinates":[[[1,2,3],[4,5,6],[7,8,9]],[[11,12,13],[13,14,15],[16,17,18]]]})");
    //            }
    //
    //            SECTION("xym - to json")
    //            {
    //                auto ml = MultiPolygonM{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                CHECK(ml.json() == R"({"type":"MultiPolygon","coordinates":[[[1,2,3],[4,5,6],[7,8,9]],[[11,12,13],[13,14,15],[16,17,18]]]})");
    //            }
    //
    //            SECTION("xyzm - to json")
    //            {
    //                auto ml = MultiPolygonZM{
    //                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                CHECK(ml.json() == R"({"type":"MultiPolygon","coordinates":[[[1,2,3,-1.5],[4,5,6,-2.5],[7,8,9,-3.5]],[[11,12,13,-10.5],[13,14,15,-11.5],[16,17,18,-12.5]]]})");
    //            }
    //        }
    //
    //        SECTION("wkt")
    //        {
    //            SECTION("xy - to wkt")
    //            {
    //                auto ml = MultiPolygon{
    //                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //                CHECK(ml.wkt() == "MultiPolygon((1 2,4 5,7 8),(11 12,13 14,16 17))");
    //            }
    //
    //            SECTION("xyz - to wkt")
    //            {
    //                auto ml = MultiPolygonZ{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                CHECK(ml.wkt() == "MultiPolygonZ((1 2 3,4 5 6,7 8 9),(11 12 13,13 14 15,16 17 18))");
    //            }
    //
    //            SECTION("xym - to wkt")
    //            {
    //                auto ml = MultiPolygonM{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                CHECK(ml.wkt() == "MultiPolygonM((1 2 3,4 5 6,7 8 9),(11 12 13,13 14 15,16 17 18))");
    //            }
    //
    //            SECTION("xyzm - to wkt")
    //            {
    //                auto ml = MultiPolygonZM{
    //                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                CHECK(ml.wkt() == "MultiPolygonZM((1 2 3 -1.5,4 5 6 -2.5,7 8 9 -3.5),(11 12 13 -10.5,13 14 15 -11.5,16 17 18 -12.5))");
    //            }
    //        }
    //    }
    //
    //    SECTION("operators")
    //    {
    //        SECTION("equal to - operator")
    //        {
    //            SECTION("xy - equal to")
    //            {
    //                auto ml1 = MultiPolygon{
    //                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //                auto ml2 = MultiPolygon{
    //                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //                CHECK(ml1 == ml2);
    //            }
    //
    //            SECTION("xyz - equal to")
    //            {
    //                auto ml1 = MultiPolygonZ{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                auto ml2 = MultiPolygonZ{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                CHECK(ml1 == ml2);
    //            }
    //
    //            SECTION("xym - equal to")
    //            {
    //                auto ml1 = MultiPolygonM{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                auto ml2 = MultiPolygonM{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                CHECK(ml1 == ml2);
    //            }
    //
    //            SECTION("xyzm - equal to")
    //            {
    //                auto ml1 = MultiPolygonZM{
    //                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                auto ml2 = MultiPolygonZM{
    //                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                CHECK(ml1 == ml2);
    //            }
    //        }
    //
    //        SECTION("not equal to - operator")
    //        {
    //            SECTION("xy - not equal to")
    //            {
    //                auto ml1 = MultiPolygon{
    //                    {{5.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 20.0}}};
    //                auto ml2 = MultiPolygon{
    //                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //                CHECK(ml1 != ml2);
    //            }
    //
    //            SECTION("xyz - not equal to")
    //            {
    //                auto ml1 = MultiPolygonZ{
    //                    {{8.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                auto ml2 = MultiPolygonZ{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {26.0, 17.0, 18.0}}};
    //                CHECK(ml1 != ml2);
    //            }
    //
    //            SECTION("xym - not equal to")
    //            {
    //                auto ml1 = MultiPolygonM{
    //                    {{8.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                auto ml2 = MultiPolygonM{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {26.0, 17.0, 18.0}}};
    //                CHECK(ml1 != ml2);
    //            }
    //
    //            SECTION("xyzm - not equal to")
    //            {
    //                auto ml1 = MultiPolygonZM{
    //                    {{1.0, 200.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                auto ml2 = MultiPolygonZM{
    //                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -3.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                CHECK(ml1 != ml2);
    //            }
    //        }
    //
    //        SECTION("index operator")
    //        {
    //            SECTION("xy - index operator")
    //            {
    //                auto ml = MultiPolygon{
    //                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //                auto& p1 = ml[0][0];
    //                CHECK(p1.geom_type() == geometry_type::POINT);
    //                CHECK(p1.x == 1.0);
    //                CHECK(p1.y == 2.0);
    //
    //                auto& p2 = ml[1][2];
    //                CHECK(p2.geom_type() == geometry_type::POINT);
    //                CHECK(p2.x == 16.0);
    //                CHECK(p2.y == 17.0);
    //            }
    //
    //            SECTION("xyz - index operator")
    //            {
    //                auto ml = MultiPolygonZ{
    //                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //                auto& p1 = ml[0][0];
    //                CHECK(p1.geom_type() == geometry_type::POINTZ);
    //                CHECK(p1.x == 1.0);
    //                CHECK(p1.y == 2.0);
    //                CHECK(p1.z == 3.0);
    //
    //                auto& p2 = ml[0][2];
    //                CHECK(p2.geom_type() == geometry_type::POINTZ);
    //                CHECK(p2.x == 7.0);
    //                CHECK(p2.y == 8.0);
    //                CHECK(p2.z == 9.0);
    //
    //                auto& p3 = ml[1][2];
    //                CHECK(p3.geom_type() == geometry_type::POINTZ);
    //                CHECK(p3.x == 16.0);
    //                CHECK(p3.y == 17.0);
    //                CHECK(p3.z == 18.0);
    //            }
    //
    //            SECTION("xym - index operator")
    //            {
    //                /// @todo add test
    //            }
    //
    //            SECTION("xyzm - index operator")
    //            {
    //                auto ml = MultiPolygonZM{
    //                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //                auto& p1 = ml[0][0];
    //                CHECK(p1.geom_type() == geometry_type::POINTZM);
    //                CHECK(p1.x == 1.0);
    //                CHECK(p1.y == 2.0);
    //                CHECK(p1.z == 3.0);
    //                CHECK(p1.m == -1.5);
    //
    //                auto& p2 = ml[0][2];
    //                CHECK(p2.geom_type() == geometry_type::POINTZM);
    //                CHECK(p2.x == 7.0);
    //                CHECK(p2.y == 8.0);
    //                CHECK(p2.z == 9.0);
    //                CHECK(p2.m == -3.5);
    //
    //                auto& p3 = ml[1][2];
    //                CHECK(p3.geom_type() == geometry_type::POINTZM);
    //                CHECK(p3.x == 16.0);
    //                CHECK(p3.y == 17.0);
    //                CHECK(p3.z == 18.0);
    //                CHECK(p3.m == -12.5);
    //            }
    //        }
    //    }
    //
    //    SECTION("coords")
    //    {
    //        SECTION("xy - coords")
    //        {
    //            //            auto ml = MultiPolygon{
    //            //                {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
    //            //                {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
    //            //            auto coords = ml.coords();
    //            //            CHECK(coords.size() == 6);
    //            //
    //            //            double x, y;
    //            //            x = coords[0][0];
    //            //            y = coords[0][1];
    //            //            CHECK(x == 1.0);
    //            //            CHECK(y == 2.0);
    //            //            x = coords[1][0];
    //            //            y = coords[1][1];
    //            //            CHECK(x == 4.0);
    //            //            CHECK(y == 5.0);
    //            //            x = coords[2][0];
    //            //            y = coords[2][1];
    //            //            CHECK(x == 7.0);
    //            //            CHECK(y == 8.0);
    //        }
    //
    //        SECTION("xyz - coords")
    //        {
    //            //            auto ml = MultiPolygon{
    //            //                {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
    //            //                {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
    //            //            auto coords = ml.coords();
    //            //            CHECK(coords.size() == 6);
    //            //
    //            //            double x, y, z;
    //            //            x = coords[0][0];
    //            //            y = coords[0][1];
    //            //            z = coords[0][2];
    //            //            CHECK(x == 1.0);
    //            //            CHECK(y == 2.0);
    //            //            CHECK(z == 3.0);
    //            //            x = coords[1][0];
    //            //            y = coords[1][1];
    //            //            z = coords[1][2];
    //            //            CHECK(x == 4.0);
    //            //            CHECK(y == 5.0);
    //            //            CHECK(z == 6.0);
    //            //            x = coords[2][0];
    //            //            y = coords[2][1];
    //            //            z = coords[2][2];
    //            //            CHECK(x == 7.0);
    //            //            CHECK(y == 8.0);
    //            //            CHECK(z == 9.0);
    //        }
    //
    //        SECTION("xym - coords")
    //        {
    //            /// @todo add test
    //        }
    //
    //        SECTION("xyzm - coords")
    //        {
    //            //            auto ml = MultiPolygon{
    //            //                {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
    //            //                {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
    //            //            auto coords = ml.coords();
    //            //            CHECK(coords.size() == 6);
    //            //
    //            //            double x, y, z, m;
    //            //            x = coords[0][0];
    //            //            y = coords[0][1];
    //            //            z = coords[0][2];
    //            //            m = coords[0][3];
    //            //            CHECK(x == 1.0);
    //            //            CHECK(y == 2.0);
    //            //            CHECK(z == 3.0);
    //            //            CHECK(m == -1.5);
    //            //            x = coords[1][0];
    //            //            y = coords[1][1];
    //            //            z = coords[1][2];
    //            //            m = coords[1][3];
    //            //            CHECK(x == 4.0);
    //            //            CHECK(y == 5.0);
    //            //            CHECK(z == 6.0);
    //            //            CHECK(m == -2.5);
    //            //            x = coords[2][0];
    //            //            y = coords[2][1];
    //            //            z = coords[2][2];
    //            //            m = coords[2][3];
    //            //            CHECK(x == 7.0);
    //            //            CHECK(y == 8.0);
    //            //            CHECK(z == 9.0);
    //            //            CHECK(m == -3.5);
    //        }
}
