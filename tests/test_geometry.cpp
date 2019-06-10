#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Geometry")
{
    SECTION("Point")
    {
        {
            Geometry geom(Point(1, 2));
            auto p = geom.get<Point>();
            std::cout << p->x << std::endl;
            std::cout << p->y << std::endl;
        }

        {
            Geometry geom(PointZ(1, 2, 3));
            auto p = geom.get<PointZ>();
            std::cout << p->x << std::endl;
            std::cout << p->y << std::endl;
            std::cout << p->z << std::endl;
        }

        {
            Geometry geom(PointM(1, 2, 3));
            auto p = geom.get<PointM>();
            std::cout << p->x << std::endl;
            std::cout << p->y << std::endl;
            std::cout << p->m << std::endl;
        }

        {
            Geometry geom(PointZM(1, 2, 3, 4));
            auto p = geom.get<PointZM>();
            std::cout << p->x << std::endl;
            std::cout << p->y << std::endl;
            std::cout << p->z << std::endl;
            std::cout << p->m << std::endl;
        }

        {
            Geometry geom(Point(1.0, 2.0));
            auto p = geom.get<Point>();
            std::cout << p->x << std::endl;
            std::cout << p->y << std::endl;
        }
    }
}
