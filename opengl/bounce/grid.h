#ifndef GRID_H
#define GRID_H

#include "bounce.h"

#define JUNCTIONS_X 31
#define JUNCTIONS_Y 9
#define JUNCTIONS_Z 31

class Grid
{
private:
    const unsigned short n_juncs_x, n_juncs_y, n_juncs_z;
    Vertex coords[JUNCTIONS_X][JUNCTIONS_Y][JUNCTIONS_Z];
public:
    Grid();
    ~Grid();

    Juncs getJuncs() const;
    Vertex getCoords(unsigned short i, unsigned short j, unsigned short k) const;
    Vertex getCoords(const Juncs& jnc) const;
    void draw();
    void init(float len_x, float len_y, float len_z);
    void setImageList(GLuint ilID);
};

#endif /* GRID_H */

