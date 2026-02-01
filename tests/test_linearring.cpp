#include <ciso646>
#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;

TEST_CASE("LinearRing - Construction")
{
    SECTION("empty linearring")
    {
        LinearRing ring;
        REQUIRE(ring.empty());
        REQUIRE(ring.size() == 0);
    }

    SECTION("construct from initializer list")
    {
        LinearRing ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};
        REQUIRE(ring.size() == 5);
        REQUIRE(ring[0].x == Approx(0.0));
        REQUIRE(ring[0].y == Approx(0.0));
    }

    SECTION("construct from points")
    {
        Point p1{0, 0};
        Point p2{1, 0};
        Point p3{1, 1};
        Point p4{0, 1};
        Point p5{0, 0};
        LinearRing ring{p1, p2, p3, p4, p5};

        REQUIRE(ring.size() == 5);
    }

    SECTION("copy construction")
    {
        LinearRing ring1{{0, 0}, {1, 0}, {1, 1}, {0, 0}};
        LinearRing ring2 = ring1;

        REQUIRE(ring2.size() == ring1.size());
        REQUIRE(ring2[0].x == ring1[0].x);
    }
}

TEST_CASE("LinearRing - Closedness")
{
    SECTION("closed ring")
    {
        LinearRing ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};
        REQUIRE(ring.is_closed());

        // First and last points should be equal
        REQUIRE(ring.front().x == ring.back().x);
        REQUIRE(ring.front().y == ring.back().y);
    }

    SECTION("open ring")
    {
        LinearRing ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}};
        REQUIRE_FALSE(ring.is_closed());
    }

    SECTION("single point")
    {
        LinearRing ring{{1, 1}};
        // Single point is technically "closed" (start == end)
        REQUIRE(ring.is_closed());
    }

    SECTION("two identical points")
    {
        LinearRing ring{{1, 1}, {1, 1}};
        REQUIRE(ring.is_closed());
    }

    SECTION("empty ring")
    {
        LinearRing ring;
        // Empty is considered closed
        REQUIRE(ring.is_closed());
    }
}

TEST_CASE("LinearRing - Container Operations")
{
    SECTION("push_back")
    {
        LinearRing ring;
        ring.push_back(Point{0, 0});
        ring.push_back(Point{1, 0});
        ring.push_back(Point{1, 1});
        ring.push_back(Point{0, 0});

        REQUIRE(ring.size() == 4);
        REQUIRE(ring.is_closed());
    }

    SECTION("pop_back")
    {
        LinearRing ring{{0, 0}, {1, 0}, {1, 1}, {0, 0}};
        ring.pop_back();

        REQUIRE(ring.size() == 3);
        REQUIRE_FALSE(ring.is_closed());
    }

    SECTION("clear")
    {
        LinearRing ring{{0, 0}, {1, 0}, {1, 1}, {0, 0}};
        ring.clear();

        REQUIRE(ring.empty());
        REQUIRE(ring.size() == 0);
    }

    SECTION("iteration")
    {
        LinearRing ring{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};

        int count = 0;
        for (const auto& pt : ring)
        {
            count++;
            // All points should be valid
            REQUIRE(std::isfinite(pt.x));
            REQUIRE(std::isfinite(pt.y));
        }

        REQUIRE(count == 5);
    }

    SECTION("indexed access")
    {
        LinearRing ring{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

        REQUIRE(ring[0].x == Approx(0.0));
        REQUIRE(ring[1].x == Approx(2.0));
        REQUIRE(ring[2].y == Approx(2.0));
    }
}

TEST_CASE("LinearRing - Geometry Properties")
{
    SECTION("bounds of closed ring")
    {
        LinearRing ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};
        auto b = ring.bounds();

        REQUIRE(b.minx == Approx(0.0));
        REQUIRE(b.maxx == Approx(4.0));
        REQUIRE(b.miny == Approx(0.0));
        REQUIRE(b.maxy == Approx(3.0));
    }

    SECTION("length of ring")
    {
        LinearRing ring{{0, 0}, {3, 0}, {3, 4}, {0, 4}, {0, 0}};
        auto len = ring.length();

        // Perimeter: 3 + 4 + 3 + 4 = 14
        REQUIRE(len == Approx(14.0));
    }

    SECTION("area interpretation")
    {
        // LinearRing as the exterior of a polygon
        LinearRing ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};

        // Can compute signed area
        using namespace simo::shapes::algorithm;
        auto signed_area = signed_area_ring(ring);

        REQUIRE(std::abs(signed_area) == Approx(12.0));
    }
}

TEST_CASE("LinearRing - Serialization")
{
    SECTION("WKT representation")
    {
        LinearRing ring{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};
        auto wkt = ring.wkt();

        // Should contain coordinates
        REQUIRE(wkt.find("0") != std::string::npos);
        REQUIRE(wkt.find("1") != std::string::npos);
    }

    SECTION("JSON representation")
    {
        LinearRing ring{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};
        auto json = ring.json();

        // Should be LineString in GeoJSON
        REQUIRE(json.find("LineString") != std::string::npos);
        REQUIRE(json.find("coordinates") != std::string::npos);
    }

    SECTION("round-trip WKT")
    {
        LinearRing ring{{0, 0}, {3, 0}, {3, 3}, {0, 3}, {0, 0}};
        auto wkt = ring.wkt();
        auto parsed = LinearRing::from_wkt(wkt);

        REQUIRE(parsed.size() == ring.size());
        REQUIRE(parsed[0].x == Approx(ring[0].x));
    }

    SECTION("round-trip JSON")
    {
        LinearRing ring{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};
        auto json = ring.json();
        auto parsed = LinearRing::from_json(json);

        REQUIRE(parsed.size() == ring.size());
        REQUIRE(parsed[0].x == Approx(ring[0].x));
        REQUIRE(parsed[0].y == Approx(ring[0].y));
    }
}

TEST_CASE("LinearRing - Special Cases")
{
    SECTION("triangle ring")
    {
        LinearRing ring{{0, 0}, {1, 0}, {0.5, 1}, {0, 0}};

        REQUIRE(ring.size() == 4);
        REQUIRE(ring.is_closed());

        auto len = ring.length();
        REQUIRE(len > 0);
    }

    SECTION("very small ring")
    {
        LinearRing ring{{0, 0}, {0.001, 0}, {0.001, 0.001}, {0, 0.001}, {0, 0}};

        REQUIRE(ring.is_closed());
        auto b = ring.bounds();
        REQUIRE(b.maxx - b.minx == Approx(0.001));
    }

    SECTION("large coordinates")
    {
        LinearRing ring{{0, 0}, {1e6, 0}, {1e6, 1e6}, {0, 1e6}, {0, 0}};

        REQUIRE(ring.is_closed());
        auto b = ring.bounds();
        REQUIRE(b.maxx == Approx(1e6));
    }

    SECTION("negative coordinates")
    {
        LinearRing ring{{-10, -10}, {10, -10}, {10, 10}, {-10, 10}, {-10, -10}};

        REQUIRE(ring.is_closed());
        auto b = ring.bounds();
        REQUIRE(b.minx == Approx(-10.0));
    }
}

TEST_CASE("LinearRing - Equality")
{
    SECTION("equal rings")
    {
        LinearRing ring1{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};
        LinearRing ring2{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};

        REQUIRE(ring1 == ring2);
    }

    SECTION("different rings")
    {
        LinearRing ring1{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};
        LinearRing ring2{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};

        REQUIRE(ring1 != ring2);
    }

    SECTION("different sizes")
    {
        LinearRing ring1{{0, 0}, {1, 0}, {1, 1}, {0, 0}};
        LinearRing ring2{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};

        REQUIRE(ring1 != ring2);
    }
}

TEST_CASE("LinearRing - Algorithms")
{
    SECTION("contains point (as polygon boundary)")
    {
        Polygon poly;
        LinearRing ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};
        poly.push_back(ring);

        Point inside{2, 1.5};
        Point outside{5, 5};

        using namespace simo::shapes::algorithm;
        REQUIRE(contains(poly, inside));
        REQUIRE_FALSE(contains(poly, outside));
    }

    SECTION("simplify ring")
    {
        LinearRing ring{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {3, 1}, {3, 2}, {3, 3},
                        {2, 3}, {1, 3}, {0, 3}, {0, 2}, {0, 1}, {0, 0}};

        auto simplified = ring.simplify(0.5);

        // Should reduce number of points
        REQUIRE(simplified.size() <= ring.size());
        REQUIRE(simplified.size() >= 2);  // At least start/end
    }

    SECTION("translate ring")
    {
        LinearRing ring{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}};
        auto translated = ring.translate(5.0, 10.0);

        REQUIRE(translated[0].x == Approx(5.0));
        REQUIRE(translated[0].y == Approx(10.0));
        REQUIRE(translated.is_closed());
    }

    SECTION("rotate ring")
    {
        LinearRing ring{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}};
        auto rotated = ring.rotate(M_PI / 2);  // 90 degrees

        REQUIRE(rotated.size() == ring.size());
        REQUIRE(rotated.is_closed());
    }
}
