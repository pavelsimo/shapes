#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <utility>
#include <simo/geom/geometry.hpp>
#include <simo/geom/linearring.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief represents a polygon
 *
 * @since 0.0.1
 */
class Polygon : public BaseGeometry<Polygon>
{
  public:
    /// linear ring that represents the shell of the polygon
    LinearRing exterior;

    /// collection of linear rings that represent the holes of the polygon
    std::vector<LinearRing> interiors;

    /*!
     * @brief creates an empty Polygon
     *
     * @since 0.0.1
     */
    Polygon() = default;

    /*!
     * @brief creates a Polygon
     * @param rings a LinearRing sequence with the shell and holes of the polygon
     *
     * @since 0.0.1
     */
    Polygon(std::initializer_list<LinearRing> rings)
    {
        if (rings.size() >= 1)
        {
            auto ring     = rings.begin();
            Bounds& b     = bounds;
            exterior      = LinearRing(*ring);
            Bounds& b_ext = exterior.bounds;
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);
            ring++;
            for (; ring != rings.end(); ++ring)
            {
                interiors.emplace_back(*ring);
                Bounds& b_int = interiors[interiors.size() - 1].bounds;
                b.extend(b_int.minx, b_int.miny);
                b.extend(b_int.maxx, b_int.maxy);
            }
        }
    }

    /*!
     * @brief creates a Polygon
     * @param shell the shell of the polygon as a Point sequence
     *
     * @since 0.0.1
     */
    explicit Polygon(const std::vector<Point>& shell)
        : exterior(shell)
    {
        Bounds& b     = bounds;
        Bounds& b_ext = exterior.bounds;
        b.extend(b_ext.minx, b_ext.miny);
        b.extend(b_ext.maxx, b_ext.maxy);
    }

    /*!
     * @brief creates a Polygon
     * @param shell the shell of the polygon as a Point sequence
     * @param holes one or more collection of points, each representing a hole in the polygon
     *
     * @since 0.0.1
     */
    Polygon(const std::vector<Point>& shell, const std::vector<std::vector<Point>>& holes)
        : exterior(shell)
    {
        Bounds& b     = bounds;
        Bounds& b_ext = exterior.bounds;
        b.extend(b_ext.minx, b_ext.miny);
        b.extend(b_ext.maxx, b_ext.maxy);
        interiors.reserve(holes.size());
        for (const auto& hole : holes)
        {
            interiors.emplace_back(hole);
            Bounds& b_int = interiors[interiors.size() - 1].bounds;
            b.extend(b_int.minx, b_int.miny);
            b.extend(b_int.maxx, b_int.maxy);
        }
    }

    /*!
     * @brief creates a Polygon from a geojson string
     * @param json the geojson string
     * @return a Polygon object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static Polygon from_json(const std::string& /*json*/)
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief dumps the geojson representation of the Polygon
     * @sa https://tools.ietf.org/html/rfc7946
     * @return a geojson string
     *
     * @since 0.0.1
     */
    std::string json()
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a Polygon from a WKT string
     * @param wkt the WKT string
     * @return a Polygon object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static Polygon from_wkt(const std::string& /*wkt*/)
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a Polygon from a WKT string
     * @param wkt the WKT string
     * @return a Polygon object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        throw exceptions::NotImplementedError();
    }

    /// @todo (pavel) add from_bounds method

  private:
    /// for allow BaseGeometry to access Polygon private members
    friend class BaseGeometry<Polygon>;

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
        return size_() == 0;
    }

    /// @private
    size_t size_() const
    {
        size_t size = exterior.size();
        for (const auto& interior : interiors)
        {
            size += interior.size();
        }
        return size;
    }

    /// @private
    bool is_closed_() const
    {
        return true;
    }

    /// @private
    std::vector<std::tuple<double, double>> xy_() const
    {
        throw exceptions::NotImplementedError();
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        throw exceptions::NotImplementedError();
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        throw exceptions::NotImplementedError();
    }

    /// @private
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        throw exceptions::NotImplementedError();
    }
};

}  // namespace shapes
}  // namespace simo