/* A Bison parser, made from ltl.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse ltl_parse
#define yylex ltl_lex
#define yyerror ltl_error
#define yylval ltl_lval
#define yychar ltl_char
#define yydebug ltl_debug
#define yynerrs ltl_nerrs
# define	t_INTEGER	257
# define	t_ID	258
# define	t_FLOAT	259
# define	t_DP	260
# define	t_QMARK	261
# define	t_LPAR	262
# define	t_RPAR	263
# define	t_CEIL	264
# define	t_FLOOR	265
# define	t_MIN	266
# define	t_MAX	267
# define	t_UNTIL	268
# define	t_OR	269
# define	t_AND	270
# define	t_EQUAL	271
# define	t_NEQ	272
# define	t_TO	273
# define	t_COMMA	274
# define	t_LESS	275
# define	t_LEQ	276
# define	t_GREATER	277
# define	t_GEQ	278
# define	t_PLUS	279
# define	t_MINUS	280
# define	t_TIMES	281
# define	t_DIV	282
# define	t_NEXT	283
# define	t_NOT	284
# define	t_TRUE	285
# define	t_FALSE	286

#line 1 "ltl.y"


extern int ltl_lineno;

#include <stdlib.h>
#include <string.h>

#include "expr.h"

int ltl_lex(void);
int ltl_error(char *error);

extern exprlist *LTL;
void free_LTL();


#line 23 "ltl.y"
#ifndef YYSTYPE
typedef union{
  char *string;
  int   integer;
  double fl;

  expr *expr;
  exprlist *el;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 1
#endif



#define	YYFINAL		79
#define	YYFLAG		-32768
#define	YYNTBASE	33

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 286 ? yytranslate[x] : 37)

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
      26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     6,     8,    10,    12,    14,    17,
      20,    25,    30,    34,    38,    42,    46,    52,    58,    66,
      70,    74,    78,    82,    86,    90,    94,    98,   102,   106,
     113,   120,   126,   130,   132,   134
};
static const short yyrhs[] =
{
      -1,    34,    33,     0,    31,     0,    32,     0,     3,     0,
       5,     0,     4,     0,    30,    34,     0,    29,    34,     0,
      10,     8,    34,     9,     0,    11,     8,    34,     9,     0,
       8,    34,     9,     0,    34,    16,    34,     0,    34,    15,
      34,     0,    34,    17,    34,     0,    34,    17,    34,    20,
      35,     0,    34,    17,    34,    19,    34,     0,    34,    17,
      34,    19,    34,    20,    35,     0,    34,    18,    34,     0,
      34,    21,    34,     0,    34,    23,    34,     0,    34,    22,
      34,     0,    34,    24,    34,     0,    34,    25,    34,     0,
      34,    26,    34,     0,    34,    27,    34,     0,    34,    28,
      34,     0,    34,    14,    34,     0,    12,     8,    34,    20,
      34,     9,     0,    13,     8,    34,    20,    34,     9,     0,
      34,     7,    34,     6,    34,     0,    36,    20,    35,     0,
      36,     0,    34,     0,    34,    19,    34,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    58,    62,    73,    78,    82,    87,    91,   104,   108,
     112,   116,   120,   124,   128,   132,   136,   145,   155,   169,
     173,   177,   181,   185,   189,   193,   197,   201,   205,   209,
     213,   217,   223,   232,   238,   244
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "t_INTEGER", "t_ID", "t_FLOAT", "t_DP", 
  "t_QMARK", "t_LPAR", "t_RPAR", "t_CEIL", "t_FLOOR", "t_MIN", "t_MAX", 
  "t_UNTIL", "t_OR", "t_AND", "t_EQUAL", "t_NEQ", "t_TO", "t_COMMA", 
  "t_LESS", "t_LEQ", "t_GREATER", "t_GEQ", "t_PLUS", "t_MINUS", "t_TIMES", 
  "t_DIV", "t_NEXT", "t_NOT", "t_TRUE", "t_FALSE", "expressions", "expr", 
  "exprlist", "exprrange", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    33,    33,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    35,    35,    36,    36
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     1,     1,     1,     1,     1,     2,     2,
       4,     4,     3,     3,     3,     3,     5,     5,     7,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     6,
       6,     5,     3,     1,     1,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     5,     7,     6,     0,     0,     0,     0,     0,     0,
       0,     3,     4,     1,     0,     0,     0,     0,     0,     9,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,    12,     0,     0,     0,
       0,     0,    28,    14,    13,    15,    19,    20,    22,    21,
      23,    24,    25,    26,    27,    10,    11,     0,     0,     0,
       0,     0,     0,     0,    31,    17,    34,    16,    33,    29,
      30,     0,     0,     0,    18,    35,    32,     0,     0,     0
};

static const short yydefgoto[] =
{
      35,    66,    67,    68
};

static const short yypact[] =
{
      32,-32768,-32768,-32768,    32,    -6,     6,    11,    12,    32,
      32,-32768,-32768,    63,   112,    32,    32,    32,    32,-32768,
  -32768,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,-32768,-32768,   134,   156,   178,
     200,    90,   295,   308,   320,    27,   337,   -20,   -20,   -20,
     -20,   -16,   -16,    10,-32768,-32768,-32768,    32,    32,    32,
      32,    32,   222,   244,   281,   329,   266,-32768,    19,-32768,
  -32768,    32,    32,    32,-32768,   337,-32768,    41,    56,-32768
};

static const short yypgoto[] =
{
      65,     0,   -70,-32768
};


#define	YYLAST		365


static const short yytable[] =
{
      13,    74,    15,    76,    14,    31,    32,    33,    34,    19,
      20,    33,    34,    13,    16,    37,    38,    39,    40,    17,
      18,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,     1,     2,     3,    34,    73,
       4,    78,     5,     6,     7,     8,    60,    61,    27,    28,
      29,    30,    31,    32,    33,    34,    79,    62,    63,    64,
      65,     9,    10,    11,    12,    77,     1,     2,     3,     0,
      21,     4,    75,     5,     6,     7,     8,    22,    23,    24,
      25,    26,     0,     0,    27,    28,    29,    30,    31,    32,
      33,    34,     9,    10,    11,    12,    59,    21,     0,     0,
       0,     0,     0,     0,    22,    23,    24,    25,    26,     0,
       0,    27,    28,    29,    30,    31,    32,    33,    34,    21,
       0,    36,     0,     0,     0,     0,    22,    23,    24,    25,
      26,     0,     0,    27,    28,    29,    30,    31,    32,    33,
      34,    21,     0,    55,     0,     0,     0,     0,    22,    23,
      24,    25,    26,     0,     0,    27,    28,    29,    30,    31,
      32,    33,    34,    21,     0,    56,     0,     0,     0,     0,
      22,    23,    24,    25,    26,     0,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    21,     0,     0,     0,     0,
       0,     0,    22,    23,    24,    25,    26,     0,    57,    27,
      28,    29,    30,    31,    32,    33,    34,    21,     0,     0,
       0,     0,     0,     0,    22,    23,    24,    25,    26,     0,
      58,    27,    28,    29,    30,    31,    32,    33,    34,    21,
       0,    69,     0,     0,     0,     0,    22,    23,    24,    25,
      26,     0,     0,    27,    28,    29,    30,    31,    32,    33,
      34,    21,     0,    70,     0,     0,     0,     0,    22,    23,
      24,    25,    26,     0,     0,    27,    28,    29,    30,    31,
      32,    33,    34,    21,     0,     0,     0,     0,     0,     0,
      22,    23,    24,    25,    26,    72,     0,    27,    28,    29,
      30,    31,    32,    33,    34,    22,    23,    24,    25,    26,
       0,     0,    27,    28,    29,    30,    31,    32,    33,    34,
      23,    24,    25,    26,     0,     0,    27,    28,    29,    30,
      31,    32,    33,    34,    24,    25,    26,     0,     0,    27,
      28,    29,    30,    31,    32,    33,    34,    25,    26,     0,
       0,    27,    28,    29,    30,    31,    32,    33,    34,    71,
      27,    28,    29,    30,    31,    32,    33,    34,    27,    28,
      29,    30,    31,    32,    33,    34
};

static const short yycheck[] =
{
       0,    71,     8,    73,     4,    25,    26,    27,    28,     9,
      10,    27,    28,    13,     8,    15,    16,    17,    18,     8,
       8,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     3,     4,     5,    28,    20,
       8,     0,    10,    11,    12,    13,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,    57,    58,    59,
      60,    29,    30,    31,    32,     0,     3,     4,     5,    -1,
       7,     8,    72,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,     7,
      -1,     9,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,     7,    -1,     9,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,     7,    -1,     9,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,     7,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     7,
      -1,     9,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,     7,    -1,     9,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    14,    15,    16,    17,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      15,    16,    17,    18,    -1,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    16,    17,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    17,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    21,    22,
      23,    24,    25,    26,    27,    28
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
#line 59 "ltl.y"
{
  LTL = NULL;
}
    break;
case 2:
#line 63 "ltl.y"
{
  exprlist *el;
  el = new(exprlist);
  el->e = yyvsp[-1].expr;
  el->next = LTL;
  LTL = el;
}
    break;
case 3:
#line 75 "ltl.y"
{
  yyval.expr = new_expr_by_intcst(1);
}
    break;
case 4:
#line 79 "ltl.y"
{
  yyval.expr = new_expr_by_intcst(0);
}
    break;
case 5:
#line 84 "ltl.y"
{
  yyval.expr = new_expr_by_intcst(yyvsp[0].integer);
}
    break;
case 6:
#line 88 "ltl.y"
{
  yyval.expr = new_expr_by_floatcst(yyvsp[0].fl);
}
    break;
case 7:
#line 92 "ltl.y"
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
case 8:
#line 105 "ltl.y"
{
  yyval.expr = new_expr_by_unary(NOT, yyvsp[0].expr);
}
    break;
case 9:
#line 109 "ltl.y"
{
  yyval.expr = new_expr_by_unary(NEXT, yyvsp[0].expr);
}
    break;
case 10:
#line 113 "ltl.y"
{
  yyval.expr = new_expr_by_unary(CEIL, yyvsp[-1].expr);
}
    break;
case 11:
#line 117 "ltl.y"
{
  yyval.expr = new_expr_by_unary(FLOOR, yyvsp[-1].expr);
}
    break;
case 12:
#line 121 "ltl.y"
{
  yyval.expr = yyvsp[-1].expr;
}
    break;
case 13:
#line 125 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, AND, yyvsp[0].expr);
}
    break;
case 14:
#line 129 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, OR, yyvsp[0].expr);
}
    break;
case 15:
#line 133 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, EQUAL, yyvsp[0].expr);
}
    break;
case 16:
#line 137 "ltl.y"
{
  struct exprlist *v;

  v = new(struct exprlist);
  v->e = yyvsp[-2].expr;
  v->next = yyvsp[0].el;
  yyval.expr = new_equal_el(yyvsp[-4].expr, v);
}
    break;
case 17:
#line 146 "ltl.y"
{
  struct exprlist *v;

  v = new_exprlist_range(yyvsp[-2].expr, yyvsp[0].expr);
  if(v==NULL)
    YYABORT;

  yyval.expr = new_equal_el(yyvsp[-4].expr, v);
}
    break;
case 18:
#line 157 "ltl.y"
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
case 19:
#line 170 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, NEQ, yyvsp[0].expr);
}
    break;
case 20:
#line 174 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, LESS, yyvsp[0].expr);
}
    break;
case 21:
#line 178 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, GREATER, yyvsp[0].expr);
}
    break;
case 22:
#line 182 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, LEQ, yyvsp[0].expr);
}
    break;
case 23:
#line 186 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, GEQ, yyvsp[0].expr);
}
    break;
case 24:
#line 190 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, PLUS, yyvsp[0].expr);
}
    break;
case 25:
#line 194 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, MINUS, yyvsp[0].expr);
}
    break;
case 26:
#line 198 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, TIMES, yyvsp[0].expr);
}
    break;
case 27:
#line 202 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, DIV, yyvsp[0].expr);
}
    break;
case 28:
#line 206 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-2].expr, UNTIL, yyvsp[0].expr);
}
    break;
case 29:
#line 210 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-3].expr, MIN, yyvsp[-1].expr);
}
    break;
case 30:
#line 214 "ltl.y"
{
  yyval.expr = new_expr_by_binary(yyvsp[-3].expr, MAX, yyvsp[-1].expr);
}
    break;
case 31:
#line 218 "ltl.y"
{
  yyval.expr = new_expr_by_ternary(ITE, yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].expr);
}
    break;
case 32:
#line 225 "ltl.y"
{
  struct exprlist *v;

  yyval.el = yyvsp[-2].el;
  for(v = yyvsp[-2].el; v->next; v = v->next) ;
  v->next = yyvsp[0].el;
}
    break;
case 33:
#line 233 "ltl.y"
{
  yyval.el = yyvsp[0].el;
}
    break;
case 34:
#line 240 "ltl.y"
{
  yyval.el = new(struct exprlist);
  yyval.el->e = yyvsp[0].expr;
}
    break;
case 35:
#line 245 "ltl.y"
{
  yyval.el = new_exprlist_range(yyvsp[-2].expr, yyvsp[0].expr);
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
#line 251 "ltl.y"


#include <stdio.h>
int ltl_parse();
int ltl_lex(void);
extern FILE *ltl_in;

int ltl_error(char *s) {
  fprintf(stderr, "error in LTL Formula at line %d : %s\n", ltl_lineno, s);
  return 0;
}

static void free_ltl(exprlist *le)
{
  if(le == NULL)
    return;

  icall(free_expr, le->e);
  icall(free_ltl, le->next);
}

void free_LTL()
{
  icall(free_ltl, LTL);
}

