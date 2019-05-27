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
        // (x1, y1, x2, y2, ..., xn, yn)
        auto coords = polyline::decode("_p~iF~ps|U_ulLnnqC_mqNvxq`@");
        CHECK(coords[0] == -120.2);
        CHECK(coords[1] == 38.5);
        CHECK(coords[2] == -120.95);
        CHECK(coords[3] == 40.7);
        CHECK(coords[4] == -126.453);
        CHECK(coords[5] == 43.252);
    }
}