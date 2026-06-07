#pragma once

#include <algorithm>
#include <ciso646>
#include <cctype>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>
#include <simo/io/wkt_parser.hpp>
#include <simo/io/wkt_lexer.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a wkt reader
 * @ingroup wkt
 *
 * @since 0.0.1
 */
class wkt_reader
{
  public:
    /*!
     * @brief creates a wkt reader
     *
     * @since 0.0.1
     */
    wkt_reader()
        : m_parser(ParseAlloc(malloc))
    {
    }

    /// destructor
    ~wkt_reader()
    {
        ParseFree(m_parser, free);
    }

    /*!
     * @brief parse the given wkt string
     *
     * @param wkt the wkt string
     * @return a wkt result object
     *
     * @since 0.0.1
     */
    wkt_result read(const std::string& wkt)
    {
        wkt_lexer lexer(wkt);
        wkt_result result{};

#ifdef SHAPES_VERBOSE
        static char WKT_TRACE_PREFIX[] = "[shapes] ";
        ParseTrace(stdout, WKT_TRACE_PREFIX);
#endif
        while (true)
        {
            int token = lexer.scan();
#ifdef SHAPES_VERBOSE
            std::cout << "--> " << lexer.get_token() << '\n';
#endif
            if (token == WKT_END_OF_INPUT)
            {
                break;
            }

            if (token == WKT_PARSE_ERROR)
            {
                throw exceptions::parse_error("lexer error at line " + std::to_string(lexer.get_position()));
            }

            if (token == WKT_NUM)
            {
                Parse(m_parser, token, std::stod(lexer.get_token()), &result);
            }
            else
            {
                Parse(m_parser, token, 0, &result);
            }

            if (result.parser_error)
            {
                throw exceptions::parse_error("parser error for token " + lexer.get_token());
            }
        }

        Parse(m_parser, 0, 0, &result);
        if (result.parser_error)
        {
            throw exceptions::parse_error("parser error");
        }
        normalize_result(wkt, result);
        return result;
    }

  private:
    static std::string compact_upper(const std::string& text)
    {
        std::string res;
        res.reserve(text.size());
        for (char c : text)
        {
            if (std::isspace(static_cast<unsigned char>(c)))
            {
                continue;
            }
            res.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
        }
        return res;
    }

    static std::vector<std::size_t> multipolygon_polygon_offsets(const std::string& wkt)
    {
        std::vector<std::size_t> res;
        auto first_paren = wkt.find('(');
        if (first_paren == std::string::npos)
        {
            return res;
        }

        int depth = 0;
        std::size_t ring_count = 0;
        for (auto it = wkt.begin() + static_cast<std::ptrdiff_t>(first_paren); it != wkt.end(); ++it)
        {
            if (*it == '(')
            {
                ++depth;
            }
            else if (*it == ')')
            {
                if (depth == 3)
                {
                    ++ring_count;
                }
                else if (depth == 2)
                {
                    res.push_back(ring_count);
                }
                --depth;
            }
        }
        return res;
    }

    static void normalize_result(const std::string& wkt, wkt_result& result)
    {
        auto& data = result.data;
        const auto compact = compact_upper(wkt);

        if (utils::is_point(data.geom_type) and compact.find("EMPTY") != std::string::npos)
        {
            data.coords.clear();
        }

        if (utils::is_linestring(data.geom_type) or utils::is_multilinestring(data.geom_type))
        {
            return;
        }

        if (utils::is_polygon(data.geom_type) and not data.ring_offsets.empty() and data.polygon_offsets.empty())
        {
            data.polygon_offsets.push_back(data.ring_offsets.size());
        }

        if (utils::is_multipolygon(data.geom_type) and data.polygon_offsets.empty())
        {
            data.polygon_offsets = multipolygon_polygon_offsets(wkt);
        }

        if (utils::get_geom_type(data.geom_type) == geometry_type::GEOMETRYCOLLECTION)
        {
            data.coords.clear();
            data.line_offsets.clear();
            data.ring_offsets.clear();
            data.polygon_offsets.clear();
        }
    }

    /// pointer to the parser
    void* m_parser = nullptr;
};

}  // namespace shapes
}  // namespace simo
