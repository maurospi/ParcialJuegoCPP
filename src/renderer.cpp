// Disclaimer: Partes de este codigo fueron generadas o sugeridas por IA para cumplir con los requerimientos del proyecto.
#include "renderer.h"
#include "sprites.h"
#include "story.h"
#include "audio.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

static const char *itemNames[4] = {
    "Vacio",
    "Compilador C++",
    "Llave Root",
    "Cafe"
};

static bool victoryAnimated = false;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void drawStoryScreen(int roomIndex) {
    clearScreen();
    printf(COLOR_CYAN COLOR_BOLD "\n  === %s ===\n\n" COLOR_RESET, GAME_STORY[roomIndex].title);
    printf(COLOR_YELLOW "%s\n\n" COLOR_RESET, GAME_STORY[roomIndex].art);
    printf(COLOR_WHITE "%s\n\n" COLOR_RESET, GAME_STORY[roomIndex].description);
    printf(COLOR_BOLD "  Presiona cualquier tecla para entrar..." COLOR_RESET);
    while(!kbhit()) usleep(100000);
    getch();
}

void drawRoom(Room *rooms, Player *player, Enemy *enemies, int enemyCount) {
    int row, col, e;
    int rIdx = (*player).currentRoom;
    
    if (rooms[rIdx].visited == 0) {
        if (rIdx == 5) {
            drawBossCinematic();
        } else {
            drawStoryScreen(rIdx);
        }
        rooms[rIdx].visited = 1;
    }

    printf(COLOR_BOLD "\n  SALA: %-40s\n" COLOR_RESET, GAME_STORY[rIdx].title);

    printf(COLOR_BOLD "  #");
    for(int i=0; i<MAP_WIDTH*2; i++) printf("#");
    printf("#\n" COLOR_RESET);

    for (row = 0; row < MAP_HEIGHT; row++) {
        printf(COLOR_BOLD "  # " COLOR_RESET);
        for (col = 0; col < MAP_WIDTH; col++) {
            if (col == (*player).x && row == (*player).y) {
                printf("%s", SPR_PLAYER);
                continue;
            }

            int isEnemy = 0;
            for (e = 0; e < enemyCount; e++) {
                if (enemies[e].alive && enemies[e].roomIndex == rIdx && enemies[e].x == col && enemies[e].y == row) {
                    if (enemies[e].type == ENEMY_TYPE_GUARD) printf("%s", (enemies[e].health > 3 ? SPR_BOSS : SPR_GUARD));
                    else printf("%s", SPR_GHOST);
                    isEnemy = 1; break;
                }
            }
            if (isEnemy) continue;

            char tile = rooms[rIdx].tiles[row][col];
            if (rooms[rIdx].itemType != ITEM_NONE && rooms[rIdx].itemPickedUp == 0 && rooms[rIdx].itemX == col && rooms[rIdx].itemY == row) {
                if (rooms[rIdx].itemType == ITEM_SWORD) printf("%s", SPR_SWORD);
                else if (rooms[rIdx].itemType == ITEM_KEY) printf("%s", SPR_KEY);
                else if (rooms[rIdx].itemType == ITEM_COFFEE) printf("%s", SPR_COFFEE);
            } 
            else if (tile == TILE_WALL) printf("%s", TXT_WALL_LIGHT);
            else if (tile == TILE_FLOOR) printf("%s", TXT_FLOOR);
            else if (tile == TILE_EXIT) printf("%s", SPR_EXIT);
            else if (tile == TILE_TREE) printf("%s", SPR_TREE);
            else if (tile == TILE_ROCK) printf("%s", SPR_ROCK);
            else printf(COLOR_YELLOW "[]" COLOR_RESET);
        }
        printf(COLOR_BOLD " #   " COLOR_RESET);
        char sideLine[128] = "";
        
        int roomX = rIdx % 3;
        int roomY = rIdx / 3;
        
        switch (row) {
            case 0:
                sprintf(sideLine, COLOR_YELLOW COLOR_BOLD "[ LEYENDA ]" COLOR_RESET);
                break;
            case 1:
                sprintf(sideLine, "  " COLOR_CYAN "@ " COLOR_RESET ": Student Jr.");
                break;
            case 2:
                sprintf(sideLine, "  " COLOR_CYAN "##" COLOR_RESET ": Pared / Pupitre");
                break;
            case 3:
                sprintf(sideLine, "  " COLOR_GREEN "C " COLOR_RESET ": Cafe (+1 HP)");
                break;
            case 4:
                sprintf(sideLine, "  " COLOR_RED "G " COLOR_RESET "/" COLOR_MAGENTA "S " COLOR_RESET ": Enemigo");
                break;
            case 5:
                sprintf(sideLine, "  " COLOR_YELLOW "K " COLOR_RESET ": Llave Root");
                break;
            case 6:
                sprintf(sideLine, "  " COLOR_YELLOW "/ " COLOR_RESET ": Compilador C++");
                break;
            case 7:
                sprintf(sideLine, "  " COLOR_GREEN "E " COLOR_RESET ": Examen / Salida");
                break;
            case 8:
                sprintf(sideLine, COLOR_CYAN COLOR_BOLD "-- Mapa de Salas --" COLOR_RESET);
                break;
            case 9: {
                const char* r0 = (roomY == 0 && roomX == 0) ? COLOR_RED "[X]" COLOR_RESET : (rooms[0].visited ? "[.]" : "[ ]");
                const char* r1 = (roomY == 0 && roomX == 1) ? COLOR_RED "[X]" COLOR_RESET : (rooms[1].visited ? "[.]" : "[ ]");
                const char* r2 = (roomY == 0 && roomX == 2) ? COLOR_RED "[X]" COLOR_RESET : (rooms[2].visited ? "[.]" : "[ ]");
                sprintf(sideLine, "  %s  %s  %s", r0, r1, r2);
                break;
            }
            case 10:
                sprintf(sideLine, "               ");
                break;
            case 11: {
                const char* r3 = (roomY == 1 && roomX == 0) ? COLOR_RED "[X]" COLOR_RESET : (rooms[3].visited ? "[.]" : "[ ]");
                const char* r4 = (roomY == 1 && roomX == 1) ? COLOR_RED "[X]" COLOR_RESET : (rooms[4].visited ? "[.]" : "[ ]");
                const char* r5 = (roomY == 1 && roomX == 2) ? COLOR_RED "[X]" COLOR_RESET : (rooms[5].visited ? "[.]" : "[ ]");
                sprintf(sideLine, "  %s  %s  %s", r3, r4, r5);
                break;
            }
            case 12:
                sprintf(sideLine, "  Leyenda:");
                break;
            case 13:
                sprintf(sideLine, "  " COLOR_RED "[X]" COLOR_RESET " Actual  " COLOR_WHITE "[.]" COLOR_RESET " Visitado");
                break;
            case 14:
                sprintf(sideLine, "  [ ] Inexplorado");
                break;
            default:
                sideLine[0] = '\0';
                break;
        }
        printf("%s\n", sideLine);
    }
    printf(COLOR_BOLD "  #");
    for(int i=0; i<MAP_WIDTH*2; i++) printf("#");
    printf("#\n" COLOR_RESET);
}

void drawHUD(GameState *game) {
    Player *player = &(*game).player;
    int hp = (*player).health;
    if (hp > 3) hp = 3;
    if (hp < 0) hp = 0;
    int percent = (hp * 100) / 3;

    printf("\n  Salud: [");
    for (int i = 0; i < 3; i++) {
        if (i < hp) {
            printf(COLOR_RED "O" COLOR_RESET " ");
        } else {
            printf(COLOR_WHITE "." COLOR_RESET " ");
        }
    }
    printf("] (%d%%)", percent);
    
    printf("  |  Sala Actual: %-25s", GAME_STORY[(*player).currentRoom].title);
    
    int bossHP = -1;
    if ((*player).currentRoom == 5) {
        for (int i = 0; i < TOTAL_ENEMIES; i++) {
            if ((*game).enemies[i].alive && (*game).enemies[i].roomIndex == 5) {
                bossHP = (*game).enemies[i].health;
                break;
            }
        }
    }
    
    if (bossHP != -1) {
        printf("  |  " COLOR_RED COLOR_BOLD "PROFE DUCUARA: [" COLOR_RESET);
        for (int i = 0; i < 3; i++) {
            if (i < bossHP) printf(COLOR_RED "X" COLOR_RESET " ");
            else printf(COLOR_WHITE "." COLOR_RESET " ");
        }
        printf("] (%d/3)\n", bossHP);
    } else {
        printf("\n");
    }
    
    printf("  Inventario: ");
    for(int i=0; i<3; i++) {
        int itemId = (*player).inventory.items[i];
        if (itemId < 0 || itemId > 3) itemId = 0;
        if (i == (*player).inventory.selectedSlot) {
            printf(COLOR_CYAN ">[%s]< " COLOR_RESET, itemNames[itemId]);
        } else {
            printf("[%s] ", itemNames[itemId]);
        }
    }
    printf("\n  " COLOR_YELLOW COLOR_BOLD "MISION:" COLOR_RESET " 1. Consigue Compilador C++ y Llave Root | 2. Entra al Examen Final y aprueba!");
    printf("\n  " COLOR_BOLD "CONTROLES:" COLOR_RESET " [WASD] Mover  [E] Recoger  [1-3] Seleccionar  [X] Atacar  [M] Mapa\n");
}

void drawMinimap(Room *rooms, Player *player) {
    clearScreen();
    printf(COLOR_CYAN COLOR_BOLD "\n  === MAPA DE LA MAZMORRA ===\n\n" COLOR_RESET);
    const char* r[6];
    for(int i=0; i<6; i++) {
        if (i == (*player).currentRoom) r[i] = COLOR_CYAN "[ @ ]" COLOR_RESET;
        else if (rooms[i].visited) r[i] = COLOR_GREEN "[ V ]" COLOR_RESET;
        else r[i] = COLOR_WHITE "[ ? ]" COLOR_RESET;
    }
    printf("    %s == %s == %s\n", r[0], r[1], r[2]);
    printf("      |               |\n");
    printf("    %s == %s == %s\n", r[3], r[4], r[5]);
    printf("\n  Presiona cualquier tecla para volver...");
}

void drawDifficultyMenu() {
    clearScreen();
    printf(COLOR_BOLD "\n  SELECCIONA TU DESTINO:\n\n" COLOR_RESET);
    printf("  1. " COLOR_GREEN "FACIL" COLOR_RESET "\n  2. " COLOR_YELLOW "NORMAL" COLOR_RESET "\n  3. " COLOR_RED "DIFICIL" COLOR_RESET "\n\n  Opcion: ");
}

static void getTop3(HighScore *top3) {
    HighScore allScores[500];
    int count = 0;
    FILE *f = fopen("highscores.txt", "r");
    if (f) {
        while (count < 500 && fscanf(f, "%19s %d", allScores[count].name, &allScores[count].score) == 2) {
            count++;
        }
        fclose(f);
    }
    for (int i = count; i < 3; i++) {
        strcpy(allScores[i].name, "Vacio");
        allScores[i].score = 0;
    }
    int total = (count < 3) ? 3 : count;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (allScores[j].score < allScores[j+1].score) {
                HighScore temp = allScores[j];
                allScores[j] = allScores[j+1];
                allScores[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        top3[i] = allScores[i];
    }
}

void drawStats(GameState *game) {
    int score = ((*game).enemyKills * 100) + ((*game).player.health * 50) - ((*game).turnCount / 10);
    if (score < 0) score = 0;
    printf(COLOR_BOLD "\n  === ESTADISTICAS ===\n" COLOR_RESET);
    printf("  Turnos: %d | Kills: %d | Dano: %d\n", (*game).turnCount, (*game).enemyKills, (*game).damageReceived);
    printf("  Puntaje: " COLOR_YELLOW "%d" COLOR_RESET " | RATING: " COLOR_CYAN "%s" COLOR_RESET "\n", score, (score > 800 ? "S" : (score > 500 ? "A" : "B")));

    HighScore top3[3];
    getTop3(top3);
    printf(COLOR_YELLOW COLOR_BOLD "\n  === TOP 3 AVENTUREROS ===\n" COLOR_RESET);
    for (int i = 0; i < 3; i++) printf("  %d. %-10s : %d\n", i+1, top3[i].name, top3[i].score);
}

void drawHighScores(HighScore *scores) {
    HighScore top3[3];
    getTop3(top3);
    printf(COLOR_YELLOW COLOR_BOLD "\n  === TOP 3 AVENTUREROS ===\n" COLOR_RESET);
    for (int i = 0; i < 3; i++) printf("  %d. %-10s : %d\n", i+1, top3[i].name, top3[i].score);
}

void drawTitleScreen() {
    victoryAnimated = false;
    printf(COLOR_CYAN COLOR_BOLD "\n  #==========================================#\n");
    printf("  #       DUNGEON ESCAPE: GRAND MASTER       #\n");
    printf("  #            (ULTIMATE EDITION)            #\n");
    printf("  #==========================================#\n" COLOR_RESET);
}

void drawGameOver() { printf(COLOR_RED COLOR_BOLD "\n  HAS PERDIDO...\n" COLOR_RESET); }
void drawMessage(const char *message) { printf(COLOR_YELLOW "  >> %-70s\n" COLOR_RESET, message); }

void drawVictory() {
    if (!victoryAnimated) {
        victoryAnimated = true;
        for (int frame = 0; frame < 9; frame++) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            printf(COLOR_GREEN COLOR_BOLD "\n");
            printf("    ====================================================\n");
            printf("    #                 CONGRATULATIONS!                 #\n");
            printf("    #               APROBASTE LA MATERIA               #\n");
            printf("    ====================================================\n" COLOR_RESET);
            printf("\n");
            
            if (frame % 3 == 0) {
                printf("                 \\O/      \\O/      \\O/\n");
                printf("                  |        |        |\n");
                printf("                 / \\      / \\      / \\\n");
            } else if (frame % 3 == 1) {
                printf("                 _O_      _O_      _O_\n");
                printf("                  |        |        |\n");
                printf("                 / \\      / \\      / \\\n");
            } else {
                printf("                 \\O/      \\O/      \\O/\n");
                printf("                  \\        \\        \\\n");
                printf("                 / \\      / \\      / \\\n");
            }
            
            printf("            [ Mini Ducuarita esta super feliz! ]\n");
            printf("\n");
            printf(COLOR_YELLOW);
            printf("             *   *   *  Felicidades!  *   *   *\n");
            printf("         Has derrotado al Profe Ducuara y completado\n");
            printf("         el proyecto final de C++ sin memory leaks!\n");
            printf("         Tu nota es un glorioso 5.0!\n" COLOR_RESET);
            printf("\n");
            fflush(stdout);
            usleep(300000);
        }
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf(COLOR_GREEN COLOR_BOLD "\n");
    printf("    ====================================================\n");
    printf("    #                 CONGRATULATIONS!                 #\n");
    printf("    #               APROBASTE LA MATERIA               #\n");
    printf("    ====================================================\n" COLOR_RESET);
    printf("\n");
    printf("                 \\O/      \\O/      \\O/\n");
    printf("                  |        |        |\n");
    printf("                 / \\      / \\      / \\\n");
    printf("            [ Mini Ducuarita esta super feliz! ]\n");
    printf("\n");
    printf(COLOR_YELLOW);
    printf("             *   *   *  Felicidades!  *   *   *\n");
    printf("         Has derrotado al Profe Ducuara y completado\n");
    printf("         el proyecto final de C++ sin memory leaks!\n");
    printf("         Tu nota es un glorioso 5.0!\n" COLOR_RESET);
    printf("\n");
}

void drawItemPickupCinematic(int itemType) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("\n\n");
    if (itemType == ITEM_SWORD) {
        printf("        ============================================\n");
        printf("                    OBJETO ADQUIRIDO!               \n");
        printf("        ============================================\n");
        printf("\n");
        printf("                    /| ________________\n");
        printf("              O|===|* >________________>\n");
        printf("                    \\|\n");
        printf("\n");
        printf("        >> COMPILADOR C++ (ESPADA LEGENDARIA)\n");
        printf("        --------------------------------------------\n");
        printf("        Item recogido! Te servira para defenderte\n");
        printf("        de los problemas y obstaculos del semestre.\n");
        printf("        --------------------------------------------\n");
    } else if (itemType == ITEM_KEY) {
        printf("        ============================================\n");
        printf("                    OBJETO ADQUIRIDO!               \n");
        printf("        ============================================\n");
        printf("\n");
        printf("                 ___    \n");
        printf("                /   \\______\n");
        printf("                \\___/  | | |\n");
        printf("\n");
        printf("        >> LLAVE DE ACCESO ROOT\n");
        printf("        --------------------------------------------\n");
        printf("        Item recogido! Esta llave abre la puerta\n");
        printf("        del Examen Final de la mazmorra.\n");
        printf("        --------------------------------------------\n");
    } else {
        printf("        ============================================\n");
        printf("                    OBJETO ADQUIRIDO!               \n");
        printf("        ============================================\n");
        printf("\n        [ Objeto desconocido recogido ]\n\n");
    }
    printf("\n        [Presiona ENTER para continuar...] ");
    
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

void drawBossCinematic() {
    for (int step = 0; step < 3; step++) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        printf(COLOR_RED COLOR_BOLD "\n\n");
        printf("    ################################################\n");
        printf("    #               !!! ALERTA !!!                 #\n");
        printf("    #         ¡AHORA TIENES QUE VENCER AL          #\n");
        printf("    #               PROFE DUCUARA!                 #\n");
        printf("    ################################################\n" COLOR_RESET);
        printf("\n");
        
        if (step == 0) {
            printf("              [ PROFE DUCUARA ACECHA ]\n");
            printf("                     .-'''-.   \n");
            printf("                    / _   _ \\  \n");
            printf("                    | o   o |  \n");
            printf("                    |   |   |  \n");
            printf("                    \\  ___  /  \n");
            printf("                     '-___-'   \n");
        } else if (step == 1) {
            printf("              [ EL EXAMEN SE ACERCA... ]\n");
            printf("                     .-'''-.   \n");
            printf("                    / >   < \\  \n");
            printf("                    | O   O |  \n");
            printf("                    |   |   |  \n");
            printf("                    \\  ___  /  \n");
            printf("                     '-___-'   \n");
        } else {
            printf("              [ PREPARA TU COMPILADOR! ]\n");
            printf("                     .-'''-.   \n");
            printf("                    / @   @ \\  \n");
            printf("                    | O   O |  \n");
            printf("                    |  \\_/  |  \n");
            printf("                    \\  ___  /  \n");
            printf("                     '-___-'   \n");
        }
        
        printf(COLOR_YELLOW "\n");
        printf("    >> ¡EL ULTIMO DESAFIO DEL SEMESTRE HA COMENZADO!\n");
        printf("    >> ¡Ahora tienes que vencer al Profe Ducuara para graduarte!\n");
        printf("    >> Atacalo con [X] usando tu Compilador C++ y esquiva sus ataques.\n");
        printf("    >> Tiene 3 puntos de vida. ¡Demuestra tu conocimiento!\n" COLOR_RESET);
        printf("\n    [Presiona ENTER para comenzar el combate final...] ");
        
        if (step < 2) {
            fflush(stdout);
            usleep(800000);
        } else {
            while(1) {
                if(kbhit()) {
                    int key = getch();
                    if (key == '\r' || key == '\n' || key == 13) {
                        break;
                    }
                }
                usleep(100000);
            }
        }
    }
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void drawExitExamCinematic() {
    const char* gppCmd = "g++ -O3 -Wall -Wextra -std=c++11 main.cpp game.cpp player.cpp enemy.cpp renderer.cpp room.cpp inventory.cpp -o DungeonGame -lwinmm";
    
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf(COLOR_CYAN COLOR_BOLD "\n  >>> EXAMEN DE SALIDA: PROCESANDO COMPILACION DEL PROYECTO FINAL <<<\n" COLOR_RESET);
    printf("  %s\n\n", gppCmd);
    printf("  Progreso: [" COLOR_YELLOW "=====>                 " COLOR_RESET "] 25%%\n\n");
    printf(COLOR_WHITE "  [INFO] Analizando archivos de cabecera (.h)...\n");
    printf("  [INFO] Procesando include/audio.h, include/constants.h, include/types.h...\n");
    printf("  [INFO] Analisis sintactico y semantico de main.cpp: CORRECTO\n" COLOR_RESET);
    fflush(stdout);
    usleep(1000000);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf(COLOR_CYAN COLOR_BOLD "\n  >>> EXAMEN DE SALIDA: PROCESANDO COMPILACION DEL PROYECTO FINAL <<<\n" COLOR_RESET);
    printf("  %s\n\n", gppCmd);
    printf("  Progreso: [" COLOR_YELLOW "==========>            " COLOR_RESET "] 50%%\n\n");
    printf(COLOR_WHITE "  [INFO] Optimizacion de codigo activa (-O3)\n");
    printf("  [INFO] Desenrollado de bucles y eliminacion de codigo muerto...\n");
    printf("  [INFO] Compilando modulos principales: game.cpp, player.cpp, enemy.cpp...\n");
    printf("  [SUCCESS] Resolucion de plantillas completada. Cero errores de enlazado.\n" COLOR_RESET);
    fflush(stdout);
    usleep(1000000);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf(COLOR_CYAN COLOR_BOLD "\n  >>> EXAMEN DE SALIDA: PROCESANDO COMPILACION DEL PROYECTO FINAL <<<\n" COLOR_RESET);
    printf("  %s\n\n", gppCmd);
    printf("  Progreso: [" COLOR_YELLOW "===============>       " COLOR_RESET "] 75%%\n\n");
    printf(COLOR_WHITE "  [INFO] Enlazando binario DungeonGame.exe con winmm.lib...\n");
    printf("  [INFO] Verificando seguridad estatica contra desbordamiento de bufer...\n");
    printf("  [INFO] Ejecutando analisis dinamico de fugas de memoria con Valgrind...\n" COLOR_RESET);
    fflush(stdout);
    usleep(1000000);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf(COLOR_GREEN COLOR_BOLD "\n  >>> EXAMEN DE SALIDA: COMPILACION EXITOSA <<< \n" COLOR_RESET);
    printf("  %s\n\n", gppCmd);
    printf("  Progreso: [" COLOR_GREEN "=======================" COLOR_RESET "] 100%%\n\n");
    printf(COLOR_GREEN "  [SUCCESS] COMPILACION Y ENLAZADO COMPLETADOS SIN ERRORES!\n");
    printf("  [ANALYSIS] Fugas de Memoria detectadas: " COLOR_YELLOW "0 bytes" COLOR_GREEN " (Heap 100%% Limpio)\n");
    printf("  [ANALYSIS] Valgrind: heap summary: 0 blocks in use, 0 bytes allocated.\n");
    printf("  [ANALYSIS] Calificacion Obtenida: " COLOR_CYAN COLOR_BOLD "5.0 / 5.0 (GLORIOSO)" COLOR_RESET COLOR_GREEN "\n");
    printf("  [INFO] Lanzando protocolo de graduacion...\n" COLOR_RESET);
    printf("\n  [Presiona ENTER para ver tu nota final...] ");
    fflush(stdout);
    
    while(1) {
        if(kbhit()) {
            int key = getch();
            if (key == '\r' || key == '\n' || key == 13) {
                break;
            }
        }
        usleep(100000);
    }
}
