#ifndef PARTICLE_H
#define PARTICLE_H

#include <list>

#include "bounce.h"
#include "grid.h"

#define TRACE_LEN 6

enum Direction { dIncX, dDecX, dIncY, dDecY, dIncZ, dDecZ };

#define MAX_PARTICLE_STEPS 30.0

class Particle
{
private:
    const Grid& grid;

    Vertex head_pos, tail_pos;                    
    Juncs trace[TRACE_LEN];        // [1..TRACE_LEN-1] - траектория движения, 0 - пункт назначения
    unsigned short steps;            // количество шагов, за которое частица достигает пункта назначения
    unsigned short cur_step;        // на каком шаге в данный момент находится частица
    const unsigned short trace_len;
    Direction direction;
    GLfloat angle_x, angle_y, angle_z;

    GLfloat red, green, blue;

public:
    Particle(const Grid& grid);
    ~Particle();

    Juncs selectDest();

    void drawTail();
    void drawParticle();
    void setTrace();
    void update();
    Juncs *getTrace();
    unsigned short getTraceLen();
    Vertex getHeadPos();
    Vertex getTailPos();

    // возвращает направление по двум точкам(типа 0,1 или last-1, last)
    void getDirection(Direction& dir, const Juncs& jnc1, const Juncs& jnc2);

    void setAngles(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z);

    bool operator==(const Particle& prt)const
    {
        return((trace[0].x == prt.trace[0].x)&&(trace[0].y == prt.trace[0].y)&&(trace[0].z == prt.trace[0].z))? true : false;
    }
};

typedef std::list<Particle> Particles;
typedef Particles::iterator ParticlesIt;
typedef Particles::const_iterator ParticlesConstIt;

#endif /* PARTICLE_H */

