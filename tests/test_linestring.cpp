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
                auto mp = LineString::from_wkt("LINESTRING(1.4 2.3, 3.2 4.1)");
                CHECK(not mp.empty());
                CHECK(mp.detailed_type() == GeometryDetailedType::LINESTRING);
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
                /// @todo add test
            }

            SECTION("xyzm - from wkt")
            {
                /// @todo add test
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
