#pragma once

#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <string>
#include <type_traits>
#include <json/json.hpp>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>

namespace simo
{
namespace shapes
{

typedef Geometry<point_t> Point;

class point_t
{
  public:
    double x;
    double y;
    double z;

    point_t()
    {
        this->x           = 0;
        this->y           = 0;
        this->z           = 0;
        this->m_dimension = 2;
    }

    template <
        typename T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    point_t(std::initializer_list<T> list)
    {
        if (list.size() == 2)
        {
            this->x           = *list.begin();
            this->y           = *(list.begin() + 1);
            this->z           = 0;
            this->m_dimension = 2;
        }
        else if (list.size() == 3)
        {
            this->x           = *list.begin();
            this->y           = *(list.begin() + 1);
            this->z           = *(list.begin() + 2);
            this->m_dimension = 3;
        }
        else
        {
            /// @todo (pavel) report error
        }
    }

    GeometryType geom_type() const
    {
        return GeometryType::POINT;
    }

    std::string geom_type_str() const
    {
        return "POINT";
    }

    int8_t dimension() const
    {
        return m_dimension;
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
        if (m_dimension == 3)
        {
            coordinates.push_back(z);
        }
        nlohmann::json j = {{"type", "Point"}, {"coordinates", coordinates}};
        return j.dump();
    }

  private:
    int8_t m_dimension;
};

}  // namespace shapes
}  // namespace simo