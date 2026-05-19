#ifndef PLAYER_H
#define PLAYER_H

#include "structs.h"

void initPlayer(Player *player);
int movePlayer(Player *player, int dx, int dy, Room *rooms);
void damagePlayer(Player *player, int amount);
int pickUpItem(Player *player, Room *room);
int dropItem(Player *player, Room *room);

#endif
