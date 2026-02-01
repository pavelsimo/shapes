#pragma once

#include <ciso646>

namespace simo
{
namespace shapes
{
namespace algorithm
{

// Forward declarations for algorithm functions used in basic_geometry
// Full implementations are in the respective algorithm headers

// measurements.hpp
template <typename LineString>
auto length(const LineString& linestring) -> typename LineString::coord_type;

template <typename Polygon>
auto area(const Polygon& polygon) -> typename Polygon::coord_type;

// predicates.hpp
template <typename Polygon, typename Point>
bool contains(const Polygon& polygon, const Point& point);

template <typename Geom1, typename Geom2>
bool intersects(const Geom1& geom1, const Geom2& geom2);

template <typename Point, typename Polygon>
bool within(const Point& point, const Polygon& polygon);

// transformations.hpp
template <typename Geom>
Geom translate(const Geom& geom, typename Geom::coord_type xoff, typename Geom::coord_type yoff);

template <typename Geom>
Geom rotate(const Geom& geom, double angle);

template <typename Geom>
Geom scale(const Geom& geom, typename Geom::coord_type xfact, typename Geom::coord_type yfact);

// operations.hpp
template <typename LineString>
LineString simplify(const LineString& linestring, double tolerance);

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
