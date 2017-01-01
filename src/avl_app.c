#include <gtk/gtk.h>

#include <avl_win.h>
#include <avl_app.h>

struct _AvlApp {
	GtkApplication parent;
};

G_DEFINE_TYPE(AvlApp, avl_app, GTK_TYPE_APPLICATION);

void avl_app_init(AvlApp *app){
}

static
void activate(GApplication *app){
	AvlWin *win;
	win = avl_win_new(GTK_APPLICATION(app));
	gtk_window_present(GTK_WINDOW(win));
}

static
void avl_app_class_init(AvlAppClass *app){
	G_APPLICATION_CLASS(app)->activate = activate;
}

AvlApp *avl_app_new(){
	return g_object_new(AVL_TYPE_APP,
			"application-id", "com.gitlab.matheushjs.avl_app",
			"flags", G_APPLICATION_FLAGS_NONE,
			NULL);
}
