#include <stdlib.h>
#include <GL/glut.h>

double angle = 0;

void OnDraw()
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    glColor3f(0, 1, 0);
    GLUquadric *q = gluNewQuadric();
    gluDisk(q, 5, 5.1, 40, 1);

    glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glColor3f(1, 1, 1);
    gluDisk(q, 0, 0.5, 40, 1);
    glColor3f(0, 0, 0);
    gluDisk(q, 0, 2.5, 40, 1);
    glTranslatef(0, -5, 0);
    glColor3f(0, 0, 0);
    gluDisk(q, 0, 0.5, 40, 1);
    glColor3f(1, 1, 1);
    gluDisk(q, 0, 2.5, 40, 1);
    glPopMatrix();
	
    glColor3f(1, 1, 1);
    gluPartialDisk(q, 0, 5, 40, 1, 0, 180);
    gluDeleteQuadric(q);

    glPopMatrix();

    glutSwapBuffers();
}

void OnInit() 
{
	glEnable(GL_DEPTH_TEST);
}

void OnExit()
{
}

void OnReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-12,12,-12,12,-1,1);
	glMatrixMode(GL_MODELVIEW);
}

void OnTimer(int value)
{
    angle = (angle >= 360) ? 0 : angle + 0.5 ;
    glutPostRedisplay();

    glutTimerFunc(10, OnTimer, 0);
}

int main(int argc,char** argv) 
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowSize(200,200);
	glutCreateWindow("A basic primitive example");

	glutDisplayFunc(OnDraw);
    glutReshapeFunc(OnReshape);
    glutTimerFunc(10, OnTimer, 0);
	
	OnInit();

	atexit(OnExit);

	glutMainLoop();
	return 0;
}

