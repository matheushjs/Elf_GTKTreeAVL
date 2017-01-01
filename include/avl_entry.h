#ifndef _AVL_ENTRY_H
#define _AVL_ENTRY_H

#include <gtk/gtk.h>

#define AVL_TYPE_ENTRY avl_entry_get_type()
G_DECLARE_FINAL_TYPE(AvlEntry, avl_entry, AVL, ENTRY, GtkEntry);

void avl_entry_activate(AvlEntry *entry);
AvlEntry *avl_entry_new(gchar *, GtkTextView *,
		gchar *(*function)(const gchar *));

#endif
