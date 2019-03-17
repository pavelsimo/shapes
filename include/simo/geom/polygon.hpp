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

class Polygon : public BasicGeometry<Polygon>
{
  public:
    /// linear ring that represents the shell of the polygon
    LinearRing exterior;

    /// collection of linear rings that represent the holes of the polygon
    std::vector<LinearRing> interiors{};

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
            Bounds& b     = bounds();
            exterior      = LinearRing(*ring);
            Bounds& b_ext = exterior.bounds();
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);
            ring++;
            for (; ring != rings.end(); ++ring)
            {
                interiors.emplace_back(*ring);
                Bounds& b_int = interiors[interiors.size() - 1].bounds();
                b.extend(b_int.minx, b_int.miny);
                b.extend(b_int.maxx, b_int.maxy);
            }
        }
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
    static Polygon from_json(const std::string& /*json*/)
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
    static Polygon from_wkt(const std::string& /*wkt*/)
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

  private:
    /// for implementation encapsulation
    friend class BasicGeometry;

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
};

}  // namespace shapes
}  // namespace simo