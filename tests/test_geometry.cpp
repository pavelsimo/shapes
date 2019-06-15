#include <ciso646>
#include <catch/catch.hpp>
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
    }
}
