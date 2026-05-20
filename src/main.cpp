#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "renderer.h"
#include "input.h"

int main() {
    srand(time(NULL));
    char playAgain = 'y';
    
    while (playAgain == 'y' || playAgain == 'Y') {
        GameState game;
        initGame(&game);
        
        clearScreen();
        drawTitleScreen();
        drawHighScores(game.topScores);
        printf("\n  Presiona cualquier tecla para continuar...");
        while (!kbhit()) usleep(100000);
        getch();

        drawDifficultyMenu();
        char diff = '2';
        while (1) {
            if (kbhit()) {
                diff = getch();
                if (diff >= '1' && diff <= '3') break;
            }
            usleep(100000);
        }
        setDifficulty(&game, diff - '1');

        clearScreen();
        printf(COLOR_CYAN "\n  PREPARANDO MAZMORRA...\n" COLOR_RESET);
        usleep(1000000);

        while (isGameRunning(&game)) {
            if (kbhit()) {
                int input = getch();
                if (input == 27) {
                    getch();
                    input = getch();
                    if (input == 'A') input = KEY_UP;
                    else if (input == 'B') input = KEY_DOWN;
                    else if (input == 'C') input = KEY_RIGHT;
                    else if (input == 'D') input = KEY_LEFT;
                }
                
                if (input == 'm' || input == 'M') {
                    drawMinimap(game.rooms, &game.player);
                    while (!kbhit()) usleep(100000);
                    getch();
                } else {
                    processInput(&game, input);
                }
            }
            
            updateGame(&game);
            clearScreen();
            drawRoom(game.rooms, &game.player, game.enemies, TOTAL_ENEMIES);
            drawHUD(&game.player, game.player.currentRoom);
            if (strlen(game.lastMessage) > 0) drawMessage(game.lastMessage);
            usleep(100000); 
        }

        clearScreen();
        if (game.state == STATE_WIN) drawVictory();
        else drawGameOver();
        
        drawStats(&game);
        
        printf("\n  " COLOR_BOLD "Quieres volver a jugar? (s/n): " COLOR_RESET);
        char buffer[10];
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            playAgain = buffer[0];
            if (playAgain == 's') playAgain = 'y';
        } else {
            playAgain = 'n';
        }
    }
    
    printf("\n  Gracias por jugar a Dungeon Escape Master Edition\n");
    return 0;
}