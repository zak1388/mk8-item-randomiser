#ifndef ITEM_H
#define ITEM_H

enum ETeamAllocation {
    ETeamAllocation_None,
    ETeamAllocation_Red,
    ETeamAllocation_Blue,
    ETeamAllocation_Both,
};

struct Item {
    char* name;
    enum ETeamAllocation team_allocation;
};

struct ItemNode {
    struct Item* item;
    struct ItemNode* next;
};

void RegisterAllItems();
void RegisterItem(char *name);
void DeregisterAllItems();
int GetItemCount();

void RandomAllocateAllItems();

struct ItemNode* getItemListHead();

#endif // ITEM_H
