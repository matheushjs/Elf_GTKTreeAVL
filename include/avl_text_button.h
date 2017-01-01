#ifndef _AVL_TEXT_BUTTON_H
#define _AVL_TEXT_BUTTON_H

#define AVL_TYPE_TEXT_BUTTON avl_text_button_get_type()
G_DECLARE_FINAL_TYPE(AvlTextButton, avl_text_button, AVL, TEXT_BUTTON, GtkButton);

AvlTextButton *avl_text_button_new(gchar *label, GtkTextView *view,
		gchar *(*function)(void));

#endif
