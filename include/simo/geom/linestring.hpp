#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <simo/geom/geometry.hpp>
#include <simo/geom/utils.hpp>
#include <simo/geom/detail/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief A curve where each consecutive pair of points defines a line segment
 * @tparam T
 * @tparam AllocatorType
 * @ingroup geometry
 *
 * @since 0.0.1
 */
template <typename T, typename AllocatorType = std::allocator<T>>
class basic_linestring : public std::vector<T, AllocatorType>, public basic_geometry<basic_linestring<T>>
{
  public:
    /// DOCUMENT ME!
    using base_type = std::vector<T, AllocatorType>;
    /// DOCUMENT ME!
    using point_type = typename T::point_type;
    /// DOCUMENT ME!
    using point_iterator = typename std::vector<T>::iterator;
    /// DOCUMENT ME!
    using point_const_iterator = typename std::vector<T>::const_iterator;
    /// DOCUMENT ME!
    using coord_type = typename T::coord_type;
    /// DOCUMENT ME!
    using coord_iterator = typename std::vector<coord_type>::iterator;
    /// DOCUMENT ME!
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    /*!
     * @brief DOCUMENT ME!
     *
     * @since 0.0.1
     */
    basic_linestring()
        : base_type() {}

    /*!
     * @brief DOCUMENT ME!
     * @param init
     *
     * @since 0.0.1
     */
    basic_linestring(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     *
     * @since 0.0.1
     */
    explicit basic_linestring(coord_const_iterator first, coord_const_iterator last)
    {
        /// @todo deal with repetition
        size_t n = ndim_();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     *
     * @since 0.0.1
     */
    explicit basic_linestring(coord_iterator first, coord_iterator last)
    {
        /// @todo deal with repetition
        size_t n = ndim_();
        this->reserve(std::distance(first, last));
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     *
     * @since 0.0.1
     */
    basic_linestring(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     *
     * @since 0.0.1
     */
    basic_linestring(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    // operators

    /*!
     * @param lhs a linestring
     * @param rhs a linestring
     * @return true if all points are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const basic_linestring<T>& lhs, const basic_linestring<T>& rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    /*!
     * @param lhs a linestring
     * @param rhs a linestring
     * @return true if at least one point is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const basic_linestring<T>& lhs, const basic_linestring<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    std::vector<std::tuple<double, double>> xy() const
    {
        std::vector<std::tuple<double, double>> res;
        res.reserve(this->size());
        for (const auto& p : *this)
        {
            res.emplace_back(p.x, p.y);
        }
        return res;
    }

    // polyline

    /*!
     * @brief DOCUMENT ME!
     * @param polyline
     * @param precision
     * @return
     *
     * @since 0.0.1
     */
    static basic_linestring<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        static_assert(std::is_same<point_type, Point::point_type>::value, "must contain XY points");

        auto coords = polyline::decode(polyline, precision);
        return {coords.begin(), coords.end()};
    }

    /*!
     * @brief DOCUMENT ME!
     * @param precision
     * @return
     *
     * @since 0.0.1
     */
    std::string polyline(std::int32_t precision = 5) const
    {
        static_assert(std::is_same<point_type, Point::point_type>::value, "must contain XY points");

        std::string res;
        res.reserve(this->size() * 6);
        double prev_lng = 0;
        double prev_lat = 0;
        for (const auto& p : *this)
        {
            res += polyline::encode(p.lat - prev_lat, precision);
            res += polyline::encode(p.lng - prev_lng, precision);
            prev_lat = p.lat;
            prev_lng = p.lng;
        }
        return res;
    }

  private:
    friend class basic_geometry<basic_linestring<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (std::is_same<point_type, PointZ::point_type>::value)
        {
            return geometry_type::LINESTRINGZ;
        }
        if (std::is_same<point_type, PointM::point_type>::value)
        {
            return geometry_type::LINESTRINGM;
        }
        if (std::is_same<point_type, PointZM::point_type>::value)
        {
            return geometry_type::LINESTRINGZM;
        }
        return geometry_type::LINESTRING;
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        if (std::is_same<point_type, PointZ::point_type>::value)
        {
            return dimension_type::XYZ;
        }
        if (std::is_same<point_type, PointM::point_type>::value)
        {
            return dimension_type::XYM;
        }
        if (std::is_same<point_type, PointZM::point_type>::value)
        {
            return dimension_type::XYZM;
        }
        return dimension_type::XY;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        if (std::is_same<point_type, PointZ::point_type>::value)
        {
            return 3;
        }
        if (std::is_same<point_type, PointM::point_type>::value)
        {
            return 3;
        }
        if (std::is_same<point_type, PointZM::point_type>::value)
        {
            return 4;
        }
        return 2;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        return *this[0] == *this[this->size() - 1];
    }

    /// @private
    void throw_for_invalid_() const
    {
        if (this->empty())
        {
            return;
        }

        if (this->size() < 2)
        {
            throw exceptions::geometry_error("LineString should be either empty or with 2 or more points");
        }

        if (this->size() == 2)
        {
            if (*this[0] == *this[1])
            {
                throw exceptions::geometry_error("LineString with exactly two equal points");
            }
        }
    }

    /// @private
    detail::bounds bounds_() const
    {
        detail::bounds res{};
        for (const auto& p : *this)
        {
            res.extend(p.x, p.y);
        }
        return res;
    }

    /// @private
    bool has_z_() const noexcept
    {
        return std::is_same<point_type, PointZ::point_type>::value or std::is_same<point_type, PointZM::point_type>::value;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return std::is_same<point_type, PointM::point_type>::value or std::is_same<point_type, PointZM::point_type>::value;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "LineString";
    }

    // json

    /// @private
    static basic_linestring<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "LineString")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& coords = j.at("coordinates").get<std::vector<std::vector<double>>>();
            std::vector<point_type> res;
            res.reserve(coords.size());
            std::for_each(std::begin(coords), std::end(coords), [&](const std::vector<double>& coord) {
                res.emplace_back(coord.begin(), coord.end());
            });
            return basic_linestring<T>(res.begin(), res.end());
        }
        catch (const nlohmann::json::exception& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const exceptions::geometry_error& e)
        {
            throw exceptions::parse_error("invalid geometry: " + std::string(e.what()));
        }
    }

    /// @private
    std::string json_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"LineString\",\"coordinates\":[";
        int i = 0;
        for (const auto& p : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (int j = 0; j < p.ndim(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << p.coords[j];
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_linestring<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_linestring(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_linestring<T>(result.data.coords.begin(), result.data.coords.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "LINESTRING";
        if (has_z_())
        {
            ss << "Z";
        }
        if (has_m_())
        {
            ss << "M";
        }
        ss << "(";
        int i = 0;
        for (const auto& p : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            for (int32_t j = 0; j < p.ndim(); ++j)
            {
                if (j > 0)
                {
                    ss << " ";
                }
                ss << p.coords[j];
            }
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <class T = double>
using linestring = basic_linestring<basic_point<T>>;

template <class T = double>
using linestring_z = basic_linestring<basic_point_z<T>>;

template <class T = double>
using linestring_m = basic_linestring<basic_point_m<T>>;

template <class T = double>
using linestring_zm = basic_linestring<basic_point_zm<T>>;

using LineString   = linestring<double>;
using LineStringZ  = linestring_z<double>;
using LineStringM  = linestring_m<double>;
using LineStringZM = linestring_zm<double>;

}  // namespace shapes
}  // namespace simo