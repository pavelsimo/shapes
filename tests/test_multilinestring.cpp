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
            MultiLineString ml;
            CHECK(ml.empty());
            CHECK(ml.dim == DimensionType::XY);
            CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
            CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRING);
            CHECK(ml.geom_type_str() == "MultiLineString");
        }

        SECTION("xy - linestring vector")
        {
            std::vector<LineString> linestrings;
            linestrings.push_back({{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}});
            linestrings.push_back({{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}});
            MultiLineString ml(linestrings);
            CHECK(ml.size() == 2);
            CHECK(ml.dim == DimensionType::XY);
            CHECK(ml[0][0].x == 1.0);
            CHECK(ml[0][0].y == 2.0);
            CHECK(ml[1][2].x == 16.0);
            CHECK(ml[1][2].y == 17.0);
        }

        SECTION("xyz - linestring vector")
        {
            std::vector<LineString> linestrings;
            linestrings.push_back({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
            linestrings.push_back({{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}});
            MultiLineString ml(linestrings);
            CHECK(ml.size() == 2);
            CHECK(ml.dim == DimensionType::XYZ);
            CHECK(ml[0][0].x == 1.0);
            CHECK(ml[0][0].y == 2.0);
            CHECK(ml[0][0].z == 3.0);
            CHECK(ml[1][2].x == 16.0);
            CHECK(ml[1][2].y == 17.0);
            CHECK(ml[1][2].z == 18.0);
        }

        SECTION("xym - linestring vector")
        {
            // not supported
        }

        SECTION("xyzm - linestring vector")
        {
            std::vector<LineString> linestrings;
            linestrings.push_back({{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}});
            linestrings.push_back({{11.0, 12.0, 13.0, -4.5}, {13.0, 14.0, 15.0, -5.5}, {16.0, 17.0, 18.0, -6.5}});
            MultiLineString ml(linestrings);
            CHECK(ml.size() == 2);
            CHECK(ml.dim == DimensionType::XYZM);
            CHECK(ml[0][0].x == 1.0);
            CHECK(ml[0][0].y == 2.0);
            CHECK(ml[0][0].z == 3.0);
            CHECK(ml[0][0].m == -1.5);
            CHECK(ml[1][2].x == 16.0);
            CHECK(ml[1][2].y == 17.0);
            CHECK(ml[1][2].z == 18.0);
            CHECK(ml[1][2].m == -6.5);
        }

        SECTION("xy - initializer list")
        {
            auto ml = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}
            };
            CHECK(ml.size() == 2);
            CHECK(ml.dim == DimensionType::XY);
            CHECK(ml[0][0].x == 1.0);
            CHECK(ml[0][0].y == 2.0);
            CHECK(ml[1][2].x == 16.0);
            CHECK(ml[1][2].y == 17.0);
        }

        SECTION("xyz - initializer list")
        {
            auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}
            };
            CHECK(ml.size() == 2);
            CHECK(ml.dim == DimensionType::XYZ);
            CHECK(ml[0][0].x == 1.0);
            CHECK(ml[0][0].y == 2.0);
            CHECK(ml[0][0].z == 3.0);
            CHECK(ml[1][2].x == 16.0);
            CHECK(ml[1][2].y == 17.0);
            CHECK(ml[1][2].z == 18.0);
        }

        SECTION("xym - initializer list")
        {
            // not supported
        }

        SECTION("xyzm - initializer list")
        {
            auto ml = MultiLineString{
                {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                {{11.0, 12.0, 13.0, -4.5}, {13.0, 14.0, 15.0, -5.5}, {16.0, 17.0, 18.0, -6.5}}
            };
            CHECK(ml.size() == 2);
            CHECK(ml.dim == DimensionType::XYZM);
            CHECK(ml[0][0].x == 1.0);
            CHECK(ml[0][0].y == 2.0);
            CHECK(ml[0][0].z == 3.0);
            CHECK(ml[0][0].m == -1.5);
            CHECK(ml[1][2].x == 16.0);
            CHECK(ml[1][2].y == 17.0);
            CHECK(ml[1][2].z == 18.0);
            CHECK(ml[1][2].m == -6.5);
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
                std::string json    = R"(
                {
                    "type": "MultiLineString",
                            "coordinates": [
                    [[10, 10], [20, 20], [10, 40]],
                    [[40, 40], [30, 30], [40, 20], [30, 10]]
                    ]
                }
                )";
                auto mls            = MultiLineString::from_json(json);
                std::string j_str   = mls.json();
                std::string wkt_str = mls.wkt();
                CHECK(mls.size() == 2);
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
