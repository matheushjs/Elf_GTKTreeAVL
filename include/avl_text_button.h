#ifndef _AVL_TEXT_BUTTON_H
#define _AVL_TEXT_BUTTON_H

#include <avl_text_box.h>

#define AVL_TYPE_TEXT_BUTTON avl_text_button_get_type()
G_DECLARE_FINAL_TYPE(AvlTextButton, avl_text_button, AVL, TEXT_BUTTON, GtkButton);

AvlTextButton *avl_text_button_new(gchar *label, AvlTextBox *box,
		gchar *(*function)(void));

#endif
