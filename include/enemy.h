#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

void initEnemies(Enemy *enemies);

void updateEnemies(Enemy *enemies, Player *player, Room *rooms);

void checkEnemyCollision(Enemy *enemies, Player *player, void* gamePtr);

void killEnemy(Enemy *enemies, int index);

int areAllEnemiesDeadInRoom(Enemy *enemies, int roomIndex);

#endif
