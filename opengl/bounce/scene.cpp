#include "textures.h"
#include "scene.h"

Scene::Scene ()
    : nParticles(150), 
    angle_x(0), angle_y(0), angle_z(0)
{}

Scene::~Scene ()
{
    if (glIsList(IL_GRID) == GL_TRUE)
        glDeleteLists(IL_GRID, 1);
    if (glIsList(IL_PARTICLE) == GL_TRUE)
        glDeleteLists(IL_PARTICLE, 1);
}


// prevent from starting with the same coords, true - good position
static bool checkParticlePos(const Particle& p, const Particles& particles)
{
    for (ParticlesConstIt it = particles.begin(); it != particles.end(); ++it) {
        if (p == *it)
            return false;
    }
    return true;
}

void Scene::init ()
{
    GLuint texParticle, texBackground;

    loadTexture("particle.bmp", &texParticle);
    loadTexture("background.bmp", &texBackground);

    grid.init(40.0, 10.0, 40.0);

    for (int i=0; i<nParticles; i++) {
        Particle ptcl(grid);

        do {
            ptcl.setTrace();
        } while (!checkParticlePos(ptcl, particles));

        particles.push_back(ptcl);
    }

// Imagelist for particle
    glNewList(IL_PARTICLE, GL_COMPILE);
    
    glPushMatrix ();

    glBindTexture(GL_TEXTURE_2D, texParticle);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.8f, -0.9f, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(+0.8f, -0.9f, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(+0.8f, +0.9f, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.8f, +0.9f, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEndList();

// Imagelist for background
    glNewList(IL_BACKGROUND, GL_COMPILE);

    glColor4f(1.0, 1.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, texBackground);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-10, -5, -10);

    glRotatef(45.0, 0.0, 1.0, 0.0);
    glScalef(10.0, 10.0, 10.0);

    glBegin(GL_QUADS);
    glTexCoord2f   (0.0, 0.0); 
    glVertex3f     (-4.0, -4.9f, -1.0);
    glTexCoord2f   (1.0, 0.0); 
    glVertex3f     (4.0, -4.9f, -1.0);
    glTexCoord2f   (1.0, 1.0); 
    glVertex3f     (3.0, 1.9f, -1.0);
    glTexCoord2f   (0.0, 1.0); 
    glVertex3f     (-3.0, 1.9f, -1.0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glEndList();
}

void Scene::update()
{
    angle_y =(angle_y+0.05 >= 360)? 0 :(angle_y+0.05);

    for (ParticlesIt it = particles.begin(); it != particles.end(); ++it)
        it->update();
}

void Scene::draw()
{
    glCallList(IL_BACKGROUND);

    glPushMatrix();

    glRotatef(angle_x, 1.0, 0.0, 0.0);
    glRotatef(angle_y, 0.0, 1.0, 0.0);
    glRotatef(angle_z, 0.0, 0.0, 1.0);

    glTranslatef(-17, -5, -17);

    GLint width;
    glGetIntegerv(GL_LINE_WIDTH, &width);

    glLineWidth(2);

    glEnable(GL_BLEND);
    for (ParticlesIt it = particles.begin(); it != particles.end(); ++it) {
        it->setAngles(-angle_x, -angle_y, -angle_z);
        it->draw();
    }
    glDisable(GL_BLEND);

    glLineWidth(width);

    glPopMatrix();
}

