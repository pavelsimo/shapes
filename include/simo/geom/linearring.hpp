#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/sequence.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a LineString that is both closed and simple, in shapes this feature is implicitly closed,
 * there is no need to specify the last coordinate, it will always be identical to the first.
 *
 * @ingroup geometry
 *
 * @since 0.0.1
 */
using LinearRing = LineString;

//class LinearRing : public BaseGeometry<LinearRing>, public detail::GeometrySequence<Point>
//{
//  public:
//    /// two-dimensional rotation direction, clockwise=true, counterclockwise=false
//    bool clockwise = true;
//
//    /*!
//     * @brief Creates an empty LinearRing
//     *
//     * @since 0.0.1
//     */
//    LinearRing() = default;
//
//    /*!
//      * @brief Creates a LinearRing from a given initializer list
//      *
//      * @tparam T an arithmetic value (e.g. int, float, double)
//      * @param init the initializer list
//      *
//      * @throw GeometryError DOCUMENT ME!
//      *
//      * @since 0.0.1
//      */
//    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
//    LinearRing(std::initializer_list<std::initializer_list<T>> init)
//    {
//        /// @todo (pavel) make LinearRing implicitly closed
//        seq.reserve(init.size());
//        for (const auto& coords : init)
//        {
//            Point p(coords);
//            bounds.extend(p.x, p.y);
//            seq.emplace_back(p);
//        }
//        throw_for_invalid();
//    }
//
//    /*!
//     * @brief Creates a LinearRing from a given point vector
//     *
//     * @param points the point list
//     *
//     * @throw GeometryError DOCUMENT ME!
//     *
//     * @since 0.0.1
//     */
//    explicit LinearRing(const std::vector<Point>& points)
//    {
//        /// @todo (pavel) make LinearRing implicitly closed
//        seq = points;
//        for (const auto& p : seq)
//        {
//            bounds.extend(p.x, p.y);
//        }
//        throw_for_invalid();
//    }
//
//  private:
//    /// for allow BaseGeometry to access LinearRing private members
//    friend class BaseGeometry<LinearRing>;
//
//    /// @private
//    void throw_for_invalid() const
//    {
//        if (empty())
//        {
//            return;
//        }
//
//        if (seq.size() < 4)
//        {
//            throw exceptions::GeometryError("LinearRing should be either empty or with 4 or more points");
//        }
//
//        if (not is_closed())
//        {
//            throw exceptions::GeometryError("LinearRing is not closed, first and last point are different");
//        }
//
//        /// @todo (pavel) check for self-intersections
//    }
//
//    /// @private
//    GeometryType geom_type_() const
//    {
//        return GeometryType::LINESTRING;
//    }
//
//    /// @private
//    std::string geom_type_str_() const
//    {
//        return "LineString";
//    }
//
//    /// @private
//    std::vector<std::vector<double>> coords_() const
//    {
//        throw exceptions::NotImplementedError();
//    }
//
//    /// @private
//    bool empty_() const
//    {
//        return seq.empty();
//    }
//
//    /// @private
//    size_t size_() const
//    {
//        return seq.size();
//    }
//
//    /// @private
//    bool is_closed_() const
//    {
//        if (seq.size() < 2)
//        {
//            return false;
//        }
//        size_t last_index = seq.size() - 1;
//        return seq[0] == seq[last_index];
//    }
//};

}  // namespace shapes
}  // namespace simo