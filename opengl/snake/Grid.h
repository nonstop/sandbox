#if !defined(AFX_GRID_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_GRID_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Globals.h"

class CGrid
{
private:
	TRect *pGrRect;				//	Размер и положение грида в оконных координатах
	unsigned short nX;			//	Число узлов по оси Х
	unsigned short nY;			//	Число узлов по оси У
	float nXLen;				//	Длина шага по оси Х
	float nYLen;				//	Длина шага по оси Х
public:
	CGrid ();
	virtual ~CGrid ();

	void Init ( TRect *nRect, unsigned short kx, unsigned short ky );
	void Draw ();

	unsigned short GetXLength ();	//	Получение числа узлов по Х
	unsigned short GetYLength ();	//	Получение числа узла по У
	float GetXStep ();				//	Получение длины шага по Х
	float GetYStep ();				//	Получение длины шага по У

									//	Возвращает мировые координаты по координатам сетки
	void GetCoords ( TCoords *pcrds, TGrCoords *pgrCrds );
};

#endif // AFX_GRID_H
