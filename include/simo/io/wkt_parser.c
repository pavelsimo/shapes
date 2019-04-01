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
#define YYNOCODE 55
#define YYACTIONTYPE unsigned char
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
#define YYNSTATE 147
#define YYNRULE 74
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
 /*     0 */   222,   79,  128,  111,  144,  139,  127,  122,  105,   97,
 /*    10 */    93,   87,  143,  137,   24,   27,   23,   21,   22,  121,
 /*    20 */   103,   56,   67,   62,   65,   61,   66,   63,   64,   68,
 /*    30 */    27,   30,   38,   26,   33,   48,   41,   29,   36,   51,
 /*    40 */    43,   27,   30,   26,   46,  126,   26,   55,   54,   29,
 /*    50 */    52,   53,   27,   91,  110,   26,   47,   26,   42,   30,
 /*    60 */    83,   29,   37,   27,   30,  141,   29,   60,   80,   72,
 /*    70 */    30,  102,   59,   58,   92,   16,  109,  104,   69,  132,
 /*    80 */    20,   17,   86,   13,  125,  121,    4,  101,    1,  118,
 /*    90 */   138,   17,  121,    7,    5,  136,   96,  121,   16,    2,
 /*   100 */     9,  115,   98,   13,  121,    3,   18,   75,  100,   13,
 /*   110 */    20,   29,  119,  106,   34,  116,   28,   14,   57,   35,
 /*   120 */    73,   99,   25,   31,   39,   17,   12,   32,  113,   44,
 /*   130 */    16,   11,   20,   49,  223,  223,   10,  223,    8,   40,
 /*   140 */   123,    6,  223,  223,  223,   85,   19,   45,  147,  133,
 /*   150 */   130,   15,   70,  223,  134,  107,   71,  146,  140,   95,
 /*   160 */    81,  145,  223,   50,   76,  108,  117,   90,  131,  120,
 /*   170 */    82,  223,  142,  124,  114,  135,  223,   94,  223,  223,
 /*   180 */    84,  112,  223,  223,   78,  129,  223,  223,  223,  223,
 /*   190 */   223,   74,   89,  223,  223,  223,  223,  223,  223,   77,
 /*   200 */   223,  223,  223,   88,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*    10 */    29,   30,   31,   32,    2,   33,    4,    5,    6,    1,
 /*    20 */    36,   39,   10,   11,   12,   13,   14,   15,   16,   17,
 /*    30 */    33,   33,   35,   33,   34,   37,   39,   33,   38,   41,
 /*    40 */    36,   33,   33,   33,   40,   34,   33,   39,   38,   33,
 /*    50 */    41,   38,   33,    8,   37,   33,   40,   33,   39,   33,
 /*    60 */    38,   33,   38,   33,   33,    8,   33,   41,   40,   39,
 /*    70 */    33,    3,   41,   40,    8,    7,    3,    3,   41,    3,
 /*    80 */     7,    7,    3,    7,    3,    1,    7,   35,    7,    3,
 /*    90 */     3,    7,    1,    7,    7,    3,    3,    1,    7,    7,
 /*   100 */     7,    3,    3,    7,    1,    7,    7,   42,    8,    7,
 /*   110 */     7,   33,   42,   33,    9,   33,   33,    9,   40,   34,
 /*   120 */    43,   33,   33,   33,    9,    7,    9,   33,   33,    9,
 /*   130 */     7,    9,    7,    9,   54,   54,    9,   54,    9,   35,
 /*   140 */    43,    9,   54,   54,   54,   44,    9,   36,    0,    8,
 /*   150 */    44,    9,   45,   54,   45,    8,   46,    8,   46,    8,
 /*   160 */    47,   47,   54,   37,   48,    8,    8,   48,    8,    8,
 /*   170 */    49,   54,    8,    8,    8,    8,   54,   49,   54,   54,
 /*   180 */    50,   50,   54,   54,   51,   51,   54,   54,   54,   54,
 /*   190 */    54,   52,   52,   54,   54,   54,   54,   54,   54,   53,
 /*   200 */    54,   54,   54,   53,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_MAX 85
static const short yy_shift_ofst[] = {
 /*     0 */    12,   84,   91,   96,  103,   18,   18,   18,   18,   18,
 /*    10 */    18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
 /*    20 */    18,   68,   73,   74,   76,   18,   18,   18,   18,   18,
 /*    30 */    18,   18,   18,  105,  102,  105,  108,  108,  115,  118,
 /*    40 */   115,  117,  117,  120,  123,  120,  122,  122,  124,  125,
 /*    50 */   124,  127,  127,  129,  129,  132,  132,  137,  137,  142,
 /*    60 */   142,   79,   81,   86,   87,   92,   93,   98,   99,  166,
 /*    70 */   167,   57,  100,  165,   66,  161,   45,  164,  141,  148,
 /*    80 */   147,  149,  151,  157,  158,  160,
};
#define YY_REDUCE_USE_DFLT (-20)
#define YY_REDUCE_MAX 60
static const short yy_reduce_ofst[] = {
 /*     0 */   -19,   -3,    4,    0,   -2,   78,  -18,    8,   10,   13,
 /*    10 */     9,   16,   19,   22,   24,   26,   28,   30,   31,   33,
 /*    20 */    37,  -16,   17,   52,   11,   80,   82,   83,   88,   89,
 /*    30 */    90,   94,   95,   65,   85,   70,   77,   97,  101,  104,
 /*    40 */   106,  107,  109,  110,  111,  112,  113,  114,  116,  126,
 /*    50 */   119,  121,  128,  130,  131,  133,  134,  139,  140,  146,
 /*    60 */   150,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   221,  221,  221,  221,  221,  221,  221,  221,  221,  221,
 /*    10 */   221,  221,  221,  221,  221,  221,  221,  221,  221,  221,
 /*    20 */   221,  221,  221,  221,  221,  221,  221,  221,  221,  221,
 /*    30 */   221,  221,  221,  177,  221,  177,  179,  179,  181,  221,
 /*    40 */   181,  183,  183,  185,  221,  185,  187,  187,  189,  221,
 /*    50 */   189,  191,  191,  205,  205,  207,  207,  209,  209,  211,
 /*    60 */   211,  221,  221,  221,  221,  221,  221,  221,  221,  221,
 /*    70 */   221,  221,  221,  221,  221,  221,  221,  221,  221,  221,
 /*    80 */   221,  221,  221,  221,  221,  221,  202,  157,  212,  210,
 /*    90 */   190,  203,  218,  156,  192,  204,  213,  155,  219,  170,
 /*   100 */   174,  164,  165,  166,  163,  154,  171,  175,  173,  167,
 /*   110 */   168,  149,  206,  172,  176,  193,  169,  214,  215,  178,
 /*   120 */   194,  160,  153,  180,  195,  196,  162,  152,  148,  208,
 /*   130 */   182,  197,  161,  216,  184,  198,  199,  159,  217,  151,
 /*   140 */   186,  200,  220,  158,  150,  188,  201,
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
  "WKT_POINT_Z_TAGGED_TEXT",  "WKT_POINT_M_TAGGED_TEXT",  "WKT_POINT_ZM_TAGGED_TEXT",  "WKT_LPAREN",  
  "WKT_RPAREN",    "WKT_COMMA",     "WKT_MULTIPOINT_TAGGED_TEXT",  "WKT_MULTIPOINT_Z_TAGGED_TEXT",
  "WKT_MULTIPOINT_M_TAGGED_TEXT",  "WKT_MULTIPOINT_ZM_TAGGED_TEXT",  "WKT_LINESTRING_TAGGED_TEXT",  "WKT_LINESTRING_Z_TAGGED_TEXT",
  "WKT_LINESTRING_M_TAGGED_TEXT",  "WKT_LINESTRING_ZM_TAGGED_TEXT",  "error",         "program",     
  "wkt_text",      "point",         "point_z",       "point_m",     
  "point_zm",      "multipoint",    "multipoint_z",  "multipoint_m",
  "multipoint_zm",  "linestring",    "linestring_z",  "linestring_m",
  "linestring_zm",  "coord",         "point_text",    "point_text_z",
  "point_text_m",  "point_text_zm",  "coord_xy",      "coord_xyz",   
  "coord_xym",     "coord_xyzm",    "multipoint_text",  "multipoint_text_2",
  "multipoint_text_z",  "multipoint_text_z_2",  "multipoint_text_m",  "multipoint_text_m_2",
  "multipoint_text_zm",  "multipoint_text_zm_2",  "linestring_text",  "linestring_text_z",
  "linestring_text_m",  "linestring_text_zm",
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
 /*  13 */ "coord ::= WKT_NUM",
 /*  14 */ "point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET",
 /*  15 */ "point ::= WKT_POINT_TAGGED_TEXT point_text",
 /*  16 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  17 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z",
 /*  18 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  19 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m",
 /*  20 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  21 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm",
 /*  22 */ "coord_xy ::= coord coord",
 /*  23 */ "coord_xyz ::= coord coord coord",
 /*  24 */ "coord_xym ::= coord coord coord",
 /*  25 */ "coord_xyzm ::= coord coord coord coord",
 /*  26 */ "point_text ::= WKT_LPAREN coord_xy WKT_RPAREN",
 /*  27 */ "point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN",
 /*  28 */ "point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN",
 /*  29 */ "point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN",
 /*  30 */ "multipoint_text ::=",
 /*  31 */ "multipoint_text ::= WKT_COMMA point_text multipoint_text",
 /*  32 */ "multipoint_text_2 ::=",
 /*  33 */ "multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2",
 /*  34 */ "multipoint_text_z ::=",
 /*  35 */ "multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z",
 /*  36 */ "multipoint_text_z_2 ::=",
 /*  37 */ "multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2",
 /*  38 */ "multipoint_text_m ::=",
 /*  39 */ "multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m",
 /*  40 */ "multipoint_text_m_2 ::=",
 /*  41 */ "multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2",
 /*  42 */ "multipoint_text_zm ::=",
 /*  43 */ "multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm",
 /*  44 */ "multipoint_text_zm_2 ::=",
 /*  45 */ "multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2",
 /*  46 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET",
 /*  47 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN",
 /*  48 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN",
 /*  49 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  50 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN",
 /*  51 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN",
 /*  52 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  53 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN",
 /*  54 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN",
 /*  55 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  56 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN",
 /*  57 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN",
 /*  58 */ "linestring_text ::=",
 /*  59 */ "linestring_text ::= WKT_COMMA coord_xy linestring_text",
 /*  60 */ "linestring_text_z ::=",
 /*  61 */ "linestring_text_z ::= WKT_COMMA coord_xyz linestring_text_z",
 /*  62 */ "linestring_text_m ::=",
 /*  63 */ "linestring_text_m ::= WKT_COMMA coord_xym linestring_text_m",
 /*  64 */ "linestring_text_zm ::=",
 /*  65 */ "linestring_text_zm ::= WKT_COMMA coord_xyzm linestring_text_zm",
 /*  66 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
 /*  67 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_LPAREN coord_xy linestring_text WKT_RPAREN",
 /*  68 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /*  69 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_LPAREN coord_xyz linestring_text_z WKT_RPAREN",
 /*  70 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
 /*  71 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_LPAREN coord_xym linestring_text_m WKT_RPAREN",
 /*  72 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /*  73 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm linestring_text_zm WKT_RPAREN",
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
  { 19, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 20, 1 },
  { 33, 1 },
  { 21, 2 },
  { 21, 2 },
  { 22, 2 },
  { 22, 2 },
  { 23, 2 },
  { 23, 2 },
  { 24, 2 },
  { 24, 2 },
  { 38, 2 },
  { 39, 3 },
  { 40, 3 },
  { 41, 4 },
  { 34, 3 },
  { 35, 3 },
  { 36, 3 },
  { 37, 3 },
  { 42, 0 },
  { 42, 3 },
  { 43, 0 },
  { 43, 3 },
  { 44, 0 },
  { 44, 3 },
  { 45, 0 },
  { 45, 3 },
  { 46, 0 },
  { 46, 3 },
  { 47, 0 },
  { 47, 3 },
  { 48, 0 },
  { 48, 3 },
  { 49, 0 },
  { 49, 3 },
  { 25, 2 },
  { 25, 5 },
  { 25, 5 },
  { 26, 2 },
  { 26, 5 },
  { 26, 5 },
  { 27, 2 },
  { 27, 5 },
  { 27, 5 },
  { 28, 2 },
  { 28, 5 },
  { 28, 5 },
  { 50, 0 },
  { 50, 3 },
  { 51, 0 },
  { 51, 3 },
  { 52, 0 },
  { 52, 3 },
  { 53, 0 },
  { 53, 3 },
  { 29, 2 },
  { 29, 5 },
  { 30, 2 },
  { 30, 5 },
  { 31, 2 },
  { 31, 5 },
  { 32, 2 },
  { 32, 5 },
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
      case 13: /* coord ::= WKT_NUM */
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
        break;
      case 14: /* point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}
        break;
      case 15: /* point ::= WKT_POINT_TAGGED_TEXT point_text */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINT;
}
        break;
      case 16: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}
        break;
      case 17: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZ;
}
        break;
      case 18: /* point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}
        break;
      case 19: /* point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTM;
}
        break;
      case 20: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
{
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.coords.push_back(0);
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}
        break;
      case 21: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm */
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POINTZM;
}
        break;
      case 22: /* coord_xy ::= coord coord */
{
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 23: /* coord_xyz ::= coord coord coord */
      case 24: /* coord_xym ::= coord coord coord */ yytestcase(yyruleno==24);
{
    result->data.coords.push_back(yymsp[-2].minor.yy0);
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 25: /* coord_xyzm ::= coord coord coord coord */
{
    result->data.coords.push_back(yymsp[-3].minor.yy0);
    result->data.coords.push_back(yymsp[-2].minor.yy0);
    result->data.coords.push_back(yymsp[-1].minor.yy0);
    result->data.coords.push_back(yymsp[0].minor.yy0);
}
        break;
      case 46: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET */
      case 47: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN */ yytestcase(yyruleno==47);
      case 48: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN */ yytestcase(yyruleno==48);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINT;
}
        break;
      case 49: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 50: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN */ yytestcase(yyruleno==50);
      case 51: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN */ yytestcase(yyruleno==51);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZ;
}
        break;
      case 52: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 53: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN */ yytestcase(yyruleno==53);
      case 54: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN */ yytestcase(yyruleno==54);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTM;
}
        break;
      case 55: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 56: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN */ yytestcase(yyruleno==56);
      case 57: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN */ yytestcase(yyruleno==57);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOINTZM;
}
        break;
      case 66: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
      case 67: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_LPAREN coord_xy linestring_text WKT_RPAREN */ yytestcase(yyruleno==67);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRING;
}
        break;
      case 68: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 69: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_LPAREN coord_xyz linestring_text_z WKT_RPAREN */ yytestcase(yyruleno==69);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZ;
}
        break;
      case 70: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 71: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_LPAREN coord_xym linestring_text_m WKT_RPAREN */ yytestcase(yyruleno==71);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGM;
}
        break;
      case 72: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 73: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm linestring_text_zm WKT_RPAREN */ yytestcase(yyruleno==73);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::LINESTRINGZM;
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
      /* (26) point_text ::= WKT_LPAREN coord_xy WKT_RPAREN */ yytestcase(yyruleno==26);
      /* (27) point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN */ yytestcase(yyruleno==27);
      /* (28) point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN */ yytestcase(yyruleno==28);
      /* (29) point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN */ yytestcase(yyruleno==29);
      /* (30) multipoint_text ::= */ yytestcase(yyruleno==30);
      /* (31) multipoint_text ::= WKT_COMMA point_text multipoint_text */ yytestcase(yyruleno==31);
      /* (32) multipoint_text_2 ::= */ yytestcase(yyruleno==32);
      /* (33) multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2 */ yytestcase(yyruleno==33);
      /* (34) multipoint_text_z ::= */ yytestcase(yyruleno==34);
      /* (35) multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z */ yytestcase(yyruleno==35);
      /* (36) multipoint_text_z_2 ::= */ yytestcase(yyruleno==36);
      /* (37) multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2 */ yytestcase(yyruleno==37);
      /* (38) multipoint_text_m ::= */ yytestcase(yyruleno==38);
      /* (39) multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m */ yytestcase(yyruleno==39);
      /* (40) multipoint_text_m_2 ::= */ yytestcase(yyruleno==40);
      /* (41) multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2 */ yytestcase(yyruleno==41);
      /* (42) multipoint_text_zm ::= */ yytestcase(yyruleno==42);
      /* (43) multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm */ yytestcase(yyruleno==43);
      /* (44) multipoint_text_zm_2 ::= */ yytestcase(yyruleno==44);
      /* (45) multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2 */ yytestcase(yyruleno==45);
      /* (58) linestring_text ::= */ yytestcase(yyruleno==58);
      /* (59) linestring_text ::= WKT_COMMA coord_xy linestring_text */ yytestcase(yyruleno==59);
      /* (60) linestring_text_z ::= */ yytestcase(yyruleno==60);
      /* (61) linestring_text_z ::= WKT_COMMA coord_xyz linestring_text_z */ yytestcase(yyruleno==61);
      /* (62) linestring_text_m ::= */ yytestcase(yyruleno==62);
      /* (63) linestring_text_m ::= WKT_COMMA coord_xym linestring_text_m */ yytestcase(yyruleno==63);
      /* (64) linestring_text_zm ::= */ yytestcase(yyruleno==64);
      /* (65) linestring_text_zm ::= WKT_COMMA coord_xyzm linestring_text_zm */ yytestcase(yyruleno==65);
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
