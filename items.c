#include <stdlib.h>
#include <stdio.h>

#include "items.h"

struct ItemNode *head = NULL;

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

void RegisterItem(char *name) {
    struct Item* item = malloc(sizeof(struct Item));
    item->name = name;
    item->team_allocation = ETeamAllocation_None;

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
        node->item->team_allocation = rand() % 4;
        node = node->next;
    }
}

void DeregisterAllItems() {
    struct ItemNode *node = head;
    while (node != NULL) {
        struct ItemNode *node_prev = node;
        node = node->next;

        free(node_prev->item);
        free(node_prev);
    }
}

struct ItemNode* getItemListHead() {
    return head;
}
