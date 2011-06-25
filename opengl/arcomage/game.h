#ifndef ARCOMAGE_GAME_H
#define ARCOMAGE_GAME_H

typedef struct CardAction
{
    int tower, wall;
} CardAction;

typedef struct Stat
{
    int tower, wall;
    int maxTower, maxWall;
} Stat;

const Stat* game_stat_our();
const Stat* game_stat_enemy();

void game_apply_action(int cardIdx);
    
void game_init_demo();

#endif /* ARCOMAGE_GAME_H */

