#ifndef SCENE_H
#define SCENE_H


#include "grid.h"
#include "particle.h"



class Scene
{
private:
    Grid grid;
    Particles particles;
    GLfloat angle_x, angle_y, angle_z;

    GLuint texParticle, texBackground;

    unsigned short nParticles;
public:
    Scene();
    ~Scene();

    void draw();
    void init();

    void print();
    void update();
    void setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z);
    void getAngles(GLfloat *ang_x, GLfloat *ang_y, GLfloat *ang_z);
};

#endif /* SCENE_H */

