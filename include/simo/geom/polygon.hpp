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
 * @brief DOCUMENT ME!
 * @tparam T
 * @tparam AllocatorType
 *
 * @since 0.0.1
 */
template <typename T, typename AllocatorType = std::allocator<T>>
class basic_polygon : public std::vector<T, AllocatorType>, public basic_geometry<basic_polygon<T>>
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
     */
    basic_polygon()
        : base_type() {}

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     */
    basic_polygon(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    /*!
     * @brief DOCUMENT ME!
     * @param first
     * @param last
     */
    basic_polygon(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    /*!
     * DOCUMENT ME!
     * @param init
     */
    basic_polygon(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    /*!
     * @brief DOCUMENT ME!
     * @tparam CoordIterator
     * @tparam OffsetIterator
     * @param coord_first
     * @param coord_last
     * @param offset_first
     * @param offset_last
     */
    template <typename CoordIterator, typename OffsetIterator>
    basic_polygon(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto n = ndim_();
            this->reserve((coord_last - coord_first) / n);
            size_t lo = 0;
            for (auto it = offset_first; it != offset_last; ++it)
            {
                size_t hi = *it;
                this->emplace_back(coord_first + lo, coord_first + hi);
                lo = hi;
            }
        }
    }

    // operators

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator==(const basic_polygon<T>& lhs, const basic_polygon<T>& rhs)
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
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator!=(const basic_polygon<T>& lhs, const basic_polygon<T>& rhs)
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

    /*!
     * @brief DOCUMENT ME!
     * @return
     *
     * @since 0.0.1
     */
    T& exterior()
    {
        return *this->begin();
    }

    /*!
     * @brief DOCUMENT ME!
     * @param pos
     * @return
     *
     * @since 0.0.1
     */
    T& interiors(size_t pos)
    {
        assert(this->begin() + pos + 1 < this->end());
        return *(this->begin() + pos + 1);
    }

  private:
    /// for allow basic_geometry to access basic_polygon private members
    friend class basic_geometry<basic_polygon<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (std::is_same<point_type, PointZ::point_type>::value)
        {
            return geometry_type::POLYGONZ;
        }
        if (std::is_same<point_type, PointM::point_type>::value)
        {
            return geometry_type::POLYGONM;
        }
        if (std::is_same<point_type, PointZM::point_type>::value)
        {
            return geometry_type::POLYGONZM;
        }
        return geometry_type::POLYGON;
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
        /// @todo (pavel) add checks
    }

    /// @private
    bounds bounds_() const
    {
        bounds res{};
        for (const auto& r : *this)
        {
            auto r_bound = r.bounds();
            res.extend(r_bound);
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
        return "Polygon";
    }

    // json

    /// @private
    static basic_polygon<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Polygon")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& rings = j.at("coordinates");
            std::vector<T> res;
            res.reserve(rings.size());
            std::vector<point_type> points;
            for (const auto& ring : rings)
            {
                if (not ring.empty())
                {
                    const auto& coords = ring.get<std::vector<std::vector<double>>>();
                    points.reserve(coords.size());
                    std::for_each(std::begin(coords), std::end(coords), [&points](const std::vector<double>& coord) {
                        points.emplace_back(coord.begin(), coord.end());
                    });
                    res.emplace_back(points.begin(), points.end());
                }
                points.clear();
            }
            return basic_polygon<T>(res.begin(), res.end());
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
        ss << "{\"type\":\"Polygon\",\"coordinates\":[";
        int i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                ss << "[";
                const auto& p = ls[j];
                for (int k = 0; k < p.ndim(); ++k)
                {
                    if (k > 0)
                    {
                        ss << ",";
                    }
                    ss << p.coords[k];
                }
                ss << "]";
                ++i;
            }
            ss << "]";
            ++i;
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_polygon<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_polygon(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_polygon<T>(result.data.coords.begin(), result.data.coords.end(), result.data.offsets.begin(), result.data.offsets.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POLYGON";
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
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << "(";
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    ss << ",";
                }
                const auto& p = ls[j];
                for (int32_t k = 0; k < p.ndim(); ++k)
                {
                    if (k > 0)
                    {
                        ss << " ";
                    }
                    ss << p.coords[k];
                }
            }
            ss << ")";
            ++i;
        }
        ss << ")";
        return ss.str();
    }
};

template <class T = double>
using polygon = basic_polygon<linearring<T>>;

template <class T = double>
using polygon_z = basic_polygon<linearring_z<T>>;

template <class T = double>
using polygon_m = basic_polygon<linearring_m<T>>;

template <class T = double>
using polygon_zm = basic_polygon<linearring_zm<T>>;

using Polygon   = polygon<double>;
using PolygonZ  = polygon_z<double>;
using PolygonM  = polygon_m<double>;
using PolygonZM = polygon_zm<double>;

}  // namespace shapes
}  // namespace simo