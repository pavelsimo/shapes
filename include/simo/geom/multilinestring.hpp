#pragma once

#include <ciso646>
#include <simo/geom/detail/multilinestring.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using multilinestring_t = basic_multilinestring<basic_linestring<basic_point<T>>>;

template <class T = double>
using multilinestring_z_t = basic_multilinestring<basic_linestring<basic_point_z<T>>>;

template <class T = double>
using multilinestring_m_t = basic_multilinestring<basic_linestring<basic_point_m<T>>>;

template <class T = double>
using multilinestring_zm_t = basic_multilinestring<basic_linestring<basic_point_zm<T>>>;

using MultiLineString   = multilinestring_t<double>;
using MultiLineStringZ  = multilinestring_z_t<double>;
using MultiLineStringM  = multilinestring_m_t<double>;
using MultiLineStringZM = multilinestring_zm_t<double>;

}  // namespace shapes
}  // namespace simo