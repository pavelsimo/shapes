#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiPolygon")
{
    SECTION("xy - from wkt")
    {
        auto mp = MultiPolygon::from_wkt("MULTIPOLYGON (((40 40, 20 45, 45 30, 40 40)), ((20 35, 10 30, 10 10, 30 5, 45 20, 20 35), (30 20, 20 15, 20 25, 30 20)))");
    }

    SECTION("xyz - from wkt")
    {
        auto mp = MultiPolygon::from_wkt("MULTIPOLYGON Z (((40 40 10, 20 45 10, 45 30 10, 40 40 10)), ((20 35 10, 10 30 10, 10 10 10, 30 5 10, 45 20 10, 20 35 10), (30 20 10, 20 15 10, 20 25 10, 30 20 10)))");
    }

    SECTION("xyzm - from wkt")
    {
        auto mp = MultiPolygon::from_wkt("MULTIPOLYGON ZM (((40 40 10 -5, 20 45 10 -5, 45 30 10 -5, 40 40 10 -5)), ((20 35 10 -5, 10 30 10 -5, 10 10 10 -5, 30 5 10 -5, 45 20 10 -5, 20 35 10 -5), (30 20 10 -5, 20 15 10 -5, 20 25 10 -5, 30 20 10 -5)))");
    }
}
