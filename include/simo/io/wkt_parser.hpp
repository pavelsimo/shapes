#pragma once

#include <ciso646>
#include <iostream>
#include <cassert>
#include <simo/geom/types.hpp>
#include <simo/io/wkt_token.hpp>

namespace simo
{
namespace shapes
{

/*!
 * @brief A Well-known text (WKT) markup language parser result data
 * @ingroup wkt
 *
 * @since 0.0.1
 */
struct WktData
{
    /// the dimension type of the geometry
    GeometryType geom_type;

    /// the coordinates as a sequence of numbers
    std::vector<double> coords;

    /// the offsets in the coordinates sequence
    std::vector<std::size_t> offsets;
};

/*!
 * @brief A Well-known text (WKT) markup language parser results
 *
 * @since 0.0.1
 */
struct WktResult
{
    /// whether there is a parser error
    bool parser_error = false;

    /// the parser result data
    WktData data;
};

/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>

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
#    define INTERFACE 1
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
#define YYNOCODE 131
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE double
typedef union
{
    int yyinit;
    ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#    define YYSTACKDEPTH 1048576
#endif
#define ParseARG_SDECL struct WktResult* result;
#define ParseARG_PDECL , struct WktResult* result
#define ParseARG_FETCH struct WktResult* result = yypParser->result
#define ParseARG_STORE yypParser->result = result
#define YYNSTATE 399
#define YYNRULE 202
#define YY_NO_ACTION (YYNSTATE + YYNRULE + 2)
#define YY_ACCEPT_ACTION (YYNSTATE + YYNRULE + 1)
#define YY_ERROR_ACTION (YYNSTATE + YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = {0};

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
#    define yytestcase(X)
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
    /*     0 */ 602,
    173,
    321,
    311,
    301,
    265,
    262,
    240,
    238,
    231,
    /*    10 */ 368,
    367,
    361,
    360,
    359,
    352,
    351,
    345,
    344,
    343,
    /*    20 */ 336,
    335,
    329,
    328,
    327,
    326,
    325,
    319,
    318,
    317,
    /*    30 */ 56,
    125,
    57,
    68,
    63,
    185,
    25,
    85,
    169,
    171,
    /*    40 */ 172,
    170,
    60,
    49,
    69,
    53,
    72,
    70,
    58,
    71,
    /*    50 */ 50,
    61,
    54,
    64,
    62,
    59,
    66,
    55,
    65,
    52,
    /*    60 */ 67,
    51,
    353,
    271,
    337,
    374,
    354,
    278,
    338,
    384,
    /*    70 */ 355,
    280,
    339,
    391,
    356,
    282,
    340,
    393,
    357,
    285,
    /*    80 */ 341,
    395,
    358,
    291,
    342,
    226,
    374,
    337,
    271,
    353,
    /*    90 */ 384,
    338,
    278,
    354,
    391,
    339,
    280,
    355,
    393,
    340,
    /*   100 */ 282,
    356,
    395,
    341,
    285,
    357,
    226,
    342,
    291,
    358,
    /*   110 */ 63,
    57,
    36,
    68,
    206,
    244,
    5,
    170,
    171,
    137,
    /*   120 */ 172,
    53,
    49,
    164,
    69,
    71,
    70,
    77,
    58,
    64,
    /*   130 */ 61,
    223,
    54,
    55,
    59,
    131,
    66,
    125,
    158,
    149,
    /*   140 */ 29,
    316,
    161,
    154,
    80,
    86,
    41,
    133,
    147,
    281,
    /*   150 */ 56,
    120,
    141,
    137,
    9,
    249,
    144,
    125,
    169,
    269,
    /*   160 */ 10,
    215,
    60,
    175,
    11,
    187,
    72,
    241,
    93,
    157,
    /*   170 */ 50,
    75,
    122,
    261,
    62,
    306,
    131,
    376,
    12,
    131,
    /*   180 */ 37,
    76,
    112,
    94,
    313,
    137,
    210,
    237,
    131,
    124,
    /*   190 */ 189,
    253,
    27,
    78,
    131,
    190,
    83,
    303,
    288,
    309,
    /*   200 */ 120,
    90,
    130,
    40,
    293,
    81,
    41,
    309,
    137,
    146,
    /*   210 */ 349,
    309,
    131,
    346,
    40,
    1,
    177,
    309,
    37,
    176,
    /*   220 */ 323,
    258,
    120,
    120,
    23,
    118,
    6,
    174,
    82,
    297,
    /*   230 */ 131,
    394,
    137,
    230,
    23,
    33,
    38,
    91,
    131,
    235,
    /*   240 */ 140,
    131,
    370,
    3,
    120,
    209,
    386,
    104,
    156,
    92,
    /*   250 */ 137,
    103,
    120,
    88,
    379,
    120,
    30,
    198,
    167,
    96,
    /*   260 */ 200,
    125,
    125,
    202,
    120,
    137,
    228,
    155,
    205,
    199,
    /*   270 */ 125,
    34,
    13,
    192,
    137,
    87,
    79,
    125,
    137,
    191,
    /*   280 */ 137,
    222,
    214,
    204,
    233,
    125,
    213,
    245,
    166,
    168,
    /*   290 */ 120,
    203,
    7,
    365,
    125,
    145,
    388,
    131,
    4,
    397,
    /*   300 */ 188,
    46,
    273,
    125,
    208,
    333,
    120,
    162,
    201,
    84,
    /*   310 */ 114,
    186,
    21,
    256,
    100,
    383,
    27,
    97,
    98,
    310,
    /*   320 */ 46,
    99,
    109,
    194,
    330,
    34,
    106,
    381,
    110,
    95,
    /*   330 */ 146,
    38,
    105,
    102,
    221,
    197,
    107,
    116,
    195,
    162,
    /*   340 */ 121,
    372,
    108,
    309,
    373,
    111,
    83,
    196,
    308,
    331,
    /*   350 */ 2,
    126,
    299,
    128,
    132,
    168,
    295,
    135,
    178,
    48,
    /*   360 */ 138,
    139,
    101,
    284,
    15,
    113,
    41,
    115,
    142,
    117,
    /*   370 */ 320,
    119,
    220,
    219,
    123,
    127,
    300,
    129,
    218,
    290,
    /*   380 */ 134,
    217,
    143,
    216,
    24,
    8,
    136,
    279,
    152,
    179,
    /*   390 */ 150,
    151,
    276,
    37,
    180,
    225,
    242,
    19,
    270,
    42,
    /*   400 */ 268,
    148,
    159,
    211,
    212,
    224,
    181,
    264,
    23,
    160,
    /*   410 */ 182,
    259,
    74,
    165,
    73,
    183,
    40,
    193,
    153,
    184,
    /*   420 */ 399,
    390,
    307,
    298,
    289,
    277,
    275,
    267,
    263,
    315,
    /*   430 */ 257,
    255,
    247,
    243,
    89,
    28,
    239,
    250,
    35,
    227,
    /*   440 */ 39,
    229,
    22,
    396,
    382,
    389,
    380,
    371,
    375,
    45,
    /*   450 */ 385,
    44,
    398,
    43,
    234,
    305,
    283,
    232,
    32,
    31,
    /*   460 */ 26,
    274,
    377,
    246,
    366,
    18,
    252,
    16,
    14,
    254,
    /*   470 */ 236,
    334,
    287,
    266,
    47,
    272,
    20,
    286,
    347,
    314,
    /*   480 */ 294,
    17,
    304,
    387,
    292,
    302,
    312,
    322,
    324,
    392,
    /*   490 */ 378,
    332,
    369,
    350,
    348,
    364,
    251,
    363,
    260,
    603,
    /*   500 */ 362,
    163,
    207,
    603,
    603,
    603,
    603,
    603,
    296,
    248,
};
static const YYCODETYPE yy_lookahead[] = {
    /*     0 */ 35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    /*    10 */ 45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    /*    20 */ 55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    /*    30 */ 2,
    65,
    4,
    5,
    6,
    85,
    7,
    71,
    10,
    11,
    /*    40 */ 12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    /*    50 */ 22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    /*    60 */ 32,
    33,
    38,
    40,
    37,
    39,
    42,
    44,
    41,
    43,
    /*    70 */ 46,
    48,
    45,
    47,
    50,
    52,
    49,
    51,
    54,
    56,
    /*    80 */ 53,
    55,
    58,
    60,
    57,
    59,
    39,
    37,
    40,
    38,
    /*    90 */ 43,
    41,
    44,
    42,
    47,
    45,
    48,
    46,
    51,
    49,
    /*   100 */ 52,
    50,
    55,
    53,
    56,
    54,
    59,
    57,
    60,
    58,
    /*   110 */ 6,
    4,
    7,
    5,
    75,
    85,
    7,
    13,
    11,
    65,
    /*   120 */ 12,
    17,
    15,
    69,
    16,
    21,
    19,
    73,
    20,
    25,
    /*   130 */ 23,
    121,
    24,
    29,
    27,
    65,
    28,
    65,
    68,
    67,
    /*   140 */ 7,
    3,
    72,
    71,
    120,
    118,
    8,
    124,
    122,
    3,
    /*   150 */ 2,
    65,
    66,
    65,
    8,
    3,
    70,
    65,
    10,
    3,
    /*   160 */ 8,
    73,
    14,
    71,
    8,
    74,
    18,
    74,
    118,
    122,
    /*   170 */ 22,
    120,
    124,
    3,
    26,
    3,
    65,
    3,
    8,
    65,
    /*   180 */ 8,
    99,
    8,
    72,
    3,
    65,
    72,
    3,
    65,
    8,
    /*   190 */ 75,
    3,
    8,
    73,
    65,
    72,
    8,
    3,
    3,
    1,
    /*   200 */ 65,
    72,
    8,
    8,
    3,
    70,
    8,
    1,
    65,
    8,
    /*   210 */ 3,
    1,
    65,
    119,
    8,
    8,
    73,
    1,
    8,
    72,
    /*   220 */ 3,
    3,
    65,
    65,
    8,
    8,
    8,
    70,
    70,
    3,
    /*   230 */ 65,
    3,
    65,
    102,
    8,
    8,
    8,
    72,
    65,
    75,
    /*   240 */ 73,
    65,
    3,
    7,
    65,
    72,
    3,
    8,
    72,
    70,
    /*   250 */ 65,
    8,
    65,
    7,
    3,
    65,
    8,
    70,
    73,
    8,
    /*   260 */ 70,
    65,
    65,
    102,
    65,
    65,
    3,
    71,
    71,
    70,
    /*   270 */ 65,
    8,
    7,
    73,
    65,
    98,
    71,
    65,
    65,
    76,
    /*   280 */ 65,
    119,
    73,
    71,
    3,
    65,
    73,
    3,
    73,
    8,
    /*   290 */ 65,
    71,
    8,
    3,
    65,
    70,
    3,
    65,
    8,
    76,
    /*   300 */ 71,
    8,
    3,
    65,
    72,
    3,
    65,
    8,
    74,
    71,
    /*   310 */ 8,
    70,
    7,
    83,
    7,
    93,
    8,
    86,
    7,
    111,
    /*   320 */ 8,
    86,
    7,
    90,
    113,
    8,
    7,
    90,
    7,
    89,
    /*   330 */ 8,
    8,
    87,
    89,
    113,
    93,
    87,
    7,
    91,
    8,
    /*   340 */ 7,
    91,
    88,
    1,
    92,
    88,
    8,
    92,
    65,
    125,
    /*   350 */ 7,
    65,
    65,
    7,
    65,
    8,
    65,
    7,
    78,
    8,
    /*   360 */ 65,
    65,
    109,
    65,
    7,
    109,
    8,
    108,
    7,
    108,
    /*   370 */ 112,
    107,
    112,
    111,
    107,
    106,
    110,
    106,
    110,
    105,
    /*   380 */ 101,
    105,
    66,
    77,
    7,
    7,
    101,
    78,
    7,
    79,
    /*   390 */ 7,
    67,
    79,
    8,
    80,
    125,
    123,
    8,
    104,
    7,
    /*   400 */ 80,
    100,
    7,
    76,
    104,
    123,
    81,
    81,
    8,
    68,
    /*   410 */ 82,
    82,
    7,
    7,
    69,
    83,
    8,
    77,
    100,
    84,
    /*   420 */ 0,
    77,
    9,
    9,
    9,
    9,
    9,
    9,
    9,
    66,
    /*   430 */ 9,
    9,
    9,
    9,
    98,
    7,
    9,
    103,
    7,
    87,
    /*   440 */ 7,
    9,
    7,
    9,
    89,
    9,
    9,
    9,
    9,
    7,
    /*   450 */ 9,
    7,
    9,
    7,
    106,
    67,
    9,
    9,
    7,
    7,
    /*   460 */ 7,
    108,
    96,
    9,
    127,
    7,
    9,
    7,
    7,
    107,
    /*   470 */ 86,
    117,
    69,
    9,
    7,
    9,
    7,
    9,
    129,
    115,
    /*   480 */ 109,
    7,
    114,
    97,
    9,
    9,
    9,
    9,
    116,
    88,
    /*   490 */ 94,
    9,
    95,
    126,
    9,
    9,
    9,
    9,
    128,
    130,
    /*   500 */ 121,
    99,
    103,
    130,
    130,
    130,
    130,
    130,
    68,
    84,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_MAX 225
static const short yy_shift_ofst[] = {
    /*     0 */ 28,
    148,
    104,
    148,
    107,
    107,
    108,
    104,
    108,
    198,
    /*    10 */ 206,
    210,
    216,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    /*    20 */ 342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    /*    30 */ 342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    /*    40 */ 342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    342,
    263,
    /*    50 */ 281,
    284,
    290,
    293,
    299,
    302,
    138,
    172,
    174,
    181,
    /*    60 */ 184,
    188,
    194,
    195,
    201,
    207,
    217,
    218,
    226,
    228,
    /*    70 */ 239,
    243,
    251,
    406,
    227,
    109,
    405,
    29,
    29,
    105,
    /*    80 */ 109,
    133,
    133,
    227,
    105,
    105,
    236,
    246,
    248,
    246,
    /*    90 */ 265,
    265,
    133,
    236,
    305,
    307,
    308,
    311,
    308,
    311,
    /*   100 */ 312,
    315,
    307,
    312,
    317,
    319,
    317,
    319,
    321,
    322,
    /*   110 */ 323,
    321,
    323,
    315,
    322,
    330,
    331,
    330,
    331,
    333,
    /*   120 */ 342,
    338,
    343,
    333,
    338,
    342,
    342,
    346,
    347,
    346,
    /*   130 */ 347,
    342,
    342,
    343,
    350,
    351,
    350,
    342,
    342,
    342,
    /*   140 */ 357,
    361,
    358,
    361,
    377,
    377,
    351,
    378,
    381,
    383,
    /*   150 */ 385,
    383,
    389,
    381,
    392,
    392,
    265,
    378,
    395,
    400,
    /*   160 */ 395,
    305,
    389,
    405,
    406,
    408,
    357,
    357,
    248,
    146,
    /*   170 */ 152,
    156,
    170,
    420,
    413,
    414,
    415,
    447,
    416,
    417,
    /*   180 */ 418,
    419,
    421,
    422,
    423,
    424,
    428,
    427,
    431,
    432,
    /*   190 */ 433,
    434,
    435,
    436,
    437,
    438,
    439,
    441,
    442,
    444,
    /*   200 */ 446,
    443,
    448,
    451,
    452,
    453,
    454,
    457,
    458,
    460,
    /*   210 */ 461,
    464,
    466,
    467,
    469,
    474,
    468,
    475,
    476,
    477,
    /*   220 */ 478,
    482,
    485,
    486,
    487,
    488,
};
#define YY_REDUCE_USE_DFLT (-51)
#define YY_REDUCE_MAX 168
static const short yy_reduce_ofst[] = {
    /*     0 */ -35,
    50,
    48,
    27,
    24,
    51,
    47,
    23,
    26,
    86,
    /*    10 */ 54,
    72,
    70,
    165,
    176,
    185,
    114,
    167,
    173,
    232,
    /*    20 */ 88,
    111,
    215,
    147,
    225,
    120,
    205,
    241,
    135,
    158,
    /*    30 */ 187,
    197,
    212,
    220,
    229,
    238,
    -34,
    92,
    123,
    129,
    /*    40 */ 143,
    157,
    196,
    179,
    190,
    199,
    200,
    209,
    213,
    352,
    /*    50 */ 348,
    349,
    337,
    355,
    353,
    354,
    363,
    388,
    366,
    364,
    /*    60 */ 384,
    362,
    368,
    403,
    371,
    367,
    372,
    370,
    440,
    401,
    /*    70 */ 397,
    386,
    396,
    425,
    402,
    379,
    399,
    -50,
    30,
    39,
    /*    80 */ 10,
    91,
    93,
    82,
    115,
    164,
    94,
    131,
    177,
    161,
    /*    90 */ 203,
    223,
    234,
    162,
    230,
    222,
    231,
    233,
    235,
    237,
    /*   100 */ 240,
    211,
    242,
    244,
    245,
    247,
    249,
    250,
    252,
    253,
    /*   110 */ 254,
    255,
    257,
    221,
    256,
    258,
    259,
    260,
    261,
    208,
    /*   120 */ 283,
    264,
    224,
    262,
    267,
    286,
    287,
    266,
    269,
    268,
    /*   130 */ 271,
    289,
    291,
    270,
    274,
    279,
    276,
    295,
    296,
    298,
    /*   140 */ 306,
    280,
    316,
    309,
    310,
    313,
    285,
    273,
    294,
    314,
    /*   150 */ 324,
    320,
    301,
    300,
    325,
    326,
    327,
    282,
    328,
    341,
    /*   160 */ 329,
    332,
    318,
    334,
    335,
    345,
    340,
    344,
    336,
};
static const YYACTIONTYPE yy_default[] = {
    /*     0 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    10 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    20 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    30 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    40 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    50 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    60 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*    70 */ 601,
    601,
    601,
    465,
    601,
    571,
    519,
    467,
    467,
    443,
    /*    80 */ 571,
    441,
    441,
    601,
    443,
    443,
    563,
    517,
    601,
    517,
    /*    90 */ 445,
    445,
    441,
    563,
    463,
    491,
    601,
    485,
    601,
    485,
    /*   100 */ 601,
    535,
    491,
    601,
    601,
    487,
    601,
    487,
    489,
    601,
    /*   110 */ 601,
    489,
    601,
    535,
    601,
    533,
    601,
    533,
    601,
    531,
    /*   120 */ 601,
    601,
    587,
    531,
    601,
    601,
    601,
    529,
    601,
    529,
    /*   130 */ 601,
    601,
    601,
    587,
    523,
    601,
    523,
    601,
    601,
    601,
    /*   140 */ 447,
    453,
    601,
    453,
    455,
    455,
    601,
    579,
    521,
    457,
    /*   150 */ 601,
    457,
    601,
    521,
    459,
    459,
    445,
    579,
    461,
    601,
    /*   160 */ 461,
    463,
    601,
    519,
    465,
    601,
    447,
    447,
    601,
    601,
    /*   170 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*   180 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*   190 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*   200 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*   210 */ 601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    601,
    /*   220 */ 601,
    601,
    601,
    601,
    601,
    601,
    578,
    496,
    495,
    482,
    /*   230 */ 518,
    407,
    525,
    537,
    538,
    444,
    494,
    493,
    406,
    481,
    /*   240 */ 405,
    442,
    580,
    480,
    468,
    599,
    514,
    479,
    466,
    478,
    /*   250 */ 520,
    591,
    526,
    539,
    540,
    477,
    464,
    476,
    597,
    462,
    /*   260 */ 598,
    475,
    404,
    474,
    460,
    403,
    515,
    473,
    458,
    472,
    /*   270 */ 522,
    581,
    527,
    541,
    542,
    471,
    456,
    470,
    582,
    454,
    /*   280 */ 583,
    469,
    584,
    452,
    440,
    585,
    516,
    436,
    435,
    451,
    /*   290 */ 524,
    586,
    528,
    543,
    544,
    439,
    434,
    433,
    450,
    438,
    /*   300 */ 530,
    402,
    545,
    549,
    550,
    432,
    431,
    449,
    437,
    428,
    /*   310 */ 532,
    401,
    546,
    551,
    552,
    430,
    429,
    427,
    426,
    425,
    /*   320 */ 534,
    400,
    547,
    553,
    554,
    424,
    423,
    422,
    421,
    420,
    /*   330 */ 536,
    588,
    548,
    555,
    556,
    419,
    418,
    557,
    558,
    559,
    /*   340 */ 560,
    561,
    562,
    417,
    416,
    415,
    564,
    600,
    589,
    593,
    /*   350 */ 594,
    414,
    413,
    565,
    566,
    567,
    568,
    569,
    570,
    412,
    /*   360 */ 411,
    410,
    572,
    592,
    590,
    595,
    596,
    409,
    408,
    508,
    /*   370 */ 507,
    502,
    488,
    490,
    573,
    503,
    509,
    510,
    506,
    505,
    /*   380 */ 501,
    486,
    500,
    492,
    574,
    504,
    511,
    512,
    499,
    484,
    /*   390 */ 448,
    575,
    498,
    576,
    497,
    577,
    483,
    446,
    513,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action) / sizeof(yy_action[0]))

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
static const YYCODETYPE yyFallback[] = {};
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
struct yyStackEntry
{
    YYACTIONTYPE stateno; /* The state-number */
    YYCODETYPE major;     /* The major token value.  This is the code
                         ** number for the token at this stack level */
    YYMINORTYPE minor;    /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser
{
    int yyidx; /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
    int yyidxMax; /* Maximum value of yyidx */
#endif
    int yyerrcnt;  /* Shifts left before out of the error */
    ParseARG_SDECL /* A place to hold %extra_argument */
#if YYSTACKDEPTH <= 0
        int yystksz;       /* Current side of the stack */
    yyStackEntry* yystack; /* The parser's stack */
#else
        yyStackEntry yystack[YYSTACKDEPTH]; /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#    include <stdio.h>
static FILE* yyTraceFILE   = 0;
static char* yyTracePrompt = 0;
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
void ParseTrace(FILE* TraceFILE, char* zTracePrompt)
{
    yyTraceFILE   = TraceFILE;
    yyTracePrompt = zTracePrompt;
    if (yyTraceFILE == 0)
        yyTracePrompt = 0;
    else if (yyTracePrompt == 0)
        yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char* const yyTokenName[] = {
    "$",
    "WKT_NUM",
    "WKT_POINT_TAGGED_TEXT",
    "WKT_EMPTY_SET",
    "WKT_POINT_Z_TAGGED_TEXT",
    "WKT_POINT_M_TAGGED_TEXT",
    "WKT_POINT_ZM_TAGGED_TEXT",
    "WKT_COMMA",
    "WKT_LPAREN",
    "WKT_RPAREN",
    "WKT_MULTIPOINT_TAGGED_TEXT",
    "WKT_MULTIPOINT_Z_TAGGED_TEXT",
    "WKT_MULTIPOINT_M_TAGGED_TEXT",
    "WKT_MULTIPOINT_ZM_TAGGED_TEXT",
    "WKT_LINESTRING_TAGGED_TEXT",
    "WKT_LINESTRING_Z_TAGGED_TEXT",
    "WKT_LINESTRING_M_TAGGED_TEXT",
    "WKT_LINESTRING_ZM_TAGGED_TEXT",
    "WKT_MULTILINESTRING_TAGGED_TEXT",
    "WKT_MULTILINESTRING_Z_TAGGED_TEXT",
    "WKT_MULTILINESTRING_M_TAGGED_TEXT",
    "WKT_MULTILINESTRING_ZM_TAGGED_TEXT",
    "WKT_POLYGON_TAGGED_TEXT",
    "WKT_POLYGON_Z_TAGGED_TEXT",
    "WKT_POLYGON_M_TAGGED_TEXT",
    "WKT_POLYGON_ZM_TAGGED_TEXT",
    "WKT_MULTIPOLYGON_TAGGED_TEXT",
    "WKT_MULTIPOLYGON_Z_TAGGED_TEXT",
    "WKT_MULTIPOLYGON_M_TAGGED_TEXT",
    "WKT_MULTIPOLYGON_ZM_TAGGED_TEXT",
    "WKT_GEOMETRYCOLLECTION_TAGGED_TEXT",
    "WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT",
    "WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT",
    "WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT",
    "error",
    "program",
    "wkt_text",
    "point",
    "point_z",
    "point_m",
    "point_zm",
    "multipoint",
    "multipoint_z",
    "multipoint_m",
    "multipoint_zm",
    "linestring",
    "linestring_z",
    "linestring_m",
    "linestring_zm",
    "multilinestring",
    "multilinestring_z",
    "multilinestring_m",
    "multilinestring_zm",
    "polygon",
    "polygon_z",
    "polygon_m",
    "polygon_zm",
    "multipolygon",
    "multipolygon_z",
    "multipolygon_m",
    "multipolygon_zm",
    "geometrycollection",
    "geometrycollection_z",
    "geometrycollection_m",
    "geometrycollection_zm",
    "coord",
    "point_text",
    "point_text_z",
    "point_text_m",
    "point_text_zm",
    "coord_xy",
    "coord_xyz",
    "coord_xym",
    "coord_xyzm",
    "coord_xy_repeated",
    "coord_xyz_repeated",
    "coord_xym_repeated",
    "coord_xyzm_repeated",
    "multipoint_text",
    "multipoint_text_2",
    "multipoint_text_z",
    "multipoint_text_z_2",
    "multipoint_text_m",
    "multipoint_text_m_2",
    "multipoint_text_zm",
    "multipoint_text_zm_2",
    "linestring_text",
    "linestring_text_z",
    "linestring_text_m",
    "linestring_text_zm",
    "linestring_text_repeated",
    "linestring_text_z_repeated",
    "linestring_text_m_repeated",
    "linestring_text_zm_repeated",
    "multilinestring_text",
    "multilinestring_text_z",
    "multilinestring_text_m",
    "multilinestring_text_zm",
    "ring_text",
    "ring_text_z",
    "ring_text_m",
    "ring_text_zm",
    "ring_text_repeated",
    "ring_text_z_repeated",
    "ring_text_m_repeated",
    "ring_text_zm_repeated",
    "polygon_text",
    "polygon_text_z",
    "polygon_text_m",
    "polygon_text_zm",
    "polygon_text_repeated",
    "polygon_text_z_repeated",
    "polygon_text_m_repeated",
    "polygon_text_zm_repeated",
    "multipolygon_text",
    "multipolygon_text_z",
    "multipolygon_text_m",
    "multipolygon_text_zm",
    "geometry_text",
    "geometry_text_repeated",
    "geometry_text_z",
    "geometry_text_z_repeated",
    "geometry_text_m",
    "geometry_text_m_repeated",
    "geometry_text_zm",
    "geometry_text_zm_repeated",
    "geometrycollection_text",
    "geometrycollection_text_z",
    "geometrycollection_text_m",
    "geometrycollection_text_zm",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char* const yyRuleName[] = {
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
    /*  25 */ "wkt_text ::= geometrycollection",
    /*  26 */ "wkt_text ::= geometrycollection_z",
    /*  27 */ "wkt_text ::= geometrycollection_m",
    /*  28 */ "wkt_text ::= geometrycollection_zm",
    /*  29 */ "coord ::= WKT_NUM",
    /*  30 */ "point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET",
    /*  31 */ "point ::= WKT_POINT_TAGGED_TEXT point_text",
    /*  32 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /*  33 */ "point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z",
    /*  34 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET",
    /*  35 */ "point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m",
    /*  36 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /*  37 */ "point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm",
    /*  38 */ "coord_xy ::= coord coord",
    /*  39 */ "coord_xyz ::= coord coord coord",
    /*  40 */ "coord_xym ::= coord coord coord",
    /*  41 */ "coord_xyzm ::= coord coord coord coord",
    /*  42 */ "coord_xy_repeated ::=",
    /*  43 */ "coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated",
    /*  44 */ "coord_xyz_repeated ::=",
    /*  45 */ "coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated",
    /*  46 */ "coord_xym_repeated ::=",
    /*  47 */ "coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated",
    /*  48 */ "coord_xyzm_repeated ::=",
    /*  49 */ "coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated",
    /*  50 */ "point_text ::= WKT_LPAREN coord_xy WKT_RPAREN",
    /*  51 */ "point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN",
    /*  52 */ "point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN",
    /*  53 */ "point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN",
    /*  54 */ "multipoint_text ::=",
    /*  55 */ "multipoint_text ::= WKT_COMMA point_text multipoint_text",
    /*  56 */ "multipoint_text_2 ::=",
    /*  57 */ "multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2",
    /*  58 */ "multipoint_text_z ::=",
    /*  59 */ "multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z",
    /*  60 */ "multipoint_text_z_2 ::=",
    /*  61 */ "multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2",
    /*  62 */ "multipoint_text_m ::=",
    /*  63 */ "multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m",
    /*  64 */ "multipoint_text_m_2 ::=",
    /*  65 */ "multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2",
    /*  66 */ "multipoint_text_zm ::=",
    /*  67 */ "multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm",
    /*  68 */ "multipoint_text_zm_2 ::=",
    /*  69 */ "multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2",
    /*  70 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET",
    /*  71 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN",
    /*  72 */ "multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN",
    /*  73 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /*  74 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN",
    /*  75 */ "multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN",
    /*  76 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET",
    /*  77 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN",
    /*  78 */ "multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN",
    /*  79 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /*  80 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN",
    /*  81 */ "multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN",
    /*  82 */ "linestring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN",
    /*  83 */ "linestring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN",
    /*  84 */ "linestring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN",
    /*  85 */ "linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN",
    /*  86 */ "linestring_text_repeated ::=",
    /*  87 */ "linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated",
    /*  88 */ "linestring_text_z_repeated ::=",
    /*  89 */ "linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated",
    /*  90 */ "linestring_text_m_repeated ::=",
    /*  91 */ "linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated",
    /*  92 */ "linestring_text_zm_repeated ::=",
    /*  93 */ "linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated",
    /*  94 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
    /*  95 */ "linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text",
    /*  96 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /*  97 */ "linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z",
    /*  98 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
    /*  99 */ "linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m",
    /* 100 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /* 101 */ "linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm",
    /* 102 */ "multilinestring_text ::= WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN",
    /* 103 */ "multilinestring_text_z ::= WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN",
    /* 104 */ "multilinestring_text_m ::= WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN",
    /* 105 */ "multilinestring_text_zm ::= WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN",
    /* 106 */ "multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET",
    /* 107 */ "multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text",
    /* 108 */ "multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /* 109 */ "multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z",
    /* 110 */ "multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET",
    /* 111 */ "multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m",
    /* 112 */ "multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /* 113 */ "multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm",
    /* 114 */ "ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN",
    /* 115 */ "ring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN",
    /* 116 */ "ring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN",
    /* 117 */ "ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN",
    /* 118 */ "ring_text_repeated ::=",
    /* 119 */ "ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated",
    /* 120 */ "ring_text_z_repeated ::=",
    /* 121 */ "ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated",
    /* 122 */ "ring_text_m_repeated ::=",
    /* 123 */ "ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated",
    /* 124 */ "ring_text_zm_repeated ::=",
    /* 125 */ "ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated",
    /* 126 */ "polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN",
    /* 127 */ "polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN",
    /* 128 */ "polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN",
    /* 129 */ "polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN",
    /* 130 */ "polygon_text_repeated ::=",
    /* 131 */ "polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated",
    /* 132 */ "polygon_text_z_repeated ::=",
    /* 133 */ "polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated",
    /* 134 */ "polygon_text_m_repeated ::=",
    /* 135 */ "polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated",
    /* 136 */ "polygon_text_zm_repeated ::=",
    /* 137 */ "polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated",
    /* 138 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET",
    /* 139 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text",
    /* 140 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /* 141 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z",
    /* 142 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
    /* 143 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m",
    /* 144 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /* 145 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm",
    /* 146 */ "multipolygon_text ::= WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN",
    /* 147 */ "multipolygon_text_z ::= WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN",
    /* 148 */ "multipolygon_text_m ::= WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN",
    /* 149 */ "multipolygon_text_zm ::= WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN",
    /* 150 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET",
    /* 151 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text",
    /* 152 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /* 153 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z",
    /* 154 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
    /* 155 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m",
    /* 156 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /* 157 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm",
    /* 158 */ "geometry_text ::= point",
    /* 159 */ "geometry_text ::= multipoint",
    /* 160 */ "geometry_text ::= linestring",
    /* 161 */ "geometry_text ::= multilinestring",
    /* 162 */ "geometry_text ::= polygon",
    /* 163 */ "geometry_text ::= multipolygon",
    /* 164 */ "geometry_text_repeated ::=",
    /* 165 */ "geometry_text_repeated ::= WKT_COMMA geometry_text geometry_text_repeated",
    /* 166 */ "geometry_text_z ::= point_z",
    /* 167 */ "geometry_text_z ::= multipoint_z",
    /* 168 */ "geometry_text_z ::= linestring_z",
    /* 169 */ "geometry_text_z ::= multilinestring_z",
    /* 170 */ "geometry_text_z ::= polygon_z",
    /* 171 */ "geometry_text_z ::= multipolygon_z",
    /* 172 */ "geometry_text_z_repeated ::=",
    /* 173 */ "geometry_text_z_repeated ::= WKT_COMMA geometry_text_z geometry_text_z_repeated",
    /* 174 */ "geometry_text_m ::= point_m",
    /* 175 */ "geometry_text_m ::= multipoint_m",
    /* 176 */ "geometry_text_m ::= linestring_m",
    /* 177 */ "geometry_text_m ::= multilinestring_m",
    /* 178 */ "geometry_text_m ::= polygon_m",
    /* 179 */ "geometry_text_m ::= multipolygon_m",
    /* 180 */ "geometry_text_m_repeated ::=",
    /* 181 */ "geometry_text_m_repeated ::= WKT_COMMA geometry_text_m geometry_text_m_repeated",
    /* 182 */ "geometry_text_zm ::= point_zm",
    /* 183 */ "geometry_text_zm ::= multipoint_zm",
    /* 184 */ "geometry_text_zm ::= linestring_zm",
    /* 185 */ "geometry_text_zm ::= multilinestring_zm",
    /* 186 */ "geometry_text_zm ::= polygon_zm",
    /* 187 */ "geometry_text_zm ::= multipolygon_zm",
    /* 188 */ "geometry_text_zm_repeated ::=",
    /* 189 */ "geometry_text_zm_repeated ::= WKT_COMMA geometry_text_zm geometry_text_zm_repeated",
    /* 190 */ "geometrycollection_text ::= WKT_LPAREN geometry_text geometry_text_repeated WKT_RPAREN",
    /* 191 */ "geometrycollection_text_z ::= WKT_LPAREN geometry_text_z geometry_text_z_repeated WKT_RPAREN",
    /* 192 */ "geometrycollection_text_m ::= WKT_LPAREN geometry_text_m geometry_text_m_repeated WKT_RPAREN",
    /* 193 */ "geometrycollection_text_zm ::= WKT_LPAREN geometry_text_zm geometry_text_zm_repeated WKT_RPAREN",
    /* 194 */ "geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT WKT_EMPTY_SET",
    /* 195 */ "geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT geometrycollection_text",
    /* 196 */ "geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT WKT_EMPTY_SET",
    /* 197 */ "geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT geometrycollection_text_z",
    /* 198 */ "geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT WKT_EMPTY_SET",
    /* 199 */ "geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT geometrycollection_text_m",
    /* 200 */ "geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT WKT_EMPTY_SET",
    /* 201 */ "geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT geometrycollection_text_zm",
};
#endif /* NDEBUG */

#if YYSTACKDEPTH <= 0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser* p)
{
    int newSize;
    yyStackEntry* pNew;

    newSize = p->yystksz * 2 + 100;
    pNew    = realloc(p->yystack, newSize * sizeof(pNew[0]));
    if (pNew)
    {
        p->yystack = pNew;
        p->yystksz = newSize;
#    ifndef NDEBUG
        if (yyTraceFILE)
        {
            fprintf(yyTraceFILE, "%sStack grows to %d entries!\n",
                    yyTracePrompt, p->yystksz);
        }
#    endif
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
void* ParseAlloc(void* (*mallocProc)(size_t))
{
    yyParser* pParser;
    pParser = (yyParser*)(*mallocProc)((size_t)sizeof(yyParser));
    if (pParser)
    {
        pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
        pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH <= 0
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
    yyParser* yypParser,  /* The parser */
    YYCODETYPE yymajor,   /* Type code for object to destroy */
    YYMINORTYPE* yypminor /* The object to be destroyed */
)
{
    ParseARG_FETCH;
    switch (yymajor)
    {
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
        default:
            break; /* If no destructor action specified: do nothing */
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
static int yy_pop_parser_stack(yyParser* pParser)
{
    YYCODETYPE yymajor;
    yyStackEntry* yytos = &pParser->yystack[pParser->yyidx];

    if (pParser->yyidx < 0)
        return 0;
#ifndef NDEBUG
    if (yyTraceFILE && pParser->yyidx >= 0)
    {
        fprintf(yyTraceFILE, "%sPopping %s\n",
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
    void* p,                /* The parser to be deleted */
    void (*freeProc)(void*) /* Function used to reclaim memory */
)
{
    yyParser* pParser = (yyParser*)p;
    if (pParser == 0)
        return;
    while (pParser->yyidx >= 0)
        yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH <= 0
    free(pParser->yystack);
#endif
    (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void* p)
{
    yyParser* pParser = (yyParser*)p;
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
    yyParser* pParser,    /* The parser */
    YYCODETYPE iLookAhead /* The look-ahead token */
)
{
    int i;
    int stateno = pParser->yystack[pParser->yyidx].stateno;

    if (stateno > YY_SHIFT_MAX || (i = yy_shift_ofst[stateno]) == YY_SHIFT_USE_DFLT)
    {
        return yy_default[stateno];
    }
    assert(iLookAhead != YYNOCODE);
    i += iLookAhead;
    if (i < 0 || i >= YY_SZ_ACTTAB || yy_lookahead[i] != iLookAhead)
    {
        if (iLookAhead > 0)
        {
#ifdef YYFALLBACK
            YYCODETYPE iFallback; /* Fallback token */
            if (iLookAhead < sizeof(yyFallback) / sizeof(yyFallback[0]) && (iFallback = yyFallback[iLookAhead]) != 0)
            {
#    ifndef NDEBUG
                if (yyTraceFILE)
                {
                    fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
                            yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
                }
#    endif
                return yy_find_shift_action(pParser, iFallback);
            }
#endif
#ifdef YYWILDCARD
            {
                int j = i - iLookAhead + YYWILDCARD;
                if (j >= 0 && j < YY_SZ_ACTTAB && yy_lookahead[j] == YYWILDCARD)
                {
#    ifndef NDEBUG
                    if (yyTraceFILE)
                    {
                        fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
                                yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
                    }
#    endif /* NDEBUG */
                    return yy_action[j];
                }
            }
#endif /* YYWILDCARD */
        }
        return yy_default[stateno];
    }
    else
    {
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
    int stateno,          /* Current state number */
    YYCODETYPE iLookAhead /* The look-ahead token */
)
{
    int i;
#ifdef YYERRORSYMBOL
    if (stateno > YY_REDUCE_MAX)
    {
        return yy_default[stateno];
    }
#else
    assert(stateno <= YY_REDUCE_MAX);
#endif
    i = yy_reduce_ofst[stateno];
    assert(i != YY_REDUCE_USE_DFLT);
    assert(iLookAhead != YYNOCODE);
    i += iLookAhead;
#ifdef YYERRORSYMBOL
    if (i < 0 || i >= YY_SZ_ACTTAB || yy_lookahead[i] != iLookAhead)
    {
        return yy_default[stateno];
    }
#else
    assert(i >= 0 && i < YY_SZ_ACTTAB);
    assert(yy_lookahead[i] == iLookAhead);
#endif
    return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser* yypParser, YYMINORTYPE* yypMinor)
{
    ParseARG_FETCH;
    yypParser->yyidx--;
#ifndef NDEBUG
    if (yyTraceFILE)
    {
        fprintf(yyTraceFILE, "%sStack Overflow!\n", yyTracePrompt);
    }
#endif
    while (yypParser->yyidx >= 0)
        yy_pop_parser_stack(yypParser);
    /* Here code is inserted which will execute if the parser
   ** stack every overflows */

    result->parser_error = true;
    ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
    yyParser* yypParser,  /* The parser to be shifted */
    int yyNewState,       /* The new state to shift in */
    int yyMajor,          /* The major token to shift in */
    YYMINORTYPE* yypMinor /* Pointer to the minor token to shift in */
)
{
    yyStackEntry* yytos;
    yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
    if (yypParser->yyidx > yypParser->yyidxMax)
    {
        yypParser->yyidxMax = yypParser->yyidx;
    }
#endif
#if YYSTACKDEPTH > 0
    if (yypParser->yyidx >= YYSTACKDEPTH)
    {
        yyStackOverflow(yypParser, yypMinor);
        return;
    }
#else
    if (yypParser->yyidx >= yypParser->yystksz)
    {
        yyGrowStack(yypParser);
        if (yypParser->yyidx >= yypParser->yystksz)
        {
            yyStackOverflow(yypParser, yypMinor);
            return;
        }
    }
#endif
    yytos          = &yypParser->yystack[yypParser->yyidx];
    yytos->stateno = (YYACTIONTYPE)yyNewState;
    yytos->major   = (YYCODETYPE)yyMajor;
    yytos->minor   = *yypMinor;
#ifndef NDEBUG
    if (yyTraceFILE && yypParser->yyidx > 0)
    {
        int i;
        fprintf(yyTraceFILE, "%sShift %d\n", yyTracePrompt, yyNewState);
        fprintf(yyTraceFILE, "%sStack:", yyTracePrompt);
        for (i = 1; i <= yypParser->yyidx; i++)
            fprintf(yyTraceFILE, " %s", yyTokenName[yypParser->yystack[i].major]);
        fprintf(yyTraceFILE, "\n");
    }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct
{
    YYCODETYPE lhs;     /* Symbol on the left-hand side of the rule */
    unsigned char nrhs; /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
    {35, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {36, 1},
    {65, 1},
    {37, 2},
    {37, 2},
    {38, 2},
    {38, 2},
    {39, 2},
    {39, 2},
    {40, 2},
    {40, 2},
    {70, 2},
    {71, 3},
    {72, 3},
    {73, 4},
    {74, 0},
    {74, 3},
    {75, 0},
    {75, 3},
    {76, 0},
    {76, 3},
    {77, 0},
    {77, 3},
    {66, 3},
    {67, 3},
    {68, 3},
    {69, 3},
    {78, 0},
    {78, 3},
    {79, 0},
    {79, 3},
    {80, 0},
    {80, 3},
    {81, 0},
    {81, 3},
    {82, 0},
    {82, 3},
    {83, 0},
    {83, 3},
    {84, 0},
    {84, 3},
    {85, 0},
    {85, 3},
    {41, 2},
    {41, 5},
    {41, 5},
    {42, 2},
    {42, 5},
    {42, 5},
    {43, 2},
    {43, 5},
    {43, 5},
    {44, 2},
    {44, 5},
    {44, 5},
    {86, 6},
    {87, 6},
    {88, 6},
    {89, 6},
    {90, 0},
    {90, 3},
    {91, 0},
    {91, 3},
    {92, 0},
    {92, 3},
    {93, 0},
    {93, 3},
    {45, 2},
    {45, 2},
    {46, 2},
    {46, 2},
    {47, 2},
    {47, 2},
    {48, 2},
    {48, 2},
    {94, 4},
    {95, 4},
    {96, 4},
    {97, 4},
    {49, 2},
    {49, 2},
    {50, 2},
    {50, 2},
    {51, 2},
    {51, 2},
    {52, 2},
    {52, 2},
    {98, 10},
    {99, 10},
    {100, 10},
    {101, 10},
    {102, 0},
    {102, 3},
    {103, 0},
    {103, 3},
    {104, 0},
    {104, 3},
    {105, 0},
    {105, 3},
    {106, 4},
    {107, 4},
    {108, 4},
    {109, 4},
    {110, 0},
    {110, 3},
    {111, 0},
    {111, 3},
    {112, 0},
    {112, 3},
    {113, 0},
    {113, 3},
    {53, 2},
    {53, 2},
    {54, 2},
    {54, 2},
    {55, 2},
    {55, 2},
    {56, 2},
    {56, 2},
    {114, 4},
    {115, 4},
    {116, 4},
    {117, 4},
    {57, 2},
    {57, 2},
    {58, 2},
    {58, 2},
    {59, 2},
    {59, 2},
    {60, 2},
    {60, 2},
    {118, 1},
    {118, 1},
    {118, 1},
    {118, 1},
    {118, 1},
    {118, 1},
    {119, 0},
    {119, 3},
    {120, 1},
    {120, 1},
    {120, 1},
    {120, 1},
    {120, 1},
    {120, 1},
    {121, 0},
    {121, 3},
    {122, 1},
    {122, 1},
    {122, 1},
    {122, 1},
    {122, 1},
    {122, 1},
    {123, 0},
    {123, 3},
    {124, 1},
    {124, 1},
    {124, 1},
    {124, 1},
    {124, 1},
    {124, 1},
    {125, 0},
    {125, 3},
    {126, 4},
    {127, 4},
    {128, 4},
    {129, 4},
    {61, 2},
    {61, 2},
    {62, 2},
    {62, 2},
    {63, 2},
    {63, 2},
    {64, 2},
    {64, 2},
};

static void yy_accept(yyParser*); /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
    yyParser* yypParser, /* The parser */
    int yyruleno         /* Number of the rule by which to reduce */
)
{
    int yygoto;              /* The next state */
    int yyact;               /* The next action */
    YYMINORTYPE yygotominor; /* The LHS of the rule reduced */
    yyStackEntry* yymsp;     /* The top of the parser's stack */
    int yysize;              /* Amount to pop the stack */
    ParseARG_FETCH;
    yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
    if (yyTraceFILE && yyruleno >= 0 && yyruleno < (int)(sizeof(yyRuleName) / sizeof(yyRuleName[0])))
    {
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

    switch (yyruleno)
    {
            /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
        case 29: /* coord ::= WKT_NUM */
        {
            yygotominor.yy0 = yymsp[0].minor.yy0;
        }
        break;
        case 30: /* point ::= WKT_POINT_TAGGED_TEXT WKT_EMPTY_SET */
        {
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.geom_type = GeometryType::POINT;
        }
        break;
        case 31: /* point ::= WKT_POINT_TAGGED_TEXT point_text */
        {
            result->data.geom_type = GeometryType::POINT;
        }
        break;
        case 32: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
        {
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.geom_type = GeometryType::POINTZ;
        }
        break;
        case 33: /* point_z ::= WKT_POINT_Z_TAGGED_TEXT point_text_z */
        {
            result->data.geom_type = GeometryType::POINTZ;
        }
        break;
        case 34: /* point_m ::= WKT_POINT_M_TAGGED_TEXT WKT_EMPTY_SET */
        {
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.geom_type = GeometryType::POINTM;
        }
        break;
        case 35: /* point_m ::= WKT_POINT_M_TAGGED_TEXT point_text_m */
        {
            result->data.geom_type = GeometryType::POINTM;
        }
        break;
        case 36: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        {
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.coords.push_back(0);
            result->data.geom_type = GeometryType::POINTZM;
        }
        break;
        case 37: /* point_zm ::= WKT_POINT_ZM_TAGGED_TEXT point_text_zm */
        {
            result->data.geom_type = GeometryType::POINTZM;
        }
        break;
        case 38: /* coord_xy ::= coord coord */
        {
            result->data.coords.push_back(yymsp[-1].minor.yy0);
            result->data.coords.push_back(yymsp[0].minor.yy0);
        }
        break;
        case 39: /* coord_xyz ::= coord coord coord */
        case 40: /* coord_xym ::= coord coord coord */
            yytestcase(yyruleno == 40);
            {
                result->data.coords.push_back(yymsp[-2].minor.yy0);
                result->data.coords.push_back(yymsp[-1].minor.yy0);
                result->data.coords.push_back(yymsp[0].minor.yy0);
            }
            break;
        case 41: /* coord_xyzm ::= coord coord coord coord */
        {
            result->data.coords.push_back(yymsp[-3].minor.yy0);
            result->data.coords.push_back(yymsp[-2].minor.yy0);
            result->data.coords.push_back(yymsp[-1].minor.yy0);
            result->data.coords.push_back(yymsp[0].minor.yy0);
        }
        break;
        case 70: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_EMPTY_SET */
        case 71: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN point_text multipoint_text WKT_RPAREN */
            yytestcase(yyruleno == 71);
        case 72: /* multipoint ::= WKT_MULTIPOINT_TAGGED_TEXT WKT_LPAREN coord_xy multipoint_text_2 WKT_RPAREN */
            yytestcase(yyruleno == 72);
            {
                result->data.geom_type = GeometryType::MULTIPOINT;
            }
            break;
        case 73: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_EMPTY_SET */
        case 74: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN point_text_z multipoint_text_z WKT_RPAREN */
            yytestcase(yyruleno == 74);
        case 75: /* multipoint_z ::= WKT_MULTIPOINT_Z_TAGGED_TEXT WKT_LPAREN coord_xyz multipoint_text_z_2 WKT_RPAREN */
            yytestcase(yyruleno == 75);
            {
                result->data.geom_type = GeometryType::MULTIPOINTZ;
            }
            break;
        case 76: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_EMPTY_SET */
        case 77: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN point_text_m multipoint_text_m WKT_RPAREN */
            yytestcase(yyruleno == 77);
        case 78: /* multipoint_m ::= WKT_MULTIPOINT_M_TAGGED_TEXT WKT_LPAREN coord_xym multipoint_text_m_2 WKT_RPAREN */
            yytestcase(yyruleno == 78);
            {
                result->data.geom_type = GeometryType::MULTIPOINTM;
            }
            break;
        case 79: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        case 80: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN point_text_zm multipoint_text_zm WKT_RPAREN */
            yytestcase(yyruleno == 80);
        case 81: /* multipoint_zm ::= WKT_MULTIPOINT_ZM_TAGGED_TEXT WKT_LPAREN coord_xyzm multipoint_text_zm_2 WKT_RPAREN */
            yytestcase(yyruleno == 81);
            {
                result->data.geom_type = GeometryType::MULTIPOINTZM;
            }
            break;
        case 82: /* linestring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN */
        case 83: /* linestring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN */
            yytestcase(yyruleno == 83);
        case 84: /* linestring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN */
            yytestcase(yyruleno == 84);
        case 85: /* linestring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN */
            yytestcase(yyruleno == 85);
        case 114: /* ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN */
            yytestcase(yyruleno == 114);
        case 115: /* ring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN */
            yytestcase(yyruleno == 115);
        case 116: /* ring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN */
            yytestcase(yyruleno == 116);
        case 117: /* ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN */
            yytestcase(yyruleno == 117);
            {
                result->data.offsets.push_back(result->data.coords.size());
            }
            break;
        case 94: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
        case 95: /* linestring ::= WKT_LINESTRING_TAGGED_TEXT linestring_text */
            yytestcase(yyruleno == 95);
            {
                result->data.geom_type = GeometryType::LINESTRING;
            }
            break;
        case 96: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
        case 97: /* linestring_z ::= WKT_LINESTRING_Z_TAGGED_TEXT linestring_text_z */
            yytestcase(yyruleno == 97);
            {
                result->data.geom_type = GeometryType::LINESTRINGZ;
            }
            break;
        case 98: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
        case 99: /* linestring_m ::= WKT_LINESTRING_M_TAGGED_TEXT linestring_text_m */
            yytestcase(yyruleno == 99);
            {
                result->data.geom_type = GeometryType::LINESTRINGM;
            }
            break;
        case 100: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        case 101: /* linestring_zm ::= WKT_LINESTRING_ZM_TAGGED_TEXT linestring_text_zm */
            yytestcase(yyruleno == 101);
            {
                result->data.geom_type = GeometryType::LINESTRINGZM;
            }
            break;
        case 106: /* multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT WKT_EMPTY_SET */
        case 107: /* multilinestring ::= WKT_MULTILINESTRING_TAGGED_TEXT multilinestring_text */
            yytestcase(yyruleno == 107);
            {
                result->data.geom_type = GeometryType::MULTILINESTRING;
            }
            break;
        case 108: /* multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT WKT_EMPTY_SET */
        case 109: /* multilinestring_z ::= WKT_MULTILINESTRING_Z_TAGGED_TEXT multilinestring_text_z */
            yytestcase(yyruleno == 109);
            {
                result->data.geom_type = GeometryType::MULTILINESTRINGZ;
            }
            break;
        case 110: /* multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT WKT_EMPTY_SET */
        case 111: /* multilinestring_m ::= WKT_MULTILINESTRING_M_TAGGED_TEXT multilinestring_text_m */
            yytestcase(yyruleno == 111);
            {
                result->data.geom_type = GeometryType::MULTILINESTRINGM;
            }
            break;
        case 112: /* multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        case 113: /* multilinestring_zm ::= WKT_MULTILINESTRING_ZM_TAGGED_TEXT multilinestring_text_zm */
            yytestcase(yyruleno == 113);
            {
                result->data.geom_type = GeometryType::MULTILINESTRINGZM;
            }
            break;
        case 138: /* polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET */
        case 139: /* polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text */
            yytestcase(yyruleno == 139);
            {
                result->data.geom_type = GeometryType::POLYGON;
            }
            break;
        case 140: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
        case 141: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z */
            yytestcase(yyruleno == 141);
            {
                result->data.geom_type = GeometryType::POLYGONZ;
            }
            break;
        case 142: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
        case 143: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m */
            yytestcase(yyruleno == 143);
            {
                result->data.geom_type = GeometryType::POLYGONM;
            }
            break;
        case 144: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        case 145: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm */
            yytestcase(yyruleno == 145);
            {
                result->data.geom_type = GeometryType::POLYGONZM;
            }
            break;
        case 150: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET */
        case 151: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text */
            yytestcase(yyruleno == 151);
            {
                result->data.geom_type = GeometryType::MULTIPOLYGON;
            }
            break;
        case 152: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
        case 153: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z */
            yytestcase(yyruleno == 153);
            {
                result->data.geom_type = GeometryType::MULTIPOLYGONZ;
            }
            break;
        case 154: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
        case 155: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m */
            yytestcase(yyruleno == 155);
            {
                result->data.geom_type = GeometryType::MULTIPOLYGONM;
            }
            break;
        case 156: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        case 157: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm */
            yytestcase(yyruleno == 157);
            {
                result->data.geom_type = GeometryType::MULTIPOLYGONZM;
            }
            break;
        case 194: /* geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT WKT_EMPTY_SET */
        case 195: /* geometrycollection ::= WKT_GEOMETRYCOLLECTION_TAGGED_TEXT geometrycollection_text */
            yytestcase(yyruleno == 195);
            {
                result->data.geom_type = GeometryType::GEOMETRYCOLLECTION;
            }
            break;
        case 196: /* geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT WKT_EMPTY_SET */
        case 197: /* geometrycollection_z ::= WKT_GEOMETRYCOLLECTION_Z_TAGGED_TEXT geometrycollection_text_z */
            yytestcase(yyruleno == 197);
            {
                result->data.geom_type = GeometryType::GEOMETRYCOLLECTIONZ;
            }
            break;
        case 198: /* geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT WKT_EMPTY_SET */
        case 199: /* geometrycollection_m ::= WKT_GEOMETRYCOLLECTION_M_TAGGED_TEXT geometrycollection_text_m */
            yytestcase(yyruleno == 199);
            {
                result->data.geom_type = GeometryType::GEOMETRYCOLLECTIONM;
            }
            break;
        case 200: /* geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT WKT_EMPTY_SET */
        case 201: /* geometrycollection_zm ::= WKT_GEOMETRYCOLLECTION_ZM_TAGGED_TEXT geometrycollection_text_zm */
            yytestcase(yyruleno == 201);
            {
                result->data.geom_type = GeometryType::GEOMETRYCOLLECTIONZM;
            }
            break;
        default:
            /* (0) program ::= wkt_text */ yytestcase(yyruleno == 0);
            /* (1) wkt_text ::= point */ yytestcase(yyruleno == 1);
            /* (2) wkt_text ::= point_z */ yytestcase(yyruleno == 2);
            /* (3) wkt_text ::= point_m */ yytestcase(yyruleno == 3);
            /* (4) wkt_text ::= point_zm */ yytestcase(yyruleno == 4);
            /* (5) wkt_text ::= multipoint */ yytestcase(yyruleno == 5);
            /* (6) wkt_text ::= multipoint_z */ yytestcase(yyruleno == 6);
            /* (7) wkt_text ::= multipoint_m */ yytestcase(yyruleno == 7);
            /* (8) wkt_text ::= multipoint_zm */ yytestcase(yyruleno == 8);
            /* (9) wkt_text ::= linestring */ yytestcase(yyruleno == 9);
            /* (10) wkt_text ::= linestring_z */ yytestcase(yyruleno == 10);
            /* (11) wkt_text ::= linestring_m */ yytestcase(yyruleno == 11);
            /* (12) wkt_text ::= linestring_zm */ yytestcase(yyruleno == 12);
            /* (13) wkt_text ::= multilinestring */ yytestcase(yyruleno == 13);
            /* (14) wkt_text ::= multilinestring_z */ yytestcase(yyruleno == 14);
            /* (15) wkt_text ::= multilinestring_m */ yytestcase(yyruleno == 15);
            /* (16) wkt_text ::= multilinestring_zm */ yytestcase(yyruleno == 16);
            /* (17) wkt_text ::= polygon */ yytestcase(yyruleno == 17);
            /* (18) wkt_text ::= polygon_z */ yytestcase(yyruleno == 18);
            /* (19) wkt_text ::= polygon_m */ yytestcase(yyruleno == 19);
            /* (20) wkt_text ::= polygon_zm */ yytestcase(yyruleno == 20);
            /* (21) wkt_text ::= multipolygon */ yytestcase(yyruleno == 21);
            /* (22) wkt_text ::= multipolygon_z */ yytestcase(yyruleno == 22);
            /* (23) wkt_text ::= multipolygon_m */ yytestcase(yyruleno == 23);
            /* (24) wkt_text ::= multipolygon_zm */ yytestcase(yyruleno == 24);
            /* (25) wkt_text ::= geometrycollection */ yytestcase(yyruleno == 25);
            /* (26) wkt_text ::= geometrycollection_z */ yytestcase(yyruleno == 26);
            /* (27) wkt_text ::= geometrycollection_m */ yytestcase(yyruleno == 27);
            /* (28) wkt_text ::= geometrycollection_zm */ yytestcase(yyruleno == 28);
            /* (42) coord_xy_repeated ::= */ yytestcase(yyruleno == 42);
            /* (43) coord_xy_repeated ::= WKT_COMMA coord_xy coord_xy_repeated */ yytestcase(yyruleno == 43);
            /* (44) coord_xyz_repeated ::= */ yytestcase(yyruleno == 44);
            /* (45) coord_xyz_repeated ::= WKT_COMMA coord_xyz coord_xyz_repeated */ yytestcase(yyruleno == 45);
            /* (46) coord_xym_repeated ::= */ yytestcase(yyruleno == 46);
            /* (47) coord_xym_repeated ::= WKT_COMMA coord_xym coord_xym_repeated */ yytestcase(yyruleno == 47);
            /* (48) coord_xyzm_repeated ::= */ yytestcase(yyruleno == 48);
            /* (49) coord_xyzm_repeated ::= WKT_COMMA coord_xyzm coord_xyzm_repeated */ yytestcase(yyruleno == 49);
            /* (50) point_text ::= WKT_LPAREN coord_xy WKT_RPAREN */ yytestcase(yyruleno == 50);
            /* (51) point_text_z ::= WKT_LPAREN coord_xyz WKT_RPAREN */ yytestcase(yyruleno == 51);
            /* (52) point_text_m ::= WKT_LPAREN coord_xym WKT_RPAREN */ yytestcase(yyruleno == 52);
            /* (53) point_text_zm ::= WKT_LPAREN coord_xyzm WKT_RPAREN */ yytestcase(yyruleno == 53);
            /* (54) multipoint_text ::= */ yytestcase(yyruleno == 54);
            /* (55) multipoint_text ::= WKT_COMMA point_text multipoint_text */ yytestcase(yyruleno == 55);
            /* (56) multipoint_text_2 ::= */ yytestcase(yyruleno == 56);
            /* (57) multipoint_text_2 ::= WKT_COMMA coord_xy multipoint_text_2 */ yytestcase(yyruleno == 57);
            /* (58) multipoint_text_z ::= */ yytestcase(yyruleno == 58);
            /* (59) multipoint_text_z ::= WKT_COMMA point_text_z multipoint_text_z */ yytestcase(yyruleno == 59);
            /* (60) multipoint_text_z_2 ::= */ yytestcase(yyruleno == 60);
            /* (61) multipoint_text_z_2 ::= WKT_COMMA coord_xyz multipoint_text_z_2 */ yytestcase(yyruleno == 61);
            /* (62) multipoint_text_m ::= */ yytestcase(yyruleno == 62);
            /* (63) multipoint_text_m ::= WKT_COMMA point_text_m multipoint_text_m */ yytestcase(yyruleno == 63);
            /* (64) multipoint_text_m_2 ::= */ yytestcase(yyruleno == 64);
            /* (65) multipoint_text_m_2 ::= WKT_COMMA coord_xym multipoint_text_m_2 */ yytestcase(yyruleno == 65);
            /* (66) multipoint_text_zm ::= */ yytestcase(yyruleno == 66);
            /* (67) multipoint_text_zm ::= WKT_COMMA point_text_zm multipoint_text_zm */ yytestcase(yyruleno == 67);
            /* (68) multipoint_text_zm_2 ::= */ yytestcase(yyruleno == 68);
            /* (69) multipoint_text_zm_2 ::= WKT_COMMA coord_xyzm multipoint_text_zm_2 */ yytestcase(yyruleno == 69);
            /* (86) linestring_text_repeated ::= */ yytestcase(yyruleno == 86);
            /* (87) linestring_text_repeated ::= WKT_COMMA linestring_text linestring_text_repeated */ yytestcase(yyruleno == 87);
            /* (88) linestring_text_z_repeated ::= */ yytestcase(yyruleno == 88);
            /* (89) linestring_text_z_repeated ::= WKT_COMMA linestring_text_z linestring_text_z_repeated */ yytestcase(yyruleno == 89);
            /* (90) linestring_text_m_repeated ::= */ yytestcase(yyruleno == 90);
            /* (91) linestring_text_m_repeated ::= WKT_COMMA linestring_text_m linestring_text_m_repeated */ yytestcase(yyruleno == 91);
            /* (92) linestring_text_zm_repeated ::= */ yytestcase(yyruleno == 92);
            /* (93) linestring_text_zm_repeated ::= WKT_COMMA linestring_text_zm linestring_text_zm_repeated */ yytestcase(yyruleno == 93);
            /* (102) multilinestring_text ::= WKT_LPAREN linestring_text linestring_text_repeated WKT_RPAREN */ yytestcase(yyruleno == 102);
            /* (103) multilinestring_text_z ::= WKT_LPAREN linestring_text_z linestring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno == 103);
            /* (104) multilinestring_text_m ::= WKT_LPAREN linestring_text_m linestring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno == 104);
            /* (105) multilinestring_text_zm ::= WKT_LPAREN linestring_text_zm linestring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno == 105);
            /* (118) ring_text_repeated ::= */ yytestcase(yyruleno == 118);
            /* (119) ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated */ yytestcase(yyruleno == 119);
            /* (120) ring_text_z_repeated ::= */ yytestcase(yyruleno == 120);
            /* (121) ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated */ yytestcase(yyruleno == 121);
            /* (122) ring_text_m_repeated ::= */ yytestcase(yyruleno == 122);
            /* (123) ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated */ yytestcase(yyruleno == 123);
            /* (124) ring_text_zm_repeated ::= */ yytestcase(yyruleno == 124);
            /* (125) ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated */ yytestcase(yyruleno == 125);
            /* (126) polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN */ yytestcase(yyruleno == 126);
            /* (127) polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno == 127);
            /* (128) polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno == 128);
            /* (129) polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno == 129);
            /* (130) polygon_text_repeated ::= */ yytestcase(yyruleno == 130);
            /* (131) polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated */ yytestcase(yyruleno == 131);
            /* (132) polygon_text_z_repeated ::= */ yytestcase(yyruleno == 132);
            /* (133) polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated */ yytestcase(yyruleno == 133);
            /* (134) polygon_text_m_repeated ::= */ yytestcase(yyruleno == 134);
            /* (135) polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated */ yytestcase(yyruleno == 135);
            /* (136) polygon_text_zm_repeated ::= */ yytestcase(yyruleno == 136);
            /* (137) polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated */ yytestcase(yyruleno == 137);
            /* (146) multipolygon_text ::= WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN */ yytestcase(yyruleno == 146);
            /* (147) multipolygon_text_z ::= WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno == 147);
            /* (148) multipolygon_text_m ::= WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno == 148);
            /* (149) multipolygon_text_zm ::= WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno == 149);
            /* (158) geometry_text ::= point */ yytestcase(yyruleno == 158);
            /* (159) geometry_text ::= multipoint */ yytestcase(yyruleno == 159);
            /* (160) geometry_text ::= linestring */ yytestcase(yyruleno == 160);
            /* (161) geometry_text ::= multilinestring */ yytestcase(yyruleno == 161);
            /* (162) geometry_text ::= polygon */ yytestcase(yyruleno == 162);
            /* (163) geometry_text ::= multipolygon */ yytestcase(yyruleno == 163);
            /* (164) geometry_text_repeated ::= */ yytestcase(yyruleno == 164);
            /* (165) geometry_text_repeated ::= WKT_COMMA geometry_text geometry_text_repeated */ yytestcase(yyruleno == 165);
            /* (166) geometry_text_z ::= point_z */ yytestcase(yyruleno == 166);
            /* (167) geometry_text_z ::= multipoint_z */ yytestcase(yyruleno == 167);
            /* (168) geometry_text_z ::= linestring_z */ yytestcase(yyruleno == 168);
            /* (169) geometry_text_z ::= multilinestring_z */ yytestcase(yyruleno == 169);
            /* (170) geometry_text_z ::= polygon_z */ yytestcase(yyruleno == 170);
            /* (171) geometry_text_z ::= multipolygon_z */ yytestcase(yyruleno == 171);
            /* (172) geometry_text_z_repeated ::= */ yytestcase(yyruleno == 172);
            /* (173) geometry_text_z_repeated ::= WKT_COMMA geometry_text_z geometry_text_z_repeated */ yytestcase(yyruleno == 173);
            /* (174) geometry_text_m ::= point_m */ yytestcase(yyruleno == 174);
            /* (175) geometry_text_m ::= multipoint_m */ yytestcase(yyruleno == 175);
            /* (176) geometry_text_m ::= linestring_m */ yytestcase(yyruleno == 176);
            /* (177) geometry_text_m ::= multilinestring_m */ yytestcase(yyruleno == 177);
            /* (178) geometry_text_m ::= polygon_m */ yytestcase(yyruleno == 178);
            /* (179) geometry_text_m ::= multipolygon_m */ yytestcase(yyruleno == 179);
            /* (180) geometry_text_m_repeated ::= */ yytestcase(yyruleno == 180);
            /* (181) geometry_text_m_repeated ::= WKT_COMMA geometry_text_m geometry_text_m_repeated */ yytestcase(yyruleno == 181);
            /* (182) geometry_text_zm ::= point_zm */ yytestcase(yyruleno == 182);
            /* (183) geometry_text_zm ::= multipoint_zm */ yytestcase(yyruleno == 183);
            /* (184) geometry_text_zm ::= linestring_zm */ yytestcase(yyruleno == 184);
            /* (185) geometry_text_zm ::= multilinestring_zm */ yytestcase(yyruleno == 185);
            /* (186) geometry_text_zm ::= polygon_zm */ yytestcase(yyruleno == 186);
            /* (187) geometry_text_zm ::= multipolygon_zm */ yytestcase(yyruleno == 187);
            /* (188) geometry_text_zm_repeated ::= */ yytestcase(yyruleno == 188);
            /* (189) geometry_text_zm_repeated ::= WKT_COMMA geometry_text_zm geometry_text_zm_repeated */ yytestcase(yyruleno == 189);
            /* (190) geometrycollection_text ::= WKT_LPAREN geometry_text geometry_text_repeated WKT_RPAREN */ yytestcase(yyruleno == 190);
            /* (191) geometrycollection_text_z ::= WKT_LPAREN geometry_text_z geometry_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno == 191);
            /* (192) geometrycollection_text_m ::= WKT_LPAREN geometry_text_m geometry_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno == 192);
            /* (193) geometrycollection_text_zm ::= WKT_LPAREN geometry_text_zm geometry_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno == 193);
            break;
    };
    yygoto = yyRuleInfo[yyruleno].lhs;
    yysize = yyRuleInfo[yyruleno].nrhs;
    yypParser->yyidx -= yysize;
    yyact = yy_find_reduce_action(yymsp[-yysize].stateno, (YYCODETYPE)yygoto);
    if (yyact < YYNSTATE)
    {
#ifdef NDEBUG
        /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
        if (yysize)
        {
            yypParser->yyidx++;
            yymsp -= yysize - 1;
            yymsp->stateno = (YYACTIONTYPE)yyact;
            yymsp->major   = (YYCODETYPE)yygoto;
            yymsp->minor   = yygotominor;
        }
        else
#endif
        {
            yy_shift(yypParser, yyact, yygoto, &yygotominor);
        }
    }
    else
    {
        assert(yyact == YYNSTATE + YYNRULE + 1);
        yy_accept(yypParser);
    }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
    yyParser* yypParser /* The parser */
)
{
    ParseARG_FETCH;
#    ifndef NDEBUG
    if (yyTraceFILE)
    {
        fprintf(yyTraceFILE, "%sFail!\n", yyTracePrompt);
    }
#    endif
    while (yypParser->yyidx >= 0)
        yy_pop_parser_stack(yypParser);
    /* Here code is inserted which will be executed whenever the
  ** parser fails */
    ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
    yyParser* yypParser, /* The parser */
    int yymajor,         /* The major type of the error token */
    YYMINORTYPE yyminor  /* The minor type of the error token */
)
{
    ParseARG_FETCH;
#define TOKEN (yyminor.yy0)

    result->parser_error = true;
#ifdef SHAPES_VERBOSE
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i)
    {
        int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
        if (a < YYNSTATE + YYNRULE)
        {
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
    yyParser* yypParser /* The parser */
)
{
    ParseARG_FETCH;
#ifndef NDEBUG
    if (yyTraceFILE)
    {
        fprintf(yyTraceFILE, "%sAccept!\n", yyTracePrompt);
    }
#endif
    while (yypParser->yyidx >= 0)
        yy_pop_parser_stack(yypParser);
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
    void* yyp,             /* The parser */
    int yymajor,           /* The major token code number */
    ParseTOKENTYPE yyminor /* The value for the token */
        ParseARG_PDECL     /* Optional %extra_argument parameter */
)
{
    YYMINORTYPE yyminorunion;
    int yyact;        /* The parser action. */
    int yyendofinput; /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
    int yyerrorhit = 0; /* True if yymajor has invoked an error */
#endif
    yyParser* yypParser; /* The parser */

    /* (re)initialize the parser, if necessary */
    yypParser = (yyParser*)yyp;
    if (yypParser->yyidx < 0)
    {
#if YYSTACKDEPTH <= 0
        if (yypParser->yystksz <= 0)
        {
            /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
            yyminorunion = yyzerominor;
            yyStackOverflow(yypParser, &yyminorunion);
            return;
        }
#endif
        yypParser->yyidx              = 0;
        yypParser->yyerrcnt           = -1;
        yypParser->yystack[0].stateno = 0;
        yypParser->yystack[0].major   = 0;
    }
    yyminorunion.yy0 = yyminor;
    yyendofinput     = (yymajor == 0);
    ParseARG_STORE;

#ifndef NDEBUG
    if (yyTraceFILE)
    {
        fprintf(yyTraceFILE, "%sInput %s\n", yyTracePrompt, yyTokenName[yymajor]);
    }
#endif

    do
    {
        yyact = yy_find_shift_action(yypParser, (YYCODETYPE)yymajor);
        if (yyact < YYNSTATE)
        {
            assert(!yyendofinput); /* Impossible to shift the $ token */
            yy_shift(yypParser, yyact, yymajor, &yyminorunion);
            yypParser->yyerrcnt--;
            yymajor = YYNOCODE;
        }
        else if (yyact < YYNSTATE + YYNRULE)
        {
            yy_reduce(yypParser, yyact - YYNSTATE);
        }
        else
        {
            assert(yyact == YY_ERROR_ACTION);
#ifdef YYERRORSYMBOL
            int yymx;
#endif
#ifndef NDEBUG
            if (yyTraceFILE)
            {
                fprintf(yyTraceFILE, "%sSyntax Error!\n", yyTracePrompt);
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
            if (yypParser->yyerrcnt < 0)
            {
                yy_syntax_error(yypParser, yymajor, yyminorunion);
            }
            yymx = yypParser->yystack[yypParser->yyidx].major;
            if (yymx == YYERRORSYMBOL || yyerrorhit)
            {
#    ifndef NDEBUG
                if (yyTraceFILE)
                {
                    fprintf(yyTraceFILE, "%sDiscard input token %s\n",
                            yyTracePrompt, yyTokenName[yymajor]);
                }
#    endif
                yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
                yymajor = YYNOCODE;
            }
            else
            {
                while (
                    yypParser->yyidx >= 0 &&
                    yymx != YYERRORSYMBOL &&
                    (yyact = yy_find_reduce_action(
                         yypParser->yystack[yypParser->yyidx].stateno,
                         YYERRORSYMBOL)) >= YYNSTATE)
                {
                    yy_pop_parser_stack(yypParser);
                }
                if (yypParser->yyidx < 0 || yymajor == 0)
                {
                    yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
                    yy_parse_failed(yypParser);
                    yymajor = YYNOCODE;
                }
                else if (yymx != YYERRORSYMBOL)
                {
                    YYMINORTYPE u2;
                    u2.YYERRSYMDT = 0;
                    yy_shift(yypParser, yyact, YYERRORSYMBOL, &u2);
                }
            }
            yypParser->yyerrcnt = 3;
            yyerrorhit          = 1;
#elif defined(YYNOERRORRECOVERY)
            /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
            yy_syntax_error(yypParser, yymajor, yyminorunion);
            yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
            yymajor = YYNOCODE;

#else /* YYERRORSYMBOL is not defined */
            /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
            if (yypParser->yyerrcnt <= 0)
            {
                yy_syntax_error(yypParser, yymajor, yyminorunion);
            }
            yypParser->yyerrcnt = 3;
            yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
            if (yyendofinput)
            {
                yy_parse_failed(yypParser);
            }
            yymajor = YYNOCODE;
#endif
        }
    } while (yymajor != YYNOCODE && yypParser->yyidx >= 0);
    return;
}

}  // namespace shapes
}  // namespace simo