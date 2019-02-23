#pragma once

#include <simo/geom/types.hpp>

namespace simo
{
namespace shapes
{

struct wkt_result
{
    int parser_error;
    DimensionType dim;
    int ndim;
    std::vector<double> coords;
    std::vector<std::size_t> offsets;
};

}  // namespace shapes
}  // namespace simo

#include <simo/io/wkt_parser.h>
#include <simo/io/wkt_parser.c>
