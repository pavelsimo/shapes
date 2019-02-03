#pragma once

#include <vector>
#include <memory>
#include <simo/shapes_fwd.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

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

class Geometry
{
  public:
    /*!
     * @brief Returns the geometry type
     * @return the geometry type
     */
    virtual GeometryType geom_type() const = 0;

    /*!
     * @brief Returns the geometry type as a string (e.g. LineString)
     * @return the geometry type as a string
     */
    virtual std::string geom_type_str() const = 0;

    /*!
     * @brief Returns true if the geometry is empty, otherwise false
     * @return
     */
    virtual bool empty() const = 0;

    /*!
     * @brief Returns the size of the geometry
     * @return the size of the geometry
     */
    virtual size_t size() const = 0;

    /*!
     * @brief Returns the number of dimensions of the geometry
     * @return the number of dimensions of the geometry
     */
    virtual int8_t ndim() const = 0;

    /*!
     * @brief Returns the geometry bounding box
     * @return the geometry bounding box
     */
    virtual Bounds bounds() const = 0;

    /*!
     * @brief Returns a clone of the given geometry
     * @return a geometry clone
     */
    virtual std::unique_ptr<Geometry> clone() = 0;

    /*!
     *
     * @return
     */
    virtual std::vector<std::tuple<double, double>> xy() const = 0;

    /*!
     *
     * @return
     */
    virtual std::vector<std::tuple<double, double, double>> xyz() const = 0;
};

template <typename T>
class BasicGeometry : public Geometry
{
  public:
    /// serialization precision
    int8_t precision = 6;

    GeometryType geom_type() const override
    {
        return static_cast<const T*>(this)->geom_type_();
    }

    std::string geom_type_str() const override
    {
        return static_cast<const T*>(this)->geom_type_str_();
    }

    bool empty() const override
    {
        return static_cast<const T*>(this)->empty_();
    }

    size_t size() const override
    {
        return static_cast<const T*>(this)->size_();
    }

    std::unique_ptr<Geometry> clone() override
    {
        return std::unique_ptr<T>(new T(*static_cast<T*>(this)));
    };

    std::vector<std::tuple<double, double>> xy() const override
    {
        return static_cast<const T*>(this)->xy_();
    }

    std::vector<std::tuple<double, double, double>> xyz() const override
    {
        return static_cast<const T*>(this)->xyz_();
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