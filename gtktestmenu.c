// gcc -o t gtktestmenu.c `pkg-config --libs --cflags gtk+-3.0`
#include <stdio.h>
#include <gtk/gtk.h>

static gint button_press (GtkWidget *, GdkEvent *);
static void menuitem_response (gchar *);

static void
button_clicked(GtkWidget *sender, gpointer data)
{
    printf("\n%s\n",__FUNCTION__);
}

int main( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *menu;
    GtkWidget *menu_items;
    GtkWidget *hbox;
    GtkWidget *button;
    char buf[128];
    int i;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 33, 33);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Menu Test");
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (gtk_main_quit), NULL);

    menu = gtk_menu_new ();

    for (i = 0; i < 3; i++)
        {
            sprintf (buf, "Testmenu - %d", i);

            menu_items = gtk_menu_item_new_with_label (buf);


            gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_items);

	    g_signal_connect_swapped (G_OBJECT (menu_items), "activate",
		                      G_CALLBACK (menuitem_response), 
                                      g_strdup (buf));

            gtk_widget_show (menu_items);
        }

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), hbox);
    gtk_widget_show (hbox);

    button = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 1);
    GtkWidget *image = gtk_image_new_from_file("/home/test/x.png");  
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_size_request (button,22, 22);
    gtk_widget_show (button);
    g_signal_connect(
        G_OBJECT(button), "clicked",
        G_CALLBACK(button_clicked), menu);

    button = gtk_button_new();
    GtkWidget *image2 = gtk_image_new_from_file("/home/test/y.png");  
    gtk_button_set_image(GTK_BUTTON(button), image2);
    g_signal_connect_swapped (G_OBJECT (button), "event",
	                      G_CALLBACK (button_press), 
                              menu);
    gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 2);
    gtk_widget_set_size_request (button,22, 22);

    gtk_widget_show (button);

    gtk_widget_show (window);

    gtk_main ();

    return 0;
}

static gint button_press( GtkWidget *widget,
                          GdkEvent *event )
{

    if (event->type == GDK_BUTTON_PRESS) {
        GdkEventButton *bevent = (GdkEventButton *) event; 
        gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL,
                        bevent->button, bevent->time);

        return TRUE;
    }

    return FALSE;
}

static void menuitem_response( gchar *string )
{
    printf ("%s\n", string);
}

