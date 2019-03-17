#pragma once

#include <ciso646>
#include <simo/geom/point.hpp>

namespace simo
{
namespace shapes
{

template <typename Derived>
class PointCollection
{
  public:
    /// iterator type
    using iterator = std::vector<Point>::iterator;

    /// const iterator type
    using const_iterator = std::vector<Point>::const_iterator;

    /*!
     * @return returns an iterator pointing to the first element in the PointCollection
     *
     * @since 0.0.1
     */
    iterator begin()
    {
        return m_points.begin();
    }

    /*!
     * @return returns a constant iterator pointing to the first element in the PointCollection
     *
     * @since 0.0.1
     */
    const_iterator begin() const
    {
        return m_points.begin();
    }

    /*!
     * @return returns an iterator pointing to the past-the-end element in the PointCollection
     *
     * @since 0.0.1
     */
    iterator end()
    {
        return m_points.end();
    }

    /*!
     * @return returns a const iterator pointing to the past-the-end element in the PointCollection
     *
     * @since 0.0.1
     */
    const_iterator end() const
    {
        return m_points.end();
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in the vector
     *
     * @since 0.0.1
     */
    Point& at(size_t pos)
    {
        return m_points.at(pos);
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in the vector
     *
     * @since 0.0.1
     */
    Point& operator[](size_t pos)
    {
        return m_points.at(pos);
    }

  protected:
    std::vector<Point> m_points;
};

}  // namespace shapes
}  // namespace simo