#ifndef SCENE_H
#define SCENE_H

#include "grid.h"
#include "particle.h"

#include <vector>

using namespace std;

class TScene
{
private:
	TGrid nGrid;
	vector<TParticle*> particles;
	GLfloat angle_x, angle_y, angle_z;

	GLuint texParticle, texBackground;

	unsigned short nParticles;
public:
	TScene ();
	~TScene ();

	void draw ();
	void init ();

	bool checkParticlePos ( unsigned short n);		// prevent from starting with the same coords, true - good position

	void print ();
	void update ();
	void setAngles ( GLfloat ang_x, GLfloat ang_y, GLfloat ang_z );
	void getAngles ( GLfloat *ang_x, GLfloat *ang_y, GLfloat *ang_z );
};

#endif /* SCENE_H */

