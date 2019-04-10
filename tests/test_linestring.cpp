#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("LineString")
{
    SECTION("xy - from wkt - form2")
    {
        auto mp = LineString::from_wkt("LINESTRING(1.4 2.3, 3.2 4.1)");
        CHECK(not mp.empty());
        CHECK(mp.detailed_type() == GeometryDetailedType::LINESTRING);
        CHECK(mp.dim == DimensionType::XY);
        const auto& p1 = mp[0];
        CHECK(p1.x == 1.4);
        CHECK(p1.y == 2.3);
        const auto& p2 = mp[1];
        CHECK(p2.x == 3.2);
        CHECK(p2.y == 4.1);
    }
}
