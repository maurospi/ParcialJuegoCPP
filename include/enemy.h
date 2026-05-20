#ifndef ENEMY_H
#define ENEMY_H

#include "structs.h"

void initEnemies(Enemy *enemies);
void updateEnemies(Enemy *enemies, Player *player, Room *rooms);
void killEnemy(Enemy *enemies, int index);

#endif