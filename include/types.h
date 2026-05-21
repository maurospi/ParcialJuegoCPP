#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

struct Inventory
{
    int items[3];
    int selectedSlot;
};

struct Player
{
    int x;
    int y;
    int health;
    int currentRoom;
    Inventory inventory;
};

struct Enemy
{
    int x;
    int y;
    int health;
    int type;
    int roomIndex;
    int alive;
    char name[30];
};

struct RoomConnections
{
    int north;
    int south;
    int east;
    int west;
};

struct Room
{
    char tiles[MAP_HEIGHT][MAP_WIDTH];
    RoomConnections connections;
    int itemType;
    int itemX;
    int itemY;
    int itemPickedUp;
    int isLocked;
    int visited;
};

struct HighScore {
    char name[20];
    int score;
};

struct GameState {
    Player player;
    Enemy enemies[TOTAL_ENEMIES];
    Room rooms[TOTAL_ROOMS];
    int state;
    int turnCount;
    int enemyKills;
    int damageReceived;
    int difficulty;
    int enemySpeed;
    char lastMessage[100];
    HighScore topScores[3];
};

#endif
