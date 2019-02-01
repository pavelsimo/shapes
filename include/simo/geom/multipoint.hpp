#pragma once

#include <vector>
#include <set>
#include <simo/geom/geometry.hpp>
#include <simo/geom/point.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

class MultiPoint : public Geometry<MultiPoint>
{
  public:
    MultiPoint() = default;

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(std::initializer_list<std::initializer_list<T>> list)
    {
        for (const auto& coordinates : list)
        {
            Point p(coordinates);
            m_bounds.extend(p.x, p.y);
            m_points.push_back(std::move(p));
        }
        /// @todo (pavel) check dimensions?
    }

    explicit MultiPoint(std::vector<Point> points)
        : m_points(std::move(points))
    {
        /// @todo (pavel) check dimensions?
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

    GeometryType geom_type_impl() const
    {
        return GeometryType::MULTIPOINT;
    }

    std::string geom_type_str_impl() const
    {
        return "MultiPoint";
    }

    int8_t dimension_impl() const
    {
        return 0;
    }

    Point at(size_t pos)
    {
        return m_points.at(pos);
    }

    Point operator[](size_t pos)
    {
        return m_points.at(pos);
    }

    bool empty_impl() const
    {
        return m_points.empty();
    }

    Bounds bounds() const
    {
        return m_bounds;
    }

    size_t size_impl() const
    {
        return m_points.size();
    }

    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        for (const auto& point : m_points)
        {
            res.push_back(point.xy());
        }
        return res;
    }

    std::vector<std::tuple<double, double, double>> xyz() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.push_back(point.xyz());
        }
        return res;
    }

    static MultiPoint from_json(const std::string& json)
    {
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "MultiPoint")
        {
            throw parse_error();
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
                throw parse_error();
            }
        }
        return MultiPoint(res);
    }

    std::string to_json()
    {
        auto coords = std::vector<std::vector<double>>();
        coords.reserve(m_points.size());
        for (const auto& p : *this)
        {
            if (p.dimension_impl() == 2)
            {
                coords.emplace_back(std::vector<double>{p.x, p.y});
            }
            else if (p.dimension_impl() == 3)
            {
                coords.emplace_back(std::vector<double>{p.x, p.y, p.z});
            }
        }
        nlohmann::json j = {{"type", "MultiPoint"}, {"coordinates", coords}};
        return j.dump();
    }

  private:

    std::vector<Point> m_points;
    Bounds m_bounds;
};

}  // namespace shapes
}  // namespace simo