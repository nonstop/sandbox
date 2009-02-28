#pragma once
#include "Sphere.h"

class CMinute	:	
	public CSphere
{
public:
	CMinute(void);
	virtual ~CMinute(void);

	void Init();
	void Draw();
	void SetPosition(GLfloat *position);
	void SetColor(GLfloat *color);
	void SetAngles(GLfloat angleX, GLfloat angleY, GLfloat angleZ);
	GLfloat *GetAngles();
};
