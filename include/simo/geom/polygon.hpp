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
 * @brief Represents a polygon
 * @ingroup geometry
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
     * @brief Creates an empty Polygon
     *
     * @since 0.0.1
     */
    Polygon() = default;

    /*!
     * @brief Creates a Polygon
     *
     * @param rings a LinearRing sequence with the shell and holes of the polygon
     *
     * @since 0.0.1
     */
    Polygon(std::initializer_list<LinearRing> rings)
    {
        if (rings.size() > 0)
        {
            auto ring     = rings.begin();
            Bounds& b     = bounds;
            exterior      = LinearRing(*ring);
            dim           = exterior.dim;
            Bounds& b_ext = exterior.bounds;
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);
            ring++;
            for (; ring != rings.end(); ++ring)
            {
                /// @todo (pavel) check dim
                interiors.emplace_back(*ring);
                Bounds& b_int = interiors[interiors.size() - 1].bounds;
                b.extend(b_int.minx, b_int.miny);
                b.extend(b_int.maxx, b_int.maxy);
            }
        }
    }

    /*!
     * @brief Creates a Polygon
     *
     * @param rings a LinearRing sequence with the shell and holes of the polygon
     *
     * @since 0.0.1
     */
    explicit Polygon(const std::vector<LinearRing>& rings)
    {
        /// @todo (pavel) eliminate duplication
        if (not rings.empty())
        {
            Bounds& b     = bounds;
            exterior      = rings[0];
            dim           = exterior.dim;
            Bounds& b_ext = exterior.bounds;
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);
            interiors.reserve(rings.size() - 1);
            for (std::size_t i = 1; i < rings.size(); ++i)
            {
                interiors.push_back(rings[i]);
                Bounds& b_int = interiors[interiors.size() - 1].bounds;
                b.extend(b_int.minx, b_int.miny);
                b.extend(b_int.maxx, b_int.maxy);
            }
        }
    }

    /*!
     * @brief Creates a Polygon
     *
     * @param shell the shell of the polygon as a Point sequence
     *
     * @since 0.0.1
     */
    explicit Polygon(const std::vector<Point>& shell)
        : exterior(shell)
    {
        if (not exterior.empty())
        {
            dim = exterior[0].dim;
            /// @todo (pavel) check dim
            Bounds& b     = bounds;
            Bounds& b_ext = exterior.bounds;
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);
        }
    }

    /*!
     * @brief Creates a Polygon
     *
     * @param shell the shell of the polygon as a Point sequence
     *
     * @since 0.0.1
     */
    explicit Polygon(const LinearRing& shell)
        : exterior(shell)
    {
        if (not exterior.empty())
        {
            dim = exterior[0].dim;
            /// @todo (pavel) check dim
            Bounds& b     = bounds;
            Bounds& b_ext = exterior.bounds;
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);
        }
    }

    /*!
     * @brief Creates a Polygon
     *
     * @param shell the shell of the polygon as a Point sequence
     * @param holes one or more collection of points, each representing a hole in the polygon
     *
     * @since 0.0.1
     */
    explicit Polygon(const std::vector<Point>& shell, const std::vector<std::vector<Point>>& holes)
        : exterior(shell)
    {
        if (not exterior.empty())
        {
            dim = exterior[0].dim;
            /// @todo (pavel) check dim
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
    }

    /*!
     * @brief Creates a MultiLineString from two pair of iterators
     *
     * @tparam CoordInputIt the coordinate input iterator
     * @tparam OffsetInputIt the offset input iterator
     * @param coord_first the first coordinate iterator
     * @param coord_last the second coordinate iterator
     * @param offset_first the offset first iterator
     * @param offset_last the offset last iterator
     * @param input_dim the dimension type
     *
     * @since 0.0.1
     */
    template <typename CoordInputIt, typename OffsetInputIt>
    Polygon(CoordInputIt coord_first, CoordInputIt coord_last, OffsetInputIt offset_first, OffsetInputIt offset_last, DimensionType input_dim)
    {
        dim = input_dim;
        if (std::distance(coord_first, coord_last) > 0 and std::distance(offset_first, offset_last) > 0)
        {
            auto ndim = static_cast<size_t>(utils::get_ndim(input_dim));

            /// set polygon exterior
            size_t lo = 0;
            size_t hi = *offset_first;
            exterior  = LinearRing(coord_first + lo, coord_first + hi, input_dim);
            lo        = hi;
            offset_first++;

            Bounds& b     = bounds;
            Bounds& b_ext = exterior.bounds;
            b.extend(b_ext.minx, b_ext.miny);
            b.extend(b_ext.maxx, b_ext.maxy);

            /// set polygon interiors
            interiors.reserve((coord_last - coord_first) / ndim);
            for (auto it = offset_first; it != offset_last; ++it)
            {
                hi = *it;
                interiors.emplace_back(coord_first + lo, coord_first + hi, input_dim);
                lo            = hi;
                const auto& l = interiors[interiors.size() - 1];
                bounds.extend(l.bounds.minx, l.bounds.miny);
                bounds.extend(l.bounds.maxx, l.bounds.maxy);
            }
        }
    }

    /*!
     * @brief Creates a Polygon from a geojson string
     *
     * @param json the geojson string
     * @return a Polygon object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static Polygon from_json(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Polygon")
            {
                throw exceptions::ParseError("invalid geometry type: " + std::string(geom_type));
            }
            const auto& linearrings = j.at("coordinates");
            std::vector<LinearRing> rings;
            rings.reserve(linearrings.size());
            std::vector<Point> points;
            std::vector<std::size_t> offsets;
            for (const auto& linearring : linearrings)
            {
                if (not linearring.empty())
                {
                    const auto& coords = linearring.get<std::vector<std::vector<double>>>();
                    points.reserve(coords.size());
                    std::for_each(std::begin(coords), std::end(coords), [&points](const std::vector<double>& coord) {
                        points.emplace_back(coord);
                    });
                    rings.emplace_back(points);
                    points.clear();
                }
            }
            return Polygon(rings);
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
     * @brief Dumps the geojson representation of the Polygon
     *
     * @param precision the output precision
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json(std::int32_t precision = -1)
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"Polygon\",\"coordinates\":[";
        auto add_ring = [&ss](const LinearRing& ring) {
            for (size_t j = 0; j < ring.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                const auto& p = ring.at(j);
                switch (p.dim)
                {
                    case DimensionType::XY:
                    {
                        ss << "[" << p.x << "," << p.y << "]";
                        break;
                    }
                    case DimensionType::XYZ:
                    {
                        ss << "[" << p.x << "," << p.y << "," << p.z << "]";
                        break;
                    }
                    case DimensionType::XYM:
                    {
                        ss << "[" << p.x << "," << p.y << "," << p.m << "]";
                        break;
                    }
                    case DimensionType::XYZM:
                    {
                        ss << "[" << p.x << "," << p.y << "," << p.z << "," << p.m << "]";
                        break;
                    }
                }
            }
        };
        ss << "[";
        add_ring(exterior);
        ss << "]";
        for (const auto& interior : interiors)
        {
            ss << ",";
            ss << "[";
            add_ring(interior);
            ss << "]";
        }
        ss << "]}";
        return ss.str();
    }

    /*!
     * @brief Creates a Polygon from a WKT string
     *
     * @param wkt the WKT string
     * @return a Polygon object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static Polygon from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_polygon(data.geom_type))
        {
            throw exceptions::ParseError("invalid wkt string");
        }
        return {data.coords.begin(), data.coords.end(), data.offsets.begin(), data.offsets.end(), utils::get_dim(data.geom_type)};
    }

    /*!
     * @brief Dumps the WKT representation of the Polygon
     *
     * @param precision the output precision
     * @return a WKT string
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt(std::int32_t precision = -1)
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POLYGON";
        if (has_z())
        {
            ss << "Z";
        }
        if (has_m())
        {
            ss << "M";
        }
        auto add_ring = [this, &ss](const LinearRing& ring) {
            ss << "(";
            int i = 0;
            for (const auto& p : ring)
            {
                if (i > 0)
                {
                    ss << ",";
                }
                ss << p.x << " " << p.y;
                if (has_z())
                {
                    ss << " " << p.z;
                }
                if (has_m())
                {
                    ss << " " << p.m;
                }
                ++i;
            }
            ss << ")";
        };
        ss << "(";
        add_ring(exterior);
        for (const auto& ring : interiors)
        {
            ss << ",";
            add_ring(ring);
        }
        ss << ")";
        return ss.str();
    }

    /*!
     * @brief Creates a Polygon from a polyline string
     *
     * @param polyline the polyline string
     * @param text the encoded polyline string
     * @return a LineString object
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static Polygon from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        auto coords = polyline::decode(polyline, precision);
        auto ring   = LinearRing{coords, DimensionType::XY};
        return Polygon(ring);
    }

    /*!
     * @brief Creates a Polygon from a collection of polyline strings
     *
     * @param polylines a collection of polyline strings
     * @param text the encoded polyline string
     * @return a Polygon object
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static Polygon from_polyline(const std::vector<std::string>& polylines, std::int32_t precision = 5)
    {
        std::vector<LineString> res;
        res.reserve(polylines.size());
        for (const auto& polyline : polylines)
        {
            res.emplace_back(polyline::decode(polyline, precision), DimensionType::XY);
        }
        return Polygon(res);
    }

    /*!
     * @brief Dumps the polyline representation of the Polygon
     *
     * @param precision the encoded precision
     * @return a polyline string
     * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
     *
     * @since 0.0.1
     */
    std::vector<std::string> polyline(std::int32_t precision = 5)
    {
        std::vector<std::string> res;
        res.reserve(size());
        res.push_back(exterior.polyline());
        std::for_each(interiors.begin(), interiors.end(), [&res, &precision](const LinearRing& ring) {
            res.push_back(ring.polyline(precision));
        });
        return res;
    }

    /*!
     * @param lhs a Polygon
     * @param rhs a Polygon
     * @return true if all LinearRing's are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const Polygon& lhs, const Polygon& rhs);

    /*!
     * @param lhs a Polygon
     * @param rhs a Polygon
     * @return true if at least one LinearRing is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const Polygon& lhs, const Polygon& rhs);

    /*!
    * @param pos the element position
    * @return returns a reference to the element at position n in T
    *
    * @since 0.0.1
    */
    LinearRing& operator[](size_t pos)
    {
        try
        {
            return (pos == 0) ? exterior : interiors[pos - 1];
        }
        catch (std::out_of_range&)
        {
            throw exceptions::IndexError("index at " + std::to_string(pos) + " is out of range");
        }
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in the LinearRing
     *
     * @throw IndexError if the index at pos is out of range
     *
     * @since 0.0.1
     */
    const LinearRing& at(size_t pos) const
    {
        try
        {
            return (pos == 0) ? exterior : interiors.at(pos - 1);
        }
        catch (std::out_of_range&)
        {
            throw exceptions::IndexError("index at " + std::to_string(pos) + " is out of range");
        }
    }

    /*!
     * @param pos the element position
     * @return returns a reference to the element at position n in the LinearRing
     *
     * @throw IndexError if the index at pos is out of range
     *
     * @since 0.0.1
     */
    LinearRing& at(size_t pos)
    {
        try
        {
            return (pos == 0) ? exterior : interiors.at(pos - 1);
        }
        catch (std::out_of_range&)
        {
            throw exceptions::IndexError("index at " + std::to_string(pos) + " is out of range");
        }
    }

  private:
    /// for allow BaseGeometry to access Polygon private members
    friend class BaseGeometry<Polygon>;

    /// @private
    GeometryType geom_type_() const
    {
        return GeometryType::POLYGON;
    }

    /// @private
    std::string geom_type_str_() const
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
        if (exterior.empty())
        {
            return 0;
        }
        if (interiors.empty())
        {
            return 1;
        }
        return interiors.size() + 1;
    }

    /// @private
    bool is_closed_() const
    {
        return true;
    }

    /// @private
    std::vector<std::vector<double>> coords_() const
    {
        std::vector<std::vector<double>> res;
        res.reserve(size());
        auto ext_coords = exterior.coords();
        res.insert(res.end(), ext_coords.begin(), ext_coords.end());
        std::for_each(interiors.begin(), interiors.end(), [&res](const LinearRing& interior) {
            auto int_coords = interior.coords();
            res.insert(res.end(), int_coords.begin(), int_coords.end());
        });
        return res;
    }
};

bool operator==(const Polygon& lhs, const Polygon& rhs)
{
    if (lhs.exterior.size() != rhs.exterior.size())
    {
        return false;
    }

    if (lhs.interiors.size() != rhs.interiors.size())
    {
        return false;
    }

    for (size_t i = 0; i < lhs.exterior.size(); ++i)
    {
        if (lhs.exterior.at(i) != rhs.exterior.at(i))
        {
            return false;
        }
    }

    for (size_t i = 0; i < lhs.interiors.size(); ++i)
    {
        if (lhs.interiors[i] != rhs.interiors[i])
        {
            return false;
        }
        for (size_t j = 0; j < lhs.interiors[i].size(); ++j)
        {
            if (lhs.interiors[i].at(j) != rhs.interiors[i].at(j))
            {
                return false;
            }
        }
    }

    return true;
}

bool operator!=(const Polygon& lhs, const Polygon& rhs)
{
    return not operator==(lhs, rhs);
}

}  // namespace shapes
}  // namespace simo