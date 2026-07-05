#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <utility>
#include <simo/geom/geometry.hpp>
#include <simo/geom/linearring.hpp>
#include <simo/geom/detail/bounds.hpp>

namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_polygon : public std::vector<T, AllocatorType>, public basic_geometry<basic_polygon<T>>
{
  public:
    using base_type = std::vector<T, AllocatorType>;

    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<T>::iterator;
    using point_const_iterator = typename std::vector<T>::const_iterator;

    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_polygon()
        : base_type() {}

    basic_polygon(point_iterator first, point_iterator last)
        : base_type(first, last)
    {
    }

    basic_polygon(point_const_iterator first, point_const_iterator last)
        : base_type(first, last)
    {
    }

    basic_polygon(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}


    explicit basic_polygon(coord_const_iterator first, coord_const_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(static_cast<size_t>(std::distance(first, last)) / n);
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    explicit basic_polygon(coord_iterator first, coord_iterator last)
    {
        /// @todo deal with repetition
        size_t n = this->ndim();
        this->reserve(static_cast<size_t>(std::distance(first, last)) / n);
        for (auto it = first; it != last; it += n)
        {
            this->emplace_back(it, it + n);
        }
    }

    template <typename CoordIterator, typename OffsetIterator>
    basic_polygon(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
    {
        if (std::distance(coord_first, coord_last) > 0)
        {
            auto n = this->ndim();
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

    friend bool operator!=(const basic_polygon<T>& lhs, const basic_polygon<T>& rhs)
    {
        return not operator==(lhs, rhs);
    }

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

    T& exterior()
    {
        return *this->begin();
    }

    T& interiors(size_t pos)
    {
        assert(this->begin() + pos + 1 < this->end());
        return *(this->begin() + pos + 1);
    }

  private:
    /// for allow basic_geometry to access basic_polygon private members
    friend class basic_geometry<basic_polygon<T>>;

    static bool ring_is_closed(const T& ring) noexcept
    {
        if (ring.empty())
        {
            return true;
        }
        return ring.front().x == ring.back().x and ring.front().y == ring.back().y;
    }

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_linestring_z<T>::value)
        {
            return geometry_type::POLYGONZ;
        }
        if (is_basic_linestring_m<T>::value)
        {
            return geometry_type::POLYGONM;
        }
        if (is_basic_linestring_zm<T>::value)
        {
            return geometry_type::POLYGONZM;
        }
        return geometry_type::POLYGON;
    }

    /// @private
    bool is_closed_() const noexcept
    {
        if (this->empty())
        {
            return true;
        }
        for (const auto& ring : *this)
        {
            if (not ring_is_closed(ring))
            {
                return false;
            }
        }
        return true;
    }

    /// @private
    void throw_for_invalid_() const
    {
        for (const auto& ring : *this)
        {
            if (ring.empty())
            {
                throw exceptions::geometry_error("Polygon rings should not be empty");
            }
            if (ring.size() < 4)
            {
                throw exceptions::geometry_error("Polygon rings should have 4 or more points");
            }
            if (not ring_is_closed(ring))
            {
                throw exceptions::geometry_error("Polygon rings should be closed");
            }
            for (const auto& point : ring)
            {
                if (point.empty())
                {
                    throw exceptions::geometry_error("Polygon rings should not contain empty points");
                }
            }
        }
    }

    /// @private
    bounds_t bounds_() const
    {
        bounds_t res{};
        for (const auto& r : *this)
        {
            auto r_bound = r.bounds();
            res.extend(r_bound);
        }
        return res;
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
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "Polygon")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& rings = j.at("coordinates").as_array();
            std::vector<T> res;
            res.reserve(rings.size());
            for (const auto& ring : rings)
            {
                if (ring.is_array() && !ring.empty())
                {
                    const auto& coords_array = ring.as_array();
                    std::vector<point_type> points;
                    points.reserve(coords_array.size());
                    for (const auto& coord : coords_array)
                    {
                        auto point_coords = coord.as_double_array();
                        points.emplace_back(point_coords.begin(), point_coords.end());
                    }
                    res.emplace_back(points.begin(), points.end());
                }
            }
            return basic_polygon<T>(res.begin(), res.end());
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
        out += "{\"type\":\"Polygon\",\"coordinates\":[";
        size_t i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                out += ',';
            }
            out += '[';
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    out += ',';
                }
                out += '[';
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        out += ',';
                    }
                    detail::append_double(out, static_cast<double>(p.coords[k]), precision);
                }
                out += ']';
            }
            out += ']';
            ++i;
        }
        out += "]}";
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
        auto polygon = basic_polygon<T>(result.data.coords.begin(), result.data.coords.end(),
                                        result.data.ring_offsets.begin(), result.data.ring_offsets.end());
        polygon.throw_for_invalid();
        return polygon;
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
        out += "POLYGON";
        if (this->has_z())
        {
            out += 'Z';
        }
        if (this->has_m())
        {
            out += 'M';
        }
        out += '(';
        size_t i = 0;
        for (const auto& ls : *this)
        {
            if (i > 0)
            {
                out += ',';
            }
            out += '(';
            for (size_t j = 0; j < ls.size(); ++j)
            {
                if (j > 0)
                {
                    out += ',';
                }
                const auto& p = ls[j];
                for (size_t k = 0; k < p.size(); ++k)
                {
                    if (k > 0)
                    {
                        out += ' ';
                    }
                    detail::append_double(out, static_cast<double>(p.coords[k]), precision);
                }
            }
            out += ')';
            ++i;
        }
        out += ')';
    }
};

template <typename>
struct is_basic_polygon : std::false_type
{};

template <typename T>
struct is_basic_polygon<basic_polygon<basic_linestring<basic_point<T>>>> : std::true_type
{};

template <typename>
struct is_basic_polygon_z : std::false_type
{};

template <typename T>
struct is_basic_polygon_z<basic_polygon<basic_linestring<basic_point_z<T>>>> : std::true_type
{};

template <typename>
struct is_basic_polygon_m : std::false_type
{};

template <typename T>
struct is_basic_polygon_m<basic_polygon<basic_linestring<basic_point_m<T>>>> : std::true_type
{};

template <typename>
struct is_basic_polygon_zm : std::false_type
{};

template <typename T>
struct is_basic_polygon_zm<basic_polygon<basic_linestring<basic_point_zm<T>>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo
