// StarLight.cpp : Defines the entry point for the console application.
//

#include <GL/gl.h>
#include <GL/glut.h>
//#include <stdlib.h>
#include <math.h>

#define radius 10.0
#define smooth 40.0

GLUquadricObj* quadObj;

void display ()
{
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix ();
	
	gluSphere ( quadObj, radius, smooth, smooth );

	glPopMatrix ();

	glutSwapBuffers ();
}

void reshape ( int w, int h )
{
	glViewport ( 0, 0, (GLsizei)w, (GLsizei)h );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	glOrtho ( -50.0, 50.0, -50.0, 50.0, -50.0, 50.0 );
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();

	glRotatef(45.0, 1.0, 0.0, 0.0); // поворот объекта - ось X
	glRotatef(-45.0, 0.0, 1.0, 0.0); // поворот объекта - ось Y
	glRotatef(0.0, 0.0, 0.0, 1.0); // поворот объекта - ось Z

}

void init ( void )
{
	quadObj = gluNewQuadric ();
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glShadeModel ( GL_FLAT );
	glColor3f ( 1.0, 0.0, 0.0 );
	
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable ( GL_DEPTH_TEST );
	glEnable ( GL_LIGHTING );
	glEnable ( GL_LIGHT0 );
	glEnable ( GL_COLOR_MATERIAL );
}

void mouse ( int button, int state, int x, int y )
{
	char buff[20];

	if (( button == GLUT_LEFT_BUTTON ) 
		&& ( state == GLUT_UP ))
	{
		glColor3d ( 0.0, 1.0, 0.0 );
		glutPostRedisplay ();
/*		itoa ( x, buff, 10 );
		printf ( " X = " );
		printf ( buff );
		itoa ( y, buff, 10 );
		printf ( "\n Y = " );
		printf ( buff );
		printf ( "\n" );*/
	}

	return;
}

int main ( int argc, char** argv )
{
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize ( 400, 400 );
	glutInitWindowPosition ( 0, 0 );
	glutCreateWindow ( argv[0] );
	init ();
	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutMouseFunc ( mouse );
	glutMainLoop ();

	return 0;
}
