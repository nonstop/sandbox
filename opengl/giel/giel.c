#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "utils.h"
#include "giel_lua.h"
#include "basic_unit.h"

Globals globals = {};
// Оси координат
static void axes()
{
    glPushMatrix();

    GLint width;
    glGetIntegerv(GL_LINE_WIDTH, &width);

    glLineWidth(2);

    glBegin(GL_LINES);
    glColor3f(1.0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 0, 0);

    glColor3f(0, 1.0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);

    glColor3f(0, 0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glEnd();

    glLineWidth(width);
    glPopMatrix();
}

static void displayInfo()
{
    static const int infoAreaWidth = 50;
    static const int infoAreaHeight = 50;
    glViewport(globals.width - infoAreaWidth, 0, infoAreaWidth, infoAreaHeight);
    glPushMatrix();
    axes();
    glPopMatrix();
}

static void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glViewport(0, 0, globals.width, globals.height);

    gluLookAt(20.0, 20.0, 20.0, 
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);

    glPushMatrix();
    /*axes();*/
    glRotatef(globals.rotateX, 0, 1, 1);
    glRotatef(globals.rotateY, 1, 0, 1);
    glRotatef(globals.rotateZ, 1, 1, 0);
    drawBasicUnits(globals.head);
    glPopMatrix();
    
    displayInfo();
    /*glutSwapBuffers();*/
}

static void initScene()
{
    globals.head = calloc(1, sizeof(BasicUnit));
    globals.currentUnit = globals.head;
    globals.currentUnit->isCurrent = 1;
    appendBasicUnits(globals.currentUnit, 24);
}

static void updateScene(Uint32 millisecs)
{
}

static void reshape(int w, int h)
{
    globals.width = w;
    globals.height = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, w/h, 1.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
}


static const GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
static const GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
static const GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
static const GLfloat mat_shininess[] = { 20.0 };
static void init(const char* initFile)
{
    srand(time(NULL));

    basic_unit_init_imagelist();
    if (initFile) {
        initSceneFromFile(&globals, initFile);
    }
    if (!globals.head) {
        initScene();
    }
    TRACE("unit=%p", globals.head);
    
    float light_pos[][3] = {{0.0, 10.0, 20.0}, {0.0, 20.0, -1.0}};
    float light_dir[][3] = {{0.0, -10.0,-20.0}, {0.0,-20.0, 1.0}};

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);
    /*glEnable(GL_CULL_FACE);*/
    glEnable(GL_NORMALIZE);
    /*if (transparent) {*/
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    /*}*/

    /*if (!wireframe) {*/
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos[0]);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir[0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
#if 1
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos[1]);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir[1]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
#endif
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    /*}*/
}

static void giel_exit()
{
    freeBasicUnits(globals.head);
    exit(0);
}

static void giel_save()
{
    char buff[] = "-/|\\";
    fprintf(stderr, "setForm('form', '");
    BasicUnit* u = globals.head;
    while (u) {
        fprintf(stderr, "%c", buff[u->rot]);
        u = u->next;
    }
    fprintf(stderr, "')\n");
}

void giel_terminate()
{
	static SDL_Event Q;
	Q.type = SDL_QUIT;
	if (SDL_PushEvent(&Q) == -1) {
		TRACE("SDL_QUIT event can't be pushed: %s", SDL_GetError() );
		giel_exit();
	}
}

static void keypress(SDLMod mode, Uint8* keys)
{
	if (!keys) {
        return;
    }
    if (keys[SDLK_ESCAPE]) {
        giel_terminate();
    }
    if (keys[SDLK_LEFT]) {
        basic_unit_turn_left(globals.currentUnit);
        keys[SDLK_LEFT] = 0;
    }
    if (keys[SDLK_RIGHT]) {
        basic_unit_turn_right(globals.currentUnit);
        keys[SDLK_RIGHT] = 0;
    }
    if (keys[SDLK_UP]) {
        if (globals.currentUnit->next) {
            globals.currentUnit->isCurrent = 0;
            globals.currentUnit = globals.currentUnit->next;
            globals.currentUnit->isCurrent = 1;
            keys[SDLK_UP] = 0;
        }
    }
    if (keys[SDLK_DOWN]) {
        if (globals.currentUnit->prev) {
            globals.currentUnit->isCurrent = 0;
            globals.currentUnit = globals.currentUnit->prev;
            globals.currentUnit->isCurrent = 1;
            keys[SDLK_DOWN] = 0;
        }
    }
    if (keys[SDLK_RETURN]) {
        giel_save();
    }
#define checkRotate(sdl_key, field) \
    if (keys[sdl_key]) { \
        if (mode & KMOD_SHIFT) { \
            globals.field -= 1; \
        } else { \
            globals.field += 1; \
        } \
        if (globals.field > 360) { \
            globals.field = 0; \
        } \
        if (globals.field < 0) { \
            globals.field = 360; \
        } \
        TRACE("key "#sdl_key " %x ", SDL_GetModState() & KMOD_SHIFT); \
    }
    checkRotate(SDLK_x, rotateX);
    checkRotate(SDLK_y, rotateY);
    checkRotate(SDLK_z, rotateZ);
}

int main(int ac, char* av[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        TRACE("Unable to init SDL: %s", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    /*const int defaultWidth = 300, defaultHeight = 300;*/
    const int defaultWidth = 600, defaultHeight = 600;
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface* screen = SDL_SetVideoMode(defaultWidth, defaultHeight, 16, SDL_HWSURFACE|SDL_OPENGL);
    if (!screen) {
        TRACE("Unable to set video mode: %s", SDL_GetError());
        return 1;
    }
    SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 0, 0, 0, 0));
    reshape(defaultWidth, defaultHeight);

	SDL_WM_SetCaption("giel", NULL);

    init(ac == 2 ? av[1] : NULL);
    SDL_ShowCursor(0);
    int appVisible = 1, appMouseFocus = 0, appKeyboardFocus = 0;
	int isProgramLooping = 1;
    Uint32 tickCount = 0, lastCount = SDL_GetTicks();
	while (isProgramLooping) {
        Uint8 *keys = NULL;
        SDL_Event ev = {};
		if (SDL_PollEvent(&ev)) {
			switch (ev.type)
			{
			case SDL_QUIT:
				{
					isProgramLooping = 0;
					break;
				}

			case SDL_VIDEORESIZE:
				{
					reshape(ev.resize.w, ev.resize.h);
					break;
				}

			case SDL_ACTIVEEVENT:
				{
					if (ev.active.state & SDL_APPACTIVE) {
                        appVisible = ev.active.gain ? 1 : 0;
					}
					
					if (ev.active.state & SDL_APPMOUSEFOCUS) {
                        appMouseFocus = ev.active.gain ? 1 : 0;
					}

					if (ev.active.state & SDL_APPINPUTFOCUS) {
                        appKeyboardFocus = ev.active.gain ? 1 : 0;
					}
					break;
				}
			}
		}
        if (!appVisible) {
            SDL_WaitEvent(NULL);
        } else {
            keys = SDL_GetKeyState(NULL);
            tickCount = SDL_GetTicks();
            keypress(SDL_GetModState(), keys);
            updateScene(tickCount - lastCount);
            lastCount = tickCount;
            drawScene(/*screen*/);
            SDL_GL_SwapBuffers();
        }
	}

    giel_exit();
    return 0;
}

