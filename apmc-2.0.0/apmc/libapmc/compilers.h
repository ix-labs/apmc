/* APMC - Approximate Model Checker
 * Copyright (C) 2003, 2005 Guillaume Guirado, Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
 *
 * This software is free software; you can redistributed it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful, but
 * WIHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this software; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _COMPILERS_H
#define _COMPILERS_H

#include "reactive-modules.h"

/*
 * To define a new compiler is to define a function
 * void atomic_step(void), who transforms the current configuration (given by
 * the set of variables statically defined) into a next one, selecting one set
 * of enabled modules -- accordingly reactive modules semantic -- and fire the
 * corresponding actions.
 *
 * To do this, one may define a function with the following prototype, who
 * generates code into the FILE, according to the pmfile. Static code may be
 * defined into an opening and a closing region.
 *
 * Every defined function/variable should be static ;
 * the strategy should include this file ;
 * the strategy should call the register macro somewhere in the code (
 *     register( "unique-strategy-name", compiler_function, opening_string, closing_string );
 * ).
 * Then, the strategy should be added as an object/source in Makefile
 * If every goes well, the "unique-strategy-name" should appear in the strategy combo box.
 */

typedef int (*compiler_func)(FILE *, struct pmfile *);

struct compiler {
  char *name;
  compiler_func comp;
  const char *opening;
  const char *closing;
  struct compiler *next;
};

extern struct compiler *COMPILERS;

void register_new_compiler( char *n, compiler_func comp,
			    const char *opening, const char *closing);
struct compiler *get_compiler_from_name( char *name );
int generate_code_with_compiler( FILE *f, exprlist *el, struct pmfile *pf, struct compiler *comp );
#endif
