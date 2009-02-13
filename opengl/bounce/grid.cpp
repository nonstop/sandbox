#include "stdafx.h"
#include <stdlib.h>
#include "grid.h"

Grid::Grid()
    : n_juncs_x(JUNCTIONS_X), n_juncs_y(JUNCTIONS_Y), n_juncs_z(JUNCTIONS_Z)
{}

Grid::~Grid()
{}

void Grid::init(float len_x, float len_y, float len_z)
{
    for(int i=0; i<n_juncs_x; i++)
        for(int j=0; j<n_juncs_y; j++)
            for(int k=0; k<n_juncs_z; k++)
            {
                coords[i][j][k].x =(GLfloat)i*len_x/(n_juncs_x-1);
                coords[i][j][k].y =(GLfloat)j*len_y/(n_juncs_y-1);
                coords[i][j][k].z =(GLfloat)k*len_z/(n_juncs_z-1);
            }
}

void Grid::setImageList(GLuint ilID)
{

    glNewList(ilID, GL_COMPILE);
    glColor3f(0.5, 0.5, 0.5);

    GLUquadricObj *qObj = gluNewQuadric();
    for(int i=0; i<n_juncs_x; i++)
        for(int j=0; j<n_juncs_y; j++)
            for(int k=0; k<n_juncs_z; k++)
            {
                glPushMatrix();

                glTranslatef(coords[i][j][k].x, coords[i][j][k].y , coords[i][j][k].z);

                glScalef(0.05f, 0.05f, 0.05f);

                gluSphere(qObj, 1, 3, 3);

                glPopMatrix();
            }


    gluDeleteQuadric(qObj);    
    glEndList();
}

void Grid::draw()
{
    glCallList(IL_GRID);
    return;
}

Junc Grid::getJuncs() const
{
    Junc nJuncs = {
        n_juncs_x,
        n_juncs_y,
        n_juncs_z};

    return nJuncs;
}

Junc Grid::selectDest(const Junc& curJunc, const Junc& junc2) const
{
    Junc dest;

    bool selected = false;

    do
    {
        dest = curJunc;

        int k = rand()% 6;

        switch(k)
        {
        case 0:        // inc X
            if((dest.x+1)<=(n_juncs_x-1))
            {
                selected = true;
                dest.x += 1;
            }
            break;
        case 1:        // dec X
            if((dest.x-1)>= 0)
            {
                selected = true;
                dest.x -= 1;
            }
            break;
        case 2:        // inc Y
            if((dest.y+1)<=(n_juncs_y-1))
            {
                selected = true;
                dest.y += 1;
            }
            break;
        case 3:        // dec Y
            if((dest.y-1)>= 0)
            {
                selected = true;
                dest.y -= 1;
            }
            break;
        case 4:        // inc Z
            if((dest.z+1)<=(n_juncs_z-1))
            {
                selected = true;
                dest.z += 1;
            }
            break;
        case 5:        // dec Z
            if((dest.z-1)>= 0)
            {
                selected = true;
                dest.z -= 1;
            }
            break;

        }

        if(dest.x == junc2.x)
            if(dest.y == junc2.y)
                if(dest.z == junc2.z)
                    selected = false;

    } while(!selected);


    return dest;
}

Vertex Grid::getCoords(unsigned short i, unsigned short j, unsigned short k) const
{
    return coords[i][j][k];
}

Vertex Grid::getCoords(const Junc& jnc) const
{
    return coords[jnc.x][jnc.y][jnc.z];
}
