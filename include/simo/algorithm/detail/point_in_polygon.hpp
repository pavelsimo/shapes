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

    // Loop through all edges of the polygon; the i + 1 bound is underflow-safe on
    // empty rings
    for (size_t i = 0; i + 1 < ring.size(); ++i)
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
    const double squared_tolerance = tolerance * tolerance;
    for (size_t i = 0; i + 1 < ring.size(); ++i)
    {
        const auto& v1 = ring[i];
        const auto& v2 = ring[i + 1];

        // Exact hit: collinear and within the segment box
        if (orient2d(v1, v2, point) == 0)
        {
            if (on_segment(v1, v2, point))
            {
                return true;
            }
        }

        // Near hit: squared distance from the point to the segment within tolerance
        double dx  = static_cast<double>(v2.x) - static_cast<double>(v1.x);
        double dy  = static_cast<double>(v2.y) - static_cast<double>(v1.y);
        double px  = static_cast<double>(point.x) - static_cast<double>(v1.x);
        double py  = static_cast<double>(point.y) - static_cast<double>(v1.y);
        double mag = dx * dx + dy * dy;
        double u   = mag == 0 ? 0 : (px * dx + py * dy) / mag;
        if (u < 0)
        {
            u = 0;
        }
        else if (u > 1)
        {
            u = 1;
        }
        double ex = px - u * dx;
        double ey = py - u * dy;
        if (ex * ex + ey * ey <= squared_tolerance)
        {
            return true;
        }
    }

    return false;
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
