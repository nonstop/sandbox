#ifndef SCENE_H
#define SCENE_H

#include "grid.h"
#include "particle.h"

class Scene
{
public:
    Scene();
    ~Scene();

    void draw();
    void init();

    void update();
private:
    const unsigned short nParticles;

    Grid grid;
    Particles particles;
    GLfloat angle_x, angle_y, angle_z;
};

#endif /* SCENE_H */

