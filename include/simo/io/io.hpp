#pragma once

#include <ciso646>
#include <cstdint>
#include <string>
#include <vector>
#include <simo/geom/geometry.hpp>
#include <simo/io/wkb_reader.hpp>
#include <simo/io/wkb_writer.hpp>

namespace simo
{
namespace shapes
{
namespace io
{
namespace detail
{

template <typename T>
geometry_t<T> geometry_from_geojson_feature_value(const geojson_value& value)
{
    require_geojson_object(value);
    const auto type = require_geojson_member(value, "type").as_string();
    if (type != "Feature")
    {
        throw exceptions::parse_error("GeoJSON object is not a Feature");
    }
    const auto& geometry = require_geojson_member(value, "geometry");
    if (geometry.is_null())
    {
        throw exceptions::parse_error("GeoJSON Feature geometry is null");
    }
    return geometry_from_geojson_value<T>(geometry);
}

}  // namespace detail
}  // namespace io

template <typename T = double>
geometry_t<T> from_wkt(const std::string& text)
{
    return geometry_t<T>::from_wkt(text);
}

template <typename Geometry>
std::string to_wkt(const Geometry& geometry, std::int32_t precision = -1)
{
    return geometry.wkt(precision);
}

template <typename T = double>
geometry_t<T> from_geojson(const std::string& text)
{
    return geometry_t<T>::from_json(text);
}

template <typename Geometry>
std::string to_geojson(const Geometry& geometry, std::int32_t precision = -1)
{
    return geometry.json(precision);
}

template <typename T = double>
geometry_t<T> from_geojson_feature(const std::string& text)
{
    try
    {
        auto value = io::geojson_parser::parse(text);
        return io::detail::geometry_from_geojson_feature_value<T>(value);
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

template <typename T = double>
std::vector<geometry_t<T>> from_geojson_feature_collection(const std::string& text)
{
    try
    {
        auto value = io::geojson_parser::parse(text);
        io::detail::require_geojson_object(value);
        const auto type = io::detail::require_geojson_member(value, "type").as_string();
        if (type != "FeatureCollection")
        {
            throw exceptions::parse_error("GeoJSON object is not a FeatureCollection");
        }

        const auto& features = io::detail::require_geojson_member(value, "features").as_array();
        std::vector<geometry_t<T>> geometries;
        geometries.reserve(features.size());
        for (const auto& feature : features)
        {
            geometries.emplace_back(io::detail::geometry_from_geojson_feature_value<T>(feature));
        }
        return geometries;
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

template <typename T = double>
geometry_t<T> from_wkb(const std::vector<std::uint8_t>& bytes)
{
    return io::detail::read_wkb<T>(bytes.begin(), bytes.end());
}

template <typename T = double, typename Iterator>
geometry_t<T> from_wkb(Iterator first, Iterator last)
{
    return io::detail::read_wkb<T>(first, last);
}

template <typename Geometry>
std::vector<std::uint8_t> to_wkb(const Geometry& geometry)
{
    return io::detail::write_wkb(geometry, wkb_options{});
}

template <typename Geometry>
std::vector<std::uint8_t> to_wkb(const Geometry& geometry, const wkb_options& options)
{
    return io::detail::write_wkb(geometry, options);
}

}  // namespace shapes
}  // namespace simo
