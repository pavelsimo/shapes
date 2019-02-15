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
#include <simo/io/wkt_reader.hpp>

namespace simo
{
namespace shapes
{

class Point : public BasicGeometry<Point>
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
     *
     * @note the default behaviour is to create a 2-dimensional point with coordinates (0, 0)
     *
     * @since 0.0.1
     */
    Point()
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
        : x(x), y(y)
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
     * @brief creates a Point from coordinates (x, y)
     *
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
     *
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
     *
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     * @param m the m-coordinate value
     *
     * @since 0.0.1
     */
    static Point from_xym(double x, double y, double m)
    {
        Point p;
        p.x         = x;
        p.y         = y;
        p.m         = m;
        p.dimension = DimensionType::XYM;
        return p;
    }

    /*!
       * @brief creates a Point from coordinates (x, y, z, m)
       *
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
            x         = *init.begin();
            y         = *(init.begin() + 1);
            dimension = DimensionType::XY;
        }
        else if (init.size() == 3)
        {
            x         = *init.begin();
            y         = *(init.begin() + 1);
            z         = *(init.begin() + 2);
            dimension = DimensionType::XYZ;
        }
        else if (init.size() == 4)
        {
            x         = *init.begin();
            y         = *(init.begin() + 1);
            z         = *(init.begin() + 2);
            m         = *(init.begin() + 3);
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
    * @copydoc Geometry::xym()
    */
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        return {std::make_tuple(x, y, m)};
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
            throw exceptions::shapes_exception("out of range");
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
        Point res;
        wkt_lexer lexer(wkt.c_str());
        auto tag = lexer.scan();
        if (tag != wkt_lexer::token_type::point_tagged_text and
            tag != wkt_lexer::token_type::point_z_tagged_text and
            tag != wkt_lexer::token_type::point_m_tagged_text and
            tag != wkt_lexer::token_type::point_zm_tagged_text)
        {
            throw exceptions::parse_error("invalid point tag");
        }

        auto text = lexer.scan();
        if (text != wkt_lexer::token_type::point_text)
        {
            throw exceptions::parse_error("invalid point text");
        }

        auto point_text = lexer.get_token();
        point_text      = point_text.substr(1, point_text.size() - 2);
        std::stringstream in(point_text);

        bool point_text_error = false;
        switch (tag)
        {
            case wkt_lexer::token_type::point_tagged_text:
            {
                res.dimension = DimensionType::XY;
                in >> res.x;
                if (in.eof())
                    point_text_error = true;
                in >> res.y;
                break;
            }
            case wkt_lexer::token_type::point_z_tagged_text:
            {
                res.dimension = DimensionType::XYZ;
                in >> res.x;
                if (in.eof())
                    point_text_error = true;
                in >> res.y;
                if (in.eof())
                    point_text_error = true;
                in >> res.z;
                break;
            }
            case wkt_lexer::token_type::point_m_tagged_text:
            {
                res.dimension = DimensionType::XYM;
                in >> res.x;
                if (in.eof())
                    point_text_error = true;
                in >> res.y;
                if (in.eof())
                    point_text_error = true;
                in >> res.m;
                break;
            }
            case wkt_lexer::token_type::point_zm_tagged_text:
            {
                res.dimension = DimensionType::XYZM;
                in >> res.x;
                if (in.eof())
                    point_text_error = true;
                in >> res.y;
                if (in.eof())
                    point_text_error = true;
                in >> res.z;
                if (in.eof())
                    point_text_error = true;
                in >> res.m;
                break;
            }
        }

        if (point_text_error or not in.eof())
        {
            throw exceptions::parse_error("invalid point dimensions");
        }

        auto token = lexer.scan();
        if (token != wkt_lexer::token_type::end_of_input)
        {
            throw exceptions::parse_error("invalid point");
        }

        return res;
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