#pragma once

#include <ciso646>
#include <simo/geom/detail/multipoint.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using multipoint = basic_multipoint<basic_point<T>>;

template <class T = double>
using multipoint_z = basic_multipoint<basic_point_z<T>>;

template <class T = double>
using multipoint_m = basic_multipoint<basic_point_m<T>>;

template <class T = double>
using multipoint_zm = basic_multipoint<basic_point_zm<T>>;

using MultiPoint   = multipoint<double>;
using MultiPointZ  = multipoint_z<double>;
using MultiPointM  = multipoint_m<double>;
using MultiPointZM = multipoint_zm<double>;

}  // namespace shapes
}  // namespace simo