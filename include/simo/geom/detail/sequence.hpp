#pragma once

#include <ciso646>
#include <simo/geom/point.hpp>

namespace simo
{
namespace shapes
{
namespace detail
{

/*!
 * @brief represents a geometry sequence
 * @tparam T the geometry type (e.g. LineString, MultiPoint)
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
     * @throw IndexError if the index at pos is out of range
     *
     * @since 0.0.1
     */
    const T& at(size_t pos) const
    {
        try
        {
            return seq.at(pos);
        }
        catch (std::out_of_range&)
        {
            throw exceptions::IndexError("index at " + std::to_string(pos) + " is out of range");
        }
    }

    /// @copydoc GeometrySequence::at()
    T& at(size_t pos)
    {
        try
        {
            return seq.at(pos);
        }
        catch (std::out_of_range&)
        {
            throw exceptions::IndexError("index at " + std::to_string(pos) + " is out of range");
        }
    }

    /*!
    * @param pos the element position
    * @return returns a reference to the element at position n in T
    *
    * @since 0.0.1
    */
    T& operator[](size_t pos)
    {
        return at(pos);
    }

  protected:
    /// the geometry sequence
    std::vector<T> seq;
};

/*!
 * @brief creates a Point sequence from a given initializer list
 * @tparam T an arithmetic value (e.g. int, float, double)
 * @param init the initializer list
 * @param[out] seq the output Point sequence
 * @param[out] bounds the bounding box for the Point sequence
 * @param[out] dim the dimension type
 *
 * @since 0.0.1
 */
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
void create_sequence(std::initializer_list<std::initializer_list<T>> init, std::vector<Point>& seq, Bounds& bounds, DimensionType& dim)
{
    if (init.size() > 0)
    {
        auto it = init.begin();
        Point head(*it);
        dim = head.dim;
        bounds.extend(head.x, head.y);
        auto ndim = static_cast<size_t>(utils::get_ndim(head.dim));
        seq.reserve(init.size() / ndim);
        seq.emplace_back(head);
        ++it;
        for (; it != init.end(); ++it)
        {
            Point p(*it);
            if (p.dim != dim)
            {
                throw exceptions::GeometryError("dimension mismatch in start point and point at index " + std::to_string(it - init.begin()));
            }
            bounds.extend(p.x, p.y);
            seq.emplace_back(p);
        }
    }
}

/*!
 * creates a Point sequence from another Point sequence
 * @param points the reference Point sequence
 * @param[out] seq the output Point sequence
 * @param[out] bounds the bounding box for the Point sequence
 * @param[out] dim the dimension type
 *
 * @since 0.0.1
 */
void create_sequence(const std::vector<Point>& points, std::vector<Point>& seq, Bounds& bounds, DimensionType& dim)
{
    if (not points.empty())
    {
        dim = points[0].dim;
        seq = points;
        std::for_each(std::begin(points), std::end(points), [&](const Point& p) {
            bounds.extend(p.x, p.y);
        });
    }
}

/*!
 * @brief creates a Point sequence from an arithmetic value sequence
 * @tparam T an arithmetic value (e.g. int, float, double)
 * @param coords the arithmetic value sequence
 * @param input_dim the input dimension type
 * @param[out] seq the output Point sequence
 * @param[out] bounds the bounding box for the Point sequence
 * @param[out] dim the dimension type
 *
 * @since 0.0.1
 */
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
void create_sequence(const std::vector<T>& coords, const DimensionType input_dim, std::vector<Point>& seq, Bounds& bounds, DimensionType& dim)
{
    auto ndim = static_cast<size_t>(utils::get_ndim(input_dim));
    seq.reserve(coords.size() / ndim);
    dim = input_dim;
    Point p;
    p.dim = input_dim;
    for (size_t i = 0; i < coords.size(); i += ndim)
    {
        for (size_t k = 0; k < ndim; ++k)
        {
            p[k] = coords[i + k];
        }
        bounds.extend(p.x, p.y);
        seq.push_back(p);
    }
}

/*!
 * @brief returns true if both sequence are equal, otherwise false
 * @tparam T the sequence type (e.g. MultiPoint, LineString)
 * @param lhs a sequence
 * @param rhs another sequence
 * @return a bool with the result of the comparison
 *
 * @since 0.0.1
 */
template <typename T>
bool is_equal_sequence(const T& lhs, const T& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs.at(i) != rhs.at(i))
        {
            return false;
        }
    }
    return true;
}

}  // namespace detail
}  // namespace shapes
}  // namespace simo