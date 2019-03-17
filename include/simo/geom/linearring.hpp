#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/point_collection.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/// @todo (pavel) DOCUMENT ME!
class LinearRing : public BasicGeometry<LinearRing>, public PointCollection<LinearRing>
{
  public:
    /// two-dimensional rotation direction, clockwise=true, counterclockwise=false
    bool clockwise = true;

    /*!
     * @brief creates an empty LinearRing
     *
     * @since 0.0.1
     */
    LinearRing() = default;

    /*!
      * @brief creates a LinearRing from a given initializer list
      *
      * @tparam T an arithmetic value (e.g. int, float, double)
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    LinearRing(std::initializer_list<std::initializer_list<T>> init)
    {
        m_points.reserve(init.size());
        Bounds& b = bounds();
        for (const auto& coords : init)
        {
            Point p(coords);
            b.extend(p.x, p.y);
            m_points.emplace_back(std::move(p));
        }
        valid_or_throw();
    }

    /*!
     * @brief creates a LinearRing from a given point vector
     *
     * @param points the point list
     * @param validate whether to validate the geometry
     *
     * @since 0.0.1
     */
    explicit LinearRing(const std::vector<Point>& points)
    {
        m_points  = points;
        Bounds& b = bounds();
        for (const auto& p : m_points)
        {
            b.extend(p.x, p.y);
        }
        valid_or_throw();
    }

  private:

    /// for implementation encapsulation
    friend class BasicGeometry;

    /// @private
    void valid_or_throw() const
    {
        if (empty())
        {
            return;
        }

        if (m_points.size() < 4)
        {
            throw exceptions::value_error("LinearRing should be either empty or with 4 or more points");
        }

        if (not is_closed())
        {
            throw exceptions::value_error("LinearRing is not closed, first and last point are different");
        }

        /// @todo (pavel) check for self-intersections
    }

    /// @private
    GeometryType type_() const
    {
        return GeometryType::LINESTRING;
    }

    /// @private
    std::string type_str_() const
    {
        return "LineString";
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
};

}  // namespace shapes
}  // namespace simo