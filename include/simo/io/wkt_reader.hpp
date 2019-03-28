#pragma once

#include <ciso646>
#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>
#include <simo/io/wkt_parser.hpp>
#include <simo/io/wkt_lexer.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief a Well-known text (WKT) markup language reader
 *
 * @since 0.0.1
 */
class WktReader
{
  public:
    /*!
     * @brief creates a WKT reader
     *
     * @since 0.0.1
     */
    WktReader()
        : m_parser(ParseAlloc(malloc))
    {
    }

    /// destructor
    ~WktReader()
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
    WktResult read(const char* wkt)
    {
        WktLexer lexer(wkt);
        WktResult result{};
#ifdef SHAPES_DEBUG
        ParseTrace(stdout, "[shapes] ");
#endif
        while (true)
        {
            int token = lexer.scan();
#ifdef SHAPES_DEBUG
            std::cout << "--> " << lexer.get_token() << '\n';
#endif
            if (token == WKT_END_OF_INPUT)
            {
                break;
            }

            if (token == WKT_PARSE_ERROR)
            {
                throw exceptions::ParseError("wkt lexer error");
            }

            if (token == WKT_NUM)
            {
                Parse(m_parser, token, std::stod(lexer.get_token()), &result);
            }
            else
            {
                Parse(m_parser, token, 0, &result);
            }

            if (result.parser_error == 1)
            {
                throw exceptions::ParseError("wkt parser error");
            }
        }
        Parse(m_parser, 0, 0, &result);
        return result;
    }

  private:
    /// pointer to the parser
    void* m_parser = nullptr;
};

}  // namespace shapes
}  // namespace simo