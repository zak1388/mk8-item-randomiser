#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdlib.h>

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
void RandomAllocateAllItems();
void PrintItems();


#endif // CONSOLE_H
