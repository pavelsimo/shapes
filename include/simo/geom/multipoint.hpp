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
 * @brief Point collection
 *
 * @since 0.0.1
 */
class MultiPoint : public BaseGeometry<MultiPoint>, public GeometrySequence<Point>
{
  public:
    /*!
     * @brief creates an empty MultiPoint
     *
     * @since 0.0.1
     */
    MultiPoint() = default;

    /*!
      * @brief creates a MultiPoint from a given initializer list
      * @tparam T an arithmetic value (e.g. int, float, double)
      * @param init the initializer list
      *
      * @since 0.0.1
      */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    MultiPoint(std::initializer_list<std::initializer_list<T>> init)
    {
        seq.reserve(init.size());
        for (const auto& coords : init)
        {
            Point p(coords);
            bounds.extend(p.x, p.y);
            seq.emplace_back(p);
        }
    }

    /*!
     * @brief creates a MultiPoint from a given point vector
     * @param points the point list
     *
     * @since 0.0.1
     */
    explicit MultiPoint(const std::vector<Point>& points)
    {
        seq = points;
        for (const auto& p : seq)
        {
            bounds.extend(p.x, p.y);
        }
    }

    /*!
     * @brief creates a MultiPoint from a geojson string
     * @param json the geojson string
     * @return a MultiPoint object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static MultiPoint from_json(const std::string& json)
    {
        /// @todo (pavel) read properties to specify z, m and zm
        nlohmann::json j = nlohmann::json::parse(json);
        std::string type = j.at("type").get<std::string>();
        if (type != "MultiPoint")
        {
            throw exceptions::ParseError("invalid geometry type");
        }

        auto coords = j.at("coordinates").get<std::vector<std::vector<double>>>();
        std::vector<Point> res;
        for (const auto& tuple : coords)
        {
            if (tuple.size() == 2)
            {
                res.emplace_back(Point{tuple[0], tuple[1]});
            }
            else if (tuple.size() == 3)
            {
                res.emplace_back(Point{tuple[0], tuple[1], tuple[2]});
            }
            else
            {
                throw exceptions::ParseError("invalid dimensions");
            }
        }
        return MultiPoint(res);
    }

    /*!
     * @brief dumps the geojson representation of the MultiPoint
     * @return a geojson string
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    std::string json()
    {
        /// @todo (pavel) add properties to specify z, m and zm
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);
        ss << "{\"type\":\"MultiPoint\",\"coordinates\":[";
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
     * @brief creates a MultiPoint from a WKT string
     * @param wkt the WKT string
     * @return a MultiPoint object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @throw ParseError if a parser error occurs
     *
     * @since 0.0.1
     */
    static MultiPoint from_wkt(const std::string& wkt)
    {
        WktReader reader{};
        auto result      = reader.read(wkt.c_str());
        const auto& data = result.data;
        auto geom_type   = data.geom_type;
        if (geom_type != GeometryDetailedType::MULTIPOINT and
            geom_type != GeometryDetailedType::MULTIPOINTZ and
            geom_type != GeometryDetailedType::MULTIPOINTM and
            geom_type != GeometryDetailedType::MULTIPOINTZM)
        {
            throw exceptions::ParseError("invalid WKT string");
        }

        std::vector<Point> points;
        points.reserve(data.coords.size());
        auto dim = get_dim(data.geom_type);
        int ndim = get_ndim(dim);
        Point p;
        p.dim = dim;
        for (size_t i = 0; i < result.data.coords.size(); i += ndim)
        {
            for (size_t j = 0; j < size_t(ndim); ++j)
            {
                p[j] = result.data.coords[i + j];
            }
            points.push_back(p);
        }
        MultiPoint res(points);
        res.dim = dim;
        return res;
    }

    /*!
     * @brief creates a MultiPoint from a WKT string
     * @param wkt the WKT string
     * @return a MultiPoint object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    std::string wkt()
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision);

        ss << "MULTIPOINT";
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
            ss << "(" << p.x << " " << p.y;
            if (has_z())
            {
                ss << " " << p.z;
            }
            if (has_m())
            {
                ss << " " << p.m;
            }
            ss << ")";
        }
        ss << ")";
        return ss.str();
    }

  private:
    /// for allow BaseGeometry to access MultiPoint private members
    friend class BaseGeometry<MultiPoint>;

    /// @private
    GeometryType type_() const
    {
        return GeometryType::MULTIPOINT;
    }

    /// @private
    std::string type_str_() const
    {
        return "MultiPoint";
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