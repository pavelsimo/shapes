#pragma once

#include <vector>
#include <memory>
#include <simo/shapes_fwd.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/// geometry types as defined by the OpenGIS "Consortium Simple Features for SQL" specification
enum class GeometryType
{
    GEOMETRY        = 0,
    POINT           = 1,
    CURVE           = 2,
    LINESTRING      = 3,
    SURFACE         = 4,
    POLYGON         = 5,
    COLLECTION      = 6,
    MULTIPOINT      = 7,
    MULTICURVE      = 8,
    MULTILINESTRING = 9,
    MULTISURFACE    = 10,
    MULTIPOLYGON    = 11
};

/// geometry interface
class Geometry
{
  public:
    /*!
     * @brief returns the geometry type
     * @return the geometry type
     *
     * @since 0.0.1
     */
    virtual GeometryType geom_type() const = 0;

    /*!
     * @brief returns the geometry type as a string (e.g. Point, LineString)
     * @return the geometry type as a string
     *
     * @since 0.0.1
     */
    virtual std::string geom_type_str() const = 0;

    /*!
     * @brief returns true if the geometry is empty
     * @return true if the the geometry is empty, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool empty() const = 0;

    /*!
     * @brief returns the geometry size
     * @return the size of the geometry
     *
     * @since 0.0.1
     */
    virtual size_t size() const = 0;

    /*!
     * @brief returns the number of dimensions of the geometry
     * @return the number of dimensions of the geometry
     *
     * @since 0.0.1
     */
    virtual int8_t ndim() const = 0;

    /*!
     * @brief returns the geometry bounds
     * @return the geometry bounds
     *
     * @since 0.0.1
     */
    virtual Bounds bounds() const = 0;

    /*!
     * @brief returns a clone of the given geometry
     * @return a geometry clone
     *
     * @since 0.0.1
     */
    virtual std::unique_ptr<Geometry> clone() = 0;

    /*!
     * @brief returns the geometry (x, y) coordinates as a tuple
     * @return a vector of (x, y) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double>> xy() const = 0;

    /*!
     * @brief returns the geometry (x, y, z) coordinates as a tuple
     * @return a vector of (x, y, z) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double, double>> xyz() const = 0;
};

/// basic geometry type
template <typename Derived>
class BasicGeometry : public Geometry
{
  public:
    /// serialization precision
    int8_t precision = 6;

    GeometryType geom_type() const override
    {
        return static_cast<const Derived*>(this)->geom_type_();
    }

    std::string geom_type_str() const override
    {
        return static_cast<const Derived*>(this)->geom_type_str_();
    }

    bool empty() const override
    {
        return static_cast<const Derived*>(this)->empty_();
    }

    size_t size() const override
    {
        return static_cast<const Derived*>(this)->size_();
    }

    std::unique_ptr<Geometry> clone() override
    {
        return std::unique_ptr<Derived>(new Derived(*static_cast<Derived*>(this)));
    };

    std::vector<std::tuple<double, double>> xy() const override
    {
        return static_cast<const Derived*>(this)->xy_();
    }

    std::vector<std::tuple<double, double, double>> xyz() const override
    {
        return static_cast<const Derived*>(this)->xyz_();
    }

    int8_t ndim() const override
    {
        return m_ndim;
    }

    Bounds bounds() const override
    {
        return m_bounds;
    }

  protected:
    /// geometry bounds
    Bounds m_bounds;

    /// number of dimensions
    int8_t m_ndim = 2;
};

}  // namespace shapes
}  // namespace simo