%include {
#pragma once

#include <ciso646>
#include <iostream>
#include <cassert>
}

%extra_argument { struct simo::shapes::wkt_result *result }

%token_type {double}

%stack_overflow {
    result->parser_error = 1;
}

%stack_size 1048576

%syntax_error {
    result->parser_error = 1;
}

program ::= wkt_text.
wkt_text ::= point.
wkt_text ::= point_z.
wkt_text ::= point_m.
wkt_text ::= point_zm.
coord(A) ::= WKT_NUM(B). { A = B; }

point ::= WKT_POINT_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) WKT_RPAREN. {
    result->coords.push_back(X);
    result->coords.push_back(Y);
    result->ndim = 2;
    result->dim = simo::shapes::DimensionType::XY;
    result->offsets.push_back(0);
}

point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) coord(Z) WKT_RPAREN. {
    result->coords.push_back(X);
    result->coords.push_back(Y);
    result->coords.push_back(Z);
    result->ndim = 3;
    result->dim = simo::shapes::DimensionType::XYZ;
    result->offsets.push_back(0);
}

point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) coord(M) WKT_RPAREN. {
    result->coords.push_back(X);
    result->coords.push_back(Y);
    result->coords.push_back(M);
    result->ndim = 3;
    result->dim = simo::shapes::DimensionType::XYM;
    result->offsets.push_back(0);
}

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) coord(Z) coord(M) WKT_RPAREN. {
    result->coords.push_back(X);
    result->coords.push_back(Y);
    result->coords.push_back(Z);
    result->coords.push_back(M);
    result->ndim = 4;
    result->dim = simo::shapes::DimensionType::XYZM;
    result->offsets.push_back(0);
}

