#include <stdlib.h>

#include "game.h"
#include "scene.h"
#include "utils.h"

typedef struct Stat
{
    int tower, wall;
} Stat;

struct Game
{
    Stat our, enemy;
} game;

int game_our_tower_height()
{
    return game.our.tower;
}

int game_enemy_tower_height()
{
    return game.enemy.tower;
}

int game_our_wall_height()
{
    return game.our.wall;
}

int game_enemy_wall_height()
{
    return game.enemy.wall;
}

static void game_apply_action__(const CardAction* ca, int target, Stat* st)
{
    if (ca->tower) {
        st->tower += ca->tower;
        scene_animate_tower(target, st->tower);
    }
    if (ca->wall) {
        st->wall += ca->wall;
        scene_animate_wall(target, st->tower);
    }
}

void game_apply_action(const CardAction* our, const CardAction* enemy)
{
    game_apply_action__(our, 0, &game.our);
    game_apply_action__(enemy, 1, &game.enemy);
}

void game_init_demo()
{
    game.our.tower = 100 + (rand() % 2 ? 1 : -1) * rand() % 25;
    game.our.wall = 100 + (rand() % 2 ? 1 : -1) * rand() % 25;

    game.enemy = game.our;

    TRACE("our %d/%d enemy %d/%d", game.our.tower, game.our.wall, game.enemy.tower, game.enemy.wall);
}

