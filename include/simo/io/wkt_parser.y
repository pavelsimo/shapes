%include {
#pragma once

#include <ciso646>
#include <iostream>
#include <cassert>
}

%extra_argument { struct simo::shapes::WktResult *result }

%token_type {double}

%stack_overflow {
    result->parser_error = 1;
}

%stack_size 1048576

%syntax_error {
    result->parser_error = 1;
#ifdef SHAPES_VERBOSE
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
        int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
        if (a < YYNSTATE + YYNRULE) {
            printf("possible token: %s\n", yyTokenName[i]);
        }
    }
#endif
}

program ::= wkt_text.
wkt_text ::= point.
wkt_text ::= point_z.
wkt_text ::= point_m.
wkt_text ::= point_zm.
wkt_text ::= multipoint.
wkt_text ::= multipoint_z.
wkt_text ::= multipoint_m.
wkt_text ::= multipoint_zm.

coord(A) ::= WKT_NUM(B). { A = B; }

// point

point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}

point ::= WKT_POINT_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) WKT_RPAREN.
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}

point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) coord(Z) WKT_RPAREN.
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.coords.push_back(Z);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}

point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}

point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) coord(M) WKT_RPAREN.
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.coords.push_back(M);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}

point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_LPAREN coord(X) coord(Y) coord(Z) coord(M) WKT_RPAREN.
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.coords.push_back(Z);
    result->data.coords.push_back(M);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}

// multipoint

point_text ::= WKT_LPAREN coord(X) coord(Y) WKT_RPAREN.
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
}

multipoint_text ::= .
multipoint_text ::= WKT_COMMA point_text multipoint_text.

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZ;
}

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTM;
}

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZM;
}