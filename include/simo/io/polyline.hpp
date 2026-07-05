#pragma once

#include <ciso646>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>
#include <simo/exceptions.hpp>

namespace simo
{
namespace shapes
{
namespace polyline
{

/// the chunk size
constexpr static const int32_t CHUNK_SIZE = 5;

/// a mask to extract the chunks
constexpr static const int32_t CHUNK_MASK = 0x1f;

/// threshold used to signal another value follows or not
constexpr static const int32_t CHUNK_THRESHOLD = 0x20;

/// the ascii offset to apply
constexpr static const int32_t ASCII_OFFSET = 63;

/*!
 * @brief Encode a polyline coordinate
 * @param coord the coordinate value
 * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 * @return the encoded coordinate
 *
 * @since 0.0.1
 */
inline std::string encode(double coord, int32_t precision = 5)
{
    assert(precision >= 0);
    double pow10 = std::pow(10, precision);
    auto value   = static_cast<int32_t>(std::round(coord * pow10));
    auto chunks  = static_cast<uint32_t>(value) << 1;
    if (value < 0)
    {
        chunks = ~chunks;
    }
    std::string res;
    while (chunks >= static_cast<uint32_t>(CHUNK_THRESHOLD))
    {
        uint32_t ch = ((chunks & static_cast<uint32_t>(CHUNK_MASK)) | static_cast<uint32_t>(CHUNK_THRESHOLD)) + static_cast<uint32_t>(ASCII_OFFSET);
        res += static_cast<char>(ch);
        chunks >>= CHUNK_SIZE;
    }
    res += static_cast<char>(chunks + static_cast<uint32_t>(ASCII_OFFSET));
    return res;
}

/*!
 * @brief Decode a section of the polyline string
 * @param text the polyline encoded string
 * @param index the current reading position
 * @return an integer with the decoded delta value
 *
 * @since 0.0.1
 */
inline int32_t advance(const std::string& text, size_t& index)
{
    uint32_t res  = 0;
    int32_t shift = 0;
    while (index < text.size())
    {
        int32_t ch = static_cast<int32_t>(text[index++]) - ASCII_OFFSET;
        res |= static_cast<uint32_t>(ch & CHUNK_MASK) << shift;
        shift += CHUNK_SIZE;
        if (ch < CHUNK_THRESHOLD)
        {
            break;
        }
    }
    if (res & 1u)
    {
        return static_cast<int32_t>(~(res >> 1));
    }
    return static_cast<int32_t>(res >> 1);
}

/*!
 * @brief Decode a polyline string
 * @param text the polyline encoded string
 * @param precision the coordinates precision
 * @sa https://developers.google.com/maps/documentation/utilities/polylinealgorithm
 * @return the decoded coordinates
 *
 * @since 0.0.1
 */
inline std::vector<double> decode(const std::string& text, int32_t precision = 5)
{
    assert(precision >= 0);
    double pow10 = std::pow(10, precision);
    std::vector<double> res;
    res.reserve(text.size() / 3);
    size_t index = 0;
    int32_t y    = 0;
    int32_t x    = 0;
    while (index < text.size())
    {
        y += advance(text, index);
        x += advance(text, index);
        res.push_back(x / pow10);
        res.push_back(y / pow10);
    }
    return res;
}

}  // namespace polyline
}  // namespace shapes
}  // namespace simo