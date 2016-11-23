#ifndef BISON_LTL_TAB_H
# define BISON_LTL_TAB_H

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


extern YYSTYPE ltl_lval;

#endif /* not BISON_LTL_TAB_H */
