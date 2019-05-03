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
                    [[10, 35], [20, 20], [10, 40]],
                    [[40, 40], [30, 30], [40, 20], [30, 5]]
                    ]
                }
                )";
                auto ml            = MultiLineString::from_json(json);
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XY);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRING);
                CHECK(ml[0][0].x == 10.0);
                CHECK(ml[0][0].y == 35.0);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == 5.0);
            }

            SECTION("xyz - from json")
            {
                std::string json    = R"(
                {
                    "type": "MultiLineString",
                            "coordinates": [
                    [[10, 35, -10], [20, 20, -10], [10, 40, -10]],
                    [[40, 40, -20], [30, 30, -20], [40, 20, -20], [30, 5, -20]]
                    ]
                }
                )";
                auto ml            = MultiLineString::from_json(json);
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XYZ);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGZ);
                CHECK(ml[0][0].x == 10.0);
                CHECK(ml[0][0].y == 35.0);
                CHECK(ml[0][0].z == -10.0);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == 5.0);
                CHECK(ml[1][3].z == -20.0);
            }

            SECTION("xym - from json")
            {
                // not supported
            }

            SECTION("xyzm - from json")
            {
                std::string json    = R"(
                {
                    "type": "MultiLineString",
                            "coordinates": [
                    [[10, 35, -10, -5], [20, 20, -10, -5], [10, 40, -10, -5]],
                    [[40, 40, -20, -4000], [30, 30, -20, -4000], [40, 20, -20, -4000], [30, 5, -20, -4000]]
                    ]
                }
                )";
                auto ml            = MultiLineString::from_json(json);
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XYZM);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGZM);
                CHECK(ml[0][0].x == 10.0);
                CHECK(ml[0][0].y == 35.0);
                CHECK(ml[0][0].z == -10.0);
                CHECK(ml[0][0].m == -5.0);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == 5.0);
                CHECK(ml[1][3].z == -20.0);
                CHECK(ml[1][3].m == -4000.0);
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - from wkt")
            {
                auto ml = MultiLineString::from_wkt("MULTILINESTRING ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))");
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XY);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRING);
                CHECK(ml[0][0].x == 10.0);
                CHECK(ml[0][0].y == 35.0);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == 10.0);
            }

            SECTION("xyz - from wkt")
            {
                auto ml = MultiLineString::from_wkt("MULTILINESTRING Z ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))");
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XYZ);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGZ);
                CHECK(ml[0][0].x == 10.0);
                CHECK(ml[0][0].y == 35.0);
                CHECK(ml[0][0].z == -10);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == 10.0);
                CHECK(ml[1][3].z == -3010.5);
            }

            SECTION("xym - from wkt")
            {
                auto ml = MultiLineString::from_wkt("MULTILINESTRING M ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))");
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XYM);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGM);
                CHECK(ml[0][0].x == 10.0);
                CHECK(ml[0][0].y == 35.0);
                CHECK(ml[0][0].m == -10);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == 10.0);
                CHECK(ml[1][3].m == -3010.5);
            }

            SECTION("xyzm - from wkt")
            {
                auto ml = MultiLineString::from_wkt("MULTILINESTRING ZM ((-100 -50 -25 -5, 0.5 1.0 1.5 2.0, 1000 500 250 50), (40 40 40 40, 30 30 30 30, 40 20 20 20, 30 -10 -210 50))");
                CHECK(ml.size() == 2);
                CHECK(ml.dim == DimensionType::XYZM);
                CHECK(ml.geom_type() == GeometryType::MULTILINESTRING);
                CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGZM);
                CHECK(ml[0][0].x == -100.0);
                CHECK(ml[0][0].y == -50.0);
                CHECK(ml[0][0].z == -25);
                CHECK(ml[0][0].m == -5);
                CHECK(ml[1][3].x == 30.0);
                CHECK(ml[1][3].y == -10.0);
                CHECK(ml[1][3].z == -210);
                CHECK(ml[1][3].m == 50);
            }

            SECTION("empty - from wkt")
            {
                SECTION("empty - xy")
                {
                    auto ml = MultiLineString::from_wkt("MultiLineString EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRING);
                    CHECK(ml.dim == DimensionType::XY);
                }

                SECTION("empty - xyz")
                {
                    auto ml = MultiLineString::from_wkt("MultiLineString Z EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGZ);
                    CHECK(ml.dim == DimensionType::XYZ);
                }

                SECTION("empty - xym")
                {
                    auto ml = MultiLineString::from_wkt("MultiLineString M EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGM);
                    CHECK(ml.dim == DimensionType::XYM);
                }

                SECTION("empty - xyzm")
                {
                    auto ml = MultiLineString::from_wkt("MultiLineString ZM EMPTY");
                    CHECK(ml.empty());
                    CHECK(ml.geom_type_dim() == GeometryType::MULTILINESTRINGZM);
                    CHECK(ml.dim == DimensionType::XYZM);
                }
            }

            SECTION("no throw - from wkt")
            {
                CHECK_NOTHROW(MultiLineString::from_wkt("multilinestring m ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
                CHECK_NOTHROW(MultiLineString::from_wkt("multilinestring z ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
            }

            SECTION("throws - from wkt")
            {
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING ((10 35, 20 20, 10 40"));
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING ZM ((10 35 -10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 -3010.5))"));
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING ((10 35, 20 20, 10 40)))"));
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING Z ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))"));
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING ZM ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))"));
                CHECK_THROWS(MultiLineString::from_wkt("MULTILINESTRING M ((10 35, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))"));
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
                auto ml = MultiLineString{
                        {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                        {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}
                };
                ml.precision = 1;
                CHECK(ml.wkt() == "MULTILINESTRING((1.0 2.0,4.0 5.0,7.0 8.0),(11.0 12.0,13.0 14.0,16.0 17.0))");
            }

            SECTION("xyz - to wkt")
            {
                auto ml = MultiLineString{
                        {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                        {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}
                };
                ml.precision = 1;
                CHECK(ml.wkt() == "MULTILINESTRINGZ((1.0 2.0 3.0,4.0 5.0 6.0,7.0 8.0 9.0),(11.0 12.0 13.0,13.0 14.0 15.0,16.0 17.0 18.0))");
            }

            SECTION("xym - to wkt")
            {
                /// @todo add test
            }

            SECTION("xyzm - to wkt")
            {
                auto ml = MultiLineString{
                        {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                        {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}
                };
                ml.precision = 1;
                CHECK(ml.wkt() == "MULTILINESTRINGZM((1.0 2.0 3.0 -1.5,4.0 5.0 6.0 -2.5,7.0 8.0 9.0 -3.5),(11.0 12.0 13.0 -10.5,13.0 14.0 15.0 -11.5,16.0 17.0 18.0 -12.5))");
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
