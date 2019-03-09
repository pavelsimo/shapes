#pragma once

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
     * @private
     */
    GeometryType type_() const
    {
        return GeometryType::LINESTRING;
    }

    /*!
     * @private
     */
    std::string type_str_() const
    {
        return "LineString";
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
    static LineString from_json(const std::string&)
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
    static LineString from_wkt(const std::string&)
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
};

}  // namespace shapes
}  // namespace simo