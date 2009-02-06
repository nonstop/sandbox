
#include <GL/gl.h>
#include <GL/glut.h>

float angle;      // Angle For The Triangle

    GLfloat lightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[]= { 0.0f, 10.0f, 00.0f, 1.0f };

void initGL()        // Create Some Everyday Functions
{

    glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);    // Black Background
    glClearDepth(1.0f);         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display()      // Create The Display Function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();         // Reset The Current Modelview Matrix

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -6.0f);
    glColor3f(0.2f, 0.7f, 0.2f);
    glutSolidCube(2.0);
        
/*    glPushMatrix();
    glTranslatef(0.0f, 1.0f, -6.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(0.2f, 0.7f, 0.2f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -6.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(0.2f, 0.2f, 0.7f);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();*/

    glPopMatrix();
    angle = (angle >= 360) ? 0 : angle + 0.2;
    

    glutSwapBuffers();
}

void reshape(int width , int height)      // Create The Reshape Function (the viewport)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int ac, char *av[])
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ying-Yang in 3D");
    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}

