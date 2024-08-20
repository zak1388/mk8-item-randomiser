#ifndef ITEM_H
#define ITEM_H

enum ETeamAllocation {
    None,
    Red,
    Blue,
    Both,
};

struct Item {
    char* name;
    enum ETeamAllocation team_allocation;
};

struct ItemNode {
    struct Item* item;
    struct ItemNode* next;
};

void RegisterItem(char *name);
void DeregisterAllItems();
int GetItemCount();

void RandomAllocateAllItems();

struct ItemNode* getItemListHead();

#endif // ITEM_H
