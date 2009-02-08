#include "stdafx.h"
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

Juncs Grid::getJuncs() const
{
    Juncs nJuncs = {
        n_juncs_x,
        n_juncs_y,
        n_juncs_z};

    return nJuncs;
}

Vertex Grid::getCoords(unsigned short i, unsigned short j, unsigned short k) const
{
    return coords[i][j][k];
}

Vertex Grid::getCoords(const Juncs& jnc) const
{
    return coords[jnc.x][jnc.y][jnc.z];
}
