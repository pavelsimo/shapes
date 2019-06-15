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
#include <simo/geom/detail/geometry.hpp>
#include <simo/exceptions.hpp>
#include <simo/io/wkt_reader.hpp>
#include <simo/io/polyline.hpp>

namespace simo
{
namespace shapes
{

#ifdef __GNUC__
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpedantic"
#endif

#ifdef __clang__
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#    pragma clang diagnostic ignored "-Wnested-anon-types"
#endif

#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable : 4201)
#endif

template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point : public basic_geometry<basic_point<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point;
    using coord_type           = T;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 2;

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

        T coords[N];
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

    explicit basic_point(coord_iterator begin, coord_iterator end)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    explicit basic_point(coord_const_iterator begin, coord_const_iterator end)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    size_type size() const noexcept
    {
        return this->ndim();
    }

    // operators

    reference operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y;
    }

    friend bool operator!=(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    // polyline

    static basic_point<T> from_polyline(const std::string& polyline, std::int32_t precision = 5)
    {
        auto coords = polyline::decode(polyline, precision);
        if (coords.size() > N)
        {
            throw exceptions::parse_error("too many points");
        }
        return {coords[0], coords[1]};
    }

    std::string polyline(std::int32_t precision = 5) const
    {
        return polyline::encode(lat, precision) + polyline::encode(lng, precision);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty()
    {
        return begin() == end();
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + N;
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + N;
    }

    reverse_iterator rbegin()
    {
        return coords + N - 1;
    }

    reverse_iterator rend()
    {
        return coords - 1;
    }

    const_reverse_iterator rbegin() const
    {
        return coords + N - 1;
    }

    const_reverse_iterator rend() const
    {
        return coords - 1;
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
    bounds_t bounds_() const
    {
        return {x, y, x, y};
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

template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point_z : public basic_geometry<basic_point_z<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point_z;
    using coord_type           = value_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 3;

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

        T coords[N];
    };

    basic_point_z()
        : x(0), y(0), z(0) {}

    basic_point_z(T x, T y, T z)
        : x(x), y(y), z(z) {}

    explicit basic_point_z(coord_iterator begin, coord_iterator end)
    {
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    explicit basic_point_z(coord_const_iterator begin, coord_const_iterator end)
    {
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    std::size_t size() const noexcept
    {
        return this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z;
    }

    friend bool operator!=(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty()
    {
        return begin() == end();
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + N;
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + N;
    }

    reverse_iterator rbegin()
    {
        return coords + N - 1;
    }

    reverse_iterator rend()
    {
        return coords - 1;
    }

    const_reverse_iterator rbegin() const
    {
        return coords + N - 1;
    }

    const_reverse_iterator rend() const
    {
        return coords - 1;
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
    bounds_t bounds_() const
    {
        return {x, y, x, y};
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

template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point_m : public basic_geometry<basic_point_m<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point_m;
    using coord_type           = value_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 3;

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

        T coords[N];
    };

    basic_point_m()
        : x(0), y(0), m(0) {}

    basic_point_m(T x, T y, T m)
        : x(x), y(y), m(m) {}

    explicit basic_point_m(coord_iterator begin, coord_iterator end)
    {
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    explicit basic_point_m(coord_const_iterator begin, coord_const_iterator end)
    {
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    std::size_t size() const noexcept
    {
        return this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.m == rhs.m;
    }

    friend bool operator!=(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty()
    {
        return begin() == end();
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + N;
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + N;
    }

    reverse_iterator rbegin()
    {
        return coords + N - 1;
    }

    reverse_iterator rend()
    {
        return coords - 1;
    }

    const_reverse_iterator rbegin() const
    {
        return coords + N - 1;
    }

    const_reverse_iterator rend() const
    {
        return coords - 1;
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
    bounds_t bounds_() const
    {
        return {x, y, x, y};
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

template <class T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class basic_point_zm : public basic_geometry<basic_point_zm<T>>
{
  public:
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using difference_type        = std::ptrdiff_t;
    using size_type              = size_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using point_type           = basic_point_zm;
    using coord_type           = value_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    static const size_type N = 4;

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

        T coords[N];
    };

    basic_point_zm()
        : x(0), y(0), z(0), m(0) {}

    basic_point_zm(T x, T y, T z, T m)
        : x(x), y(y), z(z), m(m) {}

    explicit basic_point_zm(coord_iterator begin, coord_iterator end)
    {
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    explicit basic_point_zm(coord_const_iterator begin, coord_const_iterator end)
    {
        assert(std::distance(begin, end) == N);
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
    }

    std::size_t size() const noexcept
    {
        return this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        return lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z and lhs.m == rhs.m;
    }

    friend bool operator!=(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

    size_type max_size() const
    {
        return N;
    }

    bool empty()
    {
        return begin() == end();
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + N;
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + N;
    }

    reverse_iterator rbegin()
    {
        return coords + N - 1;
    }

    reverse_iterator rend()
    {
        return coords - 1;
    }

    const_reverse_iterator rbegin() const
    {
        return coords + N - 1;
    }

    const_reverse_iterator rend() const
    {
        return coords - 1;
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
    bounds_t bounds_() const
    {
        return {x, y, x, y};
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

#ifdef __GNUC__
#    pragma GCC diagnostic pop
#endif

#ifdef __clang__
#    pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#    pragma warning(pop)
#endif

template <typename>
struct is_basic_point : std::false_type
{};

template <typename T>
struct is_basic_point<basic_point<T>> : std::true_type
{};

template <typename>
struct is_basic_point_z : std::false_type
{};

template <typename T>
struct is_basic_point_z<basic_point_z<T>> : std::true_type
{};

template <typename>
struct is_basic_point_m : std::false_type
{};

template <typename T>
struct is_basic_point_m<basic_point_m<T>> : std::true_type
{};

template <typename>
struct is_basic_point_zm : std::false_type
{};

template <typename T>
struct is_basic_point_zm<basic_point_zm<T>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo