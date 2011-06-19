#ifndef ARCOMAGE_SCENE_H
#define ARCOMAGE_SCENE_H

struct Scene* scene_new(int width, int height);
void scene_delete(struct Scene* scene);
void scene_resize(struct Scene* scene, int width, int height);
void scene_draw(const struct Scene* scene);
void scene_on_timer(struct Scene* scene);
int scene_in_animation_mode(const struct Scene* scene);
void scene_start_animation(struct Scene* scene);

#endif /* ARCOMAGE_SCENE_H */

