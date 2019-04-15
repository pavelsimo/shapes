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
            CHECK(p.type() == GeometryType::POLYGON);
            CHECK(p.detailed_type() == GeometryDetailedType::POLYGON);
            CHECK(p.type_str() == "Polygon");
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
            Polygon p = {
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
            Polygon p = {
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
                /// @todo add test
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
            }

            SECTION("xyz - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON Z ((30 10 -5, 40 40 -5, 20 40 -5, 10 20 -5, 30 10 -5))");
            }

            SECTION("xym - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON M ((30 10 -5, 40 40 -5, 20 40 -5, 10 20 -5, 30 10 -5))");
            }

            SECTION("xyzm - from wkt")
            {
                auto p = Polygon::from_wkt("POLYGON ZM ((30 10 -5 2, 40 40 -5 2, 20 40 -5 2, 10 20 -5 2, 30 10 -5 2))");
            }

            SECTION("empty - from wkt")
            {
                SECTION("empty - xy")
                {
                    /// @todo add test
                }

                SECTION("empty - xyz")
                {
                    /// @todo add test
                }

                SECTION("empty - xym")
                {
                    /// @todo add test
                }

                SECTION("empty - xyzm")
                {
                    /// @todo add test
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
                /// @todo add test
            }

            SECTION("xyz - to json")
            {
                /// @todo add test
            }

            SECTION("xym - to json")
            {
                /// @todo add test
            }

            SECTION("xyzm - to json")
            {
                /// @todo add test
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                /// @todo add test
            }

            SECTION("xyz - to wkt")
            {
                /// @todo add test
            }

            SECTION("xym - to wkt")
            {
                /// @todo add test
            }

            SECTION("xyzm - to wkt")
            {
                /// @todo add test
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

