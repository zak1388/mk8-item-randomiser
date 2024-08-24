#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

#define ITEM_BUFFER_SIZE 100

enum ETeamAllocation {
    ETeamAllocation_None,
    ETeamAllocation_Red,
    ETeamAllocation_Blue,
    ETeamAllocation_Both,
};

struct Item {
    char* name;
    bool free_name;
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
void SetItemLikelihood(int likelihood); // likelyhood ranges from 0-100
int GetItemLikelihood();

void SaveItems(char *filename);
void LoadItems(char *filename);

struct ItemNode* getItemListHead();

#endif // ITEM_H
