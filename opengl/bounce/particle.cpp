#include "stdafx.h"
#include "particle.h"

Particle::Particle(const Grid& grid)
    : grid(grid), trace_len(TRACE_LEN)
{
    steps = 10 +(rand()% int(MAX_PARTICLE_STEPS));

    angle_x = 0;
    angle_y = 0;
    angle_z = 0;

    red     =(rand()% 255)/255.0;
    green   =(rand()% 255)/255.0;
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

Junc *Particle::getTrace()
{
    return trace;
}

unsigned short Particle::getTraceLen()
{
    return trace_len;
}

Junc Particle::selectDest()
{
    Junc dest;

    bool selected = false;

    do
    {
        dest = trace[0];

        int k = rand()% 6;
        Juncs neighbors;
        grid.getNeighbors(neighbors, dest);

        switch(k)
        {
        case 0:        // inc X
            if((dest.x+1)<=(grid.getJuncs().x-1))
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
            if((dest.y+1)<=(grid.getJuncs().y-1))
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
            if((dest.z+1)<=(grid.getJuncs().z-1))
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
        for(int i=trace_len-1; i>0; --i)
            trace[i]= trace[i-1];

        trace[0] = grid.getNextDest(trace[0]);
    }


    head_pos = getHeadPos();
    tail_pos = getTailPos();
}

enum Direction { dIncX, dDecX, dIncY, dDecY, dIncZ, dDecZ };
// возвращает направление по двум точкам(типа 0,1 или last-1, last)
static Direction getDirection(const Junc& jnc1, const Junc& jnc2)
{
    if(jnc1.x > jnc2.x) return dIncX;
    if(jnc1.x < jnc2.x) return dDecX;
    if(jnc1.y > jnc2.y) return dIncY;
    if(jnc1.y < jnc2.y) return dDecY;
    if(jnc1.z > jnc2.z) return dIncZ;
    if(jnc1.z < jnc2.z) return dDecZ;
}

#warning ugly function signature - do something
static void computePosition(Vertex& pos, Direction dir, int cur_step, int steps, const Vertex& pos1, const Vertex& pos2)
{
    float delta = 0;
    switch (dir) {
    case dIncX:
        delta = pos1.x - pos2.x;
        pos.x = pos.x + delta * cur_step/steps;
        break;
    case dDecX:
        delta = pos1.x - pos2.x;
        pos.x = pos.x + delta * cur_step/steps;
        break;
    case dIncY:
        delta = pos1.y - pos2.y;
        pos.y = pos.y + delta * cur_step/steps;
        break;
    case dDecY:
        delta = pos1.y - pos2.y;
        pos.y = pos.y + delta * cur_step/steps;
        break;
    case dIncZ:
        delta = pos1.z - pos2.z;
        pos.z = pos.z + delta * cur_step/steps;
        break;
    case dDecZ:
        delta = pos1.z - pos2.z;
        pos.z = pos.z + delta * cur_step/steps;
        break;
    }

}

Vertex Particle::getHeadPos()
{
    Vertex result = grid.getCoords(trace[1]);
    Direction dir = getDirection(trace[0], trace[1]);
    computePosition(result, dir, cur_step, steps, grid.getCoords(trace[0]), grid.getCoords(trace[1]));
    return result;
}

Vertex Particle::getTailPos()
{
    Vertex result = grid.getCoords(trace[trace_len-1]);
    Direction dir = getDirection(trace[trace_len-2], trace[trace_len-1]);
    computePosition(result, dir, cur_step, steps, grid.getCoords(trace[trace_len-2]), grid.getCoords(trace[trace_len-1]));
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

// рисование следа частицы
void Particle::drawTail()
{
    glLineWidth(2);

    glBegin(GL_LINE_STRIP);

// перелив цвета от головы  к хвосту
//    GLfloat fr_red        = 0.2 + 0.8*(2*(MAX_PARTICLE_STEPS-steps)/MAX_PARTICLE_STEPS);
//    GLfloat fr_green    = 0.8f;
//    GLfloat fr_blue        = 0.8f;
    Color fromColor = {red, green, blue};
    const Color toColor = {0.1f, 0.1f, 0.4f};

    glColor3fv(&fromColor.red);
    glVertex3fv(&head_pos.x);

#define CHANGE_COLOR(x) fromColor.x -= \
    (cur_step + (i - 1) * steps) * ((fromColor.x - toColor.x)/(steps * trace_len))
    for (int i=1; i<trace_len-1; ++i) {
        CHANGE_COLOR(red);
        CHANGE_COLOR(green);
        CHANGE_COLOR(blue);

        glColor3fv(&fromColor.red);
        glVertex3fv(&(grid.getCoords(trace[i]).x));
    }

    glColor3fv(&toColor.red);
    glVertex3fv(&tail_pos.x);

    glEnd();
}
