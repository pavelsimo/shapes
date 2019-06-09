#pragma once

#include <ciso646>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <regex>
#include <json/json.hpp>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>
#include <simo/io/wkt_reader.hpp>
#include <simo/io/polyline.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief DOCUMENT ME!
 * @tparam T
 * @ingroup geometry
 *
 * @since 0.0.1
 */
template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point : public basic_geometry<basic_point<T>>
{
  public:
    /// DOCUMENT ME!
    using point_type = basic_point;
    /// DOCUMENT ME!
    using coord_type = T;
    /// DOCUMENT ME!
    using coord_iterator = typename std::vector<coord_type>::iterator;
    /// DOCUMENT ME!
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    union
    {
        struct
        {
            T x;
            T y;
        };

        struct
        {
            T lng;
            T lat;
        };

        T coords[2];
    };

    /*!
     * @brief Creates a empty point
     */
    basic_point()
        : x(0), y(0) {}

    /*!
     * @brief Creates a point from the given coordinates
     * @param x the x-coordinate
     * @param y the y-coordinate
     */
    basic_point(T x, T y)
        : x(x), y(y) {}

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point(coord_iterator begin, coord_iterator end)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == 2);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point(coord_const_iterator begin, coord_const_iterator end)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == 2);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    std::size_t size() const noexcept
    {
        return static_cast<std::size_t>(ndim_());
    }

    // operators

    /*!
     * @brief DOCUMENT ME!
     * @param pos
     * @return
     */
    T& operator[](size_t pos)
    {
        assert(pos < 2);
        return coords[pos];
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator==(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y;
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator!=(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    // polyline

    /*!
     * @brief DOCUMENT ME!
     * @param polyline
     * @param precision
     * @return
     */
    static basic_point<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        auto coords = polyline::decode(polyline, precision);
        if (coords.size() > 2)
        {
            throw exceptions::parse_error("too many points");
        }
        return {coords[0], coords[1]};
    }

    /*!
     * @brief DOCUMENT ME!
     * @param precision
     * @return
     */
    std::string polyline(std::int32_t precision = 5) const
    {
        return polyline::encode(lat, precision) + polyline::encode(lng, precision);
    }

  private:
    /// for allow basic_geometry to access basic_point private members
    friend class basic_geometry<basic_point<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINT;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Point";
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        return dimension_type::XY;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        return 2;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    detail::bounds bounds_() const
    {
        return {x, y, x, y};
    }

    /// @private
    bool has_z_() const noexcept
    {
        return false;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return false;
    }

    // json

    /// @private
    static basic_point<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").get<std::vector<double>>();
            return {coords.at(0), coords.at(1)};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
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
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINT)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return {data.coords[0], data.coords[1]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POINT "
           << "(" << x << " " << y << ")";
        return ss.str();
    }
};

// xyz

/*!
 * @brief DOCUMENT ME!
 * @tparam T
 * @ingroup geometry
 *
 * @since 0.0.1
 */
template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point_z : public basic_geometry<basic_point_z<T>>
{
  public:
    /// DOCUMENT ME!
    using point_type = basic_point_z;
    /// DOCUMENT ME!
    using coord_type = T;
    /// DOCUMENT ME!
    using coord_iterator = typename std::vector<coord_type>::iterator;
    /// DOCUMENT ME!
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    union
    {
        struct
        {
            T x;
            T y;
            T z;
        };

        struct
        {
            T lng;
            T lat;
            T height;
        };

        T coords[3];
    };

    /*!
     * @brief DOCUMENT ME!
     */
    basic_point_z()
        : x(0), y(0), z(0) {}

    /*!
     * @brief DOCUMENT ME!
     * @param x
     * @param y
     * @param z
     */
    basic_point_z(T x, T y, T z)
        : x(x), y(y), z(z) {}

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point_z(coord_iterator begin, coord_iterator end)
    {
        assert(std::distance(begin, end) == 3);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point_z(coord_const_iterator begin, coord_const_iterator end)
    {
        assert(std::distance(begin, end) == 3);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    std::size_t size() const noexcept
    {
        return static_cast<std::size_t>(ndim_());
    }

    // operators

    /*!
     * @brief DOCUMENT ME!
     * @param pos
     * @return
     */
    T& operator[](size_t pos)
    {
        assert(pos < 3);
        return coords[pos];
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator==(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z;
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator!=(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

  private:
    /// for allow basic_geometry to access basic_point_z private members
    friend class basic_geometry<basic_point_z<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINTZ;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Point";
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        return dimension_type::XYZ;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        return 3;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    detail::bounds bounds_() const
    {
        return {x, y, x, y};
    }

    /// @private
    bool has_z_() const noexcept
    {
        return true;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return false;
    }

    // json

    /// @private
    static basic_point_z<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").get<std::vector<double>>();
            return {coords.at(0), coords.at(1), coords.at(2)};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
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
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "," << z << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point_z<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINTZ)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return {data.coords[0], data.coords[1], data.coords[2]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POINT Z "
           << "(" << x << " " << y << " " << z << ")";
        return ss.str();
    }
};

// xym

/*!
 * @brief DOCUMENT ME!
 * @tparam T
 * @ingroup geometry
 */
template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point_m : public basic_geometry<basic_point_m<T>>
{
  public:
    /// DOCUMENT ME!
    using point_type = basic_point_m;
    /// DOCUMENT ME!
    using coord_type = T;
    /// DOCUMENT ME!
    using coord_iterator = typename std::vector<coord_type>::iterator;
    /// DOCUMENT ME!
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    union
    {
        struct
        {
            T x;
            T y;
            T m;
        };

        struct
        {
            T lng;
            T lat;
            T measure;
        };

        T coords[3];
    };

    /*!
     * @brief DOCUMENT ME!
     */
    basic_point_m()
        : x(0), y(0), m(0) {}

    /*!
     * @brief DOCUMENT ME!
     * @param x
     * @param y
     * @param m
     */
    basic_point_m(T x, T y, T m)
        : x(x), y(y), m(m) {}

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point_m(coord_iterator begin, coord_iterator end)
    {
        assert(std::distance(begin, end) == 3);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point_m(coord_const_iterator begin, coord_const_iterator end)
    {
        assert(std::distance(begin, end) == 3);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    std::size_t size() const noexcept
    {
        return static_cast<std::size_t>(ndim_());
    }

    // operators

    /*!
     * @brief DOCUMENT ME!
     * @param pos
     * @return
     */
    T& operator[](size_t pos)
    {
        assert(pos < 3);
        return coords[pos];
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator==(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.m == rhs.m;
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator!=(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

  private:
    /// for allow basic_geometry to access basic_point_m private members
    friend class basic_geometry<basic_point_m<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINTM;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Point";
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        return dimension_type::XYM;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        return 3;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    detail::bounds bounds_() const
    {
        return {x, y, x, y};
    }

    /// @private
    bool has_z_() const noexcept
    {
        return false;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return true;
    }

    // json

    /// @private
    static basic_point_m<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").get<std::vector<double>>();
            return {coords.at(0), coords.at(1), coords.at(2)};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
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
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "," << m << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point_m<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINTM)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return {data.coords[0], data.coords[1], data.coords[2]};
    }

    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POINT M "
           << "(" << x << " " << y << " " << m << ")";
        return ss.str();
    }
};

// xyzm

/*!
 * @brief DOCUMENT ME!
 * @tparam T
 * @ingroup geometry
 */
template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point_zm : public basic_geometry<basic_point_zm<T>>
{
  public:
    /// DOCUMENT ME!
    using point_type = basic_point_zm;
    /// DOCUMENT ME!
    using coord_type = T;
    /// DOCUMENT ME!
    using coord_iterator = typename std::vector<coord_type>::iterator;
    /// DOCUMENT ME!
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    union
    {
        struct
        {
            T x;
            T y;
            T z;
            T m;
        };

        struct
        {
            T lng;
            T lat;
            T height;
            T measure;
        };

        T coords[4];
    };

    /*!
     * @brief DOCUMENT ME!
     */
    basic_point_zm()
        : x(0), y(0), z(0), m(0) {}

    /*!
     * @brief DOCUMENT ME!
     * @param x
     * @param y
     * @param z
     * @param m
     */
    basic_point_zm(T x, T y, T z, T m)
        : x(x), y(y), z(z), m(m) {}

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point_zm(coord_iterator begin, coord_iterator end)
    {
        assert(std::distance(begin, end) == 4);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @param begin
     * @param end
     */
    explicit basic_point_zm(coord_const_iterator begin, coord_const_iterator end)
    {
        assert(std::distance(begin, end) == 4);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    /*!
     * @brief DOCUMENT ME!
     * @return
     */
    std::size_t size() const noexcept
    {
        return static_cast<std::size_t>(ndim_());
    }

    // operators

    /*!
     * @brief DOCUMENT ME!
     * @param pos
     * @return
     */
    T& operator[](size_t pos)
    {
        assert(pos < 4);
        return coords[pos];
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator==(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z and lhs.m == rhs.m;
    }

    /*!
     * @brief DOCUMENT ME!
     * @param lhs
     * @param rhs
     * @return
     */
    friend bool operator!=(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

  private:
    /// for allow basic_geometry to access basic_point_zm private members
    friend class basic_geometry<basic_point_zm<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        return geometry_type::POINTZM;
    }

    /// @private
    std::string tagged_text_() const noexcept
    {
        return "Point";
    }

    /// @private
    dimension_type dim_() const noexcept
    {
        return dimension_type::XYZM;
    }

    /// @private
    int32_t ndim_() const noexcept
    {
        return 4;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        // do nothing
    }

    /// @private
    detail::bounds bounds_() const
    {
        return {x, y, x, y};
    }

    /// @private
    bool has_z_() const noexcept
    {
        return true;
    }

    /// @private
    bool has_m_() const noexcept
    {
        return true;
    }

    // json

    /// @private
    static basic_point_zm<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = nlohmann::json::parse(json);
            auto geom_type = j.at("type").get<std::string>();
            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").get<std::vector<double>>();
            return {coords.at(0), coords.at(1), coords.at(2), coords.at(3)};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
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
        ss << "{\"type\":\"Point\",\"coordinates\":"
           << "[" << x << "," << y << "," << z << "," << m << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_point_zm<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result = reader.read(wkt);
        auto data   = result.data;
        if (data.geom_type != geometry_type::POINTZM)
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return {data.coords[0], data.coords[1], data.coords[2], data.coords[3]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "POINT ZM "
           << "(" << x << " " << y << " " << z << " " << m << ")";
        return ss.str();
    }
};

// xy

template <class T = double>
using point = basic_point<T>;

template <class T = double>
using point_z = basic_point_z<T>;

template <class T = double>
using point_m = basic_point_m<T>;

template <class T = double>
using point_zm = basic_point_zm<T>;

using Point   = point<double>;
using PointZ  = point_z<double>;
using PointM  = point_m<double>;
using PointZM = point_zm<double>;

}  // namespace shapes
}  // namespace simo