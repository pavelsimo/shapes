#pragma once

#include <ciso646>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <simo/geom/detail/geometry.hpp>
#include <simo/geom/detail/bounds.hpp>

namespace simo
{
namespace shapes
{

template <typename T, typename AllocatorType = std::allocator<T>>
class basic_multipolygon
    : public std::vector<T, AllocatorType>,
      public basic_geometry<basic_multipolygon<T>>
{
  public:
    using base_type = std::vector<T, AllocatorType>;

    using polygon_type           = T;
    using polygon_iterator       = typename std::vector<polygon_type>::iterator;
    using polygon_const_iterator = typename std::vector<polygon_type>::const_iterator;

    using point_type           = typename T::point_type;
    using point_iterator       = typename std::vector<point_type>::iterator;
    using point_const_iterator = typename std::vector<point_type>::const_iterator;

    using coord_type           = typename T::coord_type;
    using coord_iterator       = typename std::vector<coord_type>::iterator;
    using coord_const_iterator = typename std::vector<coord_type>::const_iterator;

    basic_multipolygon()
        : base_type() {}

    basic_multipolygon(polygon_iterator first, polygon_iterator last)
        : base_type(first, last)
    {
    }

    basic_multipolygon(polygon_const_iterator first, polygon_const_iterator last)
        : base_type(first, last)
    {
    }

    basic_multipolygon(std::initializer_list<T> init)
        : base_type(init.begin(), init.end()) {}

    template <typename CoordIterator, typename OffsetIterator>
    basic_multipolygon(CoordIterator coord_first, CoordIterator coord_last, OffsetIterator offset_first, OffsetIterator offset_last)
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

    friend bool operator==(const basic_multipolygon<T>& lhs, const basic_multipolygon<T>& rhs)
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

    friend bool operator!=(const basic_multipolygon<T>& lhs, const basic_multipolygon<T>& rhs)
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

  private:
    /// for allow basic_geometry to access basic_multipoint private members
    friend class basic_geometry<basic_multipolygon<T>>;

    /// @private
    geometry_type geom_type_() const noexcept
    {
        if (is_basic_polygon_z<T>::value)
        {
            return geometry_type::MULTIPOLYGONZ;
        }
        if (is_basic_polygon_m<T>::value)
        {
            return geometry_type::MULTIPOLYGONM;
        }
        if (is_basic_polygon_zm<T>::value)
        {
            return geometry_type::MULTIPOLYGONZM;
        }
        return geometry_type::MULTIPOLYGON;
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
        for (const auto& ls : *this)
        {
            ls.throw_for_invalid();
        }
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

    // json

    /// @private
    static basic_multipolygon<T> from_json_(const std::string& json)
    {
        try
        {
            auto j         = io::geojson_parser::parse(json);
            auto geom_type = j.at("type").as_string();
            if (geom_type != "MultiPolygon")
            {
                throw exceptions::parse_error("invalid geometry type: " + std::string(geom_type));
            }
            const auto& polygons = j.at("coordinates").as_array();
            std::vector<T> res;
            res.reserve(polygons.size());
            for (const auto& polygon : polygons)
            {
                if (polygon.is_array() && !polygon.empty())
                {
                    // Each polygon is an array of rings (exterior + holes)
                    const auto& rings = polygon.as_array();
                    using ring_type = typename T::value_type;
                    std::vector<ring_type> polygon_rings;
                    polygon_rings.reserve(rings.size());
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
                            polygon_rings.emplace_back(points.begin(), points.end());
                        }
                    }
                    res.emplace_back(polygon_rings.begin(), polygon_rings.end());
                }
            }
            return basic_multipolygon<T>(res.begin(), res.end());
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
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "{\"type\":\"Multipolygon\",\"coordinates\":[";
        for (size_t polygon_index = 0; polygon_index < this->size(); ++polygon_index)
        {
            const auto& pg = (*this)[polygon_index];
            if (polygon_index > 0)
            {
                ss << ",";
            }
            ss << "[";
            for (size_t ring_index = 0; ring_index < pg.size(); ++ring_index)
            {
                const auto& ring = pg[ring_index];
                if (ring_index > 0)
                {
                    ss << ",";
                }
                ss << "[";
                for (size_t point_index = 0; point_index < ring.size(); ++point_index)
                {
                    const auto& p = ring[point_index];
                    if (point_index > 0)
                    {
                        ss << ",";
                    }
                    ss << "[";
                    for (size_t coord_index = 0; coord_index < p.size(); ++coord_index)
                    {
                        if (coord_index > 0)
                        {
                            ss << ",";
                        }
                        ss << p.coords[coord_index];
                    }
                    ss << "]";
                }
                ss << "]";
            }
            ss << "]";
        }
        ss << "]}";
        return ss.str();
    }

    // wkt

    /// @private
    static basic_multipolygon<T> from_wkt_(const std::string& wkt)
    {
        wkt_reader reader{};
        auto result      = reader.read(wkt);
        const auto& data = result.data;
        if (not utils::is_multipolygon(data.geom_type))
        {
            throw exceptions::parse_error("invalid wkt string");
        }
        return basic_multipolygon<T>(data.coords.begin(), data.coords.end(), data.offsets.begin(), data.offsets.end());
    }

    /// @private
    std::string wkt_(std::int32_t precision = -1) const
    {
        std::stringstream ss;
        if (precision >= 0)
        {
            ss << std::setprecision(precision);
        }
        ss << "MULTIPOLYGON";
        if (this->has_z())
        {
            ss << "Z";
        }
        if (this->has_m())
        {
            ss << "M";
        }
        size_t polygon_index = 0;
        ss << "(";
        for (const auto& pg : *this)
        {
            if (polygon_index > 0)
            {
                ss << ",";
            }
            ss << "(";
            size_t ring_index = 0;
            for (const auto& ring : pg)
            {
                if (ring_index > 0)
                {
                    ss << ",";
                }
                ss << "(";
                size_t point_index = 0;
                for (const auto& p : ring)
                {
                    if (point_index > 0)
                    {
                        ss << ",";
                    }
                    for (size_t k = 0; k < p.ndim(); ++k)
                    {
                        if (k > 0)
                        {
                            ss << " ";
                        }
                        ss << p.coords[k];
                    }
                    ++point_index;
                }
                ss << ")";
                ++ring_index;
            }
            ss << ")";
            ++polygon_index;
        }
        ss << ")";
        return ss.str();
    }
};

template <typename>
struct is_basic_multipolygon : std::false_type
{};

template <typename T>
struct is_basic_multipolygon<basic_multipolygon<basic_polygon<basic_point<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multipolygon_z : std::false_type
{};

template <typename T>
struct is_basic_multipolygon_z<basic_multipolygon<basic_polygon<basic_point_z<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multipolygon_m : std::false_type
{};

template <typename T>
struct is_basic_multipolygon_m<basic_multipolygon<basic_polygon<basic_point_m<T>>>> : std::true_type
{};

template <typename>
struct is_basic_multipolygon_zm : std::false_type
{};

template <typename T>
struct is_basic_multipolygon_zm<basic_multipolygon<basic_polygon<basic_point_zm<T>>>> : std::true_type
{};

}  // namespace shapes
}  // namespace simo