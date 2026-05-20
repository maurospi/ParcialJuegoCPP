#ifndef AUDIO_H
#define AUDIO_H

#include <stdio.h>
#include "constants.h"

// Función para emitir un pitido del sistema (PC Speaker)
inline void playBeep(int frequency) {
    printf("\a");
    fflush(stdout);
}

// Efectos de sonido visuales (On-Screen SFX)
static const char* SFX_ATTACK = COLOR_YELLOW " ¡ZAS! " COLOR_RESET;
static const char* SFX_DAMAGE = COLOR_RED " ¡AUCH! " COLOR_RESET;
static const char* SFX_PICKUP = COLOR_GREEN " ¡CLINK! " COLOR_RESET;
static const char* SFX_DOOR   = COLOR_BLUE " *CREEEAK* " COLOR_RESET;

#endif
