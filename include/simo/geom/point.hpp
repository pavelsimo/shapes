#pragma once

#include <ciso646>
#include <simo/geom/detail/point.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using point_t = basic_point<T>;

template <class T = double>
using point_z_t = basic_point_z<T>;

template <class T = double>
using point_m_t = basic_point_m<T>;

template <class T = double>
using point_zm_t = basic_point_zm<T>;

using Point   = point_t<double>;
using PointZ  = point_z_t<double>;
using PointM  = point_m_t<double>;
using PointZM = point_zm_t<double>;

}  // namespace shapes
}  // namespace simo