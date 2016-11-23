#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <glob.h>

#include "gtkbfs.h"

static void gtk_bfs_destroy(GtkObject *o, gpointer null)
{
  GtkBFS *fs = GTK_BFS(o);
  GList *l, *p;
  for(l = fs->history; l; l = g_list_remove(l, l->data))
    free( (char*)l->data );
  for(l = fs->files_types; l; l = g_list_remove(l, l->data))
    {
      free( BFS_FILE_TYPE(l)->name );
      for( p = BFS_FILE_TYPE(l)->patterns; p; p = g_list_remove(p, p->data) )
	free( (char*)p->data );
      free( BFS_FILE_TYPE(l) );
    }
}

static void gtk_bfs_update_lists(GtkBFS *fs)
{
  char *p;
  int i;
  GList *l;
  BFSFileType *current_filetype;
  glob_t globres;
  char **text;
  char patternallocated;

  text = (char**)malloc(2*sizeof(char*));
  text[0] = (char*)malloc(FILENAME_MAX+4);
  text[1] = NULL;

  getcwd(text[0], FILENAME_MAX);
  text[0][strlen(text[0])+1] = 0;
  text[0][strlen(text[0])] = '/';

  p = gtk_editable_get_chars(GTK_EDITABLE( GTK_COMBO(fs->combo)->entry ), 0, -1);
  for( l = fs->files_types; l; l = l->next)
    if( !strcmp( BFS_FILE_TYPE(l)->name, p ) )
      break;
  if(l == NULL)
    {
      current_filetype = (BFSFileType *)calloc(sizeof(BFSFileType), 1);
      current_filetype->patterns = g_list_append(current_filetype->patterns, p);
      patternallocated = 1;
    }
  else
    {
      current_filetype = BFS_FILE_TYPE(l);
      patternallocated = 0;
    }

  if( !fs->pwd || strcmp(fs->pwd, text[0]) )
    {
      if(fs->pwd) free(fs->pwd);
      fs->pwd = strdup(text[0]);
      glob( ".*", GLOB_MARK, NULL, &globres);
      glob( "*", GLOB_MARK | GLOB_APPEND, NULL, &globres);
      gtk_clist_freeze(GTK_CLIST(fs->dirlist));
      gtk_clist_clear( GTK_CLIST(fs->dirlist));
      for(i = 0; i < globres.gl_pathc; i++)
	if( globres.gl_pathv[i][strlen(globres.gl_pathv[i])-1] == '/' )
	  {
	    globres.gl_pathv[i][strlen(globres.gl_pathv[i])-1] = 0;
	    strcpy(text[0], globres.gl_pathv[i]);
	    gtk_clist_append( GTK_CLIST(fs->dirlist), text );
	  }
      gtk_clist_thaw(GTK_CLIST(fs->dirlist));
      globfree(&globres);
    }

  for( l = current_filetype->patterns; l; l = l->next )
    glob( (char*)l->data, 
	  GLOB_MARK | GLOB_TILDE | ((l==current_filetype->patterns)?0:GLOB_APPEND),
	  NULL, &globres );
  gtk_clist_freeze(GTK_CLIST(fs->filelist));
  gtk_clist_clear( GTK_CLIST(fs->filelist));
  for(i = 0; i < globres.gl_pathc; i++)
    if( globres.gl_pathv[i][strlen(globres.gl_pathv[i])-1] != '/' )
      {
	strcpy(text[0], globres.gl_pathv[i]);
	gtk_clist_append( GTK_CLIST(fs->filelist), text);
      }
  globfree(&globres);
  gtk_clist_thaw(GTK_CLIST(fs->filelist));
  
  if(patternallocated)
    {
      g_list_free(current_filetype->patterns);
      free(current_filetype);
    }
  free(text[0]);
  free(text);
  free(p);
  current_filetype = NULL;
}

static void gtk_bfs_show(GtkWidget *widget, gpointer null)
{
  char *pwd;
  GtkBFS *fs = GTK_BFS(widget);
  guint selected;

  selected = (guint)gtk_object_get_user_data(GTK_OBJECT(gtk_menu_get_active( GTK_MENU(fs->menu) )));
  pwd = g_list_nth_data(fs->history, selected);
  if( chdir(pwd) )
    perror(pwd);

  gtk_bfs_update_lists(fs);
}

static void gtk_bfs_entry_changed(GtkEditable *editable, GtkBFS *fs)
{
  gtk_bfs_update_lists(fs);
}

static void gtk_bfs_class_init( GtkBFS *class )
{
  
}

static void gtk_bfs_history_activate( GtkMenuItem *item, GtkBFS *fs )
{
  guint selected;
  char *pwd;

  selected = (guint)gtk_object_get_user_data(GTK_OBJECT(item));
  pwd = g_list_nth_data(fs->history, selected);
  if( chdir(pwd) )
    perror(pwd);
  gtk_bfs_update_lists(fs);
}

static void gtk_bfs_ok_clicked( GtkButton *b, GtkBFS *fs )
{
  char *p;
  int n;

  p = gtk_editable_get_chars(GTK_EDITABLE( fs->entry ), 0, -1);
  if(fs->filename) free(fs->filename);  
  fs->filename = (char*)malloc(strlen(fs->pwd)+4+strlen(p));
  strcpy(fs->filename, fs->pwd);

  while( (strlen(fs->filename) > 1) && (fs->filename[strlen(fs->filename)-1] == '/') )
    fs->filename[strlen(fs->filename)-1] = 0;
  if( strcmp(p, "") )
    {
      strcat(fs->filename, "/");
      strcat(fs->filename, p);
    }
  else
    strcat(fs->filename, "/");

  n = gtk_bfs_add_to_history(fs, fs->pwd);
  gtk_bfs_history_set_selected (fs, n);

  free(p);
}

static void gtk_bfs_cancel_clicked( GtkButton *b, GtkBFS *fs )
{
  int n;
  n = gtk_bfs_add_to_history(fs, fs->pwd);
  gtk_bfs_history_set_selected (fs, n);
}

static gboolean gtk_bfs_dirlist_event(GtkCList *dirlist, GdkEvent *event, GtkBFS *fs)
{
  int row, column;
  char *p = NULL;

  if( (event->type == GDK_2BUTTON_PRESS) &&
      (((GdkEventButton*)event)->button == 1) )
    {
      if( gtk_clist_get_selection_info(dirlist, (int)((GdkEventButton*)event)->x, 
				       (int)((GdkEventButton*)event)->y,
				       &row, &column) )
	{
	  gtk_clist_get_text(dirlist, row, column, &p);
	  if( chdir(p) )
	    perror(p);
	  gtk_bfs_update_lists(fs);
	}
    }
  return FALSE;
}

static gboolean gtk_bfs_filelist_event(GtkCList *filelist, GdkEvent *event, GtkBFS *fs)
{
  if( (event->type == GDK_2BUTTON_PRESS) &&
      (((GdkEventButton*)event)->button == 1) )
    {
      gtk_button_clicked( GTK_BUTTON(fs->ok) );
      return TRUE;
    }
  return FALSE;
}

static void gtk_bfs_filelist_select(GtkCList *clist,
				    gint row,
				    gint column,
				    GdkEventButton *event,
				    GtkBFS *fs)
{
  char *p = NULL;
  int r;

  gtk_clist_get_text(clist, row, column, &p);
  gtk_editable_delete_text( GTK_EDITABLE(fs->entry), 0, -1);
  gtk_editable_insert_text( GTK_EDITABLE(fs->entry), p, strlen(p), &r);
}

static void gtk_bfs_filelist_unselect(GtkCList *clist,
				      gint row,
				      gint column,
				      GdkEventButton *event,
				      GtkBFS *fs)
{
  gtk_editable_delete_text( GTK_EDITABLE(fs->entry), 0, -1);
}

static void gtk_bfs_init( GtkBFS *fs )
{
  /*  +-------------------------+ <-vbox */
  /*  +       OptionMenu        + <-omenu*/
  /*  +-------------------------+        */
  /*  +            |            +        */
  /*  +  dirlist   |  filelist  + <-hbox */
  /*  +            |            +        */
  /*  +-------------------------+        */
  /*  +label | entry            + <-table*/
  /*  +label | Combo            +        */
  /*  +-------------------------+        */
  /*  +    OK      |   Cancel <-buttonbox*/
  /*  +-------------------------+        */
  GtkWidget *vbox, *hbox, *table, *buttonbox, *label, *sw;
  static char *titledir = "Directories";
  static char *titlefile = "Files";
  char *pwd;
  int n;
  
  vbox = gtk_vbox_new( FALSE, 0 );
   gtk_container_add( GTK_CONTAINER(fs), vbox );
  
   fs->historymenu = gtk_option_menu_new();
    fs->menu = gtk_menu_new();
    gtk_widget_show(fs->menu);
    gtk_option_menu_set_menu(GTK_OPTION_MENU(fs->historymenu), fs->menu);
    gtk_box_pack_start(GTK_BOX(vbox), fs->historymenu, FALSE, FALSE, 2);
   gtk_widget_show(fs->historymenu);

   hbox = gtk_hbox_new( TRUE, 1 );
    sw = gtk_scrolled_window_new(NULL, NULL);
     fs->dirlist = gtk_clist_new_with_titles(1, &titledir);
      gtk_container_add( GTK_CONTAINER(sw), fs->dirlist );
     gtk_widget_show(fs->dirlist);
     gtk_box_pack_start(GTK_BOX(hbox), sw, TRUE, TRUE, 1);
     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC,
				    GTK_POLICY_AUTOMATIC);
    gtk_widget_show(sw);
    sw = gtk_scrolled_window_new(NULL, NULL);
     fs->filelist = gtk_clist_new_with_titles(1, &titlefile);
      gtk_container_add( GTK_CONTAINER(sw), fs->filelist );
     gtk_widget_show(fs->filelist);
     gtk_box_pack_start(GTK_BOX(hbox), sw, TRUE, TRUE, 1);
     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC,
				    GTK_POLICY_AUTOMATIC);
    gtk_widget_show(sw);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    gtk_widget_set_usize(hbox, -1, 200);
   gtk_widget_show(hbox);

   table = gtk_table_new(2, 2, FALSE);
    label = gtk_label_new("selection :");
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, 0, 1, 
		     GTK_SHRINK,
		     GTK_EXPAND|GTK_SHRINK|GTK_FILL,
		     0, 0);
    gtk_widget_show(label);
    fs->entry = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table), fs->entry, 1, 2, 0, 1,  
		     GTK_EXPAND|GTK_SHRINK|GTK_FILL,
		     GTK_EXPAND|GTK_SHRINK|GTK_FILL,
		     0, 0);
    gtk_widget_show(fs->entry);
    label = gtk_label_new("Files types :");
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, 1, 2,  
		     GTK_SHRINK,
		     GTK_EXPAND|GTK_SHRINK|GTK_FILL,
		     0, 0);
    gtk_widget_show(label);
    fs->combo = gtk_combo_new();
    gtk_table_attach(GTK_TABLE(table), fs->combo, 1, 2, 1, 2,  
		     GTK_EXPAND|GTK_SHRINK|GTK_FILL,
		     GTK_EXPAND|GTK_SHRINK|GTK_FILL,
		     0, 0);
    gtk_widget_show(fs->combo);
    gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 0);
   gtk_widget_show(table);

   buttonbox = gtk_hbutton_box_new();
    gtk_hbutton_box_set_layout_default(GTK_BUTTONBOX_SPREAD);
    fs->ok = gtk_button_new_with_label("OK");
     gtk_box_pack_start(GTK_BOX(buttonbox), fs->ok, FALSE, FALSE, 2);
    gtk_widget_show(fs->ok);
    fs->cancel = gtk_button_new_with_label("CANCEL");
     gtk_box_pack_start(GTK_BOX(buttonbox), fs->cancel, FALSE, FALSE, 2);
    gtk_widget_show(fs->cancel);
    gtk_box_pack_start(GTK_BOX(vbox), buttonbox, FALSE, FALSE, 1);
   gtk_widget_show(buttonbox);
  gtk_widget_show(vbox);

  fs->history = NULL;
  fs->files_types = NULL;

  gtk_signal_connect(GTK_OBJECT(fs), "destroy",
		     GTK_SIGNAL_FUNC(gtk_bfs_destroy), NULL);
  gtk_signal_connect(GTK_OBJECT(fs), "show",
		     GTK_SIGNAL_FUNC(gtk_bfs_show), NULL);
  gtk_signal_connect(GTK_OBJECT( GTK_COMBO(fs->combo)->entry ), "changed",
		     GTK_SIGNAL_FUNC(gtk_bfs_entry_changed), fs );
  gtk_signal_connect(GTK_OBJECT( fs->ok ), "clicked",
		     GTK_SIGNAL_FUNC(gtk_bfs_ok_clicked), fs );
  gtk_signal_connect(GTK_OBJECT( fs->cancel ), "clicked",
		     GTK_SIGNAL_FUNC(gtk_bfs_cancel_clicked), fs );
  gtk_signal_connect(GTK_OBJECT( fs->dirlist ), "event",
		     GTK_SIGNAL_FUNC(gtk_bfs_dirlist_event), fs );
  gtk_signal_connect(GTK_OBJECT( fs->filelist ), "event",
		     GTK_SIGNAL_FUNC(gtk_bfs_filelist_event), fs );
  gtk_signal_connect(GTK_OBJECT( fs->filelist ), "select-row",
		     GTK_SIGNAL_FUNC(gtk_bfs_filelist_select), fs );
  gtk_signal_connect(GTK_OBJECT( fs->filelist ), "unselect-row",
		     GTK_SIGNAL_FUNC(gtk_bfs_filelist_unselect), fs );

  fs->pwd = NULL;
  pwd = getcwd(NULL, 0);
  n = gtk_bfs_add_to_history(fs, pwd);
  free(pwd);
  gtk_bfs_history_set_selected (fs, n);

  fs->filename = NULL;
}

guint gtk_bfs_get_type()
{
  static guint bfs_type = 0;
 
  if( !bfs_type )
    {
      GtkTypeInfo bfs_info =
        {
          "GtkBFS",
          sizeof(GtkBFS),
          sizeof(GtkBFSClass),
          (GtkClassInitFunc) gtk_bfs_class_init,
          (GtkObjectInitFunc) gtk_bfs_init,
          (GtkArgSetFunc) NULL,
          (GtkArgGetFunc) NULL
        };
 
      bfs_type = gtk_type_unique( gtk_window_get_type(), &bfs_info );
  }
 
  return bfs_type;
}

GtkWidget *gtk_bfs_new(const gchar *title)
{
  GtkBFS *fs = GTK_BFS( gtk_object_newv (gtk_bfs_get_type(), 0, NULL) );
  gtk_window_set_title( GTK_WINDOW(fs), title );
  return GTK_WIDGET(fs);
}

void gtk_bfs_clear_filetypes(GtkBFS *fs)
{
  GList *l, *p;
  for(l = fs->files_types; l; l = g_list_remove(l, l->data))
    {
      free( BFS_FILE_TYPE(l)->name );
      for( p = BFS_FILE_TYPE(l)->patterns; p; p = g_list_remove(p, p->data) )
	free( (char*)p->data );
      free( BFS_FILE_TYPE(l) );
    }
  fs->files_types = l;
}

void gtk_bfs_add_filetype(GtkBFS *fs, char *typename, char *pattern)
{
  GList *l;
  BFSFileType *ft;

  for(l = fs->files_types; l; l = l->next)
    if( !strcmp(typename, BFS_FILE_TYPE(l)->name) )
      break;
  if(!l) {
    ft = (BFSFileType*)calloc(sizeof(BFSFileType), 1);
    ft->name = strdup(typename);
    fs->files_types = g_list_append(fs->files_types, ft);
  } else
    ft = BFS_FILE_TYPE(l);
  ft->patterns = g_list_append(ft->patterns, strdup(pattern));
}

void gtk_bfs_update(GtkBFS *fs)
{
  GList *l, *p;
  GtkWidget *label, *item;
  static char *string = NULL;
  static int   allocated = 0;
  int len;

  l = gtk_container_children(GTK_CONTAINER(GTK_COMBO(fs->combo)->list));
  for(; l; l = l->next)
    gtk_container_remove(GTK_CONTAINER(GTK_COMBO(fs->combo)->list), GTK_WIDGET(l->data));
  for(l = fs->files_types; l; l = l->next)
    {
      len = strlen(BFS_FILE_TYPE(l)->name)+6;
      for(p = BFS_FILE_TYPE(l)->patterns; p; p=p->next)
	len += strlen( (char*)p->data ) + 2;
      if( len > allocated )
	string = (char*)realloc(string, allocated = len+1);
      sprintf(string, "%s (", BFS_FILE_TYPE(l)->name);
      for(p = BFS_FILE_TYPE(l)->patterns; p; p=p->next)
	{
	  strcat(string, (char*)p->data);
	  if( p->next ) strcat(string, ", ");
	  else strcat(string, ")");
	}
      label = gtk_label_new(string);
      gtk_widget_show(label);
      item = gtk_list_item_new();
      gtk_container_add (GTK_CONTAINER (item), label);
      gtk_widget_show (item);
      gtk_combo_set_item_string (GTK_COMBO (fs->combo), GTK_ITEM (item), BFS_FILE_TYPE(l)->name); 
      gtk_container_add (GTK_CONTAINER (GTK_COMBO (fs->combo)->list), item);
    }
}

int gtk_bfs_add_to_history(GtkBFS *fs, char *path)
{
  struct stat s;
  GtkWidget *menuitem;
  char *rp = strdup(path);
  GList *l;

  while( (strlen(rp) > 1) && (rp[strlen(rp)-1] == '/' ) )
    rp[strlen(rp)-1] = 0;
  
  for(l = fs->history; l; l = l->next)
    if( !strcmp( (char*)l->data, rp ) )
      return -1;
  
  if(stat(rp, &s) < 0)
    return -1;
  if( S_ISDIR(s.st_mode) )
    {
      menuitem = gtk_menu_item_new_with_label(rp);
      gtk_widget_show(menuitem);
      fs->history = g_list_append(fs->history, rp);
      gtk_object_set_user_data( GTK_OBJECT(menuitem), (gpointer)g_list_index(fs->history, rp) );
      gtk_menu_append (GTK_MENU(fs->menu), menuitem);
      gtk_signal_connect(GTK_OBJECT(menuitem), "activate",
			 GTK_SIGNAL_FUNC(gtk_bfs_history_activate), fs);
      return g_list_index(fs->history, rp);
    }  
  return -1;
}

void gtk_bfs_history_set_selected(GtkBFS *fs, int nb)
{
  if( (nb >= 0) && (nb < g_list_length(fs->history)) )
    gtk_option_menu_set_history (GTK_OPTION_MENU(fs->historymenu), nb);
}

static gboolean gtk_select_delete (GtkWidget *widget,
                                   GdkEvent *event,
                                   GtkBFS *fs)
{
  gtk_main_quit(); 
  fs->agreed = 0;
  return TRUE;
}

static void gtk_select_ok(GtkButton *b, GtkBFS *fs)
{
  fs->agreed = 1;
  gtk_main_quit();
}

static void gtk_select_cancel(GtkButton *b, GtkBFS *fs)
{
  fs->agreed = 0;
  gtk_main_quit();
}

char * gtk_bfs_select(GtkBFS *fs)
{
  gtk_window_set_modal(GTK_WINDOW(fs), TRUE);
  gtk_widget_show(GTK_WIDGET(fs));

  gtk_signal_connect(GTK_OBJECT(fs->ok), "clicked",
		     GTK_SIGNAL_FUNC(gtk_select_ok), fs);
  gtk_signal_connect(GTK_OBJECT(fs->cancel), "clicked",
		     GTK_SIGNAL_FUNC(gtk_select_cancel), fs);
  gtk_signal_connect(GTK_OBJECT(fs), "delete-event",
		     GTK_SIGNAL_FUNC(gtk_select_delete), fs);

  gtk_main();

  gtk_widget_hide(GTK_WIDGET(fs));
  gtk_window_set_modal(GTK_WINDOW(fs), FALSE);

  if(fs->agreed)
    return strdup(fs->filename);
  return NULL;
}
