#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "console.h"
#include "items.h"

void PrintItems() {
    struct ItemNode* node = getItemListHead();
    while (node != NULL) {
        char *allocation;
        switch (node->item->team_allocation) {
            case ETeamAllocation_None: allocation = "None"; break;
            case ETeamAllocation_Red: allocation = "\033[31mRed\033[39m"; break;
            case ETeamAllocation_Blue: allocation = "\033[34mBlue\033[39m"; break;
            case ETeamAllocation_Both: allocation = "\033[31mBo\033[34mth\033[39m"; break;
        }
        printf("%s: %s\n", node->item->name, allocation);
        node = node->next;
    }
}


int main(void) {
    RegisterAllItems();

    srand(time(NULL));
    RandomAllocateAllItems();
    
    PrintItems();
}

