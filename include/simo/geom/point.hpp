#pragma once

#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <json/json.hpp>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>

namespace simo
{
namespace shapes
{

class Point : public Geometry<Point>
{
  public:
    double x;
    double y;
    double z;

    Point()
        : x(0), y(0), z(0)
    {
        ndim = 2;
    }

    Point(double x, double y)
        : x(x), y(y), z(0)
    {
        ndim = 2;
    }

    Point(double x, double y, double z)
        : x(x), y(y), z(z)
    {
        ndim = 3;
    }

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Point(std::initializer_list<T> init)
    {
        if (init.size() == 2)
        {
            x    = *init.begin();
            y    = *(init.begin() + 1);
            z    = 0;
            ndim = 2;
        }
        else if (init.size() == 3)
        {
            x    = *init.begin();
            y    = *(init.begin() + 1);
            z    = *(init.begin() + 2);
            ndim = 3;
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
        return static_cast<size_t>(ndim);
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

    std::tuple<double, double> xy() const
    {
        return std::make_tuple(x, y);
    }

    std::tuple<double, double, double> xyz() const
    {
        return std::make_tuple(x, y, z);
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

    std::string to_json()
    {
        auto coordinates = std::vector<double>{x, y};
        if (ndim == 3)
        {
            coordinates.push_back(z);
        }
        nlohmann::json j = {{"type", "Point"}, {"coordinates", coordinates}};
        return j.dump();
    }
};

}  // namespace shapes
}  // namespace simo