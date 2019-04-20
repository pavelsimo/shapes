#pragma once

#include <simo/geom/types.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a Well-known text (WKT) markup language parser result data
 * @ingroup wkt
 *
 * @since 0.0.1
 */
struct WktData
{
    /// the dimension type of the geometry
    GeometryType geom_type;

    /// the coordinates as a sequence of numbers
    std::vector<double> coords;

    /// the offsets in the coordinates sequence
    std::vector<std::size_t> offsets;
};

/*!
 * @brief a Well-known text (WKT) markup language parser result
 *
 * @since 0.0.1
 */
struct WktResult
{
    /// whether there is a parser error
    bool parser_error = false;

    /// the parser result data
    WktData data;
};

#include <simo/io/wkt_parser.h>
#include <simo/io/wkt_parser.c>

}  // namespace shapes
}  // namespace simo
