#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("MultiLineString")
{
    SECTION("xy - from wkt")
    {
        auto mp = MultiLineString::from_wkt("MULTILINESTRING ((10 10, 20 20, 10 40), (40 40, 30 30, 40 20, 30 10))");
    }

    SECTION("xyz - from wkt")
    {
        auto mp = MultiLineString::from_wkt("MULTILINESTRING Z ((10 10 10, 20 20 20, 10 40 40), (40 40 40, 30 30 30, 40 20 20, 30 10 10))");
    }

    SECTION("xyzm - from wkt")
    {
        auto mp = MultiLineString::from_wkt("MULTILINESTRING ZM ((10 10 10 10, 20 20 20 20, 10 40 40 40), (40 40 40 40, 30 30 30 30, 40 20 20 20, 30 10 10 10))");
    }
}
