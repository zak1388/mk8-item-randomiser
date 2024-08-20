#ifndef GRAPHICAL_H
#define GRAPHICAL_H

#include <gtk/gtk.h>
#include "items.h"

struct ItemButton {
    struct Item *item;
    GtkButton *button;
};

#endif // GRAPHICAL_H
