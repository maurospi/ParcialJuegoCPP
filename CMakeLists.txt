cmake_minimum_required(VERSION 3.10)
project(DungeonGame)

# Estándar C++11 para máxima compatibilidad
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorio de cabeceras
include_directories(include)

# Lista de archivos fuente
set(SOURCES
    src/main.cpp
    src/player.cpp
    src/room.cpp
    src/enemy.cpp
    src/inventory.cpp
    src/renderer.cpp
    src/game.cpp
)

# Crear el ejecutable
add_executable(DungeonGame ${SOURCES})

# Mensaje de éxito al configurar
message(STATUS "DungeonGame configurado correctamente. Listo para compilar.")
