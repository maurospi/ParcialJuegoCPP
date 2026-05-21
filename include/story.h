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
        "BIENVENIDO AL LAB",
        "Ducuarita Junior despierta en el Laboratorio 301. Las pantallas brillan con errores.\n"
        "No recuerda como se durmio, pero sabe que debe entregar el proyecto final.\n"
        "Para ganar la materia, debe adentrarse en los laboratorios y sobrevivir\n"
        "a los temibles desafios del Profe Ducuara. La puerta Este te espera.",
        "      _____________________\n"
        "     |                     |\n"
        "     |   C++ PROJECT v1.0  |\n"
        "     |   [X] Segment Fault |\n"
        "     |   [X] Syntax Error  |\n"
        "     |_____________________|\n"
        "               ||\n"
        "            ___||___\n"
        "           /________\\"
    },
    {
        "EL COMPILADOR OPTIMIZADO",
        "Un area repleta de teclados rotos y manuales viejos de C++.\n"
        "En el centro, sobre un rack de servidores, descansa un compilador optimizado.\n"
        "Su codigo fuente aun brilla con una pureza legendaria.",
        "          /\\\n"
        "         /  \\\n"
        "        | C++|\n"
        "        |____|\n"
        "        |    |\n"
        "        |____|"
    },
    {
        "LABERINTO DE CABLEADO",
        "Una parte del laboratorio esta inundada de cables de red cruzados.\n"
        "Los cables parecen serpientes y las luces de los switches parpadean sin cesar.\n"
        "Escuchas murmullos de estudiantes que perdieron la cordura.",
        "         S---S---S\n"
        "         |   |   |\n"
        "         S---S---S"
    },
    {
        "SALA DE BASES DE DATOS",
        "El brillo de los discos SSD es cegador, pero hay trampas en cada consulta.\n"
        "Entre las tablas SQL, una Llave de Acceso Root espera ser encontrada.\n"
        "Es la unica forma de abrir la puerta del examen final.",
        "        ________\n"
        "       [________]\n"
        "       [________]\n"
        "       [________]"
    },
    {
        "PASILLO DE LAS NOTAS",
        "El frio en este pasillo congela tus ganas de programar.\n"
        "Espectros de notas reprobadas flotan a tu alrededor, susurrando reclamos.\n"
        "Los promedios bajos no perdonan a nadie en esta facultad.",
        "           .-.\n"
        "          ( 0 )\n"
        "           `-'\n"
        "
        "
    },
    {
        "EL EXAMEN FINAL",
        "Has llegado al laboratorio principal. La aprobacion esta tras esa puerta.\n"
        "Pero el mismisimo Profe Ducuara no te dejara pasar sin defender su materia.\n"
        "Prepara tus punteros, estudiante, y demuestra tu nivel!",
        "          .--------.\n"
        "         /  _    _  \\\n"
        "        |  (o)  (o)  |\n"
        "        |    /\\      |\n"
        "        |   |__|     |\n"
        "         \\  \\__/    /\n"
        "          '--------'"
    }
};

#endif
