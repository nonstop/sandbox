#ifndef PARTICLE_H
#define PARTICLE_H

#include <list>

#include "bounce.h"
#include "grid.h"

#define TRACE_LEN 6

class Particle
{
public:
    Particle(const Grid& grid);
    ~Particle();

    void setTrace();
    void update();
    void drawTail();
    void drawParticle();

    void setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z);

    bool operator==(const Particle& prt)const
    {
        return((trace[0].x == prt.trace[0].x)&&(trace[0].y == prt.trace[0].y)&&(trace[0].z == prt.trace[0].z))? true : false;
    }
private:
    Vertex computePosition(const Junc& j1, const Junc& j2);

    const Grid& grid;
    const unsigned short steps;     // количество шагов, за которое частица достигает пункта назначения
    const unsigned short trace_len;
    const Color m_color;
    Vertex head_pos, tail_pos;
    Junc trace[TRACE_LEN];          // [1..TRACE_LEN-1] - траектория движения, 0 - пункт назначения
    unsigned short cur_step;        // на каком шаге в данный момент находится частица
    GLfloat angle_x, angle_y, angle_z;
};

typedef std::list<Particle> Particles;
typedef Particles::iterator ParticlesIt;
typedef Particles::const_iterator ParticlesConstIt;

#endif /* PARTICLE_H */

