#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <stdbool.h>
#include <SDL3/SDL_init.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define COLUMN_WIDTH 60
#define HOLE_HEIGHT 60
#define BIRD_LEFT_MARGIN 120
#define BIRD_WIDTH 80
#define BIRD_HEIGHT 30
#define BIRD_RIGHT_X (BIRD_LEFT_MARGIN + BIRD_WIDTH)
#define PIXELS_PER_SECOND 60

void switchPause();

bool isPauseTrue();

bool isGameOverTrue();

int getMenuFocus();

int getGameOverMenuFocus();

int getAddscore();

void restart();

void gameOverPause();

void birdLimit();

float getColumnX();

float getHoleTopY();

float getHoleBottomY();

float getBirdY();

float getColumnRightX();

float getBirdBottomY();

void updateColumn(const float elapsed);

bool isBirdOvercomeColumn();

bool isBirdInsideHole();

void rectFocusUp();

void rectFocusDown();

void gameOverRectFocusUp();

void gameOverRectFocusDown();

void birdUp();

void birdDown();

void birdFall(const float elapsed);

void checkGameOver();

SDL_AppResult processGameOverMenu();

SDL_AppResult processMenu();

#endif