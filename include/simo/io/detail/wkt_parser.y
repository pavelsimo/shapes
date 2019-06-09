%include {

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4189)
#endif

}

%extra_argument { struct wkt_result *result }

%token_type {double}

%stack_overflow {
    result->parser_error = true;
}

%stack_size 1048576

%syntax_error {
    result->parser_error = true;
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
wkt_text ::= geometrycollection.
wkt_text ::= geometrycollection_z.
wkt_text ::= geometrycollection_m.
wkt_text ::= geometrycollection_zm.

coord(A) ::= WKT_NUM(B). { A = B; }

//========
// point |
//========

// point

point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = geometry_type::POINT;
}

point ::= WKT_POINT_TAGGED_TEXT point_text.
{
    result->data.geom_type = geometry_type::POINT;
}

// point z

point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = geometry_type::POINTZ;
}

point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z.
{
    result->data.geom_type = geometry_type::POINTZ;
}

// point m

point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = geometry_type::POINTM;
}

point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m.
{
    result->data.geom_type = geometry_type::POINTM;
}

// point zm

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = geometry_type::POINTZM;
}

point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm.
{
    result->data.geom_type = geometry_type::POINTZM;
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
    result->data.geom_type = geometry_type::MULTIPOINT;
}

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINT;
}

multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINT;
}

// multipoint z

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOINTZ;
}

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINTZ;
}

multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINTZ;
}

// multipoint m

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOINTM;
}

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINTM;
}

multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINTM;
}

// multipoint zm

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOINTZM;
}

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINTZM;
}

multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN.
{
    result->data.geom_type = geometry_type::MULTIPOINTZM;
}

//=============
// linestring |
//=============

linestring_text ::= WKT_LPAREN coord_xy  WKT_COMMA coord_xy  coord_xy_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

linestring_text_z ::= WKT_LPAREN coord_xyz  WKT_COMMA coord_xyz  coord_xyz_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

linestring_text_m ::= WKT_LPAREN coord_xym  WKT_COMMA coord_xym  coord_xym_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

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
    result->data.geom_type = geometry_type::LINESTRING;
}

linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text.
{
    result->data.geom_type = geometry_type::LINESTRING;
}

// linestring z

linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::LINESTRINGZ;
}

linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z.
{
    result->data.geom_type = geometry_type::LINESTRINGZ;
}

// linestring m

linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::LINESTRINGM;
}

linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m.
{
    result->data.geom_type = geometry_type::LINESTRINGM;
}

// linestring zm

linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::LINESTRINGZM;
}

linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm.
{
    result->data.geom_type = geometry_type::LINESTRINGZM;
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
    result->data.geom_type = geometry_type::MULTILINESTRING;
}

multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text.
{
    result->data.geom_type = geometry_type::MULTILINESTRING;
}

// multilinestring z

multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTILINESTRINGZ;
}

multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z.
{
    result->data.geom_type = geometry_type::MULTILINESTRINGZ;
}

// multilinestring m

multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTILINESTRINGM;
}

multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m.
{
    result->data.geom_type = geometry_type::MULTILINESTRINGM;
}

// multilinestring zm

multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTILINESTRINGZM;
}

multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm.
{
    result->data.geom_type = geometry_type::MULTILINESTRINGZM;
}

//==========
// polygon |
//==========

ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

ring_text_z ::= WKT_LPAREN coord_xyz  WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

ring_text_m ::= WKT_LPAREN coord_xym  WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN.
{
    result->data.offsets.push_back(result->data.coords.size());
}

ring_text_repeated ::= .
ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated.

ring_text_z_repeated ::= .
ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated.

ring_text_m_repeated ::= .
ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated.

ring_text_zm_repeated ::= .
ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated.

polygon_text    ::=  WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN.
polygon_text_z  ::=  WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN.
polygon_text_m  ::=  WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN.
polygon_text_zm ::=  WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN.

polygon_text_repeated ::= .
polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated.

polygon_text_z_repeated ::= .
polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated.

polygon_text_m_repeated ::= .
polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated.

polygon_text_zm_repeated ::= .
polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated.

polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::POLYGON;
}

polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text.
{
    result->data.geom_type = geometry_type::POLYGON;
}

polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::POLYGONZ;
}

polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z.
{
    result->data.geom_type = geometry_type::POLYGONZ;
}

polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::POLYGONM;
}

polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m.
{
    result->data.geom_type = geometry_type::POLYGONM;
}

polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::POLYGONZM;
}

polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm.
{
    result->data.geom_type = geometry_type::POLYGONZM;
}

//===============
// multipolygon |
//===============

multipolygon_text    ::=  WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN.
multipolygon_text_z  ::=  WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN.
multipolygon_text_m  ::=  WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN.
multipolygon_text_zm ::=  WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN.

multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOLYGON;
}

multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text.
{
    result->data.geom_type = geometry_type::MULTIPOLYGON;
}

multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOLYGONZ;
}

multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z.
{
    result->data.geom_type = geometry_type::MULTIPOLYGONZ;
}

multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOLYGONM;
}

multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m.
{
    result->data.geom_type = geometry_type::MULTIPOLYGONM;
}

multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::MULTIPOLYGONZM;
}

multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm.
{
    result->data.geom_type = geometry_type::MULTIPOLYGONZM;
}

//=====================
// geometrycollection |
//=====================

geometry_text ::= point.
geometry_text ::= multipoint.
geometry_text ::= linestring.
geometry_text ::= multilinestring.
geometry_text ::= polygon.
geometry_text ::= multipolygon.

geometry_text_repeated ::= .
geometry_text_repeated ::= WKT_COMMA geometry_text geometry_text_repeated.

geometry_text_z ::= point_z.
geometry_text_z ::= multipoint_z.
geometry_text_z ::= linestring_z.
geometry_text_z ::= multilinestring_z.
geometry_text_z ::= polygon_z.
geometry_text_z ::= multipolygon_z.

geometry_text_z_repeated ::= .
geometry_text_z_repeated ::= WKT_COMMA geometry_text_z geometry_text_z_repeated.

geometry_text_m ::= point_m.
geometry_text_m ::= multipoint_m.
geometry_text_m ::= linestring_m.
geometry_text_m ::= multilinestring_m.
geometry_text_m ::= polygon_m.
geometry_text_m ::= multipolygon_m.

geometry_text_m_repeated ::= .
geometry_text_m_repeated ::= WKT_COMMA geometry_text_m geometry_text_m_repeated.

geometry_text_zm ::= point_zm.
geometry_text_zm ::= multipoint_zm.
geometry_text_zm ::= linestring_zm.
geometry_text_zm ::= multilinestring_zm.
geometry_text_zm ::= polygon_zm.
geometry_text_zm ::= multipolygon_zm.

geometry_text_zm_repeated ::= .
geometry_text_zm_repeated ::= WKT_COMMA geometry_text_zm geometry_text_zm_repeated.

geometrycollection_text    ::=  WKT_LPAREN geometry_text geometry_text_repeated WKT_RPAREN.
geometrycollection_text_z  ::=  WKT_LPAREN geometry_text_z geometry_text_z_repeated WKT_RPAREN.
geometrycollection_text_m  ::=  WKT_LPAREN geometry_text_m geometry_text_m_repeated WKT_RPAREN.
geometrycollection_text_zm ::=  WKT_LPAREN geometry_text_zm geometry_text_zm_repeated WKT_RPAREN.

geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTION;
}

geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT geometrycollection_text.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTION;
}

geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONZ;
}

geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT geometrycollection_text_z.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONZ;
}

geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONM;
}

geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT geometrycollection_text_m.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONM;
}

geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT WKT_EMPTY_SET.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONZM;
}

geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT geometrycollection_text_zm.
{
    result->data.geom_type = geometry_type::GEOMETRYCOLLECTIONZM;
}

%code {

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

}