#pragma once

#include <ciso646>
#include <algorithm>
#include <tuple>

namespace simo
{
namespace shapes
{

/*!
 * @brief represents a bounding box
 *
 * @since 0.0.1
 */
class Bounds
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
     * @brief creates a Bounds object
     *
     * @since 0.0.1
     */
    Bounds()
        : minx(std::numeric_limits<double>::max()),
          miny(std::numeric_limits<double>::max()),
          maxx(std::numeric_limits<double>::min()),
          maxy(std::numeric_limits<double>::min())
    {
    }

    /*!
     * @brief creates a Bounds object from the given coordinates
     * @param minx the x-coordinate of the first corner
     * @param miny the y-coordinate of the first corner
     * @param maxx the x-coordinate of the second corner
     * @param maxy the y-coordinate of the second corner
     *
     * @since 0.0.1
     */
    Bounds(double minx, double miny, double maxx, double maxy)
        : minx(minx), miny(miny), maxx(maxx), maxy(maxy)
    {
    }

    /*!
     * @brief extends the bounds to contain the given point
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return the Bounds object
     *
     * @since 0.0.1
     */
    Bounds& extend(double x, double y)
    {
        minx = std::min(x, minx);
        maxx = std::max(x, maxx);
        miny = std::min(y, miny);
        maxy = std::max(y, maxy);
        return *this;
    }

    /*!
     * @brief returns a (x, y) tuple with the center of the bounds
     * @return a tuple
     *
     * @since 0.0.1
     */
    std::tuple<double, double> center() const
    {
        return std::make_tuple((minx + maxx) / 2.0, (miny + maxy) / 2.0);
    }

    /*!
     * @brief returns a (x, y) tuple with the bottom left bounds
     * @return a tuple
     *
     * @since 0.0.1
     */
    std::tuple<double, double> bottom_left() const
    {
        return std::make_tuple(minx, maxy);
    }

    /*!
     * @brief returns a (x, y) tuple with the top right bounds
     * @return a tuple
     *
     * @since 0.0.1
     */
    std::tuple<double, double> top_right() const
    {
        return std::make_tuple(maxx, miny);
    }

    /*!
     * @brief returns a (x, y) tuple with the top left bounds
     * @return a tuple
     *
     * @since 0.0.1
     */
    std::tuple<double, double> top_left() const
    {
        return std::make_tuple(minx, miny);
    }

    /*!
     * @brief returns a (x, y) tuple with the bottom right bounds
     * @return a tuple
     *
     * @since 0.0.1
     */
    std::tuple<double, double> bottom_right() const
    {
        return std::make_tuple(maxx, maxy);
    }

    /*!
     * @brief returns true if the bounds contains the given point
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return true if the Bounds contains the given point, otherwise false
     *
     * @since 0.0.1
     */
    bool contains(double x, double y) const
    {
        return (x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy);
    }

    /*!
     * @brief returns true if the bounds contains the given one
     * @param other the bounds
     * @return true if the Bounds contain the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool contains(const Bounds& other)
    {
        return contains(other.minx, other.miny) && contains(other.maxx, other.maxy);
    }

    /*!
     * @brief returns true if the bounds intersect the given one
     * @param other the bounds
     * @return true if the Bounds intersect the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool intersects(const Bounds& other)
    {
        return (other.maxx >= minx) && (other.minx <= maxx) && (other.maxy >= miny) && (other.miny <= maxy);
    }

    /*!
     * @brief returns true if the bounds overlaps the given one
     * @param other the bounds
     * @return true if the Bounds overlaps the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool overlaps(const Bounds& other)
    {
        return (other.maxx > minx) && (other.minx < maxx) && (other.maxy > miny) && (other.miny < maxy);
    }
};

}  // namespace shapes
}  // namespace simo