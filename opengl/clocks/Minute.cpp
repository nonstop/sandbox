#include "stdafx.h"
#include "Minute.h"

CMinute::CMinute(void)
{
}

CMinute::~CMinute(void)
{
}

void CMinute::Init()
{
}

void CMinute::Draw()
{
	glPushMatrix();
	glTranslatef(mProperties.fPosition[0], mProperties.fPosition[1], mProperties.fPosition[2]);
//	glRotatef(mProperties.fAngles[0], 1.0, 0.0, 0.0);
//	glRotatef(mProperties.fAngles[1], 0.0, 1.0, 0.0);
	glRotatef(mProperties.fAngles[2], 0.0, 0.0, 1.0);
	glColor3fv(&(mProperties.fColor[0]));
	glCallList(IL_MINUTE);
	glPopMatrix();
}

void CMinute::SetPosition(GLfloat *position)
{
	mProperties.fPosition[0] = position[0];
	mProperties.fPosition[1] = position[1];
	mProperties.fPosition[2] = position[2];
}

void CMinute::SetColor(GLfloat *color)
{
	mProperties.fColor[0] = color[0];
	mProperties.fColor[1] = color[1];
	mProperties.fColor[2] = color[2];

	return;
}

void CMinute::SetAngles(GLfloat angleX, GLfloat angleY, GLfloat angleZ)
{
	mProperties.fAngles[0] = angleX;
	mProperties.fAngles[1] = angleY;
	mProperties.fAngles[2] = angleZ;
}

GLfloat *CMinute::GetAngles()
{
	return &mProperties.fAngles[0];
}
