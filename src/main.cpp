// Disclaimer: Partes de este codigo fueron generadas o sugeridas por IA para cumplir con los requerimientos del proyecto.
#include <stdio.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "audio.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "story.h"

void playJRPGCinematic() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("\n\n");
    printf("         [ Ducuarita Junior ]\n");
    printf("                 ~O/\n");
    printf("                  |\n");
    printf("                 / \\\n");
    printf("\n  ========================================\n");

    const char *storyText = 
        "Ducuarita Junior despierta en el Laboratorio 301. Las pantallas brillan con errores.\n"
        "No recuerda como se durmio, pero sabe que debe entregar el proyecto final.\n"
        "Para ganar la materia, debe adentrarse en los laboratorios y sobrevivir\n"
        "a los temibles desafios del Profe Ducuara. La puerta Este te espera.";

    printf("  ");
    int len = strlen(storyText);
    for (int i = 0; i < len; i++) {
        if (kbhit()) {
            int key = getch();
            if (key == 's' || key == 'S') {
                printf("%s", &storyText[i]);
                break;
            }
        }
        putchar(storyText[i]);
        if (storyText[i] == '\n') printf("  ");
        fflush(stdout);
        usleep(40000);
    }

    printf("\n  ========================================\n");
    printf("\n  [Presiona ENTER para comenzar el semestre...] ");
    
    while(1) {
        if(kbhit()) {
            int key = getch();
            if (key == '\r' || key == '\n' || key == 13) {
                break;
            }
        }
        usleep(100000);
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    srand(time(NULL));
    char playAgain = 'y';
    
    while (playAgain == 'y' || playAgain == 'Y') {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        startBackgroundMusic();

        GameState game;
        initGame(&game);
        
        clearScreen();
        drawTitleScreen();
        drawHighScores(game.topScores);
        printf("\n  Presiona cualquier tecla para continuar...");
        while(!kbhit()) usleep(100000);
        getch();

#ifdef _WIN32
        system("cls");
#endif
        drawDifficultyMenu();
        char diff = '2';
        while(1) {
            if(kbhit()) {
                diff = getch();
                if(diff >= '1' && diff <= '3') break;
            }
            usleep(100000);
        }
        setDifficulty(&game, diff - '1');
        playJRPGCinematic();
        game.rooms[0].visited = 1;

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
                    while(!kbhit()) usleep(100000);
                    getch();
                } else {
                    processInput(&game, input);
                }
            }
            
            updateGame(&game);
            clearScreen();
            drawRoom(game.rooms, &game.player, game.enemies, TOTAL_ENEMIES);
            drawHUD(&game);
            if (strlen(game.lastMessage) > 0) {
                drawMessage(game.lastMessage);
                game.lastMessage[0] = '\0';
            }
            usleep(100000); 
        }

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        if (game.state == STATE_WIN) {
            stopBackgroundMusic();
            drawExitExamCinematic();
            playGameSound("assets/Level-Complete.wav");
            drawVictory();
        }
        else drawGameOver();
        
        int score = (game.enemyKills * 100) + (game.player.health * 50) - (game.turnCount / 10);
        if (score < 0) score = 0;
        
        printf("\n  Tu puntuacion final es: " COLOR_YELLOW "%d" COLOR_RESET "\n", score);
        
        while(kbhit()) getch();
        
        printf("\n  Deseas registrar tu puntaje en el Top 3? (s/n): ");
        char ans[10] = "n";
        if (fgets(ans, sizeof(ans), stdin) != NULL) {
            if (ans[0] == 's' || ans[0] == 'S') {
                char name[20] = "AAA";
                printf("  Ingresa tu nombre o iniciales (3 letras): ");
                if (fgets(name, sizeof(name), stdin) != NULL) {
                    size_t len = strlen(name);
                    if (len > 0 && name[len - 1] == '\n') name[len - 1] = '\0';
                }
                if (strlen(name) == 0) {
                    strcpy(name, "AAA");
                }
                
                FILE *fHigh = fopen("highscores.txt", "a");
                if (fHigh) {
                    fprintf(fHigh, "%s %d\n", name, score);
                    fclose(fHigh);
                }
            }
        }
        
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
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
    
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    stopBackgroundMusic();
    printf("\n  Gracias por jugar a Dungeon Escape Master Edition!\n");
    return 0;
}
