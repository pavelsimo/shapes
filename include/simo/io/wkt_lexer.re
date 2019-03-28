#pragma once

#include <ciso646>
#include <iostream>

namespace simo
{
namespace shapes
{

/*!
 * @brief a Well-known text (WKT) markup language lexer
 *
 * @since 0.0.1
 */
class WktLexer
{
  public:

    /*!
     * @brief creates a wkt lexer from the given source
     * @param source the source string
     *
     * @since 0.0.1
     */
    WktLexer(const char* source)
        : content(source)
    {
        start = cursor = source;
        limit          = content + strlen(source);
    }

    /*!
     * @brief scan the next token
     * @return the numeric token identifier
     *
     * @since 0.0.1
     */
    int scan()
    {

        /// pointer for backtracking information
        const char* marker = nullptr;

        start = cursor;

        /*!re2c
          re2c:yyfill:enable = 0;
          re2c:define:YYCTYPE  = char;
          re2c:define:YYCURSOR = cursor;
          re2c:define:YYLIMIT  = limit;
          re2c:define:YYMARKER = marker;
          re2c:labelprefix     = "shapes_wkt_lexer_";

          end          = "\x00";

          // white space
          ws            = [ \t\n\r];
          ws            { return scan(); }

          // number
          decimal_point = [.];
          digit         = [0-9];
          digit_1_9     = [1-9];
          e             = [eE];
          minus         = [-];
          plus          = [+];
          zero          = [0];
          exp           = e (minus|plus)? digit+;
          frac          = decimal_point digit+;
          int           = (zero|digit_1_9 digit*);
          number        = minus? int frac? exp?;
          number        { return WKT_NUM; }

          left_paren      = "(";
          left_paren      { return WKT_LPAREN; }
          right_paren     = ")";
          right_paren     { return WKT_RPAREN; }

          // empty set
          empty_set       = "EMPTY";
          empty_set       { return WKT_EMPTY_SET; }

          // comma
          //comma           = ",";
          //comma           { return WKT_COMMA; }

          // point
          point_tagged_text     = "POINT";
          point_tagged_text     { return WKT_POINT_TAGGED_TEXT; }
          point_z_tagged_text   = "POINT" ws* "Z";
          point_z_tagged_text   { return WKT_POINT_Z_TAGGED_TEXT; }
          point_m_tagged_text   = "POINT" ws* "M";
          point_m_tagged_text   { return WKT_POINT_M_TAGGED_TEXT; }
          point_zm_tagged_text  = "POINT" ws* "ZM";
          point_zm_tagged_text  { return WKT_POINT_ZM_TAGGED_TEXT; }





          end             { return WKT_END_OF_INPUT; }
          .               { return WKT_PARSE_ERROR; }
        */
    }

    /*!
     * @brief returns the current token string
     * @return the token string
     *
     * @since 0.0.1
     */
    std::string get_token() const
    {
        return std::string(reinterpret_cast<const char*>(start), static_cast<size_t>(cursor - start));
    }

  private:
    /// pointer to the buffer
    const char* content = nullptr;

    /// pointer to the beginning of the current token
    const char* start = nullptr;

    /// pointer to the current token
    const char* cursor = nullptr;

    /// pointer to the end of the buffer
    const char* limit = nullptr;
};

}  // namespace shapes
}  // namespace simo