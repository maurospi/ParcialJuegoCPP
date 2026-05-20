#ifndef GAME_H
#define GAME_H

#include "structs.h"

void initGame(GameState *game);
void updateGame(GameState *game);
void processInput(GameState *game, int input);
int isGameRunning(GameState *game);
void saveHighScore(GameState *game);
void loadHighScores(GameState *game);
void setDifficulty(GameState *game, int diff);

#endif