#pragma once

#include <ciso646>
#include <simo/geom/detail/multilinestring.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using multilinestring = basic_multilinestring<basic_linestring<basic_point<T>>>;

template <class T = double>
using multilinestring_z = basic_multilinestring<basic_linestring<basic_point_z<T>>>;

template <class T = double>
using multilinestring_m = basic_multilinestring<basic_linestring<basic_point_m<T>>>;

template <class T = double>
using multilinestring_zm = basic_multilinestring<basic_linestring<basic_point_zm<T>>>;

using MultiLineString   = multilinestring<double>;
using MultiLineStringZ  = multilinestring_z<double>;
using MultiLineStringM  = multilinestring_m<double>;
using MultiLineStringZM = multilinestring_zm<double>;

}  // namespace shapes
}  // namespace simo