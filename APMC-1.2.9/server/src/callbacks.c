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

#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <pty.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <sys/signal.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "gtkbfs.h"

#include "reactive-modules.h"
#include "path.h"
#include "proto.h"
#include "double.h"
#include "compilers.h"

#define fs_open_or_rename(title) do { \
  if(fs == 0) \
    { \
      fs = gtk_bfs_new(title); \
      gtk_bfs_history_set_selected(GTK_BFS(fs),\
				   gtk_bfs_add_to_history(GTK_BFS(fs), \
							  example_dir)); \
    } \
  else \
    gtk_window_set_title(GTK_WINDOW(fs), title);\
} while(0)

#define min(a,b) (((a)<(b))?(a):(b))

static GtkWidget *fs;
static char *model_filename;
static int current_code_id = 0;
static char *prop_filename;
static int current_path_len = 0;
static int current_job_true, current_job_false;
static int NbPath = 1;
static int timer;
static time_t starttime;
extern double Confidence, AppRatio, Prob;
extern GdkColor  black, green, red, blue, grey;

#define CODE_SOURCE  "/tmp/amc_gc_code.c"
#define CODE_BINARY  "/tmp/amc_gc_code"
#define COMPILE_CODE "gcc -o "CODE_BINARY" -O3 "CODE_SOURCE

#define MODEL_SYNC (1 <<  0)
#define PROP_SYNC  (1 <<  1)
#define COMPILED   (1 <<  2)
#define RUNNING    (1 <<  3)
static int gui_status;
#define ISRUNNING   ( gui_status & RUNNING  )

struct worker_stat {
  struct sockaddr_in remote;
  time_t last_ping;
  int code_id;
  int path_len;
  int nbtrue_tot;
  int nbfalse_tot;
  int nbtrue_last;
  int nbfalse_last;
  struct worker_stat *next;
};

struct worker_stat *WORKERS;

static void update_sensitive_widgets(void)
{
  if( (gui_status & PROP_SYNC) || !prop_filename )
    gtk_widget_set_sensitive(propsave, FALSE);
  else
    gtk_widget_set_sensitive(propsave, TRUE);

  if( (gui_status & MODEL_SYNC) || !model_filename )
    gtk_widget_set_sensitive(modelsave, FALSE);
  else
    gtk_widget_set_sensitive(modelsave, TRUE);
  
  if( (gui_status & MODEL_SYNC) && (gui_status & PROP_SYNC) && 
      prop_filename && model_filename )
    {
      if(!ISRUNNING)
	gtk_widget_set_sensitive(compile, TRUE);
    }
  else
    {
      gui_status &= ~COMPILED;
      //gtk_widget_set_sensitive(compile, FALSE);
    }

  if( (gui_status & COMPILED) && !ISRUNNING )
    {
      //gtk_widget_set_sensitive(compile, FALSE);
      gtk_widget_set_sensitive(exec, TRUE);
    }
  else
    gtk_widget_set_sensitive(exec, FALSE);

  if( ISRUNNING )
    {
      gtk_widget_set_sensitive(stop, TRUE);
      gtk_widget_set_sensitive(compile, FALSE);
      gtk_widget_set_sensitive(exec, FALSE);
      gtk_widget_set_sensitive(verifvbox, TRUE);
      gtk_widget_set_sensitive(paramtable, FALSE);
    }
  else
    {
      gtk_widget_set_sensitive(stop, FALSE);
      gtk_widget_set_sensitive(verifvbox, FALSE);
      gtk_widget_set_sensitive(paramtable, TRUE);
    }

}

static void OpenModel(char *filename)
{
  int fd;
  char *data;
  struct stat s;

  gtk_widget_set_sensitive(window, TRUE);
  if( filename == NULL )
    return;

  if( (stat(filename, &s) < 0) || (!S_ISREG(s.st_mode)) )
    {
    error:
      sprintf(msg, "Could not open %s : %s", filename, strerror(errno));
      gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
      return;
    }

  fd = open( filename, O_RDONLY);
  if(fd < 0)
    goto error;

  data = (char*)malloc(s.st_size + 1);
  read(fd, data, s.st_size);
  data[s.st_size] = 0;
  close(fd);
  
  gtk_text_set_point(GTK_TEXT(model), 0);
  gtk_text_forward_delete(GTK_TEXT(model), 
			  gtk_text_get_length(GTK_TEXT(model)));
  gtk_text_insert(GTK_TEXT(model), NULL, NULL, NULL, data, s.st_size);
  free(data);
	
  if(model_filename)
    free(model_filename);
  model_filename = filename;

  gui_status |= MODEL_SYNC;
  update_sensitive_widgets();

  sprintf(msg, "%s opened", filename);
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
}

void on_modelopen_clicked(GtkButton *button, gpointer user_data)
{
  fs_open_or_rename("Open a model");

  gtk_bfs_clear_filetypes( GTK_BFS(fs) );
  gtk_bfs_add_filetype( GTK_BFS(fs), "Reactive Module", "*.pm" );
  gtk_bfs_add_filetype( GTK_BFS(fs), "All", "*" );
  gtk_bfs_update( GTK_BFS(fs) );
  
  OpenModel(gtk_bfs_select( GTK_BFS(fs) ));
}

void on_modelclean_clicked(GtkButton *button, gpointer user_data)
{
  gui_status &= ~MODEL_SYNC;
  update_sensitive_widgets();

  gtk_text_set_point(GTK_TEXT(model), 0);
  gtk_text_forward_delete(GTK_TEXT(model), 
			  gtk_text_get_length(GTK_TEXT(model)));
}

static void OpenProp(char *filename)
{
  int fd;
  char *data;
  struct stat s;

  gtk_widget_set_sensitive(window, TRUE);
  if(filename == NULL)
    return;

  if( (stat(filename, &s) < 0) || (!S_ISREG(s.st_mode)) )
    {
    error:
      sprintf(msg, "Could not open %s : %s", filename, strerror(errno));
      gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
      return;
    }

  fd = open(filename, O_RDONLY);
  if(fd < 0)
    goto error;
 
  data = (char*)malloc(s.st_size + 1);
  read(fd, data, s.st_size);
  data[s.st_size] = 0;
  close(fd);
  
  gtk_text_set_point(GTK_TEXT(prop), 0);
  gtk_text_forward_delete(GTK_TEXT(prop), 
			  gtk_text_get_length(GTK_TEXT(prop)));
  gtk_text_insert(GTK_TEXT(prop), NULL, NULL, NULL, data, s.st_size);
  free(data);
		
  if(prop_filename)
    free(prop_filename);
  prop_filename = filename;
  gtk_widget_set_sensitive(window, TRUE);

  gui_status |= PROP_SYNC;
  update_sensitive_widgets();

  sprintf(msg, "%s opened", filename);
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
}

void on_propopen_clicked(GtkButton *button, gpointer user_data)
{
  fs_open_or_rename("Open a model");

  gtk_bfs_clear_filetypes( GTK_BFS(fs) );
  gtk_bfs_add_filetype( GTK_BFS(fs), "LTL Property", "*.prop" );
  gtk_bfs_add_filetype( GTK_BFS(fs), "All", "*" );
  gtk_bfs_update( GTK_BFS(fs) );
  
  OpenProp(gtk_bfs_select( GTK_BFS(fs) ));
}

void on_propclean_clicked(GtkButton *button, gpointer user_data)
{
  gtk_text_set_point(GTK_TEXT(prop), 0);
  gtk_text_forward_delete(GTK_TEXT(prop), 
			  gtk_text_get_length(GTK_TEXT(prop)));
  gui_status &= ~PROP_SYNC;
  update_sensitive_widgets();
}

static void SaveProp( char *filename )
{
  int fd;
  char *data;

  if( (filename == NULL) || (filename[strlen(filename)-1] == '/') )
    return;

  if(prop_filename != filename)
    {
      if(prop_filename)
	free(prop_filename);
      prop_filename = filename;
    }

  fd = creat(filename, 00644);
  if(fd < 0)
    {
      sprintf(msg, "Save on %s error : %s", filename, strerror(errno));
      gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
      return;
    }
  data = gtk_editable_get_chars(GTK_EDITABLE(prop), 0, -1);
  write(fd, data, gtk_text_get_length(GTK_TEXT(prop)));
  g_free(data);
  close(fd);
  
  gui_status |= PROP_SYNC;
  update_sensitive_widgets();
  
  sprintf(msg, "%s saved", filename);
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
}

static void SaveModel( char *filename )
{
  int fd;
  char *data;

  if( (filename == NULL) || (filename[strlen(filename)-1] == '/') )
    return;

  if(filename != model_filename)
    {
      if(model_filename)
	free(model_filename);
      model_filename = filename;
    }

  fd = creat(filename, 00644);
  if(fd < 0)
    {
      sprintf(msg, "Save on %s error : %s", filename, strerror(errno));
      gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
      return;
    }
  data = gtk_editable_get_chars(GTK_EDITABLE(model), 0, -1);
  write(fd, data, gtk_text_get_length(GTK_TEXT(model)));
  g_free(data);
  close(fd);

  gui_status |= MODEL_SYNC;
  update_sensitive_widgets();
        
  sprintf(msg, "%s saved", filename);
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
}

void on_propsave_clicked(GtkButton *button, gpointer user_data)
{
  SaveProp(prop_filename);
}

void on_modelsave_clicked(GtkButton *button, gpointer user_data)
{
  SaveModel(model_filename);
}

void on_modelsaveas_clicked(GtkButton *button, gpointer user_data)
{
  fs_open_or_rename("Save a model");

  gtk_bfs_clear_filetypes( GTK_BFS(fs) );
  gtk_bfs_add_filetype( GTK_BFS(fs), "Reactive Module", "*.pm" );
  gtk_bfs_add_filetype( GTK_BFS(fs), "All", "*" );
  gtk_bfs_update( GTK_BFS(fs) );
  
  SaveModel(gtk_bfs_select( GTK_BFS(fs) ));
}

void on_propsaveas_clicked(GtkButton *button, gpointer user_data)
{
  fs_open_or_rename("Save a property");

  gtk_bfs_clear_filetypes( GTK_BFS(fs) );
  gtk_bfs_add_filetype( GTK_BFS(fs), "LTL property", "*.prop" );
  gtk_bfs_add_filetype( GTK_BFS(fs), "All", "*" );
  gtk_bfs_update( GTK_BFS(fs) );
  
  SaveProp(gtk_bfs_select( GTK_BFS(fs) ));
}

struct file_download {
  char *data;
  char *cp;
  int   remaining_len;
};

typedef gboolean (*GIOFunc_t)         (GIOChannel *source, GIOCondition condition, gpointer data);
typedef void     (*GDestroyNotify_t)  (gpointer data);

static gboolean on_file_download_writeable(GIOChannel *source,
					   GIOCondition condition,
					   struct file_download *fd)
{
  int w;

  w = send(g_io_channel_unix_get_fd(source), fd->cp, fd->remaining_len, MSG_DONTWAIT | MSG_NOSIGNAL);
  if(w == -1)
    {
      if(errno == EAGAIN)
	return TRUE;
      perror("send");
      g_io_channel_close(source);
      return FALSE;
    }
  if(w)
    {
      fd->cp += w;
      fd->remaining_len -= w;
    }
  if(fd->remaining_len <= 0)
    {
      shutdown(g_io_channel_unix_get_fd(source), 2);
      return FALSE;
    }
  return TRUE;
}

static gboolean on_file_download_readable(GIOChannel *source,
					  GIOCondition condition,
					  struct file_download *fd)
{
  int r;
  char c;

  r = recv(g_io_channel_unix_get_fd(source), &c, 1, MSG_DONTWAIT);
  if(r == -1)
    {
      if(errno == EAGAIN)
	return TRUE;
      perror("read");
      g_io_channel_close(source);
      return FALSE;
    }
  if(!r)
    {
      g_io_channel_close(source);
      return FALSE;
    }
  return TRUE;
}

static gboolean on_file_download_error(GIOChannel *source,
				       GIOCondition condition,
				       struct file_download *fd)
{
  switch(condition)
    {
    case G_IO_ERR:
      sprintf(msg, "Download error : %s", strerror(errno));
      gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
      break;
    default:
      break;
    }

  g_io_channel_close(source);
  return FALSE;
}

static void on_file_download_destroy_notify(struct file_download *fd)
{
  free(fd->data);
  free(fd);
}

static void connect_download(int fd, struct file_download *down)
{
  GIOChannel *c;
  c = g_io_channel_unix_new(fd);
  g_io_add_watch_full(c, 0, G_IO_IN, (GIOFunc_t)on_file_download_readable,
		      down, (GDestroyNotify_t)on_file_download_destroy_notify);
  g_io_add_watch(c, G_IO_OUT,  (GIOFunc_t)on_file_download_writeable, down);
  g_io_add_watch(c, G_IO_ERR,  (GIOFunc_t)on_file_download_error, down);
  g_io_add_watch(c, G_IO_HUP,  (GIOFunc_t)on_file_download_error, down);
  g_io_add_watch(c, G_IO_NVAL, (GIOFunc_t)on_file_download_error, down);
}

gboolean on_new_code_connexion(GIOChannel *source,
			       GIOCondition condition,
			       gpointer data)
{
  int fd;
  struct sockaddr_in remote;
  int rlen = sizeof(remote);
  struct file_download *down;
  int mf;
  struct stat s;
  int code_id;
  
  fd = accept(g_io_channel_unix_get_fd(source), (struct sockaddr*)&remote, &rlen);

  if( recv(fd, &code_id, sizeof(int), 0) != sizeof(int) )
    {
      perror("read");
      close(fd);
      return TRUE;
    }

  if( ( code_id != current_code_id ) )
    {
      close(fd);
      return TRUE;
    }

  if( stat(CODE_BINARY, &s) < 0)
    {
      perror("code download stating file");
      close(fd);
      return TRUE;
    }

  down = (struct file_download*)calloc(1, sizeof(struct file_download));

  down->data = (char*)malloc(s.st_size);
  down->cp = down->data;
  down->remaining_len = s.st_size;

  mf = open(CODE_BINARY, O_RDONLY);
  if(mf < 0)
    {
      perror("code download opening file");
      close(fd);
      free(down->data);
      free(down);
      return TRUE;
    }

  read(mf, down->data, s.st_size);
  close(mf);

  connect_download(fd, down);
  return TRUE;
}

gboolean on_new_job_request(GIOChannel *source,
			    GIOCondition condition,
			    gpointer data)
{
  struct job_reply jr;
  struct job_request ja;
  struct sockaddr_in remote;
  int rlen = sizeof(remote);
  int r;
  struct worker_stat *w;

  r = recvfrom(g_io_channel_unix_get_fd(source),
	       &jr, sizeof(jr), 0, (struct sockaddr*)&remote, &rlen);
  for(w = WORKERS; w; w=w->next)
    if( (w->remote.sin_addr.s_addr == remote.sin_addr.s_addr) &&
	(w->remote.sin_port == remote.sin_port) )
      break;
  if(!w)
    {
      w = (struct worker_stat *)calloc(1, sizeof(struct worker_stat));
      memcpy(&w->remote, &remote, sizeof(struct sockaddr_in));
      w->next = WORKERS;
      WORKERS = w;
    }

  w->last_ping = time(NULL);

  if(r == sizeof(jr))
    {
      if(! ISRUNNING )
	{
	  if(jr.code_id == 0)
	    {
	    }
	  else
	    {
	      ja.code_id = 0;
	      ja.path_len = 0;
	      w->code_id = 0;
	      w->path_len = 0;
	      w->nbtrue_tot = 0;
	      w->nbfalse_tot = 0;
	      w->nbtrue_last = 0;
	      w->nbfalse_last = 0;
	      sendto(g_io_channel_unix_get_fd(source),
		     &ja, sizeof(ja), 0,
		     (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
	    }
	}
      else if( (jr.code_id != current_code_id) ||
	       (jr.path_len != current_path_len) )
	{
	  ja.code_id = current_code_id;
	  ja.path_len = current_path_len;
	  w->code_id = current_code_id;
	  w->path_len = current_path_len;
	  w->nbtrue_tot = 0;
	  w->nbfalse_tot = 0;
	  w->nbtrue_last = 0;
	  w->nbfalse_last = 0;
	  sendto(g_io_channel_unix_get_fd(source),
		 &ja, sizeof(ja), 0,
		 (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
	}
      else
	{
	  if( (w->code_id != current_code_id) ||
	      (w->path_len != current_path_len) )
	    {
	      printf("jamais atteint\n");
	      w->code_id = current_code_id;
	      w->path_len = current_path_len;
	      w->nbtrue_tot = 0;
	      w->nbfalse_tot = 0;
	      w->nbtrue_last = 0;
	      w->nbfalse_last = 0;
	    }
	  current_job_true += jr.nbtrue;
	  current_job_false += jr.nbfalse;
	  w->nbtrue_tot += jr.nbtrue;
	  w->nbtrue_last += jr.nbtrue;
	  w->nbfalse_tot += jr.nbfalse;
	  w->nbfalse_last += jr.nbfalse;
	  if( current_job_true + current_job_false >= NbPath )
	    {
	      on_stopjob_clicked(GTK_BUTTON(stop), NULL);
	    }
	}
    }

  return TRUE;
}

static int last_what = -1;

gboolean on_expose_cluster(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
  int what, width, height;
  GdkGC *gc;
  struct worker_stat *w;
  int n;

  what = -1;
  n = 0;
  for(w = WORKERS; w; w = w->next)
    {
      if( (w->code_id == current_code_id) &&
	  (w->path_len == current_path_len) )
	{
	  if(w->nbtrue_tot + w->nbfalse_tot > what )
	    what = w->nbtrue_tot + w->nbfalse_tot;
	  if(w->nbtrue_last + w->nbfalse_last > last_what)
	    last_what = w->nbtrue_last + w->nbfalse_last;
	  n++;
	}
    }

#define WIDTH 5
#define SEPARATOR 3

  width = clusterarea->allocation.width;
  height = (SEPARATOR+2*WIDTH)*n+1;

  if(height > clusterarea->allocation.height)
    gtk_drawing_area_size(GTK_DRAWING_AREA(clusterarea), width, height);
  height = clusterarea->allocation.height;

  gc = gdk_gc_new(clusterarea->window);
  gdk_gc_set_foreground(gc, &grey);
  gdk_gc_set_background(gc, &grey);
  gdk_gc_set_fill(gc, GDK_SOLID);
  gdk_draw_rectangle(clusterarea->window, gc,
		     1, 0, 0, width, height);
  
  if(what > 0)
    {
      gdk_gc_set_foreground(gc, &green);
      gdk_gc_set_background(gc, &green);
      gdk_gc_set_fill(gc, GDK_SOLID);
      n = 0;
      for(w = WORKERS; w; w = w->next)
	if( (w->code_id == current_code_id) &&
	    (w->path_len == current_path_len) )
	  {
	    gdk_draw_rectangle(clusterarea->window, gc, 1, 
			       1, SEPARATOR+(SEPARATOR+2*WIDTH)*n, 
			       (w->nbtrue_tot*(width-2))/what, WIDTH);
	    if(last_what > 0)
	      gdk_draw_rectangle(clusterarea->window, gc, 1, 
				 1, SEPARATOR+(SEPARATOR+2*WIDTH)*n+WIDTH, 
				 (w->nbtrue_last*(width-2))/last_what, WIDTH);
	    n++;
	  }
      
      gdk_gc_set_foreground(gc, &red);
      gdk_gc_set_background(gc, &red);
      gdk_gc_set_fill(gc, GDK_SOLID);
      n = 0;
      for(w = WORKERS; w; w = w->next)
	if( (w->code_id == current_code_id) &&
	    (w->path_len == current_path_len) )
	  {
	    gdk_draw_rectangle(clusterarea->window, gc, 1,
			       (w->nbtrue_tot*(width-2))/what+1, SEPARATOR+(SEPARATOR+2*WIDTH)*n, 
			       (w->nbfalse_tot*(width-2))/what, WIDTH);
	    if(last_what > 0)
	      gdk_draw_rectangle(clusterarea->window, gc, 1,
				 (w->nbtrue_last*(width-2))/last_what+1, SEPARATOR+(SEPARATOR+2*WIDTH)*n+WIDTH, 
				 (w->nbfalse_last*(width-2))/last_what, WIDTH);
	    w->nbtrue_last = w->nbfalse_last = 0;
	    n++;
	  }
    }

  return TRUE;
}

static gboolean on_timeout(gpointer data)
{
  char value[256];
  time_t now;
  int n;

  sprintf(value, "%d", current_job_false + current_job_true);
  gtk_entry_set_text(GTK_ENTRY(nbverified), value);
  sprintf(value, "%d", current_job_true);
  gtk_entry_set_text(GTK_ENTRY(nbgood), value);
  
  sprintf(value, "%g", (double)current_job_true / (double)(current_job_true+current_job_false) );
  gtk_label_set_text(GTK_LABEL(estprob), value);

  sprintf(value, "%g", prn_to_confidence(AppRatio, current_job_true+current_job_false) );
  gtk_label_set_text(GTK_LABEL(current_confidence), value);

  n = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbpath));
  gtk_progress_set_percentage ( GTK_PROGRESS(progressbar),
				(float)(min(n, current_job_false + current_job_true))/
				(float)n );

  gtk_widget_modify_style (finalbox, blue_over_gray);
  gtk_widget_modify_style (finalresult, blue_over_gray);
  now = time(NULL);
  sprintf(value, "testing (%02d:%02d:%02d)", (int)((now-starttime)/3600),
	  (int)(((now-starttime)/60)%60), (int)((now-starttime)%60));
  gtk_label_set_text(GTK_LABEL(finalresult), value);

  gtk_drawing_area_size(GTK_DRAWING_AREA(clusterarea),
			clusterarea->allocation.width,
			clusterarea->allocation.height);

  return TRUE;
}

static gboolean on_child_moves (GIOChannel   *source,
				GIOCondition  condition,
				gpointer      data)
{
  int *pid = (int*)data;
  int res;
  char line[512];
  
  if(condition & G_IO_IN) {
    res = read( g_io_channel_unix_get_fd(source), line, 511 );
    if(res <= 0)
      {
	if(res < 0)
	  perror("read");
	goto quit;
      }
    line[res] = 0;
    gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
    gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, line);
  }
  if( (condition & G_IO_ERR) || (condition & G_IO_HUP) )
    {
      debug("HUPped\n");
      sprintf(line, "Compilation interrupted");
      gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, line);
      kill(*pid, SIGKILL);
    quit:
      debug("waiting %d\n", *pid);
      waitpid( *pid, &res, 0 );
      *pid = res;
      gtk_main_quit();
      return FALSE;
    }
  return TRUE;
}

static void on_interrupt_clicked(GtkButton *button, gpointer user_data)
{
  int *pid = (int*)user_data;
  kill(*pid, SIGKILL);
}

void on_compile_clicked(GtkButton *button, gpointer user_data)
{
  FILE *f = NULL;
  struct compiler *comp;
  char *strategy_name;
  GIOChannel *ch;
  pid_t pid;
  int fd;
  guint w;
  GtkWidget *dw, *label, *btn;

  strategy_name = gtk_editable_get_chars(GTK_EDITABLE(GTK_COMBO(compile_strategy)->entry),
			     0, -1);
  comp = get_compiler_from_name(strategy_name);
  if(!comp)
    {
      sprintf(msg, "Unable to find a compiler strategy with name %s", strategy_name);
      goto end;
    }

  clean_PMFILE();
  if(LTL)
    free_LTL();

  debug("parsing reactive modules program\n");
  rm_in = fopen( model_filename, "r");
  if(!rm_in || rm_parse() )
    {
      sprintf(msg, "Parse error in %s, line %d", model_filename, rm_lineno);
      goto end;
    }
  fclose( rm_in );

  debug("parsing ltl formula\n");
  ltl_in = fopen( prop_filename, "r");
  if(!ltl_in || ltl_parse() )
    {
      sprintf(msg, "Parse error in %s, line %d", prop_filename, ltl_lineno);
      goto end;
    }
  fclose(ltl_in);

  do {
    current_code_id += (rand()%0xffffff) + 1;
  } while(current_code_id == 0);

  f = fopen( CODE_SOURCE, "w");
  switch (generate_code_with_compiler(f, LTL, PMFILE, comp))
    {
    case 0:
      break;
    case -1:
      sprintf(msg, "Error in %s, while generating code with strategy %s", model_filename, comp->name);
      goto end;
    case -2:
      sprintf(msg, "Error in %s, while generating code", prop_filename);
      goto end;
    default:
      sprintf(msg, "Internal error in generate_code_with_compiler : unexpected return code");
      goto end;
    }
  fclose(f);
  f = NULL;

  debug("compiling\n");
  gtk_widget_set_sensitive( window, FALSE );
  dw = gtk_dialog_new();
  label = gtk_label_new("Running "COMPILE_CODE);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dw)->vbox), label, TRUE, TRUE, 0);
  gtk_widget_show(label);
  btn = gtk_button_new_with_label("Interrupt");
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dw)->action_area), btn, TRUE, TRUE, 0);
  gtk_widget_show(btn);
  gtk_window_set_title(GTK_WINDOW(dw), "Compiling");
  gtk_widget_show_all(dw);
  gtk_window_set_modal(GTK_WINDOW(dw), TRUE);
  while( gtk_events_pending() ) gtk_main_iteration();

  pid = forkpty(&fd, NULL, NULL, NULL);
  if(pid == -1)
    {
      sprintf(msg, "Error : could not fork to execute "COMPILE_CODE" : %s",
	      strerror(errno));
      goto end;
    }
  if(pid == 0)
    {
      if( system(COMPILE_CODE) )
	perror(COMPILE_CODE);
      _exit(0); /* Gtk redefines exit ! Do not call in childrens */
    }

  ch = g_io_channel_unix_new(fd);
  w  = g_io_add_watch(ch, G_IO_IN|G_IO_ERR|G_IO_HUP, 
		      on_child_moves, &pid);
  gtk_signal_connect( GTK_OBJECT(btn), "clicked",
		      GTK_SIGNAL_FUNC(on_interrupt_clicked), &pid);
  gtk_main ();
  gtk_widget_destroy(dw);
  gtk_widget_set_sensitive( window, TRUE );
  //g_source_remove(w);
  g_io_channel_unref(ch);
  if(pid != 0)
    {
      sprintf(msg, "Compilation aborted or failed");
      goto end;
    }

  debug("compiled\n");
  gui_status |= COMPILED;
  update_sensitive_widgets();

  sprintf(msg, "Model and property compiled successfully into "CODE_BINARY" using startegy \"%s\" ", 
	  strategy_name);

 end:
  g_free(strategy_name);
  if(f) fclose(f);
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
  return;
}

void on_dojob_clicked(GtkButton *button, gpointer user_data)
{
  struct worker_stat *w;
  gtk_spin_button_update(GTK_SPIN_BUTTON(pathlen));
  current_path_len = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(pathlen));
  current_job_false = 0;
  current_job_true  = 0;
  timer = g_timeout_add(500, on_timeout, NULL);
  
  gtk_widget_modify_style (finalbox, blue_over_gray);
  gtk_widget_modify_style (finalresult, blue_over_gray);
  gtk_label_set_text(GTK_LABEL(finalresult), "testing (00:00:00)");

  for(w = WORKERS; w; w = w->next)
    {
      w->code_id = 0;
      w->path_len = 0;
    }

  gui_status |= RUNNING;
  update_sensitive_widgets();

  NbPath = GTK_ADJUSTMENT(nbpath_adj)->value;

  starttime = time(NULL);

  sprintf(msg, "Testing if with confidence %g, the property hold with probability %g ± %g over paths of length %d",
	  Confidence, Prob, AppRatio, current_path_len);
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
}

void on_stopjob_clicked(GtkButton *button, gpointer user_data)
{
  char *p;
  double b, eps;
  char msg[1024];
  time_t now;
  int d;
  struct worker_stat *w;

  g_source_remove(timer);
  on_timeout(NULL);
  
  p = gtk_entry_get_text(GTK_ENTRY(prob));
  b = atof(p);

  p = gtk_entry_get_text(GTK_ENTRY(appratio));
  eps = atof(p);

  sprintf(msg, "Testing finished (by user or complete)");
  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);
  gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);

  d = current_job_true+current_job_false;
  if(  b*(1-eps) < (float)current_job_true / (float)(current_job_true+current_job_false) )
    {
      /* ACCEPT */
      if( prn_to_confidence(AppRatio, d) <= Confidence )
	{
	  gtk_widget_modify_style (finalbox, black_over_green);
	  gtk_widget_modify_style (finalresult, black_over_green);      

	} else {
	  gtk_widget_modify_style (finalbox, red_over_green);
	  gtk_widget_modify_style (finalresult, red_over_green);	  
	}
      now = time(NULL);

      sprintf(msg, "The probability that the property is true is greater than (or equal to) %g with confidence %g.\nTotal computation time : (%02d:%02d:%02d)",
	      b,  prn_to_confidence(AppRatio, d),
	      (int)((now-starttime)/3600), (int)(((now-starttime)/60)%60), (int)((now-starttime)%60));
      gtk_label_set_text(GTK_LABEL(finalresult), msg);

    }
  else
    {
      /* REJECT */
      gtk_widget_modify_style (finalbox, black_over_red);
      gtk_widget_modify_style (finalresult, black_over_red);
      now = time(NULL);
      sprintf(msg, "Either the property is false, or paths of length %s does not permit to verify the property.\nTotal computation time : (%02d:%02d:%02d)",
	      gtk_entry_get_text(GTK_ENTRY(pathlen)), 
	      (int)((now-starttime)/3600), (int)(((now-starttime)/60)%60), (int)((now-starttime)%60));
      gtk_label_set_text(GTK_LABEL(finalresult), msg);
    }

  gui_status &= ~RUNNING;
  update_sensitive_widgets();

  for(w = WORKERS; w; w = w->next)
    {
      w->code_id = 0;
      w->path_len = 0;
    }
  last_what = -1;
}

void on_prop_changed(GtkEditable *editable,
		     gpointer user_data)
{
  gui_status &= ~PROP_SYNC;
  update_sensitive_widgets();
}

void on_model_changed(GtkEditable *editable,
		      gpointer user_data)
{
  gui_status &= ~MODEL_SYNC;
  update_sensitive_widgets();
}

static int dontcalculate;

void on_calculate_formula(GtkEditable *editable,
			  gpointer user)
{
  double v;
  double op, or, oc;
  char value[1024];
  unsigned long long d;
  char *p;
      
  if(dontcalculate)
    return;

  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);

  op = Prob;
  v = strtod(gtk_entry_get_text(GTK_ENTRY(prob)), &p);
  if( (v >= 0.0) && (v <= 1.0) && (*p == 0) )
    {
      Prob = v;
    }
  else
    {
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, "malformed target probability");
      return;
    }

  or = AppRatio;
  v = strtod(gtk_entry_get_text(GTK_ENTRY(appratio)), &p);
  if( (v >= 0.0) && (v <= 1.0)  && (*p == 0) )
    {
      AppRatio = v;
    }
  else
    {
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, "malformed Approximation Ratio");
      return;
    }

  oc = Confidence;
  v = strtod(gtk_entry_get_text(GTK_ENTRY(confidence)), &p);
  if( (v >= 0.0) && (v <= 1.0) && (*p == 0) )
    {
      Confidence = v;
    }
  else
    {
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, "malformed confidence");
      return;
    }

  d = prc_to_nbpath(AppRatio, Confidence);
  if(d < (unsigned long long)0x7fffffff)
    {
      NbPath = (int)d;
      dontcalculate = 1;
      gtk_adjustment_set_value(GTK_ADJUSTMENT(nbpath_adj), NbPath);
      dontcalculate = 0;
    }
  else
    {
      sprintf(msg, "Exceeding maximum path number");
      gtk_statusbar_push(GTK_STATUSBAR(statusbar), cid, msg);
      dontcalculate = 1;
      Confidence = oc;  sprintf(value, "%g", Confidence); gtk_entry_set_text(GTK_ENTRY(confidence), value);
      AppRatio = or;    sprintf(value, "%g", AppRatio);   gtk_entry_set_text(GTK_ENTRY(appratio), value);
      Prob = op;        sprintf(value, "%g", Prob);       gtk_entry_set_text(GTK_ENTRY(prob), value);
      gtk_adjustment_set_value(GTK_ADJUSTMENT(nbpath_adj), prc_to_nbpath(AppRatio, Confidence));
      dontcalculate = 0;
    }
}

void on_inverse_formula(GtkEditable *editable,  gpointer user)
{
  double v;
  char value[1024];
  unsigned long long d;
      
  if(dontcalculate)
    return;

  gtk_statusbar_pop(GTK_STATUSBAR(statusbar), cid);

  d = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbpath));
  v = prn_to_confidence(AppRatio, d);
  Confidence = v;
  sprintf(value, "%g", v);
  dontcalculate = 1;
  gtk_entry_set_text(GTK_ENTRY(confidence), value);
  dontcalculate = 0;
}
