#pragma once

#include <ciso646>
#include <simo/geom/detail/polygon.hpp>

namespace simo
{
namespace shapes
{

template <class T = double>
using polygon = basic_polygon<linearring<T>>;

template <class T = double>
using polygon_z = basic_polygon<linearring_z<T>>;

template <class T = double>
using polygon_m = basic_polygon<linearring_m<T>>;

template <class T = double>
using polygon_zm = basic_polygon<linearring_zm<T>>;

using Polygon   = polygon<double>;
using PolygonZ  = polygon_z<double>;
using PolygonM  = polygon_m<double>;
using PolygonZM = polygon_zm<double>;

}  // namespace shapes
}  // namespace simo