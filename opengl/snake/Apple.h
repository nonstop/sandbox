#if !defined(AFX_APPLE_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_APPLE_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Grid.h"
#include "Globals.h"

class CApple
{
private:
	GLuint		texApple;			//	“екстура €блока
	TGrCoords	nGrCoords;			//	ѕоложение €блока в координатах сетки
	CGrid		*pGrid;				//	”казатель на сетку
	float		nWidth, nHeight;	//	Ўирина и высота €блока

public:
	CApple ();
	virtual ~CApple ();

	void Init ( CGrid *pgrid );		//	»нициализаци€ €блока (с прив€зкой к сетке)
	void Draw ();					//	–исование €блока

	TGrCoords *GetPos ();			//	¬озвращает координаты €блока
	void SetCoords ();				//	”станавливает €блоко (random)
};

#endif // AFX_APPLE_H
