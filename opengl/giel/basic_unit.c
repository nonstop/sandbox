#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "basic_unit.h"
#include "utils.h"

#ifndef M_SQRT1_2
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif // M_SQRT1_2


#define VOFFSET 0.045
/* the triangular prism what makes up the basic unit */
static const float solid_prism_v[][3] = {
    /* first corner, bottom left front */
    { VOFFSET, VOFFSET, 1.0 },
    { VOFFSET, 0.00, 1.0 - VOFFSET },
    { 0.00, VOFFSET, 1.0 - VOFFSET },
    /* second corner, rear */
    { VOFFSET, VOFFSET, 0.00 },
    { VOFFSET, 0.00, VOFFSET },
    { 0.00, VOFFSET, VOFFSET },
    /* third, right front */
    { 1.0 - VOFFSET / M_SQRT1_2, VOFFSET, 1.0 },
    { 1.0 - VOFFSET / M_SQRT1_2, 0.0, 1.0 - VOFFSET },
    { 1.0 - VOFFSET * M_SQRT1_2, VOFFSET, 1.0 - VOFFSET },
    /* fourth, right rear */
    { 1.0 - VOFFSET / M_SQRT1_2, VOFFSET, 0.0 },
    { 1.0 - VOFFSET / M_SQRT1_2, 0.0, VOFFSET },
    { 1.0 - VOFFSET * M_SQRT1_2, VOFFSET, VOFFSET },
    /* fifth, upper front */
    { VOFFSET, 1.0 - VOFFSET / M_SQRT1_2, 1.0 },
    { VOFFSET / M_SQRT1_2, 1.0 - VOFFSET * M_SQRT1_2, 1.0 - VOFFSET },
    { 0.0, 1.0 - VOFFSET / M_SQRT1_2, 1.0 - VOFFSET},
    /* sixth, upper rear */
    { VOFFSET, 1.0 - VOFFSET / M_SQRT1_2, 0.0 },
    { VOFFSET / M_SQRT1_2, 1.0 - VOFFSET * M_SQRT1_2, VOFFSET },
    { 0.0, 1.0 - VOFFSET / M_SQRT1_2, VOFFSET }};

static const float solid_prism_n[][3] = {/* corners */
    { -VOFFSET, -VOFFSET, VOFFSET },
    { VOFFSET, -VOFFSET, VOFFSET },
    { -VOFFSET, VOFFSET, VOFFSET },
    { -VOFFSET, -VOFFSET, -VOFFSET },
    { VOFFSET, -VOFFSET, -VOFFSET },
    { -VOFFSET, VOFFSET, -VOFFSET },
    /* edges */
    { -VOFFSET, 0.0, VOFFSET },
    { 0.0, -VOFFSET, VOFFSET },
    { VOFFSET, VOFFSET, VOFFSET },
    { -VOFFSET, 0.0, -VOFFSET },
    { 0.0, -VOFFSET, -VOFFSET },
    { VOFFSET, VOFFSET, -VOFFSET },
    { -VOFFSET, -VOFFSET, 0.0 },
    { VOFFSET, -VOFFSET, 0.0 },
    { -VOFFSET, VOFFSET, 0.0 },
    /* faces */
    { 0.0, 0.0, 1.0 },
    { 0.0, -1.0, 0.0 },
    { M_SQRT1_2, M_SQRT1_2, 0.0 },
    { -1.0, 0.0, 0.0 },
    { 0.0, 0.0, -1.0 }};

static const float wire_prism_v[][3] = {{ 0.0, 0.0, 1.0 },
               { 1.0, 0.0, 1.0 },
               { 0.0, 1.0, 1.0 },
               { 0.0, 0.0, 0.0 },
               { 1.0, 0.0, 0.0 },
               { 0.0, 1.0, 0.0 }};

static const int BASIC_UNIT_LIST = 1;

void basic_unit_init_imagelist()
{
    glNewList(BASIC_UNIT_LIST, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glNormal3fv(solid_prism_n[0]);
    glVertex3fv(solid_prism_v[0]);
    glVertex3fv(solid_prism_v[2]);
    glVertex3fv(solid_prism_v[1]);
    
    glNormal3fv(solid_prism_n[1]);
    glVertex3fv(solid_prism_v[6]);
    glVertex3fv(solid_prism_v[7]);
    glVertex3fv(solid_prism_v[8]);
    
    glNormal3fv(solid_prism_n[2]);
    glVertex3fv(solid_prism_v[12]);
    glVertex3fv(solid_prism_v[13]);
    glVertex3fv(solid_prism_v[14]);
    
    glNormal3fv(solid_prism_n[3]);
    glVertex3fv(solid_prism_v[3]);
    glVertex3fv(solid_prism_v[4]);
    glVertex3fv(solid_prism_v[5]);
    
    glNormal3fv(solid_prism_n[4]);
    glVertex3fv(solid_prism_v[9]);
    glVertex3fv(solid_prism_v[11]);
    glVertex3fv(solid_prism_v[10]);
    
    glNormal3fv(solid_prism_n[5]);
    glVertex3fv(solid_prism_v[16]);
    glVertex3fv(solid_prism_v[15]);
    glVertex3fv(solid_prism_v[17]);
    glEnd();
    /* edges */
    glBegin(GL_QUADS);
    glNormal3fv(solid_prism_n[6]);
    glVertex3fv(solid_prism_v[0]);
    glVertex3fv(solid_prism_v[12]);
    glVertex3fv(solid_prism_v[14]);
    glVertex3fv(solid_prism_v[2]);
    
    glNormal3fv(solid_prism_n[7]);
    glVertex3fv(solid_prism_v[0]);
    glVertex3fv(solid_prism_v[1]);
    glVertex3fv(solid_prism_v[7]);
    glVertex3fv(solid_prism_v[6]);
    
    glNormal3fv(solid_prism_n[8]);
    glVertex3fv(solid_prism_v[6]);
    glVertex3fv(solid_prism_v[8]);
    glVertex3fv(solid_prism_v[13]);
    glVertex3fv(solid_prism_v[12]);
    
    glNormal3fv(solid_prism_n[9]);
    glVertex3fv(solid_prism_v[3]);
    glVertex3fv(solid_prism_v[5]);
    glVertex3fv(solid_prism_v[17]);
    glVertex3fv(solid_prism_v[15]);
    
    glNormal3fv(solid_prism_n[10]);
    glVertex3fv(solid_prism_v[3]);
    glVertex3fv(solid_prism_v[9]);
    glVertex3fv(solid_prism_v[10]);
    glVertex3fv(solid_prism_v[4]);
    
    glNormal3fv(solid_prism_n[11]);
    glVertex3fv(solid_prism_v[15]);
    glVertex3fv(solid_prism_v[16]);
    glVertex3fv(solid_prism_v[11]);
    glVertex3fv(solid_prism_v[9]);
    
    glNormal3fv(solid_prism_n[12]);
    glVertex3fv(solid_prism_v[1]);
    glVertex3fv(solid_prism_v[2]);
    glVertex3fv(solid_prism_v[5]);
    glVertex3fv(solid_prism_v[4]);
    
    glNormal3fv(solid_prism_n[13]);
    glVertex3fv(solid_prism_v[8]);
    glVertex3fv(solid_prism_v[7]);
    glVertex3fv(solid_prism_v[10]);
    glVertex3fv(solid_prism_v[11]);
    
    glNormal3fv(solid_prism_n[14]);
    glVertex3fv(solid_prism_v[13]);
    glVertex3fv(solid_prism_v[16]);
    glVertex3fv(solid_prism_v[17]);
    glVertex3fv(solid_prism_v[14]);
    glEnd();
    
    /* faces */
    glBegin(GL_TRIANGLES);
    glNormal3fv(solid_prism_n[15]);
    glVertex3fv(solid_prism_v[0]);
    glVertex3fv(solid_prism_v[6]);
    glVertex3fv(solid_prism_v[12]);
    
    glNormal3fv(solid_prism_n[19]);
    glVertex3fv(solid_prism_v[3]);
    glVertex3fv(solid_prism_v[15]);
    glVertex3fv(solid_prism_v[9]);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3fv(solid_prism_n[16]);
    glVertex3fv(solid_prism_v[1]);
    glVertex3fv(solid_prism_v[4]);
    glVertex3fv(solid_prism_v[10]);
    glVertex3fv(solid_prism_v[7]);
    
    glNormal3fv(solid_prism_n[17]);
    glVertex3fv(solid_prism_v[8]);
    glVertex3fv(solid_prism_v[11]);
    glVertex3fv(solid_prism_v[16]);
    glVertex3fv(solid_prism_v[13]);
    
    glNormal3fv(solid_prism_n[18]);
    glVertex3fv(solid_prism_v[2]);
    glVertex3fv(solid_prism_v[14]);
    glVertex3fv(solid_prism_v[17]);
    glVertex3fv(solid_prism_v[5]);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex3fv(wire_prism_v[0]);
    glVertex3fv(wire_prism_v[1]);
    glVertex3fv(wire_prism_v[2]);
    glVertex3fv(wire_prism_v[0]);
    glVertex3fv(wire_prism_v[3]);
    glVertex3fv(wire_prism_v[4]);
    glVertex3fv(wire_prism_v[5]);
    glVertex3fv(wire_prism_v[3]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3fv(wire_prism_v[1]);
    glVertex3fv(wire_prism_v[4]);
    glVertex3fv(wire_prism_v[2]);
    glVertex3fv(wire_prism_v[5]);
    glEnd();
    glEndList();
}

static void drawBasicUnit(const BasicUnit* unit)
{
    glPushMatrix();
    GLfloat red = 0, green = 0, blue = 0, curr = 0;
    if (unit->isCurrent) {
        curr = 0.2;
    }
    if (unit->isOdd) {
        red = 0.7; green = 0; blue = 0;
        glTranslatef(0.5, 0.5, 0);
        glRotatef(180, 0, 0, 1);
    } else {
        glTranslatef(-0.5, 0, 0);
        red = 0; green = 0; blue = 0.7;
    }
    glColor4f(red + curr, green + curr, blue + curr, 0.5);
    glTranslatef(0, 0, -0.5);
    glCallList(BASIC_UNIT_LIST);
    glPopMatrix();
}

void appendBasicUnits(BasicUnit* tail, int count)
{
    if (count == 0)
        return;
    BasicUnit* currentUnit = tail;
    while (count--) {
        currentUnit->next = (BasicUnit*)calloc(1, sizeof(BasicUnit));
        currentUnit->next->prev = currentUnit;
        currentUnit->next->isOdd = (currentUnit->isOdd) ? 0 : 1;
        currentUnit = currentUnit->next;
        TRACE("%p prev=%p count %d odd %d", currentUnit, currentUnit->prev, count, currentUnit->isOdd);
    }
}

void freeBasicUnits(BasicUnit* headUnit)
{
    TRACE("unit=%p", headUnit);
    int cnt = 0;
    BasicUnit* currentUnit = headUnit;
    while (currentUnit) {
        TRACE("count %d odd %d", cnt++, currentUnit->isOdd);
        BasicUnit* tmp = currentUnit->next;
        free(currentUnit);
        currentUnit = tmp;
    }
}

void drawBasicUnits(BasicUnit* headUnit)
{
    BasicUnit* currentUnit = headUnit;
    glPushMatrix();
    while (currentUnit) {
        GLfloat angle = 0, x = 0, y = 0;
        if (currentUnit->isOdd) {
            x = 1; y = 0;
        } else {
            x = 0; y = 1;
        }
        switch (currentUnit->rot)
        {
            case BUR_LEFT:
                angle = 90;
                break;
            case BUR_RIGHT:
                angle = -90;
                break;
            case BUR_DOWN:
                angle = -180;
                 break;
            case BUR_NONE:
                 break;
        }
        glRotatef(angle, x, y, 0);
        drawBasicUnit(currentUnit);
        if (currentUnit->isOdd) {
            glTranslatef(-0, 0.5, 0);
        } else {
            glTranslatef(-1, 0.5, 0.0);
        }
        currentUnit = currentUnit->next;
    }
    glPopMatrix();
}

void basic_unit_turn_left(BasicUnit* unit)
{
    int rot = unit->rot;
    rot++;
    if (rot > BUR_RIGHT)
        rot = BUR_NONE;
    unit->rot = rot;
    TRACE("rot=%d", rot);
}

void basic_unit_turn_right(BasicUnit* unit)
{
    int rot = unit->rot;
    rot--;
    if (rot < BUR_NONE)
        rot = BUR_RIGHT;
    unit->rot = rot;
}

