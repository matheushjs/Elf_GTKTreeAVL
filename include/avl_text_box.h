#ifndef AVL_TEXT_BOX_H
#define AVL_TEXT_BOX_H

#include <gtk/gtk.h>

#define AVL_TYPE_TEXT_BOX avl_text_box_get_type()
G_DECLARE_FINAL_TYPE(AvlTextBox, avl_text_box, AVL, TEXT_BOX, GtkBox);

void avl_text_box_print_text(AvlTextBox *view, const gchar *string);
AvlTextBox *avl_text_box_new();

#endif
