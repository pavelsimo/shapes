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

/// @todo (pavel) LinearRing is not closed, first and last point are different
/// @todo (pavel) LinearRing should be either empty or with 4 or more points
/// @todo (pavel) LinearRing cannot self-intersect
/// @todo (pavel) LinearRing should be implicitly closed

}  // namespace shapes
}  // namespace simo