#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "enemy.h"

void initGame(GameState *game);
void setDifficulty(GameState *game, int difficulty);

void processInput(GameState *game, int input);

void updateGame(GameState *game);

int isGameRunning(GameState *game);

void saveHighScore(GameState *game);
void loadHighScores(GameState *game);

#endif
