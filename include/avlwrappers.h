#ifndef _AVLWRAPPERS_H
#define _AVLWRAPPERS_H

/* FUNCTIONS FOR THE GTK APPLICATION. YES IT WILL BE HARD CODED */

#include <gtk/gtk.h>

gchar *insert_app_wrapper(const gchar *string);
gchar *search_app_wrapper(const gchar *string);
gchar *remove_app_wrapper(const gchar *string);
gchar *successor_app_wrapper(const gchar *string);
gchar *predecessor_app_wrapper(const gchar *string);
gchar *max_app_wrapper(void);
gchar *min_app_wrapper(void);
gchar *preorder_app_wrapper(void);
gchar *inorder_app_wrapper(void);
gchar *postorder_app_wrapper(void);
void parse_wrapper(gchar *filename);

#endif
