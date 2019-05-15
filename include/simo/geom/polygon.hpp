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
     * @brief Creates a Polygon
     *
     * @param rings a LinearRing sequence with the shell and holes of the polygon
     *
     * @since 0.0.1
     */
    explicit Polygon(const std::vector<LinearRing>& rings)
    {
        /// @todo (pavel) deal with duplication
        if (not rings.empty())
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
     * @brief Creates a Polygon
     *
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
            std::vector<LinearRing> res;
            res.reserve(linearrings.size());
            std::vector<Point> points;
            for (const auto& linearring : linearrings)
            {
                if (not linearring.empty())
                {
                    const auto& coords = linearring.get<std::vector<std::vector<double>>>();
                    points.reserve(coords.size());
                    std::for_each(std::begin(coords), std::end(coords), [&points](const std::vector<double>& coord) {
                        points.emplace_back(coord);
                    });
                    res.emplace_back(points);
                }
                points.clear();
            }
            return Polygon(res);
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
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "{\"type\":\"Polygon\",\"coordinates\":[";

        auto print_ring = [&ss](const LinearRing& ring) {
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
        print_ring(exterior);
        ss << "]";
        for (const auto& interior : interiors)
        {
            ss << ",";
            ss << "[";
            print_ring(interior);
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
        auto result      = reader.read(wkt.c_str());
        const auto& data = result.data;
        if (not utils::is_polygon(data.geom_type))
        {
            throw exceptions::ParseError("invalid wkt string");
        }
        return Polygon();
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
    std::string wkt()
    {
        throw exceptions::NotImplementedError();
    }

    /// @todo (pavel) add from_bounds method

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
    std::vector<std::vector<double>> coords_() const
    {
        throw exceptions::NotImplementedError();
    }
};

}  // namespace shapes
}  // namespace simo