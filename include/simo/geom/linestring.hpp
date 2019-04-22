#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/detail/sequence.hpp>
#include <simo/geom/utils.hpp>
#include <simo/geom/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a curve where each consecutive pair of points defines a line segment.
 * @ingroup geometry
 *
 * @since 0.0.1
 */
class LineString : public BaseGeometry<LineString>, public detail::GeometrySequence<Point>
{
  public:
    /*!
     * @brief creates an empty LineString
     *
     * @since 0.0.1
     */
    LineString() = default;

    /*!
     * @brief creates a LineString from a given initializer list
     * @tparam T an arithmetic value (e.g. int, float, double)
     * @param init the initializer list
     *
     * @throw GeometryError if geometry contains only one point
     * @throw GeometryError if geometry contains two equal points
     *
     * @since 0.0.1
     */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    LineString(std::initializer_list<std::initializer_list<T>> init)
    {
        detail::create_sequence(init, seq, bounds, dim);
        throw_for_invalid();
    }

    /*!
     * @brief creates a LineString from a given point vector
     * @param points the point list
     *
     * @throw GeometryError if geometry contains only one point
     * @throw GeometryError if geometry contains two equal points
     *
     * @since 0.0.1
     */
    explicit LineString(const std::vector<Point>& points)
    {
        detail::create_sequence(points, seq, bounds, dim);
        throw_for_invalid();
    }

    /*!
     * @brief creates a LineString from a given arithmetic value sequence
     * @tparam T an arithmetic value (e.g. int, float, double)
     * @param coords the arithmetic value sequence
     * @param input_dim the dimension type for the LineString points
     *
     * @throw GeometryError if geometry contains only one point
     * @throw GeometryError if geometry contains two equal points
     *
     * @since 0.0.1
     */
    LineString(const std::vector<double>& coords, DimensionType input_dim)
    {
        detail::create_sequence(coords, input_dim, seq, bounds, dim);
        throw_for_invalid();
    }

    /*!
     * @brief creates a LineString from an iterator range
     * @tparam InputIt the iterator type
     * @param first the first element of the iterator
     * @param last the last element of the iterator
     * @param input_dim the dimension type for the LineString points
     *
     * @throw GeometryError if geometry contains only one point
     * @throw GeometryError if geometry contains two equal points
     *
     * @since 0.0.1
     */
    template <typename InputIt>
    LineString(InputIt first, InputIt last, DimensionType input_dim)
    {
        auto ndim = static_cast<size_t>(utils::get_ndim(input_dim));
        seq.reserve((last - first) / ndim);
        dim = input_dim;
        Point p;
        p.dim = input_dim;
        for (auto it = first; it != last; it += ndim)
        {
            auto coord = it;
            for (size_t k = 0; k < ndim; ++k)
            {
                p[k] = *coord;
            }
            bounds.extend(p.x, p.y);
            seq.push_back(p);
        }
        throw_for_invalid();
    }


    /*!
     * @brief creates a LineString from a geojson string
     * @param json the geojson string
     * @return a LineString object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static LineString from_json(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "LineString")
            {
                throw exceptions::ParseError("invalid geometry type: " + std::string(geom_type));
            }
            const auto& coords = j.at("coordinates").get<std::vector<std::vector<double>>>();
            std::vector<Point> res;
            res.reserve(coords.size());
            std::for_each(std::begin(coords), std::end(coords), [&](const std::vector<double>& coord) {
                res.emplace_back(coord);
            });
            return LineString(res);
        }
        catch (const nlohmann::json::exception& e)
        {
            throw exceptions::ParseError("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::GeometryError&)
        {
            throw exceptions::ParseError("invalid geometry");
        }
    }

    /*!
     * @brief dumps the geojson representation of the LineString
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "{\"type\":\"LineString\",\"coordinates\":[";
        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (i > 0)
            {
                ss << ",";
            }
            const auto& p = seq[i];
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
        ss << "]}";
        return ss.str();
    }

    /*!
     * @brief creates a LineString from a WKT string
     * @param wkt the WKT string
     * @return a LineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static LineString from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_linestring(data.geom_type))
        {
            throw exceptions::ParseError("invalid WKT string");
        }
        auto dim = utils::get_dim(data.geom_type);
        return LineString(result.data.coords, dim);
    }

    /*!
     * @brief creates a LineString from a WKT string
     * @param wkt the WKT string
     * @return a LineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "LINESTRING";
        if (has_z())
        {
            ss << "Z";
        }
        if (has_m())
        {
            ss << "M";
        }

        ss << "(";
        for (size_t i = 0; i < seq.size(); ++i)
        {
            const Point& p = seq[i];
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
        }
        ss << ")";
        return ss.str();
    }

    /*!
     * @brief returns true if all Point's are equal, otherwise false
     * @param other the LineString to compare
     * @return true if all Point's are equal, otherwise false
     *
     * @since 0.0.1
     */
    bool operator==(const LineString& other) const
    {
        return detail::is_equal_sequence(*this, other);
    }

    /*!
     * @brief returns true if at least one Point is different, otherwise false
     * @param other the LineString to compare
     * @return true if at least one Point is different, otherwise false
     *
     * @since 0.0.1
     */
    bool operator!=(const LineString& other) const
    {
        return not(*this == other);
    }

  private:
    /// for allow BaseGeometry to access LineString private members
    friend class BaseGeometry<LineString>;

    /// @private
    void throw_for_invalid()
    {
        if (empty())
        {
            return;
        }

        if (seq.size() < 2)
        {
            throw exceptions::GeometryError("LineString should be either empty or with 2 or more points");
        }

        if (seq.size() == 2)
        {
            if (seq[0] == seq[1])
            {
                throw exceptions::GeometryError("LineString with exactly two equal points");
            }
        }
    }

    /// @private
    GeometryType geom_type_() const
    {
        return GeometryType::LINESTRING;
    }

    /// @private
    std::string geom_type_str_() const
    {
        return "LineString";
    }

    /// @private
    std::vector<std::tuple<double, double>> xy_() const
    {
        std::vector<std::tuple<double, double>> res;
        for (const auto& point : seq)
        {
            res.emplace_back(point.x, point.y);
        }
        return res;
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xyz_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : seq)
        {
            res.emplace_back(point.x, point.y, point.z);
        }
        return res;
    }

    /// @private
    std::vector<std::tuple<double, double, double>> xym_() const
    {
        std::vector<std::tuple<double, double, double>> res;
        for (const auto& point : seq)
        {
            res.emplace_back(point.x, point.y, point.m);
        }
        return res;
    }

    /// @private
    std::vector<std::tuple<double, double, double, double>> xyzm_() const
    {
        std::vector<std::tuple<double, double, double, double>> res;
        for (const auto& point : seq)
        {
            res.emplace_back(point.x, point.y, point.z, point.m);
        }
        return res;
    }

    /// @private
    bool empty_() const
    {
        return seq.empty();
    }

    /// @private
    size_t size_() const
    {
        return seq.size();
    }

    /// @private
    bool is_closed_() const
    {
        if (seq.size() < 2)
        {
            return false;
        }
        size_t last_index = seq.size() - 1;
        return seq[0] == seq[last_index];
    }
};

}  // namespace shapes
}  // namespace simo