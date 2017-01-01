#ifndef AVL_TEXT_VIEW_H
#define AVL_TEXT_VIEW_H

#include <gtk/gtk.h>

#define AVL_TYPE_TEXT_VIEW avl_text_view_get_type()
G_DECLARE_FINAL_TYPE(AvlTextView, avl_text_view, AVL, TEXT_VIEW, GtkTextView);

void avl_text_view_print_text(GtkTextView *view, const gchar *string);
AvlTextView *avl_text_view_new();

#endif
