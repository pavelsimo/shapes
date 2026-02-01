#include <catch/catch.hpp>
#include <simo/shapes.hpp>
#include <cmath>

using namespace simo::shapes;
using namespace simo::shapes::algorithm;

TEST_CASE("Measurements - Distance")
{
    SECTION("distance between two points")
    {
        Point p1{0, 0};
        Point p2{3, 4};
        auto d = distance(p1, p2);
        REQUIRE(d == Approx(5.0));
    }

    SECTION("distance to same point is zero")
    {
        Point p{1, 2};
        auto d = distance(p, p);
        REQUIRE(d == Approx(0.0));
    }

    SECTION("distance is symmetric")
    {
        Point p1{1, 2};
        Point p2{4, 6};
        REQUIRE(distance(p1, p2) == Approx(distance(p2, p1)));
    }

    SECTION("distance with negative coordinates")
    {
        Point p1{-3, -4};
        Point p2{0, 0};
        auto d = distance(p1, p2);
        REQUIRE(d == Approx(5.0));
    }

    SECTION("distance with 3D points")
    {
        PointZ p1{0, 0, 0};
        PointZ p2{1, 0, 0};
        // Note: distance only uses x,y coordinates
        auto d = distance(p1, p2);
        REQUIRE(d == Approx(1.0));
    }
}

TEST_CASE("Measurements - Length")
{
    SECTION("length of empty linestring")
    {
        LineString ls;
        auto len = length(ls);
        REQUIRE(len == Approx(0.0));
    }

    SECTION("length of single point linestring")
    {
        LineString ls{{0, 0}};
        auto len = length(ls);
        REQUIRE(len == Approx(0.0));
    }

    SECTION("length of straight line")
    {
        LineString ls{{0, 0}, {3, 4}};
        auto len = length(ls);
        REQUIRE(len == Approx(5.0));
    }

    SECTION("length of multi-segment linestring")
    {
        // Right triangle: 3-4-5
        LineString ls{{0, 0}, {3, 0}, {3, 4}};
        auto len = length(ls);
        REQUIRE(len == Approx(7.0));  // 3 + 4
    }

    SECTION("length via geometry method")
    {
        LineString ls{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
        auto len = ls.length();
        REQUIRE(len == Approx(3.0));  // Square perimeter minus one side
    }

    SECTION("length of zigzag line")
    {
        LineString ls{{0, 0}, {1, 1}, {2, 0}, {3, 1}};
        auto len = length(ls);
        double expected = std::sqrt(2) + std::sqrt(2) + std::sqrt(2);
        REQUIRE(len == Approx(expected));
    }
}

TEST_CASE("Measurements - Area")
{
    SECTION("area of empty polygon")
    {
        Polygon poly;
        auto a = area(poly);
        REQUIRE(a == Approx(0.0));
    }

    SECTION("area of square")
    {
        Polygon poly{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(16.0));
    }

    SECTION("area of rectangle")
    {
        Polygon poly{{{0, 0}, {5, 0}, {5, 3}, {0, 3}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(15.0));
    }

    SECTION("area of triangle")
    {
        // Right triangle with legs 3 and 4
        Polygon poly{{{0, 0}, {3, 0}, {0, 4}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(6.0));
    }

    SECTION("area via geometry method")
    {
        Polygon poly{{{0, 0}, {10, 0}, {10, 10}, {0, 10}, {0, 0}}};
        auto a = poly.area();
        REQUIRE(a == Approx(100.0));
    }

    SECTION("area with hole")
    {
        // Outer square 10x10, inner square 4x4
        Polygon poly{
            {{0, 0}, {10, 0}, {10, 10}, {0, 10}, {0, 0}},  // Exterior
            {{3, 3}, {7, 3}, {7, 7}, {3, 7}, {3, 3}}       // Hole
        };
        auto a = area(poly);
        // Outer: 100, Hole: 16, Result: 84
        REQUIRE(a == Approx(84.0));
    }

    SECTION("area independent of winding order")
    {
        // Counter-clockwise
        Polygon poly1{{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}}};
        // Clockwise
        Polygon poly2{{{0, 0}, {0, 3}, {4, 3}, {4, 0}, {0, 0}}};

        auto a1 = area(poly1);
        auto a2 = area(poly2);
        REQUIRE(a1 == Approx(a2));
        REQUIRE(a1 == Approx(12.0));
    }

    SECTION("area of complex polygon")
    {
        // L-shaped polygon
        Polygon poly{{{0, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(3.0));  // 2x1 + 1x1
    }
}

TEST_CASE("Measurements - Perimeter")
{
    SECTION("perimeter of empty polygon")
    {
        Polygon poly;
        auto p = perimeter(poly);
        REQUIRE(p == Approx(0.0));
    }

    SECTION("perimeter of square")
    {
        Polygon poly{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};
        auto p = perimeter(poly);
        REQUIRE(p == Approx(16.0));
    }

    SECTION("perimeter of rectangle")
    {
        Polygon poly{{{0, 0}, {5, 0}, {5, 3}, {0, 3}, {0, 0}}};
        auto p = perimeter(poly);
        REQUIRE(p == Approx(16.0));  // 2*(5+3)
    }

    SECTION("perimeter of triangle")
    {
        // 3-4-5 right triangle
        Polygon poly{{{0, 0}, {3, 0}, {0, 4}, {0, 0}}};
        auto p = perimeter(poly);
        REQUIRE(p == Approx(12.0));  // 3 + 4 + 5
    }

    SECTION("perimeter ignores holes")
    {
        // Only exterior ring is considered for perimeter
        Polygon poly{
            {{0, 0}, {10, 0}, {10, 10}, {0, 10}, {0, 0}},  // Exterior
            {{2, 2}, {8, 2}, {8, 8}, {2, 8}, {2, 2}}       // Hole (ignored)
        };
        auto p = perimeter(poly);
        REQUIRE(p == Approx(40.0));  // Only exterior: 4*10
    }
}

TEST_CASE("Measurements - Signed Area")
{
    SECTION("counter-clockwise gives positive area")
    {
        LineString ring{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};
        auto a = signed_area_ring(ring);
        REQUIRE(a > 0);
    }

    SECTION("clockwise gives negative area")
    {
        LineString ring{{0, 0}, {0, 3}, {4, 3}, {4, 0}, {0, 0}};
        auto a = signed_area_ring(ring);
        REQUIRE(a < 0);
    }

    SECTION("absolute values are equal")
    {
        LineString ccw{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}};
        LineString cw{{0, 0}, {0, 3}, {4, 3}, {4, 0}, {0, 0}};

        auto a1 = signed_area_ring(ccw);
        auto a2 = signed_area_ring(cw);

        REQUIRE(std::abs(a1) == Approx(std::abs(a2)));
    }
}

TEST_CASE("Measurements - Edge Cases")
{
    SECTION("degenerate polygon (line)")
    {
        Polygon poly{{{0, 0}, {1, 0}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(0.0));
    }

    SECTION("degenerate polygon (point)")
    {
        Polygon poly{{{0, 0}, {0, 0}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(0.0));
    }

    SECTION("very small polygon")
    {
        Polygon poly{{{0, 0}, {0.001, 0}, {0.001, 0.001}, {0, 0.001}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(0.000001).epsilon(0.01));
    }

    SECTION("very large polygon")
    {
        Polygon poly{{{0, 0}, {1e6, 0}, {1e6, 1e6}, {0, 1e6}, {0, 0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(1e12));
    }
}

TEST_CASE("Measurements - Precision")
{
    SECTION("distance with high precision coordinates")
    {
        Point p1{1.123456789, 2.987654321};
        Point p2{3.111111111, 4.222222222};

        double dx = 3.111111111 - 1.123456789;
        double dy = 4.222222222 - 2.987654321;
        double expected = std::sqrt(dx*dx + dy*dy);

        auto d = distance(p1, p2);
        REQUIRE(d == Approx(expected));
    }

    SECTION("area with high precision")
    {
        Polygon poly{{{0.0, 0.0}, {1.5, 0.0}, {1.5, 2.5}, {0.0, 2.5}, {0.0, 0.0}}};
        auto a = area(poly);
        REQUIRE(a == Approx(3.75));
    }
}
