#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

void initPlayer(Player *player);
int movePlayer(Player *player, int dx, int dy, Room *rooms);
int pickUpItem(Player *player, Room *room);
int dropItem(Player *player, Room *room);
void damagePlayer(Player *player, int amount);
int isPlayerAlive(Player *player);

#endif
