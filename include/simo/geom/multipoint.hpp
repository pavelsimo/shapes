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
      * @tparam T an arithmetic value (e.g. int, float, double)
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(std::initializer_list<std::initializer_list<T>> init)
    {
        m_points.reserve(init.size());
        Bounds& b = bounds();
        for (const auto& coords : init)
        {
            Point p(coords);
            b.extend(p.x, p.y);
            m_points.emplace_back(std::move(p));
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
        m_points  = points;
        Bounds& b = bounds();
        for (const auto& p : m_points)
        {
            b.extend(p.x, p.y);
        }
    }

    /*!
    * @private
    */
    GeometryType type_() const
    {
        return GeometryType::MULTIPOINT;
    }

    /*!
    * @private
    */
    std::string type_str_() const
    {
        return "MultiPoint";
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
        /// @todo (pavel) read properties to specify z, m and zm
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
        /// @todo (pavel) add properties to specify z, m and zm
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "{\"type\":\"MultiPoint\",\"coordinates\":[";
        for (size_t i = 0; i < m_points.size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            const auto& p = m_points[i];
            switch (p.dim())
            {
                case DimensionType::XY:
                {
                    ss << "[" << p.x << "," << p.y << "]";
                    break;
                }
                case DimensionType::XYZ:
                {
                    ss << "[" << p.x << "," << p.y << "," << p.z << "]";
                    break;
                }
                case DimensionType::XYM:
                {
                    ss << "[" << p.x << "," << p.y << "," << p.m << "]";
                    break;
                }
                case DimensionType::XYZM:
                {
                    ss << "[" << p.x << "," << p.y << "," << p.z << "," << p.m << "]";
                    break;
                }
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
    static MultiPoint from_wkt(const std::string&)
    {

        throw exceptions::not_implemented_error();
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
        if (has_z())
        {
            ss << "Z";
        }
        if (has_m())
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
            if (has_z())
            {
                ss << " " << p.z;
            }
            if (has_m())
            {
                ss << " " << p.m;
            }
            ss << ")";
        }
        ss << ")";
        return ss.str();
    }
};

}  // namespace shapes
}  // namespace simo