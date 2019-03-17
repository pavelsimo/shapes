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

/// geometry interface
class Geometry
{
  public:
    /// virtual destructor
    virtual ~Geometry() = default;

    /*!
     * @brief returns the geometry type (e.g. GeometryType::Point, GeometryType::MultiPoint)
     * @return the geometry type
     *
     * @since 0.0.1
     */
    virtual GeometryType type() const = 0;

    /*!
     * @brief returns the geometry detailed type (e.g. GeometryType::PointZ, GeometryType::MultiPointZM)
     * @return the geometry detailed type
     *
     * @since 0.0.1
     */
    virtual GeometryDetailedType detailed_type() const = 0;

    /*!
     * @brief returns the geometry type as a string (e.g. Point, LineString)
     * @return the geometry type as a string
     *
     * @since 0.0.1
     */
    virtual std::string type_str() const = 0;

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
     * @brief returns the dimension type of the geometry
     * @return the dimension type
     *
     * @note the dimension type is (x, y), (x, y, z), (x, y, m) and (x, y, z, m)
     *
     * @since 0.0.1
     */
    virtual DimensionType dim() const = 0;

    /*!
     * @brief set the dimension type
     * @param value the dimension type
     *
     * @since 0.0.1
     */
    virtual void set_dim(DimensionType value) = 0;

    /*!
     * @brief returns the number of dimensions of the geometry
     * @return the number of dimensions
     *
     * @note the number of dimensions is (x, y) = 2, (x, y, z) = 3, (x, y, m) = 3 and (x, y, z, m) = 4
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
    virtual Bounds& bounds() = 0;

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

    /*!
     * @brief returns the geometry (x, y, m) coordinates as a tuple
     * @return a vector of (x, y, m) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double, double>> xym() const = 0;

    /*!
     * @brief returns the geometry (x, y, z, m) coordinates as a tuple
     * @return a vector of (x, y, z, m) tuples
     *
     * @since 0.0.1
     */
    virtual std::vector<std::tuple<double, double, double, double>> xyzm() const = 0;

    /*!
     * @brief whether the geometry has z-coordinate
     * @return true if the geometry has z-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool has_z() const = 0;

    /*!
     * @brief whether the geometry has m-coordinate
     * @return true if the geometry has m-coordinate, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool has_m() const = 0;

    /*!
     * @brief whether the geometry is closed
     * @return true if the geometry is closed, otherwise false
     *
     * @since 0.0.1
     */
    virtual bool is_closed() const = 0;

    /// @todo (pavel) is_3d()
    /// @todo (pavel) is_measured()
    /// @todo (pavel) detailed_type_str()
};

/// basic geometry type
template <typename Derived>
class BasicGeometry : public Geometry
{
  public:
    /// serialization precision
    int8_t precision = 1;

    /// a spatial reference identifier (SRID) is a unique identifier associated with a specific coordinate system
    int32_t srid = -1;

    /// @copydoc Geometry::type()
    GeometryType type() const override
    {
        return static_cast<const Derived*>(this)->type_();
    }

    /// @copydoc Geometry::detailed_type()
    GeometryDetailedType detailed_type() const override
    {
        auto type = static_cast<const Derived*>(this)->type_();
        switch (dim_)
        {
            case DimensionType::XY:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRY;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINT;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRING;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGON;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINT;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRING;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGON;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTION;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRING;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVE;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGON;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVE;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACE;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVE;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACE;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACE;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TIN;
                }
            }
            case DimensionType::XYZ:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRYZ;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINTZ;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRINGZ;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGONZ;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINTZ;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRINGZ;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGONZ;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTIONZ;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRINGZ;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVEZ;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGONZ;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVEZ;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACEZ;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVEZ;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACEZ;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACEZ;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TINZ;
                }
            }
            case DimensionType::XYM:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRYM;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINTM;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRINGM;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGONM;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINTM;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRINGM;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGONM;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTIONM;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRINGM;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVEM;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGONM;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVEM;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACEM;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVEM;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACEM;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACEM;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TINM;
                }
            }
            case DimensionType::XYZM:
            {
                switch (type)
                {
                    case GeometryType::GEOMETRY:
                        return GeometryDetailedType::GEOMETRYZM;
                    case GeometryType::POINT:
                        return GeometryDetailedType::POINTZM;
                    case GeometryType::LINESTRING:
                        return GeometryDetailedType::LINESTRINGZM;
                    case GeometryType::POLYGON:
                        return GeometryDetailedType::POLYGONZM;
                    case GeometryType::MULTIPOINT:
                        return GeometryDetailedType::MULTIPOINTZM;
                    case GeometryType::MULTILINESTRING:
                        return GeometryDetailedType::MULTILINESTRINGZM;
                    case GeometryType::MULTIPOLYGON:
                        return GeometryDetailedType::MULTIPOLYGONZM;
                    case GeometryType::GEOMETRYCOLLECTION:
                        return GeometryDetailedType::GEOMETRYCOLLECTIONZM;
                    case GeometryType::CIRCULARSTRING:
                        return GeometryDetailedType::CIRCULARSTRINGZM;
                    case GeometryType::COMPOUNDCURVE:
                        return GeometryDetailedType::COMPOUNDCURVEZM;
                    case GeometryType::CURVEPOLYGON:
                        return GeometryDetailedType::CURVEPOLYGONZM;
                    case GeometryType::MULTICURVE:
                        return GeometryDetailedType::MULTICURVEZM;
                    case GeometryType::MULTISURFACE:
                        return GeometryDetailedType::MULTISURFACEZM;
                    case GeometryType::CURVE:
                        return GeometryDetailedType::CURVEZM;
                    case GeometryType::SURFACE:
                        return GeometryDetailedType::SURFACEZM;
                    case GeometryType::POLYHEDRALSURFACE:
                        return GeometryDetailedType::POLYHEDRALSURFACEZM;
                    case GeometryType::TIN:
                        return GeometryDetailedType::TINZM;
                }
            }
        }
        return GeometryDetailedType::GEOMETRY;
    }

    /// @copydoc Geometry::type_str()
    std::string type_str() const override
    {
        return static_cast<const Derived*>(this)->type_str_();
    }

    /// @copydoc Geometry::empty()
    bool empty() const override
    {
        return static_cast<const Derived*>(this)->empty_();
    }

    /// @copydoc Geometry::size()
    size_t size() const override
    {
        return static_cast<const Derived*>(this)->size_();
    }

    /// @copydoc Geometry::xy()
    std::vector<std::tuple<double, double>> xy() const override
    {
        return static_cast<const Derived*>(this)->xy_();
    }

    /// @copydoc Geometry::xyz()
    std::vector<std::tuple<double, double, double>> xyz() const override
    {
        return static_cast<const Derived*>(this)->xyz_();
    }

    /// @copydoc Geometry::xym()
    std::vector<std::tuple<double, double, double>> xym() const override
    {
        return static_cast<const Derived*>(this)->xym_();
    }

    /// @copydoc Geometry::xyzm()
    std::vector<std::tuple<double, double, double, double>> xyzm() const override
    {
        return static_cast<const Derived*>(this)->xyzm_();
    }

    /// @copydoc Geometry::dim()
    DimensionType dim() const override
    {
        return dim_;
    }

    /// @copydoc Geometry::set_dim()
    void set_dim(DimensionType value) override
    {
        dim_ = value;
    }

    /// @copydoc Geometry::bounds()
    Bounds& bounds() override
    {
        return bounds_;
    }

    /// @copydoc Geometry::has_z()
    bool has_z() const override
    {
        return dim_ == DimensionType::XYZ or dim_ == DimensionType::XYZM;
    }

    /// @copydoc Geometry::has_m()
    bool has_m() const override
    {
        return dim_ == DimensionType::XYM or dim_ == DimensionType::XYZM;
    }

    /// @copydoc Geometry::is_closed()
    bool is_closed() const override
    {
        return static_cast<const Derived*>(this)->is_closed_();
    }

    /// @copydoc Geometry::ndim()
    int8_t ndim() const override
    {
        switch (dim_)
        {
            case DimensionType::XYZM:
                return 4;
            case DimensionType::XYZ:
                // fall through
            case DimensionType::XYM:
                return 3;
            default:
                return 2;
        }
    }

  private:
    /// geometry bounds
    Bounds bounds_{};

    /// the dimension type (x, y), (x, y, z), (x, y, m) or (x, y, z, m)
    DimensionType dim_ = DimensionType::XY;
};

}  // namespace shapes
}  // namespace simo