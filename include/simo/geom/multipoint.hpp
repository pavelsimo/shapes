#pragma once

#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/point.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/// TODO(pavel) : deal with precision

class MultiPoint : public BasicGeometry<MultiPoint>
{
  public:
    MultiPoint() = default;

    typedef std::vector<Point>::iterator iterator;
    typedef std::vector<Point>::const_iterator const_iterator;

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(std::initializer_list<std::initializer_list<T>> init)
    {
        for (const auto& coords : init)
        {
            Point p(coords);
            m_bounds.extend(p.x, p.y);
            m_points.push_back(std::move(p));
        }
    }

    explicit MultiPoint(std::vector<Point> points)
        : m_points(std::move(points))
    {
    }

    /*!
    * @copydoc Geometry::geom_type()
    */
    GeometryType geom_type_() const
    {
        return GeometryType::MULTIPOINT;
    }

    /*!
    * @copydoc Geometry::geom_type_str()
    */
    std::string geom_type_str_() const
    {
        return "MultiPoint";
    }

    /*!
    * @copydoc Geometry::empty()
    */
    bool empty_() const
    {
        return m_points.empty();
    }

    /*!
    * @copydoc Geometry::size()
    */
    size_t size_() const
    {
        return m_points.size();
    }

    /*!
    * @copydoc Geometry::xy()
    */
    std::vector<std::tuple<double, double>> xy_() const
    {
        std::vector<std::tuple<double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y);
        }
        return res;
    }

    /*!
    * @copydoc Geometry::xyz()
    */
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : m_points)
        {
            res.emplace_back(point.x, point.y, point.z);
        }
        return res;
    }

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

    std::string json()
    {
        /// @todo (pavel) remove json library here...
        auto coords = std::vector<std::vector<double>>();
        coords.reserve(m_points.size());
        for (const auto& p : *this)
        {
            if (p.ndim() == 2)
            {
                coords.emplace_back(std::vector<double>{p.x, p.y});
            }
            else if (p.ndim() == 3)
            {
                coords.emplace_back(std::vector<double>{p.x, p.y, p.z});
            }
        }
        nlohmann::json j = {{"type", "MultiPoint"}, {"coordinates", coords}};
        return j.dump();
    }

    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "MULTIPOINT";
        if (m_ndim >= 3)
            ss << "Z";
        if (m_ndim == 4)
            ss << "M";
        ss << "(";
        for (size_t i = 0; i < m_points.size(); ++i)
        {
            const Point& p = m_points[i];
            if (i > 0)
                ss << ",";
            ss << "(" << p.x << " " << p.y;
            if (m_ndim == 3)
                ss << " " << p.z;
            ss << ")";
        }
        ss << ")";
        return ss.str();
    }

  private:
    std::vector<Point> m_points;
};

}  // namespace shapes
}  // namespace simo