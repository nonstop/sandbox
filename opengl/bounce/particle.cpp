#include "stdafx.h"
#include "stdlib.h"
#include "particle.h"

Particle::Particle(const Grid& grid)
    : grid(grid), trace_len(TRACE_LEN)
{
    steps = 10 +(rand()% int(MAX_PARTICLE_STEPS));

    angle_x = 0;
    angle_y = 0;
    angle_z = 0;

    red        =(rand()% 255)/255.0;
    green    =(rand()% 255)/255.0;
    blue    =(rand()% 255)/255.0;

}

Particle::~Particle()
{
}

void Particle::setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z)
{
    angle_x = ang_x;
    angle_y = ang_y;
    angle_z = ang_z;
}

void Particle::setTrace()
{
    trace[0].x = rand()% grid.getJuncs().x;
    trace[0].y = rand()% grid.getJuncs().y;
    trace[0].z = rand()% grid.getJuncs().z;

    for(int i=1; i<trace_len; i++)
        trace[i] = trace[0];

    trace[0] = selectDest();

    head_pos = grid.getCoords(trace[1]);
    tail_pos = head_pos;
}

Juncs *Particle::getTrace()
{
    return trace;
}

unsigned short Particle::getTraceLen()
{
    return trace_len;
}

Juncs Particle::selectDest()
{
    Juncs dest;

    bool selected = false;

    do
    {
        dest = trace[0];

        int k = rand()% 6;

        switch(k)
        {
        case 0:        // inc X
            if((dest.x+1)<=(grid.getJuncs().x-1))
            {
                direction = dIncX;
                selected = true;
                dest.x += 1;
            }
            break;
        case 1:        // dec X
            if((dest.x-1)>= 0)
            {
                direction = dDecX;
                selected = true;
                dest.x -= 1;
            }
            break;
        case 2:        // inc Y
            if((dest.y+1)<=(grid.getJuncs().y-1))
            {
                direction = dIncY;
                selected = true;
                dest.y += 1;
            }
            break;
        case 3:        // dec Y
            if((dest.y-1)>= 0)
            {
                direction = dDecY;
                selected = true;
                dest.y -= 1;
            }
            break;
        case 4:        // inc Z
            if((dest.z+1)<=(grid.getJuncs().z-1))
            {
                direction = dIncZ;
                selected = true;
                dest.z += 1;
            }
            break;
        case 5:        // dec Z
            if((dest.z-1)>= 0)
            {
                direction = dDecZ;
                selected = true;
                dest.z -= 1;
            }
            break;

        }

        if(dest.x == trace[2].x)
            if(dest.y == trace[2].y)
                if(dest.z == trace[2].z)
                    selected = false;

    } while(!selected);

    cur_step = 0;

    return dest;
}

void Particle::update()
{    
    cur_step++;

    if(cur_step == steps)
    {
        for(int i=trace_len-1; i>0; i--)
            trace[i]= trace[i-1];

        trace[0] = selectDest();
    }


    head_pos = getHeadPos();
    tail_pos = getTailPos();
}

Vertex Particle::getHeadPos()
{
    Vertex result = grid.getCoords(trace[1]);
    float delta;

    switch(direction)
    {
    case dIncX:
        delta = grid.getCoords(trace[0]).x - grid.getCoords(trace[1]).x;
        result.x = result.x + delta*cur_step/steps;
        break;
    case dDecX:
        delta = grid.getCoords(trace[0]).x - grid.getCoords(trace[1]).x;
        result.x = result.x + delta*cur_step/steps;
        break;
    case dIncY:
        delta = grid.getCoords(trace[0]).y - grid.getCoords(trace[1]).y;
        result.y = result.y + delta*cur_step/steps;
        break;
    case dDecY:
        delta = grid.getCoords(trace[0]).y - grid.getCoords(trace[1]).y;
        result.y = result.y + delta*cur_step/steps;
        break;
    case dIncZ:
        delta = grid.getCoords(trace[0]).z - grid.getCoords(trace[1]).z;
        result.z = result.z + delta*cur_step/steps;
        break;
    case dDecZ:
        delta = grid.getCoords(trace[0]).z - grid.getCoords(trace[1]).z;
        result.z = result.z + delta*cur_step/steps;
        break;
    }

    return result;
}

void Particle::getDirection(Direction& dir, const Juncs& jnc1, const Juncs& jnc2)
{
    if(jnc1.x > jnc2.x)
        dir = dIncX;
    if(jnc1.x < jnc2.x)
        dir = dDecX;

    if(jnc1.y > jnc2.y)
        dir = dIncY;
    if(jnc1.y < jnc2.y)
        dir = dDecY;

    if(jnc1.z > jnc2.z)
        dir = dIncZ;
    if(jnc1.z < jnc2.z)
        dir = dDecZ;
}

Vertex Particle::getTailPos()
{
    Vertex result = grid.getCoords(trace[trace_len-1]);
    float delta;

    Direction dir;
    getDirection(dir, trace[trace_len-2], trace[trace_len-1]);

    switch(dir)
    {
    case dIncX:
        delta = grid.getCoords(trace[trace_len-2]).x - grid.getCoords(trace[trace_len-1]).x;
        result.x = result.x + delta*cur_step/steps;
        break;
    case dDecX:
        delta = grid.getCoords(trace[trace_len-2]).x - grid.getCoords(trace[trace_len-1]).x;
        result.x = result.x + delta*cur_step/steps;
        break;
    case dIncY:
        delta = grid.getCoords(trace[trace_len-2]).y - grid.getCoords(trace[trace_len-1]).y;
        result.y = result.y + delta*cur_step/steps;
        break;
    case dDecY:
        delta = grid.getCoords(trace[trace_len-2]).y - grid.getCoords(trace[trace_len-1]).y;
        result.y = result.y + delta*cur_step/steps;
        break;
    case dIncZ:
        delta = grid.getCoords(trace[trace_len-2]).z - grid.getCoords(trace[trace_len-1]).z;
        result.z = result.z + delta*cur_step/steps;
        break;
    case dDecZ:
        delta = grid.getCoords(trace[trace_len-2]).z - grid.getCoords(trace[trace_len-1]).z;
        result.z = result.z + delta*cur_step/steps;
        break;
    }

    return result;
}

void Particle::drawParticle()
{
// рисование самой частицы
    glPushMatrix();
    glTranslatef(head_pos.x, head_pos.y, head_pos.z);
    glRotatef(angle_x, 1.0, 0.0, 0.0);
    glRotatef(45.0 + angle_y, 0.0, 1.0, 0.0);
    glRotatef(angle_z, 0.0, 0.0, 1.0);

    glColor4f(red, green, blue, 1.0);
    glEnable(GL_BLEND);
    glCallList(IL_PARTICLE);
    glDisable(GL_BLEND);

    glPopMatrix();

}

void Particle::drawTail()
{
// рисование следа частицы
    glLineWidth(2);

    glBegin(GL_LINE_STRIP);

// перелив цвета от головы  к хвосту
//    GLfloat fr_red        = 0.2 + 0.8*(2*(MAX_PARTICLE_STEPS-steps)/MAX_PARTICLE_STEPS);
//    GLfloat fr_green    = 0.8f;
//    GLfloat fr_blue        = 0.8f;

    GLfloat fr_red        = red;
    GLfloat fr_green    = green;
    GLfloat fr_blue        = blue;

    GLfloat to_red        = 0.1f;
    GLfloat to_green    = 0.1f;
    GLfloat to_blue        = 0.4f;


    glColor3f(fr_red, fr_green, fr_blue);
    glVertex3fv(&head_pos.x);

    for(int i=1; i<trace_len-1; i++)
    {
        fr_red   -=(cur_step +(i-1)*steps)*((fr_red - to_red)/(steps*trace_len));
        fr_green -=(cur_step +(i-1)*steps)*((fr_green - to_green)/(steps*trace_len));;
        fr_blue  -=(cur_step +(i-1)*steps)*((fr_blue - to_blue)/(steps*trace_len));;

        glColor3f(fr_red, fr_green, fr_blue);

        glVertex3fv(&(grid.getCoords(trace[i]).x));
    }

    glColor3f(to_red, to_green, to_blue);
    glVertex3fv(&tail_pos.x);

    glEnd();
}
