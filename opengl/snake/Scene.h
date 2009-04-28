#if !defined(AFX_SCENE_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_SCENE_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Globals.h"
#include "Field.h"
#include "Grid.h"
#include "Apple.h"
#include "SnakeClass.h"

class CScene
{
private:
	CField		nField;			//	Поле для змеи
	CGrid		nGrid;			//	Узлы в которых яблоки и змея поворачивает
	CApple		nApple;			//	Яблоки
	CSnake		nSnake;			//	Змея
	snDirection nDrct;			//	Направление движения змеи

	unsigned short nAnimSteps;	//	Число кадров
	unsigned short nCurStep;	//	Номер текущего кадра

public:
	CScene ();
	virtual ~CScene ();

	void Init ();				//	инициализация сцены
	void Draw ();				//	рисование сцены
	void Timer ();				//	изменения состояния (анимация движения)
								//	задание направления движения змейки
	void SetSnakeDirection ( snDirection drct );
	bool CheckApplePos ();		//	Проверка положения яблока (чтобы оно не появилось на змейке) true - все ок
};

#endif // AFX_SCENE_H
