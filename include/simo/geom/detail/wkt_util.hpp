#pragma once

#include <ciso646>
#include <cctype>
#include <string>
#include <simo/geom/detail/types.hpp>
#include <simo/exceptions.hpp>

namespace simo
{
namespace shapes
{
namespace detail
{

/*!
 * @brief Matches an uppercase keyword against the wkt text as if all whitespace had been
 *        removed and the text uppercased, without copying the input
 * @param wkt the wkt string
 * @param kw the uppercase keyword to match
 * @param start the position in the wkt string to start matching at
 * @return the index just past the match, or std::string::npos when there is no match
 *
 * @since 0.0.1
 */
inline std::size_t wkt_match_prefix(const std::string& wkt, const char* kw, std::size_t start = 0)
{
    std::size_t i = start;
    for (std::size_t k = 0; kw[k] != '\0'; ++k)
    {
        while (i < wkt.size() and std::isspace(static_cast<unsigned char>(wkt[i])))
        {
            ++i;
        }
        if (i >= wkt.size() or std::toupper(static_cast<unsigned char>(wkt[i])) != kw[k])
        {
            return std::string::npos;
        }
        ++i;
    }
    return i;
}

/*!
 * @brief Whether the wkt text starts with the given uppercase keyword, ignoring case and whitespace
 *
 * @since 0.0.1
 */
inline bool wkt_starts_with(const std::string& wkt, const char* kw)
{
    return wkt_match_prefix(wkt, kw) != std::string::npos;
}

/*!
 * @brief Whether the wkt text starts with the GEOMETRYCOLLECTION keyword
 *
 * @since 0.0.1
 */
inline bool wkt_starts_with_geometrycollection(const std::string& wkt)
{
    return wkt_starts_with(wkt, "GEOMETRYCOLLECTION");
}

/*!
 * @brief Whether the wkt text contains the EMPTY keyword, ignoring case and whitespace
 *
 * @since 0.0.1
 */
inline bool wkt_contains_empty(const std::string& wkt)
{
    for (std::size_t i = 0; i < wkt.size(); ++i)
    {
        char c = wkt[i];
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            continue;
        }
        if (std::toupper(static_cast<unsigned char>(c)) == 'E' and wkt_match_prefix(wkt, "EMPTY", i) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

/*!
 * @brief Returns the geometry collection type of the given wkt text
 * @throw parse_error if the text does not start with the GEOMETRYCOLLECTION keyword
 *
 * @since 0.0.1
 */
inline geometry_type wkt_collection_type(const std::string& wkt)
{
    const auto end = wkt_match_prefix(wkt, "GEOMETRYCOLLECTION");
    if (end == std::string::npos)
    {
        throw exceptions::parse_error("invalid geometry collection wkt string");
    }
    if (wkt_match_prefix(wkt, "ZM", end) != std::string::npos)
    {
        return geometry_type::GEOMETRYCOLLECTIONZM;
    }
    if (wkt_match_prefix(wkt, "Z", end) != std::string::npos)
    {
        return geometry_type::GEOMETRYCOLLECTIONZ;
    }
    if (wkt_match_prefix(wkt, "M", end) != std::string::npos)
    {
        return geometry_type::GEOMETRYCOLLECTIONM;
    }
    return geometry_type::GEOMETRYCOLLECTION;
}

}  // namespace detail
}  // namespace shapes
}  // namespace simo
