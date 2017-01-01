#ifndef _AVL_APP_H
#define _AVL_APP_H

#include <gtk/gtk.h>

#define AVL_TYPE_APP avl_app_get_type()
G_DECLARE_FINAL_TYPE(AvlApp, avl_app, AVL, APP, GtkApplication);

AvlApp *avl_app_new();

#endif
