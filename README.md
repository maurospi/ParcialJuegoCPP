# Dungeon Escape

**Proyecto:** Parcial Final — Videojuego en C++
**Asignatura:** Programación I
**Semestre:** 2026-1

**Integrantes:**
- Fabián Ospina
- Nicolas Bayona

---

## Descripción

**Dungeon Escape** es un videojuego de tipo *dungeon crawler* top-down con renderizado en consola ASCII. El jugador controla al personaje `@` y debe explorar 6 habitaciones conectadas, encontrar la **Llave** (`K`), desbloquear la **sala final** y llegar a la **salida** (`E`) sin morir.

El proyecto está inspirado visualmente en **Adventure (Atari 2600)** y **The Legend of Zelda (NES)**, y fue desarrollado íntegramente en C++ usando únicamente la biblioteca estándar.

---

## Mecánicas del juego

| Elemento | Descripción |
|---|---|
| `@` | Jugador controlable con W/A/S/D |
| `G` | Enemigo tipo Guardia — persigue en línea recta |
| `S` | Enemigo tipo Fantasma — persigue en diagonal, atraviesa paredes |
| `/` | Espada — permite atacar enemigos adyacentes |
| `K` | Llave — desbloquea la sala final |
| `E` | Salida — pararse aquí con la llave usada = victoria |
| `#` | Pared — bloquea el movimiento |
| `^v><` | Puertas entre habitaciones |

### Controles

| Tecla | Acción |
|---|---|
| `W` | Mover arriba |
| `S` | Mover abajo |
| `A` | Mover izquierda |
| `D` | Mover derecha |
| `E` | Recoger objeto (pararse encima) |
| `Q` | Soltar objeto |
| `X` | Atacar (requiere Espada) |

### Condición de victoria

Entrar a la **Sala 5 (Exit Chamber)** con la llave y pararse sobre el tile `E`.

### Condición de derrota

La salud del jugador llega a **0** por contacto con enemigos.

---

## Mapa de habitaciones

```
[0: Entry Hall] --east--> [1: Guard Room] --east--> [2: Dark Corridor]
      |                                                      |
    south                                                  south
      |                                                      |
[3: Key Room]  --east--> [4: Ghost Room] --east--> [5: Exit Chamber] (LOCKED)
```

---

## Estructura del proyecto

```
DungeonGame/
├── assets/
├── include/
│   ├── constants.h     <- Todas las constantes del juego
│   ├── types.h         <- Estructuras: Player, Enemy, Room, Inventory
│   ├── player.h        <- Declaraciones del módulo jugador
│   ├── room.h          <- Declaraciones del módulo de habitaciones
│   ├── enemy.h         <- Declaraciones del módulo de enemigos
│   ├── inventory.h     <- Declaraciones del módulo de inventario
│   ├── renderer.h      <- Declaraciones del módulo de renderizado
│   └── game.h          <- Declaraciones del módulo principal
├── src/
│   ├── main.cpp        <- Punto de entrada y game loop
│   ├── game.cpp        <- Lógica principal, victoria y derrota
│   ├── player.cpp      <- Movimiento, colisiones, pick up, drop
│   ├── room.cpp        <- Inicialización de las 6 habitaciones
│   ├── enemy.cpp       <- IA de persecución, colisión con jugador
│   ├── inventory.cpp   <- Manejo del inventario de un slot
│   └── renderer.cpp    <- Renderizado ASCII en consola
├── CMakeLists.txt
└── README.md
```

---

## Compilación

### Requisitos

- CMake 3.10 o superior
- Compilador C++11 (GCC, Clang o MSVC)

### Windows

```cmd
mkdir build
cd build
cmake ..
cmake --build .
DungeonGame.exe
```

### Linux / Mac

```bash
mkdir build
cd build
cmake ..
make
./DungeonGame
```

---

## Decisiones técnicas

- **Arreglos estáticos:** todos los enemigos y habitaciones se almacenan en arreglos de tamaño fijo (`Enemy enemies[10]`, `Room rooms[6]`). No se usa `new` ni `delete` en el game loop.
- **Punteros:** el jugador, las habitaciones y los enemigos se pasan por puntero a todas las funciones para demostrar uso verificable de punteros.
- **Sin `using namespace std`:** todo acceso a la biblioteca estándar es explícito.
- **Sin operador ternario:** toda lógica condicional usa `if/else` explícito.
- **Sin `auto`, lambdas ni templates avanzados:** código compatible con C++11 básico.

---

**Disclaimer de IA:**
Algunas partes del código, como la lógica de colisiones, el diseño de la interfaz ASCII y ciertas estructuras, fueron generadas o sugeridas por Inteligencia Artificial para cumplir con los requerimientos del proyecto y mejorar la experiencia de usuario.
