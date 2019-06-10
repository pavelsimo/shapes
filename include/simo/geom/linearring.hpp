#pragma once

#include <ciso646>
#include <simo/geom/detail/linestring.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using linearring_t = basic_linestring<basic_point<T>>;

template <class T = double>
using linearring_z_t = basic_linestring<basic_point_z<T>>;

template <class T = double>
using linearring_m_t = basic_linestring<basic_point_m<T>>;

template <class T = double>
using linearring_zm_t = basic_linestring<basic_point_zm<T>>;

using LinearRing   = linearring_t<double>;
using LinearRingZ  = linearring_z_t<double>;
using LinearRingM  = linearring_m_t<double>;
using LinearRingZM = linearring_zm_t<double>;

/// @todo (pavel) LinearRing is not closed, first and last point are different
/// @todo (pavel) LinearRing should be either empty or with 4 or more points
/// @todo (pavel) LinearRing cannot self-intersect
/// @todo (pavel) LinearRing should be implicitly closed

}  // namespace shapes
}  // namespace simo