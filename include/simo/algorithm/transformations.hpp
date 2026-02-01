#pragma once

#include <ciso646>
#include <cmath>
#include <type_traits>

namespace simo
{
namespace shapes
{
namespace algorithm
{

// SFINAE helpers for detecting geometry types by their structure
namespace detail
{
    // Detect if type has x and y members (Point-like)
    template <typename T, typename = void>
    struct has_xy : std::false_type {};

    template <typename T>
    struct has_xy<T, decltype(void(std::declval<T>().x), void(std::declval<T>().y))> : std::true_type {};

    // Detect if type's value_type has x and y (container of points)
    template <typename T, typename = void>
    struct value_type_has_xy : std::false_type {};

    template <typename T>
    struct value_type_has_xy<T, decltype(void(std::declval<typename T::value_type>().x),
                                          void(std::declval<typename T::value_type>().y))> : std::true_type {};

    // Detect if type's value_type's value_type has x and y (container of containers of points)
    template <typename T, typename = void>
    struct value_type_value_type_has_xy : std::false_type {};

    template <typename T>
    struct value_type_value_type_has_xy<T, decltype(
        void(std::declval<typename T::value_type::value_type>().x),
        void(std::declval<typename T::value_type::value_type>().y))> : std::true_type {};

    // Detect if type is Point-like: has x,y AND value_type is a scalar (fundamental) type
    template <typename T, typename = void>
    struct is_point_like : std::false_type {};

    template <typename T>
    struct is_point_like<T, typename std::enable_if<
        has_xy<T>::value && std::is_fundamental<typename T::value_type>::value
    >::type> : std::true_type {};

    // Detect if type is LineString-like: value_type has x,y (is a Point)
    template <typename T, typename = void>
    struct is_linestring_like : std::false_type {};

    template <typename T>
    struct is_linestring_like<T, typename std::enable_if<
        value_type_has_xy<T>::value && !value_type_value_type_has_xy<T>::value
    >::type> : std::true_type {};

    // Detect if type is Polygon-like: value_type is LineString-like (container of linestrings)
    template <typename T, typename = void>
    struct is_polygon_like : std::false_type {};

    template <typename T>
    struct is_polygon_like<T, typename std::enable_if<
        value_type_value_type_has_xy<T>::value
    >::type> : std::true_type {};
}

//
// TRANSLATE
//

/*! @brief Translate a point by offset */
template <typename Point>
typename std::enable_if<detail::is_point_like<Point>::value, Point>::type
translate(const Point& point, typename Point::coord_type xoff, typename Point::coord_type yoff)
{
    Point result = point;
    result.x += xoff;
    result.y += yoff;
    return result;
}

/*! @brief Translate a linestring by offset */
template <typename LineString>
typename std::enable_if<detail::is_linestring_like<LineString>::value, LineString>::type
translate(const LineString& linestring, typename LineString::coord_type xoff,
          typename LineString::coord_type yoff)
{
    LineString result;
    result.reserve(linestring.size());

    for (const auto& point : linestring)
    {
        result.push_back(translate(point, xoff, yoff));
    }

    return result;
}

/*! @brief Translate a polygon by offset */
template <typename Polygon>
typename std::enable_if<detail::is_polygon_like<Polygon>::value, Polygon>::type
translate(const Polygon& polygon, typename Polygon::coord_type xoff,
          typename Polygon::coord_type yoff)
{
    Polygon result;
    result.reserve(polygon.size());

    for (const auto& ring : polygon)
    {
        result.push_back(translate(ring, xoff, yoff));
    }

    return result;
}

//
// ROTATE
//

/*! @brief Rotate a point around origin by angle (in radians) */
template <typename Point>
typename std::enable_if<detail::is_point_like<Point>::value, Point>::type
rotate(const Point& point, double angle, const Point& origin = Point{0, 0})
{
    double cos_a = std::cos(angle);
    double sin_a = std::sin(angle);

    // Translate to origin
    auto dx = point.x - origin.x;
    auto dy = point.y - origin.y;

    // Rotate
    Point result;
    result.x = origin.x + dx * cos_a - dy * sin_a;
    result.y = origin.y + dx * sin_a + dy * cos_a;

    return result;
}

/*! @brief Rotate a linestring around origin by angle (in radians) */
template <typename LineString>
typename std::enable_if<detail::is_linestring_like<LineString>::value, LineString>::type
rotate(const LineString& linestring, double angle,
       const typename LineString::value_type& origin = typename LineString::value_type{0, 0})
{
    LineString result;
    result.reserve(linestring.size());

    for (const auto& point : linestring)
    {
        result.push_back(rotate(point, angle, origin));
    }

    return result;
}

/*! @brief Rotate a polygon around origin by angle (in radians) */
template <typename Polygon>
typename std::enable_if<detail::is_polygon_like<Polygon>::value, Polygon>::type
rotate(const Polygon& polygon, double angle,
       const typename Polygon::value_type::value_type& origin = typename Polygon::value_type::value_type{0, 0})
{
    Polygon result;
    result.reserve(polygon.size());

    for (const auto& ring : polygon)
    {
        result.push_back(rotate(ring, angle, origin));
    }

    return result;
}

//
// SCALE
//

/*! @brief Scale a point by factors */
template <typename Point>
typename std::enable_if<detail::is_point_like<Point>::value, Point>::type
scale(const Point& point, typename Point::coord_type xfact, typename Point::coord_type yfact,
      const Point& origin = Point{0, 0})
{
    Point result;
    result.x = origin.x + (point.x - origin.x) * xfact;
    result.y = origin.y + (point.y - origin.y) * yfact;
    return result;
}

/*! @brief Scale a linestring by factors */
template <typename LineString>
typename std::enable_if<detail::is_linestring_like<LineString>::value, LineString>::type
scale(const LineString& linestring, typename LineString::coord_type xfact,
      typename LineString::coord_type yfact,
      const typename LineString::value_type& origin = typename LineString::value_type{0, 0})
{
    LineString result;
    result.reserve(linestring.size());

    for (const auto& point : linestring)
    {
        result.push_back(scale(point, xfact, yfact, origin));
    }

    return result;
}

/*! @brief Scale a polygon by factors */
template <typename Polygon>
typename std::enable_if<detail::is_polygon_like<Polygon>::value, Polygon>::type
scale(const Polygon& polygon, typename Polygon::coord_type xfact, typename Polygon::coord_type yfact,
      const typename Polygon::value_type::value_type& origin = typename Polygon::value_type::value_type{0, 0})
{
    Polygon result;
    result.reserve(polygon.size());

    for (const auto& ring : polygon)
    {
        result.push_back(scale(ring, xfact, yfact, origin));
    }

    return result;
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo
