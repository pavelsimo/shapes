#include <catch/catch.hpp>
#include <simo/shapes.hpp>
#include <cmath>

using namespace simo::shapes;
using namespace simo::shapes::algorithm;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

TEST_CASE("Transformations - Translate Point")
{
    SECTION("translate point by positive offset")
    {
        Point p{1, 2};
        auto result = translate(p, 3.0, 4.0);

        REQUIRE(result.x == Approx(4.0));
        REQUIRE(result.y == Approx(6.0));
    }

    SECTION("translate point by negative offset")
    {
        Point p{5, 8};
        auto result = translate(p, -2.0, -3.0);

        REQUIRE(result.x == Approx(3.0));
        REQUIRE(result.y == Approx(5.0));
    }

    SECTION("translate point by zero")
    {
        Point p{3, 7};
        auto result = translate(p, 0.0, 0.0);

        REQUIRE(result.x == Approx(3.0));
        REQUIRE(result.y == Approx(7.0));
    }
}

TEST_CASE("Transformations - Translate LineString")
{
    SECTION("translate linestring")
    {
        LineString ls{{0, 0}, {1, 1}, {2, 0}};
        auto result = translate(ls, 10.0, 20.0);

        REQUIRE(result.size() == 3);
        REQUIRE(result[0].x == Approx(10.0));
        REQUIRE(result[0].y == Approx(20.0));
        REQUIRE(result[1].x == Approx(11.0));
        REQUIRE(result[1].y == Approx(21.0));
        REQUIRE(result[2].x == Approx(12.0));
        REQUIRE(result[2].y == Approx(20.0));
    }

    SECTION("translate via geometry method")
    {
        LineString ls{{0, 0}, {4, 4}};
        auto result = ls.translate(5.0, 5.0);

        REQUIRE(result[0].x == Approx(5.0));
        REQUIRE(result[0].y == Approx(5.0));
        REQUIRE(result[1].x == Approx(9.0));
        REQUIRE(result[1].y == Approx(9.0));
    }
}

TEST_CASE("Transformations - Translate Polygon")
{
    SECTION("translate polygon")
    {
        Polygon poly{{{0, 0}, {4, 0}, {4, 3}, {0, 3}, {0, 0}}};
        auto result = translate(poly, 2.0, 5.0);

        REQUIRE(result.size() == 1);
        REQUIRE(result[0][0].x == Approx(2.0));
        REQUIRE(result[0][0].y == Approx(5.0));
        REQUIRE(result[0][1].x == Approx(6.0));
        REQUIRE(result[0][1].y == Approx(5.0));
    }

    SECTION("translate polygon with hole")
    {
        Polygon poly{
            {{0, 0}, {10, 0}, {10, 10}, {0, 10}, {0, 0}},
            {{2, 2}, {8, 2}, {8, 8}, {2, 8}, {2, 2}}
        };
        auto result = translate(poly, 5.0, 5.0);

        REQUIRE(result.size() == 2);  // Exterior + hole
        REQUIRE(result[0][0].x == Approx(5.0));
        REQUIRE(result[1][0].x == Approx(7.0));  // Hole also translated
    }
}

TEST_CASE("Transformations - Rotate Point")
{
    SECTION("rotate point 90 degrees")
    {
        Point p{1, 0};
        auto result = rotate(p, M_PI / 2);  // 90 degrees

        REQUIRE(result.x == Approx(0.0).margin(1e-10));
        REQUIRE(result.y == Approx(1.0));
    }

    SECTION("rotate point 180 degrees")
    {
        Point p{1, 0};
        auto result = rotate(p, M_PI);  // 180 degrees

        REQUIRE(result.x == Approx(-1.0));
        REQUIRE(result.y == Approx(0.0).margin(1e-10));
    }

    SECTION("rotate point 360 degrees")
    {
        Point p{3, 4};
        auto result = rotate(p, 2 * M_PI);  // 360 degrees

        REQUIRE(result.x == Approx(3.0));
        REQUIRE(result.y == Approx(4.0));
    }

    SECTION("rotate around custom origin")
    {
        Point p{2, 0};
        Point origin{1, 0};
        auto result = rotate(p, M_PI / 2, origin);  // 90 degrees around (1,0)

        REQUIRE(result.x == Approx(1.0));
        REQUIRE(result.y == Approx(1.0));
    }

    SECTION("rotate via geometry method")
    {
        Point p{1, 0};
        auto result = p.rotate(M_PI / 2);

        REQUIRE(result.x == Approx(0.0).margin(1e-10));
        REQUIRE(result.y == Approx(1.0));
    }
}

TEST_CASE("Transformations - Rotate LineString")
{
    SECTION("rotate square linestring 90 degrees")
    {
        LineString ls{{1, 0}, {0, 0}, {0, 1}};
        auto result = rotate(ls, M_PI / 2);

        REQUIRE(result[0].x == Approx(0.0).margin(1e-10));
        REQUIRE(result[0].y == Approx(1.0));
        REQUIRE(result[1].x == Approx(0.0).margin(1e-10));
        REQUIRE(result[1].y == Approx(0.0).margin(1e-10));
        REQUIRE(result[2].x == Approx(-1.0));
        REQUIRE(result[2].y == Approx(0.0).margin(1e-10));
    }

    SECTION("rotate around center")
    {
        LineString ls{{0, 0}, {2, 0}};
        Point center{1, 0};
        auto result = rotate(ls, M_PI, center);  // 180 degrees around center

        // Points should swap positions
        REQUIRE(result[0].x == Approx(2.0));
        REQUIRE(result[1].x == Approx(0.0));
    }
}

TEST_CASE("Transformations - Rotate Polygon")
{
    SECTION("rotate square 45 degrees")
    {
        Polygon square{{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}};
        auto result = rotate(square, M_PI / 4);  // 45 degrees

        // Square becomes diamond
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].size() == 5);

        // After 45deg rotation, corners should move
        double sqrt2_2 = std::sqrt(2.0) / 2.0;
        REQUIRE(result[0][1].x == Approx(sqrt2_2).margin(1e-10));
    }

    SECTION("rotate around polygon center")
    {
        Polygon square{{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}}};
        Point origin{0, 0};
        auto result = rotate(square, M_PI / 2, origin);

        // Rotation around center should preserve symmetry
        REQUIRE(result.size() == 1);
    }
}

TEST_CASE("Transformations - Scale Point")
{
    SECTION("scale point by 2")
    {
        Point p{3, 4};
        auto result = scale(p, 2.0, 2.0);

        REQUIRE(result.x == Approx(6.0));
        REQUIRE(result.y == Approx(8.0));
    }

    SECTION("scale point by 0.5")
    {
        Point p{8, 12};
        auto result = scale(p, 0.5, 0.5);

        REQUIRE(result.x == Approx(4.0));
        REQUIRE(result.y == Approx(6.0));
    }

    SECTION("scale with different factors")
    {
        Point p{2, 3};
        auto result = scale(p, 3.0, 2.0);

        REQUIRE(result.x == Approx(6.0));
        REQUIRE(result.y == Approx(6.0));
    }

    SECTION("scale around custom origin")
    {
        Point p{4, 4};
        Point origin{2, 2};
        auto result = scale(p, 2.0, 2.0, origin);

        // Distance from origin should double
        REQUIRE(result.x == Approx(6.0));  // 2 + 2*(4-2)
        REQUIRE(result.y == Approx(6.0));
    }

    SECTION("scale via geometry method")
    {
        Point p{1, 2};
        auto result = p.scale(3.0, 3.0);

        REQUIRE(result.x == Approx(3.0));
        REQUIRE(result.y == Approx(6.0));
    }

    SECTION("scale by negative factor (mirror)")
    {
        Point p{3, 4};
        auto result = scale(p, -1.0, 1.0);

        REQUIRE(result.x == Approx(-3.0));
        REQUIRE(result.y == Approx(4.0));
    }
}

TEST_CASE("Transformations - Scale LineString")
{
    SECTION("scale linestring by 2")
    {
        LineString ls{{0, 0}, {1, 1}, {2, 0}};
        auto result = scale(ls, 2.0, 2.0);

        REQUIRE(result[0].x == Approx(0.0));
        REQUIRE(result[0].y == Approx(0.0));
        REQUIRE(result[1].x == Approx(2.0));
        REQUIRE(result[1].y == Approx(2.0));
        REQUIRE(result[2].x == Approx(4.0));
        REQUIRE(result[2].y == Approx(0.0));
    }

    SECTION("scale with different x and y factors")
    {
        LineString ls{{1, 1}, {2, 2}};
        auto result = scale(ls, 2.0, 3.0);

        REQUIRE(result[0].x == Approx(2.0));
        REQUIRE(result[0].y == Approx(3.0));
        REQUIRE(result[1].x == Approx(4.0));
        REQUIRE(result[1].y == Approx(6.0));
    }
}

TEST_CASE("Transformations - Scale Polygon")
{
    SECTION("scale square by 2")
    {
        Polygon square{{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}};
        auto result = scale(square, 2.0, 2.0);

        auto orig_area = area(square);
        auto new_area = area(result);

        // Area should be 4x (2^2)
        REQUIRE(new_area == Approx(orig_area * 4.0));
    }

    SECTION("scale rectangle with different factors")
    {
        Polygon rect{{{0, 0}, {4, 0}, {4, 2}, {0, 2}, {0, 0}}};
        auto result = scale(rect, 0.5, 2.0);

        // Width halved, height doubled
        auto new_area = area(result);
        REQUIRE(new_area == Approx(8.0));  // 2 * 4 (original was 8)
    }

    SECTION("scale polygon around center")
    {
        Polygon square{{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}}};
        Point origin{0, 0};
        auto result = scale(square, 2.0, 2.0, origin);

        // Square centered at origin, scaled 2x
        REQUIRE(result[0][0].x == Approx(-2.0));
        REQUIRE(result[0][1].x == Approx(2.0));
    }
}

TEST_CASE("Transformations - Composition")
{
    SECTION("translate then rotate")
    {
        Point p{1, 0};
        auto translated = translate(p, 1.0, 0.0);  // Now at (2, 0)
        auto rotated = rotate(translated, M_PI / 2);  // Rotate 90deg

        REQUIRE(rotated.x == Approx(0.0).margin(1e-10));
        REQUIRE(rotated.y == Approx(2.0));
    }

    SECTION("rotate then translate")
    {
        Point p{1, 0};
        auto rotated = rotate(p, M_PI / 2);  // Now at (0, 1)
        auto translated = translate(rotated, 5.0, 5.0);  // Move to (5, 6)

        REQUIRE(translated.x == Approx(5.0));
        REQUIRE(translated.y == Approx(6.0));
    }

    SECTION("scale then translate")
    {
        Point p{2, 3};
        auto scaled = scale(p, 2.0, 2.0);  // Now at (4, 6)
        auto translated = translate(scaled, 1.0, 1.0);  // Move to (5, 7)

        REQUIRE(translated.x == Approx(5.0));
        REQUIRE(translated.y == Approx(7.0));
    }

    SECTION("translate, rotate, scale")
    {
        LineString ls{{0, 0}, {1, 0}};

        auto t1 = translate(ls, 1.0, 0.0);  // Move to (1,0)-(2,0)
        auto t2 = rotate(t1, M_PI / 2);      // Rotate 90deg
        auto t3 = scale(t2, 2.0, 2.0);       // Scale 2x

        REQUIRE(t3.size() == 2);
    }
}

TEST_CASE("Transformations - Preserves Properties")
{
    SECTION("translation preserves distance")
    {
        LineString ls{{0, 0}, {3, 4}};
        auto orig_len = length(ls);

        auto translated = translate(ls, 10.0, 20.0);
        auto new_len = length(translated);

        REQUIRE(new_len == Approx(orig_len));
    }

    SECTION("rotation preserves distance")
    {
        LineString ls{{0, 0}, {3, 4}};
        auto orig_len = length(ls);

        auto rotated = rotate(ls, M_PI / 4);
        auto new_len = length(rotated);

        REQUIRE(new_len == Approx(orig_len));
    }

    SECTION("uniform scaling multiplies distances")
    {
        LineString ls{{0, 0}, {3, 4}};
        auto orig_len = length(ls);

        auto scaled = scale(ls, 2.0, 2.0);
        auto new_len = length(scaled);

        REQUIRE(new_len == Approx(orig_len * 2.0));
    }

    SECTION("rotation preserves area")
    {
        Polygon square{{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}};
        auto orig_area = area(square);

        auto rotated = rotate(square, M_PI / 4);
        auto new_area = area(rotated);

        REQUIRE(new_area == Approx(orig_area));
    }

    SECTION("uniform scaling multiplies area by square")
    {
        Polygon square{{{0, 0}, {2, 0}, {2, 2}, {0, 2}, {0, 0}}};
        auto orig_area = area(square);

        auto scaled = scale(square, 3.0, 3.0);
        auto new_area = area(scaled);

        REQUIRE(new_area == Approx(orig_area * 9.0));  // 3^2
    }
}

TEST_CASE("Transformations - Edge Cases")
{
    SECTION("rotate by zero")
    {
        Point p{3, 4};
        auto result = rotate(p, 0.0);

        REQUIRE(result.x == Approx(3.0));
        REQUIRE(result.y == Approx(4.0));
    }

    SECTION("scale by 1 (identity)")
    {
        Point p{3, 4};
        auto result = scale(p, 1.0, 1.0);

        REQUIRE(result.x == Approx(3.0));
        REQUIRE(result.y == Approx(4.0));
    }

    SECTION("scale by 0")
    {
        Point p{3, 4};
        auto result = scale(p, 0.0, 0.0);

        REQUIRE(result.x == Approx(0.0));
        REQUIRE(result.y == Approx(0.0));
    }

    SECTION("translate empty geometry")
    {
        LineString empty;
        auto result = translate(empty, 5.0, 5.0);

        REQUIRE(result.empty());
    }

    SECTION("rotate empty geometry")
    {
        Polygon empty;
        auto result = rotate(empty, M_PI / 2);

        REQUIRE(result.empty());
    }

    SECTION("scale empty geometry")
    {
        LineString empty;
        auto result = scale(empty, 2.0, 2.0);

        REQUIRE(result.empty());
    }
}
