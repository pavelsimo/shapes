#pragma once

#include <ciso646>
#include <cmath>
#include <type_traits>

namespace simo
{
namespace shapes
{
namespace algorithm
{

/*!
 * @brief Calculate the Euclidean distance between two points
 *
 * @param p1 First point
 * @param p2 Second point
 * @return Distance between points
 */
template <typename Point>
auto distance(const Point& p1, const Point& p2) -> decltype(p1.x)
{
    auto dx = p2.x - p1.x;
    auto dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

/*!
 * @brief Calculate the length of a linestring
 *
 * Sums the Euclidean distances between consecutive points.
 *
 * @param linestring The linestring geometry
 * @return Total length
 */
template <typename LineString>
auto length(const LineString& linestring) -> typename LineString::coord_type
{
    if (linestring.size() < 2)
    {
        return 0.0;
    }

    typename LineString::coord_type total = 0.0;

    for (size_t i = 0; i < linestring.size() - 1; ++i)
    {
        total += distance(linestring[i], linestring[i + 1]);
    }

    return total;
}

/*!
 * @brief Calculate the signed area of a ring using the Shoelace formula
 *
 * Uses the Shoelace (Gauss's area) formula:
 * A = 0.5 * |Σ(x_i * y_{i+1} - x_{i+1} * y_i)|
 *
 * @param ring The ring (polygon boundary)
 * @return Signed area (positive for counter-clockwise, negative for clockwise)
 */
template <typename Ring>
auto signed_area_ring(const Ring& ring) -> typename Ring::coord_type
{
    if (ring.size() < 3)
    {
        return 0.0;
    }

    typename Ring::coord_type area = 0.0;

    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        area += ring[i].x * ring[i + 1].y - ring[i + 1].x * ring[i].y;
    }

    return area / 2.0;
}

/*!
 * @brief Calculate the area of a polygon
 *
 * Computes area of exterior ring minus areas of holes.
 *
 * @param polygon The polygon geometry
 * @return Area of polygon
 */
template <typename Polygon>
auto area(const Polygon& polygon) -> typename Polygon::coord_type
{
    if (polygon.empty())
    {
        return 0.0;
    }

    // Area of exterior ring (first ring)
    typename Polygon::coord_type total_area = std::abs(signed_area_ring(polygon[0]));

    // Subtract areas of holes (remaining rings)
    for (size_t i = 1; i < polygon.size(); ++i)
    {
        total_area -= std::abs(signed_area_ring(polygon[i]));
    }

    return total_area;
}

/*!
 * @brief Calculate the perimeter of a polygon
 *
 * Sums the lengths of the exterior ring.
 *
 * @param polygon The polygon geometry
 * @return Perimeter length
 */
template <typename Polygon>
auto perimeter(const Polygon& polygon) -> typename Polygon::coord_type
{
    if (polygon.empty())
    {
        return 0.0;
    }

    return length(polygon[0]);  // Exterior ring
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
