#include "game_score.h"

static struct Score score;

int GS_getAddscore()
{
    return score.addscore;
}

void GS_addscoreReset() {
    score.addscore = 0;
}

bool GS_scoreFlagTrue() {
    score.flag = true;
    return score.flag;
}

bool GS_isScoreFlagTrue() {
    return score.flag;
}

bool GS_changeScoreFlag() {
    score.flag = false;
    return score.flag;
}

int GS_addScore() {
    score.addscore++;
    return score.addscore;
}