#pragma once

#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/point.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

class MultiPoint : public BasicGeometry<MultiPoint>, public PointCollection<MultiPoint>
{
  public:
    /*!
     * @brief creates an empty MultiPoint
     *
     * @since 0.0.1
     */
    MultiPoint() = default;

     /*!
      * @brief creates a MultiPoint from a given initializer list
      *
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(std::initializer_list<std::initializer_list<T>> init)
    {
        m_points.reserve(init.size());
        for (const auto& coords : init)
        {
            Point p(coords);
            m_bounds.extend(p.x, p.y);
            m_points.push_back(std::move(p));
        }
    }

    /*!
     * @brief creates a MultiPoint from a given point vector
     *
     * @param points the point list
     *
     * @since 0.0.1
     */
    explicit MultiPoint(const std::vector<Point>& points)
    {
        m_points = points;
    }

    /*!
    * @copydoc Geometry::geom_type()
    */
    GeometryType geom_type_() const
    {
        return GeometryType::MULTIPOINT;
    }

    /*!
    * @copydoc Geometry::geom_type_str()
    */
    std::string geom_type_str_() const
    {
        return "MultiPoint";
    }

    /*!
    * @copydoc Geometry::empty()
    */
    bool empty_() const
    {
        return m_points.empty();
    }

    /*!
    * @copydoc Geometry::size()
    */
    size_t size_() const
    {
        return m_points.size();
    }

    /*!
    * @copydoc Geometry::xy()
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
    * @copydoc Geometry::xyz()
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
      * @brief creates a MultiPoint from a geojson string
      *
      * @param json the geojson string
      * @return a MultiPoint object
      *
      * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
      *
      * @since 0.0.1
      */
    static MultiPoint from_json(const std::string& json)
    {
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "MultiPoint")
        {
            throw exceptions::parse_error("invalid geometry type");
        }

        auto coords = j.at("coordinates").get<std::vector<std::vector<double>>>();
        std::vector<Point> res;
        for (const auto& tuple : coords)
        {
            if (tuple.size() == 2)
            {
                res.emplace_back(Point{tuple[0], tuple[1]});
            }
            else if (tuple.size() == 3)
            {
                res.emplace_back(Point{tuple[0], tuple[1], tuple[2]});
            }
            else
            {
                throw exceptions::parse_error("invalid dimensions");
            }
        }
        return MultiPoint(res);
    }

    /*!
     * @brief dumps the geojson representation of the MultiPoint
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @return a geojson string
     *
     * @since 0.0.1
     */
    std::string json()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "{\"type\":\"MultiPoint\",\"coordinates\":[";
        for(size_t i = 0; i < m_points.size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            const auto& p = m_points[i];
            if (p.ndim() == 2)
            {
                ss << "[" << p.x << "," << p.y << "]";
            }
            else if (p.ndim() == 3)
            {
                ss << "[" << p.x << "," << p.y << "," << p.z << "]";
            }
            else if (p.ndim() == 4)
            {
                ss << "[" << p.x << "," << p.y << "," << p.z << "," << p.m << "]";
            }
        }
        ss << "]}";
        return ss.str();
    }

    /*!
     * @brief creates a MultiPoint from a WKT string
     *
     * @param wkt the WKT string
     * @return a MultiPoint object
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);

        ss << "MULTIPOINT";
        if (m_ndim >= 3)
        {
            ss << "Z";
        }
        if (m_ndim == 4)
        {
            ss << "M";
        }

        ss << "(";
        for (size_t i = 0; i < m_points.size(); ++i)
        {
            const Point& p = m_points[i];
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(" << p.x << " " << p.y;
            if (m_ndim == 3)
            {
                ss << " " << p.z;
            }
            ss << ")";
        }
        ss << ")";
        return ss.str();
    }
};

}  // namespace shapes
}  // namespace simo