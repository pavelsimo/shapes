/*
         __
   _____/ /_  ____ _____  ___  _____
  / ___/ __ \/ __ `/ __ \/ _ \/ ___/
 (__  ) / / / /_/ / /_/ /  __(__  )
/____/_/ /_/\__,_/ .___/\___/____/
                /_/

MIT License

Copyright (c) 2019 Pavel Simo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef SIMO_SHAPES_HPP
#define SIMO_SHAPES_HPP

#include <ciso646>
#include <algorithm>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <tuple>

// #include <simo/shapes_fwd.hpp>


#include <type_traits>

namespace simo
{
namespace shapes
{

//class Point;

//class MultiPoint;

//class Polygon;
//
//class MultiPolygon;

//class LineString;

//class MultiLineString;

class Bounds;

}  // namespace shapes
}  // namespace simo

// #include <simo/geom/geometry.hpp>


#include <algorithm>
#include <ciso646>
#include <cctype>
#include <sstream>
// #include <simo/geom/detail/geometry.hpp>


#include <ciso646>
#include <cstdint>
#include <vector>
#include <memory>
// #include <simo/shapes_fwd.hpp>

// #include <simo/geom/detail/bounds.hpp>


#include <ciso646>
#include <algorithm>
#include <limits>
#include <tuple>

namespace simo
{
namespace shapes
{

/*!
 * @brief Represents an axis-aligned bounding box
 * @ingroup geometry
 *
 * @since 0.0.1
 */
struct bounds_t
{
    /// the minimum x-coordinate
    double minx;

    /// the minimum y-coordinate
    double miny;

    /// the maximum x-coordinate
    double maxx;

    /// the maximum y-coordinate
    double maxy;

    /*!
         * @brief Creates a bounds object
         *
         * @since 0.0.1
         */
    bounds_t()
        : minx(std::numeric_limits<double>::max()),
          miny(std::numeric_limits<double>::max()),
          maxx(std::numeric_limits<double>::min()),
          maxy(std::numeric_limits<double>::min())
    {
    }

    /*!
     * @brief Creates a bounds object from the given coordinates
     *
     * @param minx the x-coordinate of the first corner
     * @param miny the y-coordinate of the first corner
     * @param maxx the x-coordinate of the second corner
     * @param maxy the y-coordinate of the second corner
     *
     * @since 0.0.1
     */
    bounds_t(double minx, double miny, double maxx, double maxy)
        : minx(minx), miny(miny), maxx(maxx), maxy(maxy)
    {
    }

    /*!
     * @brief Extends the bounds to contain the given point
     *
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return the bounds object
     *
     * @since 0.0.1
     */
    bounds_t& extend(double x, double y)
    {
        minx = std::min(x, minx);
        maxx = std::max(x, maxx);
        miny = std::min(y, miny);
        maxy = std::max(y, maxy);
        return *this;
    }

    /*!
     * @brief Extends the bounds to contain the given bounds
     *
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return the bounds object
     *
     * @since 0.0.1
     */
    bounds_t& extend(const bounds_t& b)
    {
        minx = std::min(b.minx, minx);
        maxx = std::max(b.maxx, maxx);
        miny = std::min(b.miny, miny);
        maxy = std::max(b.maxy, maxy);
        return *this;
    }

    /*!
     * @return a (x, y) tuple with the center of the bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> center() const
    {
        return std::make_tuple((minx + maxx) / 2.0, (miny + maxy) / 2.0);
    }

    /*!
     * @return a (x, y) tuple with the bottom left bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> bottom_left() const
    {
        return std::make_tuple(minx, maxy);
    }

    /*!
     * @return a (x, y) tuple with the top right bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> top_right() const
    {
        return std::make_tuple(maxx, miny);
    }

    /*!
     * @return a (x, y) tuple with the top left bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> top_left() const
    {
        return std::make_tuple(minx, miny);
    }

    /*!
     * @return a (x, y) tuple with the bottom right bounds
     *
     * @since 0.0.1
     */
    std::tuple<double, double> bottom_right() const
    {
        return std::make_tuple(maxx, maxy);
    }

    /*!
     * @param x the x-coordinate of the point
     * @param y the y-coordinate of the point
     * @return true if the bounds contains the given point, otherwise false
     *
     * @since 0.0.1
     */
    bool contains(double x, double y) const
    {
        return (x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy);
    }

    /*!
     * @param other the bounds
     * @return true if the bounds contain the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool contains(const bounds_t& other)
    {
        return contains(other.minx, other.miny) && contains(other.maxx, other.maxy);
    }

    /*!
     * @param other the bounds
     * @return true if the bounds intersect the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool intersects(const bounds_t& other)
    {
        return (other.maxx >= minx) && (other.minx <= maxx) && (other.maxy >= miny) && (other.miny <= maxy);
    }

    /*!
     * @param other the bounds
     * @return true if the bounds overlaps the given one, otherwise false
     *
     * @since 0.0.1
     */
    bool overlaps(const bounds_t& other)
    {
        return (other.maxx > minx) && (other.minx < maxx) && (other.maxy > miny) && (other.miny < maxy);
    }
};

}  // namespace shapes
}  // namespace simo

// #include <simo/geom/detail/types.hpp>


namespace simo
{
namespace shapes
{

/*!
 * @brief Geometry dimension type is (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
 *
 * @since 0.0.1
 */
enum class dimension_type : uint8_t
{
    XY   = 1,
    XYZ  = 2,
    XYM  = 3,
    XYZM = 4
};

/*!
 * @brief Element type for the geometry
 *
 * @since 0.0.1
 */
enum class element_type : uint8_t
{
    POINT      = 1,
    LINESTRING = 2,
    POLYGON    = 3
};

/*!
 * @brief Geometry types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
 *
 * @since 0.0.1
 */
enum class geometry_type : uint16_t
{
    GEOMETRY             = 0,
    POINT                = 1,
    LINESTRING           = 2,
    POLYGON              = 3,
    MULTIPOINT           = 4,
    MULTILINESTRING      = 5,
    MULTIPOLYGON         = 6,
    GEOMETRYCOLLECTION   = 7,
    CIRCULARSTRING       = 8,
    COMPOUNDCURVE        = 9,
    CURVEPOLYGON         = 10,
    MULTICURVE           = 11,
    MULTISURFACE         = 12,
    CURVE                = 13,
    SURFACE              = 14,
    POLYHEDRALSURFACE    = 15,
    TIN                  = 16,
    GEOMETRYZ            = 1000,
    POINTZ               = 1001,
    LINESTRINGZ          = 1002,
    POLYGONZ             = 1003,
    MULTIPOINTZ          = 1004,
    MULTILINESTRINGZ     = 1005,
    MULTIPOLYGONZ        = 1006,
    GEOMETRYCOLLECTIONZ  = 1007,
    CIRCULARSTRINGZ      = 1008,
    COMPOUNDCURVEZ       = 1009,
    CURVEPOLYGONZ        = 1010,
    MULTICURVEZ          = 1011,
    MULTISURFACEZ        = 1012,
    CURVEZ               = 1013,
    SURFACEZ             = 1014,
    POLYHEDRALSURFACEZ   = 1015,
    TINZ                 = 1016,
    GEOMETRYM            = 2000,
    POINTM               = 2001,
    LINESTRINGM          = 2002,
    POLYGONM             = 2003,
    MULTIPOINTM          = 2004,
    MULTILINESTRINGM     = 2005,
    MULTIPOLYGONM        = 2006,
    GEOMETRYCOLLECTIONM  = 2007,
    CIRCULARSTRINGM      = 2008,
    COMPOUNDCURVEM       = 2009,
    CURVEPOLYGONM        = 2010,
    MULTICURVEM          = 2011,
    MULTISURFACEM        = 2012,
    CURVEM               = 2013,
    SURFACEM             = 2014,
    POLYHEDRALSURFACEM   = 2015,
    TINM                 = 2016,
    GEOMETRYZM           = 3000,
    POINTZM              = 3001,
    LINESTRINGZM         = 3002,
    POLYGONZM            = 3003,
    MULTIPOINTZM         = 3004,
    MULTILINESTRINGZM    = 3005,
    MULTIPOLYGONZM       = 3006,
    GEOMETRYCOLLECTIONZM = 3007,
    CIRCULARSTRINGZM     = 3008,
    COMPOUNDCURVEZM      = 3009,
    CURVEPOLYGONZM       = 3010,
    MULTICURVEZM         = 3011,
    MULTISURFACEZM       = 3012,
    CURVEZM              = 3013,
    SURFACEZM            = 3014,
    POLYHEDRALSURFACEZM  = 3015,
    TINZM                = 3016
};

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/detail/utils.hpp>


#include <ciso646>
// #include <simo/geom/detail/types.hpp>


namespace simo
{
namespace shapes
{
namespace utils
{

/*!
 * @brief Returns the dimension type given a geometry type
 *
 * @param geom_type the geometry type
 * @return the dimension type
 *
 * @since 0.0.1
 */
dimension_type get_dim(geometry_type geom_type) noexcept
{
    int value = static_cast<int>(geom_type);
    if (value >= 1000 and value < 2000)
    {
        return dimension_type::XYZ;
    }
    if (value >= 2000 and value < 3000)
    {
        return dimension_type::XYM;
    }
    if (value >= 3000)
    {
        return dimension_type::XYZM;
    }
    return dimension_type::XY;
}

/*!
 * @brief Returns the dimension type given the number of dimensions
 *
 * @param ndim the number of dimensions
 * @return the dimension type
 *
 * @since 0.0.1
 */
dimension_type get_dim(int8_t ndim) noexcept
{
    switch (ndim)
    {
        case 3:
            return dimension_type::XYZ;
        case 4:
            return dimension_type::XYZM;
        default:
            return dimension_type::XY;
    }
}

/*!
 * @brief Returns the number of dimensions given a dimension type
 *
 * @param dim_type the dimension type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(dimension_type dim_type) noexcept
{
    switch (dim_type)
    {
        case dimension_type::XYZM:
            return 4;
        case dimension_type::XYZ:
        case dimension_type::XYM:
            return 3;
        default:
            return 2;
    }
}

/*!
 * @brief Returns the number of dimensions given a geometry type
 *
 * @param geom_type the geometry type
 * @return the number of dimensions
 *
 * @since 0.0.1
 */
int8_t get_ndim(geometry_type geom_type) noexcept
{
    return get_ndim(get_dim(geom_type));
}

/*!
 * @brief Returns a geometry type given the geometry type
 *
 * @param geom_type the geometry type
 * @return a geometry type
 *
 * @since 0.0.1
 */
geometry_type get_geom_type(geometry_type geom_type) noexcept
{
    switch (geom_type)
    {
        case geometry_type::POINT:
        case geometry_type::POINTZ:
        case geometry_type::POINTM:
        case geometry_type::POINTZM:
            return geometry_type::POINT;
        case geometry_type::MULTIPOINT:
        case geometry_type::MULTIPOINTZ:
        case geometry_type::MULTIPOINTM:
        case geometry_type::MULTIPOINTZM:
            return geometry_type::MULTIPOINT;
        case geometry_type::LINESTRING:
        case geometry_type::LINESTRINGZ:
        case geometry_type::LINESTRINGM:
        case geometry_type::LINESTRINGZM:
            return geometry_type::LINESTRING;
        case geometry_type::MULTILINESTRING:
        case geometry_type::MULTILINESTRINGZ:
        case geometry_type::MULTILINESTRINGM:
        case geometry_type::MULTILINESTRINGZM:
            return geometry_type::MULTILINESTRING;
        case geometry_type::POLYGON:
        case geometry_type::POLYGONZ:
        case geometry_type::POLYGONM:
        case geometry_type::POLYGONZM:
            return geometry_type::POLYGON;
        case geometry_type::MULTIPOLYGON:
        case geometry_type::MULTIPOLYGONZ:
        case geometry_type::MULTIPOLYGONM:
        case geometry_type::MULTIPOLYGONZM:
            return geometry_type::MULTIPOLYGON;
        case geometry_type::GEOMETRYCOLLECTION:
        case geometry_type::GEOMETRYCOLLECTIONZ:
        case geometry_type::GEOMETRYCOLLECTIONM:
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return geometry_type::GEOMETRYCOLLECTION;
        case geometry_type::CIRCULARSTRING:
        case geometry_type::CIRCULARSTRINGZ:
        case geometry_type::CIRCULARSTRINGM:
        case geometry_type::CIRCULARSTRINGZM:
            return geometry_type::CIRCULARSTRING;
        case geometry_type::COMPOUNDCURVE:
        case geometry_type::COMPOUNDCURVEZ:
        case geometry_type::COMPOUNDCURVEM:
        case geometry_type::COMPOUNDCURVEZM:
            return geometry_type::COMPOUNDCURVE;
        case geometry_type::CURVEPOLYGON:
        case geometry_type::CURVEPOLYGONZ:
        case geometry_type::CURVEPOLYGONM:
        case geometry_type::CURVEPOLYGONZM:
            return geometry_type::CURVEPOLYGON;
        case geometry_type::MULTICURVE:
        case geometry_type::MULTICURVEZ:
        case geometry_type::MULTICURVEM:
        case geometry_type::MULTICURVEZM:
            return geometry_type::MULTICURVE;
        case geometry_type::MULTISURFACE:
        case geometry_type::MULTISURFACEZ:
        case geometry_type::MULTISURFACEM:
        case geometry_type::MULTISURFACEZM:
            return geometry_type::MULTISURFACE;
        case geometry_type::CURVE:
        case geometry_type::CURVEZ:
        case geometry_type::CURVEM:
        case geometry_type::CURVEZM:
            return geometry_type::CURVE;
        case geometry_type::SURFACE:
        case geometry_type::SURFACEZ:
        case geometry_type::SURFACEM:
        case geometry_type::SURFACEZM:
            return geometry_type::SURFACE;
        case geometry_type::POLYHEDRALSURFACE:
        case geometry_type::POLYHEDRALSURFACEZ:
        case geometry_type::POLYHEDRALSURFACEM:
        case geometry_type::POLYHEDRALSURFACEZM:
            return geometry_type::POLYHEDRALSURFACE;
        case geometry_type::TIN:
        case geometry_type::TINZ:
        case geometry_type::TINM:
        case geometry_type::TINZM:
            return geometry_type::TIN;
        default:
            return geometry_type::GEOMETRY;
    }
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a Point, otherwise false
 *
 * @since 0.0.1
 */
bool is_point(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::POINT or geom_type == geometry_type::POINTZ or geom_type == geometry_type::POINTM or geom_type == geometry_type::POINTZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a MultiPoint, otherwise false
 *
 * @since 0.0.1
 */
bool is_multipoint(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::MULTIPOINT or geom_type == geometry_type::MULTIPOINTZ or geom_type == geometry_type::MULTIPOINTM or geom_type == geometry_type::MULTIPOINTZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a LineString, otherwise false
 *
 * @since 0.0.1
 */
bool is_linestring(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::LINESTRING or geom_type == geometry_type::LINESTRINGZ or geom_type == geometry_type::LINESTRINGM or geom_type == geometry_type::LINESTRINGZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a MultiLineString, otherwise false
 *
 * @since 0.0.1
 */
bool is_multilinestring(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::MULTILINESTRING or geom_type == geometry_type::MULTILINESTRINGZ or geom_type == geometry_type::MULTILINESTRINGM or geom_type == geometry_type::MULTILINESTRINGZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a Polygon, otherwise false
 *
 * @since 0.0.1
 */
bool is_polygon(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::POLYGON or geom_type == geometry_type::POLYGONZ or geom_type == geometry_type::POLYGONM or geom_type == geometry_type::POLYGONZM;
}

/*!
 * @param geom_type the geometry type
 * @return true if the geometry type is a MultiPolygon, otherwise false
 *
 * @since 0.0.1
 */
bool is_multipolygon(geometry_type geom_type) noexcept
{
    return geom_type == geometry_type::MULTIPOLYGON or geom_type == geometry_type::MULTIPOLYGONZ or geom_type == geometry_type::MULTIPOLYGONM or geom_type == geometry_type::MULTIPOLYGONZM;
}

}  // namespace utils
}  // namespace shapes
}  // namespace simo
// #include <simo/exceptions.hpp>


#include <ciso646>
#include <string>
#include <exception>

namespace simo
{
namespace shapes
{
namespace exceptions
{

/*!
 * @brief Base shapes exception
 *
 * @since 0.0.1
 */
class shapes_exception : public std::exception
{
  public:
    /*!
     * @brief Creates a shapes exception
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit shapes_exception(const char* reason)
        : m_reason(reason) {}

    /*!
     * @brief Returns the exception reason
     *
     * @return a string with the exception reason
     *
     * @since 0.0.1
     */
    const char* what() const noexcept override
    {
        return m_reason.c_str();
    }

  protected:
    /*!
     * @brief Set the exception reason
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    void set_reason(const std::string& reason)
    {
        m_reason.append(": ");
        m_reason.append(reason);
    }

  private:
    std::string m_reason{};
};

/*!
 * @brief Exception thrown when an error has been found while parsing
 *
 * @since 0.0.1
 */
class parse_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a parse error with the given reason
     *
     * @param reason the reason message
     *
     * @since 0.0.1
     */
    explicit parse_error(const std::string& reason)
        : shapes_exception("parse error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief Exception thrown when method or routine is not implemented
 *
 * @since 0.0.1
 */
class not_implemented_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a not implemented error exception
     *
     * @since 0.0.1
     */
    not_implemented_error()
        : shapes_exception("not implemented error")
    {
    }

    /*!
     * @brief Creates a not implemented error exception
     *
     * @param reason the reason message
     *
     * @since 0.0.1
     */
    explicit not_implemented_error(const std::string& reason)
        : shapes_exception("not implemented error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief Exception thrown when a geometry error is found
 *
 * @since 0.0.1
 */
class geometry_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a geometry error exception
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit geometry_error(const std::string& reason)
        : shapes_exception("geometry error")
    {
        set_reason(reason);
    }
};

/*!
 * @brief Exception thrown when a sequence index is out of range
 *
 * @since 0.0.1
 */
class index_error : public shapes_exception
{
  public:
    /*!
     * @brief Creates a index error exception
     *
     * @param reason the exception reason
     *
     * @since 0.0.1
     */
    explicit index_error(const std::string& reason)
        : shapes_exception("index error")
    {
        set_reason(reason);
    }
};

}  // namespace exceptions
}  // namespace shapes
}  // namespace simo


// Include algorithm headers for the convenience methods in basic_geometry
// #include <simo/algorithm/measurements.hpp>


#include <ciso646>
#include <cmath>
#include <type_traits>

namespace simo
{
namespace shapes
{
namespace algorithm
{

/*!
 * @brief Calculate the Euclidean distance between two points
 *
 * @param p1 First point
 * @param p2 Second point
 * @return Distance between points
 */
template <typename Point>
auto distance(const Point& p1, const Point& p2) -> decltype(p1.x)
{
    auto dx = p2.x - p1.x;
    auto dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

/*!
 * @brief Calculate the length of a linestring
 *
 * Sums the Euclidean distances between consecutive points.
 *
 * @param linestring The linestring geometry
 * @return Total length
 */
template <typename LineString>
auto length(const LineString& linestring) -> typename LineString::coord_type
{
    if (linestring.size() < 2)
    {
        return 0.0;
    }

    typename LineString::coord_type total = 0.0;

    for (size_t i = 0; i < linestring.size() - 1; ++i)
    {
        total += distance(linestring[i], linestring[i + 1]);
    }

    return total;
}

/*!
 * @brief Calculate the signed area of a ring using the Shoelace formula
 *
 * Uses the Shoelace (Gauss's area) formula:
 * A = 0.5 * |Σ(x_i * y_{i+1} - x_{i+1} * y_i)|
 *
 * @param ring The ring (polygon boundary)
 * @return Signed area (positive for counter-clockwise, negative for clockwise)
 */
template <typename Ring>
auto signed_area_ring(const Ring& ring) -> typename Ring::coord_type
{
    if (ring.size() < 3)
    {
        return 0.0;
    }

    typename Ring::coord_type area = 0.0;

    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        area += ring[i].x * ring[i + 1].y - ring[i + 1].x * ring[i].y;
    }

    return area / 2.0;
}

/*!
 * @brief Calculate the area of a polygon
 *
 * Computes area of exterior ring minus areas of holes.
 *
 * @param polygon The polygon geometry
 * @return Area of polygon
 */
template <typename Polygon>
auto area(const Polygon& polygon) -> typename Polygon::coord_type
{
    if (polygon.empty())
    {
        return 0.0;
    }

    // Area of exterior ring (first ring)
    typename Polygon::coord_type total_area = std::abs(signed_area_ring(polygon[0]));

    // Subtract areas of holes (remaining rings)
    for (size_t i = 1; i < polygon.size(); ++i)
    {
        total_area -= std::abs(signed_area_ring(polygon[i]));
    }

    return total_area;
}

/*!
 * @brief Calculate the perimeter of a polygon
 *
 * Sums the lengths of the exterior ring.
 *
 * @param polygon The polygon geometry
 * @return Perimeter length
 */
template <typename Polygon>
auto perimeter(const Polygon& polygon) -> typename Polygon::coord_type
{
    if (polygon.empty())
    {
        return 0.0;
    }

    return length(polygon[0]);  // Exterior ring
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo

// #include <simo/algorithm/predicates.hpp>


#include <ciso646>
// #include <simo/algorithm/detail/orient2d.hpp>


#include <ciso646>

namespace simo
{
namespace shapes
{
namespace algorithm
{
namespace detail
{

/*!
 * @brief Robust 2D orientation test
 *
 * Computes the orientation of three points p, q, r in 2D space.
 * Based on the sign of the determinant:
 *   | px py 1 |
 *   | qx qy 1 |
 *   | rx ry 1 |
 *
 * @param p First point
 * @param q Second point
 * @param r Third point
 * @return > 0 if counter-clockwise, < 0 if clockwise, == 0 if collinear
 *
 * @note Uses exact arithmetic via cross product for robustness
 */
template <typename Point>
constexpr int orient2d(const Point& p, const Point& q, const Point& r) noexcept
{
    // Compute the cross product: (q - p) × (r - p)
    // = (q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y)
    auto det = (q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y);

    // Return the sign
    if (det > 0) return 1;   // Counter-clockwise
    if (det < 0) return -1;  // Clockwise
    return 0;                 // Collinear
}

/*!
 * @brief Check if point r is on the segment pq (assuming collinearity)
 *
 * @param p First endpoint
 * @param q Second endpoint
 * @param r Point to test
 * @return true if r is on segment pq, false otherwise
 */
template <typename Point>
constexpr bool on_segment(const Point& p, const Point& q, const Point& r) noexcept
{
    return r.x <= std::max(p.x, q.x) && r.x >= std::min(p.x, q.x) &&
           r.y <= std::max(p.y, q.y) && r.y >= std::min(p.y, q.y);
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo

// #include <simo/algorithm/detail/segment_intersection.hpp>


#include <ciso646>
// #include <simo/algorithm/detail/orient2d.hpp>


namespace simo
{
namespace shapes
{
namespace algorithm
{
namespace detail
{

/*!
 * @brief Test if two line segments intersect
 *
 * Tests whether segment p1q1 and segment p2q2 intersect.
 * Uses orientation tests for robustness.
 *
 * @param p1 First endpoint of first segment
 * @param q1 Second endpoint of first segment
 * @param p2 First endpoint of second segment
 * @param q2 Second endpoint of second segment
 * @return true if segments intersect, false otherwise
 */
template <typename Point>
constexpr bool segments_intersect(const Point& p1, const Point& q1,
                                   const Point& p2, const Point& q2) noexcept
{
    int o1 = orient2d(p1, q1, p2);
    int o2 = orient2d(p1, q1, q2);
    int o3 = orient2d(p2, q2, p1);
    int o4 = orient2d(p2, q2, q1);

    // General case: segments intersect if endpoints are on opposite sides
    if (o1 != o2 && o3 != o4)
    {
        return true;
    }

    // Special cases: collinear points
    // p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, q1, p2))
    {
        return true;
    }

    // q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q1, q2))
    {
        return true;
    }

    // p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, q2, p1))
    {
        return true;
    }

    // q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q2, q1))
    {
        return true;
    }

    return false;
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo

// #include <simo/algorithm/detail/point_in_polygon.hpp>


#include <ciso646>
// #include <simo/algorithm/detail/orient2d.hpp>


namespace simo
{
namespace shapes
{
namespace algorithm
{
namespace detail
{

/*!
 * @brief Test if a point is inside a polygon using winding number algorithm
 *
 * The winding number counts the number of times the polygon winds around the point.
 * A non-zero winding number means the point is inside.
 *
 * @param point The point to test
 * @param ring The polygon ring (should be closed: first point == last point)
 * @return Winding number (0 = outside, non-zero = inside)
 */
template <typename Point, typename Ring>
int winding_number(const Point& point, const Ring& ring)
{
    int wn = 0;  // Winding number counter

    // Loop through all edges of the polygon
    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        const auto& v1 = ring[i];
        const auto& v2 = ring[i + 1];

        if (v1.y <= point.y)
        {
            // Upward crossing
            if (v2.y > point.y)
            {
                if (orient2d(v1, v2, point) > 0)
                {
                    ++wn;  // Point is left of edge
                }
            }
        }
        else
        {
            // Downward crossing
            if (v2.y <= point.y)
            {
                if (orient2d(v1, v2, point) < 0)
                {
                    --wn;  // Point is right of edge
                }
            }
        }
    }

    return wn;
}

/*!
 * @brief Test if a point is on the boundary of a polygon
 *
 * @param point The point to test
 * @param ring The polygon ring
 * @param tolerance Distance tolerance for boundary test
 * @return true if point is on the boundary
 */
template <typename Point, typename Ring>
bool point_on_boundary(const Point& point, const Ring& ring, double tolerance = 1e-10)
{
    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        const auto& v1 = ring[i];
        const auto& v2 = ring[i + 1];

        // Check if collinear
        if (orient2d(v1, v2, point) == 0)
        {
            // Check if on segment
            if (on_segment(v1, v2, point))
            {
                return true;
            }
        }

        // Alternative: distance to line segment check
        // (Can add more sophisticated distance calculation if needed)
    }

    return false;
}

}  // namespace detail
}  // namespace algorithm
}  // namespace shapes
}  // namespace simo


namespace simo
{
namespace shapes
{
namespace algorithm
{

// Forward declarations for different geometry type combinations

//
// CONTAINS
//

/*! @brief Test if a polygon contains a point */
template <typename Polygon, typename Point>
bool contains(const Polygon& polygon, const Point& point)
{
    if (polygon.empty())
    {
        return false;
    }

    // Check if point is inside exterior ring
    int wn = detail::winding_number(point, polygon[0]);
    if (wn == 0)
    {
        return false;  // Outside exterior ring
    }

    // Check if point is inside any hole (should NOT be)
    for (size_t i = 1; i < polygon.size(); ++i)
    {
        int wn_hole = detail::winding_number(point, polygon[i]);
        if (wn_hole != 0)
        {
            return false;  // Inside a hole
        }
    }

    return true;
}

//
// INTERSECTS
//

/*! @brief Test if two bounding boxes intersect */
template <typename Bounds1, typename Bounds2>
bool bounds_intersect(const Bounds1& b1, const Bounds2& b2)
{
    return !(b1.maxx < b2.minx || b2.maxx < b1.minx ||
             b1.maxy < b2.miny || b2.maxy < b1.miny);
}

/*! @brief Test if two line segments intersect */
template <typename LineString1, typename LineString2>
bool intersects(const LineString1& ls1, const LineString2& ls2)
{
    // Quick rejection test using bounding boxes
    auto b1 = ls1.bounds();
    auto b2 = ls2.bounds();
    if (!bounds_intersect(b1, b2))
    {
        return false;
    }

    // Test all segment pairs
    for (size_t i = 0; i < ls1.size() - 1; ++i)
    {
        for (size_t j = 0; j < ls2.size() - 1; ++j)
        {
            if (detail::segments_intersect(ls1[i], ls1[i + 1], ls2[j], ls2[j + 1]))
            {
                return true;
            }
        }
    }

    return false;
}

//
// WITHIN
//

/*! @brief Test if point is within polygon (inverse of contains) */
template <typename Point, typename Polygon>
bool within(const Point& point, const Polygon& polygon)
{
    return contains(polygon, point);
}

//
// TOUCHES
//

/*! @brief Test if point touches polygon boundary */
template <typename Point, typename Polygon>
bool touches(const Point& point, const Polygon& polygon)
{
    if (polygon.empty())
    {
        return false;
    }

    // Check exterior ring
    if (detail::point_on_boundary(point, polygon[0]))
    {
        return true;
    }

    // Check holes
    for (size_t i = 1; i < polygon.size(); ++i)
    {
        if (detail::point_on_boundary(point, polygon[i]))
        {
            return true;
        }
    }

    return false;
}

//
// DISJOINT
//

/*! @brief Test if two geometries are disjoint (no intersection) */
template <typename Geom1, typename Geom2>
bool disjoint(const Geom1& g1, const Geom2& g2)
{
    return !intersects(g1, g2);
}

//
// CROSSES
//

/*! @brief Test if linestring crosses polygon boundary */
template <typename LineString, typename Polygon>
bool crosses(const LineString& ls, const Polygon& polygon)
{
    if (polygon.empty() || ls.size() < 2)
    {
        return false;
    }

    const auto& exterior = polygon[0];
    if (exterior.size() < 4)  // Need at least 3 unique points + closing point
    {
        return false;
    }

    bool has_interior = false;
    bool has_exterior = false;

    // Check vertices first
    for (const auto& point : ls)
    {
        if (contains(polygon, point))
        {
            has_interior = true;
        }
        else
        {
            has_exterior = true;
        }

        if (has_interior && has_exterior)
        {
            return true;
        }
    }

    // Check if linestring segments intersect polygon boundary
    // If they do, the linestring crosses the polygon
    for (std::size_t i = 0; i + 1 < ls.size(); ++i)
    {
        const auto& p1 = ls[i];
        const auto& p2 = ls[i + 1];

        for (std::size_t j = 0; j + 1 < exterior.size(); ++j)
        {
            const auto& q1 = exterior[j];
            const auto& q2 = exterior[j + 1];

            if (detail::segments_intersect(p1, p2, q1, q2))
            {
                // Found intersection with boundary
                // Check if segment midpoint is inside polygon
                typename LineString::value_type midpoint;
                midpoint.x = (p1.x + p2.x) / 2;
                midpoint.y = (p1.y + p2.y) / 2;

                if (contains(polygon, midpoint))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

//
// OVERLAPS
//

/*! @brief Test if two geometries overlap (share some but not all interior points) */
template <typename Geom1, typename Geom2>
bool overlaps(const Geom1& g1, const Geom2& g2)
{
    // Quick rejection: check bounding boxes
    auto b1 = g1.bounds();
    auto b2 = g2.bounds();
    return bounds_intersect(b1, b2);
    // Note: Full overlap test requires more complex logic
    // This is a simplified implementation
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo

// #include <simo/algorithm/operations.hpp>


#include <ciso646>
#include <algorithm>
#include <vector>
#include <cmath>
// #include <simo/algorithm/detail/orient2d.hpp>

// #include <simo/algorithm/measurements.hpp>


namespace simo
{
namespace shapes
{
namespace algorithm
{

//
// CONVEX HULL (Graham Scan Algorithm)
//

/*! @brief Compute convex hull using Graham scan */
template <typename MultiPoint, typename Polygon>
Polygon convex_hull(const MultiPoint& points)
{
    if (points.size() < 3)
    {
        Polygon result;
        if (!points.empty())
        {
            typename Polygon::value_type ring;
            for (const auto& p : points)
            {
                ring.push_back(p);
            }
            if (!ring.empty())
            {
                ring.push_back(ring.front());  // Close the ring
            }
            result.push_back(ring);
        }
        return result;
    }

    // Find the lowest point (and leftmost if tie)
    using Point = typename MultiPoint::value_type;
    std::vector<Point> pts(points.begin(), points.end());

    auto lowest = std::min_element(pts.begin(), pts.end(),
                                     [](const Point& a, const Point& b) {
                                         return a.y < b.y || (a.y == b.y && a.x < b.x);
                                     });

    Point pivot = *lowest;

    // Sort points by polar angle with respect to pivot
    std::sort(pts.begin(), pts.end(),
              [&pivot](const Point& a, const Point& b) {
                  if (a.x == pivot.x && a.y == pivot.y) return true;
                  if (b.x == pivot.x && b.y == pivot.y) return false;

                  int o = detail::orient2d(pivot, a, b);
                  if (o == 0)
                  {
                      // Collinear: closer point comes first
                      return distance(pivot, a) < distance(pivot, b);
                  }
                  return o > 0;  // Counter-clockwise comes first
              });

    // Graham scan
    std::vector<Point> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);

    for (size_t i = 2; i < pts.size(); ++i)
    {
        // Remove points that make clockwise turn
        while (hull.size() > 1)
        {
            size_t n = hull.size();
            int o = detail::orient2d(hull[n - 2], hull[n - 1], pts[i]);
            if (o >= 0)  // Counter-clockwise or collinear
            {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }

    // Close the ring
    hull.push_back(hull.front());

    // Create polygon
    Polygon result;
    typename Polygon::value_type ring(hull.begin(), hull.end());
    result.push_back(ring);

    return result;
}

//
// SIMPLIFY (Douglas-Peucker Algorithm)
//

namespace detail
{

/*! @brief Perpendicular distance from point to line segment */
template <typename Point>
auto perpendicular_distance(const Point& point, const Point& line_start, const Point& line_end)
    -> decltype(point.x)
{
    auto dx = line_end.x - line_start.x;
    auto dy = line_end.y - line_start.y;

    auto mag = dx * dx + dy * dy;
    if (mag == 0)
    {
        return distance(point, line_start);
    }

    auto u = ((point.x - line_start.x) * dx + (point.y - line_start.y) * dy) / mag;

    if (u < 0)
    {
        return distance(point, line_start);
    }
    else if (u > 1)
    {
        return distance(point, line_end);
    }
    else
    {
        Point closest{line_start.x + u * dx, line_start.y + u * dy};
        return distance(point, closest);
    }
}

/*! @brief Recursive Douglas-Peucker simplification */
template <typename Point>
void douglas_peucker_recursive(const std::vector<Point>& points, size_t start, size_t end,
                                 double tolerance, std::vector<bool>& keep)
{
    if (end - start < 2)
    {
        return;
    }

    // Special case: tolerance of 0 means keep all points
    if (tolerance == 0)
    {
        for (size_t i = start + 1; i < end; ++i)
        {
            keep[i] = true;
        }
        return;
    }

    double max_dist = 0;
    size_t max_index = start;

    // Find point with maximum distance from line segment
    for (size_t i = start + 1; i < end; ++i)
    {
        double dist = perpendicular_distance(points[i], points[start], points[end]);
        if (dist > max_dist)
        {
            max_dist = dist;
            max_index = i;
        }
    }

    // If max distance is greater than tolerance, recursively simplify
    if (max_dist > tolerance)
    {
        keep[max_index] = true;
        douglas_peucker_recursive(points, start, max_index, tolerance, keep);
        douglas_peucker_recursive(points, max_index, end, tolerance, keep);
    }
}

}  // namespace detail

/*! @brief Simplify linestring using Douglas-Peucker algorithm */
template <typename LineString>
LineString simplify(const LineString& linestring, double tolerance)
{
    if (linestring.size() < 3)
    {
        return linestring;
    }

    using Point = typename LineString::value_type;
    std::vector<Point> points(linestring.begin(), linestring.end());

    // Mark which points to keep
    std::vector<bool> keep(points.size(), false);
    keep.front() = true;
    keep.back() = true;

    // Run Douglas-Peucker
    detail::douglas_peucker_recursive(points, 0, points.size() - 1, tolerance, keep);

    // Build simplified linestring
    LineString result;
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (keep[i])
        {
            result.push_back(points[i]);
        }
    }

    return result;
}

//
// ENVELOPE (Bounding Box)
//

/*! @brief Create polygon representing the envelope (bounding box) of a geometry */
template <typename Geom, typename Polygon>
Polygon envelope(const Geom& geom)
{
    auto bounds = geom.bounds();

    using Point = typename Polygon::value_type::value_type;
    typename Polygon::value_type ring;

    ring.push_back(Point{bounds.minx, bounds.miny});
    ring.push_back(Point{bounds.maxx, bounds.miny});
    ring.push_back(Point{bounds.maxx, bounds.maxy});
    ring.push_back(Point{bounds.minx, bounds.maxy});
    ring.push_back(Point{bounds.minx, bounds.miny});  // Close the ring

    Polygon result;
    result.push_back(ring);

    return result;
}

//
// CENTROID
//

/*! @brief Compute centroid of a polygon */
template <typename Polygon, typename Point>
Point centroid(const Polygon& polygon)
{
    if (polygon.empty() || polygon[0].empty())
    {
        return Point{0, 0};
    }

    const auto& ring = polygon[0];  // Exterior ring
    typename Point::coord_type cx = 0;
    typename Point::coord_type cy = 0;
    typename Point::coord_type signed_area = 0;

    for (size_t i = 0; i < ring.size() - 1; ++i)
    {
        auto x0 = ring[i].x;
        auto y0 = ring[i].y;
        auto x1 = ring[i + 1].x;
        auto y1 = ring[i + 1].y;
        auto a = x0 * y1 - x1 * y0;
        signed_area += a;
        cx += (x0 + x1) * a;
        cy += (y0 + y1) * a;
    }

    signed_area *= 0.5;
    cx /= (6.0 * signed_area);
    cy /= (6.0 * signed_area);

    return Point{cx, cy};
}

}  // namespace algorithm
}  // namespace shapes
}  // namespace simo

// #include <simo/algorithm/transformations.hpp>


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


namespace simo
{
namespace shapes
{

/*!
 * @brief Base class for all geometries
 *
 * @tparam T the geometry type (e.g. Point, Polygon, LineString)
 * @ingroup geometry
 *
 * @since 0.0.1
 */
template <typename T>
class basic_geometry
{
  public:
    /*!
     * @brief Returns the geometry type
     * @return the geometry type
     *
     * @since 0.0.1
     */
    constexpr geometry_type geom_type() const noexcept
    {
        return static_cast<const T*>(this)->geom_type_();
    }

    /*!
     * @brief Returns the geometry type as a string
     * @return the geometry type as a string
     *
     * @since 0.0.1
     */
    std::string tagged_text() const noexcept
    {
        switch (geom_type())
        {
            case geometry_type::POINT:
                return "Point";
            case geometry_type::POINTZ:
                return "Point Z";
            case geometry_type::POINTM:
                return "Point M";
            case geometry_type::POINTZM:
                return "Point ZM";
            case geometry_type::MULTIPOINT:
                return "MultiPoint";
            case geometry_type::MULTIPOINTZ:
                return "MultiPoint Z";
            case geometry_type::MULTIPOINTM:
                return "MultiPoint M";
            case geometry_type::MULTIPOINTZM:
                return "MultiPoint ZM";
            case geometry_type::LINESTRING:
                return "LineString";
            case geometry_type::LINESTRINGZ:
                return "LineString Z";
            case geometry_type::LINESTRINGM:
                return "LineString M";
            case geometry_type::LINESTRINGZM:
                return "LineString ZM";
            case geometry_type::MULTILINESTRING:
                return "MultiLineString";
            case geometry_type::MULTILINESTRINGZ:
                return "MultiLineString Z";
            case geometry_type::MULTILINESTRINGM:
                return "MultiLineString M";
            case geometry_type::MULTILINESTRINGZM:
                return "MultiLineString ZM";
            case geometry_type::POLYGON:
                return "Polygon";
            case geometry_type::POLYGONZ:
                return "Polygon Z";
            case geometry_type::POLYGONM:
                return "Polygon M";
            case geometry_type::POLYGONZM:
                return "Polygon ZM";
            case geometry_type::MULTIPOLYGON:
                return "MultiPolygon";
            case geometry_type::MULTIPOLYGONZ:
                return "MultiPolygon Z";
            case geometry_type::MULTIPOLYGONM:
                return "MultiPolygon M";
            case geometry_type::MULTIPOLYGONZM:
                return "MultiPolygon ZM";
            case geometry_type::GEOMETRYCOLLECTION:
                return "GeometryCollection";
            case geometry_type::GEOMETRYCOLLECTIONZ:
                return "GeometryCollection Z";
            case geometry_type::GEOMETRYCOLLECTIONM:
                return "GeometryCollection M";
            case geometry_type::GEOMETRYCOLLECTIONZM:
                return "GeometryCollection ZM";
            default:
                return "Geometry";
        }
    }

    /*!
     * @brief Returns the dimension type for the geometry
     * @return the dimension type
     *
     * @since 0.0.1
     */
    constexpr dimension_type dim() const noexcept
    {
        int value = static_cast<int>(geom_type());
        if (value >= 1000 and value < 2000)
        {
            return dimension_type::XYZ;
        }
        if (value >= 2000 and value < 3000)
        {
            return dimension_type::XYM;
        }
        if (value >= 3000)
        {
            return dimension_type::XYZM;
        }
        return dimension_type::XY;
    }

    /*!
     * @brief Returns the number of dimensions of the geometry
     * @return the number of dimensions
     * @note the number of dimensions is (x, y) = 2, (x, y, z) = 3, (x, y, m) = 3 and (x, y, z, m) = 4
     *
     * @since 0.0.1
     */
    constexpr size_t ndim() const noexcept
    {
        switch (dim())
        {
            case dimension_type::XYZM:
                return 4;
            case dimension_type::XYZ:
            case dimension_type::XYM:
                return 3;
            default:
                return 2;
        }
    }

    /*!
     * @brief Raise an error if the geometry is invalid
     * @throw geometry_error the geometry error
     *
     * @since 0.0.1
     */
    void throw_for_invalid() const
    {
        return static_cast<const T*>(this)->throw_for_invalid_();
    }

    /*!
     * @brief Whether the geometry is closed
     * @return true if the geometry is closed, otherwise false
     *
     * @since 0.0.1
     */
    bool is_closed() const noexcept
    {
        return static_cast<const T*>(this)->is_closed_();
    }

    /*!
     * @brief Whether the geometry is valid
     * @return true if the geometry is valid, otherwise false
     *
     * @since 0.0.1
     */
    bool is_valid() const noexcept
    {
        try
        {
            throw_for_invalid();
        }
        catch (const exceptions::geometry_error& e)
        {
            return false;
        }
        return true;
    }

    /*!
     * @brief Returns the bounding box of the geometry
     * @return a bounds object
     *
     * @since 0.0.1
     */
    bounds_t bounds() const
    {
        return static_cast<const T*>(this)->bounds_();
    }

    /*!
     * @brief Whether the geometry has the z-coordinate
     * @return true if the geometry has z-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    constexpr bool has_z() const noexcept
    {
        int value = static_cast<int>(geom_type());
        return (value >= 1000 and value < 2000) or value >= 3000;
    }

    /*!
     * @brief Whether the geometry has the m-coordinate (measurement coordinate)
     * @return true if the geometry has m-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    constexpr bool has_m() const noexcept
    {
        int value = static_cast<int>(geom_type());
        return value >= 2000;
    }

    // json

    /*!
     * @brief Creates a geometry from a geojson string
     * @param json the geojson string
     * @return a Geometry object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static T from_json(const std::string& json)
    {
        return T::from_json_(json);
    }

    /*!
     * @brief Dumps the geojson representation of the geometry
     * @param precision the output precision
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json(std::int32_t precision = -1) const
    {
        return static_cast<const T*>(this)->json_(precision);
    }

    // wkt

    /*!
     * @brief Creates a Geometry from a wkt string
     * @param wkt the wkt string
     * @return a Geometry object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static T from_wkt(const std::string& wkt)
    {
        return T::from_wkt_(wkt);
    }

    /*!
     * @brief Dumps the wkt representation of the geometry
     * @param precision the output precision
     * @return a wkt string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string wkt(std::int32_t precision = -1) const
    {
        return static_cast<const T*>(this)->wkt_(precision);
    }

    // Geometric algorithms (forward to algorithm namespace functions)
    // Note: These are provided as convenience methods. Full implementations
    // are in the simo::shapes::algorithm namespace.

    /*!
     * @brief Get length of the geometry (for LineString types)
     * @return Length
     * @since 0.1.0
     */
    template <typename U = T>
    auto length() const -> typename U::coord_type
    {
        return algorithm::length(*static_cast<const T*>(this));
    }

    /*!
     * @brief Get area of the geometry (for Polygon types)
     * @return Area
     * @since 0.1.0
     */
    template <typename U = T>
    auto area() const -> typename U::coord_type
    {
        return algorithm::area(*static_cast<const T*>(this));
    }

    /*!
     * @brief Test if this geometry contains another
     * @param other The other geometry
     * @return true if this contains other
     * @since 0.1.0
     */
    template <typename Other>
    bool contains(const Other& other) const
    {
        return algorithm::contains(*static_cast<const T*>(this), other);
    }

    /*!
     * @brief Test if this geometry intersects another
     * @param other The other geometry
     * @return true if geometries intersect
     * @since 0.1.0
     */
    template <typename Other>
    bool intersects(const Other& other) const
    {
        return algorithm::intersects(*static_cast<const T*>(this), other);
    }

    /*!
     * @brief Test if this geometry is within another
     * @param other The other geometry
     * @return true if this is within other
     * @since 0.1.0
     */
    template <typename Other>
    bool within(const Other& other) const
    {
        return algorithm::within(*static_cast<const T*>(this), other);
    }

    /*!
     * @brief Translate geometry by offset
     * @param xoff X offset
     * @param yoff Y offset
     * @return Translated geometry
     * @since 0.1.0
     */
    template <typename U = T>
    T translate(typename U::coord_type xoff, typename U::coord_type yoff) const
    {
        return algorithm::translate(*static_cast<const T*>(this), xoff, yoff);
    }

    /*!
     * @brief Rotate geometry around origin
     * @param angle Rotation angle in radians
     * @return Rotated geometry
     * @since 0.1.0
     */
    T rotate(double angle) const
    {
        return algorithm::rotate(*static_cast<const T*>(this), angle);
    }

    /*!
     * @brief Scale geometry by factors
     * @param xfact X scale factor
     * @param yfact Y scale factor
     * @return Scaled geometry
     * @since 0.1.0
     */
    template <typename U = T>
    T scale(typename U::coord_type xfact, typename U::coord_type yfact) const
    {
        return algorithm::scale(*static_cast<const T*>(this), xfact, yfact);
    }

    /*!
     * @brief Simplify geometry using Douglas-Peucker algorithm
     * @param tolerance Tolerance for simplification
     * @return Simplified geometry
     * @since 0.1.0
     */
    T simplify(double tolerance) const
    {
        return algorithm::simplify(*static_cast<const T*>(this), tolerance);
    }
};

}  // namespace shapes
}  // namespace simo

// #include <simo/geom/point.hpp>


#include <ciso646>
// #include <simo/geom/detail/point.hpp>


#include <ciso646>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <regex>
// #include <simo/io/geojson_parser.hpp>


#include <ciso646>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <sstream>

namespace simo
{
namespace shapes
{
namespace io
{

// Exception for GeoJSON parsing errors
class geojson_parse_error : public std::runtime_error
{
  public:
    explicit geojson_parse_error(const std::string& msg)
        : std::runtime_error(msg) {}
};

// Forward declaration
class geojson_value;

// Lightweight JSON value representation optimized for GeoJSON
class geojson_value
{
  public:
    enum class type_t
    {
        NULL_TYPE,
        STRING,
        NUMBER,
        ARRAY,
        OBJECT
    };

  private:
    type_t type_;

    // Use pointer-based storage to avoid large union
    std::unique_ptr<std::string> string_val_;
    double number_val_;
    std::unique_ptr<std::vector<geojson_value>> array_val_;
    std::unique_ptr<std::unordered_map<std::string, geojson_value>> object_val_;

  public:
    // Constructors
    geojson_value()
        : type_(type_t::NULL_TYPE), number_val_(0.0) {}

    explicit geojson_value(const std::string& s)
        : type_(type_t::STRING), string_val_(new std::string(s)), number_val_(0.0) {}

    explicit geojson_value(double n)
        : type_(type_t::NUMBER), number_val_(n) {}

    explicit geojson_value(std::vector<geojson_value>&& arr)
        : type_(type_t::ARRAY), number_val_(0.0), array_val_(new std::vector<geojson_value>(std::move(arr))) {}

    explicit geojson_value(std::unordered_map<std::string, geojson_value>&& obj)
        : type_(type_t::OBJECT), number_val_(0.0), object_val_(new std::unordered_map<std::string, geojson_value>(std::move(obj))) {}

    // Move constructor and assignment
    geojson_value(geojson_value&& other) noexcept
        : type_(other.type_),
          string_val_(std::move(other.string_val_)),
          number_val_(other.number_val_),
          array_val_(std::move(other.array_val_)),
          object_val_(std::move(other.object_val_))
    {
        other.type_ = type_t::NULL_TYPE;
    }

    geojson_value& operator=(geojson_value&& other) noexcept
    {
        if (this != &other)
        {
            type_ = other.type_;
            string_val_ = std::move(other.string_val_);
            number_val_ = other.number_val_;
            array_val_ = std::move(other.array_val_);
            object_val_ = std::move(other.object_val_);
            other.type_ = type_t::NULL_TYPE;
        }
        return *this;
    }

    // Delete copy constructor and assignment (move-only for efficiency)
    geojson_value(const geojson_value&) = delete;
    geojson_value& operator=(const geojson_value&) = delete;

    // Type queries
    type_t type() const noexcept { return type_; }
    bool is_null() const noexcept { return type_ == type_t::NULL_TYPE; }
    bool is_string() const noexcept { return type_ == type_t::STRING; }
    bool is_number() const noexcept { return type_ == type_t::NUMBER; }
    bool is_array() const noexcept { return type_ == type_t::ARRAY; }
    bool is_object() const noexcept { return type_ == type_t::OBJECT; }

    // Access methods with bounds checking
    const geojson_value& at(const std::string& key) const
    {
        if (type_ != type_t::OBJECT)
        {
            throw geojson_parse_error("not an object");
        }
        auto it = object_val_->find(key);
        if (it == object_val_->end())
        {
            throw std::out_of_range("key not found: " + key);
        }
        return it->second;
    }

    const geojson_value& operator[](size_t index) const
    {
        if (type_ != type_t::ARRAY)
        {
            throw geojson_parse_error("not an array");
        }
        if (index >= array_val_->size())
        {
            throw std::out_of_range("array index out of range");
        }
        return (*array_val_)[index];
    }

    bool has_key(const std::string& key) const
    {
        if (type_ != type_t::OBJECT)
        {
            return false;
        }
        return object_val_->find(key) != object_val_->end();
    }

    size_t size() const
    {
        if (type_ == type_t::ARRAY)
        {
            return array_val_->size();
        }
        if (type_ == type_t::OBJECT)
        {
            return object_val_->size();
        }
        return 0;
    }

    bool empty() const
    {
        return size() == 0;
    }

    // Type conversions
    std::string as_string() const
    {
        if (type_ != type_t::STRING)
        {
            throw geojson_parse_error("value is not a string");
        }
        return *string_val_;
    }

    double as_number() const
    {
        if (type_ != type_t::NUMBER)
        {
            throw geojson_parse_error("value is not a number");
        }
        return number_val_;
    }

    // Optimized conversion for coordinate arrays (common case in GeoJSON)
    std::vector<double> as_double_array() const
    {
        if (type_ != type_t::ARRAY)
        {
            throw geojson_parse_error("value is not an array");
        }

        std::vector<double> result;
        result.reserve(array_val_->size());

        for (const auto& val : *array_val_)
        {
            if (!val.is_number())
            {
                throw geojson_parse_error("array element is not a number");
            }
            result.push_back(val.as_number());
        }

        return result;
    }

    // Array access for iteration
    const std::vector<geojson_value>& as_array() const
    {
        if (type_ != type_t::ARRAY)
        {
            throw geojson_parse_error("value is not an array");
        }
        return *array_val_;
    }
};

// Lightweight JSON parser optimized for GeoJSON
class geojson_parser
{
  private:
    const char* pos_;
    const char* end_;

    // Skip whitespace
    void skip_whitespace()
    {
        while (pos_ < end_ && std::isspace(static_cast<unsigned char>(*pos_)))
        {
            ++pos_;
        }
    }

    // Parse a string
    std::string parse_string()
    {
        if (pos_ >= end_ || *pos_ != '"')
        {
            throw geojson_parse_error("expected '\"'");
        }
        ++pos_; // skip opening quote

        std::string result;
        while (pos_ < end_)
        {
            char c = *pos_++;

            if (c == '"')
            {
                return result;
            }
            else if (c == '\\')
            {
                if (pos_ >= end_)
                {
                    throw geojson_parse_error("unexpected end in string escape");
                }
                char escaped = *pos_++;
                switch (escaped)
                {
                    case '"':
                    case '\\':
                    case '/':
                        result += escaped;
                        break;
                    case 'b':
                        result += '\b';
                        break;
                    case 'f':
                        result += '\f';
                        break;
                    case 'n':
                        result += '\n';
                        break;
                    case 'r':
                        result += '\r';
                        break;
                    case 't':
                        result += '\t';
                        break;
                    default:
                        throw geojson_parse_error("invalid escape sequence");
                }
            }
            else
            {
                result += c;
            }
        }

        throw geojson_parse_error("unterminated string");
    }

    // Parse a number
    double parse_number()
    {
        const char* start = pos_;

        // Optional minus
        if (pos_ < end_ && *pos_ == '-')
        {
            ++pos_;
        }

        // Integer part
        if (pos_ >= end_ || !std::isdigit(static_cast<unsigned char>(*pos_)))
        {
            throw geojson_parse_error("invalid number");
        }

        while (pos_ < end_ && std::isdigit(static_cast<unsigned char>(*pos_)))
        {
            ++pos_;
        }

        // Fractional part
        if (pos_ < end_ && *pos_ == '.')
        {
            ++pos_;
            if (pos_ >= end_ || !std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                throw geojson_parse_error("invalid number: expected digit after '.'");
            }
            while (pos_ < end_ && std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                ++pos_;
            }
        }

        // Exponent part
        if (pos_ < end_ && (*pos_ == 'e' || *pos_ == 'E'))
        {
            ++pos_;
            if (pos_ < end_ && (*pos_ == '+' || *pos_ == '-'))
            {
                ++pos_;
            }
            if (pos_ >= end_ || !std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                throw geojson_parse_error("invalid number: expected digit in exponent");
            }
            while (pos_ < end_ && std::isdigit(static_cast<unsigned char>(*pos_)))
            {
                ++pos_;
            }
        }

        // Convert to double
        std::string num_str(start, pos_);
        return std::stod(num_str);
    }

    // Parse an array
    geojson_value parse_array()
    {
        if (pos_ >= end_ || *pos_ != '[')
        {
            throw geojson_parse_error("expected '['");
        }
        ++pos_; // skip '['

        skip_whitespace();

        std::vector<geojson_value> arr;

        // Empty array
        if (pos_ < end_ && *pos_ == ']')
        {
            ++pos_;
            return geojson_value(std::move(arr));
        }

        while (true)
        {
            arr.push_back(parse_value());

            skip_whitespace();

            if (pos_ >= end_)
            {
                throw geojson_parse_error("unexpected end in array");
            }

            if (*pos_ == ']')
            {
                ++pos_;
                break;
            }

            if (*pos_ != ',')
            {
                throw geojson_parse_error("expected ',' or ']' in array");
            }
            ++pos_; // skip ','

            skip_whitespace();
        }

        return geojson_value(std::move(arr));
    }

    // Parse an object
    geojson_value parse_object()
    {
        if (pos_ >= end_ || *pos_ != '{')
        {
            throw geojson_parse_error("expected '{'");
        }
        ++pos_; // skip '{'

        skip_whitespace();

        std::unordered_map<std::string, geojson_value> obj;

        // Empty object
        if (pos_ < end_ && *pos_ == '}')
        {
            ++pos_;
            return geojson_value(std::move(obj));
        }

        while (true)
        {
            // Parse key
            skip_whitespace();

            if (pos_ >= end_ || *pos_ != '"')
            {
                throw geojson_parse_error("expected string key in object");
            }

            std::string key = parse_string();

            // Parse colon
            skip_whitespace();

            if (pos_ >= end_ || *pos_ != ':')
            {
                throw geojson_parse_error("expected ':' after object key");
            }
            ++pos_; // skip ':'

            // Parse value
            skip_whitespace();
            obj.emplace(std::move(key), parse_value());

            // Check for continuation
            skip_whitespace();

            if (pos_ >= end_)
            {
                throw geojson_parse_error("unexpected end in object");
            }

            if (*pos_ == '}')
            {
                ++pos_;
                break;
            }

            if (*pos_ != ',')
            {
                throw geojson_parse_error("expected ',' or '}' in object");
            }
            ++pos_; // skip ','
        }

        return geojson_value(std::move(obj));
    }

    // Parse a value (recursive)
    geojson_value parse_value()
    {
        skip_whitespace();

        if (pos_ >= end_)
        {
            throw geojson_parse_error("unexpected end of input");
        }

        char c = *pos_;

        if (c == '{')
        {
            return parse_object();
        }
        else if (c == '[')
        {
            return parse_array();
        }
        else if (c == '"')
        {
            return geojson_value(parse_string());
        }
        else if (c == '-' || std::isdigit(static_cast<unsigned char>(c)))
        {
            return geojson_value(parse_number());
        }
        else if (pos_ + 4 <= end_ && std::strncmp(pos_, "null", 4) == 0)
        {
            pos_ += 4;
            return geojson_value();
        }
        else if (pos_ + 4 <= end_ && std::strncmp(pos_, "true", 4) == 0)
        {
            pos_ += 4;
            return geojson_value(1.0); // Use 1.0 for true (GeoJSON doesn't use booleans in coordinates)
        }
        else if (pos_ + 5 <= end_ && std::strncmp(pos_, "false", 5) == 0)
        {
            pos_ += 5;
            return geojson_value(0.0); // Use 0.0 for false
        }
        else
        {
            throw geojson_parse_error(std::string("unexpected character: ") + c);
        }
    }

  public:
    static geojson_value parse(const std::string& json)
    {
        if (json.empty())
        {
            throw geojson_parse_error("empty JSON string");
        }

        geojson_parser parser;
        parser.pos_ = json.data();
        parser.end_ = json.data() + json.size();

        geojson_value result = parser.parse_value();

        parser.skip_whitespace();

        if (parser.pos_ != parser.end_)
        {
            throw geojson_parse_error("unexpected characters after JSON value");
        }

        return result;
    }
};

}  // namespace io
}  // namespace shapes
}  // namespace simo

// #include <simo/geom/detail/geometry.hpp>

// #include <simo/exceptions.hpp>

// #include <simo/io/wkt_reader.hpp>


#include <algorithm>
#include <ciso646>
#include <cctype>
// #include <simo/geom/geometry.hpp>

// #include <simo/exceptions.hpp>

// #include <simo/io/wkt_parser.hpp>


#include <ciso646>
#include <iostream>
#include <cassert>
// #include <simo/geom/detail/types.hpp>

// #include <simo/io/wkt_token.hpp>


#define WKT_NUM                         1
#define WKT_POINT_TAGGED_TEXT           2
#define WKT_EMPTY_SET                   3
#define WKT_POINT_Z_TAGGED_TEXT         4
#define WKT_POINT_M_TAGGED_TEXT         5
#define WKT_POINT_ZM_TAGGED_TEXT        6
#define WKT_COMMA                       7
#define WKT_LPAREN                      8
#define WKT_RPAREN                      9
#define WKT_MULTIPOINT_TAGGED_TEXT     10
#define WKT_MULTIPOINT_Z_TAGGED_TEXT   11
#define WKT_MULTIPOINT_M_TAGGED_TEXT   12
#define WKT_MULTIPOINT_ZM_TAGGED_TEXT  13
#define WKT_LINESTRING_TAGGED_TEXT     14
#define WKT_LINESTRING_Z_TAGGED_TEXT   15
#define WKT_LINESTRING_M_TAGGED_TEXT   16
#define WKT_LINESTRING_ZM_TAGGED_TEXT  17
#define WKT_MULTILINESTRING_TAGGED_TEXT 18
#define WKT_MULTILINESTRING_Z_TAGGED_TEXT 19
#define WKT_MULTILINESTRING_M_TAGGED_TEXT 20
#define WKT_MULTILINESTRING_ZM_TAGGED_TEXT 21
#define WKT_POLYGON_TAGGED_TEXT        22
#define WKT_POLYGON_Z_TAGGED_TEXT      23
#define WKT_POLYGON_M_TAGGED_TEXT      24
#define WKT_POLYGON_ZM_TAGGED_TEXT     25
#define WKT_MULTIPOLYGON_TAGGED_TEXT   26
#define WKT_MULTIPOLYGON_Z_TAGGED_TEXT 27
#define WKT_MULTIPOLYGON_M_TAGGED_TEXT 28
#define WKT_MULTIPOLYGON_ZM_TAGGED_TEXT 29
#define WKT_GEOMETRYCOLLECTION_TAGGED_TEXT 30
#define WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT 31
#define WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT 32
#define WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT 33
#define WKT_END_OF_INPUT               99
#define WKT_PARSE_ERROR                100

namespace simo
{
namespace shapes
{

/*!
 * @brief A Well-known text (WKT) markup language parser result data
 * @ingroup wkt
 *
 * @since 0.0.1
 */
struct wkt_data
{
    /// the dimension type of the geometry
    geometry_type geom_type;

    /// the coordinates as a sequence of numbers
    std::vector<double> coords;

    /// the offsets in the coordinates sequence for line-like geometries
    std::vector<std::size_t> line_offsets;

    /// the offsets in the coordinates sequence for polygon rings
    std::vector<std::size_t> ring_offsets;

    /// the offsets in the ring sequence for multipolygon polygons
    std::vector<std::size_t> polygon_offsets;
};

/*!
 * @brief A Well-known text (WKT) markup language parser results
 * @ingroup wkt
 *
 * @since 0.0.1
 */
struct wkt_result
{
    /// whether there is a parser error
    bool parser_error = false;

    /// the parser result data
    wkt_data data;
};

/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4189)
#endif

/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 131
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE double
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 1048576
#endif
#define ParseARG_SDECL  struct wkt_result *result ;
#define ParseARG_PDECL , struct wkt_result *result 
#define ParseARG_FETCH  struct wkt_result *result  = yypParser->result 
#define ParseARG_STORE yypParser->result  = result 
#define YYNSTATE 399
#define YYNRULE 202
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   602,  173,  321,  311,  301,  265,  262,  240,  238,  231,
 /*    10 */   368,  367,  361,  360,  359,  352,  351,  345,  344,  343,
 /*    20 */   336,  335,  329,  328,  327,  326,  325,  319,  318,  317,
 /*    30 */    56,  125,   57,   68,   63,  185,   25,   85,  169,  171,
 /*    40 */   172,  170,   60,   49,   69,   53,   72,   70,   58,   71,
 /*    50 */    50,   61,   54,   64,   62,   59,   66,   55,   65,   52,
 /*    60 */    67,   51,  353,  271,  337,  374,  354,  278,  338,  384,
 /*    70 */   355,  280,  339,  391,  356,  282,  340,  393,  357,  285,
 /*    80 */   341,  395,  358,  291,  342,  226,  374,  337,  271,  353,
 /*    90 */   384,  338,  278,  354,  391,  339,  280,  355,  393,  340,
 /*   100 */   282,  356,  395,  341,  285,  357,  226,  342,  291,  358,
 /*   110 */    63,   57,   36,   68,  206,  244,    5,  170,  171,  137,
 /*   120 */   172,   53,   49,  164,   69,   71,   70,   77,   58,   64,
 /*   130 */    61,  223,   54,   55,   59,  131,   66,  125,  158,  149,
 /*   140 */    29,  316,  161,  154,   80,   86,   41,  133,  147,  281,
 /*   150 */    56,  120,  141,  137,    9,  249,  144,  125,  169,  269,
 /*   160 */    10,  215,   60,  175,   11,  187,   72,  241,   93,  157,
 /*   170 */    50,   75,  122,  261,   62,  306,  131,  376,   12,  131,
 /*   180 */    37,   76,  112,   94,  313,  137,  210,  237,  131,  124,
 /*   190 */   189,  253,   27,   78,  131,  190,   83,  303,  288,  309,
 /*   200 */   120,   90,  130,   40,  293,   81,   41,  309,  137,  146,
 /*   210 */   349,  309,  131,  346,   40,    1,  177,  309,   37,  176,
 /*   220 */   323,  258,  120,  120,   23,  118,    6,  174,   82,  297,
 /*   230 */   131,  394,  137,  230,   23,   33,   38,   91,  131,  235,
 /*   240 */   140,  131,  370,    3,  120,  209,  386,  104,  156,   92,
 /*   250 */   137,  103,  120,   88,  379,  120,   30,  198,  167,   96,
 /*   260 */   200,  125,  125,  202,  120,  137,  228,  155,  205,  199,
 /*   270 */   125,   34,   13,  192,  137,   87,   79,  125,  137,  191,
 /*   280 */   137,  222,  214,  204,  233,  125,  213,  245,  166,  168,
 /*   290 */   120,  203,    7,  365,  125,  145,  388,  131,    4,  397,
 /*   300 */   188,   46,  273,  125,  208,  333,  120,  162,  201,   84,
 /*   310 */   114,  186,   21,  256,  100,  383,   27,   97,   98,  310,
 /*   320 */    46,   99,  109,  194,  330,   34,  106,  381,  110,   95,
 /*   330 */   146,   38,  105,  102,  221,  197,  107,  116,  195,  162,
 /*   340 */   121,  372,  108,  309,  373,  111,   83,  196,  308,  331,
 /*   350 */     2,  126,  299,  128,  132,  168,  295,  135,  178,   48,
 /*   360 */   138,  139,  101,  284,   15,  113,   41,  115,  142,  117,
 /*   370 */   320,  119,  220,  219,  123,  127,  300,  129,  218,  290,
 /*   380 */   134,  217,  143,  216,   24,    8,  136,  279,  152,  179,
 /*   390 */   150,  151,  276,   37,  180,  225,  242,   19,  270,   42,
 /*   400 */   268,  148,  159,  211,  212,  224,  181,  264,   23,  160,
 /*   410 */   182,  259,   74,  165,   73,  183,   40,  193,  153,  184,
 /*   420 */   399,  390,  307,  298,  289,  277,  275,  267,  263,  315,
 /*   430 */   257,  255,  247,  243,   89,   28,  239,  250,   35,  227,
 /*   440 */    39,  229,   22,  396,  382,  389,  380,  371,  375,   45,
 /*   450 */   385,   44,  398,   43,  234,  305,  283,  232,   32,   31,
 /*   460 */    26,  274,  377,  246,  366,   18,  252,   16,   14,  254,
 /*   470 */   236,  334,  287,  266,   47,  272,   20,  286,  347,  314,
 /*   480 */   294,   17,  304,  387,  292,  302,  312,  322,  324,  392,
 /*   490 */   378,  332,  369,  350,  348,  364,  251,  363,  260,  603,
 /*   500 */   362,  163,  207,  603,  603,  603,  603,  603,  296,  248,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    35,   36,   37,   38,   39,   40,   41,   42,   43,   44,
 /*    10 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*    20 */    55,   56,   57,   58,   59,   60,   61,   62,   63,   64,
 /*    30 */     2,   65,    4,    5,    6,   85,    7,   71,   10,   11,
 /*    40 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*    50 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*    60 */    32,   33,   38,   40,   37,   39,   42,   44,   41,   43,
 /*    70 */    46,   48,   45,   47,   50,   52,   49,   51,   54,   56,
 /*    80 */    53,   55,   58,   60,   57,   59,   39,   37,   40,   38,
 /*    90 */    43,   41,   44,   42,   47,   45,   48,   46,   51,   49,
 /*   100 */    52,   50,   55,   53,   56,   54,   59,   57,   60,   58,
 /*   110 */     6,    4,    7,    5,   75,   85,    7,   13,   11,   65,
 /*   120 */    12,   17,   15,   69,   16,   21,   19,   73,   20,   25,
 /*   130 */    23,  121,   24,   29,   27,   65,   28,   65,   68,   67,
 /*   140 */     7,    3,   72,   71,  120,  118,    8,  124,  122,    3,
 /*   150 */     2,   65,   66,   65,    8,    3,   70,   65,   10,    3,
 /*   160 */     8,   73,   14,   71,    8,   74,   18,   74,  118,  122,
 /*   170 */    22,  120,  124,    3,   26,    3,   65,    3,    8,   65,
 /*   180 */     8,   99,    8,   72,    3,   65,   72,    3,   65,    8,
 /*   190 */    75,    3,    8,   73,   65,   72,    8,    3,    3,    1,
 /*   200 */    65,   72,    8,    8,    3,   70,    8,    1,   65,    8,
 /*   210 */     3,    1,   65,  119,    8,    8,   73,    1,    8,   72,
 /*   220 */     3,    3,   65,   65,    8,    8,    8,   70,   70,    3,
 /*   230 */    65,    3,   65,  102,    8,    8,    8,   72,   65,   75,
 /*   240 */    73,   65,    3,    7,   65,   72,    3,    8,   72,   70,
 /*   250 */    65,    8,   65,    7,    3,   65,    8,   70,   73,    8,
 /*   260 */    70,   65,   65,  102,   65,   65,    3,   71,   71,   70,
 /*   270 */    65,    8,    7,   73,   65,   98,   71,   65,   65,   76,
 /*   280 */    65,  119,   73,   71,    3,   65,   73,    3,   73,    8,
 /*   290 */    65,   71,    8,    3,   65,   70,    3,   65,    8,   76,
 /*   300 */    71,    8,    3,   65,   72,    3,   65,    8,   74,   71,
 /*   310 */     8,   70,    7,   83,    7,   93,    8,   86,    7,  111,
 /*   320 */     8,   86,    7,   90,  113,    8,    7,   90,    7,   89,
 /*   330 */     8,    8,   87,   89,  113,   93,   87,    7,   91,    8,
 /*   340 */     7,   91,   88,    1,   92,   88,    8,   92,   65,  125,
 /*   350 */     7,   65,   65,    7,   65,    8,   65,    7,   78,    8,
 /*   360 */    65,   65,  109,   65,    7,  109,    8,  108,    7,  108,
 /*   370 */   112,  107,  112,  111,  107,  106,  110,  106,  110,  105,
 /*   380 */   101,  105,   66,   77,    7,    7,  101,   78,    7,   79,
 /*   390 */     7,   67,   79,    8,   80,  125,  123,    8,  104,    7,
 /*   400 */    80,  100,    7,   76,  104,  123,   81,   81,    8,   68,
 /*   410 */    82,   82,    7,    7,   69,   83,    8,   77,  100,   84,
 /*   420 */     0,   77,    9,    9,    9,    9,    9,    9,    9,   66,
 /*   430 */     9,    9,    9,    9,   98,    7,    9,  103,    7,   87,
 /*   440 */     7,    9,    7,    9,   89,    9,    9,    9,    9,    7,
 /*   450 */     9,    7,    9,    7,  106,   67,    9,    9,    7,    7,
 /*   460 */     7,  108,   96,    9,  127,    7,    9,    7,    7,  107,
 /*   470 */    86,  117,   69,    9,    7,    9,    7,    9,  129,  115,
 /*   480 */   109,    7,  114,   97,    9,    9,    9,    9,  116,   88,
 /*   490 */    94,    9,   95,  126,    9,    9,    9,    9,  128,  130,
 /*   500 */   121,   99,  103,  130,  130,  130,  130,  130,   68,   84,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_MAX 225
static const short yy_shift_ofst[] = {
 /*     0 */    28,  148,  104,  148,  107,  107,  108,  104,  108,  198,
 /*    10 */   206,  210,  216,  342,  342,  342,  342,  342,  342,  342,
 /*    20 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    30 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    40 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  263,
 /*    50 */   281,  284,  290,  293,  299,  302,  138,  172,  174,  181,
 /*    60 */   184,  188,  194,  195,  201,  207,  217,  218,  226,  228,
 /*    70 */   239,  243,  251,  406,  227,  109,  405,   29,   29,  105,
 /*    80 */   109,  133,  133,  227,  105,  105,  236,  246,  248,  246,
 /*    90 */   265,  265,  133,  236,  305,  307,  308,  311,  308,  311,
 /*   100 */   312,  315,  307,  312,  317,  319,  317,  319,  321,  322,
 /*   110 */   323,  321,  323,  315,  322,  330,  331,  330,  331,  333,
 /*   120 */   342,  338,  343,  333,  338,  342,  342,  346,  347,  346,
 /*   130 */   347,  342,  342,  343,  350,  351,  350,  342,  342,  342,
 /*   140 */   357,  361,  358,  361,  377,  377,  351,  378,  381,  383,
 /*   150 */   385,  383,  389,  381,  392,  392,  265,  378,  395,  400,
 /*   160 */   395,  305,  389,  405,  406,  408,  357,  357,  248,  146,
 /*   170 */   152,  156,  170,  420,  413,  414,  415,  447,  416,  417,
 /*   180 */   418,  419,  421,  422,  423,  424,  428,  427,  431,  432,
 /*   190 */   433,  434,  435,  436,  437,  438,  439,  441,  442,  444,
 /*   200 */   446,  443,  448,  451,  452,  453,  454,  457,  458,  460,
 /*   210 */   461,  464,  466,  467,  469,  474,  468,  475,  476,  477,
 /*   220 */   478,  482,  485,  486,  487,  488,
};
#define YY_REDUCE_USE_DFLT (-51)
#define YY_REDUCE_MAX 168
static const short yy_reduce_ofst[] = {
 /*     0 */   -35,   50,   48,   27,   24,   51,   47,   23,   26,   86,
 /*    10 */    54,   72,   70,  165,  176,  185,  114,  167,  173,  232,
 /*    20 */    88,  111,  215,  147,  225,  120,  205,  241,  135,  158,
 /*    30 */   187,  197,  212,  220,  229,  238,  -34,   92,  123,  129,
 /*    40 */   143,  157,  196,  179,  190,  199,  200,  209,  213,  352,
 /*    50 */   348,  349,  337,  355,  353,  354,  363,  388,  366,  364,
 /*    60 */   384,  362,  368,  403,  371,  367,  372,  370,  440,  401,
 /*    70 */   397,  386,  396,  425,  402,  379,  399,  -50,   30,   39,
 /*    80 */    10,   91,   93,   82,  115,  164,   94,  131,  177,  161,
 /*    90 */   203,  223,  234,  162,  230,  222,  231,  233,  235,  237,
 /*   100 */   240,  211,  242,  244,  245,  247,  249,  250,  252,  253,
 /*   110 */   254,  255,  257,  221,  256,  258,  259,  260,  261,  208,
 /*   120 */   283,  264,  224,  262,  267,  286,  287,  266,  269,  268,
 /*   130 */   271,  289,  291,  270,  274,  279,  276,  295,  296,  298,
 /*   140 */   306,  280,  316,  309,  310,  313,  285,  273,  294,  314,
 /*   150 */   324,  320,  301,  300,  325,  326,  327,  282,  328,  341,
 /*   160 */   329,  332,  318,  334,  335,  345,  340,  344,  336,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    10 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    20 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    30 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    40 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    50 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    60 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*    70 */   601,  601,  601,  465,  601,  571,  519,  467,  467,  443,
 /*    80 */   571,  441,  441,  601,  443,  443,  563,  517,  601,  517,
 /*    90 */   445,  445,  441,  563,  463,  491,  601,  485,  601,  485,
 /*   100 */   601,  535,  491,  601,  601,  487,  601,  487,  489,  601,
 /*   110 */   601,  489,  601,  535,  601,  533,  601,  533,  601,  531,
 /*   120 */   601,  601,  587,  531,  601,  601,  601,  529,  601,  529,
 /*   130 */   601,  601,  601,  587,  523,  601,  523,  601,  601,  601,
 /*   140 */   447,  453,  601,  453,  455,  455,  601,  579,  521,  457,
 /*   150 */   601,  457,  601,  521,  459,  459,  445,  579,  461,  601,
 /*   160 */   461,  463,  601,  519,  465,  601,  447,  447,  601,  601,
 /*   170 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*   180 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*   190 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*   200 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*   210 */   601,  601,  601,  601,  601,  601,  601,  601,  601,  601,
 /*   220 */   601,  601,  601,  601,  601,  601,  578,  496,  495,  482,
 /*   230 */   518,  407,  525,  537,  538,  444,  494,  493,  406,  481,
 /*   240 */   405,  442,  580,  480,  468,  599,  514,  479,  466,  478,
 /*   250 */   520,  591,  526,  539,  540,  477,  464,  476,  597,  462,
 /*   260 */   598,  475,  404,  474,  460,  403,  515,  473,  458,  472,
 /*   270 */   522,  581,  527,  541,  542,  471,  456,  470,  582,  454,
 /*   280 */   583,  469,  584,  452,  440,  585,  516,  436,  435,  451,
 /*   290 */   524,  586,  528,  543,  544,  439,  434,  433,  450,  438,
 /*   300 */   530,  402,  545,  549,  550,  432,  431,  449,  437,  428,
 /*   310 */   532,  401,  546,  551,  552,  430,  429,  427,  426,  425,
 /*   320 */   534,  400,  547,  553,  554,  424,  423,  422,  421,  420,
 /*   330 */   536,  588,  548,  555,  556,  419,  418,  557,  558,  559,
 /*   340 */   560,  561,  562,  417,  416,  415,  564,  600,  589,  593,
 /*   350 */   594,  414,  413,  565,  566,  567,  568,  569,  570,  412,
 /*   360 */   411,  410,  572,  592,  590,  595,  596,  409,  408,  508,
 /*   370 */   507,  502,  488,  490,  573,  503,  509,  510,  506,  505,
 /*   380 */   501,  486,  500,  492,  574,  504,  511,  512,  499,  484,
 /*   390 */   448,  575,  498,  576,  497,  577,  483,  446,  513,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "WKT_NUM",       "WKT_POINT_TAGGED_TEXT",  "WKT_EMPTY_SET",
  "WKT_POINT_Z_TAGGED_TEXT",  "WKT_POINT_M_TAGGED_TEXT",  "WKT_POINT_ZM_TAGGED_TEXT",  "WKT_COMMA",   
  "WKT_LPAREN",    "WKT_RPAREN",    "WKT_MULTIPOINT_TAGGED_TEXT",  "WKT_MULTIPOINT_Z_TAGGED_TEXT",
  "WKT_MULTIPOINT_M_TAGGED_TEXT",  "WKT_MULTIPOINT_ZM_TAGGED_TEXT",  "WKT_LINESTRING_TAGGED_TEXT",  "WKT_LINESTRING_Z_TAGGED_TEXT",
  "WKT_LINESTRING_M_TAGGED_TEXT",  "WKT_LINESTRING_ZM_TAGGED_TEXT",  "WKT_MULTILINESTRING_TAGGED_TEXT",  "WKT_MULTILINESTRING_Z_TAGGED_TEXT",
  "WKT_MULTILINESTRING_M_TAGGED_TEXT",  "WKT_MULTILINESTRING_ZM_TAGGED_TEXT",  "WKT_POLYGON_TAGGED_TEXT",  "WKT_POLYGON_Z_TAGGED_TEXT",
  "WKT_POLYGON_M_TAGGED_TEXT",  "WKT_POLYGON_ZM_TAGGED_TEXT",  "WKT_MULTIPOLYGON_TAGGED_TEXT",  "WKT_MULTIPOLYGON_Z_TAGGED_TEXT",
  "WKT_MULTIPOLYGON_M_TAGGED_TEXT",  "WKT_MULTIPOLYGON_ZM_TAGGED_TEXT",  "WKT_GEOMETRYCOLLECTION_TAGGED_TEXT",  "WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT",
  "WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT",  "WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT",  "error",         "program",     
  "wkt_text",      "point",         "point_z",       "point_m",     
  "point_zm",      "multipoint",    "multipoint_z",  "multipoint_m",
  "multipoint_zm",  "linestring",    "linestring_z",  "linestring_m",
  "linestring_zm",  "multilinestring",  "multilinestring_z",  "multilinestring_m",
  "multilinestring_zm",  "polygon",       "polygon_z",     "polygon_m",   
  "polygon_zm",    "multipolygon",  "multipolygon_z",  "multipolygon_m",
  "multipolygon_zm",  "geometrycollection",  "geometrycollection_z",  "geometrycollection_m",
  "geometrycollection_zm",  "coord",         "point_text",    "point_text_z",
  "point_text_m",  "point_text_zm",  "coord_xy",      "coord_xyz",   
  "coord_xym",     "coord_xyzm",    "coord_xy_repeated",  "coord_xyz_repeated",
  "coord_xym_repeated",  "coord_xyzm_repeated",  "multipoint_text",  "multipoint_text_2",
  "multipoint_text_z",  "multipoint_text_z_2",  "multipoint_text_m",  "multipoint_text_m_2",
  "multipoint_text_zm",  "multipoint_text_zm_2",  "linestring_text",  "linestring_text_z",
  "linestring_text_m",  "linestring_text_zm",  "linestring_text_repeated",  "linestring_text_z_repeated",
  "linestring_text_m_repeated",  "linestring_text_zm_repeated",  "multilinestring_text",  "multilinestring_text_z",
  "multilinestring_text_m",  "multilinestring_text_zm",  "ring_text",     "ring_text_z", 
  "ring_text_m",   "ring_text_zm",  "ring_text_repeated",  "ring_text_z_repeated",
  "ring_text_m_repeated",  "ring_text_zm_repeated",  "polygon_text",  "polygon_text_z",
  "polygon_text_m",  "polygon_text_zm",  "polygon_text_repeated",  "polygon_text_z_repeated",
  "polygon_text_m_repeated",  "polygon_text_zm_repeated",  "multipolygon_text",  "multipolygon_text_z",
  "multipolygon_text_m",  "multipolygon_text_zm",  "geometry_text",  "geometry_text_repeated",
  "geometry_text_z",  "geometry_text_z_repeated",  "geometry_text_m",  "geometry_text_m_repeated",
  "geometry_text_zm",  "geometry_text_zm_repeated",  "geometrycollection_text",  "geometrycollection_text_z",
  "geometrycollection_text_m",  "geometrycollection_text_zm",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= wkt_text",
 /*   1 */ "wkt_text ::= point",
 /*   2 */ "wkt_text ::= point_z",
 /*   3 */ "wkt_text ::= point_m",
 /*   4 */ "wkt_text ::= point_zm",
 /*   5 */ "wkt_text ::= multipoint",
 /*   6 */ "wkt_text ::= multipoint_z",
 /*   7 */ "wkt_text ::= multipoint_m",
 /*   8 */ "wkt_text ::= multipoint_zm",
 /*   9 */ "wkt_text ::= linestring",
 /*  10 */ "wkt_text ::= linestring_z",
 /*  11 */ "wkt_text ::= linestring_m",
 /*  12 */ "wkt_text ::= linestring_zm",
 /*  13 */ "wkt_text ::= multilinestring",
 /*  14 */ "wkt_text ::= multilinestring_z",
 /*  15 */ "wkt_text ::= multilinestring_m",
 /*  16 */ "wkt_text ::= multilinestring_zm",
 /*  17 */ "wkt_text ::= polygon",
 /*  18 */ "wkt_text ::= polygon_z",
 /*  19 */ "wkt_text ::= polygon_m",
 /*  20 */ "wkt_text ::= polygon_zm",
 /*  21 */ "wkt_text ::= multipolygon",
 /*  22 */ "wkt_text ::= multipolygon_z",
 /*  23 */ "wkt_text ::= multipolygon_m",
 /*  24 */ "wkt_text ::= multipolygon_zm",
 /*  25 */ "wkt_text ::= geometrycollection",
 /*  26 */ "wkt_text ::= geometrycollection_z",
 /*  27 */ "wkt_text ::= geometrycollection_m",
 /*  28 */ "wkt_text ::= geometrycollection_zm",
 /*  29 */ "coord ::= WKT_NUM",
 /*  30 */ "point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET",
 /*  31 */ "point ::= WKT_POINT_TAGGED_TEXT point_text",
 /*  32 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  33 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z",
 /*  34 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  35 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m",
 /*  36 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  37 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm",
 /*  38 */ "coord_xy ::= coord coord",
 /*  39 */ "coord_xyz ::= coord coord coord",
 /*  40 */ "coord_xym ::= coord coord coord",
 /*  41 */ "coord_xyzm ::= coord coord coord coord",
 /*  42 */ "coord_xy_repeated ::=",
 /*  43 */ "coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated",
 /*  44 */ "coord_xyz_repeated ::=",
 /*  45 */ "coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated",
 /*  46 */ "coord_xym_repeated ::=",
 /*  47 */ "coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated",
 /*  48 */ "coord_xyzm_repeated ::=",
 /*  49 */ "coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated",
 /*  50 */ "point_text ::= WKT_LPAREN coord_xy WKT_RPAREN",
 /*  51 */ "point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN",
 /*  52 */ "point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN",
 /*  53 */ "point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN",
 /*  54 */ "multipoint_text ::=",
 /*  55 */ "multipoint_text ::= WKT_COMMA point_text multipoint_text",
 /*  56 */ "multipoint_text_2 ::=",
 /*  57 */ "multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2",
 /*  58 */ "multipoint_text_z ::=",
 /*  59 */ "multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z",
 /*  60 */ "multipoint_text_z_2 ::=",
 /*  61 */ "multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2",
 /*  62 */ "multipoint_text_m ::=",
 /*  63 */ "multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m",
 /*  64 */ "multipoint_text_m_2 ::=",
 /*  65 */ "multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2",
 /*  66 */ "multipoint_text_zm ::=",
 /*  67 */ "multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm",
 /*  68 */ "multipoint_text_zm_2 ::=",
 /*  69 */ "multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2",
 /*  70 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET",
 /*  71 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN",
 /*  72 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN",
 /*  73 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  74 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN",
 /*  75 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN",
 /*  76 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  77 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN",
 /*  78 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN",
 /*  79 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  80 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN",
 /*  81 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN",
 /*  82 */ "linestring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN",
 /*  83 */ "linestring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN",
 /*  84 */ "linestring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN",
 /*  85 */ "linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN",
 /*  86 */ "linestring_text_repeated ::=",
 /*  87 */ "linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated",
 /*  88 */ "linestring_text_z_repeated ::=",
 /*  89 */ "linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated",
 /*  90 */ "linestring_text_m_repeated ::=",
 /*  91 */ "linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated",
 /*  92 */ "linestring_text_zm_repeated ::=",
 /*  93 */ "linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated",
 /*  94 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
 /*  95 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text",
 /*  96 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  97 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z",
 /*  98 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  99 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m",
 /* 100 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 101 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm",
 /* 102 */ "multilinestring_text ::= WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN",
 /* 103 */ "multilinestring_text_z ::= WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN",
 /* 104 */ "multilinestring_text_m ::= WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN",
 /* 105 */ "multilinestring_text_zm ::= WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN",
 /* 106 */ "multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
 /* 107 */ "multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text",
 /* 108 */ "multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 109 */ "multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z",
 /* 110 */ "multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 111 */ "multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m",
 /* 112 */ "multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 113 */ "multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm",
 /* 114 */ "ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN",
 /* 115 */ "ring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN",
 /* 116 */ "ring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN",
 /* 117 */ "ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN",
 /* 118 */ "ring_text_repeated ::=",
 /* 119 */ "ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated",
 /* 120 */ "ring_text_z_repeated ::=",
 /* 121 */ "ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated",
 /* 122 */ "ring_text_m_repeated ::=",
 /* 123 */ "ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated",
 /* 124 */ "ring_text_zm_repeated ::=",
 /* 125 */ "ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated",
 /* 126 */ "polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN",
 /* 127 */ "polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN",
 /* 128 */ "polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN",
 /* 129 */ "polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN",
 /* 130 */ "polygon_text_repeated ::=",
 /* 131 */ "polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated",
 /* 132 */ "polygon_text_z_repeated ::=",
 /* 133 */ "polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated",
 /* 134 */ "polygon_text_m_repeated ::=",
 /* 135 */ "polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated",
 /* 136 */ "polygon_text_zm_repeated ::=",
 /* 137 */ "polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated",
 /* 138 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET",
 /* 139 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text",
 /* 140 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 141 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z",
 /* 142 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 143 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m",
 /* 144 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 145 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm",
 /* 146 */ "multipolygon_text ::= WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN",
 /* 147 */ "multipolygon_text_z ::= WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN",
 /* 148 */ "multipolygon_text_m ::= WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN",
 /* 149 */ "multipolygon_text_zm ::= WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN",
 /* 150 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET",
 /* 151 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text",
 /* 152 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 153 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z",
 /* 154 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 155 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m",
 /* 156 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 157 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm",
 /* 158 */ "geometry_text ::= point",
 /* 159 */ "geometry_text ::= multipoint",
 /* 160 */ "geometry_text ::= linestring",
 /* 161 */ "geometry_text ::= multilinestring",
 /* 162 */ "geometry_text ::= polygon",
 /* 163 */ "geometry_text ::= multipolygon",
 /* 164 */ "geometry_text_repeated ::=",
 /* 165 */ "geometry_text_repeated ::= WKT_COMMA geometry_text geometry_text_repeated",
 /* 166 */ "geometry_text_z ::= point_z",
 /* 167 */ "geometry_text_z ::= multipoint_z",
 /* 168 */ "geometry_text_z ::= linestring_z",
 /* 169 */ "geometry_text_z ::= multilinestring_z",
 /* 170 */ "geometry_text_z ::= polygon_z",
 /* 171 */ "geometry_text_z ::= multipolygon_z",
 /* 172 */ "geometry_text_z_repeated ::=",
 /* 173 */ "geometry_text_z_repeated ::= WKT_COMMA geometry_text_z geometry_text_z_repeated",
 /* 174 */ "geometry_text_m ::= point_m",
 /* 175 */ "geometry_text_m ::= multipoint_m",
 /* 176 */ "geometry_text_m ::= linestring_m",
 /* 177 */ "geometry_text_m ::= multilinestring_m",
 /* 178 */ "geometry_text_m ::= polygon_m",
 /* 179 */ "geometry_text_m ::= multipolygon_m",
 /* 180 */ "geometry_text_m_repeated ::=",
 /* 181 */ "geometry_text_m_repeated ::= WKT_COMMA geometry_text_m geometry_text_m_repeated",
 /* 182 */ "geometry_text_zm ::= point_zm",
 /* 183 */ "geometry_text_zm ::= multipoint_zm",
 /* 184 */ "geometry_text_zm ::= linestring_zm",
 /* 185 */ "geometry_text_zm ::= multilinestring_zm",
 /* 186 */ "geometry_text_zm ::= polygon_zm",
 /* 187 */ "geometry_text_zm ::= multipolygon_zm",
 /* 188 */ "geometry_text_zm_repeated ::=",
 /* 189 */ "geometry_text_zm_repeated ::= WKT_COMMA geometry_text_zm geometry_text_zm_repeated",
 /* 190 */ "geometrycollection_text ::= WKT_LPAREN geometry_text geometry_text_repeated WKT_RPAREN",
 /* 191 */ "geometrycollection_text_z ::= WKT_LPAREN geometry_text_z geometry_text_z_repeated WKT_RPAREN",
 /* 192 */ "geometrycollection_text_m ::= WKT_LPAREN geometry_text_m geometry_text_m_repeated WKT_RPAREN",
 /* 193 */ "geometrycollection_text_zm ::= WKT_LPAREN geometry_text_zm geometry_text_zm_repeated WKT_RPAREN",
 /* 194 */ "geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT WKT_EMPTY_SET",
 /* 195 */ "geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT geometrycollection_text",
 /* 196 */ "geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 197 */ "geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT geometrycollection_text_z",
 /* 198 */ "geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 199 */ "geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT geometrycollection_text_m",
 /* 200 */ "geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 201 */ "geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT geometrycollection_text_zm",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_MAX ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_MAX );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_SZ_ACTTAB );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */

    result->parser_error = true;
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 35, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 36, 1 },
  { 65, 1 },
  { 37, 2 },
  { 37, 2 },
  { 38, 2 },
  { 38, 2 },
  { 39, 2 },
  { 39, 2 },
  { 40, 2 },
  { 40, 2 },
  { 70, 2 },
  { 71, 3 },
  { 72, 3 },
  { 73, 4 },
  { 74, 0 },
  { 74, 3 },
  { 75, 0 },
  { 75, 3 },
  { 76, 0 },
  { 76, 3 },
  { 77, 0 },
  { 77, 3 },
  { 66, 3 },
  { 67, 3 },
  { 68, 3 },
  { 69, 3 },
  { 78, 0 },
  { 78, 3 },
  { 79, 0 },
  { 79, 3 },
  { 80, 0 },
  { 80, 3 },
  { 81, 0 },
  { 81, 3 },
  { 82, 0 },
  { 82, 3 },
  { 83, 0 },
  { 83, 3 },
  { 84, 0 },
  { 84, 3 },
  { 85, 0 },
  { 85, 3 },
  { 41, 2 },
  { 41, 5 },
  { 41, 5 },
  { 42, 2 },
  { 42, 5 },
  { 42, 5 },
  { 43, 2 },
  { 43, 5 },
  { 43, 5 },
  { 44, 2 },
  { 44, 5 },
  { 44, 5 },
  { 86, 6 },
  { 87, 6 },
  { 88, 6 },
  { 89, 6 },
  { 90, 0 },
  { 90, 3 },
  { 91, 0 },
  { 91, 3 },
  { 92, 0 },
  { 92, 3 },
  { 93, 0 },
  { 93, 3 },
  { 45, 2 },
  { 45, 2 },
  { 46, 2 },
  { 46, 2 },
  { 47, 2 },
  { 47, 2 },
  { 48, 2 },
  { 48, 2 },
  { 94, 4 },
  { 95, 4 },
  { 96, 4 },
  { 97, 4 },
  { 49, 2 },
  { 49, 2 },
  { 50, 2 },
  { 50, 2 },
  { 51, 2 },
  { 51, 2 },
  { 52, 2 },
  { 52, 2 },
  { 98, 10 },
  { 99, 10 },
  { 100, 10 },
  { 101, 10 },
  { 102, 0 },
  { 102, 3 },
  { 103, 0 },
  { 103, 3 },
  { 104, 0 },
  { 104, 3 },
  { 105, 0 },
  { 105, 3 },
  { 106, 4 },
  { 107, 4 },
  { 108, 4 },
  { 109, 4 },
  { 110, 0 },
  { 110, 3 },
  { 111, 0 },
  { 111, 3 },
  { 112, 0 },
  { 112, 3 },
  { 113, 0 },
  { 113, 3 },
  { 53, 2 },
  { 53, 2 },
  { 54, 2 },
  { 54, 2 },
  { 55, 2 },
  { 55, 2 },
  { 56, 2 },
  { 56, 2 },
  { 114, 4 },
  { 115, 4 },
  { 116, 4 },
  { 117, 4 },
  { 57, 2 },
  { 57, 2 },
  { 58, 2 },
  { 58, 2 },
  { 59, 2 },
  { 59, 2 },
  { 60, 2 },
  { 60, 2 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 119, 0 },
  { 119, 3 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 121, 0 },
  { 121, 3 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 123, 0 },
  { 123, 3 },
  { 124, 1 },
  { 124, 1 },
  { 124, 1 },
  { 124, 1 },
  { 124, 1 },
  { 124, 1 },
  { 125, 0 },
  { 125, 3 },
  { 126, 4 },
  { 127, 4 },
  { 128, 4 },
  { 129, 4 },
  { 61, 2 },
  { 61, 2 },
  { 62, 2 },
  { 62, 2 },
  { 63, 2 },
  { 63, 2 },
  { 64, 2 },
  { 64, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 29: /* coord ::= WKT_NUM */
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
        break;
      case 30: /* point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = geometry_type::POINT;
}
        break;
      case 31: /* point ::= WKT_POINT_TAGGED_TEXT point_text */
{
    result->data.geom_type = geometry_type::POINT;
}
        break;
      case 32: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = geometry_type::POINTZ;
}
        break;
      case 33: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z */
{
    result->data.geom_type = geometry_type::POINTZ;
}
        break;
      case 34: /* point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = geometry_type::POINTM;
}
        break;
      case 35: /* point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m */
{
    result->data.geom_type = geometry_type::POINTM;
}
        break;
      case 36: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = geometry_type::POINTZM;
}
        break;
      case 37: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm */
{
    result->data.geom_type = geometry_type::POINTZM;
}
        break;
      case 38: /* coord_xy ::= coord coord */
{
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 39: /* coord_xyz ::= coord coord coord */
      case 40: /* coord_xym ::= coord coord coord */ yytestcase(yyruleno==40);
{
    result->data.coords.push_back(yymsp[-2].minor.yy0);
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 41: /* coord_xyzm ::= coord coord coord coord */
{
    result->data.coords.push_back(yymsp[-3].minor.yy0);
    result->data.coords.push_back(yymsp[-2].minor.yy0);
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 70: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET */
      case 71: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN */ yytestcase(yyruleno==71);
      case 72: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN */ yytestcase(yyruleno==72);
{
    result->data.geom_type = geometry_type::MULTIPOINT;
}
        break;
      case 73: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 74: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN */ yytestcase(yyruleno==74);
      case 75: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN */ yytestcase(yyruleno==75);
{
    result->data.geom_type = geometry_type::MULTIPOINTZ;
}
        break;
      case 76: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 77: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN */ yytestcase(yyruleno==77);
      case 78: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN */ yytestcase(yyruleno==78);
{
    result->data.geom_type = geometry_type::MULTIPOINTM;
}
        break;
      case 79: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 80: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN */ yytestcase(yyruleno==80);
      case 81: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN */ yytestcase(yyruleno==81);
{
    result->data.geom_type = geometry_type::MULTIPOINTZM;
}
        break;
      case 82: /* linestring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN */
      case 83: /* linestring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN */ yytestcase(yyruleno==83);
      case 84: /* linestring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN */ yytestcase(yyruleno==84);
      case 85: /* linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN */ yytestcase(yyruleno==85);
{
    result->data.line_offsets.push_back(result->data.coords.size());
}
        break;
      case 114: /* ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN */ yytestcase(yyruleno==114);
      case 115: /* ring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN */ yytestcase(yyruleno==115);
      case 116: /* ring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN */ yytestcase(yyruleno==116);
      case 117: /* ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN */ yytestcase(yyruleno==117);
{
    result->data.ring_offsets.push_back(result->data.coords.size());
}
        break;
      case 94: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
      case 95: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text */ yytestcase(yyruleno==95);
{
    result->data.geom_type = geometry_type::LINESTRING;
}
        break;
      case 96: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 97: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z */ yytestcase(yyruleno==97);
{
    result->data.geom_type = geometry_type::LINESTRINGZ;
}
        break;
      case 98: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 99: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m */ yytestcase(yyruleno==99);
{
    result->data.geom_type = geometry_type::LINESTRINGM;
}
        break;
      case 100: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 101: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm */ yytestcase(yyruleno==101);
{
    result->data.geom_type = geometry_type::LINESTRINGZM;
}
        break;
      case 106: /* multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
      case 107: /* multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text */ yytestcase(yyruleno==107);
{
    result->data.geom_type = geometry_type::MULTILINESTRING;
}
        break;
      case 108: /* multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 109: /* multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z */ yytestcase(yyruleno==109);
{
    result->data.geom_type = geometry_type::MULTILINESTRINGZ;
}
        break;
      case 110: /* multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 111: /* multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m */ yytestcase(yyruleno==111);
{
    result->data.geom_type = geometry_type::MULTILINESTRINGM;
}
        break;
      case 112: /* multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 113: /* multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm */ yytestcase(yyruleno==113);
{
    result->data.geom_type = geometry_type::MULTILINESTRINGZM;
}
        break;
      case 126: /* polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN */
      case 127: /* polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==127);
      case 128: /* polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==128);
      case 129: /* polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==129);
{
    result->data.polygon_offsets.push_back(result->data.ring_offsets.size());
}
        break;
      case 138: /* polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET */
      case 139: /* polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text */ yytestcase(yyruleno==139);
{
    result->data.geom_type = geometry_type::POLYGON;
}
        break;
      case 140: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 141: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z */ yytestcase(yyruleno==141);
{
    result->data.geom_type = geometry_type::POLYGONZ;
}
        break;
      case 142: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 143: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m */ yytestcase(yyruleno==143);
{
    result->data.geom_type = geometry_type::POLYGONM;
}
        break;
      case 144: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 145: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm */ yytestcase(yyruleno==145);
{
    result->data.geom_type = geometry_type::POLYGONZM;
}
        break;
      case 150: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET */
      case 151: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text */ yytestcase(yyruleno==151);
{
    result->data.geom_type = geometry_type::MULTIPOLYGON;
}
        break;
      case 152: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 153: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z */ yytestcase(yyruleno==153);
{
    result->data.geom_type = geometry_type::MULTIPOLYGONZ;
}
        break;
      case 154: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 155: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m */ yytestcase(yyruleno==155);
{
    result->data.geom_type = geometry_type::MULTIPOLYGONM;
}
        break;
      case 156: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 157: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm */ yytestcase(yyruleno==157);
{
    result->data.geom_type = geometry_type::MULTIPOLYGONZM;
}
        break;
      case 194: /* geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT WKT_EMPTY_SET */
      case 195: /* geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT geometrycollection_text */ yytestcase(yyruleno==195);
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTION;
}
        break;
      case 196: /* geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 197: /* geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT geometrycollection_text_z */ yytestcase(yyruleno==197);
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONZ;
}
        break;
      case 198: /* geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 199: /* geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT geometrycollection_text_m */ yytestcase(yyruleno==199);
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONM;
}
        break;
      case 200: /* geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 201: /* geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT geometrycollection_text_zm */ yytestcase(yyruleno==201);
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONZM;
}
        break;
      default:
      /* (0) program ::= wkt_text */ yytestcase(yyruleno==0);
      /* (1) wkt_text ::= point */ yytestcase(yyruleno==1);
      /* (2) wkt_text ::= point_z */ yytestcase(yyruleno==2);
      /* (3) wkt_text ::= point_m */ yytestcase(yyruleno==3);
      /* (4) wkt_text ::= point_zm */ yytestcase(yyruleno==4);
      /* (5) wkt_text ::= multipoint */ yytestcase(yyruleno==5);
      /* (6) wkt_text ::= multipoint_z */ yytestcase(yyruleno==6);
      /* (7) wkt_text ::= multipoint_m */ yytestcase(yyruleno==7);
      /* (8) wkt_text ::= multipoint_zm */ yytestcase(yyruleno==8);
      /* (9) wkt_text ::= linestring */ yytestcase(yyruleno==9);
      /* (10) wkt_text ::= linestring_z */ yytestcase(yyruleno==10);
      /* (11) wkt_text ::= linestring_m */ yytestcase(yyruleno==11);
      /* (12) wkt_text ::= linestring_zm */ yytestcase(yyruleno==12);
      /* (13) wkt_text ::= multilinestring */ yytestcase(yyruleno==13);
      /* (14) wkt_text ::= multilinestring_z */ yytestcase(yyruleno==14);
      /* (15) wkt_text ::= multilinestring_m */ yytestcase(yyruleno==15);
      /* (16) wkt_text ::= multilinestring_zm */ yytestcase(yyruleno==16);
      /* (17) wkt_text ::= polygon */ yytestcase(yyruleno==17);
      /* (18) wkt_text ::= polygon_z */ yytestcase(yyruleno==18);
      /* (19) wkt_text ::= polygon_m */ yytestcase(yyruleno==19);
      /* (20) wkt_text ::= polygon_zm */ yytestcase(yyruleno==20);
      /* (21) wkt_text ::= multipolygon */ yytestcase(yyruleno==21);
      /* (22) wkt_text ::= multipolygon_z */ yytestcase(yyruleno==22);
      /* (23) wkt_text ::= multipolygon_m */ yytestcase(yyruleno==23);
      /* (24) wkt_text ::= multipolygon_zm */ yytestcase(yyruleno==24);
      /* (25) wkt_text ::= geometrycollection */ yytestcase(yyruleno==25);
      /* (26) wkt_text ::= geometrycollection_z */ yytestcase(yyruleno==26);
      /* (27) wkt_text ::= geometrycollection_m */ yytestcase(yyruleno==27);
      /* (28) wkt_text ::= geometrycollection_zm */ yytestcase(yyruleno==28);
      /* (42) coord_xy_repeated ::= */ yytestcase(yyruleno==42);
      /* (43) coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated */ yytestcase(yyruleno==43);
      /* (44) coord_xyz_repeated ::= */ yytestcase(yyruleno==44);
      /* (45) coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated */ yytestcase(yyruleno==45);
      /* (46) coord_xym_repeated ::= */ yytestcase(yyruleno==46);
      /* (47) coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated */ yytestcase(yyruleno==47);
      /* (48) coord_xyzm_repeated ::= */ yytestcase(yyruleno==48);
      /* (49) coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated */ yytestcase(yyruleno==49);
      /* (50) point_text ::= WKT_LPAREN coord_xy WKT_RPAREN */ yytestcase(yyruleno==50);
      /* (51) point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN */ yytestcase(yyruleno==51);
      /* (52) point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN */ yytestcase(yyruleno==52);
      /* (53) point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN */ yytestcase(yyruleno==53);
      /* (54) multipoint_text ::= */ yytestcase(yyruleno==54);
      /* (55) multipoint_text ::= WKT_COMMA point_text multipoint_text */ yytestcase(yyruleno==55);
      /* (56) multipoint_text_2 ::= */ yytestcase(yyruleno==56);
      /* (57) multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2 */ yytestcase(yyruleno==57);
      /* (58) multipoint_text_z ::= */ yytestcase(yyruleno==58);
      /* (59) multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z */ yytestcase(yyruleno==59);
      /* (60) multipoint_text_z_2 ::= */ yytestcase(yyruleno==60);
      /* (61) multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2 */ yytestcase(yyruleno==61);
      /* (62) multipoint_text_m ::= */ yytestcase(yyruleno==62);
      /* (63) multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m */ yytestcase(yyruleno==63);
      /* (64) multipoint_text_m_2 ::= */ yytestcase(yyruleno==64);
      /* (65) multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2 */ yytestcase(yyruleno==65);
      /* (66) multipoint_text_zm ::= */ yytestcase(yyruleno==66);
      /* (67) multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm */ yytestcase(yyruleno==67);
      /* (68) multipoint_text_zm_2 ::= */ yytestcase(yyruleno==68);
      /* (69) multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2 */ yytestcase(yyruleno==69);
      /* (86) linestring_text_repeated ::= */ yytestcase(yyruleno==86);
      /* (87) linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated */ yytestcase(yyruleno==87);
      /* (88) linestring_text_z_repeated ::= */ yytestcase(yyruleno==88);
      /* (89) linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated */ yytestcase(yyruleno==89);
      /* (90) linestring_text_m_repeated ::= */ yytestcase(yyruleno==90);
      /* (91) linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated */ yytestcase(yyruleno==91);
      /* (92) linestring_text_zm_repeated ::= */ yytestcase(yyruleno==92);
      /* (93) linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated */ yytestcase(yyruleno==93);
      /* (102) multilinestring_text ::= WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN */ yytestcase(yyruleno==102);
      /* (103) multilinestring_text_z ::= WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==103);
      /* (104) multilinestring_text_m ::= WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==104);
      /* (105) multilinestring_text_zm ::= WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==105);
      /* (118) ring_text_repeated ::= */ yytestcase(yyruleno==118);
      /* (119) ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated */ yytestcase(yyruleno==119);
      /* (120) ring_text_z_repeated ::= */ yytestcase(yyruleno==120);
      /* (121) ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated */ yytestcase(yyruleno==121);
      /* (122) ring_text_m_repeated ::= */ yytestcase(yyruleno==122);
      /* (123) ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated */ yytestcase(yyruleno==123);
      /* (124) ring_text_zm_repeated ::= */ yytestcase(yyruleno==124);
      /* (125) ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated */ yytestcase(yyruleno==125);
      /* (126) polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN */ yytestcase(yyruleno==126);
      /* (127) polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==127);
      /* (128) polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==128);
      /* (129) polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==129);
      /* (130) polygon_text_repeated ::= */ yytestcase(yyruleno==130);
      /* (131) polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated */ yytestcase(yyruleno==131);
      /* (132) polygon_text_z_repeated ::= */ yytestcase(yyruleno==132);
      /* (133) polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated */ yytestcase(yyruleno==133);
      /* (134) polygon_text_m_repeated ::= */ yytestcase(yyruleno==134);
      /* (135) polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated */ yytestcase(yyruleno==135);
      /* (136) polygon_text_zm_repeated ::= */ yytestcase(yyruleno==136);
      /* (137) polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated */ yytestcase(yyruleno==137);
      /* (146) multipolygon_text ::= WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN */ yytestcase(yyruleno==146);
      /* (147) multipolygon_text_z ::= WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==147);
      /* (148) multipolygon_text_m ::= WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==148);
      /* (149) multipolygon_text_zm ::= WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==149);
      /* (158) geometry_text ::= point */ yytestcase(yyruleno==158);
      /* (159) geometry_text ::= multipoint */ yytestcase(yyruleno==159);
      /* (160) geometry_text ::= linestring */ yytestcase(yyruleno==160);
      /* (161) geometry_text ::= multilinestring */ yytestcase(yyruleno==161);
      /* (162) geometry_text ::= polygon */ yytestcase(yyruleno==162);
      /* (163) geometry_text ::= multipolygon */ yytestcase(yyruleno==163);
      /* (164) geometry_text_repeated ::= */ yytestcase(yyruleno==164);
      /* (165) geometry_text_repeated ::= WKT_COMMA geometry_text geometry_text_repeated */ yytestcase(yyruleno==165);
      /* (166) geometry_text_z ::= point_z */ yytestcase(yyruleno==166);
      /* (167) geometry_text_z ::= multipoint_z */ yytestcase(yyruleno==167);
      /* (168) geometry_text_z ::= linestring_z */ yytestcase(yyruleno==168);
      /* (169) geometry_text_z ::= multilinestring_z */ yytestcase(yyruleno==169);
      /* (170) geometry_text_z ::= polygon_z */ yytestcase(yyruleno==170);
      /* (171) geometry_text_z ::= multipolygon_z */ yytestcase(yyruleno==171);
      /* (172) geometry_text_z_repeated ::= */ yytestcase(yyruleno==172);
      /* (173) geometry_text_z_repeated ::= WKT_COMMA geometry_text_z geometry_text_z_repeated */ yytestcase(yyruleno==173);
      /* (174) geometry_text_m ::= point_m */ yytestcase(yyruleno==174);
      /* (175) geometry_text_m ::= multipoint_m */ yytestcase(yyruleno==175);
      /* (176) geometry_text_m ::= linestring_m */ yytestcase(yyruleno==176);
      /* (177) geometry_text_m ::= multilinestring_m */ yytestcase(yyruleno==177);
      /* (178) geometry_text_m ::= polygon_m */ yytestcase(yyruleno==178);
      /* (179) geometry_text_m ::= multipolygon_m */ yytestcase(yyruleno==179);
      /* (180) geometry_text_m_repeated ::= */ yytestcase(yyruleno==180);
      /* (181) geometry_text_m_repeated ::= WKT_COMMA geometry_text_m geometry_text_m_repeated */ yytestcase(yyruleno==181);
      /* (182) geometry_text_zm ::= point_zm */ yytestcase(yyruleno==182);
      /* (183) geometry_text_zm ::= multipoint_zm */ yytestcase(yyruleno==183);
      /* (184) geometry_text_zm ::= linestring_zm */ yytestcase(yyruleno==184);
      /* (185) geometry_text_zm ::= multilinestring_zm */ yytestcase(yyruleno==185);
      /* (186) geometry_text_zm ::= polygon_zm */ yytestcase(yyruleno==186);
      /* (187) geometry_text_zm ::= multipolygon_zm */ yytestcase(yyruleno==187);
      /* (188) geometry_text_zm_repeated ::= */ yytestcase(yyruleno==188);
      /* (189) geometry_text_zm_repeated ::= WKT_COMMA geometry_text_zm geometry_text_zm_repeated */ yytestcase(yyruleno==189);
      /* (190) geometrycollection_text ::= WKT_LPAREN geometry_text geometry_text_repeated WKT_RPAREN */ yytestcase(yyruleno==190);
      /* (191) geometrycollection_text_z ::= WKT_LPAREN geometry_text_z geometry_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==191);
      /* (192) geometrycollection_text_m ::= WKT_LPAREN geometry_text_m geometry_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==192);
      /* (193) geometrycollection_text_zm ::= WKT_LPAREN geometry_text_zm geometry_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==193);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)

    result->parser_error = true;
#ifdef SHAPES_VERBOSE
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
        int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
        if (a < YYNSTATE + YYNRULE) {
            printf("possible token: %s\n", yyTokenName[i]);
        }
    }
#endif
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif


}  // namespace shapes
}  // namespace simo

// #include <simo/io/wkt_lexer.hpp>
/* Generated by re2c 1.1.1 on Sat Jun 22 16:03:54 2019 */


#include <ciso646>
#include <iostream>
// #include <simo/io/wkt_token.hpp>


namespace simo
{
namespace shapes
{

/*!
 * @brief A wkt lexer
 * @ingroup wkt
 *
 * @since 0.0.1
 */
class wkt_lexer
{
  public:

    /*!
     * @brief creates a wkt lexer from the given source
     * @param source the source string
     *
     * @since 0.0.1
     */
    wkt_lexer(const std::string& source)
            : content(source)
    {
        start = cursor = source.c_str();
        limit          = start + source.size();
    }

    /*!
     * @brief scan the next token
     * @return the numeric token identifier
     *
     * @since 0.0.1
     */
    int scan()
    {

        /// pointer for backtracking information
        const char* marker = nullptr;

        start = cursor;

        
{
	char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128,   0,   0, 128,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *cursor;
	if (yych <= 'D') {
		if (yych <= '\'') {
			if (yych <= '\f') {
				if (yych <= 0x00) goto shapes_wkt_lexer_2;
				if (yych <= 0x08) goto shapes_wkt_lexer_4;
				if (yych <= '\n') goto shapes_wkt_lexer_6;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= '\r') goto shapes_wkt_lexer_6;
				if (yych == ' ') goto shapes_wkt_lexer_6;
				goto shapes_wkt_lexer_4;
			}
		} else {
			if (yych <= ',') {
				if (yych <= '(') goto shapes_wkt_lexer_8;
				if (yych <= ')') goto shapes_wkt_lexer_10;
				if (yych <= '+') goto shapes_wkt_lexer_4;
				goto shapes_wkt_lexer_12;
			} else {
				if (yych <= '/') {
					if (yych <= '-') goto shapes_wkt_lexer_14;
					goto shapes_wkt_lexer_4;
				} else {
					if (yych <= '0') goto shapes_wkt_lexer_15;
					if (yych <= '9') goto shapes_wkt_lexer_17;
					goto shapes_wkt_lexer_4;
				}
			}
		}
	} else {
		if (yych <= 'd') {
			if (yych <= 'K') {
				if (yych <= 'E') goto shapes_wkt_lexer_19;
				if (yych == 'G') goto shapes_wkt_lexer_20;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= 'M') {
					if (yych <= 'L') goto shapes_wkt_lexer_21;
					goto shapes_wkt_lexer_22;
				} else {
					if (yych == 'P') goto shapes_wkt_lexer_23;
					goto shapes_wkt_lexer_4;
				}
			}
		} else {
			if (yych <= 'k') {
				if (yych <= 'e') goto shapes_wkt_lexer_19;
				if (yych == 'g') goto shapes_wkt_lexer_20;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= 'm') {
					if (yych <= 'l') goto shapes_wkt_lexer_21;
					goto shapes_wkt_lexer_22;
				} else {
					if (yych == 'p') goto shapes_wkt_lexer_23;
					goto shapes_wkt_lexer_4;
				}
			}
		}
	}
shapes_wkt_lexer_2:
	++cursor;
	{ return WKT_END_OF_INPUT; }
shapes_wkt_lexer_4:
	++cursor;
shapes_wkt_lexer_5:
	{ return WKT_PARSE_ERROR; }
shapes_wkt_lexer_6:
	++cursor;
	{ return scan(); }
shapes_wkt_lexer_8:
	++cursor;
	{ return WKT_LPAREN; }
shapes_wkt_lexer_10:
	++cursor;
	{ return WKT_RPAREN; }
shapes_wkt_lexer_12:
	++cursor;
	{ return WKT_COMMA; }
shapes_wkt_lexer_14:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_5;
	if (yych <= '0') goto shapes_wkt_lexer_15;
	if (yych <= '9') goto shapes_wkt_lexer_17;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_15:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= 'D') {
		if (yych == '.') goto shapes_wkt_lexer_24;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_26;
		if (yych == 'e') goto shapes_wkt_lexer_26;
	}
shapes_wkt_lexer_16:
	{ return WKT_NUM; }
shapes_wkt_lexer_17:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yybm[0+yych] & 64) {
		goto shapes_wkt_lexer_17;
	}
	if (yych <= 'D') {
		if (yych == '.') goto shapes_wkt_lexer_24;
		goto shapes_wkt_lexer_16;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_26;
		if (yych == 'e') goto shapes_wkt_lexer_26;
		goto shapes_wkt_lexer_16;
	}
shapes_wkt_lexer_19:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'M') goto shapes_wkt_lexer_27;
	if (yych == 'm') goto shapes_wkt_lexer_27;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_20:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'E') goto shapes_wkt_lexer_28;
	if (yych == 'e') goto shapes_wkt_lexer_28;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_21:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'I') goto shapes_wkt_lexer_29;
	if (yych == 'i') goto shapes_wkt_lexer_29;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_22:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'U') goto shapes_wkt_lexer_30;
	if (yych == 'u') goto shapes_wkt_lexer_30;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_23:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'O') goto shapes_wkt_lexer_31;
	if (yych == 'o') goto shapes_wkt_lexer_31;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_24:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_25;
	if (yych <= '9') goto shapes_wkt_lexer_32;
shapes_wkt_lexer_25:
	cursor = marker;
	if (yyaccept <= 4) {
		if (yyaccept <= 2) {
			if (yyaccept <= 1) {
				if (yyaccept == 0) {
					goto shapes_wkt_lexer_16;
				} else {
					goto shapes_wkt_lexer_5;
				}
			} else {
				goto shapes_wkt_lexer_55;
			}
		} else {
			if (yyaccept == 3) {
				goto shapes_wkt_lexer_75;
			} else {
				goto shapes_wkt_lexer_96;
			}
		}
	} else {
		if (yyaccept <= 6) {
			if (yyaccept == 5) {
				goto shapes_wkt_lexer_99;
			} else {
				goto shapes_wkt_lexer_123;
			}
		} else {
			if (yyaccept == 7) {
				goto shapes_wkt_lexer_138;
			} else {
				goto shapes_wkt_lexer_150;
			}
		}
	}
shapes_wkt_lexer_26:
	yych = *++cursor;
	if (yych <= ',') {
		if (yych == '+') goto shapes_wkt_lexer_34;
		goto shapes_wkt_lexer_25;
	} else {
		if (yych <= '-') goto shapes_wkt_lexer_34;
		if (yych <= '/') goto shapes_wkt_lexer_25;
		if (yych <= '9') goto shapes_wkt_lexer_35;
		goto shapes_wkt_lexer_25;
	}
shapes_wkt_lexer_27:
	yych = *++cursor;
	if (yych == 'P') goto shapes_wkt_lexer_37;
	if (yych == 'p') goto shapes_wkt_lexer_37;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_28:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_38;
	if (yych == 'o') goto shapes_wkt_lexer_38;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_29:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_39;
	if (yych == 'n') goto shapes_wkt_lexer_39;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_30:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_40;
	if (yych == 'l') goto shapes_wkt_lexer_40;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_31:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych == 'I') goto shapes_wkt_lexer_41;
		if (yych <= 'K') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_42;
	} else {
		if (yych <= 'i') {
			if (yych <= 'h') goto shapes_wkt_lexer_25;
			goto shapes_wkt_lexer_41;
		} else {
			if (yych == 'l') goto shapes_wkt_lexer_42;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_32:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= 'D') {
		if (yych <= '/') goto shapes_wkt_lexer_16;
		if (yych <= '9') goto shapes_wkt_lexer_32;
		goto shapes_wkt_lexer_16;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_26;
		if (yych == 'e') goto shapes_wkt_lexer_26;
		goto shapes_wkt_lexer_16;
	}
shapes_wkt_lexer_34:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_25;
	if (yych >= ':') goto shapes_wkt_lexer_25;
shapes_wkt_lexer_35:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_16;
	if (yych <= '9') goto shapes_wkt_lexer_35;
	goto shapes_wkt_lexer_16;
shapes_wkt_lexer_37:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_43;
	if (yych == 't') goto shapes_wkt_lexer_43;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_38:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_44;
	if (yych == 'm') goto shapes_wkt_lexer_44;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_39:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_45;
	if (yych == 'e') goto shapes_wkt_lexer_45;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_40:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_46;
	if (yych == 't') goto shapes_wkt_lexer_46;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_41:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_47;
	if (yych == 'n') goto shapes_wkt_lexer_47;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_42:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_48;
	if (yych == 'y') goto shapes_wkt_lexer_48;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_43:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_49;
	if (yych == 'y') goto shapes_wkt_lexer_49;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_44:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_51;
	if (yych == 'e') goto shapes_wkt_lexer_51;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_45:
	yych = *++cursor;
	if (yych == 'S') goto shapes_wkt_lexer_52;
	if (yych == 's') goto shapes_wkt_lexer_52;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_46:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_53;
	if (yych == 'i') goto shapes_wkt_lexer_53;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_47:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_54;
	if (yych == 't') goto shapes_wkt_lexer_54;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_48:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_56;
	if (yych == 'g') goto shapes_wkt_lexer_56;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_49:
	++cursor;
	{ return WKT_EMPTY_SET; }
shapes_wkt_lexer_51:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_57;
	if (yych == 't') goto shapes_wkt_lexer_57;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_52:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_58;
	if (yych == 't') goto shapes_wkt_lexer_58;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_53:
	yych = *++cursor;
	if (yych <= 'P') {
		if (yych == 'L') goto shapes_wkt_lexer_59;
		if (yych <= 'O') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_60;
	} else {
		if (yych <= 'l') {
			if (yych <= 'k') goto shapes_wkt_lexer_25;
			goto shapes_wkt_lexer_59;
		} else {
			if (yych == 'p') goto shapes_wkt_lexer_60;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_54:
	yyaccept = 2;
	yych = *(marker = ++cursor);
	if (yybm[0+yych] & 128) {
		goto shapes_wkt_lexer_61;
	}
	if (yych <= 'Z') {
		if (yych == 'M') goto shapes_wkt_lexer_63;
		if (yych >= 'Z') goto shapes_wkt_lexer_65;
	} else {
		if (yych <= 'm') {
			if (yych >= 'm') goto shapes_wkt_lexer_63;
		} else {
			if (yych == 'z') goto shapes_wkt_lexer_65;
		}
	}
shapes_wkt_lexer_55:
	{ return WKT_POINT_TAGGED_TEXT; }
shapes_wkt_lexer_56:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_67;
	if (yych == 'o') goto shapes_wkt_lexer_67;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_57:
	yych = *++cursor;
	if (yych == 'R') goto shapes_wkt_lexer_68;
	if (yych == 'r') goto shapes_wkt_lexer_68;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_58:
	yych = *++cursor;
	if (yych == 'R') goto shapes_wkt_lexer_69;
	if (yych == 'r') goto shapes_wkt_lexer_69;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_59:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_70;
	if (yych == 'i') goto shapes_wkt_lexer_70;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_60:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_71;
	if (yych == 'o') goto shapes_wkt_lexer_71;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_61:
	yych = *++cursor;
	if (yybm[0+yych] & 128) {
		goto shapes_wkt_lexer_61;
	}
	if (yych <= 'Z') {
		if (yych == 'M') goto shapes_wkt_lexer_63;
		if (yych <= 'Y') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_65;
	} else {
		if (yych <= 'm') {
			if (yych <= 'l') goto shapes_wkt_lexer_25;
		} else {
			if (yych == 'z') goto shapes_wkt_lexer_65;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_63:
	++cursor;
	{ return WKT_POINT_M_TAGGED_TEXT; }
shapes_wkt_lexer_65:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_72;
	if (yych == 'm') goto shapes_wkt_lexer_72;
	{ return WKT_POINT_Z_TAGGED_TEXT; }
shapes_wkt_lexer_67:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_74;
	if (yych == 'n') goto shapes_wkt_lexer_74;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_68:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_76;
	if (yych == 'y') goto shapes_wkt_lexer_76;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_69:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_77;
	if (yych == 'i') goto shapes_wkt_lexer_77;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_70:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_78;
	if (yych == 'n') goto shapes_wkt_lexer_78;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_71:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych == 'I') goto shapes_wkt_lexer_79;
		if (yych <= 'K') goto shapes_wkt_lexer_25;
		goto shapes_wkt_lexer_80;
	} else {
		if (yych <= 'i') {
			if (yych <= 'h') goto shapes_wkt_lexer_25;
			goto shapes_wkt_lexer_79;
		} else {
			if (yych == 'l') goto shapes_wkt_lexer_80;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_72:
	++cursor;
	{ return WKT_POINT_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_74:
	yyaccept = 3;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_75;
			if (yych <= '\n') goto shapes_wkt_lexer_81;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_81;
			if (yych == ' ') goto shapes_wkt_lexer_81;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_83;
			if (yych == 'Z') goto shapes_wkt_lexer_85;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_83;
			if (yych == 'z') goto shapes_wkt_lexer_85;
		}
	}
shapes_wkt_lexer_75:
	{ return WKT_POLYGON_TAGGED_TEXT; }
shapes_wkt_lexer_76:
	yych = *++cursor;
	if (yych == 'C') goto shapes_wkt_lexer_87;
	if (yych == 'c') goto shapes_wkt_lexer_87;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_77:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_88;
	if (yych == 'n') goto shapes_wkt_lexer_88;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_78:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_89;
	if (yych == 'e') goto shapes_wkt_lexer_89;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_79:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_90;
	if (yych == 'n') goto shapes_wkt_lexer_90;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_80:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_91;
	if (yych == 'y') goto shapes_wkt_lexer_91;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_81:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_81;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_81;
			if (yych == ' ') goto shapes_wkt_lexer_81;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_83;
			if (yych == 'Z') goto shapes_wkt_lexer_85;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_83;
			if (yych == 'z') goto shapes_wkt_lexer_85;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_83:
	++cursor;
	{ return WKT_POLYGON_M_TAGGED_TEXT; }
shapes_wkt_lexer_85:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_92;
	if (yych == 'm') goto shapes_wkt_lexer_92;
	{ return WKT_POLYGON_Z_TAGGED_TEXT; }
shapes_wkt_lexer_87:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_94;
	if (yych == 'o') goto shapes_wkt_lexer_94;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_88:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_95;
	if (yych == 'g') goto shapes_wkt_lexer_95;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_89:
	yych = *++cursor;
	if (yych == 'S') goto shapes_wkt_lexer_97;
	if (yych == 's') goto shapes_wkt_lexer_97;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_90:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_98;
	if (yych == 't') goto shapes_wkt_lexer_98;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_91:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_100;
	if (yych == 'g') goto shapes_wkt_lexer_100;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_92:
	++cursor;
	{ return WKT_POLYGON_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_94:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_101;
	if (yych == 'l') goto shapes_wkt_lexer_101;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_95:
	yyaccept = 4;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_96;
			if (yych <= '\n') goto shapes_wkt_lexer_102;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_102;
			if (yych == ' ') goto shapes_wkt_lexer_102;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_104;
			if (yych == 'Z') goto shapes_wkt_lexer_106;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_104;
			if (yych == 'z') goto shapes_wkt_lexer_106;
		}
	}
shapes_wkt_lexer_96:
	{ return WKT_LINESTRING_TAGGED_TEXT; }
shapes_wkt_lexer_97:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_108;
	if (yych == 't') goto shapes_wkt_lexer_108;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_98:
	yyaccept = 5;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_99;
			if (yych <= '\n') goto shapes_wkt_lexer_109;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_109;
			if (yych == ' ') goto shapes_wkt_lexer_109;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_111;
			if (yych == 'Z') goto shapes_wkt_lexer_113;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_111;
			if (yych == 'z') goto shapes_wkt_lexer_113;
		}
	}
shapes_wkt_lexer_99:
	{ return WKT_MULTIPOINT_TAGGED_TEXT; }
shapes_wkt_lexer_100:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_115;
	if (yych == 'o') goto shapes_wkt_lexer_115;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_101:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_116;
	if (yych == 'l') goto shapes_wkt_lexer_116;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_102:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_102;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_102;
			if (yych == ' ') goto shapes_wkt_lexer_102;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_104;
			if (yych == 'Z') goto shapes_wkt_lexer_106;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_104;
			if (yych == 'z') goto shapes_wkt_lexer_106;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_104:
	++cursor;
	{ return WKT_LINESTRING_M_TAGGED_TEXT; }
shapes_wkt_lexer_106:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_117;
	if (yych == 'm') goto shapes_wkt_lexer_117;
	{ return WKT_LINESTRING_Z_TAGGED_TEXT; }
shapes_wkt_lexer_108:
	yych = *++cursor;
	if (yych == 'R') goto shapes_wkt_lexer_119;
	if (yych == 'r') goto shapes_wkt_lexer_119;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_109:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_109;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_109;
			if (yych == ' ') goto shapes_wkt_lexer_109;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_111;
			if (yych == 'Z') goto shapes_wkt_lexer_113;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_111;
			if (yych == 'z') goto shapes_wkt_lexer_113;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_111:
	++cursor;
	{ return WKT_MULTIPOINT_M_TAGGED_TEXT; }
shapes_wkt_lexer_113:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_120;
	if (yych == 'm') goto shapes_wkt_lexer_120;
	{ return WKT_MULTIPOINT_Z_TAGGED_TEXT; }
shapes_wkt_lexer_115:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_122;
	if (yych == 'n') goto shapes_wkt_lexer_122;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_116:
	yych = *++cursor;
	if (yych == 'E') goto shapes_wkt_lexer_124;
	if (yych == 'e') goto shapes_wkt_lexer_124;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_117:
	++cursor;
	{ return WKT_LINESTRING_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_119:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_125;
	if (yych == 'i') goto shapes_wkt_lexer_125;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_120:
	++cursor;
	{ return WKT_MULTIPOINT_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_122:
	yyaccept = 6;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_123;
			if (yych <= '\n') goto shapes_wkt_lexer_126;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_126;
			if (yych == ' ') goto shapes_wkt_lexer_126;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_128;
			if (yych == 'Z') goto shapes_wkt_lexer_130;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_128;
			if (yych == 'z') goto shapes_wkt_lexer_130;
		}
	}
shapes_wkt_lexer_123:
	{ return WKT_MULTIPOLYGON_TAGGED_TEXT; }
shapes_wkt_lexer_124:
	yych = *++cursor;
	if (yych == 'C') goto shapes_wkt_lexer_132;
	if (yych == 'c') goto shapes_wkt_lexer_132;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_125:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_133;
	if (yych == 'n') goto shapes_wkt_lexer_133;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_126:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_126;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_126;
			if (yych == ' ') goto shapes_wkt_lexer_126;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_128;
			if (yych == 'Z') goto shapes_wkt_lexer_130;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_128;
			if (yych == 'z') goto shapes_wkt_lexer_130;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_128:
	++cursor;
	{ return WKT_MULTIPOLYGON_M_TAGGED_TEXT; }
shapes_wkt_lexer_130:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_134;
	if (yych == 'm') goto shapes_wkt_lexer_134;
	{ return WKT_MULTIPOLYGON_Z_TAGGED_TEXT; }
shapes_wkt_lexer_132:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_136;
	if (yych == 't') goto shapes_wkt_lexer_136;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_133:
	yych = *++cursor;
	if (yych == 'G') goto shapes_wkt_lexer_137;
	if (yych == 'g') goto shapes_wkt_lexer_137;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_134:
	++cursor;
	{ return WKT_MULTIPOLYGON_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_136:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_139;
	if (yych == 'i') goto shapes_wkt_lexer_139;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_137:
	yyaccept = 7;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_138;
			if (yych <= '\n') goto shapes_wkt_lexer_140;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_140;
			if (yych == ' ') goto shapes_wkt_lexer_140;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_142;
			if (yych == 'Z') goto shapes_wkt_lexer_144;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_142;
			if (yych == 'z') goto shapes_wkt_lexer_144;
		}
	}
shapes_wkt_lexer_138:
	{ return WKT_MULTILINESTRING_TAGGED_TEXT; }
shapes_wkt_lexer_139:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_146;
	if (yych == 'o') goto shapes_wkt_lexer_146;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_140:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_140;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_140;
			if (yych == ' ') goto shapes_wkt_lexer_140;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_142;
			if (yych == 'Z') goto shapes_wkt_lexer_144;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_142;
			if (yych == 'z') goto shapes_wkt_lexer_144;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_142:
	++cursor;
	{ return WKT_MULTILINESTRING_M_TAGGED_TEXT; }
shapes_wkt_lexer_144:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_147;
	if (yych == 'm') goto shapes_wkt_lexer_147;
	{ return WKT_MULTILINESTRING_Z_TAGGED_TEXT; }
shapes_wkt_lexer_146:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_149;
	if (yych == 'n') goto shapes_wkt_lexer_149;
	goto shapes_wkt_lexer_25;
shapes_wkt_lexer_147:
	++cursor;
	{ return WKT_MULTILINESTRING_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_149:
	yyaccept = 8;
	yych = *(marker = ++cursor);
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_150;
			if (yych <= '\n') goto shapes_wkt_lexer_151;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_151;
			if (yych == ' ') goto shapes_wkt_lexer_151;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_153;
			if (yych == 'Z') goto shapes_wkt_lexer_155;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_153;
			if (yych == 'z') goto shapes_wkt_lexer_155;
		}
	}
shapes_wkt_lexer_150:
	{ return WKT_GEOMETRYCOLLECTION_TAGGED_TEXT; }
shapes_wkt_lexer_151:
	yych = *++cursor;
	if (yych <= 'L') {
		if (yych <= '\f') {
			if (yych <= 0x08) goto shapes_wkt_lexer_25;
			if (yych <= '\n') goto shapes_wkt_lexer_151;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= '\r') goto shapes_wkt_lexer_151;
			if (yych == ' ') goto shapes_wkt_lexer_151;
			goto shapes_wkt_lexer_25;
		}
	} else {
		if (yych <= 'l') {
			if (yych <= 'M') goto shapes_wkt_lexer_153;
			if (yych == 'Z') goto shapes_wkt_lexer_155;
			goto shapes_wkt_lexer_25;
		} else {
			if (yych <= 'm') goto shapes_wkt_lexer_153;
			if (yych == 'z') goto shapes_wkt_lexer_155;
			goto shapes_wkt_lexer_25;
		}
	}
shapes_wkt_lexer_153:
	++cursor;
	{ return WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT; }
shapes_wkt_lexer_155:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_157;
	if (yych == 'm') goto shapes_wkt_lexer_157;
	{ return WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT; }
shapes_wkt_lexer_157:
	++cursor;
	{ return WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT; }
}

    }

    /*!
     * @brief returns the current token string
     * @return the token string
     *
     * @since 0.0.1
     */
    std::string get_token() const
    {
        return std::string(reinterpret_cast<const char*>(start), static_cast<size_t>(cursor - start));
    }

    /*!
     * @brief returns the current reading position
     * @return the index position
     *
     * @since 0.0.1
     */
    size_t get_position()
    {
        return static_cast<size_t>(start - content.c_str());
    }

  private:
    /// the source string
    std::string content;

    /// pointer to the beginning of the current token
    const char* start = nullptr;

    /// pointer to the current token
    const char* cursor = nullptr;

    /// pointer to the end of the buffer
    const char* limit = nullptr;
};

}  // namespace shapes
}  // namespace simo

namespace simo
{
namespace shapes
{

/*!
 * @brief a wkt reader
 * @ingroup wkt
 *
 * @since 0.0.1
 */
class wkt_reader
{
  public:
    /*!
     * @brief creates a wkt reader
     *
     * @since 0.0.1
     */
    wkt_reader()
        : m_parser(ParseAlloc(malloc))
    {
    }

    /// destructor
    ~wkt_reader()
    {
        ParseFree(m_parser, free);
    }

    /*!
     * @brief parse the given wkt string
     *
     * @param wkt the wkt string
     * @return a wkt result object
     *
     * @since 0.0.1
     */
    wkt_result read(const std::string& wkt)
    {
        wkt_lexer lexer(wkt);
        wkt_result result{};

#ifdef SHAPES_VERBOSE
        static char WKT_TRACE_PREFIX[] = "[shapes] ";
        ParseTrace(stdout, WKT_TRACE_PREFIX);
#endif
        while (true)
        {
            int token = lexer.scan();
#ifdef SHAPES_VERBOSE
            std::cout << "--> " << lexer.get_token() << '\n';
#endif
            if (token == WKT_END_OF_INPUT)
            {
                break;
            }

            if (token == WKT_PARSE_ERROR)
            {
                throw exceptions::parse_error("lexer error at line " + std::to_string(lexer.get_position()));
            }

            if (token == WKT_NUM)
            {
                Parse(m_parser, token, std::stod(lexer.get_token()), &result);
            }
            else
            {
                Parse(m_parser, token, 0, &result);
            }

            if (result.parser_error)
            {
                throw exceptions::parse_error("parser error for token " + lexer.get_token());
            }
        }

        Parse(m_parser, 0, 0, &result);
        if (result.parser_error)
        {
            throw exceptions::parse_error("parser error");
        }
        normalize_result(wkt, result);
        return result;
    }

  private:
    static std::string compact_upper(const std::string& text)
    {
        std::string res;
        res.reserve(text.size());
        for (char c : text)
        {
            if (std::isspace(static_cast<unsigned char>(c)))
            {
                continue;
            }
            res.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
        }
        return res;
    }

    static std::vector<std::size_t> multipolygon_polygon_offsets(const std::string& wkt)
    {
        std::vector<std::size_t> res;
        auto first_paren = wkt.find('(');
        if (first_paren == std::string::npos)
        {
            return res;
        }

        int depth = 0;
        std::size_t ring_count = 0;
        for (auto it = wkt.begin() + static_cast<std::ptrdiff_t>(first_paren); it != wkt.end(); ++it)
        {
            if (*it == '(')
            {
                ++depth;
            }
            else if (*it == ')')
            {
                if (depth == 3)
                {
                    ++ring_count;
                }
                else if (depth == 2)
                {
                    res.push_back(ring_count);
                }
                --depth;
            }
        }
        return res;
    }

    static void normalize_result(const std::string& wkt, wkt_result& result)
    {
        auto& data = result.data;
        const auto compact = compact_upper(wkt);

        if (utils::is_point(data.geom_type) and compact.find("EMPTY") != std::string::npos)
        {
            data.coords.clear();
        }

        if (utils::is_linestring(data.geom_type) or utils::is_multilinestring(data.geom_type))
        {
            return;
        }

        if (utils::is_polygon(data.geom_type) and not data.ring_offsets.empty() and data.polygon_offsets.empty())
        {
            data.polygon_offsets.push_back(data.ring_offsets.size());
        }

        if (utils::is_multipolygon(data.geom_type) and data.polygon_offsets.empty())
        {
            data.polygon_offsets = multipolygon_polygon_offsets(wkt);
        }

        if (utils::get_geom_type(data.geom_type) == geometry_type::GEOMETRYCOLLECTION)
        {
            data.coords.clear();
            data.line_offsets.clear();
            data.ring_offsets.clear();
            data.polygon_offsets.clear();
        }
    }

    /// pointer to the parser
    void* m_parser = nullptr;
};

}  // namespace shapes
}  // namespace simo

// #include <simo/io/polyline.hpp>


#include <ciso646>
// #include <simo/exceptions.hpp>


namespace simo
{
namespace shapes
{
namespace polyline
{

/// the chunk size
constexpr static const int32_t CHUNK_SIZE = 5;

/// a mask to extract the chunks
constexpr static const int32_t CHUNK_MASK = 0x1f;

/// threshold used to signal another value follows or not
constexpr static const int32_t CHUNK_THRESHOLD = 0x20;

/// the ascii offset to apply
constexpr static const int32_t ASCII_OFFSET = 63;

/*!
 * @brief Encode a polyline coordinate
 * @param coord the coordinate value
 * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 * @return the encoded coordinate
 *
 * @since 0.0.1
 */
std::string encode(double coord, int32_t precision = 5)
{
    assert(precision >= 0);
    double pow10 = std::pow(10, precision);
    auto value   = static_cast<int32_t>(std::round(coord * pow10));
    value <<= 1;
    if (coord < 0)
    {
        value = ~value;
    }
    std::string res;
    while (value >= CHUNK_THRESHOLD)
    {
        int32_t ch = ((value & CHUNK_MASK) | CHUNK_THRESHOLD) + ASCII_OFFSET;
        res += static_cast<char>(ch);
        value >>= CHUNK_SIZE;
    }
    res += static_cast<char>(value + ASCII_OFFSET);
    return res;
}

/*!
 * @brief Decode a section of the polyline string
 * @param text the polyline encoded string
 * @param index the current reading position
 * @return an integer with the decoded delta value
 *
 * @since 0.0.1
 */
int32_t advance(const std::string& text, size_t& index)
{
    int32_t res   = 0;
    int32_t shift = 0;
    char ch       = 0;
    while (index < text.size())
    {
        ch = text[index++] - ASCII_OFFSET;
        res |= (ch & CHUNK_MASK) << shift;
        shift += CHUNK_SIZE;
        if (ch < CHUNK_THRESHOLD)
        {
            break;
        }
    }
    if (res & 1)
    {
        res = ~res;
    }
    res >>= 1;
    return res;
}

/*!
 * @brief Decode a polyline string
 * @param text the polyline encoded string
 * @param precision the coordinates precision
 * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 * @return the decoded coordinates
 *
 * @since 0.0.1
 */
std::vector<double> decode(const std::string& text, int32_t precision = 5)
{
    assert(precision >= 0);
    double pow10 = std::pow(10, precision);
    std::vector<double> res;
    res.reserve(text.size() / 3);
    size_t index = 0;
    int32_t y    = 0;
    int32_t x    = 0;
    while (index < text.size())
    {
        y += advance(text, index);
        x += advance(text, index);
        res.push_back(x / pow10);
        res.push_back(y / pow10);
    }
    return res;
}

}  // namespace polyline
}  // namespace shapes
}  // namespace simo

namespace simo
{
namespace shapes
{

#ifdef __GNUC__
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpedantic"
#endif

#ifdef __clang__
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#    pragma clang diagnostic ignored "-Wnested-anon-types"
#endif

#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable : 4201)
#endif

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
class basic_point : public basic_geometry<basic_point<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point;
    using coord_type           = T;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 2;

    union
    {
        struct
        {
            T x;
            T y;
        };

        struct
        {
            T lng;
            T lat;
        };

        T coords[N];
    };

    bool m_empty;

    /*!
     * @brief Creates a empty point
     */
    basic_point()
        : x(0), y(0), m_empty(true) {}

    /*!
     * @brief Creates a point from the given coordinates
     * @param x the x-coordinate
     * @param y the y-coordinate
     */
    basic_point(T x, T y)
        : x(x), y(y), m_empty(false) {}

    explicit basic_point(coord_iterator begin, coord_iterator end)
        : x(0), y(0), m_empty(true)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), m_empty(true)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    size_type size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    reference operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
        return lhs.x == rhs.x and lhs.y == rhs.y;
    }

    friend bool operator!=(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    // polyline

    static basic_point<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        auto coords = polyline::decode(polyline, precision);
        if (coords.size() > N)
        {
            throw exceptions::parse_error("too many points");
        }
        return {coords[0], coords[1]};
    }

    std::string polyline(std::int32_t precision = 5) const
    {
        return polyline::encode(lat, precision) + polyline::encode(lng, precision);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

  private:
    /// for allow basic_geometry to access basic_point private members
    friend class basic_geometry<basic_point<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINT;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "{\"type\":\"Point\",\"coordinates\":[]}";
            return ss.str();
        }
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINT)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "POINT EMPTY";
            return ss.str();
        }
        ss << "POINT "
           << "(" << x << " " << y << ")";
        return ss.str();
    }
};

// xyz

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
class basic_point_z : public basic_geometry<basic_point_z<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point_z;
    using coord_type           = value_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 3;

    union
    {
        struct
        {
            T x;
            T y;
            T z;
        };

        struct
        {
            T lng;
            T lat;
            T height;
        };

        T coords[N];
    };

    bool m_empty;

    basic_point_z()
        : x(0), y(0), z(0), m_empty(true) {}

    basic_point_z(T x, T y, T z)
        : x(x), y(y), z(z), m_empty(false) {}

    explicit basic_point_z(coord_iterator begin, coord_iterator end)
        : x(0), y(0), z(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point_z(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), z(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    std::size_t size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z;
    }

    friend bool operator!=(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

  private:
    /// for allow basic_geometry to access basic_point_z private members
    friend class basic_geometry<basic_point_z<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINTZ;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point_z<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();

            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1)), static_cast<T>(coords.at(2))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "{\"type\":\"Point\",\"coordinates\":[]}";
            return ss.str();
        }
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "," << z << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point_z<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINTZ)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1], data.coords[2]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "POINT Z EMPTY";
            return ss.str();
        }
        ss << "POINT Z "
           << "(" << x << " " << y << " " << z << ")";
        return ss.str();
    }
};

// xym

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
class basic_point_m : public basic_geometry<basic_point_m<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point_m;
    using coord_type           = value_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 3;

    union
    {
        struct
        {
            T x;
            T y;
            T m;
        };

        struct
        {
            T lng;
            T lat;
            T measure;
        };

        T coords[N];
    };

    bool m_empty;

    basic_point_m()
        : x(0), y(0), m(0), m_empty(true) {}

    basic_point_m(T x, T y, T m)
        : x(x), y(y), m(m), m_empty(false) {}

    explicit basic_point_m(coord_iterator begin, coord_iterator end)
        : x(0), y(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point_m(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    std::size_t size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.m == rhs.m;
    }

    friend bool operator!=(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

  private:
    /// for allow basic_geometry to access basic_point_m private members
    friend class basic_geometry<basic_point_m<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINTM;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point_m<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();

            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1)), static_cast<T>(coords.at(2))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "{\"type\":\"Point\",\"coordinates\":[]}";
            return ss.str();
        }
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "," << m << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point_m<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINTM)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1], data.coords[2]};
    }

    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "POINT M EMPTY";
            return ss.str();
        }
        ss << "POINT M "
           << "(" << x << " " << y << " " << m << ")";
        return ss.str();
    }
};

// xyzm

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
class basic_point_zm : public basic_geometry<basic_point_zm<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point_zm;
    using coord_type           = value_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 4;

    union
    {
        struct
        {
            T x;
            T y;
            T z;
            T m;
        };

        struct
        {
            T lng;
            T lat;
            T height;
            T measure;
        };

        T coords[N];
    };

    bool m_empty;

    basic_point_zm()
        : x(0), y(0), z(0), m(0), m_empty(true) {}

    basic_point_zm(T x, T y, T z, T m)
        : x(x), y(y), z(z), m(m), m_empty(false) {}

    explicit basic_point_zm(coord_iterator begin, coord_iterator end)
        : x(0), y(0), z(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point_zm(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), z(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    std::size_t size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z and lhs.m == rhs.m;
    }

    friend bool operator!=(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

  private:
    /// for allow basic_geometry to access basic_point_zm private members
    friend class basic_geometry<basic_point_zm<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINTZM;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point_zm<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();

            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1)), static_cast<T>(coords.at(2)), static_cast<T>(coords.at(3))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "{\"type\":\"Point\",\"coordinates\":[]}";
            return ss.str();
        }
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "," << z << "," << m << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point_zm<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINTZM)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1], data.coords[2], data.coords[3]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        if (m_empty)
        {
            ss << "POINT ZM EMPTY";
            return ss.str();
        }
        ss << "POINT ZM "
           << "(" << x << " " << y << " " << z << " " << m << ")";
        return ss.str();
    }
};

#ifdef __GNUC__
#    pragma GCC diagnostic pop
#endif

#ifdef __clang__
#    pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#    pragma warning(pop)
#endif

template <typename>
struct is_basic_point : std::false_type
{};

template <typename T>
struct is_basic_point<basic_point<T>> : std::true_type
{};

template <typename>
struct is_basic_point_z : std::false_type
{};

template <typename T>
struct is_basic_point_z<basic_point_z<T>> : std::true_type
{};

template <typename>
struct is_basic_point_m : std::false_type
{};

template <typename T>
struct is_basic_point_m<basic_point_m<T>> : std::true_type
{};

template <typename>
struct is_basic_point_zm : std::false_type
{};

template <typename T>
struct is_basic_point_zm<basic_point_zm<T>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo


namespace simo
{
namespace shapes
{

template <class T = double>
using point_t = basic_point<T>;

template <class T = double>
using point_z_t = basic_point_z<T>;

template <class T = double>
using point_m_t = basic_point_m<T>;

template <class T = double>
using point_zm_t = basic_point_zm<T>;

using point    = point_t<double>;
using point_z  = point_z_t<double>;
using point_m  = point_m_t<double>;
using point_zm = point_zm_t<double>;

using Point   = point_t<double>;
using PointZ  = point_z_t<double>;
using PointM  = point_m_t<double>;
using PointZM = point_zm_t<double>;

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/multipoint.hpp>


#include <ciso646>
// #include <simo/geom/detail/multipoint.hpp>


#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
// #include <simo/geom/detail/geometry.hpp>

// #include <simo/geom/detail/bounds.hpp>


namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_multipoint : public std::vector<T, AllocatorType>, public basic_geometry<basic_multipoint<T>>
{
  public:
    using base_type = std::vector<T, AllocatorType>;

    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<T>::iterator;
    using point_const_iterator = typename std::vector<T>::const_iterator;

    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    inline basic_multipoint()
        : base_type() {}

    basic_multipoint(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    explicit basic_multipoint(coord_const_iterator first, coord_const_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    explicit basic_multipoint(coord_iterator first, coord_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    basic_multipoint(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    basic_multipoint(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    // operators

    /*!
     * @param lhs a mulipoint
     * @param rhs a mulipoint
     * @return true if all Point's are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const basic_multipoint<T>& lhs, const basic_multipoint<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    /*!
     * @param lhs a mulipoint
     * @param rhs a mulipoint
     * @return true if at least one Point is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const basic_multipoint<T>& lhs, const basic_multipoint<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

    // polyline

    static basic_multipoint<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        static_assert(is_basic_point<T>::value, "must contain XY points");

        auto coords = polyline::decode(polyline, precision);
        return basic_multipoint<T>(coords.begin(), coords.end());
    }

    std::string polyline(std::int32_t precision = 5) const
    {
        static_assert(is_basic_point<T>::value, "must contain XY points");

        std::string res;
        res.reserve(this->size() * 6);
        double prev_lng = 0;
        double prev_lat = 0;
        for (const auto& p : *this)
        {
            res += polyline::encode(p.lat - prev_lat, precision);
            res += polyline::encode(p.lng - prev_lng, precision);
            prev_lat = p.lat;
            prev_lng = p.lng;
        }
        return res;
    }

  private:
    /// for allow basic_geometry to access basic_multipoint private members
    friend class basic_geometry<basic_multipoint<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_point_z<T>::value)
        {
            return geometry_type::MULTIPOINTZ;
        }
        if (is_basic_point_m<T>::value)
        {
            return geometry_type::MULTIPOINTM;
        }
        if (is_basic_point_zm<T>::value)
        {
            return geometry_type::MULTIPOINTZM;
        }
        return geometry_type::MULTIPOINT;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        return *this[0] == *this[this->size() - 1];
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& p : *this)
        {
            res.extend(p.x, p.y);
        }
        return res;
    }

    // json

    /// @private
    static basic_multipoint<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "MultiPoint")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& coords_array = j.at("coordinates").as_array();
            std::vector<point_type> res;
            res.reserve(coords_array.size());
            for (const auto& coord : coords_array)
            {
                auto point_coords = coord.as_double_array();
                res.emplace_back(point_coords.begin(), point_coords.end());
            }
            return basic_multipoint<T>(res.begin(), res.end());
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"MultiPoint\",\"coordinates\":[";
        int i = 0;
        for (const auto& p : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t j = 0; j < p.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << p.coords[j];
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_multipoint<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multipoint(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_multipoint<T>(result.data.coords.begin(), result.data.coords.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTIPOINT";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        ss << "(";
        int i = 0;
        for (const auto& p : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(";
            for (size_t j = 0; j < p.size(); ++j)
            {
                if (j > 0)
                {
                    ss << " ";
                }
                ss << p.coords[j];
            }
            ss << ")";
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_multipoint : std::false_type
{};

template <typename T>
struct is_basic_multipoint<basic_multipoint<basic_point<T>>> : std::true_type
{};

template <typename>
struct is_basic_multipoint_z : std::false_type
{};

template <typename T>
struct is_basic_multipoint_z<basic_multipoint<basic_point_z<T>>> : std::true_type
{};

template <typename>
struct is_basic_multipoint_m : std::false_type
{};

template <typename T>
struct is_basic_multipoint_m<basic_multipoint<basic_point_m<T>>> : std::true_type
{};

template <typename>
struct is_basic_multipoint_zm : std::false_type
{};

template <typename T>
struct is_basic_multipoint_zm<basic_multipoint<basic_point_zm<T>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo


namespace simo
{
namespace shapes
{

template <class T = double>
using multipoint_t = basic_multipoint<basic_point<T>>;

template <class T = double>
using multipoint_z_t = basic_multipoint<basic_point_z<T>>;

template <class T = double>
using multipoint_m_t = basic_multipoint<basic_point_m<T>>;

template <class T = double>
using multipoint_zm_t = basic_multipoint<basic_point_zm<T>>;

using multipoint    = multipoint_t<double>;
using multipoint_z  = multipoint_z_t<double>;
using multipoint_m  = multipoint_m_t<double>;
using multipoint_zm = multipoint_zm_t<double>;

using MultiPoint   = multipoint_t<double>;
using MultiPointZ  = multipoint_z_t<double>;
using MultiPointM  = multipoint_m_t<double>;
using MultiPointZM = multipoint_zm_t<double>;

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/linestring.hpp>


#include <ciso646>
// #include <simo/geom/detail/linestring.hpp>


#include <ciso646>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>
#include <iomanip>
// #include <simo/geom/detail/geometry.hpp>

// #include <simo/geom/detail/utils.hpp>

// #include <simo/geom/detail/point.hpp>

// #include <simo/geom/detail/bounds.hpp>


namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_linestring : public std::vector<T, AllocatorType>, public basic_geometry<basic_linestring<T>>
{
  public:
    using base_type = std::vector<T, AllocatorType>;

    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<T>::iterator;
    using point_const_iterator = typename std::vector<T>::const_iterator;

    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_linestring()
        : base_type() {}

    basic_linestring(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    explicit basic_linestring(coord_const_iterator first, coord_const_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    explicit basic_linestring(coord_iterator first, coord_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    basic_linestring(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    basic_linestring(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    // operators

    /*!
     * @param lhs a linestring
     * @param rhs a linestring
     * @return true if all points are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const basic_linestring<T>& lhs, const basic_linestring<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    /*!
     * @param lhs a linestring
     * @param rhs a linestring
     * @return true if at least one point is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const basic_linestring<T>& lhs, const basic_linestring<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

    // polyline

    /*!
     * @brief DOCUMENT ME!
     * @param polyline
     * @param precision
     * @return
     *
     * @since 0.0.1
     */
    static basic_linestring<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        static_assert(is_basic_point<T>::value, "must contain XY points");

        auto coords = polyline::decode(polyline, precision);
        return basic_linestring<T>(coords.begin(), coords.end());
    }

    /*!
     * @brief DOCUMENT ME!
     * @param precision
     * @return
     *
     * @since 0.0.1
     */
    std::string polyline(std::int32_t precision = 5) const
    {
        static_assert(is_basic_point<T>::value, "must contain XY points");

        std::string res;
        res.reserve(this->size() * 6);
        double prev_lng = 0;
        double prev_lat = 0;
        for (const auto& p : *this)
        {
            res += polyline::encode(p.lat - prev_lat, precision);
            res += polyline::encode(p.lng - prev_lng, precision);
            prev_lat = p.lat;
            prev_lng = p.lng;
        }
        return res;
    }

  private:
    friend class basic_geometry<basic_linestring<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_point_z<T>::value)
        {
            return geometry_type::LINESTRINGZ;
        }
        if (is_basic_point_m<T>::value)
        {
            return geometry_type::LINESTRINGM;
        }
        if (is_basic_point_zm<T>::value)
        {
            return geometry_type::LINESTRINGZM;
        }
        return geometry_type::LINESTRING;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        return (*this)[0] == (*this)[this->size() - 1];
    }

    /// @private
    void throw_for_invalid_() const
    {
        if (this->empty())
        {
            return;
        }

        if (this->size() < 2)
        {
            throw exceptions::geometry_error("LineString should be either empty or with 2 or more points");
        }

        if (this->size() == 2)
        {
            if (*this[0] == *this[1])
            {
                throw exceptions::geometry_error("LineString with exactly two equal points");
            }
        }
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& p : *this)
        {
            res.extend(p.x, p.y);
        }
        return res;
    }

    // json

    /// @private
    static basic_linestring<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "LineString")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& coords_array = j.at("coordinates").as_array();
            std::vector<point_type> res;
            res.reserve(coords_array.size());
            for (const auto& coord : coords_array)
            {
                auto point_coords = coord.as_double_array();
                res.emplace_back(point_coords.begin(), point_coords.end());
            }
            return basic_linestring<T>(res.begin(), res.end());
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"LineString\",\"coordinates\":[";
        int i = 0;
        for (const auto& p : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t j = 0; j < p.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << p.coords[j];
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_linestring<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_linestring(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_linestring<T>(result.data.coords.begin(), result.data.coords.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "LINESTRING";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        ss << "(";
        int i = 0;
        for (const auto& p : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            for (size_t j = 0; j < p.size(); ++j)
            {
                if (j > 0)
                {
                    ss << " ";
                }
                ss << p.coords[j];
            }
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_linestring : std::false_type
{};

template <typename T>
struct is_basic_linestring<basic_linestring<basic_point<T>>> : std::true_type
{};

template <typename>
struct is_basic_linestring_z : std::false_type
{};

template <typename T>
struct is_basic_linestring_z<basic_linestring<basic_point_z<T>>> : std::true_type
{};

template <typename>
struct is_basic_linestring_m : std::false_type
{};

template <typename T>
struct is_basic_linestring_m<basic_linestring<basic_point_m<T>>> : std::true_type
{};

template <typename>
struct is_basic_linestring_zm : std::false_type
{};

template <typename T>
struct is_basic_linestring_zm<basic_linestring<basic_point_zm<T>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo


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

using linestring    = linestring_t<double>;
using linestring_z  = linestring_z_t<double>;
using linestring_m  = linestring_m_t<double>;
using linestring_zm = linestring_zm_t<double>;

using LineString   = linestring_t<double>;
using LineStringZ  = linestring_z_t<double>;
using LineStringM  = linestring_m_t<double>;
using LineStringZM = linestring_zm_t<double>;

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/multilinestring.hpp>


#include <ciso646>
// #include <simo/geom/detail/multilinestring.hpp>


#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <iomanip>
// #include <simo/geom/detail/geometry.hpp>

// #include <simo/geom/detail/bounds.hpp>


namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_multilinestring
    : public std::vector<T, AllocatorType>,
      public basic_geometry<basic_multilinestring<T>>
{
  public:
    using base_type            = std::vector<T, AllocatorType>;
    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<T>::iterator;
    using point_const_iterator = typename std::vector<T>::const_iterator;
    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_multilinestring()
        : base_type() {}

    basic_multilinestring(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    basic_multilinestring(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    basic_multilinestring(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    template <typename CoordIterator, typename OffsetIterator>
    basic_multilinestring(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto n = this->ndim();
            this->reserve((coord_last - coord_first) / n);
            size_t lo = 0;
            for (auto it = offset_first; it != offset_last; ++it)
            {
                size_t hi = *it;
                this->emplace_back(coord_first + lo, coord_first + hi);
                lo = hi;
            }
        }
    }

    // operators

    friend bool operator==(const basic_multilinestring<T>& lhs, const basic_multilinestring<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const basic_multilinestring<T>& lhs, const basic_multilinestring<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

  private:
    /// for allow basic_geometry to access basic_multipoint private members
    friend class basic_geometry<basic_multilinestring<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_linestring_z<T>::value)
        {
            return geometry_type::MULTILINESTRINGZ;
        }
        if (is_basic_linestring_m<T>::value)
        {
            return geometry_type::MULTILINESTRINGM;
        }
        if (is_basic_linestring_zm<T>::value)
        {
            return geometry_type::MULTILINESTRINGZM;
        }
        return geometry_type::MULTILINESTRING;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        return *this[0] == *this[this->size() - 1];
    }

    /// @private
    void throw_for_invalid_() const
    {
        for (const auto& ls : *this)
        {
            ls.throw_for_invalid();
        }
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& p : *this)
        {
            res.extend(p.x, p.y);
        }
        return res;
    }

    // json

    /// @private
    static basic_multilinestring<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "MultiLineString")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& linestrings = j.at("coordinates").as_array();
            std::vector<T> res;
            res.reserve(linestrings.size());
            for (const auto& linestring : linestrings)
            {
                if (linestring.is_array() && !linestring.empty())
                {
                    const auto& coords_array = linestring.as_array();
                    std::vector<point_type> points;
                    points.reserve(coords_array.size());
                    for (const auto& coord : coords_array)
                    {
                        auto point_coords = coord.as_double_array();
                        points.emplace_back(point_coords.begin(), point_coords.end());
                    }
                    res.emplace_back(points.begin(), points.end());
                }
            }
            return basic_multilinestring<T>(res.begin(), res.end());
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"MultiLineString\",\"coordinates\":[";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << "[";
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        ss << ",";
                    }
                    ss << p.coords[k];
                }
                ss << "]";
                ++i;
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_multilinestring<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multilinestring(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_multilinestring<T>(result.data.coords.begin(), result.data.coords.end(),
                                        result.data.line_offsets.begin(), result.data.line_offsets.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTILINESTRING";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        ss << "(";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        ss << " ";
                    }
                    ss << p.coords[k];
                }
            }
            ss << ")";
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_multilinestring : std::false_type
{};

template <typename T>
struct is_basic_multilinestring<basic_multilinestring<basic_linestring<basic_point<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multilinestring_z : std::false_type
{};

template <typename T>
struct is_basic_multilinestring_z<basic_multilinestring<basic_linestring<basic_point_z<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multilinestring_m : std::false_type
{};

template <typename T>
struct is_basic_multilinestring_m<basic_multilinestring<basic_linestring<basic_point_m<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multilinestring_zm : std::false_type
{};

template <typename T>
struct is_basic_multilinestring_zm<basic_multilinestring<basic_linestring<basic_point_zm<T>>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo


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

using multilinestring    = multilinestring_t<double>;
using multilinestring_z  = multilinestring_z_t<double>;
using multilinestring_m  = multilinestring_m_t<double>;
using multilinestring_zm = multilinestring_zm_t<double>;

using MultiLineString   = multilinestring_t<double>;
using MultiLineStringZ  = multilinestring_z_t<double>;
using MultiLineStringM  = multilinestring_m_t<double>;
using MultiLineStringZM = multilinestring_zm_t<double>;

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/polygon.hpp>


#include <ciso646>
// #include <simo/geom/detail/polygon.hpp>


#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <utility>
// #include <simo/geom/geometry.hpp>

// #include <simo/geom/linearring.hpp>


#include <ciso646>
// #include <simo/geom/detail/linestring.hpp>


namespace simo
{
namespace shapes
{

template <class T = double>
using linearring_t = basic_linestring<basic_point<T>>;

template <class T = double>
using linearring_z_t = basic_linestring<basic_point_z<T>>;

template <class T = double>
using linearring_m_t = basic_linestring<basic_point_m<T>>;

template <class T = double>
using linearring_zm_t = basic_linestring<basic_point_zm<T>>;

using linearring    = linearring_t<double>;
using linearring_z  = linearring_z_t<double>;
using linearring_m  = linearring_m_t<double>;
using linearring_zm = linearring_zm_t<double>;

using LinearRing   = linearring_t<double>;
using LinearRingZ  = linearring_z_t<double>;
using LinearRingM  = linearring_m_t<double>;
using LinearRingZM = linearring_zm_t<double>;

/// @todo (pavel) LinearRing is not closed, first and last point are different
/// @todo (pavel) LinearRing should be either empty or with 4 or more points
/// @todo (pavel) LinearRing cannot self-intersect
/// @todo (pavel) LinearRing should be implicitly closed

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/detail/bounds.hpp>


namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_polygon : public std::vector<T, AllocatorType>, public basic_geometry<basic_polygon<T>>
{
  public:
    using base_type = std::vector<T, AllocatorType>;

    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<T>::iterator;
    using point_const_iterator = typename std::vector<T>::const_iterator;

    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_polygon()
        : base_type() {}

    basic_polygon(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    basic_polygon(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    basic_polygon(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}


    explicit basic_polygon(coord_const_iterator first, coord_const_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    explicit basic_polygon(coord_iterator first, coord_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    template <typename CoordIterator, typename OffsetIterator>
    basic_polygon(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto n = this->ndim();
            this->reserve((coord_last - coord_first) / n);
            size_t lo = 0;
            for (auto it = offset_first; it != offset_last; ++it)
            {
                size_t hi = *it;
                this->emplace_back(coord_first + lo, coord_first + hi);
                lo = hi;
            }
        }
    }

    // operators

    friend bool operator==(const basic_polygon<T>& lhs, const basic_polygon<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const basic_polygon<T>& lhs, const basic_polygon<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

    T& exterior()
    {
        return *this->begin();
    }

    T& interiors(size_t pos)
    {
        assert(this->begin() + pos + 1 < this->end());
        return *(this->begin() + pos + 1);
    }

  private:
    /// for allow basic_geometry to access basic_polygon private members
    friend class basic_geometry<basic_polygon<T>>;

    static bool ring_is_closed(const T& ring) noexcept
    {
        if (ring.empty())
        {
            return true;
        }
        return ring.front().x == ring.back().x and ring.front().y == ring.back().y;
    }

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_linestring_z<T>::value)
        {
            return geometry_type::POLYGONZ;
        }
        if (is_basic_linestring_m<T>::value)
        {
            return geometry_type::POLYGONM;
        }
        if (is_basic_linestring_zm<T>::value)
        {
            return geometry_type::POLYGONZM;
        }
        return geometry_type::POLYGON;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        for (const auto& ring : *this)
        {
            if (not ring_is_closed(ring))
            {
                return false;
            }
        }
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        for (const auto& ring : *this)
        {
            if (ring.empty())
            {
                throw exceptions::geometry_error("Polygon rings should not be empty");
            }
            if (ring.size() < 4)
            {
                throw exceptions::geometry_error("Polygon rings should have 4 or more points");
            }
            if (not ring_is_closed(ring))
            {
                throw exceptions::geometry_error("Polygon rings should be closed");
            }
            for (const auto& point : ring)
            {
                if (point.empty())
                {
                    throw exceptions::geometry_error("Polygon rings should not contain empty points");
                }
            }
        }
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& r : *this)
        {
            auto r_bound = r.bounds();
            res.extend(r_bound);
        }
        return res;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Polygon";
    }

    // json

    /// @private
    static basic_polygon<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "Polygon")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& rings = j.at("coordinates").as_array();
            std::vector<T> res;
            res.reserve(rings.size());
            for (const auto& ring : rings)
            {
                if (ring.is_array() && !ring.empty())
                {
                    const auto& coords_array = ring.as_array();
                    std::vector<point_type> points;
                    points.reserve(coords_array.size());
                    for (const auto& coord : coords_array)
                    {
                        auto point_coords = coord.as_double_array();
                        points.emplace_back(point_coords.begin(), point_coords.end());
                    }
                    res.emplace_back(points.begin(), points.end());
                }
            }
            return basic_polygon<T>(res.begin(), res.end());
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"Polygon\",\"coordinates\":[";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << "[";
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        ss << ",";
                    }
                    ss << p.coords[k];
                }
                ss << "]";
                ++i;
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_polygon<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_polygon(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        auto polygon = basic_polygon<T>(result.data.coords.begin(), result.data.coords.end(),
                                        result.data.ring_offsets.begin(), result.data.ring_offsets.end());
        polygon.throw_for_invalid();
        return polygon;
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POLYGON";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        ss << "(";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        ss << " ";
                    }
                    ss << p.coords[k];
                }
            }
            ss << ")";
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_polygon : std::false_type
{};

template <typename T>
struct is_basic_polygon<basic_polygon<basic_linestring<basic_point<T>>>> : std::true_type
{};

template <typename>
struct is_basic_polygon_z : std::false_type
{};

template <typename T>
struct is_basic_polygon_z<basic_polygon<basic_linestring<basic_point_z<T>>>> : std::true_type
{};

template <typename>
struct is_basic_polygon_m : std::false_type
{};

template <typename T>
struct is_basic_polygon_m<basic_polygon<basic_linestring<basic_point_m<T>>>> : std::true_type
{};

template <typename>
struct is_basic_polygon_zm : std::false_type
{};

template <typename T>
struct is_basic_polygon_zm<basic_polygon<basic_linestring<basic_point_zm<T>>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo


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

using polygon    = polygon_t<double>;
using polygon_z  = polygon_z_t<double>;
using polygon_m  = polygon_m_t<double>;
using polygon_zm = polygon_zm_t<double>;

using Polygon   = polygon_t<double>;
using PolygonZ  = polygon_z_t<double>;
using PolygonM  = polygon_m_t<double>;
using PolygonZM = polygon_zm_t<double>;

}  // namespace shapes
}  // namespace simo
// #include <simo/geom/multipolygon.hpp>


#include <ciso646>
// #include <simo/geom/detail/multipolygon.hpp>


#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <iomanip>
// #include <simo/geom/detail/geometry.hpp>

// #include <simo/geom/detail/bounds.hpp>


namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_multipolygon
    : public std::vector<T, AllocatorType>,
      public basic_geometry<basic_multipolygon<T>>
{
  public:
    using base_type = std::vector<T, AllocatorType>;

    using polygon_type           = T;
    using polygon_iterator       = typename std::vector<polygon_type>::iterator;
    using polygon_const_iterator = typename std::vector<polygon_type>::const_iterator;

    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<point_type>::iterator;
    using point_const_iterator = typename std::vector<point_type>::const_iterator;

    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_multipolygon()
        : base_type() {}

    basic_multipolygon(polygon_iterator first, polygon_iterator last)
        : base_type(first, last)
    {
    }

    basic_multipolygon(polygon_const_iterator first, polygon_const_iterator last)
        : base_type(first, last)
    {
    }

    basic_multipolygon(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    template <typename CoordIterator, typename OffsetIterator>
    basic_multipolygon(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto n = this->ndim();
            this->reserve((coord_last - coord_first) / n);
            size_t lo = 0;
            for (auto it = offset_first; it != offset_last; ++it)
            {
                size_t hi = *it;
                this->emplace_back(coord_first + lo, coord_first + hi);
                lo = hi;
            }
        }
    }

    template <typename CoordIterator, typename RingOffsetIterator, typename PolygonOffsetIterator>
    basic_multipolygon(CoordIterator coord_first, CoordIterator coord_last,
                       RingOffsetIterator ring_offset_first, RingOffsetIterator ring_offset_last,
                       PolygonOffsetIterator polygon_offset_first, PolygonOffsetIterator polygon_offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            using ring_type = typename T::value_type;

            this->reserve(static_cast<size_t>(std::distance(polygon_offset_first, polygon_offset_last)));
            size_t coord_lo = 0;
            size_t ring_lo  = 0;
            for (auto polygon_it = polygon_offset_first; polygon_it != polygon_offset_last; ++polygon_it)
            {
                size_t ring_hi = *polygon_it;
                std::vector<ring_type> rings;
                rings.reserve(ring_hi - ring_lo);
                for (size_t ring_index = ring_lo; ring_index < ring_hi; ++ring_index)
                {
                    size_t coord_hi = *(ring_offset_first + static_cast<std::ptrdiff_t>(ring_index));
                    rings.emplace_back(coord_first + static_cast<std::ptrdiff_t>(coord_lo),
                                       coord_first + static_cast<std::ptrdiff_t>(coord_hi));
                    coord_lo = coord_hi;
                }
                this->emplace_back(rings.begin(), rings.end());
                ring_lo = ring_hi;
            }
        }
        (void)ring_offset_last;
    }

    // operators

    friend bool operator==(const basic_multipolygon<T>& lhs, const basic_multipolygon<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const basic_multipolygon<T>& lhs, const basic_multipolygon<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

  private:
    /// for allow basic_geometry to access basic_multipoint private members
    friend class basic_geometry<basic_multipolygon<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_polygon_z<T>::value)
        {
            return geometry_type::MULTIPOLYGONZ;
        }
        if (is_basic_polygon_m<T>::value)
        {
            return geometry_type::MULTIPOLYGONM;
        }
        if (is_basic_polygon_zm<T>::value)
        {
            return geometry_type::MULTIPOLYGONZM;
        }
        return geometry_type::MULTIPOLYGON;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        for (const auto& polygon : *this)
        {
            if (not polygon.is_closed())
            {
                return false;
            }
        }
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        for (const auto& ls : *this)
        {
            ls.throw_for_invalid();
        }
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& p : *this)
        {
            res.extend(p.bounds());
        }
        return res;
    }

    // json

    /// @private
    static basic_multipolygon<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "MultiPolygon")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& polygons = j.at("coordinates").as_array();
            std::vector<T> res;
            res.reserve(polygons.size());
            for (const auto& polygon : polygons)
            {
                if (polygon.is_array() && !polygon.empty())
                {
                    // Each polygon is an array of rings (exterior + holes)
                    const auto& rings = polygon.as_array();
                    using ring_type = typename T::value_type;
                    std::vector<ring_type> polygon_rings;
                    polygon_rings.reserve(rings.size());
                    for (const auto& ring : rings)
                    {
                        if (ring.is_array() && !ring.empty())
                        {
                            const auto& coords_array = ring.as_array();
                            std::vector<point_type> points;
                            points.reserve(coords_array.size());
                            for (const auto& coord : coords_array)
                            {
                                auto point_coords = coord.as_double_array();
                                points.emplace_back(point_coords.begin(), point_coords.end());
                            }
                            polygon_rings.emplace_back(points.begin(), points.end());
                        }
                    }
                    res.emplace_back(polygon_rings.begin(), polygon_rings.end());
                }
            }
            return basic_multipolygon<T>(res.begin(), res.end());
        }
        catch (const io::geojson_parse_error& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"MultiPolygon\",\"coordinates\":[";
        for (size_t polygon_index = 0; polygon_index < this->size(); ++polygon_index)
        {
            const auto& pg = (*this)[polygon_index];
            if (polygon_index > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t ring_index = 0; ring_index < pg.size(); ++ring_index)
            {
                const auto& ring = pg[ring_index];
                if (ring_index > 0)
                {
                    ss << ",";
                }
                ss << "[";
                for (size_t point_index = 0; point_index < ring.size(); ++point_index)
                {
                    const auto& p = ring[point_index];
                    if (point_index > 0)
                    {
                        ss << ",";
                    }
                    ss << "[";
                    for (size_t coord_index = 0; coord_index < p.size(); ++coord_index)
                    {
                        if (coord_index > 0)
                        {
                            ss << ",";
                        }
                        ss << p.coords[coord_index];
                    }
                    ss << "]";
                }
                ss << "]";
            }
            ss << "]";
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_multipolygon<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multipolygon(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        auto multipolygon = basic_multipolygon<T>(data.coords.begin(), data.coords.end(),
                                                  data.ring_offsets.begin(), data.ring_offsets.end(),
                                                  data.polygon_offsets.begin(), data.polygon_offsets.end());
        multipolygon.throw_for_invalid();
        return multipolygon;
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTIPOLYGON";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        size_t polygon_index = 0;
        ss << "(";
        for (const auto& pg : *this)
        {
            if (polygon_index > 0)
            {
                ss << ",";
            }
            ss << "(";
            size_t ring_index = 0;
            for (const auto& ring : pg)
            {
                if (ring_index > 0)
                {
                    ss << ",";
                }
                ss << "(";
                size_t point_index = 0;
                for (const auto& p : ring)
                {
                    if (point_index > 0)
                    {
                        ss << ",";
                    }
                    for (size_t k = 0; k < p.ndim(); ++k)
                    {
                        if (k > 0)
                        {
                            ss << " ";
                        }
                        ss << p.coords[k];
                    }
                    ++point_index;
                }
                ss << ")";
                ++ring_index;
            }
            ss << ")";
            ++polygon_index;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_multipolygon : std::false_type
{};

template <typename T>
struct is_basic_multipolygon<basic_multipolygon<basic_polygon<basic_linestring<basic_point<T>>>>> : std::true_type
{};

template <typename>
struct is_basic_multipolygon_z : std::false_type
{};

template <typename T>
struct is_basic_multipolygon_z<basic_multipolygon<basic_polygon<basic_linestring<basic_point_z<T>>>>> : std::true_type
{};

template <typename>
struct is_basic_multipolygon_m : std::false_type
{};

template <typename T>
struct is_basic_multipolygon_m<basic_multipolygon<basic_polygon<basic_linestring<basic_point_m<T>>>>> : std::true_type
{};

template <typename>
struct is_basic_multipolygon_zm : std::false_type
{};

template <typename T>
struct is_basic_multipolygon_zm<basic_multipolygon<basic_polygon<basic_linestring<basic_point_zm<T>>>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo


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

namespace simo
{
namespace shapes
{

template <typename T>
class geometry_t;

template <typename T = double, geometry_type GeometryType = geometry_type::GEOMETRYCOLLECTION,
          typename AllocatorType = std::allocator<geometry_t<T>>>
class basic_geometrycollection;

template <class T = double>
using geometrycollection_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTION>;

template <class T = double>
using geometrycollection_z_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTIONZ>;

template <class T = double>
using geometrycollection_m_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTIONM>;

template <class T = double>
using geometrycollection_zm_t = basic_geometrycollection<T, geometry_type::GEOMETRYCOLLECTIONZM>;

template <typename>
struct is_basic_geometrycollection;

template <typename>
struct is_basic_geometrycollection_z;

template <typename>
struct is_basic_geometrycollection_m;

template <typename>
struct is_basic_geometrycollection_zm;

template <typename T>
class geometry_t : public basic_geometry<geometry_t<T>>
{
  public:
    // default constructor
    geometry_t()
    {
        std::cout << "DEFAULT CONSTRUCTOR" << std::endl;
    }

    // copy constructor:
    geometry_t(const geometry_t& other)
    {
        std::cout << "COPY CONSTRUCTOR" << std::endl;
        m_geom_type = other.geom_type();
        switch (other.geom_type())
        {
                // point

            case geometry_type::POINT:
            {
                m_value = geom_value(*other.m_value.m_point);
                break;
            }
            case geometry_type::POINTZ:
            {
                m_value = geom_value(*other.m_value.m_point_z);
                break;
            }
            case geometry_type::POINTM:
            {
                m_value = geom_value(*other.m_value.m_point_m);
                break;
            }
            case geometry_type::POINTZM:
            {
                m_value = geom_value(*other.m_value.m_point_zm);
                break;
            }

                // multipoint

            case geometry_type::MULTIPOINT:
            {
                m_value = geom_value(*other.m_value.m_multipoint);
                break;
            }
            case geometry_type::MULTIPOINTZ:
            {
                m_value = geom_value(*other.m_value.m_multipoint_z);
                break;
            }
            case geometry_type::MULTIPOINTM:
            {
                m_value = geom_value(*other.m_value.m_multipoint_m);
                break;
            }
            case geometry_type::MULTIPOINTZM:
            {
                m_value = geom_value(*other.m_value.m_multipoint_zm);
                break;
            }

                // linestring

            case geometry_type::LINESTRING:
            {
                m_value = geom_value(*other.m_value.m_linestring);
                break;
            }
            case geometry_type::LINESTRINGZ:
            {
                m_value = geom_value(*other.m_value.m_linestring_z);
                break;
            }
            case geometry_type::LINESTRINGM:
            {
                m_value = geom_value(*other.m_value.m_linestring_m);
                break;
            }
            case geometry_type::LINESTRINGZM:
            {
                m_value = geom_value(*other.m_value.m_linestring_zm);
                break;
            }

                // multilinestring

            case geometry_type::MULTILINESTRING:
            {
                m_value = geom_value(*other.m_value.m_multilinestring);
                break;
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                m_value = geom_value(*other.m_value.m_multilinestring_z);
                break;
            }
            case geometry_type::MULTILINESTRINGM:
            {
                m_value = geom_value(*other.m_value.m_multilinestring_m);
                break;
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                m_value = geom_value(*other.m_value.m_multilinestring_zm);
                break;
            }

                // polygon

            case geometry_type::POLYGON:
            {
                m_value = geom_value(*other.m_value.m_polygon);
                break;
            }
            case geometry_type::POLYGONZ:
            {
                m_value = geom_value(*other.m_value.m_polygon_z);
                break;
            }
            case geometry_type::POLYGONM:
            {
                m_value = geom_value(*other.m_value.m_polygon_m);
                break;
            }
            case geometry_type::POLYGONZM:
            {
                m_value = geom_value(*other.m_value.m_polygon_zm);
                break;
            }

                // multipolygon

            case geometry_type::MULTIPOLYGON:
            {
                m_value = geom_value(*other.m_value.m_multipolygon);
                break;
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                m_value = geom_value(*other.m_value.m_multipolygon_z);
                break;
            }
            case geometry_type::MULTIPOLYGONM:
            {
                m_value = geom_value(*other.m_value.m_multipolygon_m);
                break;
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                m_value = geom_value(*other.m_value.m_multipolygon_zm);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTION:
            {
                copy_geometrycollection_(other);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONZ:
            {
                copy_geometrycollection_z_(other);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONM:
            {
                copy_geometrycollection_m_(other);
                break;
            }
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                copy_geometrycollection_zm_(other);
                break;
            }
            default:
            {
                break;
            }
        }
    }
    // copy assignment
    geometry_t& operator=(const geometry_t& other)
    {
        std::cout << "COPY ASSIGNMENT" << std::endl;
        geometry_t temp(other);
        swap(*this, temp);
        return *this;
    }

    // move constructor
    geometry_t(geometry_t&& other) noexcept
        : geometry_t()
    {
        std::cout << "MOVE CONSTRUCTOR" << std::endl;
        swap(*this, other);
    }

    friend void swap(geometry_t& lhs, geometry_t& rhs)  // nothrow
    {
        using std::swap;
        swap(lhs.m_value, rhs.m_value);
        swap(lhs.m_geom_type, rhs.m_geom_type);
        swap(lhs.m_geometrycollection, rhs.m_geometrycollection);
        swap(lhs.m_geometrycollection_z, rhs.m_geometrycollection_z);
        swap(lhs.m_geometrycollection_m, rhs.m_geometrycollection_m);
        swap(lhs.m_geometrycollection_zm, rhs.m_geometrycollection_zm);
    }

    // point

    explicit geometry_t(const point_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINT)
    {
    }

    explicit geometry_t(const point_z_t<T>& p)
        : m_value(p), m_geom_type(geometry_type::POINTZ)
    {
    }

    explicit geometry_t(const point_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POINTM)
    {
    }

    explicit geometry_t(const point_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POINTZM)
    {
    }

    // multipoint

    explicit geometry_t(const multipoint_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINT)
    {
    }

    explicit geometry_t(const multipoint_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINTZ)
    {
    }

    explicit geometry_t(const multipoint_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINTM)
    {
    }

    explicit geometry_t(const multipoint_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOINTZM)
    {
    }

    // linestring

    explicit geometry_t(const linestring_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRING)
    {
    }

    explicit geometry_t(const linestring_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRINGZ)
    {
    }

    explicit geometry_t(const linestring_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRINGM)
    {
    }

    explicit geometry_t(const linestring_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::LINESTRINGZM)
    {
    }

    // multilinestring

    explicit geometry_t(const multilinestring_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRING)
    {
    }

    explicit geometry_t(const multilinestring_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRINGZ)
    {
    }

    explicit geometry_t(const multilinestring_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRINGM)
    {
    }

    explicit geometry_t(const multilinestring_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTILINESTRINGZM)
    {
    }

    // polygon

    explicit geometry_t(const polygon_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGON)
    {
    }

    explicit geometry_t(const polygon_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGONZ)
    {
    }

    explicit geometry_t(const polygon_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGONM)
    {
    }

    explicit geometry_t(const polygon_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::POLYGONZM)
    {
    }

    // multipolygon

    explicit geometry_t(const multipolygon_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGON)
    {
    }

    explicit geometry_t(const multipolygon_z_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGONZ)
    {
    }

    explicit geometry_t(const multipolygon_m_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGONM)
    {
    }

    explicit geometry_t(const multipolygon_zm_t<T>& value)
        : m_value(value), m_geom_type(geometry_type::MULTIPOLYGONZM)
    {
    }

    explicit geometry_t(const geometrycollection_t<T>& value);

    explicit geometry_t(const geometrycollection_z_t<T>& value);

    explicit geometry_t(const geometrycollection_m_t<T>& value);

    explicit geometry_t(const geometrycollection_zm_t<T>& value);

    ~geometry_t()
    {
        switch (m_geom_type)
        {
                // point

            case geometry_type::POINT:
            {
                delete m_value.m_point;
                m_value.m_point = nullptr;
                std::cout << "DELETE POINT" << std::endl;
                break;
            }
            case geometry_type::POINTZ:
            {
                delete m_value.m_point_z;
                m_value.m_point_z = nullptr;
                std::cout << "DELETE POINT Z" << std::endl;
                break;
            }
            case geometry_type::POINTM:
            {
                delete m_value.m_point_m;
                m_value.m_point_m = nullptr;
                std::cout << "DELETE POINT M" << std::endl;
                break;
            }
            case geometry_type::POINTZM:
            {
                delete m_value.m_point_zm;
                m_value.m_point_zm = nullptr;
                std::cout << "DELETE POINT ZM" << std::endl;
                break;
            }

                // multipoint

            case geometry_type::MULTIPOINT:
            {
                delete m_value.m_multipoint;
                m_value.m_multipoint = nullptr;
                std::cout << "DELETE MULTIPOINT" << std::endl;
                break;
            }
            case geometry_type::MULTIPOINTZ:
            {
                delete m_value.m_multipoint_z;
                m_value.m_multipoint_z = nullptr;
                std::cout << "DELETE MULTIPOINT Z" << std::endl;
                break;
            }
            case geometry_type::MULTIPOINTM:
            {
                delete m_value.m_multipoint_m;
                m_value.m_multipoint_m = nullptr;
                std::cout << "DELETE MULTIPOINT M" << std::endl;
                break;
            }
            case geometry_type::MULTIPOINTZM:
            {
                delete m_value.m_multipoint_zm;
                m_value.m_multipoint_zm = nullptr;
                std::cout << "DELETE MULTIPOINT ZM" << std::endl;
                break;
            }

                // linestring

            case geometry_type::LINESTRING:
            {
                delete m_value.m_linestring;
                m_value.m_linestring = nullptr;
                std::cout << "DELETE LINESTRING" << std::endl;
                break;
            }
            case geometry_type::LINESTRINGZ:
            {
                delete m_value.m_linestring_z;
                m_value.m_linestring_z = nullptr;
                std::cout << "DELETE LINESTRING Z" << std::endl;
                break;
            }
            case geometry_type::LINESTRINGM:
            {
                delete m_value.m_linestring_m;
                m_value.m_linestring_m = nullptr;
                std::cout << "DELETE LINESTRING M" << std::endl;
                break;
            }
            case geometry_type::LINESTRINGZM:
            {
                delete m_value.m_linestring_zm;
                m_value.m_linestring_zm = nullptr;
                std::cout << "DELETE LINESTRING ZM" << std::endl;
                break;
            }

                // multilinestring

            case geometry_type::MULTILINESTRING:
            {
                delete m_value.m_multilinestring;
                m_value.m_multilinestring = nullptr;
                std::cout << "DELETE MULTILINESTRING" << std::endl;
                break;
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                delete m_value.m_multilinestring_z;
                m_value.m_multilinestring_z = nullptr;
                std::cout << "DELETE MULTILINESTRING Z" << std::endl;
                break;
            }
            case geometry_type::MULTILINESTRINGM:
            {
                delete m_value.m_multilinestring_m;
                m_value.m_multilinestring_m = nullptr;
                std::cout << "DELETE MULTILINESTRING M" << std::endl;
                break;
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                delete m_value.m_multilinestring_zm;
                m_value.m_multilinestring_zm = nullptr;
                std::cout << "DELETE MULTILINESTRING ZM" << std::endl;
                break;
            }

                // polygon

            case geometry_type::POLYGON:
            {
                delete m_value.m_polygon;
                m_value.m_polygon = nullptr;
                std::cout << "DELETE POLYGON" << std::endl;
                break;
            }
            case geometry_type::POLYGONZ:
            {
                delete m_value.m_polygon_z;
                m_value.m_polygon_z = nullptr;
                std::cout << "DELETE POLYGON Z" << std::endl;
                break;
            }
            case geometry_type::POLYGONM:
            {
                delete m_value.m_polygon_m;
                m_value.m_polygon_m = nullptr;
                std::cout << "DELETE POLYGON M" << std::endl;
                break;
            }
            case geometry_type::POLYGONZM:
            {
                delete m_value.m_polygon_zm;
                m_value.m_polygon_zm = nullptr;
                std::cout << "DELETE POLYGON ZM" << std::endl;
                break;
            }

                // multipolygon

            case geometry_type::MULTIPOLYGON:
            {
                delete m_value.m_multipolygon;
                m_value.m_multipolygon = nullptr;
                std::cout << "DELETE MULTIPOLYGON" << std::endl;
                break;
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                delete m_value.m_multipolygon_z;
                m_value.m_multipolygon_z = nullptr;
                std::cout << "DELETE MULTIPOLYGON Z" << std::endl;
                break;
            }
            case geometry_type::MULTIPOLYGONM:
            {
                delete m_value.m_multipolygon_m;
                m_value.m_multipolygon_m = nullptr;
                std::cout << "DELETE MULTIPOLYGON M" << std::endl;
                break;
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                delete m_value.m_multipolygon_zm;
                m_value.m_multipolygon_zm = nullptr;
                std::cout << "DELETE MULTIPOLYGON ZM" << std::endl;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    // getters

    template <typename ReturnType>
    ReturnType* get()
    {
        // point

        if (is_basic_point<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point());
        }
        if (is_basic_point_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point_z());
        }
        if (is_basic_point_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point_m());
        }
        if (is_basic_point_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_point_zm());
        }

        // multipoint

        if (is_basic_multipoint<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint());
        }
        if (is_basic_multipoint_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint_z());
        }
        if (is_basic_multipoint_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint_m());
        }
        if (is_basic_multipoint_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipoint_zm());
        }

        // linestring

        if (is_basic_linestring<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring());
        }
        if (is_basic_linestring_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring_z());
        }
        if (is_basic_linestring_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring_m());
        }
        if (is_basic_linestring_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_linestring_zm());
        }

        // multilinestring

        if (is_basic_multilinestring<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring());
        }
        if (is_basic_multilinestring_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring_z());
        }
        if (is_basic_multilinestring_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring_m());
        }
        if (is_basic_multilinestring_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multilinestring_zm());
        }

        // polygon

        if (is_basic_polygon<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon());
        }
        if (is_basic_polygon_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon_z());
        }
        if (is_basic_polygon_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon_m());
        }
        if (is_basic_polygon_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_polygon_zm());
        }

        // multipolygon

        if (is_basic_multipolygon<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon());
        }
        if (is_basic_multipolygon_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon_z());
        }
        if (is_basic_multipolygon_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon_m());
        }
        if (is_basic_multipolygon_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_multipolygon_zm());
        }

        // geometrycollection

        if (is_basic_geometrycollection<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection());
        }
        if (is_basic_geometrycollection_z<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection_z());
        }
        if (is_basic_geometrycollection_m<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection_m());
        }
        if (is_basic_geometrycollection_zm<ReturnType>::value)
        {
            return reinterpret_cast<ReturnType*>(get_geometrycollection_zm());
        }

        return nullptr;
    }

    // point

    inline bool is_point()
    {
        return m_geom_type == geometry_type::POINT;
    }

    inline bool is_point_z()
    {
        return m_geom_type == geometry_type::POINTZ;
    }

    inline bool is_point_m()
    {
        return m_geom_type == geometry_type::POINTM;
    }

    inline bool is_point_zm()
    {
        return m_geom_type == geometry_type::POINTZM;
    }

    // multipoint

    inline bool is_multipoint()
    {
        return m_geom_type == geometry_type::MULTIPOINT;
    }

    inline bool is_multipoint_z()
    {
        return m_geom_type == geometry_type::MULTIPOINTZ;
    }

    inline bool is_multipoint_m()
    {
        return m_geom_type == geometry_type::MULTIPOINTM;
    }

    inline bool is_multipoint_zm()
    {
        return m_geom_type == geometry_type::MULTIPOINTZM;
    }

    // linestring

    inline bool is_linestring()
    {
        return m_geom_type == geometry_type::LINESTRING;
    }

    inline bool is_linestring_z()
    {
        return m_geom_type == geometry_type::LINESTRINGZ;
    }

    inline bool is_linestring_m()
    {
        return m_geom_type == geometry_type::LINESTRINGM;
    }

    inline bool is_linestring_zm()
    {
        return m_geom_type == geometry_type::LINESTRINGZM;
    }

    // multilinestring

    inline bool is_multilinestring()
    {
        return m_geom_type == geometry_type::MULTILINESTRING;
    }

    inline bool is_multilinestring_z()
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZ;
    }

    inline bool is_multilinestring_m()
    {
        return m_geom_type == geometry_type::MULTILINESTRINGM;
    }

    inline bool is_multilinestring_zm()
    {
        return m_geom_type == geometry_type::MULTILINESTRINGZM;
    }

    // polygon

    inline bool is_polygon()
    {
        return m_geom_type == geometry_type::POLYGON;
    }

    inline bool is_polygon_z()
    {
        return m_geom_type == geometry_type::POLYGONZ;
    }

    inline bool is_polygon_m()
    {
        return m_geom_type == geometry_type::POLYGONM;
    }

    inline bool is_polygon_zm()
    {
        return m_geom_type == geometry_type::POLYGONZM;
    }

    // multipolygon

    inline bool is_multipolygon()
    {
        return m_geom_type == geometry_type::MULTIPOLYGON;
    }

    inline bool is_multipolygon_z()
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZ;
    }

    inline bool is_multipolygon_m()
    {
        return m_geom_type == geometry_type::MULTIPOLYGONM;
    }

    inline bool is_multipolygon_zm()
    {
        return m_geom_type == geometry_type::MULTIPOLYGONZM;
    }

    // geometrycollection

    inline bool is_geometrycollection()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTION;
    }

    inline bool is_geometrycollection_z()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZ;
    }

    inline bool is_geometrycollection_m()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONM;
    }

    inline bool is_geometrycollection_zm()
    {
        return m_geom_type == geometry_type::GEOMETRYCOLLECTIONZM;
    }

    // point

    point_t<T>* get_point()
    {
        assert(is_point());
        return m_value.m_point;
    }

    point_z_t<T>* get_point_z()
    {
        assert(is_point_z());
        return m_value.m_point_z;
    }

    point_m_t<T>* get_point_m()
    {
        assert(is_point_m());
        return m_value.m_point_m;
    }

    point_zm_t<T>* get_point_zm()
    {
        assert(is_point_zm());
        return m_value.m_point_zm;
    }

    // multipoint

    multipoint_t<T>* get_multipoint()
    {
        assert(is_multipoint());
        return m_value.m_multipoint;
    }

    multipoint_z_t<T>* get_multipoint_z()
    {
        assert(is_multipoint_z());
        return m_value.m_multipoint_z;
    }

    multipoint_m_t<T>* get_multipoint_m()
    {
        assert(is_multipoint_m());
        return m_value.m_multipoint_m;
    }

    multipoint_zm_t<T>* get_multipoint_zm()
    {
        assert(is_multipoint_zm());
        return m_value.m_multipoint_zm;
    }

    // linestring

    linestring_t<T>* get_linestring()
    {
        assert(is_linestring());
        return m_value.m_linestring;
    }

    linestring_z_t<T>* get_linestring_z()
    {
        assert(is_linestring_z());
        return m_value.m_linestring_z;
    }

    linestring_m_t<T>* get_linestring_m()
    {
        assert(is_linestring_m());
        return m_value.m_linestring_m;
    }

    linestring_zm_t<T>* get_linestring_zm()
    {
        assert(is_linestring_zm());
        return m_value.m_linestring_zm;
    }

    // multilinestring

    multilinestring_t<T>* get_multilinestring()
    {
        assert(is_multilinestring());
        return m_value.m_multilinestring;
    }

    multilinestring_z_t<T>* get_multilinestring_z()
    {
        assert(is_multilinestring_z());
        return m_value.m_multilinestring_z;
    }

    multilinestring_m_t<T>* get_multilinestring_m()
    {
        assert(is_multilinestring_m());
        return m_value.m_multilinestring_m;
    }

    multilinestring_zm_t<T>* get_multilinestring_zm()
    {
        assert(is_multilinestring_zm());
        return m_value.m_multilinestring_zm;
    }

    // polygon

    polygon_t<T>* get_polygon()
    {
        assert(is_polygon());
        return m_value.m_polygon;
    }

    polygon_z_t<T>* get_polygon_z()
    {
        assert(is_polygon_z());
        return m_value.m_polygon_z;
    }

    polygon_m_t<T>* get_polygon_m()
    {
        assert(is_polygon_m());
        return m_value.m_polygon_m;
    }

    polygon_zm_t<T>* get_polygon_zm()
    {
        assert(is_polygon_zm());
        return m_value.m_polygon_zm;
    }

    // multipolygon

    multipolygon_t<T>* get_multipolygon()
    {
        assert(is_multipolygon());
        return m_value.m_multipolygon;
    }

    multipolygon_z_t<T>* get_multipolygon_z()
    {
        assert(is_multipolygon_z());
        return m_value.m_multipolygon_z;
    }

    multipolygon_m_t<T>* get_multipolygon_m()
    {
        assert(is_multipolygon_m());
        return m_value.m_multipolygon_m;
    }

    multipolygon_zm_t<T>* get_multipolygon_zm()
    {
        assert(is_multipolygon_zm());
        return m_value.m_multipolygon_zm;
    }

    // geometrycollection

    geometrycollection_t<T>* get_geometrycollection();

    geometrycollection_z_t<T>* get_geometrycollection_z();

    geometrycollection_m_t<T>* get_geometrycollection_m();

    geometrycollection_zm_t<T>* get_geometrycollection_zm();

  private:
    /// for allow basic_geometry to access basic_point_zm private members
    friend class basic_geometry<geometry_t<T>>;

    void copy_geometrycollection_(const geometry_t<T>& other);
    void copy_geometrycollection_z_(const geometry_t<T>& other);
    void copy_geometrycollection_m_(const geometry_t<T>& other);
    void copy_geometrycollection_zm_(const geometry_t<T>& other);

    static bool is_geometrycollection_wkt_(const std::string& wkt);
    static geometry_type geometrycollection_type_from_wkt_(const std::string& wkt);
    static geometry_t<T> from_geometrycollection_wkt_(const std::string& wkt);
    std::string geometrycollection_json_(std::int32_t precision) const;
    std::string geometrycollection_wkt_(std::int32_t precision) const;

    union geom_value
    {
        point_t<T>* m_point;
        point_z_t<T>* m_point_z;
        point_m_t<T>* m_point_m;
        point_zm_t<T>* m_point_zm;
        multipoint_t<T>* m_multipoint;
        multipoint_z_t<T>* m_multipoint_z;
        multipoint_m_t<T>* m_multipoint_m;
        multipoint_zm_t<T>* m_multipoint_zm;
        linestring_t<T>* m_linestring;
        linestring_z_t<T>* m_linestring_z;
        linestring_m_t<T>* m_linestring_m;
        linestring_zm_t<T>* m_linestring_zm;
        multilinestring_t<T>* m_multilinestring;
        multilinestring_z_t<T>* m_multilinestring_z;
        multilinestring_m_t<T>* m_multilinestring_m;
        multilinestring_zm_t<T>* m_multilinestring_zm;
        polygon_t<T>* m_polygon;
        polygon_z_t<T>* m_polygon_z;
        polygon_m_t<T>* m_polygon_m;
        polygon_zm_t<T>* m_polygon_zm;
        multipolygon_t<T>* m_multipolygon;
        multipolygon_z_t<T>* m_multipolygon_z;
        multipolygon_m_t<T>* m_multipolygon_m;
        multipolygon_zm_t<T>* m_multipolygon_zm;

        // default constructor
        geom_value() = default;

        // point

        explicit geom_value(const point_t<T>& p)
            : m_point(new point_t<T>(p))
        {
        }

        explicit geom_value(const point_z_t<T>& p)
            : m_point_z(new point_z_t<T>(p))
        {
        }

        explicit geom_value(const point_m_t<T>& p)
            : m_point_m(new point_m_t<T>(p))
        {
        }

        explicit geom_value(const point_zm_t<T>& p)
            : m_point_zm(new point_zm_t<T>(p))
        {
        }

        // multipoint

        explicit geom_value(const multipoint_t<T>& p)
            : m_multipoint(new multipoint_t<T>(p))
        {
        }

        explicit geom_value(const multipoint_z_t<T>& p)
            : m_multipoint_z(new multipoint_z_t<T>(p))
        {
        }

        explicit geom_value(const multipoint_m_t<T>& p)
            : m_multipoint_m(new multipoint_m_t<T>(p))
        {
        }

        explicit geom_value(const multipoint_zm_t<T>& p)
            : m_multipoint_zm(new multipoint_zm_t<T>(p))
        {
        }

        // linestring

        explicit geom_value(const linestring_t<T>& p)
            : m_linestring(new linestring_t<T>(p))
        {
        }

        explicit geom_value(const linestring_z_t<T>& p)
            : m_linestring_z(new linestring_z_t<T>(p))
        {
        }

        explicit geom_value(const linestring_m_t<T>& p)
            : m_linestring_m(new linestring_m_t<T>(p))
        {
        }

        explicit geom_value(const linestring_zm_t<T>& p)
            : m_linestring_zm(new linestring_zm_t<T>(p))
        {
        }

        // multilinestring

        explicit geom_value(const multilinestring_t<T>& p)
            : m_multilinestring(new multilinestring_t<T>(p))
        {
        }

        explicit geom_value(const multilinestring_z_t<T>& p)
            : m_multilinestring_z(new multilinestring_z_t<T>(p))
        {
        }

        explicit geom_value(const multilinestring_m_t<T>& p)
            : m_multilinestring_m(new multilinestring_m_t<T>(p))
        {
        }

        explicit geom_value(const multilinestring_zm_t<T>& p)
            : m_multilinestring_zm(new multilinestring_zm_t<T>(p))
        {
        }

        // polygon

        explicit geom_value(const polygon_t<T>& p)
            : m_polygon(new polygon_t<T>(p))
        {
        }

        explicit geom_value(const polygon_z_t<T>& p)
            : m_polygon_z(new polygon_z_t<T>(p))
        {
        }

        explicit geom_value(const polygon_m_t<T>& p)
            : m_polygon_m(new polygon_m_t<T>(p))
        {
        }

        explicit geom_value(const polygon_zm_t<T>& p)
            : m_polygon_zm(new polygon_zm_t<T>(p))
        {
        }

        // multipolygon

        explicit geom_value(const multipolygon_t<T>& p)
            : m_multipolygon(new multipolygon_t<T>(p))
        {
        }

        explicit geom_value(const multipolygon_z_t<T>& p)
            : m_multipolygon_z(new multipolygon_z_t<T>(p))
        {
        }

        explicit geom_value(const multipolygon_m_t<T>& p)
            : m_multipolygon_m(new multipolygon_m_t<T>(p))
        {
        }

        explicit geom_value(const multipolygon_zm_t<T>& p)
            : m_multipolygon_zm(new multipolygon_zm_t<T>(p))
        {
        }
    };

    geom_value m_value        = {};
    geometry_type m_geom_type = geometry_type::GEOMETRY;
    std::shared_ptr<geometrycollection_t<T>> m_geometrycollection;
    std::shared_ptr<geometrycollection_z_t<T>> m_geometrycollection_z;
    std::shared_ptr<geometrycollection_m_t<T>> m_geometrycollection_m;
    std::shared_ptr<geometrycollection_zm_t<T>> m_geometrycollection_zm;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return m_geom_type;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Geometry";
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        return dimension_type::XY;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        return 2;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        return {};
    }

    /// @private
    bool has_z_() const noexcept
    {
        return true;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return true;
    }

    // json

    /// @private
    static geometry_t<T> from_json_(const std::string& /*json*/)
    {
        geometry_t<T> res;
        return res;
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        switch (m_geom_type)
        {
            // point
            case geometry_type::POINT:
            {
                return m_value.m_point->json(precision);
            }
            case geometry_type::POINTZ:
            {
                return m_value.m_point_z->json(precision);
            }
            case geometry_type::POINTM:
            {
                return m_value.m_point_m->json(precision);
            }
            case geometry_type::POINTZM:
            {
                return m_value.m_point_zm->json(precision);
            }

            // multipoint
            case geometry_type::MULTIPOINT:
            {
                return m_value.m_multipoint->json(precision);
            }
            case geometry_type::MULTIPOINTZ:
            {
                return m_value.m_multipoint_z->json(precision);
            }
            case geometry_type::MULTIPOINTM:
            {
                return m_value.m_multipoint_m->json(precision);
            }
            case geometry_type::MULTIPOINTZM:
            {
                return m_value.m_multipoint_zm->json(precision);
            }

            // linestring
            case geometry_type::LINESTRING:
            {
                return m_value.m_linestring->json(precision);
            }
            case geometry_type::LINESTRINGZ:
            {
                return m_value.m_linestring_z->json(precision);
            }
            case geometry_type::LINESTRINGM:
            {
                return m_value.m_linestring_m->json(precision);
            }
            case geometry_type::LINESTRINGZM:
            {
                return m_value.m_linestring_zm->json(precision);
            }

            // multilinestring
            case geometry_type::MULTILINESTRING:
            {
                return m_value.m_multilinestring->json(precision);
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                return m_value.m_multilinestring_z->json(precision);
            }
            case geometry_type::MULTILINESTRINGM:
            {
                return m_value.m_multilinestring_m->json(precision);
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                return m_value.m_multilinestring_zm->json(precision);
            }

            // polygon
            case geometry_type::POLYGON:
            {
                return m_value.m_polygon->json(precision);
            }
            case geometry_type::POLYGONZ:
            {
                return m_value.m_polygon_z->json(precision);
            }
            case geometry_type::POLYGONM:
            {
                return m_value.m_polygon_m->json(precision);
            }
            case geometry_type::POLYGONZM:
            {
                return m_value.m_polygon_zm->json(precision);
            }

            // multipolygon
            case geometry_type::MULTIPOLYGON:
            {
                return m_value.m_multipolygon->json(precision);
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                return m_value.m_multipolygon_z->json(precision);
            }
            case geometry_type::MULTIPOLYGONM:
            {
                return m_value.m_multipolygon_m->json(precision);
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                return m_value.m_multipolygon_zm->json(precision);
            }
            case geometry_type::GEOMETRYCOLLECTION:
            case geometry_type::GEOMETRYCOLLECTIONZ:
            case geometry_type::GEOMETRYCOLLECTIONM:
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                return geometrycollection_json_(precision);
            }
            default:
            {
                return "";
            }
        }
    }

    // wkt

    /// @private
    static geometry_t<T> from_wkt_(const std::string& wkt)
    {
        if (is_geometrycollection_wkt_(wkt))
        {
            return from_geometrycollection_wkt_(wkt);
        }

        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        switch (data.geom_type)
        {
            case geometry_type::POINT:
                return geometry_t<T>(point_t<T>::from_wkt(wkt));
            case geometry_type::POINTZ:
                return geometry_t<T>(point_z_t<T>::from_wkt(wkt));
            case geometry_type::POINTM:
                return geometry_t<T>(point_m_t<T>::from_wkt(wkt));
            case geometry_type::POINTZM:
                return geometry_t<T>(point_zm_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINT:
                return geometry_t<T>(multipoint_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINTZ:
                return geometry_t<T>(multipoint_z_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINTM:
                return geometry_t<T>(multipoint_m_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOINTZM:
                return geometry_t<T>(multipoint_zm_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRING:
                return geometry_t<T>(linestring_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRINGZ:
                return geometry_t<T>(linestring_z_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRINGM:
                return geometry_t<T>(linestring_m_t<T>::from_wkt(wkt));
            case geometry_type::LINESTRINGZM:
                return geometry_t<T>(linestring_zm_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRING:
                return geometry_t<T>(multilinestring_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRINGZ:
                return geometry_t<T>(multilinestring_z_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRINGM:
                return geometry_t<T>(multilinestring_m_t<T>::from_wkt(wkt));
            case geometry_type::MULTILINESTRINGZM:
                return geometry_t<T>(multilinestring_zm_t<T>::from_wkt(wkt));
            case geometry_type::POLYGON:
                return geometry_t<T>(polygon_t<T>::from_wkt(wkt));
            case geometry_type::POLYGONZ:
                return geometry_t<T>(polygon_z_t<T>::from_wkt(wkt));
            case geometry_type::POLYGONM:
                return geometry_t<T>(polygon_m_t<T>::from_wkt(wkt));
            case geometry_type::POLYGONZM:
                return geometry_t<T>(polygon_zm_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGON:
                return geometry_t<T>(multipolygon_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGONZ:
                return geometry_t<T>(multipolygon_z_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGONM:
                return geometry_t<T>(multipolygon_m_t<T>::from_wkt(wkt));
            case geometry_type::MULTIPOLYGONZM:
                return geometry_t<T>(multipolygon_zm_t<T>::from_wkt(wkt));
            default:
            {
                throw exceptions::parse_error("invalid wkt string");
            }
        }
        return {};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        switch (m_geom_type)
        {
            // point
            case geometry_type::POINT:
            {
                return m_value.m_point->wkt(precision);
            }
            case geometry_type::POINTZ:
            {
                return m_value.m_point_z->wkt(precision);
            }
            case geometry_type::POINTM:
            {
                return m_value.m_point_m->wkt(precision);
            }
            case geometry_type::POINTZM:
            {
                return m_value.m_point_zm->wkt(precision);
            }

            // multipoint
            case geometry_type::MULTIPOINT:
            {
                return m_value.m_multipoint->wkt(precision);
            }
            case geometry_type::MULTIPOINTZ:
            {
                return m_value.m_multipoint_z->wkt(precision);
            }
            case geometry_type::MULTIPOINTM:
            {
                return m_value.m_multipoint_m->wkt(precision);
            }
            case geometry_type::MULTIPOINTZM:
            {
                return m_value.m_multipoint_zm->wkt(precision);
            }

            // linestring
            case geometry_type::LINESTRING:
            {
                return m_value.m_linestring->wkt(precision);
            }
            case geometry_type::LINESTRINGZ:
            {
                return m_value.m_linestring_z->wkt(precision);
            }
            case geometry_type::LINESTRINGM:
            {
                return m_value.m_linestring_m->wkt(precision);
            }
            case geometry_type::LINESTRINGZM:
            {
                return m_value.m_linestring_zm->wkt(precision);
            }

            // multilinestring
            case geometry_type::MULTILINESTRING:
            {
                return m_value.m_multilinestring->wkt(precision);
            }
            case geometry_type::MULTILINESTRINGZ:
            {
                return m_value.m_multilinestring_z->wkt(precision);
            }
            case geometry_type::MULTILINESTRINGM:
            {
                return m_value.m_multilinestring_m->wkt(precision);
            }
            case geometry_type::MULTILINESTRINGZM:
            {
                return m_value.m_multilinestring_zm->wkt(precision);
            }

            // polygon
            case geometry_type::POLYGON:
            {
                return m_value.m_polygon->wkt(precision);
            }
            case geometry_type::POLYGONZ:
            {
                return m_value.m_polygon_z->wkt(precision);
            }
            case geometry_type::POLYGONM:
            {
                return m_value.m_polygon_m->wkt(precision);
            }
            case geometry_type::POLYGONZM:
            {
                return m_value.m_polygon_zm->wkt(precision);
            }

            // multipolygon
            case geometry_type::MULTIPOLYGON:
            {
                return m_value.m_multipolygon->wkt(precision);
            }
            case geometry_type::MULTIPOLYGONZ:
            {
                return m_value.m_multipolygon_z->wkt(precision);
            }
            case geometry_type::MULTIPOLYGONM:
            {
                return m_value.m_multipolygon_m->wkt(precision);
            }
            case geometry_type::MULTIPOLYGONZM:
            {
                return m_value.m_multipolygon_zm->wkt(precision);
            }
            case geometry_type::GEOMETRYCOLLECTION:
            case geometry_type::GEOMETRYCOLLECTIONZ:
            case geometry_type::GEOMETRYCOLLECTIONM:
            case geometry_type::GEOMETRYCOLLECTIONZM:
            {
                return geometrycollection_wkt_(precision);
            }
            default:
            {
                return "";
            }
        }
    }
};

template <typename T, geometry_type GeometryType, typename AllocatorType>
class basic_geometrycollection
    : public std::vector<geometry_t<T>, AllocatorType>,
      public basic_geometry<basic_geometrycollection<T, GeometryType, AllocatorType>>
{
  public:
    using base_type = std::vector<geometry_t<T>, AllocatorType>;

    basic_geometrycollection()
        : base_type() {}

    basic_geometrycollection(typename base_type::iterator first, typename base_type::iterator last)
        : base_type(first, last)
    {
    }

    basic_geometrycollection(typename base_type::const_iterator first, typename base_type::const_iterator last)
        : base_type(first, last)
    {
    }

    basic_geometrycollection(std::initializer_list<geometry_t<T>> init)
        : base_type(init.begin(), init.end()) {}

  private:
    friend class basic_geometry<basic_geometrycollection<T, GeometryType, AllocatorType>>;

    static std::string trim(const std::string& text)
    {
        auto begin = text.begin();
        while (begin != text.end() and std::isspace(static_cast<unsigned char>(*begin)))
        {
            ++begin;
        }

        auto end = text.end();
        while (end != begin and std::isspace(static_cast<unsigned char>(*(end - 1))))
        {
            --end;
        }

        return std::string(begin, end);
    }

    static std::string compact_upper(const std::string& text)
    {
        std::string res;
        res.reserve(text.size());
        for (char c : text)
        {
            if (std::isspace(static_cast<unsigned char>(c)))
            {
                continue;
            }
            res.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
        }
        return res;
    }

    static geometry_type parse_collection_type(const std::string& wkt)
    {
        const auto compact = compact_upper(wkt);
        if (compact.find("GEOMETRYCOLLECTIONZM") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTIONZM;
        }
        if (compact.find("GEOMETRYCOLLECTIONZ") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTIONZ;
        }
        if (compact.find("GEOMETRYCOLLECTIONM") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTIONM;
        }
        if (compact.find("GEOMETRYCOLLECTION") == 0)
        {
            return geometry_type::GEOMETRYCOLLECTION;
        }
        throw exceptions::parse_error("invalid geometry collection wkt string");
    }

    static std::vector<std::string> split_children(const std::string& text)
    {
        std::vector<std::string> res;
        int depth = 0;
        std::string current;
        for (char c : text)
        {
            if (c == ',' and depth == 0)
            {
                auto child = trim(current);
                if (child.empty())
                {
                    throw exceptions::parse_error("empty geometry collection child");
                }
                res.push_back(child);
                current.clear();
                continue;
            }

            if (c == '(')
            {
                ++depth;
            }
            else if (c == ')')
            {
                --depth;
                if (depth < 0)
                {
                    throw exceptions::parse_error("unbalanced geometry collection child");
                }
            }
            current.push_back(c);
        }

        if (depth != 0)
        {
            throw exceptions::parse_error("unbalanced geometry collection child");
        }

        auto child = trim(current);
        if (not child.empty())
        {
            res.push_back(child);
        }
        return res;
    }

    static std::string collection_body(const std::string& wkt)
    {
        const auto text = trim(wkt);
        const auto first_paren = text.find('(');
        if (first_paren == std::string::npos)
        {
            const auto compact = compact_upper(text);
            if (compact.find("EMPTY") != std::string::npos)
            {
                return "";
            }
            throw exceptions::parse_error("invalid geometry collection wkt string");
        }

        int depth = 0;
        for (size_t i = first_paren; i < text.size(); ++i)
        {
            if (text[i] == '(')
            {
                ++depth;
            }
            else if (text[i] == ')')
            {
                --depth;
                if (depth == 0)
                {
                    const auto tail = trim(text.substr(i + 1));
                    if (not tail.empty())
                    {
                        throw exceptions::parse_error("invalid geometry collection wkt string");
                    }
                    return text.substr(first_paren + 1, i - first_paren - 1);
                }
                if (depth < 0)
                {
                    throw exceptions::parse_error("invalid geometry collection wkt string");
                }
            }
        }

        throw exceptions::parse_error("invalid geometry collection wkt string");
    }

    geometry_type geom_type_() const noexcept
    {
        return GeometryType;
    }

    bool is_closed_() const noexcept
    {
        for (const auto& geom : *this)
        {
            if (not geom.is_closed())
            {
                return false;
            }
        }
        return true;
    }

    void throw_for_invalid_() const
    {
        for (const auto& geom : *this)
        {
            geom.throw_for_invalid();
        }
    }

    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& geom : *this)
        {
            res.extend(geom.bounds());
        }
        return res;
    }

    static basic_geometrycollection<T, GeometryType, AllocatorType> from_json_(const std::string& /*json*/)
    {
        throw exceptions::not_implemented_error("GeometryCollection from_json is not implemented");
    }

    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        ss << "{\"type\":\"GeometryCollection\",\"geometries\":[";
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << (*this)[i].json(precision);
        }
        ss << "]}";
        return ss.str();
    }

    static basic_geometrycollection<T, GeometryType, AllocatorType> from_wkt_(const std::string& wkt)
    {
        const auto parsed_type = parse_collection_type(wkt);
        if (parsed_type != GeometryType)
        {
            throw exceptions::parse_error("invalid wkt string");
        }

        const auto body = trim(collection_body(wkt));
        if (body.empty())
        {
            return {};
        }

        auto children = split_children(body);
        basic_geometrycollection<T, GeometryType, AllocatorType> res;
        res.reserve(children.size());
        for (const auto& child : children)
        {
            res.emplace_back(geometry_t<T>::from_wkt(child));
        }
        return res;
    }

    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        ss << "GEOMETRYCOLLECTION";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        if (this->empty())
        {
            ss << " EMPTY";
            return ss.str();
        }

        ss << "(";
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << (*this)[i].wkt(precision);
        }
        ss << ")";
        return ss.str();
    }
};

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTION),
      m_geometrycollection(new geometrycollection_t<T>(value))
{
}

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_z_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONZ),
      m_geometrycollection_z(new geometrycollection_z_t<T>(value))
{
}

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_m_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONM),
      m_geometrycollection_m(new geometrycollection_m_t<T>(value))
{
}

template <typename T>
geometry_t<T>::geometry_t(const geometrycollection_zm_t<T>& value)
    : m_geom_type(geometry_type::GEOMETRYCOLLECTIONZM),
      m_geometrycollection_zm(new geometrycollection_zm_t<T>(value))
{
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection)
    {
        m_geometrycollection.reset(new geometrycollection_t<T>(*other.m_geometrycollection));
    }
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_z_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection_z)
    {
        m_geometrycollection_z.reset(new geometrycollection_z_t<T>(*other.m_geometrycollection_z));
    }
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_m_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection_m)
    {
        m_geometrycollection_m.reset(new geometrycollection_m_t<T>(*other.m_geometrycollection_m));
    }
}

template <typename T>
void geometry_t<T>::copy_geometrycollection_zm_(const geometry_t<T>& other)
{
    if (other.m_geometrycollection_zm)
    {
        m_geometrycollection_zm.reset(new geometrycollection_zm_t<T>(*other.m_geometrycollection_zm));
    }
}

template <typename T>
bool geometry_t<T>::is_geometrycollection_wkt_(const std::string& wkt)
{
    std::string compact;
    compact.reserve(wkt.size());
    for (char c : wkt)
    {
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            continue;
        }
        compact.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    return compact.find("GEOMETRYCOLLECTION") == 0;
}

template <typename T>
geometry_type geometry_t<T>::geometrycollection_type_from_wkt_(const std::string& wkt)
{
    std::string compact;
    compact.reserve(wkt.size());
    for (char c : wkt)
    {
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            continue;
        }
        compact.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
    }
    if (compact.find("GEOMETRYCOLLECTIONZM") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTIONZM;
    }
    if (compact.find("GEOMETRYCOLLECTIONZ") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTIONZ;
    }
    if (compact.find("GEOMETRYCOLLECTIONM") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTIONM;
    }
    if (compact.find("GEOMETRYCOLLECTION") == 0)
    {
        return geometry_type::GEOMETRYCOLLECTION;
    }
    throw exceptions::parse_error("invalid geometry collection wkt string");
}

template <typename T>
geometry_t<T> geometry_t<T>::from_geometrycollection_wkt_(const std::string& wkt)
{
    switch (geometrycollection_type_from_wkt_(wkt))
    {
        case geometry_type::GEOMETRYCOLLECTION:
            return geometry_t<T>(geometrycollection_t<T>::from_wkt(wkt));
        case geometry_type::GEOMETRYCOLLECTIONZ:
            return geometry_t<T>(geometrycollection_z_t<T>::from_wkt(wkt));
        case geometry_type::GEOMETRYCOLLECTIONM:
            return geometry_t<T>(geometrycollection_m_t<T>::from_wkt(wkt));
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return geometry_t<T>(geometrycollection_zm_t<T>::from_wkt(wkt));
        default:
            throw exceptions::parse_error("invalid geometry collection wkt string");
    }
}

template <typename T>
std::string geometry_t<T>::geometrycollection_json_(std::int32_t precision) const
{
    switch (m_geom_type)
    {
        case geometry_type::GEOMETRYCOLLECTION:
            return m_geometrycollection->json(precision);
        case geometry_type::GEOMETRYCOLLECTIONZ:
            return m_geometrycollection_z->json(precision);
        case geometry_type::GEOMETRYCOLLECTIONM:
            return m_geometrycollection_m->json(precision);
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return m_geometrycollection_zm->json(precision);
        default:
            return "";
    }
}

template <typename T>
std::string geometry_t<T>::geometrycollection_wkt_(std::int32_t precision) const
{
    switch (m_geom_type)
    {
        case geometry_type::GEOMETRYCOLLECTION:
            return m_geometrycollection->wkt(precision);
        case geometry_type::GEOMETRYCOLLECTIONZ:
            return m_geometrycollection_z->wkt(precision);
        case geometry_type::GEOMETRYCOLLECTIONM:
            return m_geometrycollection_m->wkt(precision);
        case geometry_type::GEOMETRYCOLLECTIONZM:
            return m_geometrycollection_zm->wkt(precision);
        default:
            return "";
    }
}

template <typename T>
geometrycollection_t<T>* geometry_t<T>::get_geometrycollection()
{
    assert(is_geometrycollection());
    return m_geometrycollection.get();
}

template <typename T>
geometrycollection_z_t<T>* geometry_t<T>::get_geometrycollection_z()
{
    assert(is_geometrycollection_z());
    return m_geometrycollection_z.get();
}

template <typename T>
geometrycollection_m_t<T>* geometry_t<T>::get_geometrycollection_m()
{
    assert(is_geometrycollection_m());
    return m_geometrycollection_m.get();
}

template <typename T>
geometrycollection_zm_t<T>* geometry_t<T>::get_geometrycollection_zm()
{
    assert(is_geometrycollection_zm());
    return m_geometrycollection_zm.get();
}

template <typename>
struct is_basic_geometrycollection : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection<geometrycollection_t<T>> : std::true_type
{};

template <typename>
struct is_basic_geometrycollection_z : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection_z<geometrycollection_z_t<T>> : std::true_type
{};

template <typename>
struct is_basic_geometrycollection_m : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection_m<geometrycollection_m_t<T>> : std::true_type
{};

template <typename>
struct is_basic_geometrycollection_zm : std::false_type
{};

template <typename T>
struct is_basic_geometrycollection_zm<geometrycollection_zm_t<T>> : std::true_type
{};

using geometrycollection    = geometrycollection_t<double>;
using geometrycollection_z  = geometrycollection_z_t<double>;
using geometrycollection_m  = geometrycollection_m_t<double>;
using geometrycollection_zm = geometrycollection_zm_t<double>;

using GeometryCollection   = geometrycollection_t<double>;
using GeometryCollectionZ  = geometrycollection_z_t<double>;
using GeometryCollectionM  = geometrycollection_m_t<double>;
using GeometryCollectionZM = geometrycollection_zm_t<double>;

using geometry = geometry_t<double>;
using Geometry = geometry_t<double>;

}  // namespace shapes
}  // namespace simo

// #include <simo/geom/detail/bounds.hpp>

// #include <simo/geom/point.hpp>

// #include <simo/geom/multipoint.hpp>

// #include <simo/geom/linestring.hpp>

// #include <simo/geom/multilinestring.hpp>

// #include <simo/geom/polygon.hpp>

// #include <simo/geom/multipolygon.hpp>

// #include <simo/geom/geometrycollection.hpp>


#include <ciso646>
// #include <simo/geom/geometry.hpp>


// #include <simo/geom/linearring.hpp>

// #include <simo/io/polyline.hpp>

// #include <simo/algorithm/measurements.hpp>

// #include <simo/algorithm/predicates.hpp>

// #include <simo/algorithm/operations.hpp>

// #include <simo/algorithm/transformations.hpp>


#endif  // SIMO_SHAPES_HPP
