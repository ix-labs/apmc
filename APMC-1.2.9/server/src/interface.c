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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "proto.h"
#include "compilers.h"

#include "../pixmap/open.xpm"
#include "../pixmap/save.xpm"
#include "../pixmap/saveas.xpm"
#include "../pixmap/clean.xpm"
#include "../pixmap/go.xpm"
#include "../pixmap/stop.xpm"
#include "../pixmap/compile.xpm"

GtkWidget *modelopen;
GtkWidget *modelsave;
GtkWidget *modelsaveas;
GtkWidget *modelclean;
GtkWidget *model;
GtkWidget *propopen;
GtkWidget *propsave;
GtkWidget *propsaveas;
GtkWidget *propclean;
GtkWidget *prop;
GtkWidget *paramtable;
GtkObject *nbpath_adj;
GtkWidget *nbpath;
GtkObject *pathlen_adj;
GtkWidget *pathlen;
GtkWidget *confidence;
GtkWidget *prob;
GtkWidget *appratio;
GtkWidget *compile;
GtkWidget *exec;
GtkWidget *stop;
GtkWidget *verifvbox;
GtkWidget *progressbar;
GtkWidget *nbverified;
GtkWidget *nbgood;
GtkWidget *estprob;
GtkWidget *finalbox;
GtkWidget *finalresult;
GtkWidget *statusbar;
GtkWidget *clusterarea;
GtkWidget *window;
GtkWidget *current_confidence;
GtkWidget *compile_strategy;
GtkRcStyle *black_over_green, *black_over_red, *red_over_green, *blue_over_gray;
GdkColor black, green, red, blue, grey;
int cid;

double Confidence, AppRatio, Prob;

GIOChannel *code_server, *job_server;

GtkWidget* create_window1 (void)
{
  GtkWidget *vbox4;
  GtkWidget *frame1;
  GtkWidget *vbox6;
  GtkWidget *toolbar2;
  GtkWidget *tmp_toolbar_icon;
  GtkWidget *scrolledwindow2;
  GtkWidget *frame2;
  GtkWidget *vbox7;
  GtkWidget *toolbar3;
  GtkWidget *scrolledwindow3;
  GtkWidget *frame4;
  GtkWidget *vbox9;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *label3;
  GtkWidget *label4;
  GtkWidget *label5;
  GtkWidget *hbox3;
  GtkWidget *toolbar5;
  GtkWidget *toolbar6;
  GtkWidget *hbox5;
  GtkWidget *label6;
  GtkWidget *label7;
  GtkWidget *hbox6;
  GtkWidget *label8;
  GtkWidget *label9;
  GtkWidget *label10;
  GtkWidget *frame3;
  GtkWidget *hpane1, *hpane2, *vpane1;
  GtkWidget *label11;
  GList *items;

  int fd;
  struct sockaddr_in remote;
  struct compiler *comp;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_object_set_data (GTK_OBJECT (window), "window", window);
  gtk_window_set_title (GTK_WINDOW (window), "AMC");
  gtk_signal_connect( GTK_OBJECT(window), "destroy",
		      GTK_SIGNAL_FUNC(gtk_main_quit), NULL);

  vbox4 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox4);

  hpane1 = gtk_hpaned_new();
  hpane2 = gtk_hpaned_new();

  gtk_box_pack_start (GTK_BOX(vbox4), hpane1, TRUE, TRUE, 0);
  gtk_paned_pack1 (GTK_PANED(hpane1), hpane2, TRUE, TRUE);

  frame1 = gtk_frame_new ("Model");
  gtk_paned_pack1 (GTK_PANED (hpane2), frame1, TRUE, TRUE);

  vbox6 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame1), vbox6);

  toolbar2 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_box_pack_start (GTK_BOX (vbox6), toolbar2, FALSE, FALSE, 0);
  gtk_toolbar_set_space_size (GTK_TOOLBAR (toolbar2), 4);
  gtk_toolbar_set_space_style (GTK_TOOLBAR (toolbar2), GTK_TOOLBAR_SPACE_LINE);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_OPEN);
  modelopen = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar2),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Open",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(modelopen), "clicked",
		     GTK_SIGNAL_FUNC(on_modelopen_clicked), NULL);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_SAVE);
  modelsave = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar2),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Save",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(modelsave), "clicked",
		     GTK_SIGNAL_FUNC(on_modelsave_clicked), NULL);
  gtk_widget_set_sensitive(modelsave, FALSE);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_SAVE_AS);
  modelsaveas = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar2),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Save As",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(modelsaveas), "clicked",
		     GTK_SIGNAL_FUNC(on_modelsaveas_clicked), NULL);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_TRASH);
  modelclean = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar2),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Clean",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(modelclean), "clicked",
		     GTK_SIGNAL_FUNC(on_modelclean_clicked), NULL);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_box_pack_start (GTK_BOX (vbox6), scrolledwindow2, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  model = gtk_text_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), model);
  gtk_text_set_editable (GTK_TEXT (model), TRUE);
  gtk_signal_connect(GTK_OBJECT(model), "changed",
		     GTK_SIGNAL_FUNC(on_model_changed), NULL);

  vpane1 = gtk_vpaned_new();
  gtk_paned_pack2( GTK_PANED(hpane2), vpane1, TRUE, TRUE);

  frame2 = gtk_frame_new ("Property");
  gtk_paned_pack1( GTK_PANED(vpane1), frame2, TRUE, TRUE);

  vbox7 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame2), vbox7);

  toolbar3 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_box_pack_start (GTK_BOX (vbox7), toolbar3, FALSE, FALSE, 0);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_OPEN);
  propopen = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar3),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Open",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(propopen), "clicked",
		     GTK_SIGNAL_FUNC(on_propopen_clicked), NULL);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_SAVE);
  propsave = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar3),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Save",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_set_sensitive(propsave, FALSE);
  gtk_signal_connect(GTK_OBJECT(propsave), "clicked",
		     GTK_SIGNAL_FUNC(on_propsave_clicked), NULL);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_SAVE_AS);
  propsaveas = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar3),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Save As",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(propsaveas), "clicked",
		     GTK_SIGNAL_FUNC(on_propsaveas_clicked), NULL);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_TRASH);
  propclean = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar3),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Clean",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(propclean), "clicked",
		     GTK_SIGNAL_FUNC(on_propclean_clicked), NULL);

  scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
  gtk_box_pack_start (GTK_BOX (vbox7), scrolledwindow3, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow3), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  prop = gtk_text_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (scrolledwindow3), prop);
  gtk_text_set_editable (GTK_TEXT (prop), TRUE);
  gtk_signal_connect(GTK_OBJECT(prop), "changed",
		     GTK_SIGNAL_FUNC(on_prop_changed), NULL);

  frame4 = gtk_frame_new ("Verification");
  gtk_paned_pack2( GTK_PANED(vpane1), frame4, FALSE, FALSE );

  vbox9 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame4), vbox9);

  paramtable = gtk_table_new (2, 6, FALSE);
  gtk_box_pack_start (GTK_BOX (vbox9), paramtable, TRUE, TRUE, 0);

  label1 = gtk_label_new ("prob");
  gtk_table_attach (GTK_TABLE (paramtable), label1, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label1), 0, 0.5);

  label2 = gtk_label_new ("app. ratio");
  gtk_table_attach (GTK_TABLE (paramtable), label2, 2, 3, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label2), 0, 0.5);

  label3 = gtk_label_new ("confidence");
  gtk_table_attach (GTK_TABLE (paramtable), label3, 4, 5, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label3), 0, 0.5);

  label4 = gtk_label_new ("# paths");
  gtk_table_attach (GTK_TABLE (paramtable), label4, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label4), 0, 0.5);

  label5 = gtk_label_new ("paths length");
  gtk_table_attach (GTK_TABLE (paramtable), label5, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 5, 0);
  gtk_misc_set_alignment (GTK_MISC (label5), 0, 0.5);

  pathlen_adj = gtk_adjustment_new (1, 0, 0xffffffff, 1, 10, 10);
  pathlen = gtk_spin_button_new (GTK_ADJUSTMENT (pathlen_adj), 1, 0);
  gtk_table_attach (GTK_TABLE (paramtable), pathlen, 3, 4, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);

  confidence = gtk_entry_new ();
  gtk_table_attach (GTK_TABLE (paramtable), confidence, 5, 6, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);
  gtk_entry_set_text (GTK_ENTRY (confidence), "1e-10");
  Confidence = 1E-10;
  gtk_signal_connect(GTK_OBJECT(confidence), "changed",
		     GTK_SIGNAL_FUNC(on_calculate_formula), NULL);

  prob = gtk_entry_new ();
  gtk_table_attach (GTK_TABLE (paramtable), prob, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);
  gtk_entry_set_text (GTK_ENTRY (prob), "1.0");
  Prob = 1.0;
  gtk_signal_connect(GTK_OBJECT(prob), "changed",
		     GTK_SIGNAL_FUNC(on_calculate_formula), NULL);

  appratio = gtk_entry_new ();
  gtk_table_attach (GTK_TABLE (paramtable), appratio, 3, 4, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);
  gtk_entry_set_text (GTK_ENTRY (appratio), "0.01");
  AppRatio = 0.01;
  gtk_signal_connect(GTK_OBJECT(appratio), "changed",
		     GTK_SIGNAL_FUNC(on_calculate_formula), NULL);

  nbpath_adj = gtk_adjustment_new (prc_to_nbpath(AppRatio, Confidence), 0.0, 
				   (gfloat)((int)0x7fffffff), 10.0, 100.0, 200.0);
  nbpath = gtk_spin_button_new (GTK_ADJUSTMENT (nbpath_adj), 1, 0);
  gtk_table_attach (GTK_TABLE (paramtable), nbpath, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);
  gtk_signal_connect(GTK_OBJECT(nbpath), "changed",
		     GTK_SIGNAL_FUNC(on_inverse_formula), NULL);

  label11 = gtk_label_new("Compilation strategy");
  gtk_table_attach (GTK_TABLE (paramtable), label11, 4, 5, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);
  gtk_widget_show(label11);
  
  items = NULL;
  for( comp = get_compiler_from_name(NULL); comp; comp = comp->next )
    items = g_list_append (items, comp->name);

  compile_strategy = gtk_combo_new();
  gtk_combo_set_popdown_strings (GTK_COMBO (compile_strategy), items);
  gtk_combo_set_value_in_list ( GTK_COMBO(compile_strategy), TRUE, FALSE);
  gtk_combo_set_use_arrows_always ( GTK_COMBO(compile_strategy), TRUE);
  gtk_table_attach (GTK_TABLE (paramtable), compile_strategy, 5, 6, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    GTK_FILL|GTK_EXPAND|GTK_SHRINK, 0, 0);
  gtk_editable_set_editable( GTK_EDITABLE( GTK_COMBO(compile_strategy)->entry ),
			     FALSE );
  gtk_widget_show( compile_strategy );
  
  hbox3 = gtk_hbox_new (TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox9), hbox3, TRUE, TRUE, 0);

  toolbar6 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_box_pack_start (GTK_BOX (hbox3), toolbar6, TRUE, FALSE, 0);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_COMPILE);
  compile = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar6),
					GTK_TOOLBAR_CHILD_BUTTON,
					NULL,
					"Compile",
					NULL, NULL,
					tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(compile), "clicked",
		     GTK_SIGNAL_FUNC(on_compile_clicked), items);
  gtk_widget_set_sensitive(compile, FALSE);

  toolbar5 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_box_pack_start (GTK_BOX (hbox3), toolbar5, TRUE, FALSE, 0);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_EXEC);
  exec = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar5),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Go!",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(exec), "clicked",
		     GTK_SIGNAL_FUNC(on_dojob_clicked), NULL);
  gtk_widget_set_sensitive(exec, FALSE);

  toolbar6 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_box_pack_start (GTK_BOX (hbox3), toolbar6, TRUE, FALSE, 0);

  tmp_toolbar_icon = build_pixmap (window, STOCK_PIXMAP_STOP);
  stop = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar6),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                "Stop",
                                NULL, NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_signal_connect(GTK_OBJECT(stop), "clicked",
		     GTK_SIGNAL_FUNC(on_stopjob_clicked), NULL);
  gtk_widget_set_sensitive(stop, FALSE);

  verifvbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_sensitive(verifvbox, FALSE);
  gtk_box_pack_start (GTK_BOX (vbox9), verifvbox, TRUE, TRUE, 0);

  progressbar = gtk_progress_bar_new ();
  gtk_box_pack_start (GTK_BOX (verifvbox), progressbar, FALSE, FALSE, 0);
  gtk_progress_set_show_text (GTK_PROGRESS (progressbar), TRUE);

  hbox5 = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (verifvbox), hbox5, TRUE, TRUE, 0);

  label6 = gtk_label_new ("#paths verified");
  gtk_box_pack_start (GTK_BOX (hbox5), label6, FALSE, FALSE, 5);

  nbverified = gtk_entry_new ();
  gtk_box_pack_start (GTK_BOX (hbox5), nbverified, TRUE, TRUE, 0);
  gtk_entry_set_editable (GTK_ENTRY (nbverified), FALSE);

  label7 = gtk_label_new ("# satisfying paths");
  gtk_box_pack_start (GTK_BOX (hbox5), label7, FALSE, FALSE, 5);

  nbgood = gtk_entry_new ();
  gtk_box_pack_start (GTK_BOX (hbox5), nbgood, TRUE, TRUE, 0);
  gtk_entry_set_editable (GTK_ENTRY (nbgood), FALSE);

  hbox6 = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (verifvbox), hbox6, TRUE, TRUE, 0);

  label8 = gtk_label_new ("Estimated probability");
  gtk_box_pack_start (GTK_BOX (hbox6), label8, FALSE, FALSE, 5);

  estprob = gtk_label_new("");
  gtk_box_pack_start (GTK_BOX (hbox6), estprob, FALSE, FALSE, 5);

  label10 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(hbox6), label10, TRUE, TRUE, 5);

  label9 = gtk_label_new ("Current confidence");
  gtk_box_pack_start(GTK_BOX(hbox6), label9, FALSE, FALSE, 5);

  current_confidence = gtk_label_new("");
  gtk_box_pack_start (GTK_BOX (hbox6), current_confidence, FALSE, FALSE, 5);

  finalbox = gtk_event_box_new ();
  gtk_box_pack_start (GTK_BOX (vbox9), finalbox, TRUE, TRUE, 0);

  finalresult = gtk_label_new ("");
  gtk_container_add (GTK_CONTAINER (finalbox), finalresult);

  frame3 = gtk_frame_new ("Cluster");
  gtk_paned_pack2( GTK_PANED(hpane1), frame3, TRUE, TRUE);

  clusterarea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (frame3), clusterarea);
  gtk_signal_connect(GTK_OBJECT(clusterarea), "expose-event",
		     GTK_SIGNAL_FUNC(on_expose_cluster), NULL);
  statusbar = gtk_statusbar_new ();
  gtk_box_pack_start (GTK_BOX (vbox4), statusbar, FALSE, FALSE, 0);
  cid = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
				     "AMC");

  gtk_widget_show_all(window);

  if( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    perror("socket");
  remote.sin_addr.s_addr = INADDR_ANY;
  remote.sin_port = htons(CODE_PORT);
  remote.sin_family = AF_INET;
  if( bind(fd, (struct sockaddr*)&remote, sizeof(remote)) < 0)
    perror("bind");
  if( listen(fd, 1) < 0)
    perror("listen");
  code_server = g_io_channel_unix_new(fd);
  g_io_add_watch(code_server, G_IO_IN, on_new_code_connexion, NULL);

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  remote.sin_addr.s_addr = INADDR_ANY;
  remote.sin_port = htons(JOB_PORT);
  remote.sin_family = AF_INET;
  if( bind(fd, (struct sockaddr*)&remote, sizeof(remote)) < 0)
    perror("bind");
  job_server = g_io_channel_unix_new(fd);
  g_io_add_watch(job_server, G_IO_IN, on_new_job_request, NULL);

  
  green.red   = 0;
  green.green = 65535;
  green.blue  = 0;
  green.pixel = 0;
  gdk_color_alloc(gtk_widget_get_colormap(finalresult), &green);

  grey.red   = 54015;
  grey.green = 54015;
  grey.blue  = 54015;
  grey.pixel = 0;
  gdk_color_alloc(gtk_widget_get_colormap(finalresult), &grey);

  black.red  = 0;
  black.green = 0;
  black.blue = 0;
  black.pixel = 0;
  gdk_color_alloc(gtk_widget_get_colormap(finalresult), &black);

  red.red = 65535;
  red.green = 0;
  red.blue = 0;
  red.pixel = 0;
  gdk_color_alloc(gtk_widget_get_colormap(finalresult), &red);
    
  blue.red = 0;
  blue.green = 0;
  blue.blue = 65535;
  blue.pixel = 0;
  gdk_color_alloc(gtk_widget_get_colormap(finalresult), &blue);

  black_over_green = gtk_rc_style_new();
  black_over_green->fg[GTK_STATE_NORMAL] = black;
  black_over_green->bg[GTK_STATE_NORMAL] = green;
  black_over_green->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG | GTK_RC_BG;

  red_over_green = gtk_rc_style_new();
  red_over_green->fg[GTK_STATE_NORMAL] = red;
  red_over_green->bg[GTK_STATE_NORMAL] = green;
  red_over_green->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG | GTK_RC_BG;

  blue_over_gray = gtk_rc_style_new();
  blue_over_gray->fg[GTK_STATE_NORMAL] = blue;
  blue_over_gray->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG;

  black_over_red = gtk_rc_style_new();
  black_over_red->fg[GTK_STATE_NORMAL] = black;
  black_over_red->bg[GTK_STATE_NORMAL] = red;
  black_over_red->color_flags[GTK_STATE_NORMAL] |= GTK_RC_FG | GTK_RC_BG;

  return window;
}

