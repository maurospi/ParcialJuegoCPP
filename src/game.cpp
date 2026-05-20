#include "game.h"
#include "player.h"
#include "enemy.h"
#include "room.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void initGame(GameState *game) {
    initRooms((*game).rooms);
    initEnemies((*game).enemies);
    initPlayer(&(*game).player);
    (*game).state = STATE_PLAYING;
    (*game).turnCount = 0;
    (*game).enemyKills = 0;
    (*game).damageReceived = 0;
    (*game).difficulty = 1;
    (*game).enemySpeed = 3;
    strcpy((*game).lastMessage, "Bienvenido a la Grand Master Edition");
    loadHighScores(game);
}

void setDifficulty(GameState *game, int diff) {
    (*game).difficulty = diff;
    if (diff == 0) { (*game).player.health = 8; (*game).enemySpeed = 4; }
    else if (diff == 1) { (*game).player.health = 5; (*game).enemySpeed = 3; }
    else { (*game).player.health = 3; (*game).enemySpeed = 2; }
}

void processInput(GameState *game, int input) {
    Player *p = &(*game).player;
    Room *r = &(*game).rooms[(*p).currentRoom];

    if (input == 'w' || input == 'W' || input == KEY_UP) movePlayer(p, 0, -1, (*game).rooms);
    else if (input == 's' || input == 'S' || input == KEY_DOWN) movePlayer(p, 0, 1, (*game).rooms);
    else if (input == 'a' || input == 'A' || input == KEY_LEFT) movePlayer(p, -1, 0, (*game).rooms);
    else if (input == 'd' || input == 'D' || input == KEY_RIGHT) movePlayer(p, 1, 0, (*game).rooms);
    else if (input == 'e' || input == 'E') {
        if (pickUpItem(p, r)) { strcpy((*game).lastMessage, "Objeto recogido"); playBeep(600); }
    }
    else if (input == '1') (*p).inventory.selectedSlot = 0;
    else if (input == '2') (*p).inventory.selectedSlot = 1;
    else if (input == '3') (*p).inventory.selectedSlot = 2;
    else if (input == 'x' || input == 'X') {
        int currentItem = (*p).inventory.items[(*p).inventory.selectedSlot];
        if (currentItem == ITEM_SWORD) {
            for (int i = 0; i < TOTAL_ENEMIES; i++) {
                if ((*game).enemies[i].alive && (*game).enemies[i].roomIndex == (*p).currentRoom) {
                    int dist = abs((*game).enemies[i].x - (*p).x) + abs((*game).enemies[i].y - (*p).y);
                    if (dist <= 2) {
                        (*game).enemies[i].health--;
                        strcpy((*game).lastMessage, "ZAS Enemigo golpeado");
                        playBeep(400);
                        if ((*game).enemies[i].health <= 0) {
                            killEnemy((*game).enemies, i);
                            (*game).enemyKills++;
                            strcpy((*game).lastMessage, "Enemigo derrotado");
                            playBeep(800);
                        }
                    }
                }
            }
        }
    }
}

void updateGame(GameState *game) {
    (*game).turnCount++;
    if ((*game).turnCount % (*game).enemySpeed == 0) {
        updateEnemies((*game).enemies, &(*game).player, (*game).rooms);
    }
    for (int i = 0; i < TOTAL_ENEMIES; i++) {
        if ((*game).enemies[i].alive && (*game).enemies[i].roomIndex == (*game).player.currentRoom) {
            if ((*game).enemies[i].x == (*game).player.x && (*game).enemies[i].y == (*game).player.y) {
                damagePlayer(&(*game).player, ENEMY_DAMAGE);
                (*game).damageReceived++;
                strcpy((*game).lastMessage, "AUCH Te han golpeado");
                playBeep(200);
            }
        }
    }
    if ((*game).player.health <= 0) (*game).state = STATE_LOSE;
    if ((*game).rooms[(*game).player.currentRoom].tiles[(*game).player.y][(*game).player.x] == TILE_EXIT) (*game).state = STATE_WIN;
}

int isGameRunning(GameState *game) { return (*game).state == STATE_PLAYING; }

void saveHighScore(GameState *game) {
    int score = ((*game).enemyKills * 100) + ((*game).player.health * 50) - ((*game).turnCount / 10);
    FILE *f = fopen("highscore.txt", "a");
    if (f) { fprintf(f, "Heroe %d\n", score); fclose(f); }
}

void loadHighScores(GameState *game) {
    FILE *f = fopen("highscore.txt", "r");
    if (f) {
        for (int i = 0; i < 3; i++) {
            if (fscanf(f, "%s %d", (*game).topScores[i].name, &(*game).topScores[i].score) == EOF) break;
        }
        fclose(f);
    }
}
