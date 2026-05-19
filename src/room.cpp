#include "room.h"
#include <string.h>
#include <stdlib.h>

void initRooms(Room *rooms) {
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1)
                    rooms[i].tiles[y][x] = TILE_WALL;
                else
                    rooms[i].tiles[y][x] = TILE_FLOOR;
            }
        }
        rooms[i].connections = {NO_ROOM, NO_ROOM, NO_ROOM, NO_ROOM};
        rooms[i].itemType = ITEM_NONE;
        rooms[i].itemPickedUp = 0;
        rooms[i].isLocked = 0;
        rooms[i].visited = 0;
    }

    rooms[0].connections.east = 1;
    rooms[0].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    rooms[0].visited = 1;

    rooms[1].connections.west = 0;
    rooms[1].connections.east = 2;
    rooms[1].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    rooms[1].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    rooms[1].itemType = ITEM_SWORD;
    rooms[1].itemX = 10; rooms[1].itemY = 5;

    rooms[2].connections.west = 1;
    rooms[2].connections.south = 5;
    rooms[2].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    rooms[2].tiles[MAP_HEIGHT-1][MAP_WIDTH/2] = TILE_DOOR_SOUTH;
    for (int i = 0; i < 10; i++) rooms[2].tiles[rand()%13+1][rand()%38+1] = TILE_TREE;

    rooms[3].connections.east = 4;
    rooms[3].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    rooms[3].itemType = ITEM_KEY;
    rooms[3].itemX = 20; rooms[3].itemY = 7;

    rooms[4].connections.west = 3;
    rooms[4].connections.east = 5;
    rooms[4].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    rooms[4].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;

    rooms[5].connections.west = 4;
    rooms[5].connections.north = 2;
    rooms[5].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    rooms[5].tiles[0][MAP_WIDTH/2] = TILE_DOOR_NORTH;
    rooms[5].tiles[MAP_HEIGHT/2][MAP_WIDTH-2] = TILE_EXIT;
    rooms[5].isLocked = 1;
}