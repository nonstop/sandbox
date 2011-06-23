#include "game.h"

struct Game
{
    int ourTowerHeight, enemyTowerHeight;
    int ourWallHeight, enemyWallHeight;
} game;

int game_our_tower_height()
{
    return game.ourTowerHeight;
}

int game_enemy_tower_height()
{
    return game.enemyTowerHeight;
}

int game_our_wall_height()
{
    return game.ourWallHeight;
}

int game_enemy_wall_height()
{
    return game.enemyWallHeight;
}

void game_apply_action(const CardAction* our, const CardAction* enemy)
{
    game.ourTowerHeight += our->tower;
    game.ourWallHeight += our->wall;
    game.enemyTowerHeight += enemy->tower;
    game.enemyWallHeight += enemy->wall;
}
