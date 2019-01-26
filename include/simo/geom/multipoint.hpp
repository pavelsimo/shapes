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

  private:
    std::vector<Point> m_points;
    Envelope m_envelope;
};

typedef Geometry<multipoint_t> MultiPoint;

}  // namespace shapes
}  // namespace simo