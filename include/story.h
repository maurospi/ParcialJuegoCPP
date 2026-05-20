#ifndef STORY_H
#define STORY_H

#include "constants.h"

struct RoomStory {
    const char* title;
    const char* description;
    const char* art;
};

const RoomStory GAME_STORY[TOTAL_ROOMS] = {
    {
        "inicio",
    },
    {
        "Parte 1",
    },
    {
        "Parte 2",
    },
    {
        "Parte 3",
    },
    {
        "Parte 4",
    },
    {
        "Parte 5",
    }
};

#endif
