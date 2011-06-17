#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "utils.h"
#include "menu.h"

typedef struct Screen
{
    int width, height;
} Screen;

static void arcomage_quit(int returnCode)
{
    SDL_Quit();
    exit(returnCode);
}

static void resizeWindow(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static int handleKeyPress(SDL_Surface* surface, SDL_keysym* keysym)
{
    switch (keysym->sym) {
    case SDLK_ESCAPE:
        return 1;
    case SDLK_F1: // fullscreen mode
        SDL_WM_ToggleFullScreen(surface);
        break;
    default:
        break;
    }
    return 0;
}

static void initGL(GLvoid)
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

    menu_init();
}

static void drawMesh(int width, int height)
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

static void drawTower(int width, int height, int size)
{
    glPushMatrix();
    const int xStep = width / 10;
    const int yStep = height / 10;
    glColor3f(0.0f, 0.0f, 1.0f);
    const GLfloat w = 1.5 * xStep, h = 4 * yStep;
    if (size > 0) {
        glTranslatef((float)xStep / 2., yStep, 0.0);
    } else {
        glTranslatef(width - w - (float)xStep / 2., yStep, 0.0);
    }
    glBegin(GL_QUADS);
    glVertex3f(0, h, 0);
    glVertex3f(w, h, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0, h, 0);
    glVertex3f(w / 2., h + yStep, 0);
    glVertex3f(w, h, 0);
    glEnd();
    glPopMatrix();
}

static void drawWall(int width, int height, int size)
{
    glPushMatrix();
    const int xStep = width / 10;
    const int yStep = height / 10;
    glColor3f(0.0f, 0.0f, 0.5f);
    const GLfloat w = 0.5 * xStep, h = 3 * yStep;
    float delta = (float)(3 * xStep);
    if (size > 0) {
        glTranslatef(delta - w, yStep, 0.0);
    } else {
        glTranslatef(width - delta, yStep, 0.0);
    }
    glBegin(GL_QUADS);
    glVertex3f(0, h, 0);
    glVertex3f(w, h, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
}

static void drawGLScene(const Screen* screen)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    /*glTranslatef(0, 0, -36.3f);*/

    drawMesh(screen->width, screen->height);
    drawTower(screen->width, screen->height, 1);
    drawTower(screen->width, screen->height, -1);
    drawWall(screen->width, screen->height, 1);
    drawWall(screen->width, screen->height, -1);
    /*drawTower(screen->width, screen->height, -1);*/

    menu_draw();

    SDL_GL_SwapBuffers();
}

int main(int ac, char* av[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        arcomage_quit(1);
    }

    const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
    if (!videoInfo) {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        arcomage_quit(1);
    }

    int videoFlags = SDL_OPENGL
        | SDL_GL_DOUBLEBUFFER
        | SDL_HWPALETTE
        | SDL_RESIZABLE;

    if (videoInfo->hw_available) {
        videoFlags |= SDL_HWSURFACE;
    } else {
        videoFlags |= SDL_SWSURFACE;
    }

    if (videoInfo->blit_hw)
        videoFlags |= SDL_HWACCEL;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    struct Screen screen = {640, 480};
    SDL_Surface* surface = SDL_SetVideoMode(640, 480, 16, videoFlags);
    if (!surface) {
        fprintf(stderr,  "Video mode set failed: %s\n", SDL_GetError());
        arcomage_quit(1);
    }

    initGL();
    resizeWindow(screen.width, screen.height);

    int isActive = 1;
    int done = 0;
    SDL_Event event = {};
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_ACTIVEEVENT:
                if (event.active.gain == 0) {
                    isActive = 0;
                } else {
                    isActive = 1;
                }
                break;
            case SDL_VIDEORESIZE:
                surface = SDL_SetVideoMode(event.resize.w, event.resize.h, 16, videoFlags);
                if (!surface) {
                    fprintf(stderr, "Could not get a surface after resize: %s\n", SDL_GetError());
                    arcomage_quit(1);
                }
                resizeWindow(screen.width, screen.height);
                break;
            case SDL_KEYDOWN:
                done = handleKeyPress(surface, &event.key.keysym);
                break;
            case SDL_QUIT:
                done = 1;
                break;
            default:
                break;
            }
        }

        if (isActive) {
            drawGLScene(&screen);
        }
    }

    SDL_Quit();
    return 0;
}
