#ifndef GAME_COLUMNSTATE_H
#define GAME_COLUMNSTATE_H

#include <stdbool.h>

struct ColumnState {
    float column;
    float rect_hole;
    float column_speed;
};

int GC_columnStateReset();

void GC_randRectHole();

float GC_getColumnX();

float GC_getHoleTopY();

float GC_getColumnState();

void GC_moveColumn(const float elapsed);

float GC_getHoleBottomY();

float GC_getColumnRightX();

void GC_initState();

#endif