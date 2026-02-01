#include <catch/catch.hpp>
#include <simo/shapes.hpp>

using namespace simo::shapes;
using namespace simo::shapes::algorithm;

TEST_CASE("Operations - Convex Hull")
{
    SECTION("convex hull of triangle")
    {
        MultiPoint points{{0, 0}, {4, 0}, {2, 3}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        REQUIRE(hull.size() == 1);  // One ring
        REQUIRE(hull[0].size() == 4);  // 3 points + closing point
    }

    SECTION("convex hull of square points")
    {
        MultiPoint points{{0, 0}, {4, 0}, {4, 4}, {0, 4}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        REQUIRE(hull.size() == 1);
        REQUIRE(hull[0].size() == 5);  // 4 points + closing
    }

    SECTION("convex hull removes interior points")
    {
        // Square with center point
        MultiPoint points{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {2, 2}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        // Should only have 4 corners + closing
        REQUIRE(hull[0].size() == 5);
    }

    SECTION("convex hull of collinear points")
    {
        MultiPoint points{{0, 0}, {1, 1}, {2, 2}, {3, 3}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        // Degenerate case - should have 2 points + closing (or similar)
        REQUIRE(hull.size() >= 1);
    }

    SECTION("convex hull of single point")
    {
        MultiPoint points{{1, 1}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        REQUIRE(hull.size() == 1);
    }

    SECTION("convex hull of two points")
    {
        MultiPoint points{{0, 0}, {4, 4}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        REQUIRE(hull.size() == 1);
    }

    SECTION("convex hull with duplicate points")
    {
        MultiPoint points{{0, 0}, {4, 0}, {4, 0}, {4, 4}, {0, 4}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        REQUIRE(hull.size() == 1);
    }

    SECTION("convex hull of pentagon")
    {
        // Regular pentagon-ish points
        MultiPoint points{{0, 0}, {2, -1}, {4, 0}, {3, 2}, {1, 2}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        // Should form convex polygon
        REQUIRE(hull.size() == 1);
        REQUIRE(hull[0].size() >= 4);  // At least 3 points + closing
    }
}

TEST_CASE("Operations - Simplify (Douglas-Peucker)")
{
    SECTION("simplify straight line")
    {
        LineString ls{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
        auto simplified = simplify(ls, 0.1);

        // Should reduce to just endpoints
        REQUIRE(simplified.size() == 2);
        REQUIRE(simplified[0].x == Approx(0.0));
        REQUIRE(simplified[1].x == Approx(4.0));
    }

    SECTION("simplify zigzag with high tolerance")
    {
        LineString ls{{0, 0}, {1, 1}, {2, 0}, {3, 1}, {4, 0}};
        auto simplified = simplify(ls, 2.0);  // High tolerance

        // Should simplify significantly
        REQUIRE(simplified.size() <= ls.size());
        REQUIRE(simplified.size() >= 2);  // At least start and end
    }

    SECTION("simplify zigzag with low tolerance")
    {
        LineString ls{{0, 0}, {1, 1}, {2, 0}, {3, 1}, {4, 0}};
        auto simplified = simplify(ls, 0.1);  // Low tolerance

        // Should keep most points
        REQUIRE(simplified.size() == ls.size());
    }

    SECTION("simplify preserves endpoints")
    {
        LineString ls{{0, 0}, {1, 0.5}, {2, 0}, {3, 0.5}, {4, 0}};
        auto simplified = simplify(ls, 1.0);

        // Endpoints must be preserved
        REQUIRE(simplified.front().x == Approx(0.0));
        REQUIRE(simplified.front().y == Approx(0.0));
        REQUIRE(simplified.back().x == Approx(4.0));
        REQUIRE(simplified.back().y == Approx(0.0));
    }

    SECTION("simplify via geometry method")
    {
        LineString ls{{0, 0}, {1, 0}, {2, 0}, {3, 0}};
        auto simplified = ls.simplify(0.1);

        REQUIRE(simplified.size() == 2);
    }

    SECTION("simplify empty linestring")
    {
        LineString ls;
        auto simplified = simplify(ls, 1.0);

        REQUIRE(simplified.empty());
    }

    SECTION("simplify single point")
    {
        LineString ls{{1, 1}};
        auto simplified = simplify(ls, 1.0);

        REQUIRE(simplified.size() == 1);
    }

    SECTION("simplify two points")
    {
        LineString ls{{0, 0}, {4, 4}};
        auto simplified = simplify(ls, 1.0);

        REQUIRE(simplified.size() == 2);
    }
}

TEST_CASE("Operations - Envelope")
{
    SECTION("envelope of point")
    {
        Point p{2, 3};
        auto env = envelope<Point, Polygon>(p);

        REQUIRE(env.size() == 1);  // One ring
        REQUIRE(env[0].size() == 5);  // 4 corners + closing

        // All corners should be at the point
        for (const auto& pt : env[0])
        {
            REQUIRE(pt.x == Approx(2.0));
            REQUIRE(pt.y == Approx(3.0));
        }
    }

    SECTION("envelope of linestring")
    {
        LineString ls{{0, 0}, {4, 3}};
        auto env = envelope<LineString, Polygon>(ls);

        auto bounds = ls.bounds();
        REQUIRE(env[0][0].x == Approx(bounds.minx));
        REQUIRE(env[0][0].y == Approx(bounds.miny));
        REQUIRE(env[0][2].x == Approx(bounds.maxx));
        REQUIRE(env[0][2].y == Approx(bounds.maxy));
    }

    SECTION("envelope of polygon")
    {
        Polygon poly{{{1, 1}, {5, 2}, {4, 6}, {2, 5}, {1, 1}}};
        auto env = envelope<Polygon, Polygon>(poly);

        auto bounds = poly.bounds();

        // Check corners
        REQUIRE(env[0][0].x == Approx(bounds.minx));
        REQUIRE(env[0][0].y == Approx(bounds.miny));
        REQUIRE(env[0][1].x == Approx(bounds.maxx));
        REQUIRE(env[0][2].y == Approx(bounds.maxy));
    }

    SECTION("envelope forms valid polygon")
    {
        LineString ls{{-2, -3}, {5, 7}};
        auto env = envelope<LineString, Polygon>(ls);

        REQUIRE(env[0].size() == 5);
        REQUIRE(env[0][0].x == env[0][4].x);  // Closed
        REQUIRE(env[0][0].y == env[0][4].y);
    }
}

TEST_CASE("Operations - Centroid")
{
    SECTION("centroid of square")
    {
        Polygon square{{{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 0}}};
        auto c = centroid<Polygon, Point>(square);

        REQUIRE(c.x == Approx(2.0));
        REQUIRE(c.y == Approx(2.0));
    }

    SECTION("centroid of triangle")
    {
        Polygon tri{{{0, 0}, {6, 0}, {3, 6}, {0, 0}}};
        auto c = centroid<Polygon, Point>(tri);

        // Centroid of triangle is average of vertices
        REQUIRE(c.x == Approx(3.0));
        REQUIRE(c.y == Approx(2.0));
    }

    SECTION("centroid of rectangle")
    {
        Polygon rect{{{0, 0}, {8, 0}, {8, 4}, {0, 4}, {0, 0}}};
        auto c = centroid<Polygon, Point>(rect);

        REQUIRE(c.x == Approx(4.0));
        REQUIRE(c.y == Approx(2.0));
    }

    SECTION("centroid of empty polygon")
    {
        Polygon empty;
        auto c = centroid<Polygon, Point>(empty);

        REQUIRE(c.x == Approx(0.0));
        REQUIRE(c.y == Approx(0.0));
    }

    SECTION("centroid of L-shaped polygon")
    {
        // L-shape: (0,0)-(2,0)-(2,1)-(1,1)-(1,2)-(0,2)-(0,0)
        Polygon lshape{{{0, 0}, {2, 0}, {2, 1}, {1, 1}, {1, 2}, {0, 2}, {0, 0}}};
        auto c = centroid<Polygon, Point>(lshape);

        // Centroid should be offset from center
        REQUIRE(c.x < 1.0);  // Toward left
        REQUIRE(c.y < 1.0);  // Toward bottom
    }
}

TEST_CASE("Operations - Complex Cases")
{
    SECTION("convex hull then simplify")
    {
        MultiPoint points{{0, 0}, {1, 0.1}, {2, 0}, {2.1, 1}, {2, 2}, {1, 2.1}, {0, 2}, {-0.1, 1}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        // Hull should be a polygon
        REQUIRE(hull.size() == 1);

        // Convert hull ring to linestring for simplification
        LineString hull_ls(hull[0].begin(), hull[0].end());
        auto simplified = simplify(hull_ls, 0.5);

        // Should simplify to fewer points
        REQUIRE(simplified.size() <= hull[0].size());
    }

    SECTION("envelope of complex polygon")
    {
        // Star-like shape
        Polygon star{{{0, 1}, {1, 1}, {2, 0}, {1, -1}, {0, -1}, {-1, 0}, {0, 1}}};
        auto env = envelope<Polygon, Polygon>(star);

        auto bounds = star.bounds();
        auto env_area = area(env);
        auto star_area = area(star);

        // Envelope area should be >= polygon area
        REQUIRE(env_area >= star_area);
    }

    SECTION("centroid near geometric center")
    {
        // Regular hexagon-ish
        Polygon hex{{{1, 0}, {2, 0}, {3, 1}, {2, 2}, {1, 2}, {0, 1}, {1, 0}}};
        auto c = centroid<Polygon, Point>(hex);

        // Should be near center
        REQUIRE(c.x == Approx(1.5).margin(0.5));
        REQUIRE(c.y == Approx(1.0).margin(0.5));
    }
}

TEST_CASE("Operations - Edge Cases")
{
    SECTION("convex hull with all same points")
    {
        MultiPoint points{{1, 1}, {1, 1}, {1, 1}};
        auto hull = convex_hull<MultiPoint, Polygon>(points);

        REQUIRE(hull.size() >= 1);
    }

    SECTION("simplify with zero tolerance")
    {
        LineString ls{{0, 0}, {1, 0}, {2, 0}};
        auto simplified = simplify(ls, 0.0);

        // Zero tolerance - should keep all points
        REQUIRE(simplified.size() == ls.size());
    }

    SECTION("envelope of degenerate geometry")
    {
        LineString degenerate{{5, 5}};
        auto env = envelope<LineString, Polygon>(degenerate);

        REQUIRE(env.size() == 1);
        REQUIRE(env[0].size() == 5);
    }
}
