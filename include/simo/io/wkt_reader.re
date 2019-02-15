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
        point_text,
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
        point_tagged_text     = "POINT" ws*;
        point_tagged_text     { return token_type::point_tagged_text; }
        point_tagged_text_z   = "POINT" ws* "Z" ws*;
        point_tagged_text_z   { return token_type::point_z_tagged_text; }
        point_tagged_text_m   = "POINT" ws* "M" ws*;
        point_tagged_text_m   { return token_type::point_m_tagged_text; }
        point_tagged_text_zm  = "POINT" ws* "ZM" ws*;
        point_tagged_text_zm  { return token_type::point_zm_tagged_text; }

        left_paren      = "(";
        right_paren     = ")";
        x               = number;
        y               = number;
        z               = number;
        m               = number;
        point           = ws* x ws+ y (ws+ z)? (ws+ m)? ws*;
        point_text      = (empty_set|left_paren point right_paren);
        point_text      { return token_type::point_text; }

        //
        // multipoint
        //
//            multipoint_tagged_text  = ws* "MULTIPOINT" zm?;
//            multipoint_tagged_text  { return token_type::multipoint_tagged_text; }
//
//            multipoint_text         = (empty_set|left_paren point_text (comma point_text)* right_paren);
//            multipoint_text         { return token_type::multipoint_text; }

        end             { return token_type::end_of_input; }
        .               { return token_type::parse_error; }
        */
    }

    std::string get_token() const
    {
        return std::string(reinterpret_cast<const char*>(start), static_cast<size_t>(cursor - start));
    }

  private:
    /// the buffer
    const char* content = nullptr;
    /// pointer to he beginning of the current symbol
    const char* start = nullptr;
    /// pointer to the current symbol
    const char* cursor = nullptr;
    /// pointer to the end of the buffer
    const char* limit = nullptr;
};

}  // namespace shapes
}  // namespace simo