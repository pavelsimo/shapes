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
                CHECK(p.dim == DimensionType::XY);
                CHECK(p.geom_type() == GeometryType::POLYGON);
                CHECK(p.geom_type_dim() == GeometryType::POLYGON);
                CHECK(p[0][0].x == 35.0);
                CHECK(p[0][0].y == 10.0);
                CHECK(p[1][3].x == 20.0);
                CHECK(p[1][3].y == 30.0);
            }

            SECTION("xyz - from json")
            {
                /// @todo add test
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
                /// @todo add test
            }

            SECTION("throws - from wkt")
            {
                /// @todo add test
            }

            SECTION("misc - from wkt")
            {
                /// @todo add test
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
                /// @todo add test
            }

            SECTION("xyz - equal to")
            {
                /// @todo add test
            }

            SECTION("xym - equal to")
            {
                /// @todo add test
            }

            SECTION("xyzm - equal to")
            {
                /// @todo add test
            }
        }

        SECTION("not equal to - operator")
        {
            SECTION("xy - not equal to")
            {
                /// @todo add test
            }

            SECTION("xyz - not equal to")
            {
                /// @todo add test
            }

            SECTION("xym - not equal to")
            {
                /// @todo add test
            }

            SECTION("xyzm - not equal to")
            {
                /// @todo add test
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                /// @todo add test
            }

            SECTION("xyz - index operator")
            {
                /// @todo add test
            }

            SECTION("xym - index operator")
            {
                /// @todo add test
            }

            SECTION("xyzm - index operator")
            {
                /// @todo add test
            }
        }
    }

    SECTION("coordinates tuples")
    {
        SECTION("xy - tuples")
        {
            /// @todo add test
        }

        SECTION("xyz - tuples")
        {
            /// @todo add test
        }

        SECTION("xym - tuples")
        {
            /// @todo add test
        }

        SECTION("xyzm - tuples")
        {
            /// @todo add test
        }
    }
}
