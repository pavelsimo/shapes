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
                {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
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
                {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
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
                {{11.0, 12.0, 13.0, -4.5}, {13.0, 14.0, 15.0, -5.5}, {16.0, 17.0, 18.0, -6.5}}};
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
            CHECK_THROWS(MultiLineString{{{1.0}, {4.0}, {7.0}}, {{11.0}, {13.0}, {16.0}}});
            CHECK_THROWS(MultiLineString{{{1.0, 2.0, 3.0, -1.5, 0.0}, {4.0, 5.0, 6.0, -2.5, 0.0}, {7.0, 8.0, 9.0, -3.5, 0.0}}, {{11.0, 12.0, 13.0, -4.5, 0.0}, {13.0, 14.0, 15.0, -5.5, 0.0}, {16.0, 17.0, 18.0, -6.5, 0.0}}});
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
                    "type": "MultiLineString",
                            "coordinates": [
                    [[10, 35], [20, 20], [10, 40]],
                    [[40, 40], [30, 30], [40, 20], [30, 5]]
                    ]
                }
                )";
                auto ml          = MultiLineString::from_json(json);
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
                std::string json = R"(
                {
                    "type": "MultiLineString",
                            "coordinates": [
                    [[10, 35, -10], [20, 20, -10], [10, 40, -10]],
                    [[40, 40, -20], [30, 30, -20], [40, 20, -20], [30, 5, -20]]
                    ]
                }
                )";
                auto ml          = MultiLineString::from_json(json);
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
                std::string json = R"(
                {
                    "type": "MultiLineString",
                            "coordinates": [
                    [[10, 35, -10, -5], [20, 20, -10, -5], [10, 40, -10, -5]],
                    [[40, 40, -20, -4000], [30, 30, -20, -4000], [40, 20, -20, -4000], [30, 5, -20, -4000]]
                    ]
                }
                )";
                auto ml          = MultiLineString::from_json(json);
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
        }
    }

    SECTION("to_... methods")
    {
        SECTION("json")
        {
            SECTION("xy - to json")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                CHECK(ml.json() == R"({"type":"MultiLineString","coordinates":[[[1,2],[4,5],[7,8]],[[11,12],[13,14],[16,17]]]})");
            }

            SECTION("xyz - to json")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                CHECK(ml.json() == R"({"type":"MultiLineString","coordinates":[[[1,2,3],[4,5,6],[7,8,9]],[[11,12,13],[13,14,15],[16,17,18]]]})");
            }

            SECTION("xym - to json")
            {
                /// @todo add test
            }

            SECTION("xyzm - to json")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                CHECK(ml.json() == R"({"type":"MultiLineString","coordinates":[[[1,2,3,-1.5],[4,5,6,-2.5],[7,8,9,-3.5]],[[11,12,13,-10.5],[13,14,15,-11.5],[16,17,18,-12.5]]]})");
            }
        }

        SECTION("wkt")
        {
            SECTION("xy - to wkt")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                CHECK(ml.wkt() == "MULTILINESTRING((1 2,4 5,7 8),(11 12,13 14,16 17))");
            }

            SECTION("xyz - to wkt")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                CHECK(ml.wkt() == "MULTILINESTRINGZ((1 2 3,4 5 6,7 8 9),(11 12 13,13 14 15,16 17 18))");
            }

            SECTION("xym - to wkt")
            {
                /// @todo add test
            }

            SECTION("xyzm - to wkt")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                CHECK(ml.wkt() == "MULTILINESTRINGZM((1 2 3 -1.5,4 5 6 -2.5,7 8 9 -3.5),(11 12 13 -10.5,13 14 15 -11.5,16 17 18 -12.5))");
            }
        }
    }

    SECTION("operators")
    {
        SECTION("equal to - operator")
        {
            SECTION("xy - equal to")
            {
                auto ml1 = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                auto ml2 = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                CHECK(ml1 == ml2);
            }

            SECTION("xyz - equal to")
            {
                auto ml1 = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                auto ml2 = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                CHECK(ml1 == ml2);
            }

            SECTION("xym - equal to")
            {
                /// @todo add test
            }

            SECTION("xyzm - equal to")
            {
                auto ml1 = MultiLineString{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                auto ml2 = MultiLineString{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                CHECK(ml1 == ml2);
            }
        }

        SECTION("not equal to - operator")
        {
            SECTION("xy - not equal to")
            {
                auto ml1 = MultiLineString{
                    {{5.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 20.0}}};
                auto ml2 = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                CHECK(ml1 != ml2);
            }

            SECTION("xyz - not equal to")
            {
                auto ml1 = MultiLineString{
                    {{8.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                auto ml2 = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {26.0, 17.0, 18.0}}};
                CHECK(ml1 != ml2);
            }

            SECTION("xym - not equal to")
            {
                /// @todo add test
            }

            SECTION("xyzm - not equal to")
            {
                auto ml1 = MultiLineString{
                    {{1.0, 200.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                auto ml2 = MultiLineString{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -3.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                CHECK(ml1 != ml2);
            }
        }

        SECTION("index operator")
        {
            SECTION("xy - index operator")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                    {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
                auto& p1 = ml[0][0];
                CHECK(p1.geom_type_dim() == GeometryType::POINT);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);

                auto& p2 = ml[1][2];
                CHECK(p2.geom_type_dim() == GeometryType::POINT);
                CHECK(p2.x == 16.0);
                CHECK(p2.y == 17.0);
            }

            SECTION("xyz - index operator")
            {
                auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                    {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
                auto& p1 = ml[0][0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);

                auto& p2 = ml[0][2];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZ);
                CHECK(p2.x == 7.0);
                CHECK(p2.y == 8.0);
                CHECK(p2.z == 9.0);

                auto& p3 = ml[1][2];
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
                auto ml = MultiLineString{
                    {{1.0, 2.0, 3.0, -1.5}, {4.0, 5.0, 6.0, -2.5}, {7.0, 8.0, 9.0, -3.5}},
                    {{11.0, 12.0, 13.0, -10.5}, {13.0, 14.0, 15.0, -11.5}, {16.0, 17.0, 18.0, -12.5}}};
                auto& p1 = ml[0][0];
                CHECK(p1.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p1.x == 1.0);
                CHECK(p1.y == 2.0);
                CHECK(p1.z == 3.0);
                CHECK(p1.m == -1.5);

                auto& p2 = ml[0][2];
                CHECK(p2.geom_type_dim() == GeometryType::POINTZM);
                CHECK(p2.x == 7.0);
                CHECK(p2.y == 8.0);
                CHECK(p2.z == 9.0);
                CHECK(p2.m == -3.5);

                auto& p3 = ml[1][2];
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
            auto ml = MultiLineString{
                {{1.0, 2.0}, {4.0, 5.0}, {7.0, 8.0}},
                {{11.0, 12.0}, {13.0, 14.0}, {16.0, 17.0}}};
            auto coords = ml.coords();
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
        }

        SECTION("xyz - coords")
        {
            auto ml = MultiLineString{
                {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
                {{11.0, 12.0, 13.0}, {13.0, 14.0, 15.0}, {16.0, 17.0, 18.0}}};
            auto coords = ml.coords();
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
        }

        SECTION("xym - coords")
        {
            /// @todo add test
        }

        SECTION("xyzm - coords")
        {
            auto ml = MultiLineString{
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
        }
    }
}
