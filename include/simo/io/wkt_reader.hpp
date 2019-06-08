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
 * @ingroup wkt
 *
 * @since 0.0.1
 */
class wkt_reader
{
  public:
    /*!
     * @brief creates a WKT reader
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
        ParseTrace(stdout, "[shapes] ");
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
                /// @todo (pavel) add position to the error message
                throw exceptions::parse_error("wkt lexer error");
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
                /// @todo (pavel) add position to the error message
                throw exceptions::parse_error("wkt parser error");
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