#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>

#include "scene.h"

typedef struct Screen
{
    int width, height;
} Screen;

static void handleQuit(int returnCode)
{
    SDL_Quit();
    exit(returnCode);
}

static int handleKeyPress(SDL_Surface* surface, SDL_keysym* keysym)
{
    switch (keysym->sym) {
    case SDLK_ESCAPE:
        return 1;
    case SDLK_F1: // fullscreen mode
        SDL_WM_ToggleFullScreen(surface);
        break;
    case SDLK_1:
    case SDLK_2:
    case SDLK_3:
    case SDLK_4:
    case SDLK_5: {
        break;
    }
    default:
        break;
    }
    return 0;
}

Uint32 handleTimer(Uint32 interval, void* param)
{
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = 0;
    event.user.data1 = NULL;
    event.user.data2 = NULL;

    SDL_PushEvent(&event);
    return(interval);
}

static void drawScene()
{
    scene_draw();
    SDL_GL_SwapBuffers();
}

int main(int ac, char* av[])
{
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        handleQuit(1);
    }

    srand(time(0));
    const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
    if (!videoInfo) {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        handleQuit(1);
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
        handleQuit(1);
    }

    int isActive = 1;
    int done = 0;
    SDL_TimerID timer = SDL_AddTimer(100, handleTimer, NULL);
    if (!timer) {
        fprintf(stderr,  "timer failed: %s\n", SDL_GetError());
        handleQuit(1);
    }
    scene_init(screen.width, screen.height);

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
                    handleQuit(1);
                }
                scene_resize(screen.width, screen.height);
                break;
            case SDL_USEREVENT: {
                scene_on_timer();
                break;
            }
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
            drawScene();
        } else {
            SDL_Delay(0);
        }
    }

    SDL_Quit();
    return 0;
}
