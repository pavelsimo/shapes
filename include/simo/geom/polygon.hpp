#pragma once

#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/linearring.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

class Polygon : public BasicGeometry<Polygon>
{
  public:
    ///
    std::unique_ptr<LinearRing> exterior;

    ///
    std::unique_ptr<std::vector<LinearRing>> interiors;

    /*!
     * @brief creates an empty Polygon
     *
     * @since 0.0.1
     */
    Polygon() = default;

    /*!
     * @brief DOCUMENT ME!
     * @param exterior
     */
    explicit Polygon(const std::vector<Point>& exterior)
        : exterior(std::make_unique<LinearRing>(exterior))
    {
    }

    /*!
     * @brief DOCUMENT ME!
     * @param exterior
     * @param interiors
     */
    Polygon(const std::vector<Point>& exterior, const std::vector<std::vector<Point>>& interiors)
        : exterior(std::make_unique<LinearRing>(exterior))
    {
    }

    /// @private
    GeometryType type_() const
    {
        return GeometryType::POLYGON;
    }

    /// @private
    std::string type_str_() const
    {
        return "Polygon";
    }

    /// @private
    bool empty_() const
    {
        throw exceptions::not_implemented_error();
    }

    /// @private
    size_t size_() const
    {
        throw exceptions::not_implemented_error();
    }

    /// @private
    bool is_closed_() const
    {
        throw exceptions::not_implemented_error();
    }

    /// @private
    std::vector<std::tuple<double, double>> xy_() const
    {
        throw exceptions::not_implemented_error();
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        throw exceptions::not_implemented_error();
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        throw exceptions::not_implemented_error();
    }

    /// @private
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief creates a Polygon from a geojson string
     *
     * @param json the geojson string
     * @return a Polygon object
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @since 0.0.1
     */
    static Polygon from_json(const std::string&)
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief dumps the geojson representation of the Polygon
     *
     * @note RFC7946 <https://tools.ietf.org/html/rfc7946>
     *
     * @return a geojson string
     *
     * @since 0.0.1
     */
    std::string json()
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief creates a Polygon from a WKT string
     *
     * @param wkt the WKT string
     * @return a Polygon object
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @since 0.0.1
     */
    static Polygon from_wkt(const std::string&)
    {
        throw exceptions::not_implemented_error();
    }

    /*!
     * @brief creates a Polygon from a WKT string
     *
     * @param wkt the WKT string
     * @return a Polygon object
     *
     * @note WKT <https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry>
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        throw exceptions::not_implemented_error();
    }
};

}  // namespace shapes
}  // namespace simo