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
#define YYNOCODE 111
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
#define YYNSTATE 331
#define YYNRULE 154
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
 /*     0 */   486,  155,  281,  278,  276,  274,  267,  241,  238,  236,
 /*    10 */   234,  227,  326,  316,  306,  302,  301,  295,  294,  293,
 /*    20 */   292,  291,  285,  284,  283,  280,   50,  108,   44,   42,
 /*    30 */    55,  321,  329,  128,  149,  150,  152,  151,   52,   57,
 /*    40 */    51,   53,   60,   41,   58,   56,   47,   48,   43,   45,
 /*    50 */    59,   54,   49,   46,  104,  124,  108,  118,  132,  129,
 /*    60 */   114,   64,  137,   87,  279,   69,  313,   62,  118,   30,
 /*    70 */   330,    5,  104,  304,  114,   14,   94,   75,   38,  218,
 /*    80 */   108,   63,  244,  235,   77,  275,  184,    4,    3,  215,
 /*    90 */   224,  275,    6,  114,    1,    2,  253,  275,   27,  108,
 /*   100 */   142,    6,  209,  275,   39,   81,  322,   79,  104,  328,
 /*   110 */    30,   23,  108,   61,   86,  114,  299,  309,  185,  104,
 /*   120 */   308,   92,  170,  118,  180,   98,  300,   17,  104,  104,
 /*   130 */   104,  157,  118,  130,  179,  166,  318,   33,  118,  108,
 /*   140 */   193,   95,  114,  181,  163,  153,  172,   65,  114,  113,
 /*   150 */   164,  108,  108,  219,  104,  190,    6,  168,  138,  178,
 /*   160 */    71,  114,  260,  207,  118,  269,  114,   27,  156,  118,
 /*   170 */   117,  271,  103,  189,  213,  289,   39,  195,  114,  114,
 /*   180 */   106,  108,  118,  254,   66,  188,  148,  183,  121,  104,
 /*   190 */    70,  229,  118,  104,   74,   40,   68,  249,  154,  108,
 /*   200 */    93,  258,  136,  118,  145,   80,  146,   12,  165,  136,
 /*   210 */    67,  194,   76,  206,  211,  167,  204,   38,  199,   72,
 /*   220 */    25,  169,   78,  324,  177,   73,   84,  325,  147,  296,
 /*   230 */     5,   82,  143,   90,  162,   85,  176,   23,   68,   32,
 /*   240 */   315,  175,   89,   88,  173,  311,  198,   97,   91,  305,
 /*   250 */    14,   96,   99,  174,  101,  196,    7,  100,  286,  275,
 /*   260 */   273,  111,  197,  102,  110,  109,   34,  264,   11,  106,
 /*   270 */   107,  287,  191,  266,  115,  257,  112,  192,  123,  125,
 /*   280 */   105,  119,   29,  122,  120,  251,  116,  201,  246,   30,
 /*   290 */   158,  126,  187,  243,   15,  135,  133,  134,  186,  247,
 /*   300 */    39,  117,  131,  127,    9,  159,  239,  141,  160,  233,
 /*   310 */   200,   27,  161,  320,  231,  144,  139,  263,  272,  171,
 /*   320 */   223,  331,  255,  245,  240,  237,  232,  225,  220,  217,
 /*   330 */   259,  212,  205,   16,  140,   24,  203,  226,  323,   21,
 /*   340 */   319,   13,  314,  182,  310,  307,  317,  327,   83,  208,
 /*   350 */    37,   36,   35,  265,  230,  222,  228,   22,   20,   18,
 /*   360 */   277,  297,  242,  270,   10,  248,    8,   26,  290,  210,
 /*   370 */   261,  312,  262,   31,  268,   28,  282,  250,  487,  202,
 /*   380 */    19,  487,  221,  288,  298,  216,  256,  303,  487,  487,
 /*   390 */   214,  252,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    10 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    20 */    51,   52,   53,   54,   55,   56,    2,   57,    4,    5,
 /*    30 */     6,   79,   88,   63,   10,   11,   12,   13,   14,   15,
 /*    40 */    16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
 /*    50 */    26,   27,   28,   29,   57,   58,   57,   57,   59,   62,
 /*    60 */    57,   61,   63,   60,    3,   65,    3,   64,   57,    8,
 /*    70 */     3,    8,   57,    3,   57,    8,   65,   62,    8,    3,
 /*    80 */    57,   64,    3,    3,    8,    1,   63,    8,    8,    3,
 /*    90 */     3,    1,    8,   57,    8,    8,    3,    1,    8,   57,
 /*   100 */    64,    8,    3,    1,    8,   63,    3,    8,   57,    3,
 /*   110 */     8,    8,   57,   62,    8,   57,    3,   86,   63,   57,
 /*   120 */     3,    8,   64,   57,   62,    8,  106,    7,   57,   57,
 /*   130 */    57,   65,   57,   62,   62,   62,    3,    7,   57,   57,
 /*   140 */    65,    8,   57,   66,   75,   63,   65,    7,   57,   64,
 /*   150 */    76,   57,   57,   75,   57,   64,    8,   63,   63,   62,
 /*   160 */     7,   57,    3,  103,   57,    3,   57,    8,   64,   57,
 /*   170 */     8,    3,   65,   64,   76,    3,    8,   65,   57,   57,
 /*   180 */     8,   57,   57,    3,   61,   64,   64,   63,    8,   57,
 /*   190 */    65,    3,   57,   57,   62,    8,    8,    3,   62,   57,
 /*   200 */    65,    3,    8,   57,   90,   63,    8,    7,   77,    8,
 /*   210 */    99,   65,    7,   85,   77,   66,   66,    8,  103,   81,
 /*   220 */     7,   67,   81,   67,   85,   99,    7,   84,    7,  102,
 /*   230 */     8,   80,    7,    7,   74,   80,   84,    8,    8,    7,
 /*   240 */    83,   83,   79,   98,   69,   69,  102,    7,   79,   82,
 /*   250 */     8,   78,   78,   82,    7,   69,    8,   93,   97,    1,
 /*   260 */    57,    7,   97,   93,    7,   57,    7,   57,    8,    8,
 /*   270 */    92,  105,   68,   96,   57,   57,   92,   96,    7,    7,
 /*   280 */   101,   57,    8,   91,   57,   57,  101,  105,   95,    8,
 /*   290 */    70,   58,   95,   70,    7,    7,    7,   59,   67,  104,
 /*   300 */     8,    8,  100,   91,    7,   71,   71,    7,   72,   72,
 /*   310 */   104,    8,   73,   68,   73,   60,  100,    9,    9,   68,
 /*   320 */    74,    0,    9,    9,    9,    9,    9,    9,    9,    9,
 /*   330 */    60,    9,    9,    7,   90,    7,    9,   94,    9,    7,
 /*   340 */    87,    7,    9,   94,    9,    9,    9,    9,   98,    9,
 /*   350 */     7,    7,    7,   59,   98,    9,    9,    7,    7,    7,
 /*   360 */    58,  109,    9,  100,    7,    9,    7,    7,  101,   89,
 /*   370 */   108,   80,    9,    7,    9,    7,    9,   99,  110,   78,
 /*   380 */     7,  110,  107,    9,    9,    9,    9,   81,  110,  110,
 /*   390 */     9,   61,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_MAX 201
static const short yy_shift_ofst[] = {
 /*     0 */    24,   84,   90,   96,  102,  258,  258,  258,  258,  258,
 /*    10 */   258,  258,  258,  258,  258,  258,  258,  258,  258,  258,
 /*    20 */   258,  258,  258,  258,  258,  258,  258,  258,  258,  258,
 /*    30 */   258,  258,  258,  258,  258,  258,  258,  258,  258,  258,
 /*    40 */   258,  133,  159,  162,  168,  172,  180,  188,  194,  198,
 /*    50 */    61,   63,   67,   70,   76,   93,   99,  103,  106,  113,
 /*    60 */   117,  120,  130,  130,  140,  148,  140,  153,  187,  200,
 /*    70 */   200,  201,  205,  153,  120,  120,  209,  201,  205,  209,
 /*    80 */   213,  213,  219,  221,  222,  219,  222,  225,  221,  226,
 /*    90 */   229,  226,  230,  232,  232,  229,  240,  242,  242,  240,
 /*   100 */   247,  248,  247,  232,  258,  254,  248,  257,  258,  258,
 /*   110 */   260,  261,  257,  259,  258,  258,  254,  260,  258,  258,
 /*   120 */   258,  261,  271,  274,  272,  281,  272,  271,  213,  287,
 /*   130 */   287,  288,  289,  292,  289,  293,  274,  297,  297,  288,
 /*   140 */   300,  187,  259,  303,  225,  300,  293,  230,  259,   79,
 /*   150 */    80,   86,   87,  308,  309,  321,  313,  314,  315,  316,
 /*   160 */   317,  318,  319,  320,  322,  323,  326,  327,  328,  329,
 /*   170 */   332,  333,  334,  335,  336,  337,  338,  340,  343,  344,
 /*   180 */   345,  346,  347,  350,  351,  352,  353,  356,  357,  359,
 /*   190 */   360,  363,  365,  366,  368,  373,  367,  374,  375,  376,
 /*   200 */   377,  381,
};
#define YY_REDUCE_USE_DFLT (-57)
#define YY_REDUCE_MAX 148
static const short yy_reduce_ofst[] = {
 /*     0 */   -31,    0,    3,   -1,   -3,   58,   66,   75,   91,   95,
 /*    10 */   109,  121,  125,  135,   73,   71,  132,   15,  -30,  107,
 /*    20 */    55,  122,   23,   94,  142,   42,   85,  104,  112,  124,
 /*    30 */   136,  146,   11,   17,   36,   51,   62,   72,   81,   82,
 /*    40 */    97,  253,  270,  263,  294,  267,  252,  256,  278,  262,
 /*    50 */   302,  291,  301,  306,  275,  330,  280,  -48,  -56,   20,
 /*    60 */    31,   77,   69,   78,   74,  123,   98,   60,  114,  131,
 /*    70 */   137,  111,  128,  115,  149,  150,  138,  126,  139,  141,
 /*    80 */   154,  156,  143,  127,  151,  152,  155,  160,  144,  157,
 /*    90 */   163,  158,  145,  175,  176,  169,  167,  173,  174,  171,
 /*   100 */   161,  164,  165,  186,  203,  166,  170,  177,  208,  210,
 /*   110 */   178,  179,  181,  204,  217,  218,  182,  184,  224,  227,
 /*   120 */   228,  185,  193,  192,  220,  233,  223,  197,  231,  234,
 /*   130 */   235,  195,  236,  238,  237,  202,  212,  239,  241,  206,
 /*   140 */   243,  244,  245,  255,  246,  249,  216,  250,  251,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*    10 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*    20 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*    30 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*    40 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*    50 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*    60 */   485,  369,  391,  391,  393,  485,  393,  459,  485,  395,
 /*    70 */   395,  485,  419,  459,  369,  369,  485,  485,  419,  485,
 /*    80 */   371,  371,  417,  457,  485,  417,  485,  389,  457,  415,
 /*    90 */   485,  415,  485,  375,  375,  485,  413,  485,  485,  413,
 /*   100 */   451,  485,  451,  375,  485,  463,  485,  449,  485,  485,
 /*   110 */   485,  485,  449,  373,  485,  485,  463,  485,  485,  485,
 /*   120 */   485,  485,  447,  485,  381,  485,  381,  447,  371,  383,
 /*   130 */   383,  461,  385,  485,  385,  485,  485,  387,  387,  461,
 /*   140 */   445,  485,  373,  485,  389,  445,  485,  485,  373,  485,
 /*   150 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*   160 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*   170 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*   180 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*   190 */   485,  485,  485,  485,  485,  485,  485,  485,  485,  485,
 /*   200 */   485,  485,  422,  409,  370,  408,  420,  460,  432,  439,
 /*   210 */   440,  396,  407,  394,  476,  406,  474,  405,  479,  392,
 /*   220 */   404,  480,  441,  390,  403,  402,  446,  341,  453,  465,
 /*   230 */   466,  388,  401,  386,  340,  400,  339,  399,  338,  384,
 /*   240 */   398,  337,  442,  382,  397,  380,  448,  462,  454,  467,
 /*   250 */   468,  368,  364,  363,  483,  379,  475,  367,  481,  362,
 /*   260 */   361,  482,  443,  378,  366,  360,  450,  336,  455,  469,
 /*   270 */   470,  359,  377,  365,  335,  356,  334,  358,  333,  357,
 /*   280 */   355,  332,  444,  354,  353,  352,  452,  464,  456,  471,
 /*   290 */   472,  351,  350,  349,  348,  347,  458,  484,  473,  477,
 /*   300 */   478,  346,  345,  428,  427,  414,  344,  429,  433,  434,
 /*   310 */   412,  376,  426,  425,  411,  416,  343,  430,  435,  436,
 /*   320 */   374,  424,  423,  410,  372,  418,  342,  431,  437,  438,
 /*   330 */   421,
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
  "multilinestring_text_m",  "multilinestring_text_zm",  "ring_text",     "ring_text_z", 
  "ring_text_m",   "ring_text_zm",  "ring_text_repeated",  "ring_text_z_repeated",
  "ring_text_m_repeated",  "ring_text_zm_repeated",  "polygon_text",  "polygon_text_z",
  "polygon_text_m",  "polygon_text_zm",  "polygon_text_repeated",  "polygon_text_z_repeated",
  "polygon_text_m_repeated",  "polygon_text_zm_repeated",  "multipolygon_text",  "multipolygon_text_z",
  "multipolygon_text_m",  "multipolygon_text_zm",
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
 /* 110 */ "ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN",
 /* 111 */ "ring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN",
 /* 112 */ "ring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN",
 /* 113 */ "ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN",
 /* 114 */ "ring_text_repeated ::=",
 /* 115 */ "ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated",
 /* 116 */ "ring_text_z_repeated ::=",
 /* 117 */ "ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated",
 /* 118 */ "ring_text_m_repeated ::=",
 /* 119 */ "ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated",
 /* 120 */ "ring_text_zm_repeated ::=",
 /* 121 */ "ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated",
 /* 122 */ "polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN",
 /* 123 */ "polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN",
 /* 124 */ "polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN",
 /* 125 */ "polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN",
 /* 126 */ "polygon_text_repeated ::=",
 /* 127 */ "polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated",
 /* 128 */ "polygon_text_z_repeated ::=",
 /* 129 */ "polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated",
 /* 130 */ "polygon_text_m_repeated ::=",
 /* 131 */ "polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated",
 /* 132 */ "polygon_text_zm_repeated ::=",
 /* 133 */ "polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated",
 /* 134 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET",
 /* 135 */ "polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text",
 /* 136 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 137 */ "polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z",
 /* 138 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 139 */ "polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m",
 /* 140 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 141 */ "polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm",
 /* 142 */ "multipolygon_text ::= WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN",
 /* 143 */ "multipolygon_text_z ::= WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN",
 /* 144 */ "multipolygon_text_m ::= WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN",
 /* 145 */ "multipolygon_text_zm ::= WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN",
 /* 146 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET",
 /* 147 */ "multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text",
 /* 148 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET",
 /* 149 */ "multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z",
 /* 150 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET",
 /* 151 */ "multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m",
 /* 152 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET",
 /* 153 */ "multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm",
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
  { 90, 10 },
  { 91, 10 },
  { 92, 10 },
  { 93, 10 },
  { 94, 0 },
  { 94, 3 },
  { 95, 0 },
  { 95, 3 },
  { 96, 0 },
  { 96, 3 },
  { 97, 0 },
  { 97, 3 },
  { 98, 4 },
  { 99, 4 },
  { 100, 4 },
  { 101, 4 },
  { 102, 0 },
  { 102, 3 },
  { 103, 0 },
  { 103, 3 },
  { 104, 0 },
  { 104, 3 },
  { 105, 0 },
  { 105, 3 },
  { 49, 2 },
  { 49, 2 },
  { 50, 2 },
  { 50, 2 },
  { 51, 2 },
  { 51, 2 },
  { 52, 2 },
  { 52, 2 },
  { 106, 4 },
  { 107, 4 },
  { 108, 4 },
  { 109, 4 },
  { 53, 2 },
  { 53, 2 },
  { 54, 2 },
  { 54, 2 },
  { 55, 2 },
  { 55, 2 },
  { 56, 2 },
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
      case 134: /* polygon ::= WKT_POLYGON_TAGGED_TEXT WKT_EMPTY_SET */
      case 135: /* polygon ::= WKT_POLYGON_TAGGED_TEXT polygon_text */ yytestcase(yyruleno==135);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGON;
}
        break;
      case 136: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 137: /* polygon_z ::= WKT_POLYGON_Z_TAGGED_TEXT polygon_text_z */ yytestcase(yyruleno==137);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONZ;
}
        break;
      case 138: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 139: /* polygon_m ::= WKT_POLYGON_M_TAGGED_TEXT polygon_text_m */ yytestcase(yyruleno==139);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONM;
}
        break;
      case 140: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 141: /* polygon_zm ::= WKT_POLYGON_ZM_TAGGED_TEXT polygon_text_zm */ yytestcase(yyruleno==141);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::POLYGONZM;
}
        break;
      case 146: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT WKT_EMPTY_SET */
      case 147: /* multipolygon ::= WKT_MULTIPOLYGON_TAGGED_TEXT multipolygon_text */ yytestcase(yyruleno==147);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGON;
}
        break;
      case 148: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT WKT_EMPTY_SET */
      case 149: /* multipolygon_z ::= WKT_MULTIPOLYGON_Z_TAGGED_TEXT multipolygon_text_z */ yytestcase(yyruleno==149);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONZ;
}
        break;
      case 150: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT WKT_EMPTY_SET */
      case 151: /* multipolygon_m ::= WKT_MULTIPOLYGON_M_TAGGED_TEXT multipolygon_text_m */ yytestcase(yyruleno==151);
{
    result->data.geom_type = simo::shapes::GeometryDetailedType::MULTIPOLYGONM;
}
        break;
      case 152: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT WKT_EMPTY_SET */
      case 153: /* multipolygon_zm ::= WKT_MULTIPOLYGON_ZM_TAGGED_TEXT multipolygon_text_zm */ yytestcase(yyruleno==153);
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
      /* (110) ring_text ::= WKT_LPAREN coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy WKT_COMMA coord_xy coord_xy_repeated WKT_RPAREN */ yytestcase(yyruleno==110);
      /* (111) ring_text_z ::= WKT_LPAREN coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz WKT_COMMA coord_xyz coord_xyz_repeated WKT_RPAREN */ yytestcase(yyruleno==111);
      /* (112) ring_text_m ::= WKT_LPAREN coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym WKT_COMMA coord_xym coord_xym_repeated WKT_RPAREN */ yytestcase(yyruleno==112);
      /* (113) ring_text_zm ::= WKT_LPAREN coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm WKT_COMMA coord_xyzm coord_xyzm_repeated WKT_RPAREN */ yytestcase(yyruleno==113);
      /* (114) ring_text_repeated ::= */ yytestcase(yyruleno==114);
      /* (115) ring_text_repeated ::= WKT_COMMA ring_text ring_text_repeated */ yytestcase(yyruleno==115);
      /* (116) ring_text_z_repeated ::= */ yytestcase(yyruleno==116);
      /* (117) ring_text_z_repeated ::= WKT_COMMA ring_text_z ring_text_z_repeated */ yytestcase(yyruleno==117);
      /* (118) ring_text_m_repeated ::= */ yytestcase(yyruleno==118);
      /* (119) ring_text_m_repeated ::= WKT_COMMA ring_text_m ring_text_m_repeated */ yytestcase(yyruleno==119);
      /* (120) ring_text_zm_repeated ::= */ yytestcase(yyruleno==120);
      /* (121) ring_text_zm_repeated ::= WKT_COMMA ring_text_zm ring_text_zm_repeated */ yytestcase(yyruleno==121);
      /* (122) polygon_text ::= WKT_LPAREN ring_text ring_text_repeated WKT_RPAREN */ yytestcase(yyruleno==122);
      /* (123) polygon_text_z ::= WKT_LPAREN ring_text_z ring_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==123);
      /* (124) polygon_text_m ::= WKT_LPAREN ring_text_m ring_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==124);
      /* (125) polygon_text_zm ::= WKT_LPAREN ring_text_zm ring_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==125);
      /* (126) polygon_text_repeated ::= */ yytestcase(yyruleno==126);
      /* (127) polygon_text_repeated ::= WKT_COMMA polygon_text polygon_text_repeated */ yytestcase(yyruleno==127);
      /* (128) polygon_text_z_repeated ::= */ yytestcase(yyruleno==128);
      /* (129) polygon_text_z_repeated ::= WKT_COMMA polygon_text_z polygon_text_z_repeated */ yytestcase(yyruleno==129);
      /* (130) polygon_text_m_repeated ::= */ yytestcase(yyruleno==130);
      /* (131) polygon_text_m_repeated ::= WKT_COMMA polygon_text_m polygon_text_m_repeated */ yytestcase(yyruleno==131);
      /* (132) polygon_text_zm_repeated ::= */ yytestcase(yyruleno==132);
      /* (133) polygon_text_zm_repeated ::= WKT_COMMA polygon_text_zm polygon_text_zm_repeated */ yytestcase(yyruleno==133);
      /* (142) multipolygon_text ::= WKT_LPAREN polygon_text polygon_text_repeated WKT_RPAREN */ yytestcase(yyruleno==142);
      /* (143) multipolygon_text_z ::= WKT_LPAREN polygon_text_z polygon_text_z_repeated WKT_RPAREN */ yytestcase(yyruleno==143);
      /* (144) multipolygon_text_m ::= WKT_LPAREN polygon_text_m polygon_text_m_repeated WKT_RPAREN */ yytestcase(yyruleno==144);
      /* (145) multipolygon_text_zm ::= WKT_LPAREN polygon_text_zm polygon_text_zm_repeated WKT_RPAREN */ yytestcase(yyruleno==145);
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
