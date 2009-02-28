#if !defined(AFX_SNAKEUNIT_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_SNAKEUNIT_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#include "Grid.h"
#include "Globals.h"

class CSnakeUnit
{
public:
	static CGrid	*pGrid;				//	Привязка к сетке
	elType			nType;				//	Тип звена
	elMoveState		nDrct;				//	Состояние движения (для учета поворотов)
	TGrCoords		nGrCrds;			//	Положение звена в гриде
	static float	nWidth, nHeight;	//	Ширина и высота изображения звена
public:
	CSnakeUnit ();
	virtual ~CSnakeUnit ();
										//	Инициализация звена змейки
	void Init ( elType type, elMoveState drct, unsigned short x, unsigned short y );
										//	Рисование звена
	void Draw ( unsigned short animStep, unsigned short steps, TGrCoords target );
	void DrawHead ();
	void DrawBody ();
	void DrawTail ();
};

#endif	//	AFX_SNAKEUNIT_H