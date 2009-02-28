#if !defined(AFX_SNAKECLASS_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_SNAKECLASS_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Grid.h"
#include "Globals.h"
#include "SnakeUnit.h"

typedef std::vector<CSnakeUnit*> TUnits;

class CSnake
{	
private:
	TUnits			m_elems;		//	«вень€ змейки
	unsigned short	nSnakeLength;	//	ƒлина змейки - количество звеньев
	TGrCoords		nTarget;		//	—ледующа€ по направлению движени€ точка сетки
	snDirection		m_drct;			//	Ќаправление движени€ змейки
	CGrid			*pGrid;			//	”казатель на сетку, на которой движение
	GLuint			texSnakeBody;	//	Ўкура змейки
public:
	CSnake ();
	virtual ~CSnake ();

	void Init ( CGrid *pgrid );				//	инициализаци€ с прив€зкой к сетке
	void InitElems ();						//	инициализаци€ звеньев
	void AddElement ();						//	добавление нового звена
	void InitDraw ();						//	формирование списков изображений
											//	рисование
	void Draw (  unsigned short animStep, unsigned short steps );
	void ChangePos ();						//	изменение позиции (при достижении следующего узла сетки)
	void SetMoveStates ();					//	простановка состо€ний на все звень€
	void SetDirection ( snDirection drct );	//	задание направлени€ движени€ змейки
	snDirection GetDirection ();			//	возвращает направление движени€
	TGrCoords *GetTarget ();				//	возвращает следующий по напр. движени€ узел сетки
											//	проверкаа на столкновени€
	elCollis CheckPos ( TGrCoords *target, TGrCoords *appleCrds );
											//	возвращает положение на сетке звена змейки
	TGrCoords *GetPos ( unsigned short unit );
	unsigned short GetSnakeLength ();		//	возвращает число звеньев в змейке
};


#endif
