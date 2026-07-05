#pragma once

#include <ciso646>
#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <tuple>
#include <string>
#include <type_traits>
#include <simo/io/geojson_parser.hpp>
#include <simo/geom/detail/geometry.hpp>
#include <simo/detail/number_util.hpp>
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

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
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

    bool m_empty;

    /*!
     * @brief Creates a empty point
     */
    basic_point()
        : x(0), y(0), m_empty(true) {}

    /*!
     * @brief Creates a point from the given coordinates
     * @param x the x-coordinate
     * @param y the y-coordinate
     */
    basic_point(T x, T y)
        : x(x), y(y), m_empty(false) {}

    explicit basic_point(coord_iterator begin, coord_iterator end)
        : x(0), y(0), m_empty(true)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), m_empty(true)
    {
        /// @todo (pavel) deal with repetition
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    size_type size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    reference operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    const_reference operator[](size_t pos) const
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point<T>& lhs, const basic_point<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
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
        if (coords.size() != N)
        {
            throw exceptions::parse_error("invalid polyline point");
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

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
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
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
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
        std::string out;
        out.reserve(64);
        write_json_(out, precision);
        return out;
    }

    /// @private
    void write_json_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "{\"type\":\"Point\",\"coordinates\":[]}";
            return;
        }
        out += "{\"type\":\"Point\",\"coordinates\":[";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(y), precision);
        out += "]}";
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
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::string out;
        out.reserve(64);
        write_wkt_(out, precision);
        return out;
    }

    /// @private
    void write_wkt_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "POINT EMPTY";
            return;
        }
        out += "POINT (";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ')';
    }
};

// xyz

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
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

    bool m_empty;

    basic_point_z()
        : x(0), y(0), z(0), m_empty(true) {}

    basic_point_z(T x, T y, T z)
        : x(x), y(y), z(z), m_empty(false) {}

    explicit basic_point_z(coord_iterator begin, coord_iterator end)
        : x(0), y(0), z(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point_z(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), z(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    std::size_t size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    const T& operator[](size_t pos) const
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_z<T>& lhs, const basic_point_z<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
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

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
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
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point_z<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();

            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1)), static_cast<T>(coords.at(2))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
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
        std::string out;
        out.reserve(64);
        write_json_(out, precision);
        return out;
    }

    /// @private
    void write_json_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "{\"type\":\"Point\",\"coordinates\":[]}";
            return;
        }
        out += "{\"type\":\"Point\",\"coordinates\":[";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(z), precision);
        out += "]}";
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
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1], data.coords[2]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::string out;
        out.reserve(64);
        write_wkt_(out, precision);
        return out;
    }

    /// @private
    void write_wkt_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "POINT Z EMPTY";
            return;
        }
        out += "POINT Z (";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(z), precision);
        out += ')';
    }
};

// xym

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
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

    bool m_empty;

    basic_point_m()
        : x(0), y(0), m(0), m_empty(true) {}

    basic_point_m(T x, T y, T m)
        : x(x), y(y), m(m), m_empty(false) {}

    explicit basic_point_m(coord_iterator begin, coord_iterator end)
        : x(0), y(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point_m(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    std::size_t size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    const T& operator[](size_t pos) const
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_m<T>& lhs, const basic_point_m<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
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

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
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
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point_m<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();

            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1)), static_cast<T>(coords.at(2))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
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
        std::string out;
        out.reserve(64);
        write_json_(out, precision);
        return out;
    }

    /// @private
    void write_json_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "{\"type\":\"Point\",\"coordinates\":[]}";
            return;
        }
        out += "{\"type\":\"Point\",\"coordinates\":[";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(m), precision);
        out += "]}";
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
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1], data.coords[2]};
    }

    std::string wkt_(std::int32_t precision = -1) const
    {
        std::string out;
        out.reserve(64);
        write_wkt_(out, precision);
        return out;
    }

    /// @private
    void write_wkt_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "POINT M EMPTY";
            return;
        }
        out += "POINT M (";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(m), precision);
        out += ')';
    }
};

// xyzm

template <class T, typename = std::enable_if_t<std::is_arithmetic<T>::value, T>>
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

    bool m_empty;

    basic_point_zm()
        : x(0), y(0), z(0), m(0), m_empty(true) {}

    basic_point_zm(T x, T y, T z, T m)
        : x(x), y(y), z(z), m(m), m_empty(false) {}

    explicit basic_point_zm(coord_iterator begin, coord_iterator end)
        : x(0), y(0), z(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    explicit basic_point_zm(coord_const_iterator begin, coord_const_iterator end)
        : x(0), y(0), z(0), m(0), m_empty(true)
    {
        assert(std::distance(begin, end) == 0 or std::distance(begin, end) == N);
        if (begin == end)
        {
            return;
        }
        size_t i = 0;
        for (auto it = begin; it != end; ++it)
        {
            coords[i++] = *it;
        }
        m_empty = false;
    }

    std::size_t size() const noexcept
    {
        return m_empty ? 0 : this->ndim();
    }

    // operators

    T& operator[](size_t pos)
    {
        assert(pos < N);
        return coords[pos];
    }

    const T& operator[](size_t pos) const
    {
        assert(pos < N);
        return coords[pos];
    }

    friend bool operator==(const basic_point_zm<T>& lhs, const basic_point_zm<T>& rhs)
    {
        if (lhs.m_empty != rhs.m_empty)
        {
            return false;
        }
        if (lhs.m_empty)
        {
            return true;
        }
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

    bool empty() const noexcept
    {
        return m_empty;
    }

    // iterators

    iterator begin()
    {
        return coords;
    }

    iterator end()
    {
        return coords + size();
    }

    const_iterator begin() const
    {
        return coords;
    }
    const_iterator end() const
    {
        return coords + size();
    }

    reverse_iterator rbegin() noexcept
    {
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() noexcept
    {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return std::reverse_iterator<const_iterator>(begin());
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
        if (m_empty)
        {
            return {};
        }
        return {x, y, x, y};
    }

    // json

    /// @private
    static basic_point_zm<T> from_json_(const std::string& json)
    {
        /// @todo (pavel) deal with repeated code
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();

            if (geom_type != "Point")
            {
                throw exceptions::parse_error("invalid geometry type");
            }
            auto coords = j.at("coordinates").as_double_array();
            if (coords.empty())
            {
                return {};
            }
            if (coords.size() != N)
            {
                throw exceptions::parse_error("invalid coordinate count");
            }
            return {static_cast<T>(coords.at(0)), static_cast<T>(coords.at(1)), static_cast<T>(coords.at(2)), static_cast<T>(coords.at(3))};
        }
        catch (const std::out_of_range& e)
        {
            throw exceptions::parse_error("invalid json: " + std::string(e.what()));
        }
        catch (const io::geojson_parse_error& e)
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
        std::string out;
        out.reserve(64);
        write_json_(out, precision);
        return out;
    }

    /// @private
    void write_json_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "{\"type\":\"Point\",\"coordinates\":[]}";
            return;
        }
        out += "{\"type\":\"Point\",\"coordinates\":[";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(z), precision);
        out += ',';
        detail::append_double(out, static_cast<double>(m), precision);
        out += "]}";
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
        if (data.coords.empty())
        {
            return {};
        }
        return {data.coords[0], data.coords[1], data.coords[2], data.coords[3]};
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::string out;
        out.reserve(64);
        write_wkt_(out, precision);
        return out;
    }

    /// @private
    void write_wkt_(std::string& out, std::int32_t precision) const
    {
        if (m_empty)
        {
            out += "POINT ZM EMPTY";
            return;
        }
        out += "POINT ZM (";
        detail::append_double(out, static_cast<double>(x), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(y), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(z), precision);
        out += ' ';
        detail::append_double(out, static_cast<double>(m), precision);
        out += ')';
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
