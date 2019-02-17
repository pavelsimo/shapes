#pragma once

#include <simo/geom/point.hpp>

namespace simo
{
namespace shapes
{

template <typename Derived>
class PointCollection
{
  public:

    /// DOCUMENT ME!
    typedef std::vector<Point>::iterator iterator;

    /// DOCUMENT ME!
    typedef std::vector<Point>::const_iterator const_iterator;

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    iterator begin()
    {
        return m_points.begin();
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    const_iterator begin() const
    {
        return m_points.begin();
    }

    /*!
     *
     * @return
     */
    iterator end()
    {
        return m_points.end();
    }

    /*!
     *
     * @return
     */
    const_iterator end() const
    {
        return m_points.end();
    }

    /*!
     *
     * @param pos
     * @return
     */
    Point at(size_t pos)
    {
        return m_points.at(pos);
    }

    /*!
     *
     * @param pos
     * @return
     */
    Point operator[](size_t pos)
    {
        return m_points.at(pos);
    }

    /*!
     * @private
     */
    std::vector<std::tuple<double, double>> xy_() const
    {
        std::vector<std::tuple<double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y);
        }
        return res;
    }

    /*!
     * @private
     */
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.z);
        }
        return res;
    }

    /*!
     * @private
     */
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.m);
        }
        return res;
    }

    /*!
     * @private
     */
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        std::vector<std::tuple<double, double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.z, point.m);
        }
        return res;
    }

    /*!
     * @private
     */
    bool empty_() const
    {
        return m_points.empty();
    }

    /*!
     * @private
     */
    size_t size_() const
    {
        return m_points.size();
    }

  protected:
    std::vector<Point> m_points;
};

}  // namespace shapes
}  // namespace simo