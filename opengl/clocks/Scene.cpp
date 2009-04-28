#include <math.h>

#include "stdafx.h"
#include "Scene.h"

const double pi = 3.14;

CScene::CScene(void)
{
	mRadius = 0.0;
	mRadiusZ = 1.0;
	mCurve	= 0.0;

	mAngleX = 0.0;
	mAngleY = 0.0;
	mAngleZ = 0.0;

	mQO = 0;
}

CScene::~CScene(void)
{
	gluDeleteQuadric(mQO);
}

void CScene::Init()
{ 
	mQO = gluNewQuadric();

//	изображение минут
	glNewList ( IL_MINUTE, GL_COMPILE );	
	glPushMatrix ();
	glColor3f(0.0, 1.0, 0.0);
	gluSphere(mQO, 0.4, 12, 12);
	glEndList ();

//	поворот изображений минут
	for (int i=0; i<30; i++)
	{
		GLfloat angle = -360*float(i)/30.0;
		mMinute[i].SetAngles(0, 0, angle);
	}

//	изображение секунд
	return;
}

void CScene::Draw()
{
	for (int i=0; i<30; i++)
	{
		GLfloat position[3];
		position[0] = mRadius*cos(2*pi*(30-i)/30 + pi/2);
		position[1] = mRadius*sin(2*pi*(30-i)/30 + pi/2);

		GLuint cur = ((i+mCurve) < 30) ? i+mCurve : i+mCurve-30;
		position[2] = mRadiusZ*cos(pi*cur/15);

		GLfloat color[3];
		if (i == mCurMinute)
		{
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 0.0;
		}
		else
		{
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
		}

		mMinute[i].SetPosition(&position[0]);
		mMinute[i].SetColor(&color[0]);
		mMinute[i].Draw();
	}

	return;
}

void CScene::Update()
{
//	mAngleX = (mAngleX>=360) ? 0 : (++mAngleX);
//	mAngleY = (mAngleY>=360) ? 0 : (++mAngleY);
	mAngleZ = (mAngleZ>=360) ? 0 : (++mAngleZ);
	
	for (int i=0; i<30; i++)
		mMinute[i].SetAngles(mAngleX, mAngleY, mAngleZ);

	return;
}

void CScene::SetHour(GLuint hour)
{
	mCurHour = hour;
	return;
}

void CScene::SetMinute(GLuint minute)
{
	mCurMinute = minute;
	return;
}

void CScene::SetSecond(GLuint second)
{
	mCurSecond = second;
	return;
}

void CScene::SetRadius(GLfloat radius)
{
	mRadius = radius;
	return;
}

void CScene::SetCurve(GLuint curve)
{
	mCurve = curve;
	return;
}
