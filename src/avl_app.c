#include <gtk/gtk.h>

#include <avl_win.h>
#include <avl_app.h>

struct _AvlApp {
	GtkApplication parent;
};

G_DEFINE_TYPE(AvlApp, avl_app, GTK_TYPE_APPLICATION);

static
void avl_app_init(AvlApp *app){
}

static
void activate(GApplication *app){
	AvlWin *win;
	win = avl_win_new(GTK_APPLICATION(app));
	gtk_window_present(GTK_WINDOW(win));
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

#include <stdio.h>
static
void response(GtkDialog *diag, gint response_id, gpointer user_data){
	if(response_id == GTK_RESPONSE_DELETE_EVENT)
		gtk_window_close(GTK_WINDOW(diag));
}

static
void about_activated(GSimpleAction *action, GVariant *param, gpointer app){
	GtkAboutDialog *diag;
	gchar *authors[2] = {"Matheus H. J. Saldanha", NULL};

	diag = g_object_new(GTK_TYPE_ABOUT_DIALOG, 
			"application", app,
			"authors", authors,
			"copyright", copyright_string,
			"program-name", "GtkAvlTree",
			"version", "1.0",
			"comments", "Implementation, with an user interface, of an AvlTree for storing numbers of type integer.",
			NULL);

	g_signal_connect(diag, "response", G_CALLBACK(response), NULL);

	gtk_window_present(GTK_WINDOW(diag));
}

static
void quit_activated(GSimpleAction *action, GVariant *param, gpointer app){
	g_application_quit(G_APPLICATION(app));
}

static GActionEntry app_entries[] =
{
	{ "about", about_activated, NULL, NULL, NULL },
	{ "quit", quit_activated, NULL, NULL, NULL }
};

static
void avl_app_startup(GApplication *app){
	GtkBuilder *builder;
	GMenuModel *app_menu;
	const gchar *accels[2] = { "<Ctrl>Q", NULL };

	G_APPLICATION_CLASS(avl_app_parent_class)->startup(app);

	g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.quit", accels);

	builder = gtk_builder_new_from_resource("/com/gitlab/matheushjs/avl_app/resource/app_menu.ui");
	app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "app_menu"));
	gtk_application_set_app_menu(GTK_APPLICATION(app), app_menu);
	g_object_unref(builder);
}

static
void avl_app_class_init(AvlAppClass *app){
	G_APPLICATION_CLASS(app)->startup = avl_app_startup;
	G_APPLICATION_CLASS(app)->activate = activate;
}

AvlApp *avl_app_new(){
	return g_object_new(AVL_TYPE_APP,
			"application-id", "com.gitlab.matheushjs.avl_app",
			"flags", G_APPLICATION_FLAGS_NONE,
			NULL);
}
