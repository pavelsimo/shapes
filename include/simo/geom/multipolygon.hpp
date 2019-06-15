#pragma once

#include <ciso646>
#include <simo/geom/detail/multipolygon.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using multipolygon_t = basic_multipolygon<basic_polygon<linearring_t<T>>>;

template <class T = double>
using multipolygon_z_t = basic_multipolygon<basic_polygon<linearring_z_t<T>>>;

template <class T = double>
using multipolygon_m_t = basic_multipolygon<basic_polygon<linearring_m_t<T>>>;

template <class T = double>
using multipolygon_zm_t = basic_multipolygon<basic_polygon<linearring_zm_t<T>>>;

using multipolygon    = multipolygon_t<double>;
using multipolygon_z  = multipolygon_z_t<double>;
using multipolygon_m  = multipolygon_m_t<double>;
using multipolygon_zm = multipolygon_zm_t<double>;

using MultiPolygon   = multipolygon_t<double>;
using MultiPolygonZ  = multipolygon_z_t<double>;
using MultiPolygonM  = multipolygon_m_t<double>;
using MultiPolygonZM = multipolygon_zm_t<double>;

}  // namespace shapes
}  // namespace simo