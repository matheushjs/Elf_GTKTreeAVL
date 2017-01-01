#include <gtk/gtk.h>

#include <avl_win.h>
#include <avl_entry.h>
#include <avl_text_view.h>
#include <avl_entry_button.h>
#include <avl_text_button.h>

#include <avlwrappers.h>

struct _AvlWin {
	GtkApplicationWindow parent;
};

typedef struct {
	GtkGrid *main_grid;
	GtkGrid *input_grid;
} AvlWinPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(AvlWin, avl_win, GTK_TYPE_APPLICATION_WINDOW);

void avl_win_init(AvlWin *win){
	AvlWinPrivate *priv;
	AvlEntry *entry;
	AvlEntryButton *but;
	AvlTextView *view;
	AvlTextButton *tbut;

	gtk_widget_init_template(GTK_WIDGET(win));
	priv = avl_win_get_instance_private(win);

	view = avl_text_view_new();
	gtk_grid_attach(priv->main_grid, GTK_WIDGET(view), 1, 0, 1, 1);

	//Insert pair
	entry = avl_entry_new("Value to Insert", GTK_TEXT_VIEW(view), insert_app_wrapper);
	but = avl_entry_button_new("Insert", entry);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(entry), 0, 0, 1, 1);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(but), 1, 0, 1, 1);

	//Search pair
	entry = avl_entry_new("Value to Search", GTK_TEXT_VIEW(view), search_app_wrapper);
	but = avl_entry_button_new("Search", entry);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(entry), 0, 1, 1, 1);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(but), 1, 1, 1, 1);

	//Remove pair
	entry = avl_entry_new("Value to Remove", GTK_TEXT_VIEW(view), remove_app_wrapper);
	but = avl_entry_button_new("Remove", entry);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(entry), 0, 2, 1, 1);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(but), 1, 2, 1, 1);

	//Successor pair
	entry = avl_entry_new("Fetch Successor of", GTK_TEXT_VIEW(view), successor_app_wrapper);
	but = avl_entry_button_new("Successor", entry);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(entry), 0, 3, 1, 1);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(but), 1, 3, 1, 1);

	//Predecessor pair
	entry = avl_entry_new("Fetch Predecessor of", GTK_TEXT_VIEW(view), predecessor_app_wrapper);
	but = avl_entry_button_new("Predecessor", entry);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(entry), 0, 4, 1, 1);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(but), 1, 4, 1, 1);

	//Max/Min buttons
	tbut = avl_text_button_new("Max", GTK_TEXT_VIEW(view), max_app_wrapper);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(tbut), 0, 5, 2, 1);
	tbut = avl_text_button_new("Min", GTK_TEXT_VIEW(view), min_app_wrapper);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(tbut), 0, 6, 2, 1);

	//Print buttons 
	tbut = avl_text_button_new("Print Pre-Order", GTK_TEXT_VIEW(view), preorder_app_wrapper);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(tbut), 0, 7, 2, 1);
	tbut = avl_text_button_new("Print In-Order", GTK_TEXT_VIEW(view), inorder_app_wrapper);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(tbut), 0, 8, 2, 1);
	tbut = avl_text_button_new("Print Post-Order", GTK_TEXT_VIEW(view), postorder_app_wrapper);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(tbut), 0, 9, 2, 1);

	//Size button
	tbut = avl_text_button_new("Size", GTK_TEXT_VIEW(view), NULL);
	gtk_grid_attach(priv->input_grid, GTK_WIDGET(tbut), 0, 10, 2, 1);

	gtk_widget_show_all(GTK_WIDGET(priv->main_grid));
}

void avl_win_class_init(AvlWinClass *win){
	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(win),
			"/com/gitlab/matheushjs/avl_app/resource/avl_win.ui");
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(win),
			AvlWin, main_grid);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(win),
			AvlWin, input_grid);
}

AvlWin *avl_win_new(GtkApplication *app){
	return g_object_new(AVL_TYPE_WIN, "application", app, NULL);
}
