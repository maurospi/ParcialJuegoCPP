#ifndef ROOM_H
#define ROOM_H

#include "types.h"

void initRooms(Room *rooms);

int isTileWalkable(Room *room, int x, int y);

#endif
