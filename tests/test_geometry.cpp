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
            Geometry geom(Point(1, 2));
            CHECK(geom.is_point());
            auto p = geom.get<Point>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
        }

        SECTION("xyz")
        {
            Geometry geom(PointZ(1, 2, 3));
            CHECK(geom.is_point_z());
            auto p = geom.get<PointZ>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
            CHECK(p->z == 3);
        }

        SECTION("xym")
        {
            Geometry geom(PointM(1, 2, 3));
            CHECK(geom.is_point_m());
            auto p = geom.get<PointM>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
            CHECK(p->m == 3);
        }

        SECTION("xyzm")
        {
            Geometry geom(PointZM(1, 2, 3, 4));
            CHECK(geom.is_point_zm());
            auto p = geom.get<PointZM>();
            CHECK(p->x == 1);
            CHECK(p->y == 2);
            CHECK(p->z == 3);
            CHECK(p->m == 4);
        }

        SECTION("wkt")
        {
            std::vector<Geometry> geoms;
            std::cout << sizeof(Geometry) << std::endl;
            geoms.reserve(10);
            geoms.emplace_back(Point(1, 2));
            geoms.emplace_back(PointZ(1, 2, 3));
            geoms.emplace_back(PointM(1, 2, 3));
            geoms.emplace_back(PointZM(1, 2, 3, 4));
            for (const auto& p : geoms)
            {
                std::cout << p.wkt() << std::endl;
                std::cout << p.json() << std::endl;
            }
        }
    }
}
