#include "gtkvlabel.h"
#include <math.h>
#include <pango/pango.h>

static void gtk_vlabel_class_init(GtkVLabelClass *klass);
static void gtk_vlabel_init(GtkVLabel *label);
static void gtk_vlabel_size_request(GtkWidget *widget, GtkRequisition *requisition);
static void gtk_vlabel_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static void gtk_vlabel_realize(GtkWidget *widget);
static gboolean gtk_vlabel_expose(GtkWidget *widget, GdkEventExpose *event);
static void gtk_vlabel_paint(GtkWidget *widget);
static void gtk_vlabel_destroy(GtkObject *object);
static void gtk_vlabel_set_text_internal(GtkVLabel *label, gchar *str);


GtkType 
gtk_vlabel_get_type(void) 
{
  static GtkType gtk_vlabel_type = 0;
  
  if (!gtk_vlabel_type) {
    static const GtkTypeInfo gtk_vlabel_info = {
      "GtkVLabel",
      sizeof(GtkVLabel),
      sizeof(GtkVLabelClass),
      (GtkClassInitFunc) gtk_vlabel_class_init,
      (GtkObjectInitFunc) gtk_vlabel_init,
      NULL,
      NULL,
      (GtkClassInitFunc) NULL
    };
    gtk_vlabel_type = gtk_type_unique (GTK_TYPE_WIDGET, &gtk_vlabel_info);
  }

  return gtk_vlabel_type;
}


void 
gtk_vlabel_set_text (GtkVLabel *label, 
    const gchar *str) {
  g_return_if_fail (GTK_IS_VLABEL (label));
  g_object_freeze_notify (G_OBJECT (label));
  gtk_vlabel_set_text_internal (label, g_strdup (str ? str : ""));
  g_object_thaw_notify (G_OBJECT (label));
}


static void 
gtk_vlabel_class_init(GtkVLabelClass *klass) 
{
  GtkWidgetClass *widget_class;
  GtkObjectClass *object_class;

  widget_class = (GtkWidgetClass *) klass;
  object_class = (GtkObjectClass *) klass;

  widget_class->realize = gtk_vlabel_realize;
  widget_class->size_request = gtk_vlabel_size_request;
  widget_class->size_allocate = gtk_vlabel_size_allocate;
  widget_class->expose_event = gtk_vlabel_expose;
  
  object_class->destroy = gtk_vlabel_destroy;
}


static void 
gtk_vlabel_init(GtkVLabel *label) 
{
 //TODO: find out what GTK_WIDGET_SET_FLAGS (label, GTK_NO_WINDOW); is!
  label->text = NULL;
  gtk_widget_set_direction(label, GTK_TEXT_DIR_RTL);
  gtk_vlabel_set_text(label, "");
}

/**
 * gtk_vlabel_new:
 * @str: The text of the label
 *
 * Creates a new label with the given text inside it. You can
 * pass %NULL to get an empty label widget.
 *
 * Return value: the new #GtkVLabel
 **/
GtkWidget* 
gtk_vlabel_new (const gchar *str) 
{
  GtkVLabel *label;

  label = g_object_new (GTK_TYPE_VLABEL, NULL);

  if (str && *str)
    gtk_vlabel_set_text (label, str);

  return GTK_WIDGET (label);
}

static void 
gtk_vlabel_set_text_internal (GtkVLabel *label, 
    gchar *str) 
{
  g_free (label->text);
  label->text = str;
}

static void 
gtk_vlabel_size_request(GtkWidget *widget, 
    GtkRequisition *requisition) 
{
  g_return_if_fail(widget != NULL);
  g_return_if_fail(GTK_IS_VLABEL(widget));
  g_return_if_fail(requisition != NULL);

  requisition->width = 300;
  requisition->height = 300;
}

static void
gtk_vlabel_size_allocate(GtkWidget *widget,
    GtkAllocation *allocation) 
{
  g_return_if_fail(widget != NULL);
  g_return_if_fail(GTK_IS_VLABEL(widget));
  g_return_if_fail(allocation != NULL);

  widget->allocation = *allocation;

  if (GTK_WIDGET_REALIZED(widget)) {
     gdk_window_move_resize(
         widget->window,
         allocation->x, allocation->y,
         allocation->width, allocation->height
     );
   }
}

static void
gtk_vlabel_realize(GtkWidget *widget)
{
  GdkWindowAttr attributes;
  guint attributes_mask;

  g_return_if_fail(widget != NULL);
  g_return_if_fail(GTK_IS_VLABEL(widget));

  GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);

  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.x = widget->allocation.x;
  attributes.y = widget->allocation.y;
  attributes.width = 300;
  attributes.height = 300;

  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

  attributes_mask = GDK_WA_X | GDK_WA_Y;

  widget->window = gdk_window_new(
     gtk_widget_get_parent_window (widget),
     & attributes, attributes_mask
  );

  gdk_window_set_user_data(widget->window, widget);

  widget->style = gtk_style_attach(widget->style, widget->window);
  gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);
}

static gboolean
gtk_vlabel_expose(GtkWidget *widget,
    GdkEventExpose *event)
{
  g_return_val_if_fail(widget != NULL, FALSE);
  g_return_val_if_fail(GTK_IS_VLABEL(widget), FALSE);
  g_return_val_if_fail(event != NULL, FALSE);

  gtk_vlabel_paint(widget);

  return FALSE;
}

static void
gtk_vlabel_paint(GtkWidget *widget)
{
  cairo_t *cr;

  cr = gdk_cairo_create(widget->window);

  cairo_set_source_rgb(cr, 0, 0, 0);

  PangoLayout *layout;
  PangoFontDescription *desc;

  layout = pango_cairo_create_layout(cr);
  pango_layout_set_text(layout, GTK_VLABEL(widget)->text, -1);

  desc = pango_font_description_from_string("Mongolian Baiti 20");
  pango_layout_set_font_description(layout, desc);

  pango_context_set_base_gravity(pango_layout_get_context(layout), PANGO_GRAVITY_NORTH);

  cairo_translate(cr, 0,120);
  cairo_rotate(cr, M_PI * 1.5);
  
  pango_font_description_free(desc);

  pango_cairo_layout_path(cr, layout);
  cairo_fill(cr);

  g_object_unref(layout);

  cairo_destroy(cr);
}


static void
gtk_vlabel_destroy(GtkObject *object)
{
  GtkVLabel *label;
  GtkVLabelClass *klass;

  g_return_if_fail(object != NULL);
  g_return_if_fail(GTK_IS_VLABEL(object));

  label = GTK_VLABEL(object);

  klass = gtk_type_class(gtk_widget_get_type());

  if (GTK_OBJECT_CLASS(klass)->destroy) {
     (* GTK_OBJECT_CLASS(klass)->destroy) (object);
  }
}

