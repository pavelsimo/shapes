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
 * @brief Test if two line segments intersect
 *
 * Tests whether segment p1q1 and segment p2q2 intersect.
 * Uses orientation tests for robustness.
 *
 * @param p1 First endpoint of first segment
 * @param q1 Second endpoint of first segment
 * @param p2 First endpoint of second segment
 * @param q2 Second endpoint of second segment
 * @return true if segments intersect, false otherwise
 */
template <typename Point>
constexpr bool segments_intersect(const Point& p1, const Point& q1,
                                   const Point& p2, const Point& q2) noexcept
{
    int o1 = orient2d(p1, q1, p2);
    int o2 = orient2d(p1, q1, q2);
    int o3 = orient2d(p2, q2, p1);
    int o4 = orient2d(p2, q2, q1);

    // General case: segments intersect if endpoints are on opposite sides
    if (o1 != o2 && o3 != o4)
    {
        return true;
    }

    // Special cases: collinear points
    // p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, q1, p2))
    {
        return true;
    }

    // q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q1, q2))
    {
        return true;
    }

    // p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, q2, p1))
    {
        return true;
    }

    // q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q2, q1))
    {
        return true;
    }

    return false;
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
