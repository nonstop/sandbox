#include <locale.h>
#include <libintl.h>

#include <gtk/gtk.h>

#define _(str) gettext(str)
#define PACKAGE "loc_test"
#define LOCALEDIR "/usr/local/share/locale"

GtkWidget *window;
GtkWidget *notebook;
GtkWidget *hbox;

GtkWidget *lab1, *lab2;
GtkWidget *tab1, *tab2;

void init()
{
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), _("qqq"));
    
    hbox = gtk_hbox_new(TRUE, 0);

    notebook = gtk_notebook_new();
    
    lab1 = gtk_label_new(_("lab1"));
    lab2 = gtk_label_new(_("lab2"));

    tab1 = gtk_label_new(_("text 1"));
    tab2 = gtk_label_new(_("text 2"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab1, NULL);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab2, NULL);


    gtk_box_pack_start(GTK_BOX(hbox), notebook, TRUE, TRUE, 0);

	gtk_container_add(GTK_CONTAINER(window), hbox);

    gtk_widget_show_all(window);
}

int main(int ac, char *av[])
{
//	setlocale(LC_ALL, "");
    bind_textdomain_codeset (PACKAGE, "UTF-8");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    gtk_init(&ac, &av);

    init();
    gtk_widget_show(window);

	gtk_main();
    return 0;
}


