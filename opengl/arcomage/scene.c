#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "utils.h"
#include "scene.h"

typedef struct Tower
{
    int height; // in points
    int maxHeight; // in points
} Tower;

typedef struct Wall
{
    int height; // in points
    int maxHeight; // in points
} Wall;

typedef struct Scene
{
    int mode;
    int width, height;
    GLfloat xStep, yStep;
    GLfloat towerWidth, wallWidth;
    GLfloat minTowerHeight, maxTowerHeight;
    GLfloat minWallHeight, maxWallHeight;
    Tower ourTower, enemyTower;
    Wall ourWall, enemyWall;
} Scene;

void scene_resize(Scene* scene, int width, int height)
{
    scene->width = width;
    scene->height = (height == 0 ? 1 : height);
    scene->xStep = scene->width / 10;
    scene->yStep = scene->height / 10;
    scene->towerWidth = 1.5 * scene->xStep;
    scene->wallWidth = 0.5 * scene->xStep;
    scene->minTowerHeight = scene->yStep + 0.2 * scene->yStep;
    scene->maxTowerHeight = 5.0 * scene->yStep;
    scene->minWallHeight = 0.1;
    scene->maxWallHeight = 5.0 * scene->yStep;

    TRACE("minTowerHeight=%f maxTowerHeight=%f", scene->minTowerHeight, scene->maxTowerHeight);

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, scene->width, 0, scene->height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


static void tower_draw(const Scene* scene, const Tower* t)
{
    const float k = (scene->maxTowerHeight - scene->minTowerHeight) / (float)t->maxHeight;
    const float y = k * t->height + scene->minTowerHeight;
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, y - scene->yStep, 0);
    glVertex3f(scene->towerWidth / 2.0, y, 0);
    glVertex3f(scene->towerWidth, y - scene->yStep, 0);
    glVertex3f(scene->towerWidth, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

static void wall_draw(const Scene* scene, const Wall* wall)
{
    glColor3f(0.0f, 0.0f, 0.5f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, scene->maxWallHeight, 0);
    glVertex3f(scene->wallWidth, scene->maxWallHeight, 0);
    glVertex3f(scene->wallWidth, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

static void mesh_draw(int width, int height)
{
    glColor3f(0.0f, 1.0f, 0.0f);
    int i = 0;
    const int xStep = width / 10;
    for (; i <= 10; ++i) {
        glBegin(GL_LINE_STRIP);
        glVertex3f(i * xStep, 0, 0.0f);
        glVertex3f(i * xStep, height, 0.0f);
        glEnd();
    }
    const int yStep = height / 10;
    for (i = 0; i <= 10; ++i) {
        glBegin(GL_LINE_STRIP);
        glVertex3f(0, i * yStep, 0.0f);
        glVertex3f(width, i * yStep, 0.0f);
        glEnd();
    }
}

Scene* scene_new(int width, int height)
{
    static Scene scene = {};
    /* Enable smooth shading */
    glShadeModel(GL_SMOOTH);
    /* Set the background black */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    /* Depth buffer setup */
    glClearDepth(1.0f);
    /* Enables Depth Testing */
    glEnable(GL_DEPTH_TEST);
    /* The Type Of Depth Test To Do */
    glDepthFunc(GL_LEQUAL);
    /* Really Nice Perspective Calculations */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    scene_resize(&scene, width, height);
    scene.ourTower.height = 100 + (rand() % 2 ? 1 : -1) * rand() % 25;
    scene.ourTower.maxHeight = 125;
    scene.enemyTower.height = 100 + (rand() % 2 ? 1 : -1) * rand() % 25;
    scene.enemyTower.maxHeight = 125;
    TRACE("ourTower %d enemyTower %d", scene.ourTower.height, scene.enemyTower.height);
    menu_init();
    return &scene;
}

void scene_on_timer(Scene* scene)
{
    if (!scene_in_animation_mode(scene)) {
        return;
    }
    if (scene->ourTower.height < scene->ourTower.maxHeight) {
        ++scene->ourTower.height;
    } else {
        scene->mode = 0;
        TRACE("stop animation");
    }
}

void scene_draw(const Scene* scene)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    mesh_draw(scene->width, scene->height);
    glPushMatrix();
    const float delta = (float)(2.0 * scene->xStep);
    glTranslatef(delta - scene->towerWidth, 3.0 * scene->yStep, 0);
    tower_draw(scene, &scene->ourTower);
    glTranslatef(scene->towerWidth + scene->xStep / 2., 0, 0);
    wall_draw(scene, &scene->ourWall);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(scene->width - delta, 3.0 * scene->yStep, 0.0);
    tower_draw(scene, &scene->enemyTower);
    glTranslatef(-scene->towerWidth + scene->xStep / 2., 0, 0);
    wall_draw(scene, &scene->ourWall);
    glPopMatrix();

    /*menu_draw(scene);*/
}

int scene_in_animation_mode(const Scene* scene)
{
    return scene->mode;
}

void scene_start_animation(Scene* scene)
{
    TRACE("start animation");
    scene->mode = 1;
}
