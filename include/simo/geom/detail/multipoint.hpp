#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iomanip>
#include <simo/geom/detail/geometry.hpp>
#include <simo/geom/detail/bounds.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief DOCUMENT ME!
 * @tparam T
 * @tparam AllocatorType
 *
 * @since 0.0.1
 */
template <typename T, typename AllocatorType = std::allocator<T>>
class basic_multipoint : public std::vector<T, AllocatorType>, public basic_geometry<basic_multipoint<T>>
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
    inline basic_multipoint()
        : base_type() {}

    /*!
     * @brief DOCUMENT ME!
     * @param init
     *
     * @since 0.0.1
     */
    basic_multipoint(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     *
     * @since 0.0.1
     */
    explicit basic_multipoint(coord_const_iterator first, coord_const_iterator last)
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
     *
     * @since 0.0.1
     */
    explicit basic_multipoint(coord_iterator first, coord_iterator last)
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
    basic_multipoint(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     */
    basic_multipoint(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    // operators

    /*!
     * @param lhs a mulipoint
     * @param rhs a mulipoint
     * @return true if all Point's are equal, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator==(const basic_multipoint<T>& lhs, const basic_multipoint<T>& rhs)
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
     * @param lhs a mulipoint
     * @param rhs a mulipoint
     * @return true if at least one Point is different, otherwise false
     *
     * @since 0.0.1
     */
    friend bool operator!=(const basic_multipoint<T>& lhs, const basic_multipoint<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     *
     * @since 0.0.1
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
    static basic_multipoint<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        static_assert(is_basic_point<T>::value, "must contain XY points");

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
        static_assert(is_basic_point<T>::value, "must contain XY points");

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
    /// for allow basic_geometry to access basic_multipoint private members
    friend class basic_geometry<basic_multipoint<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_point_z<T>::value)
        {
            return geometry_type::MULTIPOINTZ;
        }
        if (is_basic_point_m<T>::value)
        {
            return geometry_type::MULTIPOINTM;
        }
        if (is_basic_point_zm<T>::value)
        {
            return geometry_type::MULTIPOINTZM;
        }
        return geometry_type::MULTIPOINT;
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        if (is_basic_point_z<T>::value)
        {
            return dimension_type::XYZ;
        }
        if (is_basic_point_m<T>::value)
        {
            return dimension_type::XYM;
        }
        if (is_basic_point_zm<T>::value)
        {
            return dimension_type::XYZM;
        }
        return dimension_type::XY;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        if (is_basic_point_z<T>::value)
        {
            return 3;
        }
        if (is_basic_point_m<T>::value)
        {
            return 3;
        }
        if (is_basic_point_zm<T>::value)
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
        // do nothing
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& p : *this)
        {
            res.extend(p.x, p.y);
        }
        return res;
    }

    /// @private
    bool has_z_() const noexcept
    {
        return is_basic_point_z<T>::value or is_basic_point_zm<T>::value;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return is_basic_point_m<T>::value or is_basic_point_zm<T>::value;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "MultiPoint";
    }

    // json

    /// @private
    static basic_multipoint<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "MultiPoint")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& coords = j.at("coordinates").get<std::vector<std::vector<double>>>();
            std::vector<point_type> res;
            res.reserve(coords.size());
            std::for_each(std::begin(coords), std::end(coords), [&](const std::vector<double>& coord) {
                res.emplace_back(coord.begin(), coord.end());
            });
            return basic_multipoint<T>(res.begin(), res.end());
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
        ss << "{\"type\":\"MultiPoint\",\"coordinates\":[";
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
    static basic_multipoint<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multipoint(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_multipoint<T>(result.data.coords.begin(), result.data.coords.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTIPOINT";
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
            ss << "(";
            for (int32_t j = 0; j < p.ndim(); ++j)
            {
                if (j > 0)
                {
                    ss << " ";
                }
                ss << p.coords[j];
            }
            ss << ")";
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

}  // namespace shapes
}  // namespace simo