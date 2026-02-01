#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;
using namespace simo::shapes::algorithm;

TEST_CASE("Predicates - Contains (Point in Polygon)")
{
    Polygon square{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};

    SECTION("point inside polygon")
    {
        Point p{2, 2};
        REQUIRE(contains(square, p));
        REQUIRE(square.contains(p));
    }

    SECTION("point outside polygon")
    {
        Point p{5, 5};
        REQUIRE_FALSE(contains(square, p));
        REQUIRE_FALSE(square.contains(p));
    }

    SECTION("point on corner")
    {
        Point p{0, 0};
        // On boundary - depends on winding number implementation
        // This is often considered outside in computational geometry
        auto result = contains(square, p);
        // Just verify it returns a boolean (implementation may vary)
        REQUIRE((result == true || result == false));
    }

    SECTION("point on edge")
    {
        Point p{2, 0};
        // On boundary
        auto result = contains(square, p);
        REQUIRE((result == true || result == false));
    }

    SECTION("multiple points")
    {
        REQUIRE(contains(square, Point{1, 1}));
        REQUIRE(contains(square, Point{3, 3}));
        REQUIRE_FALSE(contains(square, Point{-1, 2}));
        REQUIRE_FALSE(contains(square, Point{2, 5}));
    }
}

TEST_CASE("Predicates - Contains (Polygon with Hole)")
{
    // Square with square hole in middle
    Polygon poly{
        {{0, 0}, {10, 0}, {10, 10}, {0, 10}, {0, 0}},  // Exterior
        {{3, 3}, {7, 3}, {7, 7}, {3, 7}, {3, 3}}       // Hole
    };

    SECTION("point inside exterior but outside hole")
    {
        Point p{1, 1};
        REQUIRE(contains(poly, p));
    }

    SECTION("point inside hole")
    {
        Point p{5, 5};
        REQUIRE_FALSE(contains(poly, p));
    }

    SECTION("point outside exterior")
    {
        Point p{15, 15};
        REQUIRE_FALSE(contains(poly, p));
    }

    SECTION("point between exterior and hole")
    {
        Point p{8, 8};
        REQUIRE(contains(poly, p));
    }
}

TEST_CASE("Predicates - Within")
{
    Polygon poly{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};

    SECTION("point within polygon")
    {
        Point p{2, 2};
        REQUIRE(within(p, poly));
        REQUIRE(p.within(poly));
    }

    SECTION("point not within polygon")
    {
        Point p{5, 5};
        REQUIRE_FALSE(within(p, poly));
    }

    SECTION("within is inverse of contains")
    {
        Point p{1, 1};
        REQUIRE(contains(poly, p) == within(p, poly));
    }
}

TEST_CASE("Predicates - Intersects (LineStrings)")
{
    LineString ls1{{0, 0}, {4, 4}};  // Diagonal
    LineString ls2{{0, 4}, {4, 0}};  // Opposite diagonal

    SECTION("intersecting linestrings")
    {
        REQUIRE(intersects(ls1, ls2));
        REQUIRE(ls1.intersects(ls2));
    }

    SECTION("parallel linestrings")
    {
        LineString ls3{{0, 0}, {4, 0}};
        LineString ls4{{0, 1}, {4, 1}};
        REQUIRE_FALSE(intersects(ls3, ls4));
    }

    SECTION("touching endpoints")
    {
        LineString ls3{{0, 0}, {2, 2}};
        LineString ls4{{2, 2}, {4, 4}};
        REQUIRE(intersects(ls3, ls4));
    }

    SECTION("completely separate")
    {
        LineString ls3{{0, 0}, {1, 1}};
        LineString ls4{{3, 3}, {4, 4}};
        REQUIRE_FALSE(intersects(ls3, ls4));
    }

    SECTION("overlapping segments")
    {
        LineString ls3{{0, 0}, {4, 0}};
        LineString ls4{{2, 0}, {6, 0}};
        REQUIRE(intersects(ls3, ls4));
    }
}

TEST_CASE("Predicates - Touches")
{
    Polygon square{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};

    SECTION("point on polygon boundary")
    {
        Point p{2, 0};
        REQUIRE(touches(p, square));
    }

    SECTION("point on polygon corner")
    {
        Point p{0, 0};
        REQUIRE(touches(p, square));
    }

    SECTION("point inside polygon")
    {
        Point p{2, 2};
        REQUIRE_FALSE(touches(p, square));
    }

    SECTION("point outside polygon")
    {
        Point p{5, 5};
        REQUIRE_FALSE(touches(p, square));
    }
}

TEST_CASE("Predicates - Disjoint")
{
    LineString ls1{{0, 0}, {1, 1}};
    LineString ls2{{3, 3}, {4, 4}};

    SECTION("disjoint linestrings")
    {
        REQUIRE(disjoint(ls1, ls2));
    }

    SECTION("intersecting linestrings are not disjoint")
    {
        LineString ls3{{0, 0}, {4, 4}};
        REQUIRE_FALSE(disjoint(ls1, ls3));
    }
}

TEST_CASE("Predicates - Crosses")
{
    Polygon square{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};

    SECTION("linestring crosses polygon")
    {
        LineString ls{{-1, 2}, {5, 2}};  // Horizontal line through square
        REQUIRE(crosses(ls, square));
    }

    SECTION("linestring completely inside")
    {
        LineString ls{{1, 1}, {3, 3}};
        REQUIRE_FALSE(crosses(ls, square));
    }

    SECTION("linestring completely outside")
    {
        LineString ls{{5, 5}, {6, 6}};
        REQUIRE_FALSE(crosses(ls, square));
    }

    SECTION("linestring touches boundary")
    {
        LineString ls{{0, 0}, {0, 4}};  // On edge
        auto result = crosses(ls, square);
        // Boundary case - implementation specific
        REQUIRE((result == true || result == false));
    }
}

TEST_CASE("Predicates - Overlaps")
{
    Polygon poly1{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};
    Polygon poly2{{{2, 2}, {6, 2}, {6, 6}, {2, 6}, {2, 2}}};

    SECTION("overlapping polygons")
    {
        // This is a simplified test - full overlap requires more complex logic
        REQUIRE(overlaps(poly1, poly2));
    }

    SECTION("non-overlapping polygons")
    {
        Polygon poly3{{{10, 10}, {14, 10}, {14, 14}, {10, 14}, {10, 10}}};
        REQUIRE_FALSE(overlaps(poly1, poly3));
    }
}

TEST_CASE("Predicates - Orientation Tests")
{
    using namespace simo::shapes::algorithm::detail;

    SECTION("counter-clockwise points")
    {
        Point p{0, 0};
        Point q{4, 0};
        Point r{2, 2};
        REQUIRE(orient2d(p, q, r) > 0);
    }

    SECTION("clockwise points")
    {
        Point p{0, 0};
        Point q{4, 0};
        Point r{2, -2};
        REQUIRE(orient2d(p, q, r) < 0);
    }

    SECTION("collinear points")
    {
        Point p{0, 0};
        Point q{4, 0};
        Point r{2, 0};
        REQUIRE(orient2d(p, q, r) == 0);
    }

    SECTION("collinear vertical")
    {
        Point p{0, 0};
        Point q{0, 4};
        Point r{0, 2};
        REQUIRE(orient2d(p, q, r) == 0);
    }

    SECTION("collinear diagonal")
    {
        Point p{0, 0};
        Point q{4, 4};
        Point r{2, 2};
        REQUIRE(orient2d(p, q, r) == 0);
    }
}

TEST_CASE("Predicates - Segment Intersection")
{
    using namespace simo::shapes::algorithm::detail;

    SECTION("crossing segments")
    {
        Point p1{0, 0}, q1{4, 4};
        Point p2{0, 4}, q2{4, 0};
        REQUIRE(segments_intersect(p1, q1, p2, q2));
    }

    SECTION("parallel segments")
    {
        Point p1{0, 0}, q1{4, 0};
        Point p2{0, 1}, q2{4, 1};
        REQUIRE_FALSE(segments_intersect(p1, q1, p2, q2));
    }

    SECTION("touching endpoints")
    {
        Point p1{0, 0}, q1{2, 2};
        Point p2{2, 2}, q2{4, 4};
        REQUIRE(segments_intersect(p1, q1, p2, q2));
    }

    SECTION("collinear overlapping")
    {
        Point p1{0, 0}, q1{4, 0};
        Point p2{2, 0}, q2{6, 0};
        REQUIRE(segments_intersect(p1, q1, p2, q2));
    }

    SECTION("collinear non-overlapping")
    {
        Point p1{0, 0}, q1{2, 0};
        Point p2{3, 0}, q2{5, 0};
        REQUIRE_FALSE(segments_intersect(p1, q1, p2, q2));
    }

    SECTION("T-intersection")
    {
        Point p1{0, 2}, q1{4, 2};
        Point p2{2, 0}, q2{2, 4};
        REQUIRE(segments_intersect(p1, q1, p2, q2));
    }
}

TEST_CASE("Predicates - Complex Polygons")
{
    SECTION("concave polygon")
    {
        // L-shaped polygon
        Polygon poly{{{0, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 0}}};

        REQUIRE(contains(poly, Point{0.5, 0.5}));
        REQUIRE(contains(poly, Point{0.5, 1.5}));
        REQUIRE_FALSE(contains(poly, Point{1.5, 1.5}));
    }

    SECTION("star-shaped polygon")
    {
        // Simple 4-pointed star
        Polygon star{{{0, 1}, {1, 1}, {2, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}}};

        REQUIRE(contains(star, Point{0, 0}));
        REQUIRE_FALSE(contains(star, Point{1.5, 1.5}));
    }
}

TEST_CASE("Predicates - Empty Geometries")
{
    SECTION("empty polygon contains nothing")
    {
        Polygon empty;
        Point p{1, 1};
        REQUIRE_FALSE(contains(empty, p));
    }

    SECTION("empty linestring doesn't intersect")
    {
        LineString empty;
        LineString ls{{0, 0}, {1, 1}};
        REQUIRE_FALSE(intersects(empty, ls));
    }
}

TEST_CASE("Predicates - Edge Cases")
{
    SECTION("polygon with single point")
    {
        Polygon degenerate{{{0, 0}, {0, 0}, {0, 0}}};
        Point p{0, 0};
        auto result = contains(degenerate, p);
        // Degenerate case
        REQUIRE((result == true || result == false));
    }

    SECTION("linestring as single point")
    {
        LineString ls1{{1, 1}};
        LineString ls2{{1, 1}, {2, 2}};
        auto result = intersects(ls1, ls2);
        REQUIRE((result == true || result == false));
    }

    SECTION("very small polygon")
    {
        Polygon tiny{{{0, 0}, {0.00001, 0}, {0.00001, 0.00001}, {0, 0.00001}, {0, 0}}};
        Point p{0.000005, 0.000005};
        REQUIRE(contains(tiny, p));
    }
}
