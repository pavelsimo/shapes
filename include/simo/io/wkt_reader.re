#pragma once

#include <iostream>

namespace simo
{
namespace shapes
{

class wkt_lexer
{
  public:
    enum token_type
    {
        point_tagged_text,
        point_z_tagged_text,
        point_m_tagged_text,
        point_zm_tagged_text,
        point_2_text,
        point_3_text,
        point_4_text,
        multipoint_tagged_text,
        multipoint_text,
        parse_error,
        end_of_input
    };

    wkt_lexer(const char* source)
        : content(source)
    {
        start = cursor = source;
        limit          = content + strlen(source);
    }

    token_type scan()
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

        // empty set
        empty_set       = "EMPTY";
        comma           = ",";

        // point
        point_tagged_text     = ws* "POINT" ws*;
        point_tagged_text     { return token_type::point_tagged_text; }
        point_z_tagged_text   = ws* "POINT" ws* "Z" ws*;
        point_z_tagged_text   { return token_type::point_z_tagged_text; }
        point_m_tagged_text   = ws* "POINT" ws* "M" ws*;
        point_m_tagged_text   { return token_type::point_m_tagged_text; }
        point_zm_tagged_text  = ws* "POINT" ws* "ZM" ws*;
        point_zm_tagged_text  { return token_type::point_zm_tagged_text; }

        left_paren      = ws* "(";
        right_paren     = ")" ws*;
        point_2         = ws* number ws+ number ws*;
        point_3         = ws* number ws+ number ws+ number ws*;
        point_4         = ws* number ws+ number ws+ number ws+ number ws*;

        point_2_text      = (empty_set|left_paren point_2 right_paren);
        point_2_text      { return token_type::point_2_text; }

        point_3_text      = (empty_set|left_paren point_3 right_paren);
        point_3_text      { return token_type::point_3_text; }

        point_4_text      = (empty_set|left_paren point_4 right_paren);
        point_4_text      { return token_type::point_4_text; }

        // multipoint
//        multipoint_tagged_text  = ws* "MULTIPOINT" zm?;
//        multipoint_tagged_text  { return token_type::multipoint_tagged_text; }
//
//        multipoint_text         = (empty_set|left_paren point_text (comma point_text)* right_paren);
//        multipoint_text         { return token_type::multipoint_text; }

        end             { return token_type::end_of_input; }
        .               { return token_type::parse_error; }
        */
    }

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