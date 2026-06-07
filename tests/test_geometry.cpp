#include <ciso646>
#include <catch2/catch_amalgamated.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Geometry")
{
    SECTION("Point")
    {
        SECTION("xy")
        {
            geometry geom(point(1, 2));
            CHECK(geom.is_point());
            auto p = geom.get<point>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
        }

        SECTION("xyz")
        {
            geometry geom(point_z(1, 2, 3));
            CHECK(geom.is_point_z());
            auto p = geom.get<point_z>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
            CHECK(p->z == 3);
        }

        SECTION("xym")
        {
            geometry geom(point_m(1, 2, 3));
            CHECK(geom.is_point_m());
            auto p = geom.get<point_m>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
            CHECK(p->m == 3);
        }

        SECTION("xyzm")
        {
            geometry geom(point_zm(1, 2, 3, 4));
            CHECK(geom.is_point_zm());
            auto p = geom.get<point_zm>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
            CHECK(p->z == 3);
            CHECK(p->m == 4);
        }

        SECTION("wkt")
        {
            std::vector<geometry> geoms;

            geoms.emplace_back(point(1, 2));
            geoms.emplace_back(point_z(1, 2, 3));
            geoms.emplace_back(point_m(1, 2, 3));
            geoms.emplace_back(point_zm(1, 2, 3, 4));
            geoms.emplace_back(point_zm(8, 9, 10, 11));

            geoms.emplace_back(multipoint{{1, 2}, {3, 4}, {5, 6}, {7, 8}});
            geoms.emplace_back(multipoint_z{{1, 2, -10}, {3, 4, -100}, {5, 6, -1000}, {7, 8, -1000}});
            geoms.emplace_back(multipoint_m{{1, 2, 10}, {3, 4, 20}, {5, 6, 30}, {7, 8, 40}});
            geoms.emplace_back(multipoint_zm{{1, 2, 10, -5}, {3, 4, 20, -50}, {5, 6, 30, -500}, {7, 8, 40, -5000}});

            geoms.emplace_back(linestring{{1, 2}, {3, 4}, {5, 6}, {7, 8}});
            geoms.emplace_back(linestring_z{{1, 2, -10}, {3, 4, -100}, {5, 6, -1000}, {7, 8, -1000}});
            geoms.emplace_back(linestring_m{{1, 2, 10}, {3, 4, 20}, {5, 6, 30}, {7, 8, 40}});
            geoms.emplace_back(linestring_zm{{1, 2, 10, -5}, {3, 4, 20, -50}, {5, 6, 30, -500}, {7, 8, 40, -5000}});

            geoms.emplace_back(multilinestring{{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}});
            geoms.emplace_back(multilinestring_z{{{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}, {{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}});
            geoms.emplace_back(multilinestring_m{{{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}, {{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}});
            geoms.emplace_back(multilinestring_zm{{{1, 2, -10, 100}, {3, 4, -10, 100}, {5, 6, -10, 100}, {7, 8, -10, 100}}, {{1, 2, -10, 100}, {3, 4, -10, 100}, {5, 6, -10, 100}, {7, 8, -10, 100}}});

            geoms.emplace_back(polygon{{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}});
            geoms.emplace_back(polygon_z{{{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}, {{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}});
            geoms.emplace_back(polygon_m{{{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}, {{1, 2, -10}, {3, 4, -10}, {5, 6, -10}, {7, 8, -10}}});
            geoms.emplace_back(polygon_zm{{{1, 2, -10, 100}, {3, 4, -10, 100}, {5, 6, -10, 100}, {7, 8, -10, 100}}, {{1, 2, -10, 100}, {3, 4, -10, 100}, {5, 6, -10, 100}, {7, 8, -10, 100}}});

            geoms.emplace_back(multipolygon{{{{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}, {{1, 2}, {3, 4}, {5, 6}, {7, 8}}}});

            for (const auto& p : geoms)
            {
                std::cout << static_cast<int32_t>(p.geom_type()) << std::endl;
                std::cout << p.wkt() << std::endl;
                std::cout << p.json() << std::endl;
            }
        }

        SECTION("from_wkt")
        {
            auto geom = geometry::from_wkt("POINT ZM (8 9 10 11)");
            auto p    = geom.get<point_zm>();
            std::cout << p->x << std::endl;
            std::cout << p->y << std::endl;
        }

        SECTION("geometrycollection from wkt")
        {
            SECTION("empty")
            {
                auto geom = geometry::from_wkt("GEOMETRYCOLLECTION EMPTY");
                CHECK(geom.is_geometrycollection());
                auto gc = geom.get_geometrycollection();
                REQUIRE(gc != nullptr);
                CHECK(gc->empty());
                CHECK(gc->wkt() == "GEOMETRYCOLLECTION EMPTY");
                CHECK(gc->json() == R"({"type":"GeometryCollection","geometries":[]})");
            }

            SECTION("mixed children")
            {
                auto gc = GeometryCollection::from_wkt("GEOMETRYCOLLECTION (POINT (1 2), LINESTRING (0 0, 1 1), POLYGON ((0 0, 1 0, 1 1, 0 0)))");
                REQUIRE(gc.size() == 3);
                CHECK(gc[0].wkt() == "POINT (1 2)");
                CHECK(gc[1].wkt() == "LINESTRING(0 0,1 1)");
                CHECK(gc[2].wkt() == "POLYGON((0 0,1 0,1 1,0 0))");
            }

            SECTION("nested")
            {
                auto geom = geometry::from_wkt("GEOMETRYCOLLECTION (POINT EMPTY, GEOMETRYCOLLECTION (POINT Z (1 2 3)))");
                auto gc = geom.get_geometrycollection();
                REQUIRE(gc != nullptr);
                REQUIRE(gc->size() == 2);
                CHECK((*gc)[0].wkt() == "POINT EMPTY");
                CHECK((*gc)[1].is_geometrycollection());
                auto nested = (*gc)[1].get_geometrycollection();
                REQUIRE(nested != nullptr);
                REQUIRE(nested->size() == 1);
                CHECK((*nested)[0].wkt() == "POINT Z (1 2 3)");
            }

            SECTION("collection dimension preserves child tags")
            {
                auto geom = geometry::from_wkt("GEOMETRYCOLLECTION Z (POINT (1 2), POINT Z (3 4 5))");
                CHECK(geom.is_geometrycollection_z());
                auto gc = geom.get_geometrycollection_z();
                REQUIRE(gc != nullptr);
                REQUIRE(gc->size() == 2);
                CHECK(gc->wkt() == "GEOMETRYCOLLECTIONZ(POINT (1 2),POINT Z (3 4 5))");
            }
        }
    }
}
