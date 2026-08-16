# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A small Flappy-Bird clone in C17 (`FlappyPigeon`) built on SDL3 + SDL3_image, using SDL3's callback-based app model (`SDL_MAIN_USE_CALLBACKS`). There is also an unrelated second CMake target, `homework` (`homework.c`, a plain "Hello world" `main()`) — leftover coursework scaffolding, not part of the game; don't assume changes to one affect the other.

## Build

Windows + MSVC + Ninja. SDL3 and SDL3_image are external dev packages found via `find_package`, not vendored — their CMake config dirs must be pointed to explicitly (there is no vcpkg manifest or CMakePresets.json in this repo):

```
cmake -B build -G Ninja -DSDL3_DIR=<path-to-SDL3>/cmake -DSDL3_image_DIR=<path-to-SDL3_image>/cmake
cmake --build build
```

If `build/CMakeCache.txt` already exists with those paths cached, a plain `cmake --build build` is enough.

- MSVC builds use `/W4 /WX /permissive- /sdl` (see [CMakeLists.txt](CMakeLists.txt)) — **warnings are errors**, so any new warning breaks the build.
- No test suite and no lint config exist in this repo.
- Output binaries land in `build/<Config>/` (e.g. `build/Debug/FlappyPigeon.exe`), matching `CMAKE_RUNTIME_OUTPUT_DIRECTORY`.

### Running

Asset loading (`render.c`, `sound.c`) uses plain relative paths (e.g. `"background.bmp"`, `SDL_LoadWAV("1-02 - Moon in One's Cup.wav", ...)`) resolved against the **process working directory**, not the executable's location. The build copies every asset from `CMAKE_SOURCE_DIR` into the output dir (see the `FLAPPY_PIGEON_ASSETS` loop at the bottom of [CMakeLists.txt](CMakeLists.txt)), so the exe must be *run with its own directory as cwd* (e.g. `cd build\Debug; .\FlappyPigeon.exe`) — running it from elsewhere with a relative reference will fail to find its assets even though they exist on disk.

When adding a new asset file, add it to both the source tree root and the `FLAPPY_PIGEON_ASSETS` list in CMakeLists.txt, and make sure it's actually committed to git — a file only present in the working tree (untracked) will be missing after a fresh clone even though local builds work fine.

## Architecture

Per-frame flow, driven by SDL3's callbacks in [main.c](main.c):

```
SDL_AppIterate → processMath() → gameRender()
```

- **[main.c](main.c)** — `SDL_AppInit`/`SDL_AppEvent`/`SDL_AppIterate`/`SDL_AppQuit`. Owns input handling (arrow keys move the bird or navigate menus depending on pause/game-over state; Space selects; Esc pauses; Q quits) and a crude frame counter that retriggers the flapping sound effect periodically.
- **[game_math.c](game_math.c)/[.h](game_math.h)** — the per-frame "model" step. `processMath()` advances physics/state and packs everything the renderer needs into one `GameFrameData` struct (bird rect, both column rects, window size, score, pause/game-over flags + menu focus indices). This struct is the sole data contract between the model and the renderer — no other cross-talk.
- **[game_math_priv.c](game_math_priv.c)/[.h](game_math_priv.h)** — internal game rules: bird gravity/limits (`birdFall`, `birdLimit`), collision detection (`isBirdOvercomeColumn`/`isBirdInsideHole`), and menu action dispatch (`processMenu`/`processGameOverMenu` → continue/restart/exit). Also defines the core game constants (`WINDOW_WIDTH/HEIGHT`, `COLUMN_WIDTH`, `HOLE_HEIGHT`, bird geometry).
- **[game_math/](game_math/)** — three independent state modules, each a small singleton: a file-local `static struct` instance plus a `GX_`-prefixed function API (`GP_*` for pause/menu state in `game_pause.c`, `GS_*` for scoring in `game_score.c`, `GC_*` for column position/hole/speed in `game_columnState.c`). There's no instance/handle passed around — follow this same static-singleton pattern if adding another state module.
  - Note: `game_columnState.c` redefines `WINDOW_WIDTH/HEIGHT`, `HOLE_HEIGHT`, `COLUMN_WIDTH` locally instead of including them from `game_math_priv.h`. These must be kept in sync by hand — a past bug came from `HOLE_HEIGHT` drifting between the two definitions.
- **[render.c](render.c)/[.h](render.h)** — all SDL drawing, driven entirely by the `GameFrameData` passed in each frame: background/bird/column textures, pause and game-over menu rectangles + `SDL_RenderDebugText` labels, score display. Textures are loaded once in `Game_Init` and reused.
- **[sound.c](sound.c)/[.h](sound.h)** — WAV loading via `SDL_LoadWAV`/`SDL_AudioStream`. Background music is started once in `GameSound_Init`; the flapping SFX (`FlappingSound`) opens a fresh audio stream and reloads the WAV from disk on every call rather than reusing/stopping the previous one.

Some comments in `render.c`/`sound.c` are in Ukrainian — match that when extending comments in those specific files rather than switching the whole file to English.
