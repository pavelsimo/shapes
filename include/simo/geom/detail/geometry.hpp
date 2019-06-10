#pragma once

#include <ciso646>
#include <vector>
#include <memory>
#include <simo/shapes_fwd.hpp>
#include <simo/geom/detail/bounds.hpp>
#include <simo/geom/detail/types.hpp>
#include <simo/geom/detail/utils.hpp>
#include <simo/exceptions.hpp>

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
    geometry_type geom_type() const noexcept
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
        return static_cast<const T*>(this)->tagged_text_();
    }

    /*!
     * @brief Returns the dimension type for the geometry
     * @return the dimension type
     *
     * @since 0.0.1
     */
    dimension_type dim() const noexcept
    {
        return static_cast<const T*>(this)->dim_();
    }

    /*!
     * @brief Returns the number of dimensions of the geometry
     * @return the number of dimensions
     * @note the number of dimensions is (x, y) = 2, (x, y, z) = 3, (x, y, m) = 3 and (x, y, z, m) = 4
     *
     * @since 0.0.1
     */
    int32_t ndim() const noexcept
    {
        return static_cast<const T*>(this)->ndim_();
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
    bool has_z() const noexcept
    {
        return static_cast<const T*>(this)->has_z_();
    }

    /*!
     * @brief Whether the geometry has the m-coordinate (measurement coordinate)
     * @return true if the geometry has m-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    bool has_m() const noexcept
    {
        return static_cast<const T*>(this)->has_m_();
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
};

}  // namespace shapes
}  // namespace simo