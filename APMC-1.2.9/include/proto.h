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
 * 59 Templs Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#define JOB_PORT    6666
#define CODE_PORT  6667

struct job_request {
  unsigned int code_id;
  int path_len;
};

struct job_reply {
  unsigned int code_id;
  unsigned int path_len;
  unsigned int nbtrue;
  unsigned int nbfalse;
};
