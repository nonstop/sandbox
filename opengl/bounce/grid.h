#ifndef GRID_H
#define GRID_H

#include "bounce.h"

#define JUNCTIONS_X 31
#define JUNCTIONS_Y 9
#define JUNCTIONS_Z 31

class TGrid
{
private:
	unsigned short n_juncs_x, n_juncs_y, n_juncs_z;
	TVertex coords[JUNCTIONS_X][JUNCTIONS_Y][JUNCTIONS_Z];
public:
	TGrid ();
	~TGrid ();

	TJuncs getJuncs ();
	TVertex getCoords ( unsigned short i, unsigned short j, unsigned short k );
	TVertex getCoords ( TJuncs *jnc );
	void draw ();
	void init ( float len_x, float len_y, float len_z );
	void setImageList ( GLuint ilID );
};

#endif /* GRID_H */

