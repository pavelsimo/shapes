#pragma once

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <regex>
#include <json/json.hpp>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>

namespace simo
{
namespace shapes
{

class Point : public BasicGeometry<Point>
{
  public:
    /// the x-coordinate value for this Point
    double x;

    /// the y-coordinate value for this Point
    double y;

    /// the z-coordinate value for this Point, if it has one.
    double z;

    /// the m-coordinate value for this Point, if it has one.
    double m;

    /*!
     * @brief creates a Point
     *
     * @note the default behaviour is to create a 2-dimensional point with coordinates (0, 0)
     *
     * @since 0.0.1
     */
    Point()
        : x(0), y(0), z(0)
    {
        dimension = DimensionType::XY;
    }

    /*!
     * @brief creates a Point from coordinates (x, y)
     *
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     *
     * @since 0.0.1
     */
    Point(double x, double y)
        : x(x), y(y), z(0)
    {
        dimension = DimensionType::XY;
    }

    /*!
     * @brief creates a Point from coordinates (x, y, z)
     *
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param z the z-coordinate value
     *
     * @since 0.0.1
     */
    Point(double x, double y, double z)
        : x(x), y(y), z(z)
    {
        dimension = DimensionType::XYZ;
    }

    /*!
     * @brief creates a Point from coordinates (x, y, z, m)
     *
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param z the z-coordinate value
     * @param m the m-coordinate (measure) value
     *
     * @since 0.0.1
     */
    Point(double x, double y, double z, double m)
        : x(x), y(y), z(z), m(m)
    {
        dimension = DimensionType::XYZM;
    }

    /*!
     * @brief creates a Point
     *
     * @param init the coordinates list
     *
     * @throw exception if the given number of coordinates is either less than two or greater than four
     *
     * @since 0.0.1
     */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Point(std::initializer_list<T> init)
    {
        if (init.size() == 2)
        {
            x      = *init.begin();
            y      = *(init.begin() + 1);
            z      = 0;
            dimension = DimensionType::XY;
        }
        else if (init.size() == 3)
        {
            x      = *init.begin();
            y      = *(init.begin() + 1);
            z      = *(init.begin() + 2);
            dimension = DimensionType::XYZ;
        }
        else if (init.size() == 4)
        {
            x      = *init.begin();
            y      = *(init.begin() + 1);
            z      = *(init.begin() + 2);
            m      = *(init.begin() + 3);
            dimension = DimensionType::XYZM;
        }
        else
        {
            throw exceptions::shapes_exception("invalid dimensions");
        }
    }

    /*!
     * @copydoc Geometry::type()
     */
    GeometryType type_() const
    {
        return GeometryType::POINT;
    }

    /*!
     * @copydoc Geometry::type_str()
     */
    std::string type_str_() const
    {
        return "Point";
    }

    /*!
     * @copydoc Geometry::empty()
     */
    bool empty_() const
    {
        return false;
    }

    /*!
     * @copydoc Geometry::size()
     */
    size_t size_() const
    {
        return static_cast<size_t>(get_num_dimension());
    }

    /*!
     * @copydoc Geometry::xy()
     */
    std::vector<std::tuple<double, double>> xy_() const
    {
        return {std::make_tuple(x, y)};
    }

    /*!
    * @copydoc Geometry::xyz()
    */
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        return {std::make_tuple(x, y, z)};
    }

    /*!
    * @copydoc Geometry::xyzm()
    */
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        return {std::make_tuple(x, y, z, m)};
    }

    /*!
     * @brief returns the coordinate at the given index
     *
     * @param pos the coordinate position
     * @return a double with the coordinate value
     *
     * @throw exception if the position is not found
     *
     * @since 0.0.1
     */
    double at(size_t pos)
    {
        if (pos >= size_())
        {
            throw exceptions::shapes_exception("index out of bounds");
        }
        if (pos == 0)
            return x;
        if (pos == 1)
            return y;
        if (pos == 2)
            return z;
        return m;
    }

    /*!
     * @copydoc Point::at()
     */
    double operator[](size_t pos)
    {
        return at(pos);
    }

    /*!
     * @brief creates a Point from a geojson string
     *
     * @param json the geojson string
     * @return a Point object
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @since 0.0.1
     */
    static Point from_json(const std::string& json)
    {
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "Point")
        {
            throw exceptions::parse_error("invalid geometry type");
        }

        std::vector<double> coords = j.at("coordinates");
        if (coords.size() == 2)
        {
            return {coords[0], coords[1]};
        }
        else if (coords.size() == 3)
        {
            return {coords[0], coords[1], coords[2]};
        }
        else if (coords.size() == 4)
        {
            return {coords[0], coords[1], coords[2], coords[3]};
        }
        throw exceptions::parse_error("invalid dimensions");
    }

    /*!
     * @brief dumps the geojson representation of the Point
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
        ss << "{\"type\":\"Point\",\"coordinates\":";
        ss << "[" << x << "," << y;
        if (has_z())
        {
            ss << "," << z;
        }
        if (has_m())
        {
            ss << "," << m;
        }
        ss << "]}";
        return ss.str();
    }

    /*!
     * @brief creates a Point from a WKT string
     *
     * @param wkt the WKT string
     * @return a Point object
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @since 0.0.1
     */
    static Point from_wkt(const std::string& wkt)
    {
        /// @todo (pavel) ensure the number of coordinates for POINT, POINTZ, POINTM, POINTZM
        /// @todo (pavel) empty spaces
        std::regex tagged_text_regex("(?:POINT|Point){1}[Z]?[M]?\\((.*)\\)");
        std::smatch tagged_text_match;
        std::string tagged_text;
        if (std::regex_search(wkt, tagged_text_match, tagged_text_regex) && tagged_text_match.size() > 1)
        {
            tagged_text = tagged_text_match.str(1);
            std::regex coords_regex("\\s+");
            std::sregex_token_iterator iter(tagged_text.begin(), tagged_text.end(), coords_regex, -1);
            std::sregex_token_iterator end;

            /// @todo (pavel) add another point constructor Point(const std::vector<double> coords) ...
            std::vector<double> coords;
            for (; iter != end; ++iter)
            {
                coords.push_back(std::stod(*iter));
            }
            if (coords.size() == 2)
            {
                return {coords[0], coords[1]};
            }
            else if (coords.size() == 3)
            {
                return {coords[0], coords[1], coords[2]};
            }
            else if (coords.size() == 4)
            {
                return {coords[0], coords[1], coords[2], coords[3]};
            }
            else
            {
                throw exceptions::parse_error("invalid dimensions");
            }
        }
        throw exceptions::parse_error("invalid tagged text");
    }

    /*!
     * @brief dumps the WKT representation of the point
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @return a WKT string
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "POINT";
        if (has_z())
        {
            ss << "Z";
        }
        if (has_m())
        {
            ss << "M";
        }
        ss << "(";
        ss << x << " " << y;
        if (has_z())
        {
            ss << " " << z;
        }
        if (has_m())
        {
            ss << " " << m;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename Derived>
class PointCollection
{
  public:
    typedef std::vector<Point>::iterator iterator;
    typedef std::vector<Point>::const_iterator const_iterator;

    iterator begin()
    {
        return m_points.begin();
    }

    const_iterator begin() const
    {
        return m_points.begin();
    }

    iterator end()
    {
        return m_points.end();
    }

    const_iterator end() const
    {
        return m_points.end();
    }

    Point at(size_t pos)
    {
        return m_points.at(pos);
    }

    Point operator[](size_t pos)
    {
        return m_points.at(pos);
    }

  protected:
    std::vector<Point> m_points;
};

}  // namespace shapes
}  // namespace simo