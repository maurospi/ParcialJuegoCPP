#include "player.h"
#include "room.h"
#include <stdio.h>

void initPlayer(Player *player) {
    (*player).x = PLAYER_START_X;
    (*player).y = PLAYER_START_Y;
    (*player).health = 3;
    (*player).currentRoom = PLAYER_START_ROOM;
    for(int i=0; i<3; i++) (*player).inventory.items[i] = ITEM_NONE;
    (*player).inventory.selectedSlot = 0;
}

int movePlayer(Player *player, int dx, int dy, Room *rooms) {
    int newX = (*player).x + dx;
    int newY = (*player).y + dy;
    int rIdx = (*player).currentRoom;

    if (isTileWalkable(&rooms[rIdx], newX, newY)) {
        char tile = rooms[rIdx].tiles[newY][newX];
        
        int nextRoom = NO_ROOM;
        if (tile == TILE_DOOR_NORTH) nextRoom = rooms[rIdx].connections.north;
        else if (tile == TILE_DOOR_SOUTH) nextRoom = rooms[rIdx].connections.south;
        else if (tile == TILE_DOOR_EAST) nextRoom = rooms[rIdx].connections.east;
        else if (tile == TILE_DOOR_WEST) nextRoom = rooms[rIdx].connections.west;

        if (nextRoom != NO_ROOM) {
            int hasKey = 0;
            for(int i=0; i<3; i++) if((*player).inventory.items[i] == ITEM_KEY) hasKey = 1;
            if (rooms[nextRoom].isLocked && !hasKey) {
                return -1;
            }
            (*player).currentRoom = nextRoom;
            if (tile == TILE_DOOR_NORTH) { (*player).x = MAP_WIDTH / 2; (*player).y = MAP_HEIGHT - 2; }
            else if (tile == TILE_DOOR_SOUTH) { (*player).x = MAP_WIDTH / 2; (*player).y = 1; }
            else if (tile == TILE_DOOR_EAST) { (*player).x = 1; (*player).y = MAP_HEIGHT / 2; }
            else if (tile == TILE_DOOR_WEST) { (*player).x = MAP_WIDTH - 2; (*player).y = MAP_HEIGHT / 2; }
            return 1;
        }

        (*player).x = newX;
        (*player).y = newY;
        return 1;
    }
    return 0;
}

int pickUpItem(Player *player, Room *room) {
    if ((*room).itemType != ITEM_NONE && (*room).itemPickedUp == 0) {
        if ((*player).x == (*room).itemX && (*player).y == (*room).itemY) {
            if ((*room).itemType == ITEM_COFFEE) {
                if ((*player).health < 3) {
                    (*player).health++;
                    (*room).itemPickedUp = 1;
                    return 3;
                } else {
                    return 2;
                }
            }
            for(int i=0; i<3; i++) {
                if ((*player).inventory.items[i] == ITEM_NONE) {
                    (*player).inventory.items[i] = (*room).itemType;
                    (*room).itemPickedUp = 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int dropItem(Player *player, Room *room) {
    int slot = (*player).inventory.selectedSlot;
    if ((*player).inventory.items[slot] != ITEM_NONE) {
        if ((*room).itemType == ITEM_NONE || (*room).itemPickedUp == 1) {
            (*room).itemType = (*player).inventory.items[slot];
            (*room).itemX = (*player).x;
            (*room).itemY = (*player).y;
            (*room).itemPickedUp = 0;
            (*player).inventory.items[slot] = ITEM_NONE;
            return 1;
        }
    }
    return 0;
}

void damagePlayer(Player *player, int amount) {
    (*player).health -= amount;
    if ((*player).health < 0) (*player).health = 0;
}

int isPlayerAlive(Player *player) {
    return ((*player).health > 0);
}
