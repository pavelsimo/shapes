#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/sequence.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a LineString collection
 * @ingroup geometry
 *
 * @since 0.0.1
 */
class MultiLineString : public BaseGeometry<MultiLineString>, public detail::GeometrySequence<LineString>
{
  public:
    /*!
     * @brief creates an empty MultiLineString
     *
     * @since 0.0.1
     */
    MultiLineString() = default;

    /*!
     * @brief DOCUMENT ME!
     * @param init
     *
     * @since 0.0.1
     */
    MultiLineString(std::initializer_list<LineString> init)
    {
        if (init.size() > 0)
        {
            const auto& head = *init.begin();
            dim = head.dim;
            seq.reserve(init.size());
            for(auto it = init.begin(); it != init.end(); ++it)
            {
                const auto& l = *it;
                if (l.dim != dim)
                {
                    throw exceptions::GeometryError("dimension mismatch in start point and point at index " + std::to_string(it - init.begin()));
                }
                bounds.extend(l.bounds.minx, l.bounds.miny);
                bounds.extend(l.bounds.maxx, l.bounds.maxy);
            }
        }
    }

    /*!
     *
     * @param linestrings
     */
    explicit MultiLineString(const std::vector<LineString>& linestrings)
    {
        if (not linestrings.empty())
        {
            seq = linestrings;
            dim = linestrings[0].dim;
            std::for_each(std::begin(linestrings), std::end(linestrings), [&](const LineString& l) {
                bounds.extend(l.bounds.minx, l.bounds.miny);
                bounds.extend(l.bounds.maxx, l.bounds.maxy);
            });
        }
    }

    /*!
     * @brief creates a MultiLineString from a geojson string
     * @param json the geojson string
     * @return a MultiLineString object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static MultiLineString from_json(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "MultiLineString")
            {
                throw exceptions::ParseError("invalid geometry type: " + std::string(geom_type));
            }
            const auto& linestrings = j.at("coordinates");
            std::vector<LineString> res;
            res.reserve(linestrings.size());
            for (const auto& linestring: linestrings)
            {
                if (not linestring.empty())
                {
                    res.emplace_back(linestring, utils::get_dim(static_cast<int8_t>(linestring.size())));
                }

            }
            return MultiLineString(res);
        }
        catch (const nlohmann::json::exception& e)
        {
            throw exceptions::ParseError("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::GeometryError& e)
        {
            throw exceptions::ParseError("invalid geometry: " + std::string(e.what()));
        }
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
    static MultiLineString from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multilinestring(data.geom_type))
        {
            throw exceptions::ParseError("invalid WKT string");
        }
        return MultiLineString();
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
    GeometryType geom_type_() const
    {
        return GeometryType::MULTILINESTRING;
    }

    /// @private
    std::string geom_type_str_() const
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