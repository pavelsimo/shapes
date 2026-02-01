#pragma once

#include <ciso646>

namespace simo
{
namespace shapes
{
namespace algorithm
{
namespace detail
{

/*!
 * @brief Robust 2D orientation test
 *
 * Computes the orientation of three points p, q, r in 2D space.
 * Based on the sign of the determinant:
 *   | px py 1 |
 *   | qx qy 1 |
 *   | rx ry 1 |
 *
 * @param p First point
 * @param q Second point
 * @param r Third point
 * @return > 0 if counter-clockwise, < 0 if clockwise, == 0 if collinear
 *
 * @note Uses exact arithmetic via cross product for robustness
 */
template <typename Point>
constexpr int orient2d(const Point& p, const Point& q, const Point& r) noexcept
{
    // Compute the cross product: (q - p) × (r - p)
    // = (q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y)
    auto det = (q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y);

    // Return the sign
    if (det > 0) return 1;   // Counter-clockwise
    if (det < 0) return -1;  // Clockwise
    return 0;                 // Collinear
}

/*!
 * @brief Check if point r is on the segment pq (assuming collinearity)
 *
 * @param p First endpoint
 * @param q Second endpoint
 * @param r Point to test
 * @return true if r is on segment pq, false otherwise
 */
template <typename Point>
constexpr bool on_segment(const Point& p, const Point& q, const Point& r) noexcept
{
    return r.x <= std::max(p.x, q.x) && r.x >= std::min(p.x, q.x) &&
           r.y <= std::max(p.y, q.y) && r.y >= std::min(p.y, q.y);
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
