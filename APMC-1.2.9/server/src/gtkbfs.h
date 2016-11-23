#ifndef __GTK_BETTER_FILESELECTOR_H__
#define __GTK_BETTER_FILESELECTOR_H__
 
#include <gdk/gdk.h>
#include <gtk/gtkwindow.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BFS_FILE_TYPE(list)  ( (BFSFileType*)list->data )

typedef struct _BFSFileType  BFSFileType;
struct _BFSFileType
{
  char *name;
  GList *patterns;
};

 
#define GTK_TYPE_BFS            (gtk_bfs_get_type ())
#define GTK_BFS(obj)            (GTK_CHECK_CAST ((obj), GTK_TYPE_BFS, GtkBFS))
#define GTK_BFS_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_BFS, GtkBFSClass))
#define GTK_IS_BFS(obj)         (GTK_CHECK_TYPE ((obj), GTK_TYPE_BFS))
#define GTK_IS_BFS_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BFS))

typedef struct _GtkBFS       GtkBFS;
typedef struct _GtkBFSClass  GtkBFSClass;
 
struct _GtkBFS
{
  GtkWindow window;
  
  GList *history;
  GList *files_types;

  char *pwd;
  char *filename;
  unsigned char agreed; /* internal for gtk_bfs_select */

  GtkWidget *historymenu, *dirlist, *filelist, *entry, *combo;
  GtkWidget *menu, *ok, *cancel;
};
 
struct _GtkBFSClass
{
  GtkWindowClass parent_class;
};
 
GtkType    gtk_bfs_get_type            (void);
GtkWidget *gtk_bfs_new                 (const gchar      *title);
void       gtk_bfs_clear_filetypes     (GtkBFS *fs);
/* 
 * example : gtk_bfs_add_filetype(fs, "postscript", "*.eps");
 *           gtk_bfs_add_filetype(fs, "postscript", "*.ps");
 */
void       gtk_bfs_add_filetype        (GtkBFS *fs, char *typename, char *pattern);
/*
 * call when finished adding file types
 */
void       gtk_bfs_update(GtkBFS *fs);

int  gtk_bfs_add_to_history(GtkBFS *fs, char *path);
void gtk_bfs_history_set_selected(GtkBFS *fs, int nb);

/*
 * shows the window, let the user select a filename, return the
 * selected filename (NULL if cancel selected ; the directory if no filename
 * selected and OK clicked)
 */
char      *gtk_bfs_select              (GtkBFS *fs);

#ifdef __cplusplus
}
#endif /* __cplusplus */
 
#endif /* __GTK_BETTER_FILESELECTOR_H__ */
