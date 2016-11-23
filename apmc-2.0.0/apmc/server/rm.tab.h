#ifndef BISON_RM_TAB_H
# define BISON_RM_TAB_H

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
# define	t_QMARK	284
# define	t_UNTIL	285
# define	t_OR	286
# define	t_NEQ	287
# define	t_LESS	288
# define	t_LEQ	289
# define	t_GREATER	290
# define	t_GEQ	291
# define	t_PLUS	292
# define	t_MINUS	293
# define	t_TIMES	294
# define	t_DIV	295
# define	t_NEXT	296
# define	t_NOT	297
# define	t_TRUE	298
# define	t_FALSE	299


extern YYSTYPE rm_lval;

#endif /* not BISON_RM_TAB_H */
