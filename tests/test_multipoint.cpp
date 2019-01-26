#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPoint tests")
{
    SECTION("geometry type")
    {
        MultiPoint mp;
        CHECK(mp.geom_type() == GeometryType::MULTIPOINT);
        CHECK(mp.geom_type_str() == "MULTIPOINT");
    }

    SECTION("2d multipoint constructor - initializer list")
    {
        MultiPoint mp2 = {{1.0, 2.0}, {2.0, 3.0}};
    }

    SECTION("3d multipoint constructor - initializer list")
    {
        MultiPoint mp = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
        CHECK(mp[0].x == 1.0);
        CHECK(mp[0].y == 2.0);
        CHECK(mp[0].z == 3.0);
        CHECK(mp[1].x == 4.0);
        CHECK(mp[1].y == 5.0);
        CHECK(mp[1].z == 6.0);
    }
}
