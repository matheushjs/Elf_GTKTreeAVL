#include <gtk/gtk.h>

#include <avl_win.h>
#include <avl_about_win.h>
#include <avl_app.h>

struct _AvlApp {
	GtkApplication parent;
};

typedef struct {
	AvlAboutWin *about_win;
} AvlAppPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(AvlApp, avl_app, GTK_TYPE_APPLICATION);

static
void avl_app_init(AvlApp *app){
}

static
void activate(GApplication *app){
	AvlWin *win;
	AvlAboutWin *about;
	AvlAppPrivate *priv;

	win = avl_win_new(GTK_APPLICATION(app));
	gtk_window_present(GTK_WINDOW(win));

	about = avl_about_win_new(GTK_APPLICATION(app), GTK_WINDOW(win));
	priv = avl_app_get_instance_private(AVL_APP(app));
	priv->about_win = about;
}

static
void about_activated(GSimpleAction *action, GVariant *param, gpointer app){
	AvlAppPrivate *priv;

	priv = avl_app_get_instance_private(AVL_APP(app));
	gtk_widget_show(GTK_WIDGET(priv->about_win));
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
