#include "room.h"
#include <string.h>

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
        rooms[i].connections.north = NO_ROOM;
        rooms[i].connections.south = NO_ROOM;
        rooms[i].connections.east = NO_ROOM;
        rooms[i].connections.west = NO_ROOM;
        rooms[i].itemType = ITEM_NONE;
        rooms[i].isLocked = 0;
        rooms[i].itemPickedUp = 0;
        rooms[i].visited = 0;
    }

    rooms[0].connections.east = 1;
    rooms[0].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    
    rooms[0].connections.south = 3;
    rooms[0].tiles[MAP_HEIGHT-1][MAP_WIDTH/2] = TILE_DOOR_SOUTH;

    rooms[1].connections.west = 0;
    rooms[1].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    
    rooms[1].connections.east = 2;
    rooms[1].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    
    rooms[1].itemType = ITEM_SWORD;
    rooms[1].itemX = 10; rooms[1].itemY = 5;

    rooms[2].connections.west = 1;
    rooms[2].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    for(int y=2; y<7; y++) rooms[2].tiles[y][10] = TILE_WALL;
    rooms[2].itemType = ITEM_COFFEE;
    rooms[2].itemX = 15; rooms[2].itemY = 12;
    rooms[2].itemPickedUp = 0;

    rooms[3].connections.north = 0;
    rooms[3].tiles[0][MAP_WIDTH/2] = TILE_DOOR_NORTH;
    
    rooms[3].connections.east = 4;
    rooms[3].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    
    rooms[3].itemType = ITEM_KEY;
    rooms[3].itemX = 5; rooms[3].itemY = 5;

    rooms[4].connections.west = 3;
    rooms[4].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    rooms[4].connections.east = 5;
    rooms[4].tiles[MAP_HEIGHT/2][MAP_WIDTH-1] = TILE_DOOR_EAST;
    rooms[4].itemType = ITEM_COFFEE;
    rooms[4].itemX = 15; rooms[4].itemY = 6;
    rooms[4].itemPickedUp = 0;

    rooms[5].connections.west = 4;
    rooms[5].tiles[MAP_HEIGHT/2][0] = TILE_DOOR_WEST;
    rooms[5].isLocked = 1;
    rooms[5].tiles[MAP_HEIGHT/2][MAP_WIDTH/2] = TILE_EXIT;
}

int isTileWalkable(Room *room, int x, int y) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return 0;
    char tile = (*room).tiles[y][x];
    if (tile == TILE_WALL) return 0;
    return 1;
}
