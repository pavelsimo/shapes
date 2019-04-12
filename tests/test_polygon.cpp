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

        SECTION("xy shell - initializer list")
        {
            Polygon p = {
                {{1, 2}, {3, 4}, {5, 6}, {1, 2}}  // exterior
            };
            CHECK(p.exterior[0].x == 1);
            CHECK(p.exterior[0].y == 2);
            CHECK(p.exterior[1].x == 3);
            CHECK(p.exterior[1].y == 4);
            CHECK(p.exterior[2].x == 5);
            CHECK(p.exterior[2].y == 6);
            CHECK(p.exterior[3].x == 1);
            CHECK(p.exterior[3].y == 2);
            CHECK(p.type() == GeometryType::POLYGON);
            CHECK(p.detailed_type() == GeometryDetailedType::POLYGON);
            CHECK(p.type_str() == "Polygon");
        }

        SECTION("xy shell, holes - initializer list")
        {
            /// @todo (pavel) add test
        }

        SECTION("xyz shell - initializer list")
        {
            Polygon p = {
                {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}  // exterior
            };
            CHECK(p.exterior[0].x == 1);
            CHECK(p.exterior[0].y == 2);
            CHECK(p.exterior[0].z == 3);
            CHECK(p.exterior[1].x == 4);
            CHECK(p.exterior[1].y == 5);
            CHECK(p.exterior[1].z == 6);
        }

        SECTION("xyz shell, holes - initializer list")
        {
            Polygon p = {
                {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},  // exterior
                {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}   // interior
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

        SECTION("xyzm shell - initializer list")
        {
            /// @todo (pavel) add test
        }

        SECTION("xyzm shell, holes - initializer list")
        {
            /// @todo (pavel) add test
        }

        SECTION("shell, holes - constructor")
        {
            //            Polygon p(
            //                    {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}},     // exterior
            //                    {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 2, 3}}}}  // interior
            //            );
            //            LinearRing& exterior = p.exterior;
            //            CHECK(exterior[0].x == 1);
            //            CHECK(exterior[0].y == 2);
            //            CHECK(exterior[0].z == 3);
            //            CHECK(exterior[1].x == 4);
            //            CHECK(exterior[1].y == 5);
            //            CHECK(exterior[1].z == 6);
            //            CHECK(exterior[2].x == 7);
            //            CHECK(exterior[2].y == 8);
            //            CHECK(exterior[2].z == 9);
            //            CHECK(exterior[3].x == 1);
            //            CHECK(exterior[3].y == 2);
            //            CHECK(exterior[3].z == 3);
            //
            //            CHECK(p.interiors.size() == 1);
            //            LinearRing& interior = p.interiors[0];
            //            CHECK(interior[0].x == 1);
            //            CHECK(interior[0].y == 2);
            //            CHECK(interior[0].z == 3);
            //            CHECK(interior[1].x == 4);
            //            CHECK(interior[1].y == 5);
            //            CHECK(interior[1].z == 6);
            //            CHECK(interior[2].x == 7);
            //            CHECK(interior[2].y == 8);
            //            CHECK(interior[2].z == 9);
            //            CHECK(interior[3].x == 1);
            //            CHECK(interior[3].y == 2);
            //            CHECK(interior[3].z == 3);
        }

        SECTION("no throw - constructor")
        {
            /// @todo (pavel) add test
        }

        SECTION("throws - constructor")
        {
            /// @todo (pavel) add test
        }

        SECTION("xy - from wkt")
        {
            auto p = Polygon::from_wkt("POLYGON ((30 10, 40 40, 20 40, 10 20, 30 10))");
        }

        SECTION("xyz - from wkt")
        {

        }

        SECTION("xyzm - from wkt")
        {

        }
    }
}
