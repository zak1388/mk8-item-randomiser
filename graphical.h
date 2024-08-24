#ifndef GRAPHICAL_H
#define GRAPHICAL_H

#include <gtk/gtk.h>
#include "items.h"

struct ItemButton {
    struct Item *item;
    GtkButton *button;
};

struct ItemButtonsAndItemBox {
    struct ItemButton **itemButtonsPtr;
    GtkFlowBox *itemButtonBox;
};

#endif // GRAPHICAL_H
