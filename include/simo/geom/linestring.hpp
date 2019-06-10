#pragma once

#include <ciso646>
#include <simo/geom/detail/linestring.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using linestring_t = basic_linestring<basic_point<T>>;

template <class T = double>
using linestring_z_t = basic_linestring<basic_point_z<T>>;

template <class T = double>
using linestring_m_t = basic_linestring<basic_point_m<T>>;

template <class T = double>
using linestring_zm_t = basic_linestring<basic_point_zm<T>>;

using LineString   = linestring_t<double>;
using LineStringZ  = linestring_z_t<double>;
using LineStringM  = linestring_m_t<double>;
using LineStringZM = linestring_zm_t<double>;

}  // namespace shapes
}  // namespace simo