#pragma once

#include <ciso646>
#include <simo/algorithm/detail/orient2d.hpp>

namespace simo
{
namespace shapes
{
namespace algorithm
{
namespace detail
{

/*!
 * @brief Test if a point is inside a polygon using winding number algorithm
 *
 * The winding number counts the number of times the polygon winds around the point.
 * A non-zero winding number means the point is inside.
 *
 * @param point The point to test
 * @param ring The polygon ring (should be closed: first point == last point)
 * @return Winding number (0 = outside, non-zero = inside)
 */
template <typename Point, typename Ring>
int winding_number(const Point& point, const Ring& ring)
{
    int wn = 0;  // Winding number counter

    // Loop through all edges of the polygon
    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        const auto& v1 = ring[i];
        const auto& v2 = ring[i + 1];

        if (v1.y <= point.y)
        {
            // Upward crossing
            if (v2.y > point.y)
            {
                if (orient2d(v1, v2, point) > 0)
                {
                    ++wn;  // Point is left of edge
                }
            }
        }
        else
        {
            // Downward crossing
            if (v2.y <= point.y)
            {
                if (orient2d(v1, v2, point) < 0)
                {
                    --wn;  // Point is right of edge
                }
            }
        }
    }

    return wn;
}

/*!
 * @brief Test if a point is on the boundary of a polygon
 *
 * @param point The point to test
 * @param ring The polygon ring
 * @param tolerance Distance tolerance for boundary test
 * @return true if point is on the boundary
 */
template <typename Point, typename Ring>
bool point_on_boundary(const Point& point, const Ring& ring, double tolerance = 1e-10)
{
    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        const auto& v1 = ring[i];
        const auto& v2 = ring[i + 1];

        // Check if collinear
        if (orient2d(v1, v2, point) == 0)
        {
            // Check if on segment
            if (on_segment(v1, v2, point))
            {
                return true;
            }
        }

        // Alternative: distance to line segment check
        // (Can add more sophisticated distance calculation if needed)
    }

    return false;
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
