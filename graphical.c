#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "items.h"
#include "graphical.h"

void updateButtonClass(struct ItemButton *itemButton) {
    char* colorClass[2];
    colorClass[1] = NULL;
    switch (itemButton->item->team_allocation) {
        case ETeamAllocation_None:
            colorClass[0] = "None";
            break;
        case ETeamAllocation_Red:
            colorClass[0] = "Red";
            break;
        case ETeamAllocation_Blue:
            colorClass[0] = "Blue";
            break;
        case ETeamAllocation_Both:
            colorClass[0] = "Both";
            break;
    }
    gtk_widget_set_css_classes((GtkWidget*) itemButton->button, (const char**) colorClass);
}

void cycleItemTeamAllocation(GtkWidget *button, gpointer data) {
    struct ItemButton *itemButton = data;
    itemButton->item->team_allocation = (itemButton->item->team_allocation + 1) % 4; // we love magic numbers
    updateButtonClass(itemButton);
}

struct ItemButton* createItemButtons() {
    int itemCount = GetItemCount();
    struct ItemButton *itemButtons = malloc(sizeof(struct ItemButton) * itemCount);
    struct ItemNode *node = getItemListHead();
    for (int i = 0; i < itemCount && node != NULL; i++, node=node->next) {
        itemButtons[i].button = (GtkButton*) gtk_button_new_with_label(node->item->name);
        itemButtons[i].item = node->item;
        updateButtonClass(&itemButtons[i]);
        g_signal_connect(itemButtons[i].button, "clicked", G_CALLBACK(cycleItemTeamAllocation), &itemButtons[i]);
    } 
    return itemButtons;
}

void reallocateItems(GtkWidget *widget, gpointer data) {
    RandomAllocateAllItems();
    struct ItemButton *itemButtons = data;
    for (int i = 0; i < GetItemCount(); i++) {
        updateButtonClass(&itemButtons[i]);
    }
}

void itemLikelihoodSliderUpdate(GtkWidget *widget, gpointer data) {
    int likely = gtk_range_get_value((GtkRange *) widget);
    SetItemLikelihood(likely); 

    char value_str[4];
    snprintf(value_str, 4, "%d", likely);
    gtk_label_set_text((GtkLabel*) data, value_str);
}

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    struct ItemButton *itemButtons;
    GtkWidget *itemScrollWindow;
    GtkWidget *itemButtonBox;
    GtkWidget *itemLikelihoodSlider;
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

    RegisterAllItems();
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

    GtkWidget *likelihoodBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *likelihoodLabel = gtk_label_new("Item likelihood: ");
    char value_str[3];
    snprintf(value_str, 3, "%d", GetItemLikelihood());
    GtkWidget *likelihoodValueLabel = gtk_label_new(value_str);
    itemLikelihoodSlider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    gtk_range_set_value((GtkRange*) itemLikelihoodSlider, GetItemLikelihood());
    g_signal_connect(itemLikelihoodSlider, "value-changed", G_CALLBACK(itemLikelihoodSliderUpdate), likelihoodValueLabel);
    gtk_box_append((GtkBox*) likelihoodBox, likelihoodLabel);
    gtk_box_append((GtkBox*) likelihoodBox, itemLikelihoodSlider);
    gtk_widget_set_hexpand(itemLikelihoodSlider, TRUE);
    gtk_box_append((GtkBox*) likelihoodBox, likelihoodValueLabel);

    reallocateButton = gtk_button_new_with_label("Reallocate");
    g_signal_connect(reallocateButton, "clicked", G_CALLBACK(reallocateItems), itemButtons);

    grid = gtk_grid_new();
    gtk_grid_attach((GtkGrid*) grid, itemScrollWindow, 0, 0, 3, 1);
    gtk_grid_attach((GtkGrid*) grid, likelihoodBox, 0, 1, 3, 1);
    gtk_grid_attach((GtkGrid*) grid, reallocateButton, 1, 2, 1, 1);

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
