#ifndef ARCOMAGE_SCENE_H
#define ARCOMAGE_SCENE_H

void scene_init(int width, int height);
void scene_resize(int width, int height);
void scene_draw();
void scene_on_timer();
int scene_in_animation_mode();

void scene_animate_tower(int target, int newHeight);
void scene_animate_wall(int target, int newHeight);

#endif /* ARCOMAGE_SCENE_H */

