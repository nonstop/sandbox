#include <stdlib.h>

#include "particle.h"

namespace
{
unsigned short generateSteps()
{
    const int MAX_PARTICLE_STEPS = 60;
    return 10 +(rand()% int(MAX_PARTICLE_STEPS));
}
Color generateColor()
{
    Color c = {
        (rand() % 255)/255.0,
        (rand() % 255)/255.0,
        (rand() % 255)/255.0};
    return c;
}
}

Particle::Particle(const Grid& grid)
    : grid(grid), steps(generateSteps()), trace_len(TRACE_LEN), m_color(generateColor()),
    cur_step(0)
{
    angle_x = 0;
    angle_y = 0;
    angle_z = 0;
}

Particle::~Particle()
{}

void Particle::setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z)
{
    angle_x = ang_x;
    angle_y = ang_y;
    angle_z = ang_z;
}

void Particle::setTrace()
{
    trace[0].x = rand() % grid.getJuncs().x;
    trace[0].y = rand() % grid.getJuncs().y;
    trace[0].z = rand() % grid.getJuncs().z;

    for(int i=1; i<trace_len; i++)
        trace[i] = trace[0];

    trace[0] = grid.selectDest(trace[0], trace[2]);

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

void Particle::update()
{    
    cur_step++;

    if(cur_step == steps)
    {
        for(int i=trace_len-1; i>0; --i)
            trace[i]= trace[i-1];

        trace[0] = grid.selectDest(trace[0], trace[2]);
        cur_step = 0;
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

    glColor4f(m_color.red, m_color.green, m_color.blue, 1.0);
    glCallList(IL_PARTICLE);

    glPopMatrix();

}

// рисование следа частицы
void Particle::drawTail()
{
    glBegin(GL_LINE_STRIP);

    glColor4f(m_color.red, m_color.green, m_color.blue, 1.0);
    glVertex3fv(&head_pos.x);

    GLfloat k = 1.0 / (steps * (trace_len - 1));
    GLfloat alpha = 1.0 - cur_step * k;
    for (int i=1; i<trace_len-1; ++i) {
        alpha -= steps * k;

        glColor4f(m_color.red, m_color.green, m_color.blue, alpha);
        glVertex3fv(&(grid.getCoords(trace[i]).x));
    }

    glColor4f(m_color.red, m_color.green, m_color.blue, 0.0);
    glVertex3fv(&tail_pos.x);

    glEnd();
}
