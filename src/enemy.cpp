#include "enemy.h"
#include "room.h"
#include "player.h"
#include <stdlib.h>

void initEnemies(Enemy *enemies) {
    for (int i = 0; i < TOTAL_ENEMIES; i++) {
        enemies[i].alive = 0;
    }

    enemies[0] = {15, 5, 3, ENEMY_TYPE_GUARD, 1, 1};
    enemies[1] = {25, 10, 3, ENEMY_TYPE_GUARD, 1, 1};
    enemies[2] = {10, 5, 2, ENEMY_TYPE_GHOST, 4, 1};
    enemies[3] = {30, 10, 2, ENEMY_TYPE_GHOST, 4, 1};
    enemies[4] = {20, 7, 10, ENEMY_TYPE_GUARD, 5, 1};
}

void updateEnemies(Enemy *enemies, Player *player, Room *rooms) {
    for (int i = 0; i < TOTAL_ENEMIES; i++) {
        if (enemies[i].alive && enemies[i].roomIndex == (*player).currentRoom) {
            int dx = 0, dy = 0;
            if (enemies[i].x < (*player).x) dx = 1;
            else if (enemies[i].x > (*player).x) dx = -1;
            if (enemies[i].y < (*player).y) dy = 1;
            else if (enemies[i].y > (*player).y) dy = -1;

            if (dx != 0) {
                int newX = enemies[i].x + dx;
                if (enemies[i].type == ENEMY_TYPE_GHOST || rooms[enemies[i].roomIndex].tiles[enemies[i].y][newX] != TILE_WALL)
                    enemies[i].x = newX;
            }
            if (dy != 0) {
                int newY = enemies[i].y + dy;
                if (enemies[i].type == ENEMY_TYPE_GHOST || rooms[enemies[i].roomIndex].tiles[newY][enemies[i].x] != TILE_WALL)
                    enemies[i].y = newY;
            }
        }
    }
}

void killEnemy(Enemy *enemies, int index) {
    enemies[index].alive = 0;
}
