#pragma once

#include <ciso646>
#include <simo/geom/detail/point.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using point = basic_point<T>;

template <class T = double>
using point_z = basic_point_z<T>;

template <class T = double>
using point_m = basic_point_m<T>;

template <class T = double>
using point_zm = basic_point_zm<T>;

using Point   = point<double>;
using PointZ  = point_z<double>;
using PointM  = point_m<double>;
using PointZM = point_zm<double>;

}  // namespace shapes
}  // namespace simo