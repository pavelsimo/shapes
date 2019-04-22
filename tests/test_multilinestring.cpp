#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiLineString")
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
//                std::string json = R"(
//                {
//                    "type": "MultiLineString",
//                            "coordinates": [
//                    [[10, 10], [20, 20], [10, 40]],
//                    [[40, 40], [30, 30], [40, 20], [30, 10]]
//                    ]
//                }
//                )";
//                auto mls          = MultiLineString::from_json(json);
//                CHECK(mls.size() == 2);
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
                auto mp = MultiLineString::from_wkt("MULTILINESTRING ((10 10, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))");
            }

            SECTION("xyz - from wkt")
            {
                auto mp = MultiLineString::from_wkt("MULTILINESTRING Z ((10 10 10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 10))");
            }

            SECTION("xym - from wkt")
            {
                /// @todo add test
            }

            SECTION("xyzm - from wkt")
            {
                auto mp = MultiLineString::from_wkt("MULTILINESTRING ZM ((10 10 10 10, 20 20 20 20, 10 40 40 40), (40 40 40 40, 30 30 30 30, 40 20 20 20, 30 10 10 10))");
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
