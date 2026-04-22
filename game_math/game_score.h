#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#include <stdbool.h>

struct Score {
    bool flag;
    int addscore;
};

int GS_getAddscore();

int GS_addscoreReset();

bool GS_scoreFlagTrue();

bool GS_isScoreFlagTrue();

bool GS_changeScoreFlag();

int GS_addScore();

#endif