#pragma once

#include <ciso646>
#include <simo/geom/detail/polygon.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using polygon_t = basic_polygon<linearring_t<T>>;

template <class T = double>
using polygon_z_t = basic_polygon<linearring_z_t<T>>;

template <class T = double>
using polygon_m_t = basic_polygon<linearring_m_t<T>>;

template <class T = double>
using polygon_zm_t = basic_polygon<linearring_zm_t<T>>;

using Polygon   = polygon_t<double>;
using PolygonZ  = polygon_z_t<double>;
using PolygonM  = polygon_m_t<double>;
using PolygonZM = polygon_zm_t<double>;

}  // namespace shapes
}  // namespace simo