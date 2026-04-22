#include "game_columnState.h"
#include <SDL3/SDL_init.h>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640
#define HOLE_HEIGHT 60
#define COLUMN_WIDTH 60

static struct ColumnState columnState;

int GC_columnStateReset() {
    columnState.column = 1;
    return columnState.column;
}

void GC_randRectHole() {
    columnState.rect_hole = SDL_randf() * ((float)(WINDOW_HEIGHT - HOLE_HEIGHT) / WINDOW_HEIGHT);
}

float GC_getColumnX()
{
    return columnState.column * WINDOW_WIDTH;
}

float GC_getHoleTopY()
{
    return columnState.rect_hole * WINDOW_HEIGHT;
}

float GC_getColumnState() {
    return columnState.column;
}

void GC_moveColumn(const float elapsed) {
    columnState.column -= columnState.column_speed * elapsed;
}

float GC_getHoleBottomY()
{
    return GC_getHoleTopY() + HOLE_HEIGHT * 2;
}

float GC_getColumnRightX()
{
    return GC_getColumnX() + COLUMN_WIDTH;
}

void GC_initState() {
    GC_columnStateReset();
    columnState.rect_hole = 0.5;
    columnState.column_speed = 0.18;
}