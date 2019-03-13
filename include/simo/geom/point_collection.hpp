#pragma once

#include <ciso646>
#include <simo/geom/point.hpp>

namespace simo
{
namespace shapes
{

/// @todo (pavel) add method to get first point
/// @todo (pavel) add method to get last point

template <typename Derived>
class PointCollection
{
  public:
    /// iterator type
    typedef std::vector<Point>::iterator iterator;

    /// const iterator type
    typedef std::vector<Point>::const_iterator const_iterator;

    /*!
     * @return returns an iterator pointing to the first element in the PointCollection
     *
     * @since 0.0.1
     */
    iterator begin()
    {
        return m_points.begin();
    }

    /*!
     * @return returns a constant iterator pointing to the first element in the PointCollection
     *
     * @since 0.0.1
     */
    const_iterator begin() const
    {
        return m_points.begin();
    }

    /*!
     * @return returns an iterator pointing to the past-the-end element in the PointCollection
     *
     * @since 0.0.1
     */
    iterator end()
    {
        return m_points.end();
    }

    /*!
     * @return returns a const iterator pointing to the past-the-end element in the PointCollection
     *
     * @since 0.0.1
     */
    const_iterator end() const
    {
        return m_points.end();
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in the vector
     *
     * @since 0.0.1
     */
    Point& at(size_t pos)
    {
        return m_points.at(pos);
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in the vector
     *
     * @since 0.0.1
     */
    Point& operator[](size_t pos)
    {
        return m_points.at(pos);
    }

    /// @private
    std::vector<std::tuple<double, double>> xy_() const
    {
        std::vector<std::tuple<double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y);
        }
        return res;
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.z);
        }
        return res;
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.m);
        }
        return res;
    }

    /// @private
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        std::vector<std::tuple<double, double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.z, point.m);
        }
        return res;
    }

    /// @private
    bool empty_() const
    {
        return m_points.empty();
    }

    /// @private
    size_t size_() const
    {
        return m_points.size();
    }

    /// @private
    bool is_closed_() const
    {
        if (m_points.size() < 2)
        {
            return false;
        }
        size_t last_index = m_points.size() - 1;
        return m_points[0] == m_points[last_index];
    }

  protected:
    std::vector<Point> m_points;
};

}  // namespace shapes
}  // namespace simo