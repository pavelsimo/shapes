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
class LineString : public BasicGeometry<LineString>, public PointCollection<LineString>
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
      *
      * @tparam T an arithmetic value (e.g. int, float, double)
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    LineString(std::initializer_list<std::initializer_list<T>> init)
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
     * @brief creates a LineString from a given point vector
     *
     * @param points the point list
     *
     * @since 0.0.1
     */
    explicit LineString(const std::vector<Point>& points)
    {
        m_points = points;
    }

    /*!
     * @brief creates a LineString from a geojson string
     *
     * @param json the geojson string
     * @return a LineString object
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @since 0.0.1
     */
    static LineString from_json(const std::string& /*json*/)
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief dumps the geojson representation of the LineString
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @return a geojson string
     *
     * @since 0.0.1
     */
    std::string json()
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief creates a LineString from a WKT string
     *
     * @param wkt the WKT string
     * @return a LineString object
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @since 0.0.1
     */
    static LineString from_wkt(const std::string& /*wkt*/)
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief creates a LineString from a WKT string
     *
     * @param wkt the WKT string
     * @return a LineString object
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        throw exceptions::not_implemented_error();
    }

  private:
    /// for implementation encapsulation
    friend class BasicGeometry<LineString>;

    /// @private
    void valid_or_throw()
    {
        if (empty())
        {
            return;
        }

        if (m_points.size() < 2)
        {
            throw exceptions::value_error("LineString should be either empty or with 2 or more points");
        }

        if (m_points.size() == 2)
        {
            if (m_points[0] == m_points[1])
            {
                throw exceptions::value_error("LineString with exactly two equal points");
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