#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "console.h"

struct ItemNode *head = NULL;

void RegisterItem(char *name) {
    struct Item* item = malloc(sizeof(struct Item));
    item->name = name;
    item->team_allocation = None;

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

void RandomAllocateAllItems() {
    struct ItemNode* node = head;
    while (node != NULL) {
        node->item->team_allocation = rand() % 4;
        node = node->next;
    }
}

void PrintItems() {
    struct ItemNode* node = head;
    while (node != NULL) {
        char *allocation;
        switch (node->item->team_allocation) {
            case None: allocation = "None"; break;
            case Red: allocation = "\033[31mRed\033[39m"; break;
            case Blue: allocation = "\033[34mBlue\033[39m"; break;
            case Both: allocation = "\033[31mBo\033[34mth\033[39m"; break;
        }
        printf("%s: %s\n", node->item->name, allocation);
        node = node->next;
    }
}

int main(void) {
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

    srand(time(NULL));
    RandomAllocateAllItems();
    
    PrintItems();
}

