#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#include <GL/glut.h>

#define TRACE(fmt, ...) fprintf(stderr, "%s:%d " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

struct Point
{
    GLfloat x, y;
};

struct PointsElement
{
    struct PointsElement* next;
    struct Point pt;
};

struct Globals
{
    struct PointsElement* firstElem;
} glob;

static struct PointsElement* appendPoint(struct PointsElement* currElem, GLfloat x, GLfloat y)
{
    struct PointsElement* elem = (struct PointsElement*)calloc(sizeof(struct PointsElement), 1);
    elem->pt.x = x;
    elem->pt.y = y;
    if (currElem) {
        elem->next = currElem->next;
        currElem->next = elem;
    }
    return elem;
}

static void traceElems(const char* file, int line)
{
    TRACE("%s:%d %s", file, line, __FUNCTION__);
    struct PointsElement* elem = glob.firstElem;
    do {
        TRACE("elem=%p next=%p x=%f y=%f", elem, elem->next, elem->pt.x, elem->pt.y);
        elem = elem->next;
    } while (elem != glob.firstElem);
}

static void iter()
{
    struct PointsElement* elem = glob.firstElem;
    do {
        struct PointsElement* nextElem = elem->next;
        GLfloat new_x = (elem->pt.x + elem->next->pt.x) / 2.0;
        GLfloat new_y = (elem->pt.y + elem->next->pt.y) / 2.0;
        appendPoint(elem, new_x, new_y);
        elem = nextElem;
    } while (elem != glob.firstElem);
}

static void initScene()
{
    struct PointsElement* elem = appendPoint(NULL, 0, 0.5);
    glob.firstElem = elem;
    glob.firstElem->next = glob.firstElem;
    elem = appendPoint(elem, -0.5, -0.5);
    elem = appendPoint(elem, 0.5, -0.5);
    TRACE("glob.firstElem=%p", glob.firstElem);
    traceElems(__FILE__, __LINE__);
    iter();
    traceElems(__FILE__, __LINE__);
}

static void drawScene()
{
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0, 0);

    struct PointsElement* elem = glob.firstElem;
    do {
        glVertex3f(elem->pt.x, elem->pt.y, 0);
        elem = elem->next;
    } while (elem != glob.firstElem);
    
    glEnd();
}

static void updateScene()
{
}


static void axes()
{
    glPushMatrix();

    GLint width;
    glGetIntegerv(GL_LINE_WIDTH, &width);

    glLineWidth(1);

    glBegin(GL_LINES);
    glColor3f(0, 1.0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1.0, 0, 0);

    glColor3f(0, 1.0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1.0, 0);
    glEnd();

    glLineWidth(width);
    glPopMatrix();
}

static void init()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    initScene();
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);
    axes();
    drawScene();

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h == 0)  // Calculate The Aspect Ratio Of The Window
        gluPerspective(20, (GLfloat)w, 1.0, 5000.0);
    else
        gluPerspective(20, (GLfloat)w/(GLfloat)h, 1.0, 5000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ( );
}

static void keyboard(unsigned char key, int x, int y) 
{
    switch ( key ) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(100, 100);
    glutCreateWindow("fract1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
