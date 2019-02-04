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
        : x(0), y(0), z(0), has_z(false), has_m(false)
    {
        m_ndim = 2;
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
        m_ndim = 2;
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
        : x(x), y(y), z(z), has_z(true)
    {
        m_ndim = 3;
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
        : x(x), y(y), z(z), m(m), has_z(true), has_m(true)
    {
        m_ndim = 4;
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
            m_ndim = 2;
        }
        else if (init.size() == 3)
        {
            x      = *init.begin();
            y      = *(init.begin() + 1);
            z      = *(init.begin() + 2);
            m_ndim = 3;
            has_z  = true;
        }
        else if (init.size() == 4)
        {
            x      = *init.begin();
            y      = *(init.begin() + 1);
            z      = *(init.begin() + 2);
            m      = *(init.begin() + 3);
            m_ndim = 4;
            has_m  = true;
            has_z  = true;
        }
        else
        {
            throw exception();
        }
    }

    /*!
     * @copydoc Geometry::geom_type()
     */
    GeometryType geom_type_() const
    {
        return GeometryType::POINT;
    }

    /*!
     * @copydoc Geometry::geom_type_str()
     */
    std::string geom_type_str_() const
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
        return static_cast<size_t>(m_ndim);
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
            throw exception();
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
            throw parse_error();
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
        throw parse_error();
    }

    /*!
     * @brief dumps the geojson representation of the point
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @return a geojson string
     *
     * @since 0.0.1
     */
    std::string json()
    {
        auto coordinates = std::vector<double>{x, y};
        if (m_ndim == 3)
        {
            coordinates.push_back(z);
        }
        nlohmann::json j = {{"type", "Point"}, {"coordinates", coordinates}};
        return j.dump();
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
        /// @todo (pavel) consider the case, Point(...) should also be a valid WKT
        std::regex point_regex("POINT[Z]?[M]?\\((.*)\\)");
        std::smatch match;
        std::string coords_str;
        if (std::regex_search(wkt, match, point_regex) && match.size() > 1)
        {
            coords_str = match.str(1);
            std::regex coords_regex("\\s+");
            std::sregex_token_iterator iter(coords_str.begin(), coords_str.end(), coords_regex, -1);
            std::sregex_token_iterator end;

            /// @todo (pavel) add another point constructor Point(const std::vector<double> coords) ...
            std::vector<double> coords;
            for (; iter != end; ++iter)
            {
                coords.push_back(std::stod(*iter));
            }
            if (coords.size() == 2)
            {
                return Point(coords[0], coords[1]);
            }
            else if (coords.size() == 3)
            {
                return Point(coords[0], coords[1], coords[2]);
            }
            else if (coords.size() == 4)
            {
                return Point(coords[0], coords[1], coords[2], coords[3]);
            }
        }
        throw parse_error();
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
        if (has_z)
            ss << "Z";
        if (has_m)
            ss << "M";
        ss << "(";
        ss << x << " " << y;
        if (has_z)
            ss << " " << z;
        if (has_m)
            ss << " " << m;
        ss << ")";
        return ss.str();
    }

  private:
    bool has_z = false;
    bool has_m = false;
};

}  // namespace shapes
}  // namespace simo