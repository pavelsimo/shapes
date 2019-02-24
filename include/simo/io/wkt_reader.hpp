#pragma once

#include <simo/geom/geometry.hpp>
#include <simo/exceptions.hpp>
#include <simo/io/wkt_parser.hpp>
#include <simo/io/wkt_lexer.hpp>

namespace simo
{
namespace shapes
{

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

    /// wkt_reader destructor
    ~wkt_reader()
    {
        ParseFree(m_parser, free);
    }

    /*!
     * @brief parse the given wkt string
     *
     * @param wkt the wkt string
     * @return wkt_result object
     *
     * @since 0.0.1
     */
    wkt_result read(const char* wkt)
    {
        wkt_lexer lexer(wkt);
        wkt_result result{};
        while (true)
        {
            int token = lexer.scan();
            //std::cout << lexer.get_token() << "\t: " << token << "\n";

            if (token == WKT_END_OF_INPUT)
            {
                break;
            }

            if (token == WKT_PARSE_ERROR)
            {
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

            if (result.parser_error == 1)
            {
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