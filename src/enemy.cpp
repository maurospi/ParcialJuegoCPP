#include "enemy.h"
#include "room.h"
#include "player.h"
#include <stdlib.h>
#include <string.h>

void initEnemies(Enemy *enemies) {
    for (int i = 0; i < TOTAL_ENEMIES; i++) {
        enemies[i].alive = 0;
        strcpy(enemies[i].name, "Enemigo");
    }

    enemies[0].x = 15; enemies[0].y = 5; enemies[0].health = 2;
    enemies[0].type = ENEMY_TYPE_GUARD; enemies[0].roomIndex = 1; enemies[0].alive = 1;
    strcpy(enemies[0].name, "Quiz Sorpresa");

    enemies[1].x = 5; enemies[1].y = 3; enemies[1].health = 2;
    enemies[1].type = ENEMY_TYPE_GUARD; enemies[1].roomIndex = 2; enemies[1].alive = 1;
    strcpy(enemies[1].name, "Parcial de Punteros");
    enemies[2].x = 15; enemies[2].y = 7; enemies[2].health = 2;
    enemies[2].type = ENEMY_TYPE_GUARD; enemies[2].roomIndex = 2; enemies[2].alive = 1;
    strcpy(enemies[2].name, "Quiz Sorpresa");

    enemies[3].x = 15; enemies[3].y = 5; enemies[3].health = 1;
    enemies[3].type = ENEMY_TYPE_GHOST; enemies[3].roomIndex = 3; enemies[3].alive = 1;
    strcpy(enemies[3].name, "Error de Sintaxis");

    enemies[4].x = 5; enemies[4].y = 2; enemies[4].health = 1;
    enemies[4].type = ENEMY_TYPE_GHOST; enemies[4].roomIndex = 4; enemies[4].alive = 1;
    strcpy(enemies[4].name, "Segmentation Fault");
    enemies[5].x = 15; enemies[5].y = 8; enemies[5].health = 1;
    enemies[5].type = ENEMY_TYPE_GHOST; enemies[5].roomIndex = 4; enemies[5].alive = 1;
    strcpy(enemies[5].name, "Error de Sintaxis");

    enemies[6].x = 10; enemies[6].y = 2; enemies[6].health = 3;
    enemies[6].type = ENEMY_TYPE_GUARD; enemies[6].roomIndex = 5; enemies[6].alive = 1;
    strcpy(enemies[6].name, "Profe Ducuara");
}

void updateEnemies(Enemy *enemies, Player *player, Room *rooms) {
    int rIdx = (*player).currentRoom;
    for (int i = 0; i < TOTAL_ENEMIES; i++) {
        if (enemies[i].alive && enemies[i].roomIndex == rIdx) {
            int dx = 0, dy = 0;
            if ((*player).x > enemies[i].x) dx = 1;
            else if ((*player).x < enemies[i].x) dx = -1;
            if ((*player).y > enemies[i].y) dy = 1;
            else if ((*player).y < enemies[i].y) dy = -1;

            if (enemies[i].type == ENEMY_TYPE_GUARD) {
                if (dx != 0 && isTileWalkable(&rooms[rIdx], enemies[i].x + dx, enemies[i].y)) {
                    enemies[i].x += dx;
                } else if (dy != 0 && isTileWalkable(&rooms[rIdx], enemies[i].x, enemies[i].y + dy)) {
                    enemies[i].y += dy;
                } else {
                    int randMove = rand() % 2;
                    if (randMove == 0 && isTileWalkable(&rooms[rIdx], enemies[i].x + 1, enemies[i].y)) enemies[i].x++;
                    else if (isTileWalkable(&rooms[rIdx], enemies[i].x, enemies[i].y + 1)) enemies[i].y++;
                }
            } else {
                if (rand() % 10 > 2) {
                    enemies[i].x += dx;
                    enemies[i].y += dy;
                } else {
                    enemies[i].x += (rand() % 3) - 1;
                    enemies[i].y += (rand() % 3) - 1;
                }
                if (enemies[i].x < 1) enemies[i].x = 1;
                if (enemies[i].x > MAP_WIDTH - 2) enemies[i].x = MAP_WIDTH - 2;
                if (enemies[i].y < 1) enemies[i].y = 1;
                if (enemies[i].y > MAP_HEIGHT - 2) enemies[i].y = MAP_HEIGHT - 2;
            }
        }
    }
}

#include "game.h"
#include "audio.h"
#include <string.h>
#include <stdio.h>

void checkEnemyCollision(Enemy *enemies, Player *player, void* gamePtr) {
    GameState* game = (GameState*)gamePtr;
    int rIdx = (*player).currentRoom;
    for (int i = 0; i < TOTAL_ENEMIES; i++) {
        if (enemies[i].alive && enemies[i].roomIndex == rIdx) {
            if (enemies[i].x == (*player).x && enemies[i].y == (*player).y) {
                damagePlayer(player, ENEMY_DAMAGE);
                char msg[80];
                sprintf(msg, "%s %s te ha golpeado!", SFX_DAMAGE, enemies[i].name);
                strcpy((*game).lastMessage, msg);
                playBeep(200);

                if (isTileWalkable(&((*game).rooms[rIdx]), (*player).x - 1, (*player).y)) {
                    (*player).x--;
                } else if (isTileWalkable(&((*game).rooms[rIdx]), (*player).x + 1, (*player).y)) {
                    (*player).x++;
                } else if (isTileWalkable(&((*game).rooms[rIdx]), (*player).x, (*player).y - 1)) {
                    (*player).y--;
                } else if (isTileWalkable(&((*game).rooms[rIdx]), (*player).x, (*player).y + 1)) {
                    (*player).y++;
                }
                break;
            }
        }
    }
}

void killEnemy(Enemy *enemies, int index) {
    enemies[index].alive = 0;
}
