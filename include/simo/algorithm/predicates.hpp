#pragma once

#include <ciso646>
#include <simo/algorithm/detail/orient2d.hpp>
#include <simo/algorithm/detail/segment_intersection.hpp>
#include <simo/algorithm/detail/point_in_polygon.hpp>

namespace simo
{
namespace shapes
{
namespace algorithm
{

// Forward declarations for different geometry type combinations

//
// CONTAINS
//

/*! @brief Test if a polygon contains a point */
template <typename Polygon, typename Point>
bool contains(const Polygon& polygon, const Point& point)
{
    if (polygon.empty())
    {
        return false;
    }

    // Check if point is inside exterior ring
    int wn = detail::winding_number(point, polygon[0]);
    if (wn == 0)
    {
        return false;  // Outside exterior ring
    }

    // Check if point is inside any hole (should NOT be)
    for (size_t i = 1; i < polygon.size(); ++i)
    {
        int wn_hole = detail::winding_number(point, polygon[i]);
        if (wn_hole != 0)
        {
            return false;  // Inside a hole
        }
    }

    return true;
}

//
// INTERSECTS
//

/*! @brief Test if two bounding boxes intersect */
template <typename Bounds1, typename Bounds2>
bool bounds_intersect(const Bounds1& b1, const Bounds2& b2)
{
    return !(b1.maxx < b2.minx || b2.maxx < b1.minx ||
             b1.maxy < b2.miny || b2.maxy < b1.miny);
}

/*! @brief Test if two line segments intersect */
template <typename LineString1, typename LineString2>
bool intersects(const LineString1& ls1, const LineString2& ls2)
{
    // Quick rejection test using bounding boxes
    auto b1 = ls1.bounds();
    auto b2 = ls2.bounds();
    if (!bounds_intersect(b1, b2))
    {
        return false;
    }

    // Test all segment pairs
    for (size_t i = 0; i < ls1.size() - 1; ++i)
    {
        for (size_t j = 0; j < ls2.size() - 1; ++j)
        {
            if (detail::segments_intersect(ls1[i], ls1[i + 1], ls2[j], ls2[j + 1]))
            {
                return true;
            }
        }
    }

    return false;
}

//
// WITHIN
//

/*! @brief Test if point is within polygon (inverse of contains) */
template <typename Point, typename Polygon>
bool within(const Point& point, const Polygon& polygon)
{
    return contains(polygon, point);
}

//
// TOUCHES
//

/*! @brief Test if point touches polygon boundary */
template <typename Point, typename Polygon>
bool touches(const Point& point, const Polygon& polygon)
{
    if (polygon.empty())
    {
        return false;
    }

    // Check exterior ring
    if (detail::point_on_boundary(point, polygon[0]))
    {
        return true;
    }

    // Check holes
    for (size_t i = 1; i < polygon.size(); ++i)
    {
        if (detail::point_on_boundary(point, polygon[i]))
        {
            return true;
        }
    }

    return false;
}

//
// DISJOINT
//

/*! @brief Test if two geometries are disjoint (no intersection) */
template <typename Geom1, typename Geom2>
bool disjoint(const Geom1& g1, const Geom2& g2)
{
    return !intersects(g1, g2);
}

//
// CROSSES
//

/*! @brief Test if linestring crosses polygon boundary */
template <typename LineString, typename Polygon>
bool crosses(const LineString& ls, const Polygon& polygon)
{
    if (polygon.empty() || ls.size() < 2)
    {
        return false;
    }

    const auto& exterior = polygon[0];
    if (exterior.size() < 4)  // Need at least 3 unique points + closing point
    {
        return false;
    }

    bool has_interior = false;
    bool has_exterior = false;

    // Check vertices first
    for (const auto& point : ls)
    {
        if (contains(polygon, point))
        {
            has_interior = true;
        }
        else
        {
            has_exterior = true;
        }

        if (has_interior && has_exterior)
        {
            return true;
        }
    }

    // Check if linestring segments intersect polygon boundary
    // If they do, the linestring crosses the polygon
    for (std::size_t i = 0; i + 1 < ls.size(); ++i)
    {
        const auto& p1 = ls[i];
        const auto& p2 = ls[i + 1];

        for (std::size_t j = 0; j + 1 < exterior.size(); ++j)
        {
            const auto& q1 = exterior[j];
            const auto& q2 = exterior[j + 1];

            if (detail::segments_intersect(p1, p2, q1, q2))
            {
                // Found intersection with boundary
                // Check if segment midpoint is inside polygon
                typename LineString::value_type midpoint;
                midpoint.x = (p1.x + p2.x) / 2;
                midpoint.y = (p1.y + p2.y) / 2;

                if (contains(polygon, midpoint))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

//
// OVERLAPS
//

/*! @brief Test if two geometries overlap (share some but not all interior points) */
template <typename Geom1, typename Geom2>
bool overlaps(const Geom1& g1, const Geom2& g2)
{
    // Quick rejection: check bounding boxes
    auto b1 = g1.bounds();
    auto b2 = g2.bounds();
    return bounds_intersect(b1, b2);
    // Note: Full overlap test requires more complex logic
    // This is a simplified implementation
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
