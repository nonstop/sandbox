#include <stdlib.h>

#include "stdafx.h"
#include "Clocks.h"
#include "Scene.h"

CScene			Scene;				//	сцена

void redraw_timer(int)
{
    Scene.Update();
    display ();
    glutPostRedisplay();

    glutTimerFunc(10, redraw_timer, 1); 
}

void curve_timer(int)
{
    static GLuint curve = 0;
    curve = ((curve+1) <= 59) ? ++curve : 0;
    Scene.SetCurve(curve);
    glutTimerFunc(10, curve_timer, 1); 
}

void shrink_timer(int)
{
    static bool shrink_grow = true;
    static GLfloat radius = 8.0;
    const GLfloat step = 0.1;
    if (shrink_grow) {
        if ((radius + step) > 10) {
            radius -= step;
            shrink_grow = false;
        } else
            radius += step;
    } else {
        if ((radius - step) < 8) {
            radius += step;
            shrink_grow = true;
        } else
            radius -= step;
    }
    Scene.SetRadius(radius);
    glutTimerFunc(100, shrink_timer, 1); 
}

void clock_timer(int)
{
    static GLuint seconds = 0;
    static GLuint minutes = 0;
    static GLuint hours = 0;
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours = (hours >= 11) ? 0 : ++hours;
            Scene.SetHour(hours);
        }
        Scene.SetMinute(minutes);
    } else
        Scene.SetSecond(seconds);
    glutTimerFunc(1000, clock_timer, 1); 
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

void initLight()
{
//	Устанавливаем цвет
	GLfloat l_diffuse[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
	GLfloat l_specular[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat l_ambient[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0,GL_DIFFUSE,l_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,l_specular);
	glLightfv(GL_LIGHT0,GL_AMBIENT,l_ambient);
//	Устанавливаем источник освещения
	GLfloat l_position[4] = { 0.0f, 0.0f, -20.0f, 0.0f };
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0,GL_POSITION,l_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	return;
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.4f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);

	initLight();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	Scene.Init();
}

void display ()	
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene.Draw();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, w/h, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt ( 0.0, 0.0, 20.0, 
				0.0, 0.0, 0.0,
				0.0, 1.0, 0.0 );
}

void special(int key, int x, int y)
{
    exit(0);
}

int main(int ac, char* av[])
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(800, 800);
    glutCreateWindow("All star game");
//    glutFullScreen();

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keypress);
    glutSpecialFunc(special);
    glutTimerFunc(10, redraw_timer, 1); 
    glutTimerFunc(1000, clock_timer, 1); 
    glutTimerFunc(100, shrink_timer, 1); 
    glutTimerFunc(10, curve_timer, 1);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();
    return 0;
}
