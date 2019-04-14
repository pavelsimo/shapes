#pragma once

#include <ciso646>
#include <vector>
#include <memory>
#include <simo/shapes_fwd.hpp>
#include <simo/geom/bounds.hpp>
#include <simo/geom/types.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief abstract class for all geometries
 * @tparam T the geometry type (e.g. Point, Polygon, LineString)
 * @ingroup geometry
 *
 * @since 0.0.1
 */
template <typename T>
class BaseGeometry
{
  public:
    /// a spatial reference identifier (SRID) is a unique identifier associated with a specific coordinate system
    int32_t srid = -1;

    /// the geometry bounds
    Bounds bounds{};

    /// the dimension type is either 2D (x, y), 3D (x, y, z), 4D (x, y, z, m) or 2D with measure-coordinate (x, y, m)
    DimensionType dim = DimensionType::XY;

    /// serialization precision
    int8_t precision = 1;

    /*!
     * @brief returns the geometry type (e.g. GeometryType::Point, GeometryType::MultiPoint)
     * @return the geometry type
     *
     * @since 0.0.1
     */
    GeometryType type() const
    {
        return static_cast<const T*>(this)->type_();
    }

    /*!
     * @brief returns the geometry detailed type (e.g. GeometryType::PointZ, GeometryType::MultiPointZM)
     * @return the geometry detailed type
     *
     * @since 0.0.1
     */
    GeometryDetailedType detailed_type() const
    {
        auto type = static_cast<const T*>(this)->type_();
        return get_geom_detailed_type(type, dim);
    }

    /*!
     * @brief returns the geometry type as a string (e.g. Point, LineString)
     * @return the geometry type as a string
     *
     * @since 0.0.1
     */
    std::string type_str() const
    {
        return static_cast<const T*>(this)->type_str_();
    }

    /*!
     * @brief returns true if the geometry is empty
     * @return true if the the geometry is empty, otherwise false
     *
     * @since 0.0.1
     */
    bool empty() const
    {
        return static_cast<const T*>(this)->empty_();
    }

    /*!
     * @brief returns the geometry size
     * @return the size of the geometry
     *
     * @since 0.0.1
     */
    size_t size() const
    {
        return static_cast<const T*>(this)->size_();
    }

    /*!
     * @brief returns the geometry (x, y) coordinates as a tuple
     * @return a vector of (x, y) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double>> xy() const
    {
        return static_cast<const T*>(this)->xy_();
    }

    /*!
     * @brief returns the geometry (x, y, z) coordinates as a tuple
     * @return a vector of (x, y, z) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double, double>> xyz() const
    {
        return static_cast<const T*>(this)->xyz_();
    }

    /*!
     * @brief returns the geometry (x, y, m) coordinates as a tuple
     * @return a vector of (x, y, m) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double, double>> xym() const
    {
        return static_cast<const T*>(this)->xym_();
    }

    /*!
     * @brief returns the geometry (x, y, z, m) coordinates as a tuple
     * @return a vector of (x, y, z, m) tuples
     *
     * @since 0.0.1
     */
    std::vector<std::tuple<double, double, double, double>> xyzm() const
    {
        return static_cast<const T*>(this)->xyzm_();
    }

    /*!
     * @brief whether the geometry has z-coordinate
     * @return true if the geometry has z-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    bool has_z() const
    {
        return dim == DimensionType::XYZ or dim == DimensionType::XYZM;
    }

    /*!
     * @brief whether the geometry has m-coordinate
     * @return true if the geometry has m-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    bool has_m() const
    {
        return dim == DimensionType::XYM or dim == DimensionType::XYZM;
    }

    /*!
     * @brief whether the geometry is closed
     * @return true if the geometry is closed, otherwise false
     *
     * @since 0.0.1
     */
    bool is_closed() const
    {
        return static_cast<const T*>(this)->is_closed_();
    }

    /*!
     * @brief returns the number of dimensions of the geometry
     * @return the number of dimensions
     * @note the number of dimensions is (x, y) = 2, (x, y, z) = 3, (x, y, m) = 3 and (x, y, z, m) = 4
     *
     * @since 0.0.1
     */
    int8_t ndim() const
    {
        return get_ndim(dim);
    }
};

/*!
 * @brief the geometry type
 *
 * @since 0.0.1
 */
typedef union Geometry
{
    Point* point;                            ///< Point value
    MultiPoint* multipoint;                  ///< MultiPoint value
    LineString* linestring;                  ///< LineString value
    MultiLineString* multilinestring;        ///< MultiLineString value
    Polygon* polygon;                        ///< Polygon value
    MultiPolygon* multipolygon;              ///< MultiPolygon value
    GeometryCollection* geometrycollection;  ///< GeometryCollection value
} Geometry;

}  // namespace shapes
}  // namespace simo