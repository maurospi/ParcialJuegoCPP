#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 15;
const int TOTAL_ROOMS = 6;
const int NO_ROOM = -1;
const int TOTAL_ENEMIES = 10;
const int PLAYER_START_HEALTH = 5;
const int PLAYER_START_X = 2;
const int PLAYER_START_Y = 2;
const int PLAYER_START_ROOM = 0;

const char TILE_WALL = '#';
const char TILE_FLOOR = '.';
const char TILE_EXIT = 'E';
const char TILE_DOOR_NORTH = '^';
const char TILE_DOOR_SOUTH = 'v';
const char TILE_DOOR_EAST = '>';
const char TILE_DOOR_WEST = '<';
const char TILE_TREE = 'T';
const char TILE_ROCK = 'R';

const int ITEM_NONE = 0;
const int ITEM_SWORD = 1;
const int ITEM_KEY = 2;

const int ENEMY_TYPE_GUARD = 0;
const int ENEMY_TYPE_GHOST = 1;
const int ENEMY_DAMAGE = 1;

const int STATE_PLAYING = 0;
const int STATE_WIN = 1;
const int STATE_LOSE = 2;
//COLORES HECHOS POR IA
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

#define ICON_HEART "❤ "

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

#endif
