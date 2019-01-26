#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Point tests")
{
    SECTION("geometry type")
    {
        Point p;
        CHECK(p.geom_type() == GeometryType::POINT);
        CHECK(p.geom_type_str() == "POINT");
    }

    SECTION("empty constructor")
    {
        Point p;
        CHECK(p.x == 0);
        CHECK(p.y == 0);
        CHECK(p.dimension() == 2);
    }

    SECTION("2d point constructor - initializer list")
    {
        Point p = {1, 2};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 0);
        CHECK(p.dimension() == 2);
    }


    SECTION("3d point constructor - initializer list")
    {
        Point p = {1, 2, 3};
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
        CHECK(p.dimension() == 3);
    }
}
