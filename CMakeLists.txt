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

# Configuración de bibliotecas según la plataforma
if(WIN32)
    # En Windows, necesitamos winmm para el audio
    target_link_libraries(DungeonGame winmm)
elseif(APPLE)
    # En macOS, no necesitamos winmm y podemos agregar flags específicos si fuera necesario
    message(STATUS "Configurando para macOS")
elseif(UNIX)
    # En Linux, configuración estándar de Unix
    message(STATUS "Configurando para Linux")
endif()

# Guardar el ejecutable directamente en la carpeta raíz del proyecto
set_target_properties(DungeonGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Mensaje de éxito al configurar
message(STATUS "DungeonGame configurado correctamente para ${CMAKE_SYSTEM_NAME}. Listo para compilar.")
