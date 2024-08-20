#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "items.h"
#include "graphical.h"

void RegisterItems() {
    RegisterItem("Coin");
    RegisterItem("Blooper");
    RegisterItem("Bob-omb");
    RegisterItem("Piranha Plant");
    RegisterItem("Banana");
    RegisterItem("Triple Bananas");
    RegisterItem("Boo");
    RegisterItem("Green Shell");
    RegisterItem("Triple Green Shells");
    RegisterItem("Fire Flower");
    RegisterItem("Mushroom");
    RegisterItem("Triple Mushrooms");
    RegisterItem("Red Shell");
    RegisterItem("Triple Red Shells");
    RegisterItem("Boomerang");
    RegisterItem("King Mushroom");
    RegisterItem("Star");
    RegisterItem("Blue Shell");
    RegisterItem("Lightning");
    RegisterItem("Bullet Bill");
    RegisterItem("Super Horn");
    RegisterItem("8");
}

void cycleItemTeamAllocation(GtkWidget *button, gpointer data) {
    struct Item *item = data;
    item->team_allocation = (item->team_allocation + 1) % 4; // we love magic numbers
}

struct ItemButton* createItemButtons() {
    int itemCount = GetItemCount();
    struct ItemButton *itemButtons = malloc(sizeof(struct ItemButton) * itemCount);
    struct ItemNode *node = getItemListHead();
    for (int i = 0; i < itemCount && node != NULL; i++, node=node->next) {
        itemButtons[i].button = (GtkButton*) gtk_button_new_with_label(node->item->name);
        itemButtons[i].item = node->item;
        g_signal_connect(itemButtons[i].button, "clicked", G_CALLBACK(cycleItemTeamAllocation), itemButtons[i].item);
    } 
    return itemButtons;
}

void reallocateItems(GtkWidget *widget, gpointer data) {
    RandomAllocateAllItems();
    struct ItemButton *itemButtons = data;
    for (int i = 0; i < GetItemCount(); i++) {
        char* color[2];
        color[1] = NULL;
        switch (itemButtons[i].item->team_allocation) {
            case None:
                color[0] = "None";
                break;
            case Red:
                color[0] = "Red";
                break;
            case Blue:
                color[0] = "Blue";
                break;
            case Both:
                color[0] = "Both";
                break;
        }
        gtk_widget_set_css_classes((GtkWidget*) itemButtons[i].button, (const char**) color);
    }
}

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    struct ItemButton *itemButtons;
    GtkWidget *itemScrollWindow;
    GtkWidget *itemButtonBox;
    GtkWidget *reallocateButton;
    GtkWidget *grid;

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(cssProvider, 
        ".Red { color: red; }\n"
        ".Blue { color: blue; }\n"
        ".Both { color: white; }\n"
        ".None { color: grey; }"
    );
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), (GtkStyleProvider*) cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Mario Kart 8 -- Item randomiser");
    gtk_window_set_default_size (GTK_WINDOW (window), 600, 500);

    RegisterItems();
    itemButtons = createItemButtons();

    GtkSizeGroup *group = gtk_size_group_new(GTK_SIZE_GROUP_BOTH);
    itemButtonBox = gtk_flow_box_new();
    gtk_widget_set_hexpand(itemButtonBox, TRUE);
    gtk_widget_set_vexpand(itemButtonBox, TRUE);
    for (int i = 0; i < GetItemCount(); i++) {
        gtk_size_group_add_widget(group, (GtkWidget*) itemButtons[i].button);
        gtk_flow_box_insert((GtkFlowBox*) itemButtonBox, (GtkWidget*) itemButtons[i].button, i);
    }

    itemScrollWindow = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child((GtkScrolledWindow*) itemScrollWindow, itemButtonBox);

    reallocateButton = gtk_button_new_with_label("Reallocate");
    g_signal_connect(reallocateButton, "clicked", G_CALLBACK(reallocateItems), itemButtons);

    grid = gtk_grid_new();
    gtk_grid_attach((GtkGrid*) grid, itemScrollWindow, 0, 0, 3, 1);
    gtk_grid_attach((GtkGrid*) grid, reallocateButton, 1, 1, 1, 1);

    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_window_present (GTK_WINDOW (window));
}


int main(int argc, char** argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
