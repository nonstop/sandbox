#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "scene.h"
#include "menu.h"
#include "game.h"
#include "utils.h"

// animationMode flags
#define ANIMATE_OUR_TOWER 0x1
#define ANIMATE_ENEMY_TOWER 0x2
#define ANIMATE_OUR_WALL 0x4
#define ANIMATE_ENEMY_WALL 0x8

static const GLfloat towerColor[] = {1.0, 0.0, 1.0};

typedef struct Tower
{
    GLfloat color[3];
    int step, steps;
    int height; // in points
    int newHeight;
    int maxHeight; // in points
} Tower;

typedef struct Wall
{
    int height; // in points
    int newHeight;
    int maxHeight; // in points
} Wall;

struct Scene
{
    int animationMode;
    int width, height;
    GLfloat xStep, yStep;
    GLfloat towerWidth, wallWidth;
    GLfloat minTowerHeight, maxTowerHeight;
    GLfloat minWallHeight, maxWallHeight;
    Tower ourTower, enemyTower;
    Wall ourWall, enemyWall;
} scene;

void scene_resize(int width, int height)
{
    scene.width = width;
    scene.height = (height == 0 ? 1 : height);
    scene.xStep = scene.width / 10;
    scene.yStep = scene.height / 10;
    scene.towerWidth = 1.5 * scene.xStep;
    scene.wallWidth = 0.5 * scene.xStep;
    scene.minTowerHeight = scene.yStep + 0.2 * scene.yStep;
    scene.maxTowerHeight = 6.0 * scene.yStep;
    scene.minWallHeight = 0.1;
    scene.maxWallHeight = 5.0 * scene.yStep;

    TRACE("minTowerHeight=%f maxTowerHeight=%f", scene.minTowerHeight, scene.maxTowerHeight);

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, scene.width, 0, scene.height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


static void tower_draw(const Tower* t)
{
    const float k = (scene.maxTowerHeight - scene.minTowerHeight) / (float)t->maxHeight;
    const float y = k * t->height + scene.minTowerHeight;
    const float roofHeight = 2.0 * scene.yStep;
    
    glColor3fv(t->color);

    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, y - roofHeight, 0);
    glVertex3f(0 - scene.xStep * 0.25, y - roofHeight, 0);
    glVertex3f(0 + scene.xStep * 0.25, y - roofHeight * 0.66, 0);
    glVertex3f(scene.towerWidth / 2.0, y, 0);
    glVertex3f(scene.towerWidth - scene.xStep * 0.25, y - roofHeight * 0.66, 0);
    glVertex3f(scene.towerWidth + scene.xStep * 0.25, y - roofHeight, 0);
    glVertex3f(scene.towerWidth, y - roofHeight, 0);
    glVertex3f(scene.towerWidth, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

static void wall_draw(const Wall* w)
{
    static GLfloat wallColor[] = {0.0, 0.0, 0.5};

    const float k = (scene.maxWallHeight - scene.minWallHeight) / (float)w->maxHeight;
    const float y = k * w->height + scene.minWallHeight;
    glColor3fv(wallColor);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, y, 0);
    glVertex3f(scene.wallWidth, y, 0);
    glVertex3f(scene.wallWidth, 0, 0);
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

void scene_init(int width, int height)
{
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

    memset(&scene, sizeof(struct Scene), 0);
    scene_resize(width, height);
    const Stat* our = game_stat_our();
    scene.ourTower.height = our->tower;
    scene.ourTower.maxHeight = our->maxTower;
    memcpy(scene.ourTower.color, towerColor, sizeof(towerColor));
    scene.ourWall.height = our->wall;
    scene.ourWall.maxHeight = our->maxWall;

    const Stat* enemy = game_stat_enemy();
    scene.enemyTower.height = enemy->tower;
    scene.enemyTower.maxHeight = enemy->maxTower;
    memcpy(scene.enemyTower.color, towerColor, sizeof(towerColor));
    scene.enemyWall.height = enemy->wall;
    scene.enemyWall.maxHeight = enemy->maxWall;
    TRACE("our %d %d enemy %d %d", scene.ourTower.height, scene.ourWall.height,
            scene.enemyTower.height, scene.enemyWall.height);
    menu_init();
}

static void tower_reset(Tower* t)
{
    t->height = t->newHeight;
    t->step = 0;
    t->steps = 0;
    memcpy(&t->color, towerColor, sizeof(towerColor));
}

static void change_color_by_step(GLfloat* color, const GLfloat* defaultColor, int step, int steps)
{
    static const GLfloat intermediateColor[] = {1.0, 1.0, 1.0};
    const int sign = (step > (float)steps / 2.0 ? 1 : -1);
    const float k = 2.0 * (float)step / (float)steps;
    int i = 0;
    for (; i < 3; ++i) {
        color[i] += sign * (defaultColor[i] - intermediateColor[i]) * k;
    }
}

static void tower_on_timer(Tower* t, int flag)
{
    TRACE("height=%d newHeight=%d step=%d steps=%d",
            t->height, t->newHeight, t->step, t->steps);
    if (t->height < t->newHeight) {
        ++t->step;
        t->height += 2;
        change_color_by_step(t->color, towerColor, t->step, t->steps);
        if (t->height >= t->newHeight) {
            tower_reset(t);
            scene.animationMode &= ~flag;
        }
    } else if (t->height > t->newHeight) {
        ++t->step;
        t->height -= 2;
        change_color_by_step(t->color, towerColor, t->step, t->steps);
        if (t->height <= t->newHeight) {
            tower_reset(t);
            scene.animationMode &= ~flag;
        }
    } else {
        tower_reset(t);
        scene.animationMode &= ~flag;
    }
}

static void wall_on_timer(Wall* wall, int flag)
{
    if (wall->height < wall->newHeight) {
        ++wall->height;
    } else if (wall->height > wall->newHeight) {
        --wall->height;
    } else {
        scene.animationMode &= ~flag;
    }
}

void scene_on_timer()
{
    if (scene.animationMode == 0) {
        return;
    }
    if (scene.animationMode & ANIMATE_OUR_TOWER) {
        tower_on_timer(&scene.ourTower, ANIMATE_OUR_TOWER);
    }
    if (scene.animationMode & ANIMATE_ENEMY_TOWER) {
        tower_on_timer(&scene.enemyTower, ANIMATE_ENEMY_TOWER);
    }
    if (scene.animationMode & ANIMATE_OUR_WALL) {
        wall_on_timer(&scene.ourWall, ANIMATE_OUR_WALL);
    }
    if (scene.animationMode & ANIMATE_ENEMY_WALL) {
        wall_on_timer(&scene.enemyWall, ANIMATE_ENEMY_WALL);
    }
}

void scene_draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    mesh_draw(scene.width, scene.height);
    glPushMatrix();
    const float delta = (float)(2.0 * scene.xStep);
    glTranslatef(delta - scene.towerWidth, 3.0 * scene.yStep, 0);
    tower_draw(&scene.ourTower);
    glTranslatef(scene.towerWidth + scene.xStep / 2., 0, 0);
    wall_draw(&scene.ourWall);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(scene.width - delta, 3.0 * scene.yStep, 0.0);
    tower_draw(&scene.enemyTower);
    glTranslatef(-scene.xStep, 0, 0);
    wall_draw(&scene.enemyWall);
    glPopMatrix();

    int i = 1;
    for (; i < 6; ++i) {
        glColor3f(1.0, 1.0, 0);
        glPushMatrix();
        glTranslatef(1.5 * i * scene.xStep - scene.xStep * 0.125, scene.yStep * 0.25, 0);
        glBegin(GL_LINE_STRIP);
        glVertex3f(0, 0, 0);
        glVertex3f(0, scene.yStep * 2.5, 0);
        glVertex3f(scene.xStep * 1.25, scene.yStep * 2.5, 0);
        glVertex3f(scene.xStep * 1.25, 0, 0);
        glVertex3f(0, 0, 0);
        glEnd();
        glPopMatrix();
    }

    /*menu_draw(scene);*/
}

int scene_in_animation_mode()
{
    return scene.animationMode != 0;
}

static void scene_animate_tower__(Tower* t, int newHeight, int flag)
{
    scene.animationMode |= flag;
    t->step = 0;
    const int delta = abs(t->height - newHeight);
    t->steps = delta / 2 + delta % 2;
    TRACE("height=%d newHeight=%d abs=%d steps=%d", t->height, newHeight, delta, t->steps);
    t->newHeight = newHeight;
    TRACE("%s newHeight=%d animationMode=%x steps=%d", __FUNCTION__,
            newHeight, scene.animationMode, scene.enemyTower.steps);
}

void scene_animate_tower(int target, int newHeight)
{
    if (target) {
        scene_animate_tower__(&scene.enemyTower, newHeight, ANIMATE_ENEMY_TOWER);
    } else {
        scene_animate_tower__(&scene.ourTower, newHeight, ANIMATE_OUR_TOWER);
    }
}

void scene_animate_wall(int target, int newHeight)
{
    if (target) {
        scene.animationMode |= ANIMATE_ENEMY_WALL;
        scene.enemyWall.newHeight = newHeight;
//        TRACE("%s newHeight=%d animationMode=%x", __FUNCTION__, newHeight, scene.animationMode);
    } else {
        scene.animationMode |= ANIMATE_OUR_WALL;
        scene.ourWall.newHeight = newHeight;
//        TRACE("%s newHeight=%d animationMode=%x", __FUNCTION__, newHeight, scene.animationMode);
    }
}
