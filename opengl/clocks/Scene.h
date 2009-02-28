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
	GLuint			mCurve;			//	выступающая сфера
	GLfloat			mRadiusZ;		//	радиус выгиба
public:
	CScene(void);
	virtual ~CScene(void);

	void Init();					//	инициализация сцены
	void Update();					//	изменение сцены
	void Draw();					//	рисование сцены
	void SetHour(GLuint hour);		//	установить выделение часа
	void SetMinute(GLuint minute);	//	установить выделение минуты
	void SetSecond(GLuint second);	//	установить выделение секунды
	void SetRadius(GLfloat radius);	//	установить радиус
	void SetCurve(GLuint curve);	//	установить выгиб
};
