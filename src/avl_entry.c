#include <gtk/gtk.h>

#include <avl_entry.h>
#include <avl_text_view.h>

struct _AvlEntry {
	GtkEntry parent;

	GtkTextView *text_view;

	//This is the function that each entry
	//	will call when they are activated.
	//The gchar* returned will be printed on text view.
	//The argument passed to the function is the entry text.
	gchar *(*function_to_call)(const gchar *);
};

G_DEFINE_TYPE(AvlEntry, avl_entry, GTK_TYPE_ENTRY);

void avl_entry_init(AvlEntry *entry){
	gtk_entry_set_buffer(GTK_ENTRY(entry), gtk_entry_buffer_new(NULL, -1));
	entry->function_to_call = NULL;
}

void avl_entry_class_init(AvlEntryClass *klass){
}

void avl_entry_activate(AvlEntry *entry){
	const gchar *entry_text;
	gchar *print_text;
	
	if(entry->function_to_call){
		entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
		print_text = entry->function_to_call(entry_text);
		avl_text_view_print_text(entry->text_view, print_text);
		g_free(print_text);
	}
	
	gtk_entry_set_text(GTK_ENTRY(entry), "");
}

AvlEntry *avl_entry_new(gchar *string, GtkTextView *view, 
		gchar *(function)(const gchar *)){
	AvlEntry *entry;
	entry = g_object_new(AVL_TYPE_ENTRY, "placeholder-text", string, NULL);
	entry->text_view = view;
	entry->function_to_call = function;

	g_signal_connect(entry, "activate", G_CALLBACK(avl_entry_activate), NULL);

	return entry;
}
