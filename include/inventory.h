#ifndef INVENTORY_H
#define INVENTORY_H

#include "structs.h"

int hasItem(Player *player);
int getItemType(Player *player);
const char *getItemName(int itemType);

#endif
