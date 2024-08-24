#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include "items.h"

struct ItemNode *head = NULL;
int LIKELIHOOD = 50;

void RegisterAllItems() {
    RegisterItem("Banana");
    RegisterItem("Triple Bananas");
    RegisterItem("Green Shell");
    RegisterItem("Triple Green Shells");
    RegisterItem("Red Shell");
    RegisterItem("Triple Red Shells");
    RegisterItem("Blue Shell");
    RegisterItem("Bob-omb");
    RegisterItem("Mushroom");
    RegisterItem("Triple Mushrooms");
    RegisterItem("King Mushroom");
    RegisterItem("Bullet Bill");
    RegisterItem("Blooper");
    RegisterItem("Lightning");
    RegisterItem("Star");
    RegisterItem("Fire Flower");
    RegisterItem("Boomerang");
    RegisterItem("Piranha Plant");
    RegisterItem("Super Horn");
    RegisterItem("8");
    RegisterItem("Coin");
    RegisterItem("Boo");
}

struct ItemNode* RegisterAndReturnNode(char *name) {
    struct Item* item = malloc(sizeof(struct Item));
    item->name = name;
    item->team_allocation = ETeamAllocation_None;
    item->free_name = false;

    struct ItemNode* node = malloc(sizeof(struct ItemNode));
    node->item = item;
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        struct ItemNode* lastNode = head;
        while (lastNode->next != NULL) lastNode = lastNode->next;
        lastNode->next = node;
    }

    return node;
}

void RegisterItem(char *name) {
    RegisterAndReturnNode(name);
}

int GetItemCount() {
    struct ItemNode *node = getItemListHead();
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void RandomAllocateAllItems() {
    struct ItemNode* node = head;
    while (node != NULL) {
        if (rand() % 100 < GetItemLikelihood() ) {
            node->item->team_allocation = rand() % 3 + 1;
        } else {
            node->item->team_allocation = ETeamAllocation_None;
        }
        node = node->next;
    }
}

void SetItemLikelihood(int likelihood) {
    if (likelihood > 100) likelihood = 100;
    else if (likelihood < 0) likelihood = 0;

    LIKELIHOOD = likelihood;
}

int GetItemLikelihood() {
    return LIKELIHOOD;
}

void DeregisterAllItems() {
    struct ItemNode *node = head;
    while (node != NULL) {
        struct ItemNode *node_prev = node;
        node = node->next;

        if (node_prev->item->free_name) {
            free(node_prev->item->name);
        }

        free(node_prev->item);
        free(node_prev);
    }
    head = NULL;
}

void SaveItems(char *filename) {
    FILE* file = fopen(filename, "r");
    bool exists = true;
    if (errno == ENOENT) {
        exists = false;
    } 
    if (file != NULL) {
        fclose(file);
    }


    if (exists) return; // dont save to files that exist

    file = fopen(filename, "w");
    struct ItemNode *node = getItemListHead();
    while (node != NULL) {
        char buffer[ITEM_BUFFER_SIZE];
        int len;

        len = snprintf(buffer, ITEM_BUFFER_SIZE, "%s", node->item->name);
        fwrite(buffer, len, 1, file);

        fwrite(",", 1, 1, file);

        len = snprintf(buffer, ITEM_BUFFER_SIZE, "%d", node->item->team_allocation);
        fwrite(buffer, len, 1, file);

        fwrite("\n", 1, 1, file);

        node = node->next;
    }
    fclose(file);
}

void LoadItems(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    DeregisterAllItems();

    char *buffer = malloc(ITEM_BUFFER_SIZE);
    buffer[ITEM_BUFFER_SIZE - 1] = '\0';
    int buffer_ptr = 0;
    struct ItemNode *last_node;
    while (fread(buffer + buffer_ptr, 1, 1, file) != 0) {
        buffer_ptr++;

        if (buffer_ptr >= ITEM_BUFFER_SIZE - 1) {
            buffer_ptr = 0;
        }

        if (buffer[buffer_ptr - 1] == ',') {
            // mustve just read item name
            buffer[buffer_ptr - 1] = '\0';
            last_node = RegisterAndReturnNode(buffer);
            last_node->item->free_name = true;
            buffer = malloc(ITEM_BUFFER_SIZE);
            buffer[ITEM_BUFFER_SIZE - 1] = '\0';
            buffer_ptr = 0;
        } 

        if (buffer[buffer_ptr - 1] == '\n') {
            // mustve just read team allocation
            buffer[buffer_ptr-1] = '\0';
            last_node->item->team_allocation = atoi(buffer);
            buffer = malloc(ITEM_BUFFER_SIZE);
            buffer[ITEM_BUFFER_SIZE - 1] = '\0';
            buffer_ptr = 0;
        }
    }
    
    fclose(file);
    for (struct ItemNode *node = head; node != NULL; node = node->next) {
        printf("%s\n", node->item->name);
    }
}

struct ItemNode* getItemListHead() {
    return head;
}
