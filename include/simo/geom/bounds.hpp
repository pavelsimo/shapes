#pragma once

#include <ciso646>
#include <algorithm>
#include <tuple>

namespace simo
{
namespace shapes
{

/*!
 * @brief Represents a bounding box
 * @ingroup geometry
 *
 * @since 0.0.1
 */
class bounds
{
  public:
    /// the minimum x-coordinate
    double minx;

    /// the minimum y-coordinate
    double miny;

    /// the maximum x-coordinate
    double maxx;

    /// the maximum y-coordinate
    double maxy;

    /*!
     * @brief Creates a bounds object
     *
     * @since 0.0.1
     */
    bounds()
        : minx(std::numeric_limits<double>::max()),
          miny(std::numeric_limits<double>::max()),
          maxx(std::numeric_limits<double>::min()),
          maxy(std::numeric_limits<double>::min())
    {
    }

    /*!
     * @brief Creates a bounds object from the given coordinates
     *
     * @param minx the x-coordinate of the first corner
     * @param miny the y-coordinate of the first corner
     * @param maxx the x-coordinate of the second corner
     * @param maxy the y-coordinate of the second corner
     *
     * @since 0.0.1
     */
    bounds(double minx, double miny, double maxx, double maxy)
        : minx(minx), miny(miny), maxx(maxx), maxy(maxy)
    {
    }

    /*!
     * @brief Extends the bounds to contain the given point
     *
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return the bounds object
     *
     * @since 0.0.1
     */
    bounds& extend(double x, double y)
    {
        minx = std::min(x, minx);
        maxx = std::max(x, maxx);
        miny = std::min(y, miny);
        maxy = std::max(y, maxy);
        return *this;
    }

    /*!
     * @brief Extends the bounds to contain the given bounds
     *
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return the bounds object
     *
     * @since 0.0.1
     */
    bounds& extend(const bounds& b)
    {
        minx = std::min(b.minx, minx);
        maxx = std::max(b.maxx, maxx);
        miny = std::min(b.miny, miny);
        maxy = std::max(b.maxy, maxy);
        return *this;
    }

    /*!
     * @return a (x, y) tuple with the center of the bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> center() const
    {
        return std::make_tuple((minx + maxx) / 2.0, (miny + maxy) / 2.0);
    }

    /*!
     * @return a (x, y) tuple with the bottom left bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> bottom_left() const
    {
        return std::make_tuple(minx, maxy);
    }

    /*!
     * @return a (x, y) tuple with the top right bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> top_right() const
    {
        return std::make_tuple(maxx, miny);
    }

    /*!
     * @return a (x, y) tuple with the top left bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> top_left() const
    {
        return std::make_tuple(minx, miny);
    }

    /*!
     * @return a (x, y) tuple with the bottom right bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> bottom_right() const
    {
        return std::make_tuple(maxx, maxy);
    }

    /*!
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return true if the bounds contains the given point, otherwise false
     *
     * @since 0.0.1
     */
    bool contains(double x, double y) const
    {
        return (x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy);
    }

    /*!
     * @param other the bounds
     * @return true if the bounds contain the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool contains(const bounds& other)
    {
        return contains(other.minx, other.miny) && contains(other.maxx, other.maxy);
    }

    /*!
     * @param other the bounds
     * @return true if the bounds intersect the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool intersects(const bounds& other)
    {
        return (other.maxx >= minx) && (other.minx <= maxx) && (other.maxy >= miny) && (other.miny <= maxy);
    }

    /*!
     * @param other the bounds
     * @return true if the bounds overlaps the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool overlaps(const bounds& other)
    {
        return (other.maxx > minx) && (other.minx < maxx) && (other.maxy > miny) && (other.miny < maxy);
    }
};

}  // namespace shapes
}  // namespace simo