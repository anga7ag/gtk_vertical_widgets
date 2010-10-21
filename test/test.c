#include "gtkvlabel.h"


int main (int argc, char ** argv)
{
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *fixed;

  gtk_init(&argc, &argv);


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "vertical label widget");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 10, 10);


  g_signal_connect(G_OBJECT(window), "destroy", 
       G_CALLBACK(gtk_main_quit), NULL);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  label = gtk_vlabel_new("ᠡᠷᠲᠡ ᠤᠷᠢᠳᠠ ᠺᠠᠪᠠᠯᠢᠺ\n ᠪᠠᠯᠭᠠᠰᠤᠨ\n ᠳᠤᠷ ᠪᠢᠷᠠᠮᠠᠨ\n ᠤ ᠬᠠᠮᠤᠭ");
  gtk_fixed_put(GTK_FIXED(fixed), label, 0, 0);

  gtk_widget_show(label);
  gtk_widget_show(fixed);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

