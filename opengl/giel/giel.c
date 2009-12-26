#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

#include "utils.h"
#include "basic_unit.h"

struct Globals
{
    BasicUnit* head;
    BasicUnit* currentUnit;
} globals;

void drawScene()
{
    drawBasicUnits(globals.head);
}

void initScene()
{
    // TODO
    basic_unit_init_imagelist();
    globals.head = calloc(1, sizeof(BasicUnit));
    globals.currentUnit = globals.head;
    globals.currentUnit->isCurrent = 1;
    appendBasicUnits(globals.currentUnit, 7);
    TRACE("unit=%p", globals.head);
}

void updateScene()
{
}

// Оси координат
void axes()
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    axes();
    drawScene();

    glPopMatrix();

    glLoadIdentity();
    gluLookAt(20.0, 20.0, 20.0, 
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* jwz: 0.05 was too close (left black rectangles) */
    gluPerspective(25.0, (GLdouble) w / (GLdouble) h, 1.0, 100.0);
    gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    /*gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);*/
    glLoadIdentity();
return;
    glViewport(0, 0, w, h);                // Set the viewport for the OpenGL window
    glMatrixMode(GL_PROJECTION);            // Change Matrix Mode to Projection
    glLoadIdentity();                        // Reset View

// Do the perspective calculations. Last value = max clipping depth
    gluPerspective(60.0, w/h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);            // Return to the modelview matrix
    glLoadIdentity();                        // Reset View

    glutPostRedisplay();
}


static const GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
static const GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
static const GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
static const GLfloat mat_shininess[] = { 20.0 };
void init()
{
    srand(time(NULL));
    /*glClearColor(0.1f, 0.1f, 0.4f, 0.0);                    // Dark Blue Background*/
    /*glShadeModel(GL_SMOOTH);                                // Enables Smooth Color Shading*/
    /*glClearDepth(1.0);                                    // Depth Buffer Setup*/
    /*glDepthFunc(GL_LESS);                                    // The Type Of Depth Test To Do*/
    /*glBlendFunc(GL_SRC_ALPHA, GL_ONE);*/

    /*glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Realy Nice perspective calculations*/
    /*glEnable(GL_TEXTURE_2D);                                // Enable Texture Mapping*/

    initScene();
    
    float light_pos[][3] = {{0.0, 10.0, 20.0}, {0.0, 20.0, -1.0}};
    float light_dir[][3] = {{0.0, -10.0,-20.0}, {0.0,-20.0, 1.0}};

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);
    /*glEnable(GL_CULL_FACE);*/
    glEnable(GL_NORMALIZE);
    /*if (transparent) {*/
    /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    /*glEnable(GL_BLEND);*/
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

void special(int key, int x, int y)
{
    TRACE("key=%c(%d) x=%d y=%d", key, key, x, y);
    switch (key)
    {
    case 100: // left
        base_unit_turn_left(globals.currentUnit);
        break;
    case 101: // up
        if (globals.currentUnit->next) {
            globals.currentUnit->isCurrent = 0;
            globals.currentUnit = globals.currentUnit->next;
            globals.currentUnit->isCurrent = 1;
        }
        break;
    case 102: // right
        base_unit_turn_right(globals.currentUnit);
        break;
    case 103: // down
        if (globals.currentUnit->prev) {
            globals.currentUnit->isCurrent = 0;
            globals.currentUnit = globals.currentUnit->prev;
            globals.currentUnit->isCurrent = 1;
        }
        break;
    default:
        // pass
        break;
    };
}

void keypress(unsigned char key, int x, int y)
{
    TRACE("key=%c(%d) x=%d y=%d", key, key, x, y);
    switch(key)
    {
    case 27://VK_ESCAPE:
        giel_exit();
        break;
    default:
        giel_exit();
        break;
    }

    glutPostRedisplay();
}

void timer(int value)
{
    updateScene();
    glutPostRedisplay();

    glutTimerFunc(10, timer, 1); 
}

int main(int ac, char* av[])
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(300, 300);
    glutCreateWindow("giel");
    //    glutFullScreen();

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keypress);
    glutSpecialFunc(special);
    glutTimerFunc(10, timer, 1); 
    glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();
    giel_exit();
    return 0;
}

