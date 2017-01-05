#ifndef _AVL_ABOUT_WIN_H
#define _AVL_ABOUT_WIN_H

#include <gtk/gtk.h>

#define AVL_TYPE_ABOUT_WIN avl_about_win_get_type()
G_DECLARE_FINAL_TYPE(AvlAboutWin, avl_about_win, AVL, ABOUT_WIN, GtkAboutDialog);

AvlAboutWin *avl_about_win_new(GtkApplication *app, GtkWindow *transient);

#endif
