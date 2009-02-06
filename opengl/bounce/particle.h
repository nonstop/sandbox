#ifndef PARTICLE_H
#define PARTICLE_H

#include "bounce.h"
#include "grid.h"

#define TRACE_LEN 6

enum TDirection { dIncX, dDecX, dIncY, dDecY, dIncZ, dDecZ };

#define MAX_PARTICLE_STEPS 30.0

class TParticle
{
private:
	TGrid *nGrid;

	TVertex head_pos, tail_pos;					
	TJuncs trace[TRACE_LEN];		// [1..TRACE_LEN-1] - ���������� ��������, 0 - ����� ����������
	unsigned short steps;			// ���������� �����, �� ������� ������� ��������� ������ ����������
	unsigned short cur_step;		// �� ����� ���� � ������ ������ ��������� �������
	unsigned short trace_len;
	TDirection direction;
	GLfloat angle_x, angle_y, angle_z;

	GLfloat red, green, blue;

public:
	TParticle ( TGrid *grid );
	~TParticle ();

	TJuncs selectDest ();

	void drawTail ();
	void drawParticle ();
	void setTrace ();
	void update ();
	TJuncs *getTrace ();
	unsigned short getTraceLen ();
	TVertex getHeadPos ();
	TVertex getTailPos ();

	void getDirection ( TDirection *dir, TJuncs *jnc1, TJuncs *jnc2 );		// ���������� ����������� �� ���� ������ (���� 0,1 ��� last-1, last)

	void setAngles ( GLfloat ang_x, GLfloat ang_y, GLfloat ang_z );

	bool operator== (TParticle prt) const
	{
		return ((trace[0].x == prt.trace[0].x) && (trace[0].y == prt.trace[0].y) && (trace[0].z == prt.trace[0].z)) ? true : false;
	}
};

#endif /* PARTICLE_H */

