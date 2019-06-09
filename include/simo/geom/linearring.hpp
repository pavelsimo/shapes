#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/bounds.hpp>

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
template <class T = double>
using linearring = basic_linestring<basic_point<T>>;

template <class T = double>
using linearring_z = basic_linestring<basic_point_z<T>>;

template <class T = double>
using linearring_m = basic_linestring<basic_point_m<T>>;

template <class T = double>
using linearring_zm = basic_linestring<basic_point_zm<T>>;

using LinearRing   = linearring<double>;
using LinearRingZ  = linearring_z<double>;
using LinearRingM  = linearring_m<double>;
using LinearRingZM = linearring_zm<double>;

/// @todo (pavel) LinearRing is not closed, first and last point are different
/// @todo (pavel) LinearRing should be either empty or with 4 or more points
/// @todo (pavel) LinearRing cannot self-intersect
/// @todo (pavel) LinearRing should be implicitly closed

}  // namespace shapes
}  // namespace simo