#pragma once

#include <vector>
#include <set>
#include <simo/geom/geometry.hpp>
#include <simo/geom/point.hpp>
#include <simo/geom/envelope.hpp>

namespace simo
{
namespace shapes
{

typedef Geometry<multipoint_t> MultiPoint;

class multipoint_t
{
  public:
    multipoint_t() = default;

    template <
        typename T,  //real type
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    multipoint_t(std::initializer_list<std::initializer_list<T>> list)
    {
        std::set<int> dimensions;
        for (const auto& coords : list)
        {
            Point p(coords);
            dimensions.insert(p.dimension());
            m_envelope.extend(p.x, p.y);
            m_points.push_back(std::move(p));
        }

        if (dimensions.size() >= 2)
        {
            /// @todo throw an exception
        }
    }

    explicit multipoint_t(std::vector<Point> points)
        : m_points(std::move(points))
    {
    }

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

    GeometryType geom_type() const
    {
        return GeometryType::MULTIPOINT;
    }

    std::string geom_type_str() const
    {
        return "MULTIPOINT";
    }

    int8_t dimension() const
    {
        return 0;
    }

    Point at(size_t pos)
    {
        return m_points.at(pos);
    }

    Point operator[](size_t pos)
    {
        return m_points[pos];
    }

    Envelope envelope() const
    {
        return m_envelope;
    }

    size_t size() noexcept
    {
        return m_points.size();
    }

    static MultiPoint from_json(const std::string& json)
    {
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "MultiPoint")
        {
            /// @todo parse error...
        }

        auto points = j.at("coordinates").get<std::vector<std::vector<double>>>();
        std::vector<Point> res;
        for (const auto& coordinates : points)
        {
            if (coordinates.size() == 2)
            {
                res.emplace_back(Point{coordinates[0], coordinates[1]});
            }
            else if (coordinates.size() == 3)
            {
                res.emplace_back(Point{coordinates[0], coordinates[1], coordinates[2]});
            }
            else
            {
                /// @todo parse error...
            }
        }
        return MultiPoint(res);
    }

    std::string to_json()
    {
        auto coordinates = std::vector<std::vector<double>>();
        coordinates.reserve(m_points.size());
        for (const auto& p : *this)
        {
            if (p.dimension() == 2)
            {
                coordinates.emplace_back(std::vector<double>{p.x, p.y});
            }
            else if (p.dimension() == 3)
            {
                coordinates.emplace_back(std::vector<double>{p.x, p.y, p.z});
            }
        }
        nlohmann::json j = {{"type", "MultiPoint"}, {"coordinates", coordinates}};
        return j.dump();
    }

  private:
    std::vector<Point> m_points;
    Envelope m_envelope;
};

}  // namespace shapes
}  // namespace simo