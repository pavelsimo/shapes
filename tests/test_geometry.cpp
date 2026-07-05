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

TEST_CASE("Geometry - facade dispatch")
{
    SECTION("dim/ndim/has_z/has_m for a Z point")
    {
        auto geom = geometry::from_wkt("POINT Z (1 2 3)");
        CHECK(geom.dim() == dimension_type::XYZ);
        CHECK(geom.ndim() == 3);
        CHECK(geom.has_z());
        CHECK_FALSE(geom.has_m());
    }

    SECTION("bounds dispatches to the concrete geometry")
    {
        auto geom = geometry::from_wkt("LINESTRING(-3 -2,-1 -1)");
        auto b    = geom.bounds();
        CHECK(b.minx == -3.0);
        CHECK(b.miny == -2.0);
        CHECK(b.maxx == -1.0);
        CHECK(b.maxy == -1.0);
    }

    SECTION("is_closed dispatches to the concrete geometry")
    {
        CHECK(geometry::from_wkt("LINESTRING(0 0,1 0,1 1,0 0)").is_closed());
        CHECK_FALSE(geometry::from_wkt("LINESTRING(0 0,1 0,1 1)").is_closed());
    }
}

TEST_CASE("Geometry - checked getters")
{
    SECTION("mismatched getter returns nullptr")
    {
        geometry geom(point(1, 2));
        CHECK(geom.get_linestring() == nullptr);
        CHECK(geom.get_multipoint() == nullptr);
        CHECK(geom.get_point() != nullptr);
    }

    SECTION("const getters work on const geometries")
    {
        const geometry geom(point(1, 2));
        CHECK(geom.is_point());
        CHECK(geom.get_point() != nullptr);
        CHECK(geom.get<point>() != nullptr);
    }
}

TEST_CASE("Geometry - move semantics")
{
    SECTION("move assignment steals the container without copying")
    {
        geometry src(linestring{{1, 2}, {3, 4}});
        auto* before = src.get_linestring();
        geometry dst;
        dst = std::move(src);
        CHECK(dst.get_linestring() == before);
    }

    SECTION("move construction leaves the source empty")
    {
        geometry src(multipoint{{1, 2}, {3, 4}});
        geometry dst(std::move(src));
        CHECK(dst.is_multipoint());
        CHECK(src.geom_type() == geometry_type::GEOMETRY);
    }

    SECTION("copies of collections are deep")
    {
        geometrycollection gc;
        gc.emplace_back(geometry(point(1, 2)));
        geometry a(gc);
        geometry b(a);
        CHECK(a.get_geometrycollection() != b.get_geometrycollection());
        CHECK(a.wkt() == b.wkt());
    }
}

TEST_CASE("Geometry - default precision round-trip")
{
    SECTION("high precision coordinates survive a wkt round-trip")
    {
        point p{-122.4194155, 37.7749295};
        auto q = point::from_wkt(p.wkt());
        CHECK(p == q);
        CHECK(p.wkt() == "POINT (-122.4194155 37.7749295)");
    }

    SECTION("integer coordinates print without a decimal point")
    {
        CHECK(point(1, 2).wkt() == "POINT (1 2)");
    }
}

TEST_CASE("Geometry - wkt reader is not copyable")
{
    static_assert(not std::is_copy_constructible<wkt_reader>::value, "wkt_reader must not be copyable");
    static_assert(not std::is_copy_assignable<wkt_reader>::value, "wkt_reader must not be copy assignable");
    static_assert(std::is_move_constructible<wkt_reader>::value, "wkt_reader should be movable");
}
