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
 * @brief a curve where each consecutive pair of points defines a line segment.
 *
 * @since 0.0.1
 */
class LineString : public BaseGeometry<LineString>, public GeometrySequence<Point>
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
     * @throw GeometryError DOCUMENT ME!
     *
     * @since 0.0.1
     */
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    LineString(std::initializer_list<std::initializer_list<T>> init)
    {
        seq.reserve(init.size());
        for (const auto& coords : init)
        {
            Point p(coords);
            bounds.extend(p.x, p.y);
            seq.emplace_back(p);
        }
        throw_for_invalid();
    }

    /*!
     * @brief creates a LineString from a given point vector
     * @param points the point list
     *
     * @throw GeometryError DOCUMENT ME!
     *
     * @since 0.0.1
     */
    explicit LineString(const std::vector<Point>& points)
    {
        seq = points;
        for (const auto& p : seq)
        {
            bounds.extend(p.x, p.y);
        }
    }

    /*!
     * @brief creates a LineString from a geojson string
     * @param json the geojson string
     * @return a LineString object
     * @sa https://tools.ietf.org/html/rfc7946
     *
     * @since 0.0.1
     */
    static LineString from_json(const std::string& /*json*/)
    {
        throw exceptions::NotImplementedError();
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
        throw exceptions::NotImplementedError();
    }

    /*!
     * @brief creates a LineString from a WKT string
     * @param wkt the WKT string
     * @return a LineString object
     * @sa https://en.wikipedia.org/wiki/Well-known_text_representation_of_geometry
     *
     * @since 0.0.1
     */
    static LineString from_wkt(const std::string& /*wkt*/)
    {
        throw exceptions::NotImplementedError();
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
        throw exceptions::NotImplementedError();
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
    GeometryType type_() const
    {
        return GeometryType::LINESTRING;
    }

    /// @private
    std::string type_str_() const
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