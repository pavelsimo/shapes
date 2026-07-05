#include <ciso646>
#include <catch2/catch_amalgamated.hpp>
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

    SECTION("decode - small")
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
TEST_CASE("Polyline - edge cases")
{
    SECTION("tiny negative value rounds to zero and encodes like zero")
    {
        CHECK(polyline::encode(-1e-9) == polyline::encode(0.0));
    }

    SECTION("negative deltas round-trip")
    {
        std::string encoded = polyline::encode(-179.9832104);
        size_t index        = 0;
        auto decoded        = polyline::advance(encoded, index);
        CHECK(decoded == -17998321);
    }

    SECTION("from_polyline rejects truncated input")
    {
        CHECK_THROWS_AS(Point::from_polyline(""), exceptions::parse_error);
        CHECK_THROWS_AS(Point::from_polyline("_p~iF~ps|U_ulLnnqC"), exceptions::parse_error);
    }
}
