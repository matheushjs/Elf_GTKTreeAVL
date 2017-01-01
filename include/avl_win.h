#ifndef _AVL_WIN_H
#define _AVL_WIN_H

#include <gtk/gtk.h>

#define AVL_TYPE_WIN avl_win_get_type()
G_DECLARE_FINAL_TYPE(AvlWin, avl_win, AVL, WIN, GtkApplicationWindow);

AvlWin *avl_win_new(GtkApplication *);

#endif
