/*
 * OpenGL bitmap viewing demo from Chapter 7.
 *
 * Written by Michael Sweet.
 */

/*
 * Include necessary headers.
 */

#include "bitmap.h"
#include <GL/glut.h>


/*
 * Globals...
 */

int        Width;       /* Width of window */
int        Height;      /* Height of window */
BITMAPINFO *BitmapInfo; /* Bitmap information */
GLubyte    *BitmapBits; /* Bitmap data */


/*
 * Functions...
 */

void Redraw(void);
void Resize(int width, int height);


/*
 * 'main()' - Open a window and display a bitmap.
 */

int                /* O - Exit status */
main(int  argc,    /* I - Number of command-line arguments */
     char *argv[]) /* I - Command-line arguments */
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(792, 573);
    glutCreateWindow("Bitmap File Viewer");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);

    if (argc > 1)
        BitmapBits = LoadDIBitmap(argv[1], &BitmapInfo);
    else
        BitmapBits = LoadDIBitmap("mountain.bmp", &BitmapInfo);

    glutMainLoop();
    if (BitmapInfo)
        {
	free(BitmapInfo);
	free(BitmapBits);
	}
    return (0);
    }


/*
 * 'Redraw()' - Redraw the window...
 */

void
Redraw(void)
    {
    GLfloat xsize, ysize;     /* Size of image */
    GLfloat xoffset, yoffset; /* Offset of image */
    GLfloat xscale, yscale;   /* Scaling of image */

    /* Clear the window to black */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (BitmapInfo)
        {
        xsize = Width;
        ysize = BitmapInfo->bmiHeader.biHeight * xsize /
                BitmapInfo->bmiHeader.biWidth;
        if (ysize > Height)
            {
            ysize = Height;
            xsize = BitmapInfo->bmiHeader.biWidth * ysize /
                    BitmapInfo->bmiHeader.biHeight;
            }

        xscale  = xsize / BitmapInfo->bmiHeader.biWidth;
        yscale  = ysize / BitmapInfo->bmiHeader.biHeight;

        xoffset = (Width - xsize) * 0.5;
        yoffset = (Height - ysize) * 0.5;

        glRasterPos2f(xoffset, yoffset);
        glPixelZoom(xscale, yscale);

        glDrawPixels(BitmapInfo->bmiHeader.biWidth,
                     BitmapInfo->bmiHeader.biHeight,
                     GL_BGR_EXT, GL_UNSIGNED_BYTE, BitmapBits);
        }

    glFinish();
    }


/*
 * 'Resize()' - Resize the window...
 */

void
Resize(int width,  /* I - Width of window */
       int height) /* I - Height of window */
    {
    /* Save the new width and height */
    Width  = width;
    Height = height;

    /* Reset the viewport... */
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLfloat)width, 0.0, (GLfloat)height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    }
