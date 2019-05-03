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
 * @ingroup geometry
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
     * @brief creates a Point from coordinates
     * @param coords the coordinates
     *
     * @throw GeometryError DOCUMENT ME!
     *
     * @since 0.0.1
     */
    explicit Point(const std::vector<double>& coords)
    {
        if (coords.size() == 2)
        {
            x   = coords[0];
            y   = coords[1];
            dim = DimensionType::XY;
        }
        else if (coords.size() == 3)
        {
            x   = coords[0];
            y   = coords[1];
            z   = coords[2];
            dim = DimensionType::XYZ;
        }
        else if (coords.size() == 4)
        {
            x   = coords[0];
            y   = coords[1];
            z   = coords[2];
            m   = coords[3];
            dim = DimensionType::XYZM;
        }
        else
        {
            throw exceptions::GeometryError("invalid number of dimensions " + std::to_string(coords.size()));
        }
    }
    /*!
     * @brief creates a Point
     * @tparam T an arithmetic value (e.g. int, float, double)
     * @param init the coordinates list
     * @throw exception if the given number of coordinates is either less than two or greater than four
     *
     * @throw GeometryError DOCUMENT ME!
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
            throw exceptions::GeometryError("invalid number of dimensions " + std::to_string(init.size()));
        }
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
     * @brief returns the coordinate at the given index
     * @param pos the coordinate position
     * @return a double with the coordinate value
     *
     * @throw IndexError if the index at pos is out of range
     *
     * @since 0.0.1
     */
    double& at(size_t pos)
    {
        if (pos >= size_())
        {
            throw exceptions::IndexError("index at " + std::to_string(pos) + " is out of range");
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
    double& operator[](size_t pos)
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

    /// @todo (pavel) implement operator std::ostream & operator<<

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
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Point")
            {
                throw exceptions::ParseError("invalid geometry type");
            }
            auto coords = j.at("coordinates").get<std::vector<double>>();
            return Point(coords);
        }
        catch (const nlohmann::json::exception& e)
        {
            throw exceptions::ParseError("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::GeometryError& e)
        {
            throw exceptions::ParseError("invalid geometry: " + std::string(e.what()));
        }
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
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static Point from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        switch (data.geom_type)
        {
            case GeometryType::POINT:
                return {data.coords[0], data.coords[1]};
            case GeometryType::POINTZ:
                return {data.coords[0], data.coords[1], data.coords[2]};
            case GeometryType::POINTM:
                return Point::from_xym(data.coords[0], data.coords[1], data.coords[2]);
            case GeometryType::POINTZM:
                return {data.coords[0], data.coords[1], data.coords[2], data.coords[3]};
            default:
                throw exceptions::ParseError("invalid wkt string");
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
    GeometryType geom_type_() const
    {
        return GeometryType::POINT;
    }

    /// @private
    std::string geom_type_str_() const
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