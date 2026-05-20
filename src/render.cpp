#include "renderer.h"
#include "input.h"
#include "story.h"
#include "sprites.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static const char *itemNames[3] = {"Vacio", "Espada Sagrada", "Llave Maestra"};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

void drawStoryScreen(int roomIndex) {
    clearScreen();
    printf(COLOR_CYAN COLOR_BOLD "\n  === %s ===\n\n" COLOR_RESET, GAME_STORY[roomIndex].title);
    printf(COLOR_YELLOW "%s\n\n" COLOR_RESET, GAME_STORY[roomIndex].art);
    printf(COLOR_WHITE "%s\n\n" COLOR_RESET, GAME_STORY[roomIndex].description);
    printf(COLOR_BOLD "  Presiona cualquier tecla para entrar..." COLOR_RESET);
    while (!kbhit()) usleep(100000);
    getch();
}

void drawRoom(Room *rooms, Player *player, Enemy *enemies, int enemyCount) {
    int row, col, e;
    int rIdx = (*player).currentRoom;
    
    if (rooms[rIdx].visited == 0) {
        drawStoryScreen(rIdx);
        rooms[rIdx].visited = 1;
    }

    printf(COLOR_BOLD "\n  SALA: %s\n" COLOR_RESET, GAME_STORY[rIdx].title);
    printf(COLOR_BOLD "  ╔");
    for (int i = 0; i < MAP_WIDTH*2; i++) printf("═");
    printf("╗\n" COLOR_RESET);

    for (row = 0; row < MAP_HEIGHT; row++) {
        printf(COLOR_BOLD "  ║ " COLOR_RESET);
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
                printf("%s", (rooms[rIdx].itemType == ITEM_SWORD ? SPR_SWORD : SPR_KEY));
            } 
            else if (tile == TILE_WALL) printf("%s", TXT_WALL_LIGHT);
            else if (tile == TILE_FLOOR) printf("%s", TXT_FLOOR);
            else if (tile == TILE_EXIT) printf("%s", SPR_EXIT);
            else if (tile == TILE_TREE) printf("%s", SPR_TREE);
            else if (tile == TILE_ROCK) printf("%s", SPR_ROCK);
            else printf(COLOR_YELLOW "[]" COLOR_RESET);
        }
        printf(COLOR_BOLD " ║\n" COLOR_RESET);
    }
    printf(COLOR_BOLD "  ╚");
    for (int i = 0; i < MAP_WIDTH*2; i++) printf("═");
    printf("╝\n" COLOR_RESET);
}

void drawHUD(Player *player, int roomIndex) {
    printf("\n  Vida: ");
    for (int h = 0; h < (*player).health; h++) printf(ICON_HEART);
    printf("\n  Inventario: ");
    for (int i = 0; i < 3; i++) {
        if (i == (*player).inventory.selectedSlot) printf(COLOR_CYAN ">[%s]< " COLOR_RESET, itemNames[(*player).inventory.items[i]]);
        else printf("[%s] ", itemNames[(*player).inventory.items[i]]);
    }
    printf("\n  " COLOR_BOLD "CONTROLES:" COLOR_RESET " [WASD] Mover  [E] Recoger  [1-3] Seleccionar  [X] Atacar  [M] Mapa\n");
}

void drawMessage(const char *message) { printf(COLOR_YELLOW "  >> %s\n" COLOR_RESET, message); }
void drawGameOver() { printf(COLOR_RED COLOR_BOLD "\n  HAS PERDIDO...\n" COLOR_RESET); }
void drawVictory() { printf(COLOR_GREEN COLOR_BOLD "\n  ¡VICTORIA!\n" COLOR_RESET); }
