/* APMC - Approximate Model Checker
 * Copyright (C) 2003 Thomas Hérault, Frédéric Magniett and Sylvain Peyronnet
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

#ifndef RM_DISPLAY
#define RM_DISPLAY

#include "reactive-modules.h"

void display_pmfile(struct pmfile *pm);
void display_PMFILE_variables();
void display_constant(struct constdef *c);
void display_expression(struct expr *e);
void display_act(struct affectations *aff);
void display_probact(struct probaff *aff);
void display_action(struct action *act);
void display_boolexpr(struct boolexpr *b);
void display_rule(struct rule *r);
void display_module(struct moduledef *m);
void display_pmentries(struct pmentry *p);
void display_list_action(struct action_list *al);
void display_applicable_actions(struct action_list_list *all);

#endif
