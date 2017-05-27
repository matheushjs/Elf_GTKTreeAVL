#include <gtk/gtk.h>

#include <avl_file_button.h>
#include <avlwrappers.h>

struct _AvlFileButton {
	GtkButton parent;
};

typedef struct {
	GtkWindow *parent;
} AvlFileButtonPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(AvlFileButton, avl_file_button, GTK_TYPE_BUTTON);

static
void choose_file(AvlFileButton *but){
	GtkFileChooserDialog *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	AvlFileButtonPrivate *priv;

	priv = avl_file_button_get_instance_private(but);

	dialog = GTK_FILE_CHOOSER_DIALOG(
			gtk_file_chooser_dialog_new("Choose File", priv->parent, action,
			"_Cancel", GTK_RESPONSE_CANCEL,
			"_Open", GTK_RESPONSE_ACCEPT,
			NULL)
		);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if(res == GTK_RESPONSE_ACCEPT){
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		filename = gtk_file_chooser_get_filename(chooser);
		parse_wrapper(filename);
		g_free(filename);
	}
	
	gtk_widget_destroy(GTK_WIDGET(dialog));
}

static
void avl_file_button_init(AvlFileButton *but){
	g_signal_connect(but, "clicked", G_CALLBACK(choose_file), NULL);
}

static
void avl_file_button_class_init(AvlFileButtonClass *klass){
}

AvlFileButton *avl_file_button_new(GtkWindow *transient){
	AvlFileButton *ret;
	AvlFileButtonPrivate *priv;

	ret = g_object_new(AVL_TYPE_FILE_BUTTON,
			"label", "Select an Input File",
			NULL);

	priv = avl_file_button_get_instance_private(ret);
	priv->parent = transient;

	return ret;
}
