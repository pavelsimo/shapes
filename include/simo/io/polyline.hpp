#pragma once

#include <ciso646>
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
std::string encode(double coord, int32_t precision = 5)
{
    assert(precision >= 0);
    double pow10 = std::pow(10, precision);
    auto value   = static_cast<int32_t>(std::round(coord * pow10));
    value <<= 1;
    if (coord < 0)
    {
        value = ~value;
    }
    std::string res;
    while (value >= CHUNK_THRESHOLD)
    {
        int32_t ch = ((value & CHUNK_MASK) | CHUNK_THRESHOLD) + ASCII_OFFSET;
        res += static_cast<char>(ch);
        value >>= CHUNK_SIZE;
    }
    res += static_cast<char>(value + ASCII_OFFSET);
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
int32_t advance(const std::string& text, size_t& index)
{
    int32_t res   = 0;
    int32_t shift = 0;
    char ch       = 0;
    while (index < text.size())
    {
        ch = text[index++] - ASCII_OFFSET;
        res |= (ch & CHUNK_MASK) << shift;
        shift += CHUNK_SIZE;
        if (ch < CHUNK_THRESHOLD)
        {
            break;
        }
    }
    if (res & 1)
    {
        res = ~res;
    }
    res >>= 1;
    return res;
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
std::vector<double> decode(const std::string& text, int32_t precision = 5)
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