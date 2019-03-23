#pragma once

#include <ciso646>
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
#include <simo/io/wkt_reader.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief represents a point
 *
 * @since 0.0.1
 */
class Point : public BaseGeometry<Point>
{
  public:
    /// the x-coordinate value for this Point
    double x = 0;

    /// the y-coordinate value for this Point
    double y = 0;

    /// the z-coordinate value for this Point, if it has one.
    double z = 0;

    /// the m-coordinate value for this Point, if it has one.
    double m = 0;

    /*!
     * @brief creates a Point
     * @note the default behaviour is to create a 2-dimensional point with coordinates (0, 0)
     *
     * @since 0.0.1
     */
    Point() = default;

    /*!
     * @brief creates a Point from coordinates (x, y)
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     *
     * @since 0.0.1
     */
    Point(double x, double y)
        : x(x), y(y)
    {
        dim = DimensionType::XY;
    }

    /*!
     * @brief creates a Point from coordinates (x, y, z)
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param z the z-coordinate value
     *
     * @since 0.0.1
     */
    Point(double x, double y, double z)
        : x(x), y(y), z(z)
    {
        dim = DimensionType::XYZ;
    }

    /*!
     * @brief creates a Point from coordinates (x, y, z, m)
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
        dim = DimensionType::XYZM;
    }

    /*!
     * @brief creates a Point from coordinates (x, y)
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     *
     * @since 0.0.1
     */
    static Point from_xy(double x, double y)
    {
        return {x, y};
    }

    /*!
     * @brief creates a Point from coordinates (x, y, z)
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param z the z-coordinate value
     *
     * @since 0.0.1
     */
    static Point from_xyz(double x, double y, double z)
    {
        return {x, y, z};
    }

    /*!
     * @brief creates a Point from coordinates (x, y, m)
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param m the m-coordinate value
     *
     * @since 0.0.1
     */
    static Point from_xym(double x, double y, double m)
    {
        Point p;
        p.x   = x;
        p.y   = y;
        p.m   = m;
        p.dim = DimensionType::XYM;
        return p;
    }

    /*!
     * @brief creates a Point from coordinates (x, y, z, m)
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param z the z-coordinate value
     * @param m the m-coordinate value
     *
     * @since 0.0.1
     */
    static Point from_xyzm(double x, double y, double z, double m)
    {
        return {x, y, z, m};
    }

    /*!
     * @brief creates a Point
     * @tparam T an arithmetic value (e.g. int, float, double)
     * @param init the coordinates list
     * @throw exception if the given number of coordinates is either less than two or greater than four
     *
     * @since 0.0.1
     */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Point(std::initializer_list<T> init)
    {
        if (init.size() == 2)
        {
            x   = *init.begin();
            y   = *(init.begin() + 1);
            dim = DimensionType::XY;
        }
        else if (init.size() == 3)
        {
            x   = *init.begin();
            y   = *(init.begin() + 1);
            z   = *(init.begin() + 2);
            dim = DimensionType::XYZ;
        }
        else if (init.size() == 4)
        {
            x   = *init.begin();
            y   = *(init.begin() + 1);
            z   = *(init.begin() + 2);
            m   = *(init.begin() + 3);
            dim = DimensionType::XYZM;
        }
        else
        {
            throw exceptions::ValueError("invalid point");
        }
    }

    /*!
     * @brief returns the coordinate at the given index
     * @param pos the coordinate position
     * @return a double with the coordinate value
     * @throw exception if the position is not found
     *
     * @since 0.0.1
     */
    double at(size_t pos)
    {
        if (pos >= size_())
        {
            throw exceptions::ShapesException("out of range");
        }

        if (pos == 0)
        {
            return x;
        }

        if (pos == 1)
        {
            return y;
        }

        if (pos == 2)
        {
            return dim == DimensionType::XYM ? m : z;
        }

        return m;
    }

    /// @copydoc Point::at()
    double operator[](size_t pos)
    {
        return at(pos);
    }

    /*!
     * @brief returns true if all coordinates are equal, otherwise false
     * @param other the point to compare
     * @return true if all coordinates are equal, otherwise false
     *
     * @since 0.0.1
     */
    bool operator==(const Point& other) const
    {
        return x == other.x and y == other.y and z == other.z and m == other.m;
    }

    /*!
     * @brief returns true if at least one coordinate is different, otherwise false
     * @param other the point to compare
     * @return true if at least one coordinate is different, otherwise false
     *
     * @since 0.0.1
     */
    bool operator!=(const Point& other) const
    {
        return not(*this == other);
    }

    /*!
     * @brief creates a Point from a geojson string
     * @param json the geojson string
     * @return a Point object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static Point from_json(const std::string& json)
    {
        /// @todo (pavel) read properties to specify z, m and zm
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "Point")
        {
            throw exceptions::ParseError("invalid geometry type");
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
        throw exceptions::ParseError("");
    }

    /*!
     * @brief dumps the geojson representation of the Point
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        /// @todo (pavel) add properties to specify z, m and zm
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
     * @param wkt the WKT string
     * @return a Point object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static Point from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result = reader.read(wkt.c_str());
        switch (result.dim)
        {
            case DimensionType::XY:
                return {result.coords[0], result.coords[1]};
            case DimensionType::XYZ:
                return {result.coords[0], result.coords[1], result.coords[2]};
            case DimensionType::XYM:
                return Point::from_xym(result.coords[0], result.coords[1], result.coords[2]);
            case DimensionType::XYZM:
                return {result.coords[0], result.coords[1], result.coords[2], result.coords[3]};
            default:
                throw exceptions::ParseError("");
        }
    }

    /*!
     * @brief dumps the WKT representation of the point
     * @return a WKT string
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "POINT ";
        if (has_z())
        {
            ss << "Z";
        }
        if (has_m())
        {
            ss << "M";
        }
        if (has_z() or has_m())
        {
            ss << " ";
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

  private:
    /// for allow BaseGeometry to access Point private members
    friend class BaseGeometry<Point>;

    /// @private
    GeometryType type_() const
    {
        return GeometryType::POINT;
    }

    /// @private
    std::string type_str_() const
    {
        return "Point";
    }

    /// @private
    bool empty_() const
    {
        return false;
    }

    /// @private
    size_t size_() const
    {
        return static_cast<size_t>(ndim());
    }

    /// @private
    bool is_closed_() const
    {
        return false;
    }

    /*!
     * @private
     */
    std::vector<std::tuple<double, double>> xy_() const
    {
        return {std::make_tuple(x, y)};
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        return {std::make_tuple(x, y, z)};
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        return {std::make_tuple(x, y, m)};
    }

    /// @private
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        return {std::make_tuple(x, y, z, m)};
    }
};

}  // namespace shapes
}  // namespace simo