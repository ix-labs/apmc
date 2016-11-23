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

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

extern GtkWidget *modelopen;
extern GtkWidget *modelsave;
extern GtkWidget *modelsaveas;
extern GtkWidget *modelclean;
extern GtkWidget *model;
extern GtkWidget *propopen;
extern GtkWidget *propsave;
extern GtkWidget *propsaveas;
extern GtkWidget *propclean;
extern GtkWidget *prop;
extern GtkWidget *paramtable;
extern GtkObject *nbpath_adj;
extern GtkWidget *nbpath;
extern GtkObject *pathlen_adj;
extern GtkWidget *pathlen;
extern GtkWidget *confidence;
extern GtkWidget *prob;
extern GtkWidget *appratio;
extern GtkWidget *exec;
extern GtkWidget *compile;
extern GtkWidget *stop;
extern GtkWidget *verifvbox;
extern GtkWidget *progressbar;
extern GtkWidget *nbverified;
extern GtkWidget *nbgood;
extern GtkWidget *estprob;
extern GtkWidget *finalbox;
extern GtkWidget *finalresult;
extern GtkWidget *statusbar;
extern GtkWidget *clusterarea;
extern GtkWidget *window;
extern GtkWidget *current_confidence;
extern GtkRcStyle *black_over_green, *black_over_red, *red_over_green, *blue_over_gray;
extern GtkWidget *compile_strategy;
extern int cid;
char msg[4096];

extern GIOChannel *code_server, *job_server;

void on_modelopen_clicked(GtkButton *button, gpointer user_data);
void on_modelclean_clicked(GtkButton *button, gpointer user_data);
void on_modelsave_clicked(GtkButton *button, gpointer user_data);
void on_modelsaveas_clicked(GtkButton *button, gpointer user_data);

void on_propopen_clicked(GtkButton *button, gpointer user_data);
void on_propclean_clicked(GtkButton *button, gpointer user_data);
void on_propsave_clicked(GtkButton *button, gpointer user_data);
void on_propsaveas_clicked(GtkButton *button, gpointer user_data);

gboolean on_new_code_connexion(GIOChannel *source,
			       GIOCondition condition,
			       gpointer data);
gboolean on_new_job_request(GIOChannel *source,
			    GIOCondition condition,
			    gpointer data);

void on_dojob_clicked(GtkButton *button, gpointer user_data);
void on_stopjob_clicked(GtkButton *button, gpointer user_data);
void on_compile_clicked(GtkButton *button, gpointer user_data);
void on_prop_changed(GtkEditable *editable, gpointer user_data);
void on_model_changed(GtkEditable *editable, gpointer user_data);
void on_calculate_formula(GtkEditable *editable,  gpointer user);
void on_inverse_formula(GtkEditable *editable,  gpointer user);
gboolean on_expose_cluster(GtkWidget *widget, 
			   GdkEventExpose *event, 
			   gpointer data);

static inline unsigned long long prc_to_nbpath(double r, double c)
{
  return (unsigned long long)(4.0*log(2.0/c)/(r * r));
}

static inline double prn_to_confidence(double r, int n)
{
  return 2.0*exp(-(double)n * r * r / 4.0 );
}
