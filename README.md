# GoNe

A 2D/3D game built with a lightweight single-header C game engine.

## Engine Features

- **3D rendering** — PBR materials, dynamic lights, shadow mapping (CSM/VSM), cubemaps, environment maps, post-FX pipeline
- **2D rendering** — sprites, spritesheets, tilemaps (Tiled .tmx), bitmap fonts, UI system
- **Asset pipeline** — automatic cooking & compression, virtual filesystem with zip archive mounting
- **Audio** — WAV, MP3, MIDI, MOD/XM, SFXR support; 3D positional audio
- **Physics & collision** — ray casting, sphere/capsule/AABB/plane hit tests, frustum culling
- **AI** — A* pathfinding, behavior trees, swarm/boids simulation
- **Networking** — net synchronization demo included
- **Scripting** — embedded Lua + Teal (typed Lua) with FFI access to all C APIs
- **Animation** — sprite animation, Spine skeletal animation, 3D model animation (Assimp/FBX)
- **Editor** — built-in editor with gizmos, scene graph, property editor, cook-on-demand
- **Cross-platform** — Windows, Linux, macOS, Emscripten (Web)
- **Compilers** — MSVC, MinGW, TCC, GCC, Clang, clang-cl, Emscripten

## Language

The game and its engine are written in **C** (C99/C11).  
Scripting support is provided via **Lua** and **Teal** (typed Lua).

## Credits

- **Game**: Made by **TIGames**
- **2D Assets**: Most 2D art & sprites by 🐲 **Dragon Mate2000** 🐉

---

*Built with ❤️ and a lot of C.*

