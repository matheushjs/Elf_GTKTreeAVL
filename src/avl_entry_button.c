#include <gtk/gtk.h>

#include <avl_entry_button.h>
#include <avl_entry.h>

struct _AvlEntryButton {
	GtkButton parent;
};

G_DEFINE_TYPE(AvlEntryButton, avl_entry_button, GTK_TYPE_BUTTON);

static
void avl_entry_button_init(AvlEntryButton *but){
}

static
void avl_entry_button_class_init(AvlEntryButtonClass *klass){
}

AvlEntryButton *avl_entry_button_new(gchar *label, AvlEntry *entry){
	AvlEntryButton *new;
	new = g_object_new(AVL_TYPE_ENTRY_BUTTON,
			"label", label,
			NULL);
	if(entry)
		g_signal_connect_swapped(new, "clicked", G_CALLBACK(avl_entry_activate), entry);

	return new;
}
