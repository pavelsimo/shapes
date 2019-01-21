#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("test multipoint")
{
    SECTION("Test Initializer List")
    {
        Point p(1, 2, 3);
        CHECK(p.x == 1);
        CHECK(p.y == 2);
        CHECK(p.z == 3);
    }

}
