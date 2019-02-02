#pragma once

#include <algorithm>
#include <tuple>

namespace simo
{
namespace shapes
{

class Bounds
{
  public:
    double minx;
    double miny;
    double maxx;
    double maxy;

    Bounds()
        : minx(std::numeric_limits<double>::max()), miny(std::numeric_limits<double>::max()), maxx(std::numeric_limits<double>::max()), maxy(std::numeric_limits<double>::max())
    {
    }

    Bounds(double minx, double miny, double maxx, double maxy)
        : minx(minx), miny(miny), maxx(maxx), maxy(maxy)
    {
    }

    Bounds& extend(double x, double y)
    {
        minx = std::min(x, minx);
        maxx = std::max(x, maxx);
        miny = std::min(y, miny);
        maxy = std::max(y, maxy);
        return *this;
    }

    std::tuple<double, double> center() const
    {
        return std::make_tuple((minx + maxx) / 2.0, (miny + maxy) / 2.0);
    }

    std::tuple<double, double> bottom_left() const
    {
        return std::make_tuple(minx, maxy);
    }

    std::tuple<double, double> top_right() const
    {
        return std::make_tuple(maxx, miny);
    }

    std::tuple<double, double> top_left() const
    {
        return std::make_tuple(minx, miny);
    }

    std::tuple<double, double> bottom_right() const
    {
        return std::make_tuple(maxx, maxy);
    }

    bool contains(double x, double y) const
    {
        return (x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy);
    }

    bool contains(const Bounds& other)
    {
        return contains(other.minx, other.miny) && contains(other.maxx, other.maxy);
    }

    bool intersects(const Bounds& other)
    {
        return (other.maxx >= minx) && (other.minx <= maxx) && (other.maxy >= miny) && (other.miny <= maxy);
    }

    bool overlaps(const Bounds& other)
    {
        return (other.maxx > minx) && (other.minx < maxx) && (other.maxy > miny) && (other.miny < maxy);
    }
};

}  // namespace shapes
}  // namespace simo