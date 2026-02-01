#pragma once

#include <ciso646>
#include <algorithm>
#include <vector>
#include <cmath>
#include <simo/algorithm/detail/orient2d.hpp>
#include <simo/algorithm/measurements.hpp>

namespace simo
{
namespace shapes
{
namespace algorithm
{

//
// CONVEX HULL (Graham Scan Algorithm)
//

/*! @brief Compute convex hull using Graham scan */
template <typename MultiPoint, typename Polygon>
Polygon convex_hull(const MultiPoint& points)
{
    if (points.size() < 3)
    {
        Polygon result;
        if (!points.empty())
        {
            typename Polygon::value_type ring;
            for (const auto& p : points)
            {
                ring.push_back(p);
            }
            if (!ring.empty())
            {
                ring.push_back(ring.front());  // Close the ring
            }
            result.push_back(ring);
        }
        return result;
    }

    // Find the lowest point (and leftmost if tie)
    using Point = typename MultiPoint::value_type;
    std::vector<Point> pts(points.begin(), points.end());

    auto lowest = std::min_element(pts.begin(), pts.end(),
                                     [](const Point& a, const Point& b) {
                                         return a.y < b.y || (a.y == b.y && a.x < b.x);
                                     });

    Point pivot = *lowest;

    // Sort points by polar angle with respect to pivot
    std::sort(pts.begin(), pts.end(),
              [&pivot](const Point& a, const Point& b) {
                  if (a.x == pivot.x && a.y == pivot.y) return true;
                  if (b.x == pivot.x && b.y == pivot.y) return false;

                  int o = detail::orient2d(pivot, a, b);
                  if (o == 0)
                  {
                      // Collinear: closer point comes first
                      return distance(pivot, a) < distance(pivot, b);
                  }
                  return o > 0;  // Counter-clockwise comes first
              });

    // Graham scan
    std::vector<Point> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);

    for (size_t i = 2; i < pts.size(); ++i)
    {
        // Remove points that make clockwise turn
        while (hull.size() > 1)
        {
            size_t n = hull.size();
            int o = detail::orient2d(hull[n - 2], hull[n - 1], pts[i]);
            if (o >= 0)  // Counter-clockwise or collinear
            {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }

    // Close the ring
    hull.push_back(hull.front());

    // Create polygon
    Polygon result;
    typename Polygon::value_type ring(hull.begin(), hull.end());
    result.push_back(ring);

    return result;
}

//
// SIMPLIFY (Douglas-Peucker Algorithm)
//

namespace detail
{

/*! @brief Perpendicular distance from point to line segment */
template <typename Point>
auto perpendicular_distance(const Point& point, const Point& line_start, const Point& line_end)
    -> decltype(point.x)
{
    auto dx = line_end.x - line_start.x;
    auto dy = line_end.y - line_start.y;

    auto mag = dx * dx + dy * dy;
    if (mag == 0)
    {
        return distance(point, line_start);
    }

    auto u = ((point.x - line_start.x) * dx + (point.y - line_start.y) * dy) / mag;

    if (u < 0)
    {
        return distance(point, line_start);
    }
    else if (u > 1)
    {
        return distance(point, line_end);
    }
    else
    {
        Point closest{line_start.x + u * dx, line_start.y + u * dy};
        return distance(point, closest);
    }
}

/*! @brief Recursive Douglas-Peucker simplification */
template <typename Point>
void douglas_peucker_recursive(const std::vector<Point>& points, size_t start, size_t end,
                                 double tolerance, std::vector<bool>& keep)
{
    if (end - start < 2)
    {
        return;
    }

    // Special case: tolerance of 0 means keep all points
    if (tolerance == 0)
    {
        for (size_t i = start + 1; i < end; ++i)
        {
            keep[i] = true;
        }
        return;
    }

    double max_dist = 0;
    size_t max_index = start;

    // Find point with maximum distance from line segment
    for (size_t i = start + 1; i < end; ++i)
    {
        double dist = perpendicular_distance(points[i], points[start], points[end]);
        if (dist > max_dist)
        {
            max_dist = dist;
            max_index = i;
        }
    }

    // If max distance is greater than tolerance, recursively simplify
    if (max_dist > tolerance)
    {
        keep[max_index] = true;
        douglas_peucker_recursive(points, start, max_index, tolerance, keep);
        douglas_peucker_recursive(points, max_index, end, tolerance, keep);
    }
}

}  // namespace detail

/*! @brief Simplify linestring using Douglas-Peucker algorithm */
template <typename LineString>
LineString simplify(const LineString& linestring, double tolerance)
{
    if (linestring.size() < 3)
    {
        return linestring;
    }

    using Point = typename LineString::value_type;
    std::vector<Point> points(linestring.begin(), linestring.end());

    // Mark which points to keep
    std::vector<bool> keep(points.size(), false);
    keep.front() = true;
    keep.back() = true;

    // Run Douglas-Peucker
    detail::douglas_peucker_recursive(points, 0, points.size() - 1, tolerance, keep);

    // Build simplified linestring
    LineString result;
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (keep[i])
        {
            result.push_back(points[i]);
        }
    }

    return result;
}

//
// ENVELOPE (Bounding Box)
//

/*! @brief Create polygon representing the envelope (bounding box) of a geometry */
template <typename Geom, typename Polygon>
Polygon envelope(const Geom& geom)
{
    auto bounds = geom.bounds();

    using Point = typename Polygon::value_type::value_type;
    typename Polygon::value_type ring;

    ring.push_back(Point{bounds.minx, bounds.miny});
    ring.push_back(Point{bounds.maxx, bounds.miny});
    ring.push_back(Point{bounds.maxx, bounds.maxy});
    ring.push_back(Point{bounds.minx, bounds.maxy});
    ring.push_back(Point{bounds.minx, bounds.miny});  // Close the ring

    Polygon result;
    result.push_back(ring);

    return result;
}

//
// CENTROID
//

/*! @brief Compute centroid of a polygon */
template <typename Polygon, typename Point>
Point centroid(const Polygon& polygon)
{
    if (polygon.empty() || polygon[0].empty())
    {
        return Point{0, 0};
    }

    const auto& ring = polygon[0];  // Exterior ring
    typename Point::coord_type cx = 0;
    typename Point::coord_type cy = 0;
    typename Point::coord_type signed_area = 0;

    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        auto x0 = ring[i].x;
        auto y0 = ring[i].y;
        auto x1 = ring[i + 1].x;
        auto y1 = ring[i + 1].y;
        auto a = x0 * y1 - x1 * y0;
        signed_area += a;
        cx += (x0 + x1) * a;
        cy += (y0 + y1) * a;
    }

    signed_area *= 0.5;
    cx /= (6.0 * signed_area);
    cy /= (6.0 * signed_area);

    return Point{cx, cy};
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
