#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("Polyline")
{
    SECTION("encode")
    {
        CHECK(polyline::encode(-179.9832104) == "`~oia@");
        std::string encoded = "";
        encoded += polyline::encode(38.5);
        encoded += polyline::encode(-120.2);
        encoded += polyline::encode(40.7 - 38.5);
        encoded += polyline::encode(-120.95 - (-120.2));
        encoded += polyline::encode(43.252 - 40.7);
        encoded += polyline::encode(-126.453 - (-120.95));
        CHECK(encoded == "_p~iF~ps|U_ulLnnqC_mqNvxq`@");
    }

    SECTION("decode")
    {
        auto coords = polyline::decode("_p~iF~ps|U_ulLnnqC_mqNvxq`@");
        CHECK(coords[0][0] == 38.5);
        CHECK(coords[0][1] == -120.2);
        CHECK(coords[1][0] == 40.7);
        CHECK(coords[1][1] == -120.95);
        CHECK(coords[2][0] == 43.252);
        CHECK(coords[2][1] == -126.453);
    }
}