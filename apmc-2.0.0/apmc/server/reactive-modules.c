/* A Bison parser, made from reactive-modules.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	t_CONST	257
# define	t_EQUAL	258
# define	t_SC	259
# define	t_DP	260
# define	t_COMMA	261
# define	t_MODULE	262
# define	t_ENDMODULE	263
# define	t_LBRACKET	264
# define	t_RBRACKET	265
# define	t_RATE	266
# define	t_LPAR	267
# define	t_RPAR	268
# define	t_PROBAND	269
# define	t_NEXT_AFF	270
# define	t_ARROW	271
# define	t_AND	272
# define	t_PROBABILISTIC	273
# define	t_TO	274
# define	t_FORMULA	275
# define	t_INIT	276
# define	t_INTEGER	277
# define	t_FLOAT	278
# define	t_ID	279
# define	t_CEIL	280
# define	t_FLOOR	281
# define	t_MIN	282
# define	t_MAX	283
# define	t_UNTIL	284
# define	t_OR	285
# define	t_NEQ	286
# define	t_LESS	287
# define	t_LEQ	288
# define	t_GREATER	289
# define	t_GEQ	290
# define	t_PLUS	291
# define	t_MINUS	292
# define	t_TIMES	293
# define	t_DIV	294
# define	t_NEXT	295
# define	t_NOT	296
# define	t_TRUE	297
# define	t_FALSE	298

#line 1 "reactive-modules.y"


extern int rm_lineno;

#include "reactive-modules.h"
#include "rm_free.h"
#include <stdlib.h>
#include <string.h>

int rm_lex(void);
int rm_error(char *error);
extern struct pmfile *PMFILE;
struct moduledef *CURRENT_MODULE;


#line 25 "reactive-modules.y"
#ifndef YYSTYPE
typedef union{
  char *string;
  int   integer;
  double fl;

  struct pmentry *pmentry;
  struct constdef *constdef;
  struct moduledef *moduledef;
  struct formuladef *formuladef;
  struct expr *expr;
  struct vardef *vardef;
  struct rule *rule;
  struct action *action;
  struct probaff *probaff;
  struct exprlist *el;
  struct affectations *affectations;
  struct renamelist *renamelist;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		157
#define	YYFLAG		-32768
#define	YYNTBASE	45

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 67)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     5,     6,     8,    10,    12,    14,    16,
      22,    28,    29,    34,    41,    44,    45,    48,    51,    60,
      71,    76,    78,    80,    83,    87,    92,    98,   100,   104,
     107,   111,   115,   117,   119,   121,   123,   125,   128,   131,
     136,   141,   145,   149,   153,   157,   163,   169,   177,   181,
     185,   189,   193,   197,   201,   205,   209,   213,   217,   224,
     231,   235,   237,   239,   243,   247,   253
};
static const short yyrhs[] =
{
      -1,    47,    46,    45,     0,     0,    48,     0,    49,     0,
      50,     0,    66,     0,    19,     0,     3,    25,     4,    62,
       5,     0,    12,    25,     4,    62,     5,     0,     0,     8,
      25,    51,    52,     0,     4,    25,    10,    65,    11,     9,
       0,    53,     9,     0,     0,    54,    53,     0,    55,    53,
       0,    25,     6,    10,    62,    20,    62,    11,     5,     0,
      25,     6,    10,    62,    20,    62,    11,    22,    62,     5,
       0,    57,    62,    17,    56,     0,    58,     0,    60,     0,
      10,    11,     0,    10,    25,    11,     0,    62,     6,    59,
       5,     0,    62,     6,    59,    15,    58,     0,    61,     0,
      61,    18,    59,     0,    59,     5,     0,    13,    61,    14,
       0,    25,    16,    62,     0,    43,     0,    44,     0,    23,
       0,    24,     0,    25,     0,    42,    62,     0,    41,    62,
       0,    26,    13,    62,    14,     0,    27,    13,    62,    14,
       0,    13,    62,    14,     0,    62,    18,    62,     0,    62,
      31,    62,     0,    62,     4,    62,     0,    62,     4,    62,
       7,    63,     0,    62,     4,    62,    20,    62,     0,    62,
       4,    62,    20,    62,     7,    63,     0,    62,    32,    62,
       0,    62,    33,    62,     0,    62,    35,    62,     0,    62,
      34,    62,     0,    62,    36,    62,     0,    62,    37,    62,
       0,    62,    38,    62,     0,    62,    39,    62,     0,    62,
      40,    62,     0,    62,    30,    62,     0,    28,    13,    62,
       7,    62,    14,     0,    29,    13,    62,     7,    62,    14,
       0,    64,     7,    63,     0,    64,     0,    62,     0,    62,
      20,    62,     0,    25,     4,    25,     0,    25,     4,    25,
       7,    65,     0,    21,    25,     4,    62,     5,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    87,    87,   118,   121,   128,   134,   140,   148,   152,
     161,   178,   178,   189,   229,   235,   240,   248,   255,   267,
     281,   292,   299,   307,   312,   318,   326,   336,   341,   348,
     355,   360,   379,   384,   388,   393,   397,   410,   414,   418,
     422,   426,   430,   434,   438,   442,   451,   461,   475,   479,
     483,   487,   491,   495,   499,   503,   507,   511,   515,   519,
     525,   534,   540,   546,   553,   572,   594
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "t_CONST", "t_EQUAL", "t_SC", "t_DP", 
  "t_COMMA", "t_MODULE", "t_ENDMODULE", "t_LBRACKET", "t_RBRACKET", 
  "t_RATE", "t_LPAR", "t_RPAR", "t_PROBAND", "t_NEXT_AFF", "t_ARROW", 
  "t_AND", "t_PROBABILISTIC", "t_TO", "t_FORMULA", "t_INIT", "t_INTEGER", 
  "t_FLOAT", "t_ID", "t_CEIL", "t_FLOOR", "t_MIN", "t_MAX", "t_UNTIL", 
  "t_OR", "t_NEQ", "t_LESS", "t_LEQ", "t_GREATER", "t_GEQ", "t_PLUS", 
  "t_MINUS", "t_TIMES", "t_DIV", "t_NEXT", "t_NOT", "t_TRUE", "t_FALSE", 
  "pmfile", "@1", "pmentry", "pmtype", "constdef", "moduledef", "@2", 
  "moduleinside", "var_or_rules", "vardef", "rule", "action", "rulename", 
  "probpart", "affectation_list", "detpart", "affectation", "expr", 
  "exprlist", "exprrange", "rename", "formdef", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    46,    45,    45,    47,    47,    47,    47,    48,    49,
      49,    51,    50,    52,    52,    53,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      63,    63,    64,    64,    65,    65,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     3,     0,     1,     1,     1,     1,     1,     5,
       5,     0,     4,     6,     2,     0,     2,     2,     8,    10,
       4,     1,     1,     2,     3,     4,     5,     1,     3,     2,
       3,     3,     1,     1,     1,     1,     1,     2,     2,     4,
       4,     3,     3,     3,     3,     5,     5,     7,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     6,
       3,     1,     1,     3,     3,     5,     5
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       3,     0,     0,     0,     8,     0,     1,     4,     5,     6,
       7,     0,    11,     0,     0,     3,     0,    15,     0,     0,
       2,     0,    34,    35,    36,     0,     0,     0,     0,     0,
       0,    32,    33,     0,     0,     0,     0,    12,     0,    15,
      15,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      37,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     0,     0,    14,
      16,    17,     0,    10,    66,    41,     0,     0,     0,     0,
      44,    42,    57,    43,    48,    49,    51,    50,    52,    53,
      54,    55,    56,     0,    24,     0,     0,    39,    40,     0,
       0,     0,     0,     0,     0,     0,     0,    36,    20,    21,
       0,    22,    27,     0,     0,     0,    62,    45,    61,    46,
       0,     0,     0,     0,     0,    29,     0,     0,    58,    59,
       0,     0,     0,    64,    13,     0,    30,    31,     0,     0,
      28,     0,    63,    60,    47,     0,     0,    25,     0,    65,
      18,     0,    26,     0,    19,     0,     0,     0
};

static const short yydefgoto[] =
{
      20,    15,     6,     7,     8,     9,    17,    37,    38,    39,
      40,   108,    41,   109,   110,   111,   112,   116,   117,   118,
     104,    10
};

static const short yypact[] =
{
       7,   -18,    -8,    -1,-32768,    46,-32768,-32768,-32768,-32768,
  -32768,     5,-32768,    78,    81,     7,   499,     2,   499,   499,
  -32768,   499,-32768,-32768,-32768,    76,    94,    98,    99,   499,
     499,-32768,-32768,    63,    88,     9,   122,-32768,   124,    -2,
      -2,   499,    87,   111,   148,   499,   499,   499,   499,-32768,
  -32768,   499,-32768,   499,   499,   499,   499,   499,   499,   499,
     499,   499,   499,   499,   499,   120,-32768,   123,   126,-32768,
  -32768,-32768,   159,-32768,-32768,-32768,   196,   207,   244,   281,
     481,   220,    18,   135,   121,    36,    36,    36,    36,    30,
      30,    91,-32768,   112,-32768,   499,   521,-32768,-32768,   499,
     499,   499,   499,   134,   129,   304,   521,   149,-32768,-32768,
     197,-32768,   146,   327,   364,   375,   412,-32768,   194,    26,
     178,   195,   499,   191,   499,-32768,    -9,    -9,-32768,-32768,
     499,   499,   499,   199,-32768,   423,-32768,   436,    -9,   149,
  -32768,     6,   121,-32768,-32768,   112,    -4,-32768,   499,-32768,
  -32768,   499,-32768,   460,-32768,   208,   209,-32768
};

static const short yypgoto[] =
{
     212,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    38,-32768,
  -32768,-32768,-32768,    59,   -39,-32768,   -34,   -16,   -22,-32768,
      68,-32768
};


#define	YYLAST		565


static const short yytable[] =
{
      33,   150,    42,    43,   138,    44,    34,    11,    35,    16,
       1,   147,    35,    49,    50,     2,   139,    12,   151,     3,
      66,   148,    51,    36,    13,    72,     4,    36,     5,    76,
      77,    78,    79,   132,    67,    80,    53,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    57,
      58,    59,    60,    61,    62,    63,    64,    51,    52,    63,
      64,    14,   123,    61,    62,    63,    64,    70,    71,   105,
     113,    53,    18,   114,   115,    19,   119,   140,   141,    45,
      44,    51,    73,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,   123,    53,   135,    46,   137,   143,
     144,    47,    48,    65,   142,    51,    74,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    68,    53,
      93,    64,   113,    69,    94,   153,    95,   103,   120,    51,
     121,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    51,    53,    57,    58,    59,    60,    61,    62,
      63,    64,    75,    51,   126,   124,    53,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    96,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      51,   131,   125,   133,   134,   136,   145,   152,   156,   157,
      97,    51,   155,   149,    53,     0,     0,     0,     0,     0,
       0,    98,     0,     0,    51,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    51,     0,
       0,    99,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,    53,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    51,     0,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    53,     0,   122,     0,     0,     0,     0,     0,
       0,    51,     0,   127,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   128,    51,
       0,     0,    53,     0,     0,     0,     0,     0,     0,   129,
       0,     0,     0,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
      53,     0,   130,     0,   146,     0,     0,     0,     0,     0,
      51,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    51,   154,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,    57,    58,    59,    60,    61,    62,
      63,    64,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
      29,    30,    31,    32,    22,    23,   107,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,    30,    31,    32
};

static const short yycheck[] =
{
      16,     5,    18,    19,    13,    21,     4,    25,    10,     4,
       3,     5,    10,    29,    30,     8,    25,    25,    22,    12,
      11,    15,     4,    25,    25,    41,    19,    25,    21,    45,
      46,    47,    48,     7,    25,    51,    18,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    33,
      34,    35,    36,    37,    38,    39,    40,     4,     5,    39,
      40,    25,   106,    37,    38,    39,    40,    39,    40,    95,
      96,    18,     4,    99,   100,     4,   102,   126,   127,    13,
     106,     4,     5,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,   138,    18,   122,    13,   124,   131,
     132,    13,    13,    25,   130,     4,     5,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     6,    18,
      10,    40,   148,     9,    11,   151,    10,    25,     4,     4,
      11,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     4,    18,    33,    34,    35,    36,    37,    38,
      39,    40,    14,     4,    18,    16,    18,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    17,    18,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       4,     7,     5,    25,     9,    14,     7,   148,     0,     0,
      14,     4,     0,   145,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    -1,    -1,     4,    18,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     4,    -1,
      -1,     7,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     4,    -1,    -1,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,     4,    -1,     6,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,     4,
      -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    18,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,    -1,    -1,
      18,    -1,    20,    -1,    11,    -1,    -1,    -1,    -1,    -1,
       4,    18,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     4,     5,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 89 "reactive-modules.y"
{ 
     switch(yyvsp[0].pmentry->kind)
       {
       case PMENTRY_TYPE:
	 PMFILE->kind = yyvsp[0].pmentry->u.file_type;
	 break;
       case PMENTRY_CONST:
	 yyvsp[0].pmentry->next = PMFILE->constants;
	 if(PMFILE->constants)
	   PMFILE->constants->prev = yyvsp[0].pmentry;
	 yyvsp[0].pmentry->prev = NULL;
	 PMFILE->constants = yyvsp[0].pmentry;
	 break;
       case PMENTRY_MODULE:
	 yyvsp[0].pmentry->next = PMFILE->modules;
	 if(PMFILE->modules)
	   PMFILE->modules->prev = yyvsp[0].pmentry;
	 yyvsp[0].pmentry->prev = NULL;
	 PMFILE->modules = yyvsp[0].pmentry;
	 break;
       case PMENTRY_FORM:
	 yyvsp[0].pmentry->next = PMFILE->formulas;
	 if(PMFILE->formulas)
	   PMFILE->formulas->prev = yyvsp[0].pmentry;
	 yyvsp[0].pmentry->prev = NULL;
	 PMFILE->formulas = yyvsp[0].pmentry;
	 break;
       }
   }
    break;
case 3:
#line 118 "reactive-modules.y"
{}
    break;
case 4:
#line 123 "reactive-modules.y"
{
    yyval.pmentry = new(struct pmentry);
    yyval.pmentry->kind = PMENTRY_TYPE;
    yyval.pmentry->u.file_type = yyvsp[0].integer;
  }
    break;
case 5:
#line 129 "reactive-modules.y"
{
    yyval.pmentry = new(struct pmentry);
    yyval.pmentry->kind = PMENTRY_CONST;
    yyval.pmentry->u.constant = yyvsp[0].constdef;
  }
    break;
case 6:
#line 135 "reactive-modules.y"
{
    yyval.pmentry = new(struct pmentry);
    yyval.pmentry->kind = PMENTRY_MODULE;
    yyval.pmentry->u.module = yyvsp[0].moduledef;
  }
    break;
case 7:
#line 141 "reactive-modules.y"
{
    yyval.pmentry = new(struct pmentry);
    yyval.pmentry->kind = PMENTRY_FORM;
    yyval.pmentry->u.formula = yyvsp[0].formuladef;
  }
    break;
case 8:
#line 149 "reactive-modules.y"
{ yyval.integer = PMFILE_PROBABILISTIC; }
    break;
case 9:
#line 154 "reactive-modules.y"
{
  yyval.constdef = new(struct constdef);
  yyval.constdef->name = yyvsp[-3].string;
  yyval.constdef->kind = CONST_INT;
  yyval.constdef->u.intvalue = evaluate_intexpr(yyvsp[-1].expr, PMFILE->constants);
  icall(free_expr, yyvsp[-1].expr);
}
    break;
case 10:
#line 162 "reactive-modules.y"
{
  if( (yyvsp[-1].expr->ekind != CST) && (yyvsp[-1].expr->etype != FLOAT) )
    {
      fprintf(stderr, "bug : in constdef, expr kind = %d not float or cst\n",
	      yyvsp[-1].expr->ekind);
      exit(1);
    }

  yyval.constdef = new(struct constdef);
  yyval.constdef->name = yyvsp[-3].string;
  yyval.constdef->kind = CONST_FLOAT;
  yyval.constdef->u.floatvalue = yyvsp[-1].expr->efloat_value;
  icall(free_expr, yyvsp[-1].expr);
}
    break;
case 11:
#line 179 "reactive-modules.y"
{
  CURRENT_MODULE = new(struct moduledef);
  CURRENT_MODULE->modulename = yyvsp[0].string;
}
    break;
case 12:
#line 184 "reactive-modules.y"
{
  yyval.moduledef = CURRENT_MODULE;
}
    break;
case 13:
#line 191 "reactive-modules.y"
{
  struct pmentry *m;
  struct renamelist *rl;

  for(m = PMFILE->modules; m; m = m->next)
    if(m->kind == PMENTRY_MODULE)
      if(!strcmp(m->u.module->modulename, yyvsp[-4].string))
	{
	  CURRENT_MODULE->rules = clone_rules(m->u.module->rules, yyvsp[-2].renamelist);
	  break;
	}

  for(rl = yyvsp[-2].renamelist; rl; rl = rl->next)
    if(rl->is_var)
      {
	if( var_is_undef(rl->u.var.into) && !var_is_undef(rl->u.var.what) )
	  {
	    rl->u.var.into->min = rl->u.var.what->min;
	    rl->u.var.into->max = rl->u.var.what->max;
	    rl->u.var.into->initial_value = rl->u.var.what->initial_value;
	    rl->u.var.into->current_value = rl->u.var.what->current_value;	    
	  }
      }

  icall(free_rl, yyvsp[-2].renamelist);

  if(m)
    {
      yyval.moduledef = CURRENT_MODULE;
    }
  else
    {
      char msg[128+strlen(yyvsp[-4].string)];
      sprintf(msg, "module %s is used but not defined", yyvsp[-4].string);
      rm_error(msg);
      YYABORT;
    }
}
    break;
case 14:
#line 230 "reactive-modules.y"
{
  yyval.moduledef = CURRENT_MODULE;
}
    break;
case 15:
#line 237 "reactive-modules.y"
{

}
    break;
case 16:
#line 242 "reactive-modules.y"
{   
  /*
  $1->next = PMFILE->variables;
  PMFILE->variables = $1;
  */
}
    break;
case 17:
#line 249 "reactive-modules.y"
{ 
 yyvsp[-1].rule->next = CURRENT_MODULE->rules;
 CURRENT_MODULE->rules = yyvsp[-1].rule;
}
    break;
case 18:
#line 257 "reactive-modules.y"
{
  yyval.vardef = lookup_or_create_var(yyvsp[-7].string);
  ifree(yyvsp[-7].string);
  yyval.vardef->min = evaluate_intexpr(yyvsp[-4].expr, PMFILE->constants);
  icall(free_expr, yyvsp[-4].expr);
  yyval.vardef->max = evaluate_intexpr(yyvsp[-2].expr, PMFILE->constants);
  icall(free_expr, yyvsp[-2].expr);
  yyval.vardef->initial_value = yyval.vardef->min;
  yyval.vardef->current_value = yyval.vardef->min;
}
    break;
case 19:
#line 268 "reactive-modules.y"
{
  yyval.vardef = lookup_or_create_var(yyvsp[-9].string);
  ifree(yyvsp[-9].string);
  yyval.vardef->min = evaluate_intexpr(yyvsp[-6].expr, PMFILE->constants);
  icall(free_expr, yyvsp[-6].expr);
  yyval.vardef->max = evaluate_intexpr(yyvsp[-4].expr, PMFILE->constants);
  icall(free_expr, yyvsp[-4].expr);
  yyval.vardef->initial_value = evaluate_intexpr(yyvsp[-1].expr, PMFILE->constants);
  icall(free_expr, yyvsp[-1].expr);
  yyval.vardef->current_value = yyval.vardef->initial_value;
}
    break;
case 20:
#line 283 "reactive-modules.y"
{
  yyval.rule = new(struct rule);
  yyval.rule->stateofrule = yyvsp[-3].string;
  yyval.rule->guard    = yyvsp[-2].expr;

  yyval.rule->act      = yyvsp[0].action;
}
    break;
case 21:
#line 294 "reactive-modules.y"
{
  yyval.action = new(struct action);
  yyval.action->probabilistic = 1;
  yyval.action->u.prob = yyvsp[0].probaff;
}
    break;
case 22:
#line 300 "reactive-modules.y"
{
  yyval.action = new(struct action);
  yyval.action->probabilistic = 0;
  yyval.action->u.det = yyvsp[0].affectations;  
}
    break;
case 23:
#line 309 "reactive-modules.y"
{
  yyval.string = NULL;
}
    break;
case 24:
#line 313 "reactive-modules.y"
{
  yyval.string = yyvsp[-1].string;
}
    break;
case 25:
#line 320 "reactive-modules.y"
{
  yyval.probaff = new(struct probaff);
  yyval.probaff->proba = yyvsp[-3].expr->efloat_value;
  icall(free_expr, yyvsp[-3].expr);
  yyval.probaff->det   = yyvsp[-1].affectations;
}
    break;
case 26:
#line 327 "reactive-modules.y"
{
  yyval.probaff = new(struct probaff);
  yyval.probaff->proba = yyvsp[-4].expr->efloat_value;
  icall(free_expr, yyvsp[-4].expr);
  yyval.probaff->det   = yyvsp[-2].affectations;
  yyval.probaff->next  = yyvsp[0].probaff;
}
    break;
case 27:
#line 338 "reactive-modules.y"
{
  yyval.affectations = yyvsp[0].affectations;
}
    break;
case 28:
#line 342 "reactive-modules.y"
{
  yyval.affectations = yyvsp[-2].affectations;
  yyval.affectations->next = yyvsp[0].affectations;
}
    break;
case 29:
#line 350 "reactive-modules.y"
{
  yyval.affectations = yyvsp[-1].affectations;
}
    break;
case 30:
#line 357 "reactive-modules.y"
{
  yyval.affectations = yyvsp[-1].affectations;
}
    break;
case 31:
#line 361 "reactive-modules.y"
{
  yyval.affectations = new(struct affectations);
  yyval.affectations->id = new_expr_by_id(yyvsp[-2].string, SEARCH_IN_VARIABLES);
  if(!yyval.affectations->id)
    {
      char msg[128+strlen(yyvsp[-2].string)];
      sprintf(msg, "identifier %s is used but not defined as a variable", yyvsp[-2].string);
      rm_error(msg);
      ifree(yyvsp[-2].string);
      YYABORT;
    }
  else
    ifree(yyvsp[-2].string);
  yyval.affectations->exp = yyvsp[0].expr;
}
    break;
case 32:
#line 381 "reactive-modules.y"
{
  yyval.expr = new_expr_by_intcst(1);
}
    break;
case 33:
#line 385 "reactive-modules.y"
{
  yyval.expr = new_expr_by_intcst(0);
}
    break;
case 34:
#line 390 "reactive-modules.y"
{
  yyval.expr = new_expr_by_intcst(yyvsp[0].integer);
}
    break;
case 35:
#line 394 "reactive-modules.y"
{
  yyval.expr = new_expr_by_floatcst(yyvsp[0].fl);
}
    break;
case 36:
#line 398 "reactive-modules.y"
{
  yyval.expr = new_expr_by_id(yyvsp[0].string, SEARCH_IN_FORMULAE | SEARCH_IN_CONSTANTS | SEARCH_IN_VARIABLES);
  if(yyval.expr == NULL)
    {
      char msg[128+strlen(yyvsp[0].string)];
      sprintf(msg, "identifier %s is used but not defined", yyvsp[0].string);
      rm_error(msg);
      ifree(yyvsp[0].string);
      YYABORT;
    }
  ifree(yyvsp[0].string);
}
    break;
case 37:
#line 411 "reactive-modules.y"
{
  yyval.expr = new_expr_by_unary(NOT, yyvsp[0].expr);
}
    break;
case 38:
#line 415 "reactive-modules.y"
{
  yyval.expr = new_expr_by_unary(NEXT, yyvsp[0].expr);
}
    break;
case 39:
#line 419 "reactive-modules.y"
{
  yyval.expr = new_expr_by_unary(CEIL, yyvsp[-1].expr);
}
    break;
case 40:
#line 423 "reactive-modules.y"
{
  yyval.expr = new_expr_by_unary(FLOOR, yyvsp[-1].expr);
}
    break;
case 41:
#line 427 "reactive-modules.y"
{
  yyval.expr = yyvsp[-1].expr;
}
    break;
case 42:
#line 431 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, AND, yyvsp[0].expr);
}
    break;
case 43:
#line 435 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, OR, yyvsp[0].expr);
}
    break;
case 44:
#line 439 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, EQUAL, yyvsp[0].expr);
}
    break;
case 45:
#line 443 "reactive-modules.y"
{
  struct exprlist *v;

  v = new(struct exprlist);
  v->e = yyvsp[-2].expr;
  v->next = yyvsp[0].el;
  yyval.expr = new_equal_el(yyvsp[-4].expr, v);
}
    break;
case 46:
#line 452 "reactive-modules.y"
{
  struct exprlist *v;

  v = new_exprlist_range(yyvsp[-2].expr, yyvsp[0].expr);
  if(v==NULL)
    YYABORT;

  yyval.expr = new_equal_el(yyvsp[-4].expr, v);
}
    break;
case 47:
#line 463 "reactive-modules.y"
{
  struct exprlist *v, *el;

  el = new_exprlist_range(yyvsp[-4].expr, yyvsp[-2].expr);
  if(v == NULL)
    YYABORT;

  for(v=el; v->next; v=v->next);
  v->next = yyvsp[0].el;

  yyval.expr = new_equal_el(yyvsp[-6].expr, el);
}
    break;
case 48:
#line 476 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, NEQ, yyvsp[0].expr);
}
    break;
case 49:
#line 480 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, LESS, yyvsp[0].expr);
}
    break;
case 50:
#line 484 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, GREATER, yyvsp[0].expr);
}
    break;
case 51:
#line 488 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, LEQ, yyvsp[0].expr);
}
    break;
case 52:
#line 492 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, GEQ, yyvsp[0].expr);
}
    break;
case 53:
#line 496 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, PLUS, yyvsp[0].expr);
}
    break;
case 54:
#line 500 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, MINUS, yyvsp[0].expr);
}
    break;
case 55:
#line 504 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, TIMES, yyvsp[0].expr);
}
    break;
case 56:
#line 508 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, DIV, yyvsp[0].expr);
}
    break;
case 57:
#line 512 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, UNTIL, yyvsp[0].expr);
}
    break;
case 58:
#line 516 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-3].expr, MIN, yyvsp[-1].expr);
}
    break;
case 59:
#line 520 "reactive-modules.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-3].expr, MAX, yyvsp[-1].expr);
}
    break;
case 60:
#line 527 "reactive-modules.y"
{
  struct exprlist *v;

  yyval.el = yyvsp[-2].el;
  for(v = yyvsp[-2].el; v->next; v = v->next) ;
  v->next = yyvsp[0].el;
}
    break;
case 61:
#line 535 "reactive-modules.y"
{
  yyval.el = yyvsp[0].el;
}
    break;
case 62:
#line 542 "reactive-modules.y"
{
  yyval.el = new(struct exprlist);
  yyval.el->e = yyvsp[0].expr;
}
    break;
case 63:
#line 547 "reactive-modules.y"
{
  yyval.el = new_exprlist_range(yyvsp[-2].expr, yyvsp[0].expr);
}
    break;
case 64:
#line 555 "reactive-modules.y"
{
  yyval.renamelist = new(struct renamelist);
  if(id_is_synchro(yyvsp[-2].string))
    {
      yyval.renamelist->is_var = 0;
      yyval.renamelist->u.synchro.what = yyvsp[-2].string;
      yyval.renamelist->u.synchro.into = yyvsp[0].string;
    }
  else
    {
      yyval.renamelist->is_var = 1;
      yyval.renamelist->u.var.what = lookup_or_create_var(yyvsp[-2].string);
      free(yyvsp[-2].string);
      yyval.renamelist->u.var.into = lookup_or_create_var(yyvsp[0].string);
      free(yyvsp[0].string);
    }
}
    break;
case 65:
#line 574 "reactive-modules.y"
{
  yyval.renamelist = new(struct renamelist);
  if(id_is_synchro(yyvsp[-4].string))
    {
      yyval.renamelist->is_var = 0;
      yyval.renamelist->u.synchro.what = yyvsp[-4].string;
      yyval.renamelist->u.synchro.into = yyvsp[-2].string;
    }
  else
    {
      yyval.renamelist->is_var = 1;
      yyval.renamelist->u.var.what = lookup_or_create_var(yyvsp[-4].string);
      free(yyvsp[-4].string);
      yyval.renamelist->u.var.into = lookup_or_create_var(yyvsp[-2].string);
      free(yyvsp[-2].string);
    }
  yyval.renamelist->next = yyvsp[0].renamelist;
}
    break;
case 66:
#line 596 "reactive-modules.y"
{
  yyval.formuladef = new(struct formuladef);
  yyval.formuladef->name = yyvsp[-3].string;
  yyval.formuladef->exp  = yyvsp[-1].expr;
}
    break;
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 603 "reactive-modules.y"


#include <stdio.h>
int rm_parse();
int rm_lex(void);
extern FILE *rm_in;

int rm_error(char *s) {
  fprintf(stderr, "error in MODEL at line %d : %s\n", rm_lineno, s);
  return 0;
}
