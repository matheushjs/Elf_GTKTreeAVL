#include <gtk/gtk.h>

#include <avl_text_box.h>

struct _AvlTextBox {
	GtkBox parent;
};

typedef struct {
	GtkTextView *text_view;
} AvlTextBoxPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(AvlTextBox, avl_text_box, GTK_TYPE_BOX);

static
void buffer_changed_action(AvlTextBox *tb){
	AvlTextBoxPrivate *priv;
	GtkTextBuffer *buf;
	GtkTextIter start, end;
	gchar *text;

	priv = avl_text_box_get_instance_private(tb);

	buf = gtk_text_view_get_buffer(priv->text_view);
	if(gtk_text_buffer_get_line_count(buf) >= 30){
		gtk_text_buffer_get_end_iter(buf, &end);
		gtk_text_buffer_get_iter_at_line(buf, &start, 5);
		text = gtk_text_buffer_get_text(buf, &start, &end, FALSE);
		gtk_text_buffer_set_text(buf, text, -1);
	}
}

static
void avl_text_box_init(AvlTextBox *tb){
	AvlTextBoxPrivate *priv;
	GtkTextBuffer *buf;

	gtk_widget_init_template(GTK_WIDGET(tb));
	priv = avl_text_box_get_instance_private(tb);

	buf = gtk_text_buffer_new(NULL);
	g_signal_connect_swapped(buf, "changed", G_CALLBACK(buffer_changed_action), tb);
	gtk_text_view_set_buffer(priv->text_view, buf);
}

static
void avl_text_box_class_init(AvlTextBoxClass *klass){
	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(klass),
			"/com/gitlab/matheushjs/avl_app/resource/avl_text_box.ui");
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(klass),
			AvlTextBox, text_view);
}

void avl_text_box_print_text(AvlTextBox *view, const gchar *string){
	AvlTextBoxPrivate *priv;
	GtkTextBuffer *buf;
	GtkTextIter end;

	priv = avl_text_box_get_instance_private(view);

	buf = gtk_text_view_get_buffer(priv->text_view);
	gtk_text_buffer_get_end_iter(buf, &end);
	gtk_text_buffer_insert(buf, &end, string, -1);
	
	//gtk_text_buffer_get_end_iter(buf, &end);
	//gtk_text_buffer_insert(buf, &end, "\n", -1);
}

AvlTextBox *avl_text_box_new(){
	return g_object_new(AVL_TYPE_TEXT_BOX, NULL);
}
