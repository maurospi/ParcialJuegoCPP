// Disclaimer: Partes de este codigo fueron generadas o sugeridas por IA para cumplir con los requerimientos del proyecto.
#include "game.h"
#include "player.h"
#include "room.h"
#include "enemy.h"
#include "inventory.h"
#include "audio.h"
#include "renderer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void initGame(GameState *game) {
    initRooms((*game).rooms);
    initEnemies((*game).enemies);
    
    (*game).player.x = PLAYER_START_X;
    (*game).player.y = PLAYER_START_Y;
    (*game).player.health = PLAYER_START_HEALTH;
    (*game).player.currentRoom = PLAYER_START_ROOM;
    
    for(int i=0; i<3; i++) (*game).player.inventory.items[i] = ITEM_NONE;
    (*game).player.inventory.selectedSlot = 0;
    
    (*game).state = STATE_PLAYING;
    (*game).turnCount = 0;
    (*game).enemyKills = 0;
    (*game).damageReceived = 0;
    (*game).difficulty = 1;
    (*game).enemySpeed = 3;
    strcpy((*game).lastMessage, "Bienvenido a la Grand Master Edition!");
    
    loadHighScores(game);
}

void setDifficulty(GameState *game, int diff) {
    (*game).difficulty = diff;
    (*game).player.health = 3;
    if (diff == 0) {
        (*game).enemySpeed = 5;
    } else if (diff == 1) {
        (*game).enemySpeed = 3;
    } else {
        (*game).enemySpeed = 2;
    }
}

void processInput(GameState *game, int input) {
    Player *p = &(*game).player;
    Room *r = &(*game).rooms[(*p).currentRoom];
    
    int moveRes = 1;
    if (input == 'w' || input == 'W' || input == KEY_UP) moveRes = movePlayer(p, 0, -1, (*game).rooms);
    else if (input == 's' || input == 'S' || input == KEY_DOWN) moveRes = movePlayer(p, 0, 1, (*game).rooms);
    else if (input == 'a' || input == 'A' || input == KEY_LEFT) moveRes = movePlayer(p, -1, 0, (*game).rooms);
    else if (input == 'd' || input == 'D' || input == KEY_RIGHT) moveRes = movePlayer(p, 1, 0, (*game).rooms);
    
    if (moveRes == -1) {
        strcpy((*game).lastMessage, "EXAMEN BLOQUEADO! Necesitas conseguir la Llave Root.");
        playBeep(250);
    }
    else if (input == 'e' || input == 'E') {
        int pickedType = r->itemType;
        int res = pickUpItem(p, r);
        if (res == 1) {
            playGameSound("assets/Item.wav");
            strcpy((*game).lastMessage, "Objeto guardado en el inventario!");
            playBeep(600);
            drawItemPickupCinematic(pickedType);
        } else if (res == 2) {
            strcpy((*game).lastMessage, "Tu vida ya esta al maximo!");
            playBeep(400);
        } else if (res == 3) {
            playGameSound("assets/Curacion.wav");
            strcpy((*game).lastMessage, "Tomaste cafe! Recuperas 1 de vida.");
            playBeep(800);
        } else {
            strcpy((*game).lastMessage, "Inventario lleno o nada que recoger.");
        }
    }
    else if (input == 'q' || input == 'Q') {
        if (dropItem(p, r)) {
            strcpy((*game).lastMessage, "Objeto soltado en la sala.");
            playBeep(300);
        } else {
            strcpy((*game).lastMessage, "No tienes nada para soltar o el suelo esta ocupado.");
        }
    }
    else if (input == '1') (*p).inventory.selectedSlot = 0;
    else if (input == '2') (*p).inventory.selectedSlot = 1;
    else if (input == '3') (*p).inventory.selectedSlot = 2;
    else if (input == 'x' || input == 'X') {
        int currentItem = (*p).inventory.items[(*p).inventory.selectedSlot];
        if (currentItem == ITEM_SWORD) {
            playGameSound("assets/Espada.wav");
            int hit = 0;
            int killed = 0;
            char hitName[30] = "";
            int remainingHP = 0;
            char killedName[30] = "";
            
            for (int i = 0; i < TOTAL_ENEMIES; i++) {
                if ((*game).enemies[i].alive && (*game).enemies[i].roomIndex == (*p).currentRoom) {
                    int dist = abs((*game).enemies[i].x - (*p).x) + abs((*game).enemies[i].y - (*p).y);
                    if (dist <= 1) {
                        (*game).enemies[i].health--;
                        hit++;
                        strcpy(hitName, (*game).enemies[i].name);
                        remainingHP = (*game).enemies[i].health;
                        
                        if ((*game).enemies[i].health <= 0) {
                            killEnemy((*game).enemies, i);
                            (*game).enemyKills++;
                            killed++;
                            strcpy(killedName, (*game).enemies[i].name);
                        }
                        break;
                    }
                }
            }
            if (killed > 0) {
                sprintf((*game).lastMessage, "%s ¡%s derrotado!", SFX_ATTACK, killedName);
                playBeep(440);
            } else if (hit > 0) {
                sprintf((*game).lastMessage, "%s ¡Golpeaste a %s! (Vida restante: %d)", SFX_ATTACK, hitName, remainingHP);
                playBeep(400);
            } else {
                strcpy((*game).lastMessage, "Ataque al aire...");
            }
        } else {
            strcpy((*game).lastMessage, "Necesitas una espada para atacar.");
        }
    }
}

void updateGame(GameState *game) {
    (*game).turnCount++;
    
    if ((*game).turnCount % (*game).enemySpeed == 0) {
        updateEnemies((*game).enemies, &(*game).player, (*game).rooms);
    }
    
    int oldHealth = (*game).player.health;
    checkEnemyCollision((*game).enemies, &(*game).player, game);
    if ((*game).player.health < oldHealth) {
        (*game).damageReceived += (oldHealth - (*game).player.health);
    }
    
    if ((*game).player.health <= 0) (*game).state = STATE_LOSE;
    
    if ((*game).player.currentRoom == VICTORY_ROOM) {
        if ((*game).rooms[VICTORY_ROOM].tiles[(*game).player.y][(*game).player.x] == TILE_EXIT) {
            (*game).state = STATE_WIN;
        }
    }
}

int isGameRunning(GameState *game) {
    return ((*game).state == STATE_PLAYING);
}

void loadHighScores(GameState *game) {
    FILE *f = fopen("highscores.txt", "r");
    if (f) {
        for (int i = 0; i < 3; i++) {
            if (fscanf(f, "%s %d", (*game).topScores[i].name, &(*game).topScores[i].score) != 2) {
                strcpy((*game).topScores[i].name, "Vacio");
                (*game).topScores[i].score = 0;
            }
        }
        fclose(f);
    } else {
        for (int i = 0; i < 3; i++) {
            strcpy((*game).topScores[i].name, "Vacio");
            (*game).topScores[i].score = 0;
        }
    }
}

void saveHighScore(GameState *game) {
    int score = ((*game).enemyKills * 100) + ((*game).player.health * 50) - ((*game).turnCount / 10);
    if (score < 0) score = 0;
    
    if (score > (*game).topScores[2].score) {
        strcpy((*game).topScores[2].name, "Jugador");
        (*game).topScores[2].score = score;
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2 - i; j++) {
                if ((*game).topScores[j].score < (*game).topScores[j+1].score) {
                    HighScore temp = (*game).topScores[j];
                    (*game).topScores[j] = (*game).topScores[j+1];
                    (*game).topScores[j+1] = temp;
                }
            }
        }
        
        FILE *f = fopen("highscores.txt", "w");
        if (f) {
            for (int i = 0; i < 3; i++) {
                fprintf(f, "%s %d\n", (*game).topScores[i].name, (*game).topScores[i].score);
            }
            fclose(f);
        }
    }
}
