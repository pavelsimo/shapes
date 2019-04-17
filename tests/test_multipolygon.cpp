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
            /// @todo add test
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

        SECTION("xy - initializer list")
        {
            /// @todo add test
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
                auto mp = MultiPolygon::from_wkt("MULTIPOLYGON (((40 40, 20 45, 45 30, 40 40)), ((20 35, 10 30, 10 10, 30 5, 45 20, 20 35), (30 20, 20 15, 20 25, 30 20)))");
            }

            SECTION("xyz - from wkt")
            {
                auto mp = MultiPolygon::from_wkt("MULTIPOLYGON Z (((40 40 10, 20 45 10, 45 30 10, 40 40 10)), ((20 35 10, 10 30 10, 10 10 10, 30 5 10, 45 20 10, 20 35 10), (30 20 10, 20 15 10, 20 25 10, 30 20 10)))");
            }

            SECTION("xyzm - from wkt")
            {
                auto mp = MultiPolygon::from_wkt("MULTIPOLYGON ZM (((40 40 10 -5, 20 45 10 -5, 45 30 10 -5, 40 40 10 -5)), ((20 35 10 -5, 10 30 10 -5, 10 10 10 -5, 30 5 10 -5, 45 20 10 -5, 20 35 10 -5), (30 20 10 -5, 20 15 10 -5, 20 25 10 -5, 30 20 10 -5)))");
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
