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
wkt_text ::= multilinestring.
wkt_text ::= multilinestring_z.
wkt_text ::= multilinestring_m.
wkt_text ::= multilinestring_zm.
wkt_text ::= polygon.
wkt_text ::= polygon_z.
wkt_text ::= polygon_m.
wkt_text ::= polygon_zm.
wkt_text ::= multipolygon.
wkt_text ::= multipolygon_z.
wkt_text ::= multipolygon_m.
wkt_text ::= multipolygon_zm.

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

// coords text

coord_xy_repeated ::= .
coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated.

coord_xyz_repeated ::= .
coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated.

coord_xym_repeated ::= .
coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated.

coord_xyzm_repeated ::= .
coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated.

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

linestring_text ::= WKT_LPAREN coord_xy  WKT_COMMA coord_xy  coord_xy_repeated WKT_RPAREN.
linestring_text_z ::= WKT_LPAREN coord_xyz  WKT_COMMA coord_xyz  coord_xyz_repeated WKT_RPAREN.
linestring_text_m ::= WKT_LPAREN coord_xym  WKT_COMMA coord_xym  coord_xym_repeated WKT_RPAREN.
linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN.

linestring_text_repeated ::= .
linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated.

linestring_text_z_repeated ::= .
linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated.

linestring_text_m_repeated ::= .
linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated.

linestring_text_zm_repeated ::= .
linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated.


// linestring

linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRING;
}

linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRING;
}

// linestring z

linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZ;
}

linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZ;
}

// linestring m

linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGM;
}

linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGM;
}

// linestring zm

linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZM;
}

linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZM;
}

//==================
// multilinestring |
//==================

multilinestring_text    ::=  WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN.
multilinestring_text_z  ::=  WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN.
multilinestring_text_m  ::=  WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN.
multilinestring_text_zm ::=  WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN.

// multilinestring

multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRING;
}

multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRING;
}

// multilinestring z

multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGZ;
}

multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGZ;
}

// multilinestring m

multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGM;
}

multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGM;
}

// multilinestring zm

multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGZM;
}

multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGZM;
}

//==========
// polygon |
//==========

polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGON;
}

polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONZ;
}

polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONM;
}

polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONZM;
}

//===============
// multipolygon |
//===============

multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGON;
}

multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONZ;
}

multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONM;
}

multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONZM;
}
