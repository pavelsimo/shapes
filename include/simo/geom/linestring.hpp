#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/curve.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a line string is a curve where each consecutive pair of points defines a line segment.
 *
 * @since 0.0.1
 */
class LineString : public BaseGeometry<LineString>, public Curve<LineString>
{
  public:
    /*!
     * @brief creates an empty LineString
     *
     * @since 0.0.1
     */
    LineString() = default;

    /*!
     * @brief creates a LineString from a given initializer list
     * @tparam T an arithmetic value (e.g. int, float, double)
     * @param init the initializer list
     *
     * @since 0.0.1
     */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    LineString(std::initializer_list<std::initializer_list<T>> init)
    {
        m_points.reserve(init.size());
        for (const auto& coords : init)
        {
            Point p(coords);
            bounds.extend(p.x, p.y);
            m_points.emplace_back(p);
        }
        valid_or_throw();
    }

    /*!
     * @brief creates a LineString from a given point vector
     * @param points the point list
     *
     * @since 0.0.1
     */
    explicit LineString(const std::vector<Point>& points)
    {
        m_points = points;
        for (const auto& p : m_points)
        {
            bounds.extend(p.x, p.y);
        }
    }

    /*!
     * @brief creates a LineString from a geojson string
     * @param json the geojson string
     * @return a LineString object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static LineString from_json(const std::string& /*json*/)
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief dumps the geojson representation of the LineString
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a LineString from a WKT string
     * @param wkt the WKT string
     * @return a LineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static LineString from_wkt(const std::string& /*wkt*/)
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a LineString from a WKT string
     * @param wkt the WKT string
     * @return a LineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        throw exceptions::NotImplementedError();
    }

  private:
    /// for allow BaseGeometry to access LineString private members
    friend class BaseGeometry<LineString>;

    /// @private
    void valid_or_throw()
    {
        if (empty())
        {
            return;
        }

        if (m_points.size() < 2)
        {
            throw exceptions::ValueError("LineString should be either empty or with 2 or more points");
        }

        if (m_points.size() == 2)
        {
            if (m_points[0] == m_points[1])
            {
                throw exceptions::ValueError("LineString with exactly two equal points");
            }
        }
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