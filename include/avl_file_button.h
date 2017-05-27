#ifndef _AVL_FILE_BUTTON_H
#define _AVL_FILE_BUTTON_H

#define AVL_TYPE_FILE_BUTTON avl_file_button_get_type()
G_DECLARE_FINAL_TYPE(AvlFileButton, avl_file_button, AVL, FILE_BUTTON, GtkButton);

AvlFileButton *avl_file_button_new(GtkWindow *transient);

#endif
