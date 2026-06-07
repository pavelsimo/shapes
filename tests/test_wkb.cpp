#include <ciso646>
#include <catch2/catch_amalgamated.hpp>
#include <cstdint>
#include <cstring>
#include <vector>
#include <simo/shapes.hpp>

using namespace simo::shapes;

namespace
{

void append_u32(std::vector<std::uint8_t>& bytes, std::uint32_t value, bool little_endian)
{
    if (little_endian)
    {
        for (int i = 0; i < 4; ++i)
        {
            bytes.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
        }
        return;
    }

    for (int i = 3; i >= 0; --i)
    {
        bytes.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
    }
}

void append_u64(std::vector<std::uint8_t>& bytes, std::uint64_t value, bool little_endian)
{
    if (little_endian)
    {
        for (int i = 0; i < 8; ++i)
        {
            bytes.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
        }
        return;
    }

    for (int i = 7; i >= 0; --i)
    {
        bytes.push_back(static_cast<std::uint8_t>((value >> (i * 8)) & 0xff));
    }
}

void append_double(std::vector<std::uint8_t>& bytes, double value, bool little_endian)
{
    std::uint64_t bits = 0;
    std::memcpy(&bits, &value, sizeof(value));
    append_u64(bytes, bits, little_endian);
}

void append_header(std::vector<std::uint8_t>& bytes, std::uint32_t type_id, bool little_endian)
{
    bytes.push_back(little_endian ? 1 : 0);
    append_u32(bytes, type_id, little_endian);
}

std::vector<std::uint8_t> point_wkb(std::uint32_t type_id, const std::vector<double>& coords, bool little_endian)
{
    std::vector<std::uint8_t> bytes;
    append_header(bytes, type_id, little_endian);
    for (auto coord : coords)
    {
        append_double(bytes, coord, little_endian);
    }
    return bytes;
}

std::vector<std::uint8_t> linestring_wkb(std::uint32_t type_id, const std::vector<std::vector<double>>& points, bool little_endian)
{
    std::vector<std::uint8_t> bytes;
    append_header(bytes, type_id, little_endian);
    append_u32(bytes, static_cast<std::uint32_t>(points.size()), little_endian);
    for (const auto& point : points)
    {
        for (auto coord : point)
        {
            append_double(bytes, coord, little_endian);
        }
    }
    return bytes;
}

std::vector<std::uint8_t> polygon_wkb(std::uint32_t type_id, const std::vector<std::vector<std::vector<double>>>& rings, bool little_endian)
{
    std::vector<std::uint8_t> bytes;
    append_header(bytes, type_id, little_endian);
    append_u32(bytes, static_cast<std::uint32_t>(rings.size()), little_endian);
    for (const auto& ring : rings)
    {
        append_u32(bytes, static_cast<std::uint32_t>(ring.size()), little_endian);
        for (const auto& point : ring)
        {
            for (auto coord : point)
            {
                append_double(bytes, coord, little_endian);
            }
        }
    }
    return bytes;
}

std::vector<std::uint8_t> collection_wkb(std::uint32_t type_id, const std::vector<std::vector<std::uint8_t>>& children, bool little_endian)
{
    std::vector<std::uint8_t> bytes;
    append_header(bytes, type_id, little_endian);
    append_u32(bytes, static_cast<std::uint32_t>(children.size()), little_endian);
    for (const auto& child : children)
    {
        bytes.insert(bytes.end(), child.begin(), child.end());
    }
    return bytes;
}

template <typename Geometry>
void check_round_trip(const Geometry& geometry)
{
    auto parsed = from_wkb(to_wkb(geometry));
    CHECK(parsed.wkt() == geometry.wkt());
}

}  // namespace

TEST_CASE("WKB reader")
{
    SECTION("parses little-endian and big-endian Point fixtures")
    {
        CHECK(from_wkb(point_wkb(1, {1, 2}, true)).wkt() == "POINT (1 2)");
        CHECK(from_wkb(point_wkb(1, {1, 2}, false)).wkt() == "POINT (1 2)");
    }

    SECTION("parses fixtures for each geometry type")
    {
        const auto point = point_wkb(1, {1, 2}, true);
        const auto line = linestring_wkb(2, {{0, 0}, {1, 1}}, true);
        const auto polygon = polygon_wkb(3, {{{0, 0}, {1, 0}, {1, 1}, {0, 0}}}, true);

        CHECK(from_wkb(point).is_point());
        CHECK(from_wkb(line).is_linestring());
        CHECK(from_wkb(polygon).is_polygon());
        CHECK(from_wkb(collection_wkb(4, {point_wkb(1, {0, 0}, true), point_wkb(1, {1, 1}, true)}, true)).is_multipoint());
        CHECK(from_wkb(collection_wkb(5, {line}, true)).is_multilinestring());
        CHECK(from_wkb(collection_wkb(6, {polygon}, true)).is_multipolygon());
        CHECK(from_wkb(collection_wkb(7, {point, line}, true)).is_geometrycollection());
    }

    SECTION("parses Z, M, and ZM type IDs")
    {
        CHECK(from_wkb(point_wkb(1001, {1, 2, 3}, true)).is_point_z());
        CHECK(from_wkb(point_wkb(2001, {1, 2, 3}, true)).is_point_m());
        CHECK(from_wkb(point_wkb(3001, {1, 2, 3, 4}, true)).is_point_zm());
    }

    SECTION("parses nested geometry collections")
    {
        const auto nested = collection_wkb(7, {point_wkb(1, {3, 4}, true)}, true);
        auto geom = from_wkb(collection_wkb(7, {point_wkb(1, {1, 2}, true), nested}, true));
        REQUIRE(geom.is_geometrycollection());
        auto collection = geom.get_geometrycollection();
        REQUIRE(collection != nullptr);
        REQUIRE(collection->size() == 2);
        CHECK((*collection)[1].is_geometrycollection());
    }

    SECTION("rejects invalid WKB")
    {
        CHECK_THROWS_AS(from_wkb(std::vector<std::uint8_t>{2, 1, 0, 0, 0}), exceptions::parse_error);
        CHECK_THROWS_AS(from_wkb(collection_wkb(8, {}, true)), exceptions::parse_error);
        CHECK_THROWS_AS(from_wkb(std::vector<std::uint8_t>{1, 1, 0}), exceptions::parse_error);
    }
}

TEST_CASE("WKB writer")
{
    SECTION("round-trips every geometry type")
    {
        check_round_trip(Point(1, 2));
        check_round_trip(LineString{{0, 0}, {1, 1}});
        check_round_trip(Polygon{{{0, 0}, {1, 0}, {1, 1}, {0, 0}}});
        check_round_trip(MultiPoint{{0, 0}, {1, 1}});
        check_round_trip(MultiLineString{{{0, 0}, {1, 1}}});
        check_round_trip(MultiPolygon{{{{0, 0}, {1, 0}, {1, 1}, {0, 0}}}});
        check_round_trip(GeometryCollection{geometry(Point(1, 2)), geometry(LineString{{0, 0}, {1, 1}})});
    }

    SECTION("supports explicit byte order")
    {
        wkb_options options;
        options.order = byte_order::big_endian;
        auto bytes = to_wkb(Point(1, 2), options);
        REQUIRE(not bytes.empty());
        CHECK(bytes[0] == 0);
        CHECK(from_wkb(bytes).wkt() == "POINT (1 2)");

        options.order = byte_order::little_endian;
        bytes = to_wkb(Point(1, 2), options);
        REQUIRE(not bytes.empty());
        CHECK(bytes[0] == 1);
        CHECK(from_wkb(bytes).wkt() == "POINT (1 2)");
    }

    SECTION("supports output dimension overrides")
    {
        wkb_options options;
        options.output_dimension = 2;
        auto xy = from_wkb(to_wkb(PointZM(1, 2, 3, 4), options));
        REQUIRE(xy.is_point());
        CHECK(xy.wkt() == "POINT (1 2)");

        options.output_dimension = 3;
        auto z = from_wkb(to_wkb(PointZM(1, 2, 3, 4), options));
        REQUIRE(z.is_point_z());
        CHECK(z.wkt() == "POINT Z (1 2 3)");

        auto m = from_wkb(to_wkb(PointM(1, 2, 3), options));
        REQUIRE(m.is_point_m());
        CHECK(m.wkt() == "POINT M (1 2 3)");

        options.output_dimension = 4;
        CHECK_THROWS_AS(to_wkb(PointZ(1, 2, 3), options), exceptions::parse_error);
    }

    SECTION("round-trips empty Point as NaN WKB coordinates")
    {
        Point point;
        auto parsed = from_wkb(to_wkb(point));
        REQUIRE(parsed.is_point());
        REQUIRE(parsed.get_point() != nullptr);
        CHECK(parsed.get_point()->empty());
    }

    SECTION("supports iterator input and generic geometry dispatch")
    {
        geometry geom(Point(1, 2));
        auto bytes = to_wkb(geom);
        auto parsed = from_wkb<double>(bytes.begin(), bytes.end());
        REQUIRE(parsed.is_point());
        CHECK(parsed.wkt() == "POINT (1 2)");
    }
}
