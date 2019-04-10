/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>

#pragma once

#include <ciso646>
#include <iostream>
#include <cassert>
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 91
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE double
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 1048576
#endif
#define ParseARG_SDECL  struct simo::shapes::WktResult *result ;
#define ParseARG_PDECL , struct simo::shapes::WktResult *result 
#define ParseARG_FETCH  struct simo::shapes::WktResult *result  = yypParser->result 
#define ParseARG_STORE yypParser->result  = result 
#define YYNSTATE 227
#define YYNRULE 118
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   346,  101,  127,  128,  129,  130,  131,  132,  133,  134,
 /*    10 */   135,  136,  137,  138,  139,  140,  141,  142,  143,  144,
 /*    20 */   145,  146,  147,  148,  149,  150,   36,   37,   29,   28,
 /*    30 */    25,  196,   17,  124,   89,   90,   92,   91,   26,   35,
 /*    40 */    32,   31,   27,   33,   34,   30,  119,  122,  123,  125,
 /*    50 */    94,   96,   98,  100,   37,   81,   57,   51,   40,   83,
 /*    60 */    69,   56,   47,   87,   75,   81,  218,   51,   79,  202,
 /*    70 */    81,   71,   38,   88,   23,   56,  198,   21,  120,   51,
 /*    80 */   210,   13,  111,   81,   39,   59,   37,  117,  214,  164,
 /*    90 */   171,   49,   70,   65,   12,   37,  118,  194,   37,   81,
 /*   100 */    10,   41,   20,  173,  110,  168,  153,   50,    2,   51,
 /*   110 */     3,  183,  178,    7,  112,   81,    4,    1,  153,  151,
 /*   120 */   200,   56,  190,  114,   18,    6,  153,   11,  105,  206,
 /*   130 */   153,   56,   51,   18,   52,  153,   56,  104,   80,   51,
 /*   140 */   160,   56,   12,   45,   48,    7,   37,  154,   46,  156,
 /*   150 */    11,   54,   42,  109,    6,   64,   53,   58,   55,  102,
 /*   160 */     6,   20,   63,  204,   61,   67,  103,   60,  174,  162,
 /*   170 */    62,   13,   24,  189,   23,  208,   73,   66,   76,  108,
 /*   180 */   115,   68,   77,  212,  176,   72,    7,  158,   97,  179,
 /*   190 */    14,  116,   82,  107,   74,  216,  181,   86,   84,   99,
 /*   200 */    12,   22,   85,  184,  166,  121,  224,  197,  186,  225,
 /*   210 */   180,  226,  126,  185,  227,  165,  175,  191,  207,  209,
 /*   220 */   155,  170,   15,   16,  203,  219,  182,  161,  199,  213,
 /*   230 */   205,  163,  193,  157,    9,  195,  211,   19,  152,  215,
 /*   240 */   167,  177,  217,   78,  172,  220,   43,  201,    8,  221,
 /*   250 */    93,  222,  187,  223,  159,  188,    5,  106,   44,   18,
 /*   260 */   113,  347,  192,  347,  347,   95,  169,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    10 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    20 */    51,   52,   53,   54,   55,   56,    2,   57,    4,    5,
 /*    30 */     6,   68,    7,   63,   10,   11,   12,   13,   14,   15,
 /*    40 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*    50 */    26,   27,   28,   29,   57,   57,   59,   57,   58,   61,
 /*    60 */    63,   57,   62,   65,   60,   57,    3,   57,   64,    3,
 /*    70 */    57,    8,   62,   65,    8,   57,    3,    7,   65,   57,
 /*    80 */     3,    8,   64,   57,   62,    8,   57,   71,    3,    3,
 /*    90 */    71,   65,   63,    8,    8,   57,   69,    3,   57,   57,
 /*   100 */     7,   63,    8,    3,   63,    3,    1,   65,    8,   57,
 /*   110 */     8,    3,    3,    8,   62,   57,    8,    8,    1,    3,
 /*   120 */    69,   57,    3,   65,    8,    8,    1,    8,   64,    3,
 /*   130 */     1,   57,   57,    8,    8,    1,   57,   62,   64,   57,
 /*   140 */     3,   57,    8,   64,   62,    8,   57,   57,   64,    3,
 /*   150 */     8,    7,   63,   82,    8,   57,   78,    7,   78,   72,
 /*   160 */     8,    8,   59,   82,    7,    7,   83,   79,   72,   57,
 /*   170 */    79,    8,    7,    9,    8,   83,    7,   80,    7,   84,
 /*   180 */    73,   80,   60,   84,   73,   81,    8,   57,   74,   74,
 /*   190 */     7,   85,   57,   75,   81,   85,   75,   57,    7,   76,
 /*   200 */     8,    7,   61,   76,   57,   77,    3,    9,   77,    3,
 /*   210 */     9,    3,    3,    9,    0,   61,    9,   78,   86,    9,
 /*   220 */     9,    9,    7,    7,   81,   89,    9,   60,   80,    9,
 /*   230 */     9,    9,    9,   59,    7,   79,   87,    7,   58,   88,
 /*   240 */     9,    9,    9,   57,    9,    3,    7,    9,    7,    3,
 /*   250 */    66,    3,    9,    3,    9,   66,    7,   70,   58,    8,
 /*   260 */    67,   90,   67,   90,   90,   68,   70,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_MAX 125
static const short yy_shift_ofst[] = {
 /*     0 */    24,  105,  117,  125,  134,  129,  129,  129,  129,  129,
 /*    10 */   129,  129,  129,  129,  129,  129,  129,  129,  129,  129,
 /*    20 */   129,  129,  129,  129,  129,   86,  119,  126,  137,  146,
 /*    30 */    63,   66,   73,   77,   85,   94,  116,  129,  216,  216,
 /*    40 */   239,  249,  249,  251,  239,   25,   25,   70,   70,   93,
 /*    50 */    93,  129,  142,  144,  142,  144,  129,  150,  152,  153,
 /*    60 */   157,  153,  157,  150,  129,  163,  158,  163,  158,  165,
 /*    70 */   165,  166,  169,  166,  169,  171,  178,  171,  129,  183,
 /*    80 */   183,  129,  129,  191,  192,  191,  129,  194,  194,  102,
 /*    90 */   100,  108,  109,  164,  203,  198,  206,  201,  208,  204,
 /*   100 */   209,  214,  207,  210,  211,  215,  212,  217,  220,  221,
 /*   110 */   227,  222,  230,  223,  231,  232,  233,  235,  238,  242,
 /*   120 */   241,  243,  246,  248,  245,  250,
};
#define YY_REDUCE_USE_DFLT (-38)
#define YY_REDUCE_MAX 88
static const short yy_reduce_ofst[] = {
 /*     0 */   -31,    4,   -3,    0,   -2,   89,  -30,   18,   26,   38,
 /*    10 */    42,   52,   58,   64,   74,   79,   22,   84,   75,   10,
 /*    20 */    41,   82,    8,   13,   29,  154,  139,  132,  167,  174,
 /*    30 */   136,  143,  148,  149,  151,  156,  180,  186,  184,  189,
 /*    40 */   187,  193,  195,  200,  196,  197,  -37,   16,   19,   27,
 /*    50 */    51,   90,   78,   71,   80,   81,   98,   87,  103,   88,
 /*    60 */    83,   91,   92,   96,  112,   97,   95,  101,   99,  107,
 /*    70 */   111,  104,  106,  113,  110,  114,  122,  115,  130,  118,
 /*    80 */   121,  135,  140,  123,  141,  127,  147,  128,  131,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   345,  345,  345,  345,  345,  345,  345,  345,  345,  345,
 /*    10 */   345,  345,  345,  345,  345,  345,  345,  345,  345,  345,
 /*    20 */   345,  345,  345,  345,  345,  345,  345,  345,  345,  345,
 /*    30 */   345,  345,  345,  345,  345,  345,  345,  345,  265,  265,
 /*    40 */   277,  267,  267,  345,  277,  269,  269,  279,  279,  271,
 /*    50 */   271,  345,  345,  309,  345,  309,  345,  281,  345,  345,
 /*    60 */   311,  345,  311,  281,  345,  345,  313,  345,  313,  283,
 /*    70 */   283,  345,  315,  345,  315,  285,  345,  285,  345,  287,
 /*    80 */   287,  345,  345,  289,  345,  289,  345,  291,  291,  345,
 /*    90 */   345,  345,  345,  345,  345,  345,  345,  345,  345,  345,
 /*   100 */   345,  345,  345,  345,  345,  345,  345,  345,  345,  345,
 /*   110 */   345,  345,  345,  345,  345,  345,  345,  345,  345,  345,
 /*   120 */   345,  345,  345,  345,  345,  345,  344,  228,  229,  230,
 /*   130 */   231,  232,  233,  234,  235,  236,  237,  238,  239,  240,
 /*   140 */   241,  242,  243,  244,  245,  246,  247,  248,  249,  250,
 /*   150 */   251,  253,  254,  252,  261,  273,  255,  256,  262,  274,
 /*   160 */   257,  258,  263,  275,  259,  260,  264,  276,  293,  278,
 /*   170 */   294,  280,  295,  296,  282,  297,  284,  298,  299,  286,
 /*   180 */   300,  288,  301,  302,  290,  303,  292,  304,  266,  305,
 /*   190 */   317,  318,  268,  306,  319,  320,  270,  307,  321,  322,
 /*   200 */   272,  308,  323,  324,  310,  325,  329,  330,  312,  326,
 /*   210 */   331,  332,  314,  327,  333,  334,  316,  328,  335,  336,
 /*   220 */   337,  338,  339,  340,  341,  342,  343,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "WKT_NUM",       "WKT_POINT_TAGGED_TEXT",  "WKT_EMPTY_SET",
  "WKT_POINT_Z_TAGGED_TEXT",  "WKT_POINT_M_TAGGED_TEXT",  "WKT_POINT_ZM_TAGGED_TEXT",  "WKT_COMMA",   
  "WKT_LPAREN",    "WKT_RPAREN",    "WKT_MULTIPOINT_TAGGED_TEXT",  "WKT_MULTIPOINT_Z_TAGGED_TEXT",
  "WKT_MULTIPOINT_M_TAGGED_TEXT",  "WKT_MULTIPOINT_ZM_TAGGED_TEXT",  "WKT_LINESTRING_TAGGED_TEXT",  "WKT_LINESTRING_Z_TAGGED_TEXT",
  "WKT_LINESTRING_M_TAGGED_TEXT",  "WKT_LINESTRING_ZM_TAGGED_TEXT",  "WKT_MULTILINESTRING_TAGGED_TEXT",  "WKT_MULTILINESTRING_Z_TAGGED_TEXT",
  "WKT_MULTILINESTRING_M_TAGGED_TEXT",  "WKT_MULTILINESTRING_ZM_TAGGED_TEXT",  "WKT_POLYGON_TAGGED_TEXT",  "WKT_POLYGON_Z_TAGGED_TEXT",
  "WKT_POLYGON_M_TAGGED_TEXT",  "WKT_POLYGON_ZM_TAGGED_TEXT",  "WKT_MULTIPOLYGON_TAGGED_TEXT",  "WKT_MULTIPOLYGON_Z_TAGGED_TEXT",
  "WKT_MULTIPOLYGON_M_TAGGED_TEXT",  "WKT_MULTIPOLYGON_ZM_TAGGED_TEXT",  "error",         "program",     
  "wkt_text",      "point",         "point_z",       "point_m",     
  "point_zm",      "multipoint",    "multipoint_z",  "multipoint_m",
  "multipoint_zm",  "linestring",    "linestring_z",  "linestring_m",
  "linestring_zm",  "multilinestring",  "multilinestring_z",  "multilinestring_m",
  "multilinestring_zm",  "polygon",       "polygon_z",     "polygon_m",   
  "polygon_zm",    "multipolygon",  "multipolygon_z",  "multipolygon_m",
  "multipolygon_zm",  "coord",         "point_text",    "point_text_z",
  "point_text_m",  "point_text_zm",  "coord_xy",      "coord_xyz",   
  "coord_xym",     "coord_xyzm",    "coord_xy_repeated",  "coord_xyz_repeated",
  "coord_xym_repeated",  "coord_xyzm_repeated",  "multipoint_text",  "multipoint_text_2",
  "multipoint_text_z",  "multipoint_text_z_2",  "multipoint_text_m",  "multipoint_text_m_2",
  "multipoint_text_zm",  "multipoint_text_zm_2",  "linestring_text",  "linestring_text_z",
  "linestring_text_m",  "linestring_text_zm",  "linestring_text_repeated",  "linestring_text_z_repeated",
  "linestring_text_m_repeated",  "linestring_text_zm_repeated",  "multilinestring_text",  "multilinestring_text_z",
  "multilinestring_text_m",  "multilinestring_text_zm",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= wkt_text",
 /*   1 */ "wkt_text ::= point",
 /*   2 */ "wkt_text ::= point_z",
 /*   3 */ "wkt_text ::= point_m",
 /*   4 */ "wkt_text ::= point_zm",
 /*   5 */ "wkt_text ::= multipoint",
 /*   6 */ "wkt_text ::= multipoint_z",
 /*   7 */ "wkt_text ::= multipoint_m",
 /*   8 */ "wkt_text ::= multipoint_zm",
 /*   9 */ "wkt_text ::= linestring",
 /*  10 */ "wkt_text ::= linestring_z",
 /*  11 */ "wkt_text ::= linestring_m",
 /*  12 */ "wkt_text ::= linestring_zm",
 /*  13 */ "wkt_text ::= multilinestring",
 /*  14 */ "wkt_text ::= multilinestring_z",
 /*  15 */ "wkt_text ::= multilinestring_m",
 /*  16 */ "wkt_text ::= multilinestring_zm",
 /*  17 */ "wkt_text ::= polygon",
 /*  18 */ "wkt_text ::= polygon_z",
 /*  19 */ "wkt_text ::= polygon_m",
 /*  20 */ "wkt_text ::= polygon_zm",
 /*  21 */ "wkt_text ::= multipolygon",
 /*  22 */ "wkt_text ::= multipolygon_z",
 /*  23 */ "wkt_text ::= multipolygon_m",
 /*  24 */ "wkt_text ::= multipolygon_zm",
 /*  25 */ "coord ::= WKT_NUM",
 /*  26 */ "point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET",
 /*  27 */ "point ::= WKT_POINT_TAGGED_TEXT point_text",
 /*  28 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  29 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z",
 /*  30 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  31 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m",
 /*  32 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  33 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm",
 /*  34 */ "coord_xy ::= coord coord",
 /*  35 */ "coord_xyz ::= coord coord coord",
 /*  36 */ "coord_xym ::= coord coord coord",
 /*  37 */ "coord_xyzm ::= coord coord coord coord",
 /*  38 */ "coord_xy_repeated ::=",
 /*  39 */ "coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated",
 /*  40 */ "coord_xyz_repeated ::=",
 /*  41 */ "coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated",
 /*  42 */ "coord_xym_repeated ::=",
 /*  43 */ "coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated",
 /*  44 */ "coord_xyzm_repeated ::=",
 /*  45 */ "coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated",
 /*  46 */ "point_text ::= WKT_LPAREN coord_xy WKT_RPAREN",
 /*  47 */ "point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN",
 /*  48 */ "point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN",
 /*  49 */ "point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN",
 /*  50 */ "multipoint_text ::=",
 /*  51 */ "multipoint_text ::= WKT_COMMA point_text multipoint_text",
 /*  52 */ "multipoint_text_2 ::=",
 /*  53 */ "multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2",
 /*  54 */ "multipoint_text_z ::=",
 /*  55 */ "multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z",
 /*  56 */ "multipoint_text_z_2 ::=",
 /*  57 */ "multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2",
 /*  58 */ "multipoint_text_m ::=",
 /*  59 */ "multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m",
 /*  60 */ "multipoint_text_m_2 ::=",
 /*  61 */ "multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2",
 /*  62 */ "multipoint_text_zm ::=",
 /*  63 */ "multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm",
 /*  64 */ "multipoint_text_zm_2 ::=",
 /*  65 */ "multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2",
 /*  66 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET",
 /*  67 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN",
 /*  68 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN",
 /*  69 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  70 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN",
 /*  71 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN",
 /*  72 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  73 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN",
 /*  74 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN",
 /*  75 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  76 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN",
 /*  77 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN",
 /*  78 */ "linestring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN",
 /*  79 */ "linestring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN",
 /*  80 */ "linestring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN",
 /*  81 */ "linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN",
 /*  82 */ "linestring_text_repeated ::=",
 /*  83 */ "linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated",
 /*  84 */ "linestring_text_z_repeated ::=",
 /*  85 */ "linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated",
 /*  86 */ "linestring_text_m_repeated ::=",
 /*  87 */ "linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated",
 /*  88 */ "linestring_text_zm_repeated ::=",
 /*  89 */ "linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated",
 /*  90 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
 /*  91 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text",
 /*  92 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  93 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z",
 /*  94 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  95 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m",
 /*  96 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  97 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm",
 /*  98 */ "multilinestring_text ::= WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN",
 /*  99 */ "multilinestring_text_z ::= WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN",
 /* 100 */ "multilinestring_text_m ::= WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN",
 /* 101 */ "multilinestring_text_zm ::= WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN",
 /* 102 */ "multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
 /* 103 */ "multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text",
 /* 104 */ "multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 105 */ "multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z",
 /* 106 */ "multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 107 */ "multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m",
 /* 108 */ "multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 109 */ "multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm",
 /* 110 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET",
 /* 111 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 112 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 113 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 114 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET",
 /* 115 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 116 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 117 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_MAX ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_MAX );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_SZ_ACTTAB );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */

    result->parser_error = 1;
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 31, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 57, 1 },
  { 33, 2 },
  { 33, 2 },
  { 34, 2 },
  { 34, 2 },
  { 35, 2 },
  { 35, 2 },
  { 36, 2 },
  { 36, 2 },
  { 62, 2 },
  { 63, 3 },
  { 64, 3 },
  { 65, 4 },
  { 66, 0 },
  { 66, 3 },
  { 67, 0 },
  { 67, 3 },
  { 68, 0 },
  { 68, 3 },
  { 69, 0 },
  { 69, 3 },
  { 58, 3 },
  { 59, 3 },
  { 60, 3 },
  { 61, 3 },
  { 70, 0 },
  { 70, 3 },
  { 71, 0 },
  { 71, 3 },
  { 72, 0 },
  { 72, 3 },
  { 73, 0 },
  { 73, 3 },
  { 74, 0 },
  { 74, 3 },
  { 75, 0 },
  { 75, 3 },
  { 76, 0 },
  { 76, 3 },
  { 77, 0 },
  { 77, 3 },
  { 37, 2 },
  { 37, 5 },
  { 37, 5 },
  { 38, 2 },
  { 38, 5 },
  { 38, 5 },
  { 39, 2 },
  { 39, 5 },
  { 39, 5 },
  { 40, 2 },
  { 40, 5 },
  { 40, 5 },
  { 78, 6 },
  { 79, 6 },
  { 80, 6 },
  { 81, 6 },
  { 82, 0 },
  { 82, 3 },
  { 83, 0 },
  { 83, 3 },
  { 84, 0 },
  { 84, 3 },
  { 85, 0 },
  { 85, 3 },
  { 41, 2 },
  { 41, 2 },
  { 42, 2 },
  { 42, 2 },
  { 43, 2 },
  { 43, 2 },
  { 44, 2 },
  { 44, 2 },
  { 86, 4 },
  { 87, 4 },
  { 88, 4 },
  { 89, 4 },
  { 45, 2 },
  { 45, 2 },
  { 46, 2 },
  { 46, 2 },
  { 47, 2 },
  { 47, 2 },
  { 48, 2 },
  { 48, 2 },
  { 49, 2 },
  { 50, 2 },
  { 51, 2 },
  { 52, 2 },
  { 53, 2 },
  { 54, 2 },
  { 55, 2 },
  { 56, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 25: /* coord ::= WKT_NUM */
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
        break;
      case 26: /* point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}
        break;
      case 27: /* point ::= WKT_POINT_TAGGED_TEXT point_text */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}
        break;
      case 28: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}
        break;
      case 29: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}
        break;
      case 30: /* point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}
        break;
      case 31: /* point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}
        break;
      case 32: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}
        break;
      case 33: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}
        break;
      case 34: /* coord_xy ::= coord coord */
{
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 35: /* coord_xyz ::= coord coord coord */
      case 36: /* coord_xym ::= coord coord coord */ yytestcase(yyruleno==36);
{
    result->data.coords.push_back(yymsp[-2].minor.yy0);
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 37: /* coord_xyzm ::= coord coord coord coord */
{
    result->data.coords.push_back(yymsp[-3].minor.yy0);
    result->data.coords.push_back(yymsp[-2].minor.yy0);
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 66: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET */
      case 67: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN */ yytestcase(yyruleno==67);
      case 68: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN */ yytestcase(yyruleno==68);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}
        break;
      case 69: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 70: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN */ yytestcase(yyruleno==70);
      case 71: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN */ yytestcase(yyruleno==71);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZ;
}
        break;
      case 72: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 73: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN */ yytestcase(yyruleno==73);
      case 74: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN */ yytestcase(yyruleno==74);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTM;
}
        break;
      case 75: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 76: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN */ yytestcase(yyruleno==76);
      case 77: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN */ yytestcase(yyruleno==77);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZM;
}
        break;
      case 90: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
      case 91: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text */ yytestcase(yyruleno==91);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRING;
}
        break;
      case 92: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 93: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z */ yytestcase(yyruleno==93);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZ;
}
        break;
      case 94: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 95: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m */ yytestcase(yyruleno==95);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGM;
}
        break;
      case 96: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 97: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm */ yytestcase(yyruleno==97);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZM;
}
        break;
      case 102: /* multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
      case 103: /* multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text */ yytestcase(yyruleno==103);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRING;
}
        break;
      case 104: /* multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 105: /* multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z */ yytestcase(yyruleno==105);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGZ;
}
        break;
      case 106: /* multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 107: /* multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m */ yytestcase(yyruleno==107);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGM;
}
        break;
      case 108: /* multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 109: /* multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm */ yytestcase(yyruleno==109);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTILINESTRINGZM;
}
        break;
      case 110: /* polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGON;
}
        break;
      case 111: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONZ;
}
        break;
      case 112: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONM;
}
        break;
      case 113: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONZM;
}
        break;
      case 114: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGON;
}
        break;
      case 115: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONZ;
}
        break;
      case 116: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONM;
}
        break;
      case 117: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONZM;
}
        break;
      default:
      /* (0) program ::= wkt_text */ yytestcase(yyruleno==0);
      /* (1) wkt_text ::= point */ yytestcase(yyruleno==1);
      /* (2) wkt_text ::= point_z */ yytestcase(yyruleno==2);
      /* (3) wkt_text ::= point_m */ yytestcase(yyruleno==3);
      /* (4) wkt_text ::= point_zm */ yytestcase(yyruleno==4);
      /* (5) wkt_text ::= multipoint */ yytestcase(yyruleno==5);
      /* (6) wkt_text ::= multipoint_z */ yytestcase(yyruleno==6);
      /* (7) wkt_text ::= multipoint_m */ yytestcase(yyruleno==7);
      /* (8) wkt_text ::= multipoint_zm */ yytestcase(yyruleno==8);
      /* (9) wkt_text ::= linestring */ yytestcase(yyruleno==9);
      /* (10) wkt_text ::= linestring_z */ yytestcase(yyruleno==10);
      /* (11) wkt_text ::= linestring_m */ yytestcase(yyruleno==11);
      /* (12) wkt_text ::= linestring_zm */ yytestcase(yyruleno==12);
      /* (13) wkt_text ::= multilinestring */ yytestcase(yyruleno==13);
      /* (14) wkt_text ::= multilinestring_z */ yytestcase(yyruleno==14);
      /* (15) wkt_text ::= multilinestring_m */ yytestcase(yyruleno==15);
      /* (16) wkt_text ::= multilinestring_zm */ yytestcase(yyruleno==16);
      /* (17) wkt_text ::= polygon */ yytestcase(yyruleno==17);
      /* (18) wkt_text ::= polygon_z */ yytestcase(yyruleno==18);
      /* (19) wkt_text ::= polygon_m */ yytestcase(yyruleno==19);
      /* (20) wkt_text ::= polygon_zm */ yytestcase(yyruleno==20);
      /* (21) wkt_text ::= multipolygon */ yytestcase(yyruleno==21);
      /* (22) wkt_text ::= multipolygon_z */ yytestcase(yyruleno==22);
      /* (23) wkt_text ::= multipolygon_m */ yytestcase(yyruleno==23);
      /* (24) wkt_text ::= multipolygon_zm */ yytestcase(yyruleno==24);
      /* (38) coord_xy_repeated ::= */ yytestcase(yyruleno==38);
      /* (39) coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated */ yytestcase(yyruleno==39);
      /* (40) coord_xyz_repeated ::= */ yytestcase(yyruleno==40);
      /* (41) coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated */ yytestcase(yyruleno==41);
      /* (42) coord_xym_repeated ::= */ yytestcase(yyruleno==42);
      /* (43) coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated */ yytestcase(yyruleno==43);
      /* (44) coord_xyzm_repeated ::= */ yytestcase(yyruleno==44);
      /* (45) coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated */ yytestcase(yyruleno==45);
      /* (46) point_text ::= WKT_LPAREN coord_xy WKT_RPAREN */ yytestcase(yyruleno==46);
      /* (47) point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN */ yytestcase(yyruleno==47);
      /* (48) point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN */ yytestcase(yyruleno==48);
      /* (49) point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN */ yytestcase(yyruleno==49);
      /* (50) multipoint_text ::= */ yytestcase(yyruleno==50);
      /* (51) multipoint_text ::= WKT_COMMA point_text multipoint_text */ yytestcase(yyruleno==51);
      /* (52) multipoint_text_2 ::= */ yytestcase(yyruleno==52);
      /* (53) multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2 */ yytestcase(yyruleno==53);
      /* (54) multipoint_text_z ::= */ yytestcase(yyruleno==54);
      /* (55) multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z */ yytestcase(yyruleno==55);
      /* (56) multipoint_text_z_2 ::= */ yytestcase(yyruleno==56);
      /* (57) multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2 */ yytestcase(yyruleno==57);
      /* (58) multipoint_text_m ::= */ yytestcase(yyruleno==58);
      /* (59) multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m */ yytestcase(yyruleno==59);
      /* (60) multipoint_text_m_2 ::= */ yytestcase(yyruleno==60);
      /* (61) multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2 */ yytestcase(yyruleno==61);
      /* (62) multipoint_text_zm ::= */ yytestcase(yyruleno==62);
      /* (63) multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm */ yytestcase(yyruleno==63);
      /* (64) multipoint_text_zm_2 ::= */ yytestcase(yyruleno==64);
      /* (65) multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2 */ yytestcase(yyruleno==65);
      /* (78) linestring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN */ yytestcase(yyruleno==78);
      /* (79) linestring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN */ yytestcase(yyruleno==79);
      /* (80) linestring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN */ yytestcase(yyruleno==80);
      /* (81) linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN */ yytestcase(yyruleno==81);
      /* (82) linestring_text_repeated ::= */ yytestcase(yyruleno==82);
      /* (83) linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated */ yytestcase(yyruleno==83);
      /* (84) linestring_text_z_repeated ::= */ yytestcase(yyruleno==84);
      /* (85) linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated */ yytestcase(yyruleno==85);
      /* (86) linestring_text_m_repeated ::= */ yytestcase(yyruleno==86);
      /* (87) linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated */ yytestcase(yyruleno==87);
      /* (88) linestring_text_zm_repeated ::= */ yytestcase(yyruleno==88);
      /* (89) linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated */ yytestcase(yyruleno==89);
      /* (98) multilinestring_text ::= WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN */ yytestcase(yyruleno==98);
      /* (99) multilinestring_text_z ::= WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==99);
      /* (100) multilinestring_text_m ::= WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==100);
      /* (101) multilinestring_text_zm ::= WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==101);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)

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
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
