#include <stdlib.h>

#include "particle.h"

namespace
{
static unsigned short generateSteps()
{
    const int MAX_PARTICLE_STEPS = 60;
    return 10 +(rand()% int(MAX_PARTICLE_STEPS));
}
static Color generateColor()
{
    Color c = {
        (rand() % 255)/255.0,
        (rand() % 255)/255.0,
        (rand() % 255)/255.0,
        1.0};
    return c;
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

}

Particle::Particle(const Grid& grid)
    : grid(grid), steps(generateSteps()), trace_len(TRACE_LEN), m_color(generateColor()),
    cur_step(0), angle_x(0), angle_y(0), angle_z(0)
{}

Particle::~Particle()
{}

bool Particle::operator==(const Particle& prt) const
{
    return ((trace[0].x == prt.trace[0].x)
            && (trace[0].y == prt.trace[0].y)
            && (trace[0].z == prt.trace[0].z)) ? true : false;
}

void Particle::setTrace()
{
    trace[0] = grid.generatePos();

    for(int i=1; i<trace_len; i++)
        trace[i] = trace[0];

    trace[0] = grid.selectDest(trace[0], trace[2]);

    head_pos = grid.getCoords(trace[1]);
    tail_pos = head_pos;
}

void Particle::setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z)
{
    angle_x = ang_x;
    angle_y = ang_y;
    angle_z = ang_z;
}

Vertex Particle::computePosition(const Junc& j1, const Junc& j2)
{
    Vertex pos = grid.getCoords(j2);
    const Vertex pos1 = grid.getCoords(j1);
    const Vertex pos2 = grid.getCoords(j2);
    Direction dir = getDirection(j1, j2);

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

    return pos;
}

void Particle::update()
{
    cur_step++;

    if (cur_step == steps) {
        for (int i=trace_len-1; i>0; --i)
            trace[i]= trace[i-1];

        trace[0] = grid.selectDest(trace[0], trace[2]);
        cur_step = 0;
    }

    head_pos = computePosition(trace[0], trace[1]);
    tail_pos = computePosition(trace[trace_len - 2], trace[trace_len - 1]);
}

void Particle::draw()
{
// рисование следа частицы
    glBegin(GL_LINE_STRIP);

    glColor4fv(&m_color.red);
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
// рисование самой частицы
    glPushMatrix();
    glTranslatef(head_pos.x, head_pos.y, head_pos.z);
    glRotatef(angle_x, 1.0, 0.0, 0.0);
    glRotatef(45.0 + angle_y, 0.0, 1.0, 0.0);
    glRotatef(angle_z, 0.0, 0.0, 1.0);

    glColor4fv(&m_color.red);
    glCallList(IL_PARTICLE);

    glPopMatrix();
}

