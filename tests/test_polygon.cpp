#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Polygon")
{
    SECTION("constructors")
    {
        SECTION("empty")
        {
            Polygon p;
            CHECK(p.empty());
            CHECK(p.size() == 0);
            CHECK(p.geom_type() == GeometryType::POLYGON);
            CHECK(p.geom_type_dim() == GeometryType::POLYGON);
            CHECK(p.geom_type_str() == "Polygon");
        }

        SECTION("xy - constructor")
        {
            /// @todo add test
        }

        SECTION("xyz - constructor")
        {
            /// @todo add test
        }

        SECTION("xym - constructor")
        {
            // not supported
        }

        SECTION("xyzm - constructor")
        {
            /// @todo add test
        }

        SECTION("xy shell - initializer list")
        {
            auto p = Polygon{
                {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}  // shell
            };
            CHECK(p.exterior[0].x == 1);
            CHECK(p.exterior[0].y == 2);
            CHECK(p.exterior[0].z == 3);
            CHECK(p.exterior[1].x == 4);
            CHECK(p.exterior[1].y == 5);
            CHECK(p.exterior[1].z == 6);
        }

        SECTION("xy shell, holes - initializer list")
        {
            auto p = Polygon{
                {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},  // shell
                {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // hole #1
            };
            CHECK(p.exterior[0].x == 1);
            CHECK(p.exterior[0].y == 2);
            CHECK(p.exterior[0].z == 3);
            CHECK(p.exterior[1].x == 4);
            CHECK(p.exterior[1].y == 5);
            CHECK(p.exterior[1].z == 6);

            CHECK(p.interiors.size() == 1);
            LinearRing& interior = p.interiors[0];
            CHECK(interior[0].x == 1);
            CHECK(interior[0].y == 2);
            CHECK(interior[0].z == 3);
            CHECK(interior[1].x == 4);
            CHECK(interior[1].y == 5);
            CHECK(interior[1].z == 6);
            CHECK(interior[2].x == 7);
            CHECK(interior[2].y == 8);
            CHECK(interior[2].z == 9);
            CHECK(interior[3].x == 1);
            CHECK(interior[3].y == 2);
            CHECK(interior[3].z == 3);
        }

        SECTION("xyz - initializer list")
        {
            /// @todo add test
        }

        SECTION("xym - initializer list")
        {
            // not supported
        }

        SECTION("xyzm - initializer list")
        {
            /// @todo add test
        }

        SECTION("throws - initializer list")
        {
            /// @todo add test
        }
    }

    SECTION("from_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - from json")
            {
                std::string json = R"(
                    {
                        "type": "Polygon",
                        "coordinates": [
                            [[35, 10], [45, 45], [15, 40], [10, 20], [35, 10]],
                            [[20, 30], [35, 35], [30, 20], [20, 30]]
                        ]
                    }
                )";
                auto p           = Polygon::from_json(json);
                CHECK(p.size() == 2);
                CHECK(p[0].size() == 5);
                CHECK(p[1].size() == 4);
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.size() == 1);
                CHECK(p.interiors[0].size() == 4);
                CHECK(p.dim == DimensionType::XY);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGON);

                CHECK(p[0][0].x == 35.0);
                CHECK(p[0][0].y == 10.0);
                CHECK(p[1][3].x == 20.0);
                CHECK(p[1][3].y == 30.0);

                CHECK(p[0][0].x == p[0][4].x);
                CHECK(p[0][0].y == p[0][4].y);
                CHECK(p[1][0].x == p[1][3].x);
                CHECK(p[1][0].y == p[1][3].y);
            }

            SECTION("xyz - from json")
            {
                std::string json = R"(
                    {
                        "type": "Polygon",
                        "coordinates": [
                            [[35, 10, 1], [45, 45, 2], [15, 40, 3], [10, 20, 4], [35, 10, 1]],
                            [[20, 30, 4], [35, 35, 3], [30, 20, 2], [20, 30, 4]]
                        ]
                    }
                )";
                auto p           = Polygon::from_json(json);
                CHECK(p.size() == 2);
                CHECK(p[0].size() == 5);
                CHECK(p[1].size() == 4);
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.size() == 1);
                CHECK(p.interiors[0].size() == 4);
                CHECK(p.dim == DimensionType::XYZ);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGONZ);

                CHECK(p[0][0].x == 35.0);
                CHECK(p[0][0].y == 10.0);
                CHECK(p[0][0].z == 1.0);
                CHECK(p[1][3].x == 20.0);
                CHECK(p[1][3].y == 30.0);
                CHECK(p[1][3].z == 4.0);

                CHECK(p[0][0].x == p[0][4].x);
                CHECK(p[0][0].y == p[0][4].y);
                CHECK(p[0][0].z == p[0][4].z);
                CHECK(p[1][0].x == p[1][3].x);
                CHECK(p[1][0].y == p[1][3].y);
                CHECK(p[1][0].z == p[1][3].z);
            }

            SECTION("xym - from json")
            {
                // not supported
            }

            SECTION("xyzm - from json")
            {
                std::string json = R"(
                    {
                        "type": "Polygon",
                        "coordinates": [
                            [[35, 10, 1, 1], [45, 45, 2, 2], [15, 40, 3, 3], [10, 20, 4, 4], [35, 10, 1, 1]],
                            [[20, 30, 4, 4], [35, 35, 3, 3], [30, 20, 2, 2], [20, 30, 4, 4]]
                        ]
                    }
                )";
                auto p           = Polygon::from_json(json);
                CHECK(p.size() == 2);
                CHECK(p[0].size() == 5);
                CHECK(p[1].size() == 4);
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.size() == 1);
                CHECK(p.interiors[0].size() == 4);
                CHECK(p.dim == DimensionType::XYZM);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGONZM);

                CHECK(p[0][0].x == 35.0);
                CHECK(p[0][0].y == 10.0);
                CHECK(p[0][0].z == 1.0);
                CHECK(p[0][0].m == 1.0);
                CHECK(p[1][3].x == 20.0);
                CHECK(p[1][3].y == 30.0);
                CHECK(p[1][3].z == 4.0);
                CHECK(p[1][3].m == 4.0);

                CHECK(p[0][0].x == p[0][4].x);
                CHECK(p[0][0].y == p[0][4].y);
                CHECK(p[0][0].z == p[0][4].z);
                CHECK(p[0][0].m == p[0][4].m);
                CHECK(p[1][0].x == p[1][3].x);
                CHECK(p[1][0].y == p[1][3].y);
                CHECK(p[1][0].z == p[1][3].z);
                CHECK(p[1][0].m == p[1][3].m);
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))");
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.empty());
                CHECK(p.dim == DimensionType::XY);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGON);
                CHECK(p.exterior[0].x == 30);
                CHECK(p.exterior[0].y == 10);
                CHECK(p.exterior[1].x == 40);
                CHECK(p.exterior[1].y == 40);
                CHECK(p.exterior[2].x == 20);
                CHECK(p.exterior[2].y == 40);
                CHECK(p.exterior[3].x == 10);
                CHECK(p.exterior[3].y == 20);
                CHECK(p.exterior[4].x == 30);
                CHECK(p.exterior[4].y == 10);
            }

            SECTION("xyz - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON Z ((30 10 -5, 40 40 -15, 20 40 -25, 10 20 -35, 30 10 -45))");
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.empty());
                CHECK(p.dim == DimensionType::XYZ);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGONZ);
                CHECK(p.exterior[0].x == 30);
                CHECK(p.exterior[0].y == 10);
                CHECK(p.exterior[0].z == -5);
                CHECK(p.exterior[1].x == 40);
                CHECK(p.exterior[1].y == 40);
                CHECK(p.exterior[1].z == -15);
                CHECK(p.exterior[2].x == 20);
                CHECK(p.exterior[2].y == 40);
                CHECK(p.exterior[2].z == -25);
                CHECK(p.exterior[3].x == 10);
                CHECK(p.exterior[3].y == 20);
                CHECK(p.exterior[3].z == -35);
                CHECK(p.exterior[4].x == 30);
                CHECK(p.exterior[4].y == 10);
                CHECK(p.exterior[4].z == -45);
            }

            SECTION("xym - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON M ((30 10 -5, 40 40 -15, 20 40 -25, 10 20 -35, 30 10 -45))");
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.empty());
                CHECK(p.dim == DimensionType::XYM);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGONM);
                CHECK(p.exterior[0].x == 30);
                CHECK(p.exterior[0].y == 10);
                CHECK(p.exterior[0].m == -5);
                CHECK(p.exterior[1].x == 40);
                CHECK(p.exterior[1].y == 40);
                CHECK(p.exterior[1].m == -15);
                CHECK(p.exterior[2].x == 20);
                CHECK(p.exterior[2].y == 40);
                CHECK(p.exterior[2].m == -25);
                CHECK(p.exterior[3].x == 10);
                CHECK(p.exterior[3].y == 20);
                CHECK(p.exterior[3].m == -35);
                CHECK(p.exterior[4].x == 30);
                CHECK(p.exterior[4].y == 10);
                CHECK(p.exterior[4].m == -45);
            }

            SECTION("xyzm - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON ZM ((30 10 -5 20, 40 40 -15 200, 20 40 -25 2000, 10 20 -35 20000, 30 10 -45 200000))");
                CHECK(p.exterior.size() == 5);
                CHECK(p.interiors.empty());
                CHECK(p.dim == DimensionType::XYZM);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGONZM);
                CHECK(p.exterior[0].x == 30);
                CHECK(p.exterior[0].y == 10);
                CHECK(p.exterior[0].z == -5);
                CHECK(p.exterior[0].m == 20);
                CHECK(p.exterior[1].x == 40);
                CHECK(p.exterior[1].y == 40);
                CHECK(p.exterior[1].z == -15);
                CHECK(p.exterior[1].m == 200);
                CHECK(p.exterior[2].x == 20);
                CHECK(p.exterior[2].y == 40);
                CHECK(p.exterior[2].z == -25);
                CHECK(p.exterior[2].m == 2000);
                CHECK(p.exterior[3].x == 10);
                CHECK(p.exterior[3].y == 20);
                CHECK(p.exterior[3].z == -35);
                CHECK(p.exterior[3].m == 20000);
                CHECK(p.exterior[4].x == 30);
                CHECK(p.exterior[4].y == 10);
                CHECK(p.exterior[4].z == -45);
                CHECK(p.exterior[4].m == 200000);
            }

            SECTION("empty - from wkt")
            {
                SECTION("empty - xy")
                {
                    auto ml = Polygon::from_wkt("Polygon EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::POLYGON);
                    CHECK(ml.dim == DimensionType::XY);
                }

                SECTION("empty - xyz")
                {
                    auto ml = Polygon::from_wkt("Polygon Z EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::POLYGONZ);
                    CHECK(ml.dim == DimensionType::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto ml = Polygon::from_wkt("Polygon M EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::POLYGONM);
                    CHECK(ml.dim == DimensionType::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto ml = Polygon::from_wkt("Polygon ZM EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::POLYGONZM);
                    CHECK(ml.dim == DimensionType::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(Polygon::from_wkt("polygon ((35 10, 45 45, 15 40, 10 20, 35 10), (20 30, 35 35, 30 20, 20 30))"));
                CHECK_NOTHROW(Polygon::from_wkt("polygon z ((35 10 -20, 45 45 -20, 15 40 -20, 10 20 -20, 35 10 -20), (20 30 -20, 35 35 -20, 30 20 -20, 20 30 -3010.5))"));
                CHECK_NOTHROW(Polygon::from_wkt("polygon m ((35 10 -20, 45 45 -20, 15 40 -20, 10 20 -20, 35 10 -20), (20 30 -20, 35 35 -20, 30 20 -20, 20 30 -3010.5))"));
                CHECK_NOTHROW(Polygon::from_wkt("polygon zm ((35 10 -20 -0.5, 45 45 -20 -0.5, 15 40 -20 -0.5, 10 20 -20 -0.5, 35 10 -20 -0.5), (20 30 -20 -0.5, 35 35 -20 -0.5, 30 20 -20 -0.5, 20 30 -3010.5 -0.5))"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(Polygon::from_wkt("polygon ((35 10, 45 45, 15 40, 11.11.11 20, 35 10), (20 30, 35 35, 30 20, 20 30.2.2))"));
                CHECK_THROWS(Polygon::from_wkt("polygon 35 10, 45 45, 15 40, 11.11.11 20, 35 10, 20 30, 35 35, 30 20, 20 30.2.2"));
                CHECK_THROWS(Polygon::from_wkt("polygon z ((35 10 -20, 45 45 -20, 15 40 -20, 10 20 -20, 35 10 -20), (20 30 -20, 35 35 -20, 30 20 -20, 20 30 -3010.5)) @@"));
                CHECK_THROWS(Polygon::from_wkt("polygon zm ((35 10, 45 45, 15 40, 10 20, 35 10), (20 30, 35 35, 30 20, 20 30))"));
                CHECK_THROWS(Polygon::from_wkt("polygon z ((35 10, 45 45, 15 40, 10 20, 35 10), (20 30, 35 35, 30 20, 20 30))"));
            }
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                auto p = Polygon{
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}},  // shell
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}}   // hole #1
                };
                CHECK(p.json() == R"({"type":"Polygon","coordinates":[[[1.0,2.0],[4.0,5.0],[7.0,8.0],[1.0,2.0]],[[1.0,2.0],[4.0,5.0],[7.0,8.0],[1.0,2.0]]]})");
            }

            SECTION("xyz - to json")
            {
                auto p = Polygon{
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},  // shell
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // hole #1
                };
                CHECK(p.json() == R"({"type":"Polygon","coordinates":[[[1.0,2.0,3.0],[4.0,5.0,6.0],[7.0,8.0,9.0],[1.0,2.0,3.0]],[[1.0,2.0,3.0],[4.0,5.0,6.0],[7.0,8.0,9.0],[1.0,2.0,3.0]]]})");
            }

            SECTION("xym - to json")
            {
                /// @todo add test
            }

            SECTION("xyzm - to json")
            {
                auto p = Polygon{
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}},  // shell
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}}   // hole #1
                };
                CHECK(p.json() == R"({"type":"Polygon","coordinates":[[[1.0,2.0,3.0,-1.0],[4.0,5.0,6.0,-5.0],[7.0,8.0,9.0,-5.0],[1.0,2.0,3.0,-1.0]],[[1.0,2.0,3.0,-1.0],[4.0,5.0,6.0,-5.0],[7.0,8.0,9.0,-5.0],[1.0,2.0,3.0,-1.0]]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                auto p = Polygon{
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}},  // shell
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}}   // hole #1
                };
                CHECK(p.wkt() == "POLYGON((1.0 2.0,4.0 5.0,7.0 8.0,1.0 2.0),(1.0 2.0,4.0 5.0,7.0 8.0,1.0 2.0))");
            }

            SECTION("xyz - to wkt")
            {
                auto p = Polygon{
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},  // shell
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // hole #1
                };
                CHECK(p.wkt() == "POLYGONZ((1.0 2.0 3.0,4.0 5.0 6.0,7.0 8.0 9.0,1.0 2.0 3.0),(1.0 2.0 3.0,4.0 5.0 6.0,7.0 8.0 9.0,1.0 2.0 3.0))");
            }

            SECTION("xym - to wkt")
            {
                /// @todo add test
            }

            SECTION("xyzm - to wkt")
            {
                auto p = Polygon{
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}},  // shell
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}}   // hole #1
                };
                CHECK(p.wkt() == "POLYGONZM((1.0 2.0 3.0 -1.0,4.0 5.0 6.0 -5.0,7.0 8.0 9.0 -5.0,1.0 2.0 3.0 -1.0),(1.0 2.0 3.0 -1.0,4.0 5.0 6.0 -5.0,7.0 8.0 9.0 -5.0,1.0 2.0 3.0 -1.0))");
            }
        }
    }

    SECTION("operators")
    {
        SECTION("equal to - operator")
        {
            SECTION("xy - equal to")
            {
                auto p1 = Polygon{
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}},  // shell
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}}   // hole #1
                };
                auto p2 = Polygon{
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}},  // shell
                    {{1, 2}, {4, 5}, {7, 8}, {1, 2}}   // hole #1
                };
                CHECK(p1 == p2);
            }

            SECTION("xyz - equal to")
            {
                auto p1 = Polygon{
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},  // shell
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // hole #1
                };
                auto p2 = Polygon{
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},  // shell
                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // hole #1
                };
                CHECK(p1 == p2);
            }

            SECTION("xym - equal to")
            {
                /// @todo add test
            }

            SECTION("xyzm - equal to")
            {
                auto p1 = Polygon{
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}},  // shell
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}}   // hole #1
                };
                auto p2 = Polygon{
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}},  // shell
                    {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}}   // hole #1
                };
                CHECK(p1 == p2);
            }
        }

        SECTION("not equal to - operator")
        {
            SECTION("xy - not equal to")
            {
                auto p1 = Polygon{
                        {{1, 2}, {4, 5}, {7, 8}, {100, 2}},  // shell
                        {{1, 2}, {4, 5}, {7, 8}, {1, 2}}     // hole #1
                };
                auto p2 = Polygon{
                        {{1, 2}, {4, 5}, {7, 8}, {1, 2}},    // shell
                        {{1, 2}, {4, 5}, {700, 8}, {1, 2}}   // hole #1
                };
                CHECK(p1 != p2);
            }

            SECTION("xyz - not equal to")
            {
                auto p1 = Polygon{
                        {{1, 2, 3}, {4, 500, 6}, {7, 8, 9}, {1, 2, 3}},  // shell
                        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // hole #1
                };
                auto p2 = Polygon{
                        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},    // shell
                        {{1, 2, 3}, {4, 5, 6}, {7, 800, 9}, {1, 2, 3}}   // hole #1
                };
                CHECK(p1 != p2);
            }

            SECTION("xym - not equal to")
            {
                /// @todo add test
            }

            SECTION("xyzm - not equal to")
            {
                auto p1 = Polygon{
                        {{1, 2, 3, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}},  // shell
                        {{1, 2, 3, -1}, {4, 6, 5, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}}   // hole #1
                };
                auto p2 = Polygon{
                        {{1, 2, 3, -1}, {4, 5, 6, -5}, {8, 7, 9, -5}, {1, 2, 3, -1}},  // shell
                        {{1, 3, 2, -1}, {4, 5, 6, -5}, {7, 8, 9, -5}, {1, 2, 3, -1}}   // hole #1
                };
                CHECK(p1 != p2);
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                auto pg = Polygon{
                        {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                        {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                auto& p1 = pg[0][0];
                CHECK(p1.geom_type_dim() == GeometryType::POINT);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);

                auto& p2 = pg[1][2];
                CHECK(p2.geom_type_dim() == GeometryType::POINT);
                CHECK(p2.x == 16.0);
                CHECK(p2.y == 17.0);
            }

            SECTION("xyz - index operator")
            {
                auto pg = Polygon{
                        {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                        {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                auto& p1 = pg[0][0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);

                auto& p2 = pg[0][2];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p2.x == 7.0);
                CHECK(p2.y == 8.0);
                CHECK(p2.z == 9.0);

                auto& p3 = pg[1][2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p3.x == 16.0);
                CHECK(p3.y == 17.0);
                CHECK(p3.z == 18.0);
            }

            SECTION("xym - index operator")
            {
                /// @todo add test
            }

            SECTION("xyzm - index operator")
            {
                auto pg = Polygon{
                        {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                        {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                auto& p1 = pg[0][0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -1.5);

                auto& p2 = pg[0][2];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p2.x == 7.0);
                CHECK(p2.y == 8.0);
                CHECK(p2.z == 9.0);
                CHECK(p2.m == -3.5);

                auto& p3 = pg[1][2];
                CHECK(p3.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p3.x == 16.0);
                CHECK(p3.y == 17.0);
                CHECK(p3.z == 18.0);
                CHECK(p3.m == -12.5);
            }
        }
    }

    SECTION("coords")
    {
        SECTION("xy - coords")
        {
            auto p = Polygon{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
            auto coords = p.coords();
            CHECK(coords.size() == 6);
            double x, y;
            x = coords[0][0];
            y = coords[0][1];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            x = coords[1][0];
            y = coords[1][1];
            CHECK(x == 4.0);
            CHECK(y == 5.0);
            x = coords[2][0];
            y = coords[2][1];
            CHECK(x == 7.0);
            CHECK(y == 8.0);
            x = coords[3][0];
            y = coords[3][1];
            CHECK(x == 11.0);
            CHECK(y == 12.0);
            x = coords[4][0];
            y = coords[4][1];
            CHECK(x == 13.0);
            CHECK(y == 14.0);
            x = coords[5][0];
            y = coords[5][1];
            CHECK(x == 16.0);
            CHECK(y == 17.0);
        }

        SECTION("xyz - coords")
        {
            auto p = Polygon{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
            auto coords = p.coords();
            CHECK(coords.size() == 6);
            double x, y, z;
            x = coords[0][0];
            y = coords[0][1];
            z = coords[0][2];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == 3.0);
            x = coords[1][0];
            y = coords[1][1];
            z = coords[1][2];
            CHECK(x == 4.0);
            CHECK(y == 5.0);
            CHECK(z == 6.0);
            x = coords[2][0];
            y = coords[2][1];
            z = coords[2][2];
            CHECK(x == 7.0);
            CHECK(y == 8.0);
            CHECK(z == 9.0);
            x = coords[3][0];
            y = coords[3][1];
            z = coords[3][2];
            CHECK(x == 11.0);
            CHECK(y == 12.0);
            CHECK(z == 13.0);
            x = coords[4][0];
            y = coords[4][1];
            z = coords[4][2];
            CHECK(x == 13.0);
            CHECK(y == 14.0);
            CHECK(z == 15.0);
            x = coords[5][0];
            y = coords[5][1];
            z = coords[5][2];
            CHECK(x == 16.0);
            CHECK(y == 17.0);
            CHECK(z == 18.0);
        }

        SECTION("xym - coords")
        {
            /// @todo add test
        }

        SECTION("xyzm - coords")
        {
            auto ml = Polygon{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
            auto coords = ml.coords();
            CHECK(coords.size() == 6);
            double x, y, z, m;
            x = coords[0][0];
            y = coords[0][1];
            z = coords[0][2];
            m = coords[0][3];
            CHECK(x == 1.0);
            CHECK(y == 2.0);
            CHECK(z == 3.0);
            CHECK(m == -1.5);
            x = coords[1][0];
            y = coords[1][1];
            z = coords[1][2];
            m = coords[1][3];
            CHECK(x == 4.0);
            CHECK(y == 5.0);
            CHECK(z == 6.0);
            CHECK(m == -2.5);
            x = coords[2][0];
            y = coords[2][1];
            z = coords[2][2];
            m = coords[2][3];
            CHECK(x == 7.0);
            CHECK(y == 8.0);
            CHECK(z == 9.0);
            CHECK(m == -3.5);
            x = coords[3][0];
            y = coords[3][1];
            z = coords[3][2];
            m = coords[3][3];
            CHECK(x == 11.0);
            CHECK(y == 12.0);
            CHECK(z == 13.0);
            CHECK(m == -10.5);
            x = coords[4][0];
            y = coords[4][1];
            z = coords[4][2];
            m = coords[4][3];
            CHECK(x == 13.0);
            CHECK(y == 14.0);
            CHECK(z == 15.0);
            CHECK(m == -11.5);
            x = coords[5][0];
            y = coords[5][1];
            z = coords[5][2];
            m = coords[5][3];
            CHECK(x == 16.0);
            CHECK(y == 17.0);
            CHECK(z == 18.0);
            CHECK(m == -12.5);
        }
    }
}
