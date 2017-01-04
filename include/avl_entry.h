#ifndef _AVL_ENTRY_H
#define _AVL_ENTRY_H

#include <gtk/gtk.h>
#include <avl_text_box.h>

#define AVL_TYPE_ENTRY avl_entry_get_type()
G_DECLARE_FINAL_TYPE(AvlEntry, avl_entry, AVL, ENTRY, GtkEntry);

void avl_entry_activate(AvlEntry *entry);
AvlEntry *avl_entry_new(gchar *, AvlTextBox *,
		gchar *(*function)(const gchar *));

#endif
