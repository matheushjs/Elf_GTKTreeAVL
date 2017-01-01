#ifndef _AVL_ENTRY_BUTTON_H
#define _AVL_ENTRY_BUTTON_H

#include <gtk/gtk.h>
#include <avl_entry.h>

#define AVL_TYPE_ENTRY_BUTTON avl_entry_button_get_type()
G_DECLARE_FINAL_TYPE(AvlEntryButton, avl_entry_button, AVL, ENTRY_BUTTON, GtkButton);

AvlEntryButton *avl_entry_button_new(gchar *label, AvlEntry *entry);

#endif
