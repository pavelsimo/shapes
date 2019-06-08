#pragma once

#include <ciso646>
#include <iostream>
#include <simo/io/wkt_token.hpp>

namespace simo
{

namespace shapes
{

/*!
 * @brief A Well-known text (WKT) markup language lexer
 * @ingroup wkt
 *
 * @since 0.0.1
 */
class wkt_lexer
{
  public:

    /*!
     * @brief creates a wkt lexer from the given source
     * @param source the source string
     *
     * @since 0.0.1
     */
    wkt_lexer(const std::string& source)
            : content(source)
    {
        start = cursor = source.c_str();
        limit          = start + source.size();
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
          empty_set       = 'EMPTY';
          empty_set       { return WKT_EMPTY_SET; }

          // comma
          comma           = ",";
          comma           { return WKT_COMMA; }

          // point
          point_tagged_text     = 'POINT';
          point_tagged_text     { return WKT_POINT_TAGGED_TEXT; }
          point_z_tagged_text   = 'POINT' ws* 'Z';
          point_z_tagged_text   { return WKT_POINT_Z_TAGGED_TEXT; }
          point_m_tagged_text   = 'POINT' ws* 'M';
          point_m_tagged_text   { return WKT_POINT_M_TAGGED_TEXT; }
          point_zm_tagged_text  = 'POINT' ws* 'ZM';
          point_zm_tagged_text  { return WKT_POINT_ZM_TAGGED_TEXT; }

          // multipoint
          multipoint_tagged_text     = 'MULTIPOINT';
          multipoint_tagged_text     { return WKT_MULTIPOINT_TAGGED_TEXT; }
          multipoint_z_tagged_text   = 'MULTIPOINT' ws* 'Z';
          multipoint_z_tagged_text   { return WKT_MULTIPOINT_Z_TAGGED_TEXT; }
          multipoint_m_tagged_text   = 'MULTIPOINT' ws* 'M';
          multipoint_m_tagged_text   { return WKT_MULTIPOINT_M_TAGGED_TEXT; }
          multipoint_zm_tagged_text  = 'MULTIPOINT' ws* 'ZM';
          multipoint_zm_tagged_text  { return WKT_MULTIPOINT_ZM_TAGGED_TEXT; }

          // linestring
          linestring_tagged_text     = 'LINESTRING';
          linestring_tagged_text     { return WKT_LINESTRING_TAGGED_TEXT; }
          linestring_z_tagged_text   = 'LINESTRING' ws* 'Z';
          linestring_z_tagged_text   { return WKT_LINESTRING_Z_TAGGED_TEXT; }
          linestring_m_tagged_text   = 'LINESTRING' ws* 'M';
          linestring_m_tagged_text   { return WKT_LINESTRING_M_TAGGED_TEXT; }
          linestring_zm_tagged_text  = 'LINESTRING' ws* 'ZM';
          linestring_zm_tagged_text  { return WKT_LINESTRING_ZM_TAGGED_TEXT; }

          // multilinestring
          multilinestring_tagged_text     = 'MULTILINESTRING';
          multilinestring_tagged_text     { return WKT_MULTILINESTRING_TAGGED_TEXT; }
          multilinestring_z_tagged_text   = 'MULTILINESTRING' ws* 'Z';
          multilinestring_z_tagged_text   { return WKT_MULTILINESTRING_Z_TAGGED_TEXT; }
          multilinestring_m_tagged_text   = 'MULTILINESTRING' ws* 'M';
          multilinestring_m_tagged_text   { return WKT_MULTILINESTRING_M_TAGGED_TEXT; }
          multilinestring_zm_tagged_text  = 'MULTILINESTRING' ws* 'ZM';
          multilinestring_zm_tagged_text  { return WKT_MULTILINESTRING_ZM_TAGGED_TEXT; }

          // polygon
          polygon_tagged_text     = 'POLYGON';
          polygon_tagged_text     { return WKT_POLYGON_TAGGED_TEXT; }
          polygon_z_tagged_text   = 'POLYGON' ws* 'Z';
          polygon_z_tagged_text   { return WKT_POLYGON_Z_TAGGED_TEXT; }
          polygon_m_tagged_text   = 'POLYGON' ws* 'M';
          polygon_m_tagged_text   { return WKT_POLYGON_M_TAGGED_TEXT; }
          polygon_zm_tagged_text  = 'POLYGON' ws* 'ZM';
          polygon_zm_tagged_text  { return WKT_POLYGON_ZM_TAGGED_TEXT; }

          // multipolygon
          multipolygon_tagged_text     = 'MULTIPOLYGON';
          multipolygon_tagged_text     { return WKT_MULTIPOLYGON_TAGGED_TEXT; }
          multipolygon_z_tagged_text   = 'MULTIPOLYGON' ws* 'Z';
          multipolygon_z_tagged_text   { return WKT_MULTIPOLYGON_Z_TAGGED_TEXT; }
          multipolygon_m_tagged_text   = 'MULTIPOLYGON' ws* 'M';
          multipolygon_m_tagged_text   { return WKT_MULTIPOLYGON_M_TAGGED_TEXT; }
          multipolygon_zm_tagged_text  = 'MULTIPOLYGON' ws* 'ZM';
          multipolygon_zm_tagged_text  { return WKT_MULTIPOLYGON_ZM_TAGGED_TEXT; }

          // geometrycollection
          geometrycollection_tagged_text     = 'GEOMETRYCOLLECTION';
          geometrycollection_tagged_text     { return WKT_GEOMETRYCOLLECTION_TAGGED_TEXT; }
          geometrycollection_z_tagged_text   = 'GEOMETRYCOLLECTION' ws* 'Z';
          geometrycollection_z_tagged_text   { return WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT; }
          geometrycollection_m_tagged_text   = 'GEOMETRYCOLLECTION' ws* 'M';
          geometrycollection_m_tagged_text   { return WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT; }
          geometrycollection_zm_tagged_text  = 'GEOMETRYCOLLECTION' ws* 'ZM';
          geometrycollection_zm_tagged_text  { return WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT; }

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
    /// the source string
    std::string content;

    /// pointer to the beginning of the current token
    const char* start = nullptr;

    /// pointer to the current token
    const char* cursor = nullptr;

    /// pointer to the end of the buffer
    const char* limit = nullptr;
};

}  // namespace shapes
}  // namespace simo