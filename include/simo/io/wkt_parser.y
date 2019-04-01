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
wkt_text ::= linestring.
wkt_text ::= linestring_z.
wkt_text ::= linestring_m.
wkt_text ::= linestring_zm.

coord(A) ::= WKT_NUM(B). { A = B; }

//========
// point |
//========

// point

point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}

point ::= WKT_POINT_TAGGED_TEXT point_text.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}

// point z

point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}

point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}

// point m

point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}

point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}

// point zm

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}

// coords

coord_xy ::= coord(X) coord(Y).
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
}

coord_xyz ::= coord(X) coord(Y) coord(Z).
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.coords.push_back(Z);
}

coord_xym ::= coord(X) coord(Y) coord(M).
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.coords.push_back(M);
}

coord_xyzm ::= coord(X) coord(Y) coord(Z) coord(M).
{
    result->data.coords.push_back(X);
    result->data.coords.push_back(Y);
    result->data.coords.push_back(Z);
    result->data.coords.push_back(M);
}

// point text

point_text ::= WKT_LPAREN coord_xy WKT_RPAREN.

point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN.

point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN.

point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN.

//=============
// multipoint |
//=============

multipoint_text ::= .
multipoint_text ::= WKT_COMMA point_text multipoint_text.

multipoint_text_2 ::= .
multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2.

multipoint_text_z ::= .
multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z.

multipoint_text_z_2 ::= .
multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2.

multipoint_text_m ::= .
multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m.

multipoint_text_m_2 ::= .
multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2.

multipoint_text_zm ::= .
multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm.

multipoint_text_zm_2 ::= .
multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2.

// multipoint

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}

// multipoint z

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZ;
}

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZ;
}

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZ;
}

// multipoint m

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTM;
}

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTM;
}

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTM;
}

// multipoint zm

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZM;
}

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZM;
}

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZM;
}

//=============
// linestring |
//=============


linestring_text ::= .
linestring_text ::= WKT_COMMA coord_xy linestring_text.

linestring_text_z ::= .
linestring_text_z ::= WKT_COMMA coord_xyz linestring_text_z.

linestring_text_m ::= .
linestring_text_m ::= WKT_COMMA coord_xym linestring_text_m.

linestring_text_zm ::= .
linestring_text_zm ::= WKT_COMMA coord_xyzm linestring_text_zm.

// linestring

linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRING;
}

linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_LPAREN coord_xy linestring_text WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRING;
}

// linestring z

linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZ;
}

linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_LPAREN coord_xyz linestring_text_z WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZ;
}

// linestring m

linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGM;
}

linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_LPAREN coord_xym linestring_text_m WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGM;
}

// linestring zm

linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZM;
}

linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm linestring_text_zm WKT_RPAREN.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZM;
}