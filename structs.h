#ifndef TYPES_H
#define TYPES_H
#include "constants.h"

struct Inventory {
    int itemType;
    char itemChar;
};

struct Player {
    int x;
    int y;
    int health;
    int currentRoom;
    Inventory inventory;
};

struct Enemy {
    int x;
    int y;
    int health;
    int type;
    int roomIndex;
    int alive;
};

struct RoomConnections {
    int north;
    int south;
    int east;
    int west;
};

struct Room {
    char tiles[MAP_HEIGHT][MAP_WIDTH];
    RoomConnections connections;
    int itemType;
    int itemX;
    int itemY;
    int itemPickedUp;
    int isLocked;
    int visited;
};

#endif