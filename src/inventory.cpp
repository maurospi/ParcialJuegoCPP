#include "inventory.h"
#include "structs.h"

int hasItem(Player *player) {
    for (int i = 0; i < 3; i++) {
        if ((*player).inventory.items[i] != ITEM_NONE) return 1;
    }
    return 0;
}

int getItemType(Player *player) {
    int slot = (*player).inventory.selectedSlot;
    return (*player).inventory.items[slot];
}

const char *getItemName(int itemType) {
    if (itemType == ITEM_SWORD) return "Espada";
    if (itemType == ITEM_KEY) return "Llave";
    return "Nada";
}
