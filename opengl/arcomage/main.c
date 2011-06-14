#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

/* Define our booleans */
#define TRUE  1
#define FALSE 0

static void arcomage_quit(int returnCode)
{
    SDL_Quit();
    exit(returnCode);
}

static int resizeWindow(int width, int height)
{
    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if (height == 0) {
        height = 1;
    }

    ratio = (GLfloat)width / (GLfloat)height;

    /* Setup our viewport. */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Set our perspective */
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode(GL_MODELVIEW);

    /* Reset The View */
    glLoadIdentity();
    return 1;
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
}

/* Here goes our drawing code */
static void drawGLScene()
{
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;

    /* Clear The Screen And The Depth Buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);

    glBegin(GL_TRIANGLES);               /* Drawing Using Triangles       */
    glColor3f(1.0f,  0.0f,  0.0f);     /* Red                           */
    glVertex3f(0.0f,  1.0f,  0.0f);    /* Top Of Triangle               */
    glColor3f(0.0f,  1.0f,  0.0f);     /* Green                         */
    glVertex3f(-1.0f, -1.0f,  0.0f);   /* Left Of Triangle              */
    glColor3f(0.0f,  0.0f,  1.0f);     /* Blue                          */
    glVertex3f(1.0f, -1.0f,  0.0f);    /* Right Of Triangle             */
    glEnd();                             /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glTranslatef(3.0f, 0.0f, 0.0f);

    /* Set The Color To Blue One Time Only */
    glColor3f(0.5f, 0.5f, 1.0f);

    glBegin(GL_QUADS);                   /* Draw A Quad              */
    glVertex3f(1.0f,  1.0f,  0.0f);    /* Top Right Of The Quad    */
    glVertex3f(-1.0f,  1.0f,  0.0f);   /* Top Left Of The Quad     */
    glVertex3f(-1.0f, -1.0f,  0.0f);   /* Bottom Left Of The Quad  */
    glVertex3f(1.0f, -1.0f,  0.0f);    /* Bottom Right Of The Quad */
    glEnd();                             /* Done Drawing The Quad    */

    /* Draw it to the screen */
    SDL_GL_SwapBuffers();

    /* Gather our frames per second */
    Frames++;
    {
        GLint t = SDL_GetTicks();
        if (t - T0 >= 5000) {
            GLfloat seconds = (t - T0) / 1000.0;
            GLfloat fps = Frames / seconds;
            printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
            T0 = t;
            Frames = 0;
        }
    }
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

    SDL_Surface* surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, videoFlags);
    if (!surface) {
        fprintf(stderr,  "Video mode set failed: %s\n", SDL_GetError());
        arcomage_quit(1);
    }

    initGL();
    resizeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

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
                resizeWindow(event.resize.w, event.resize.h);
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
            drawGLScene();
        }
    }

    SDL_Quit();
    return 0;
}
