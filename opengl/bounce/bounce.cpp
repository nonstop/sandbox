#include <GL/glut.h>

#include <ctime>
#include <math.h>

#include "scene.h"


namespace
{
Scene scene;
}

// Оси координат
void axes()
{
    glPushMatrix();

    GLint width;
    glGetIntegerv(GL_LINE_WIDTH, &width);

    glLineWidth(5);

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

    scene.draw();

    glPopMatrix();

    glLoadIdentity();
    gluLookAt(20.0, 20.0, 20.0, 
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);                // Set the viewport for the OpenGL window
    glMatrixMode(GL_PROJECTION);            // Change Matrix Mode to Projection
    glLoadIdentity();                        // Reset View

// Do the perspective calculations. Last value = max clipping depth
    gluPerspective(60.0, w/h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);            // Return to the modelview matrix
    glLoadIdentity();                        // Reset View

    glutPostRedisplay();
}


void idle()
{
/*    GLfloat ang_x, ang_y, ang_z;
    scene.getAngles(&ang_x, &ang_y, &ang_z);

    ang_y =(ang_y+0.05 >= 360)? 0 :(ang_y+0.05);

    scene.setAngles(ang_x, ang_y, ang_z);

    scene.update();
    glutPostRedisplay();*/
}

void init()
{
    srand(time(NULL));
    glClearColor(0.1f, 0.1f, 0.4f, 0.0);                    // Dark Blue Background
    glShadeModel(GL_SMOOTH);                                // Enables Smooth Color Shading
    glClearDepth(1.0);                                    // Depth Buffer Setup
    glDepthFunc(GL_LESS);                                    // The Type Of Depth Test To Do
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Realy Nice perspective calculations
    glEnable(GL_TEXTURE_2D);                                // Enable Texture Mapping
    
    scene.init();
}

void special(int key, int x, int y)
{
    exit(0);
}

void keypress(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27://VK_ESCAPE:
        exit(0);
        break;
    default:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void timer(int value)
{
    GLfloat ang_x, ang_y, ang_z;
    scene.getAngles(&ang_x, &ang_y, &ang_z);

    ang_y =(ang_y+0.05 >= 360)? 0 :(ang_y+0.05);

    scene.setAngles(ang_x, ang_y, ang_z);

    scene.update();
    glutPostRedisplay();

    glutTimerFunc(10, timer, 1); 
}

void run(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(800, 800);
    glutCreateWindow("GLUT-based OpenGL skyfly");
//    glutFullScreen();

    init();
    glutDisplayFunc(display);
//    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keypress);
    glutSpecialFunc(special);
    glutTimerFunc(10, timer, 1); 
    glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();

    return;
}

int main(int argc, char* argv[])
{
    run(argc, argv);

    return 0;
}
