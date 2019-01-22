#pragma once

#include <simo/geom/point.hpp>

class Envelope
{
  public:
    Envelope(double minx, double maxx, double miny, double maxy)
        : m_min(Point(minx, miny)), m_max(Point(maxx, maxy))
    {
    }

    Envelope& extend(double x, double y)
    {
        m_min.x = std::min(x, m_min.x);
        m_max.x = std::max(x, m_max.x);
        m_min.y = std::min(y, m_min.y);
        m_max.y = std::max(y, m_max.y);
        return *this;
    }

    Point center() const { return {(m_min.x + m_max.x) / 2, (m_min.y + m_max.y) / 2}; }

    Point bottom_left() const { return {m_min.x, m_max.y}; }

    Point top_right() const { return {m_max.x, m_min.y}; }

    Point top_left() const { return m_min; }

    Point bottom_right() const { return m_max; }

    Point min() const { return m_min; }

    Point max() const { return m_max; }

    bool contains(const Point& other) const
    {
        return (other.x >= m_min.x) && (other.x <= m_max.x) && (other.y >= m_min.y) && (other.y <= m_max.y);
    }

    bool contains(const Envelope& other) { return contains(other.min()) && contains(other.max()); }

    bool intersects(const Envelope& other)
    {
        auto min  = m_min;
        auto max  = m_max;
        auto min2 = other.min();
        auto max2 = other.max();
        return (max2.x >= min.x) && (min2.x <= max.x) && (max2.y >= min.y) && (min2.y <= max.y);
    }

    bool overlaps(const Envelope& other)
    {
        auto min  = m_min;
        auto max  = m_max;
        auto min2 = other.min();
        auto max2 = other.max();
        return (max2.x > min.x) && (min2.x < max.x) && (max2.y > min.y) && (min2.y < max.y);
    }

  private:
    Point m_min;
    Point m_max;
};
