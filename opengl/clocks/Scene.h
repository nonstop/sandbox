#pragma once
#include "Minute.h"

class CScene
{
private:
	CMinute			mMinute[60];
	GLuint			mHourTexture, mMinuteTexture;
	GLUquadricObj	*mQO;
	GLfloat			mAngleX, mAngleY, mAngleZ;
	GLuint			mCurHour, mCurMinute, mCurSecond;
	GLfloat			mRadius;
	GLuint			mCurve;			//	����������� �����
	GLfloat			mRadiusZ;		//	������ ������
public:
	CScene(void);
	virtual ~CScene(void);

	void Init();					//	������������� �����
	void Update();					//	��������� �����
	void Draw();					//	��������� �����
	void SetHour(GLuint hour);		//	���������� ��������� ����
	void SetMinute(GLuint minute);	//	���������� ��������� ������
	void SetSecond(GLuint second);	//	���������� ��������� �������
	void SetRadius(GLfloat radius);	//	���������� ������
	void SetCurve(GLuint curve);	//	���������� �����
};
