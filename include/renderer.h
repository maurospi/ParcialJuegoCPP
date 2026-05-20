#ifndef RENDERER_H
#define RENDERER_H

#include "structs.h"

void clearScreen();
void drawRoom(Room *rooms, Player *player, Enemy *enemies, int enemyCount);
void drawHUD(Player *player, int roomIndex);
void drawMessage(const char *message);
void drawGameOver();
void drawVictory();
void drawMinimap(Room *rooms, Player *player);
void drawDifficultyMenu();
void drawStats(GameState *game);
void drawHighScores(HighScore *scores);
void drawTitleScreen();
void drawStoryScreen(int roomIndex);

#endif