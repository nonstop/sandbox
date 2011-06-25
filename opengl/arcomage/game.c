#include <stdlib.h>

#include "game.h"
#include "scene.h"
#include "utils.h"

struct Game
{
    Stat our, enemy;
} game;

typedef struct Card
{
    CardAction our, enemy;
} Card;
Card cards[5];

const Stat* game_stat_our()
{
    return &game.our;
}

const Stat* game_stat_enemy()
{
    return &game.enemy;
}

static void game_apply_action__(const CardAction* ca, int target, Stat* st)
{
    if (ca->tower) {
        st->tower += ca->tower;
        if (st->tower > st->maxTower) {
            st->tower = st->maxTower;
        }
        scene_animate_tower(target, st->tower);
    }
    if (ca->wall) {
        st->wall += ca->wall;
        if (st->wall > st->maxWall) {
            st->wall = st->maxWall;
        }
        scene_animate_wall(target, st->wall);
    }
    TRACE("%s %d/%d", (target ? "enemy" : "our"), st->tower, st->wall);
}

void game_apply_action(int cardIdx)
{
    game_apply_action__(&cards[cardIdx].our, 0, &game.our);
    game_apply_action__(&cards[cardIdx].enemy, 1, &game.enemy);
}

void game_init_demo()
{
    game.our.tower = 100 + (rand() % 2 ? 1 : -1) * rand() % 25;
    game.our.maxTower = 125;
    game.our.wall = 100 + (rand() % 2 ? 1 : -1) * rand() % 25;
    game.our.maxWall = 125;

    game.enemy = game.our;

    TRACE("our %d/%d enemy %d/%d", game.our.tower, game.our.wall, game.enemy.tower, game.enemy.wall);
    int i = 0;
    for (; i < 5; ++i) {
        cards[i].our.tower = (rand() % 2 ? 1 : -1) * rand() % 15;
        cards[i].our.wall = (rand() % 2 ? 1 : -1) * rand() % 15;
        cards[i].enemy.tower = (rand() % 2 ? 1 : -1) * rand() % 15;
        cards[i].enemy.wall = (rand() % 2 ? 1 : -1) * rand() % 15;
        TRACE("%d our %d/%d enemy %d/%d", (i + 1), cards[i].our.tower, cards[i].our.wall,
                cards[i].enemy.tower, cards[i].enemy.wall);
    }
}

