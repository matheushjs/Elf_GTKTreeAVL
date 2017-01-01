#include <gtk/gtk.h>

#include <avl_text_view.h>

struct _AvlTextView {
	GtkTextView parent;
};

G_DEFINE_TYPE(AvlTextView, avl_text_view, GTK_TYPE_TEXT_VIEW);

static
void buffer_changed_action(AvlTextView *tv){
	GtkTextBuffer *buf;
	GtkTextIter start, end;
	gchar *text;

	buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
	if(gtk_text_buffer_get_line_count(buf) >= 30){
		gtk_text_buffer_get_end_iter(buf, &end);
		gtk_text_buffer_get_iter_at_line(buf, &start, 5);
		text = gtk_text_buffer_get_text(buf, &start, &end, FALSE);
		gtk_text_buffer_set_text(buf, text, -1);
	}
}

void avl_text_view_init(AvlTextView *tv){
	GtkTextBuffer *buf;

	buf = gtk_text_buffer_new(NULL);
	g_signal_connect_swapped(buf, "changed", G_CALLBACK(buffer_changed_action), tv);
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(tv), buf);
}

void avl_text_view_class_init(AvlTextViewClass *klass){
}

void avl_text_view_print_text(GtkTextView *view, const gchar *string){
	GtkTextBuffer *buf;
	GtkTextIter end;

	buf = gtk_text_view_get_buffer(view);
	gtk_text_buffer_get_end_iter(buf, &end);
	gtk_text_buffer_insert(buf, &end, string, -1);
	
	//gtk_text_buffer_get_end_iter(buf, &end);
	//gtk_text_buffer_insert(buf, &end, "\n", -1);
}

AvlTextView *avl_text_view_new(){
	return g_object_new(AVL_TYPE_TEXT_VIEW,
			"editable", FALSE,
			"cursor-visible", FALSE,
			"width-request", 500,
			"height-request", 500,
			NULL);
}
