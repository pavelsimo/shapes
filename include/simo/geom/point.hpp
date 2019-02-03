#pragma once

#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <sstream>
#include <iomanip>
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

    Point()
        : x(0), y(0), z(0), has_z(false), has_m(false)
    {
        m_ndim = 2;
    }

    Point(double x, double y)
        : x(x), y(y), z(0), has_z(false), has_m(false)
    {
        m_ndim = 2;
    }

    Point(double x, double y, double z)
        : x(x), y(y), z(z), has_z(true), has_m(false)
    {
        m_ndim = 3;
    }

    Point(double x, double y, double z, double m)
        : x(x), y(y), z(z), m(m), has_z(true), has_m(true)
    {
        m_ndim = 4;
    }

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
        }
        else
        {
            throw exception();
        }
    }

    GeometryType geom_type_() const
    {
        return GeometryType::POINT;
    }

    std::string geom_type_str_() const
    {
        return "Point";
    }

    bool empty_() const
    {
        return false;
    }

    size_t size_() const
    {
        return static_cast<size_t>(m_ndim);
    }

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
        return z;
    }

    double operator[](size_t pos)
    {
        return at(pos);
    }

    std::vector<std::tuple<double, double>> xy_() const
    {
        return {std::make_tuple(x, y)};
    }

    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        return {std::make_tuple(x, y, z)};
    }

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

    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "POINT";
        if (has_z) ss << "Z";
        if (has_m) ss << "M";
        ss << "(";
        ss << x << " " << y;
        if (has_z) ss << " " << z;
        if (has_m) ss << " " << m;
        ss << ")";
        return ss.str();
    }


  private:
    bool has_z;
    bool has_m;
};

}  // namespace shapes
}  // namespace simo