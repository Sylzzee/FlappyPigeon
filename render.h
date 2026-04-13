#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_log.h>

#define MENURECT_LEFT_MARGIN 160
#define MENURECT_WIDTH 320
#define MENURECT_HEIGHT 60
#define TEXT_SIZE 20

SDL_AppResult Game_Init();

void drawBackground();

void drawColumn();

void drawBird();

void drawRectFocus(int rect_focus);

void drawGameOverRectFocus(int game_over_rect_focus);

void drawMenuRects();

void drawGameOverMenuRects();

void drawScore();

void drawMenuText(const Uint64 now);

void drawGameOverMenuText(const Uint64 now);

void processBird(const float elapsed);

void processColumn(const float elapsed);

void drawMenu(const Uint64 now);

void drawGameOverMenu(const Uint64 now);

void gameRender();

#endif