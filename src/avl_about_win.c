#include <gtk/gtk.h>

#include <avl_about_win.h>

struct _AvlAboutWin{
	GtkAboutDialog parent;
};

G_DEFINE_TYPE(AvlAboutWin, avl_about_win, GTK_TYPE_ABOUT_DIALOG);

static
void avl_about_win_init(AvlAboutWin *win){
}

static
void avl_about_win_class_init(AvlAboutWinClass *klass){
}

static gchar *copyright_string =
"	Copyright (C) 2017 Matheus H. J. Saldanha\n\
\n\
	This program is free software: you can redistribute it and/or modify\n\
	it under the terms of the GNU General Public License as published by\n\
	the Free Software Foundation, either version 3 of the License, or\n\
	(at your option) any later version.\n\
\n\
	This program is distributed in the hope that it will be useful,\n\
	but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
	GNU General Public License for more details.\n\
\n\
	You should have received a copy of the GNU General Public License\n\
	along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\
\n\
	Contact me: matheus.saldanha@usp.br";

//Must be global, so that the gchar pointer isn't invalidated at the end of the function.
static
gchar *global_authors[2] = {"Matheus H. J. Saldanha", NULL};

static
void response(GtkDialog *diag, gint response_id, gpointer user_data){
	if(response_id == GTK_RESPONSE_DELETE_EVENT)
		gtk_widget_hide(GTK_WIDGET(diag));
}

//Doing other stuff into the new() function might be bad practice.
//Could use class_init() or instance_init() functions instead!
AvlAboutWin *avl_about_win_new(GtkApplication *app, GtkWindow *transient){
	AvlAboutWin *win;
	
	win = g_object_new(AVL_TYPE_ABOUT_WIN, 
			"application", app,
			"authors", global_authors,
			"copyright", copyright_string,
			"program-name", "GtkAvlTree",
			"version", "1.0",
			"comments", "Implementation, with an user interface, of an AvlTree for storing numbers of type integer.",
			"destroy-with-parent", TRUE,
			"transient-for", transient,
			NULL);
	
	g_signal_connect(win, "delete-event", G_CALLBACK(gtk_widget_hide), NULL);
	g_signal_connect(win, "response", G_CALLBACK(response), NULL);
	return win;
}
