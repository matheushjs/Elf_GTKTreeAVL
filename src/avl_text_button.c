#include <gtk/gtk.h>

#include <avl_text_button.h>
#include <avl_text_box.h>

struct _AvlTextButton {
	GtkButton parent;

	AvlTextBox *box;
	gchar *(*function_to_call)(void);
};

G_DEFINE_TYPE(AvlTextButton, avl_text_button, GTK_TYPE_BUTTON);

static
void avl_text_button_init(AvlTextButton *but){
}

static
void avl_text_button_class_init(AvlTextButtonClass *klass){
}

static
void activate(AvlTextButton *but){
	gchar *text;

	if(but->function_to_call){
		text = but->function_to_call();
		avl_text_box_print_text(but->box, text);
		g_free(text);
	}
}

AvlTextButton *avl_text_button_new(gchar *label, AvlTextBox *box,
		gchar *(*function)(void)){
	AvlTextButton *but;

	but = g_object_new(AVL_TYPE_TEXT_BUTTON,
			"label", label,
			NULL);
	but->box = box;
	but->function_to_call = function;
	g_signal_connect(but, "clicked", G_CALLBACK(activate), NULL);
	
	return but;
}
