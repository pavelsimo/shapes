#pragma once

#include <ciso646>
#include <simo/geom/detail/multipoint.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using multipoint_t = basic_multipoint<basic_point<T>>;

template <class T = double>
using multipoint_z_t = basic_multipoint<basic_point_z<T>>;

template <class T = double>
using multipoint_m_t = basic_multipoint<basic_point_m<T>>;

template <class T = double>
using multipoint_zm_t = basic_multipoint<basic_point_zm<T>>;

using MultiPoint   = multipoint_t<double>;
using MultiPointZ  = multipoint_z_t<double>;
using MultiPointM  = multipoint_m_t<double>;
using MultiPointZM = multipoint_zm_t<double>;

}  // namespace shapes
}  // namespace simo