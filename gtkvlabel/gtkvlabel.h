#if defined(GTK_DISABLE_SINGLE_INCLUDES) && !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h> can be included directly."
#endif

#ifndef __GTK_VLABEL_H__
#define __GTK_VLABEL_H__


#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTK_TYPE_VLABEL	  (gtk_vlabel_get_type ())
#define GTK_VLABEL(obj)	  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VLABEL, GtkVLabel))
#define GTK_LABEL_CLASSMN(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_VLABEL, GtkVLabelClass))
#define GTK_IS_VLABEL(obj)	  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VLABEL))
#define GTK_IS_VLABEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VLABEL))
#define GTK_VLABEL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_VLABEL, GtkVLabelClass))


typedef struct _GtkVLabel       GtkVLabel;
typedef struct _GtkVLabelClass  GtkVLabelClass;

struct _GtkVLabel
{
  GtkWidget widget;

  gchar *GSEAL(text);
};

struct _GtkVLabelClass
{
  GtkWidgetClass parent_class;
};

GtkType gtk_vlabel_get_type(void);
void gtk_vlabel_set_text(GtkVLabel *label, const gchar *text);
GtkWidget *gtk_vlabel_new();

G_END_DECLS

#endif /* __GTK_VLABEL_H__ */
