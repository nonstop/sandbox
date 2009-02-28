// Snake.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>

#include "StdAfx.h"
#include "Scene.h"

CScene Scene;

void display ()
{
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	Scene.Draw ();

	glLoadIdentity ();

	gluLookAt ( 0.0, 0.0, 20.0, 
				0.0, 0.0, 0.0,
				0.0, 1.0, 0.0 );
	
	glutSwapBuffers ();
}

void reshape ( int w, int h )
{
	glViewport ( 0, 0, w, h );				// Set the viewport for the OpenGL window
	glMatrixMode ( GL_PROJECTION );			// Change Matrix Mode to Projection
	glLoadIdentity ();						// Reset View

// Do the perspective calculations. Last value = max clipping depth
	gluPerspective ( 60.0, w/h, 1.0, 100.0 );

	glMatrixMode ( GL_MODELVIEW );			// Return to the modelview matrix
	glLoadIdentity ();						// Reset View

	glutPostRedisplay ();
}

void init ( void )
{
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glEnable ( GL_SMOOTH );
	glEnable ( GL_BLEND );
	glBlendFunc ( GL_ONE, GL_ONE );

	Scene.Init ();
}

void mouse ( int button, int state, int x, int y )
{
	Scene.Timer ();
	glutPostRedisplay ();

}

void keypress ( unsigned char key, int x, int y )
{
	switch (key) 
	{
	case 27:	//VK_ESCAPE:
		exit(0);
		break;
	}

	glutPostRedisplay ();
}

void special ( int key, int x, int y )
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Scene.SetSnakeDirection ( sdLeft );
		break;
	case GLUT_KEY_RIGHT:
		Scene.SetSnakeDirection ( sdRight );
		break;
	case GLUT_KEY_UP:
		Scene.SetSnakeDirection ( sdUp );
		break;
	case GLUT_KEY_DOWN:
		Scene.SetSnakeDirection ( sdDown );
		break;
	}
}

void timer ( int value )
{
	Scene.Timer ();
	glutPostRedisplay ();
	glutTimerFunc ( 10, timer, 1 );
}

int main ( int argc, char** argv )
{
	glutInit ( &argc, argv );
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize ( 800, 600 );
	glutInitWindowPosition ( 0, 0 );
	glutCreateWindow ( "GLUT-based snake game" );

	init ();

	glutDisplayFunc		( display );
	glutReshapeFunc		( reshape );
	glutMouseFunc		( mouse );
	glutKeyboardFunc	( keypress );
	glutSpecialFunc		( special ); 
	glutTimerFunc		( 10, timer, 1 );

	glutMainLoop ();

	return 0;
}
