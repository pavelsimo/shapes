#pragma once

#include <ciso646>
#include <simo/geom/point.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief represents a geometry sequence
 * @tparam T the geometry type (e.g. Point, LineString, Polygon)
 *
 * @since 0.0.1
 */
template <typename T>
class GeometrySequence
{
  public:
    /// iterator type
    typedef typename std::vector<T>::iterator iterator;

    /// const iterator type
    typedef typename std::vector<T>::const_iterator const_iterator;

    /*!
     * @return returns an iterator pointing to the first element in T
     *
     * @since 0.0.1
     */
    iterator begin()
    {
        return seq.begin();
    }

    /*!
     * @return returns a constant iterator pointing to the first element in T
     *
     * @since 0.0.1
     */
    const_iterator begin() const
    {
        return seq.begin();
    }

    /*!
     * @return returns an iterator pointing to the past-the-end element in T
     *
     * @since 0.0.1
     */
    iterator end()
    {
        return seq.end();
    }

    /*!
     * @return returns a const iterator pointing to the past-the-end element in T
     *
     * @since 0.0.1
     */
    const_iterator end() const
    {
        return seq.end();
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in T
     *
     * @since 0.0.1
     */
    T& at(size_t pos)
    {
        return seq.at(pos);
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in T
     *
     * @since 0.0.1
     */
    T& operator[](size_t pos)
    {
        return seq.at(pos);
    }

  protected:
    /// the geometry sequence
    std::vector<T> seq;
};

}  // namespace shapes
}  // namespace simo