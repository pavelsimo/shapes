#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/detail/geometry.hpp>
#include <simo/geom/detail/bounds.hpp>

namespace simo
{
namespace shapes
{

/// @todo (pavel) implement multipolygon

template <class T = double>
using multipolygon_t = basic_multilinestring<basic_linestring<basic_point<T>>>;

template <class T = double>
using multipolygon_z_t = basic_multilinestring<basic_linestring<basic_point_z<T>>>;

template <class T = double>
using multipolygon_m_t = basic_multilinestring<basic_linestring<basic_point_m<T>>>;

template <class T = double>
using multipolygon_zm_t = basic_multilinestring<basic_linestring<basic_point_zm<T>>>;

using MultiLineString   = multilinestring_t<double>;
using MultiLineStringZ  = multilinestring_z_t<double>;
using MultiLineStringM  = multilinestring_m_t<double>;
using MultiLineStringZM = multilinestring_zm_t<double>;

}  // namespace shapes
}  // namespace simo