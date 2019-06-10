#pragma once

#include <ciso646>
#include <simo/geom/detail/linestring.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using linestring = basic_linestring<basic_point<T>>;

template <class T = double>
using linestring_z = basic_linestring<basic_point_z<T>>;

template <class T = double>
using linestring_m = basic_linestring<basic_point_m<T>>;

template <class T = double>
using linestring_zm = basic_linestring<basic_point_zm<T>>;

using LineString   = linestring<double>;
using LineStringZ  = linestring_z<double>;
using LineStringM  = linestring_m<double>;
using LineStringZM = linestring_zm<double>;

}  // namespace shapes
}  // namespace simo