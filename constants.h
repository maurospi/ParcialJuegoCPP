#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;
const int TOTAL_ROOMS = 6;
const int TOTAL_ENEMIES = 10;
const int PLAYER_START_HEALTH = 5;
const int PLAYER_START_ROOM = 0;
const int PLAYER_START_X = 2;
const int PLAYER_START_Y = 2;
const int ENEMY_DAMAGE = 1;

const char TILE_WALL = '#';
const char TILE_FLOOR = '.';
const char TILE_DOOR_NORTH = '^';
const char TILE_DOOR_SOUTH = 'v';
const char TILE_DOOR_EAST = '>';
const char TILE_DOOR_WEST = '<';
const char TILE_ITEM = '*';
const char TILE_KEY = 'K';
const char TILE_EXIT = 'E';

const char CHAR_PLAYER = '@';
const char CHAR_ENEMY_ONE = 'G';
const char CHAR_ENEMY_TWO = 'S';

const int NO_ROOM = -1;
const int ITEM_NONE = 0;
const int ITEM_SWORD = 1;
const int ITEM_KEY = 2;

const int ENEMY_TYPE_ONE = 0;
const int ENEMY_TYPE_TWO = 1;

const int STATE_PLAYING = 0;
const int STATE_WIN = 1;
const int STATE_LOSE = 2;
const int VICTORY_ROOM = 5;

#endif