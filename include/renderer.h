#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "enemy.h"

void clearScreen();

void drawRoom(Room *rooms, Player *player, Enemy *enemies, int enemyCount);

void drawHUD(GameState *game);

void drawGameOver();

void drawVictory();

void drawTitleScreen();
void drawMessage(const char *message);
void drawDifficultyMenu();
void drawMinimap(Room *rooms, Player *player);
void drawStats(GameState *game);
void drawHighScores(HighScore *scores);
void drawItemPickupCinematic(int itemType);
void drawBossCinematic();
void drawExitExamCinematic();

#endif
