#ifndef ARCOMAGE_GAME_H
#define ARCOMAGE_GAME_H

typedef struct CardAction
{
    int tower, wall;
} CardAction;

int game_our_tower_height();
int game_enemy_tower_height();
int game_our_wall_height();
int game_enemy_wall_height();

void game_apply_action(const CardAction* our, const CardAction* enemy);
    
void game_init_demo();

#endif /* ARCOMAGE_GAME_H */

