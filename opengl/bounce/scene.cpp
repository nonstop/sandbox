#include "stdafx.h"

#include "scene.h"

#include "textures.h"

Scene::Scene ()
{
    nParticles = 150;
    angle_x = 0;
    angle_y = 0;
    angle_z = 0;
}

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

    glEnable(GL_BLEND);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.8f, -0.9f, 0);
    glTexCoord2f(1.0, 0.0); glVertex3f(+0.8f, -0.9f, 0);
    glTexCoord2f(1.0, 1.0); glVertex3f(+0.8f, +0.9f, 0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.8f, +0.9f, 0);
    glEnd();

    glDisable(GL_BLEND);
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
    for (ParticlesIt it = particles.begin(); it != particles.end(); ++it)
        it->update();
}

void Scene::setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z)
{
    angle_x = ang_x;
    angle_y = ang_y;
    angle_z = ang_z;
}

void Scene::getAngles(GLfloat *ang_x, GLfloat *ang_y, GLfloat *ang_z)
{
    *ang_x = angle_x;
    *ang_y = angle_y;
    *ang_z = angle_z;
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

    for (ParticlesIt it = particles.begin(); it != particles.end(); ++it) {
        it->setAngles(-angle_x, -angle_y, -angle_z);
        it->drawTail();
        it->drawParticle();
    }

    glLineWidth(width);

    glPopMatrix();
}

