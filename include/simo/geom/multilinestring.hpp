#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/geometry_sequence.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief LineString collection
 *
 * @since 0.0.1
 */
class MultiLineString : public BaseGeometry<MultiLineString>, public GeometrySequence<LineString>
{
  public:

    /*!
     * @brief creates an empty MultiLineString
     *
     * @since 0.0.1
     */
    MultiLineString() = default;

    /*!
     * @brief creates a MultiLineString from a geojson string
     * @param json the geojson string
     * @return a MultiLineString object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static MultiLineString from_json(const std::string& /*json*/)
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief dumps the geojson representation of the MultiLineString
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a MultiLineString from a WKT string
     * @param wkt the WKT string
     * @return a MultiLineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static MultiLineString from_wkt(const std::string& /*wkt*/)
    {
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a MultiLineString from a WKT string
     * @param wkt the WKT string
     * @return a MultiLineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        throw exceptions::NotImplementedError();
    }

  private:
    /// for allow BaseGeometry to access MultiLineString private members
    friend class BaseGeometry<MultiLineString>;

    /// @private
    GeometryType type_() const
    {
        return GeometryType::MULTILINESTRING;
    }

    /// @private
    std::string type_str_() const
    {
        return "MultiLineString";
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

    /// @private
    bool empty_() const
    {
        throw exceptions::NotImplementedError();
    }

    /// @private
    size_t size_() const
    {
        throw exceptions::NotImplementedError();
    }

    /// @private
    bool is_closed_() const
    {
        throw exceptions::NotImplementedError();
    }
};

}  // namespace shapes
}  // namespace simo