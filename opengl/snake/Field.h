#if !defined(AFX_FIELD_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_FIELD_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Globals.h"

class CField
{
private:
	GLuint texBackground;		//	Текстура поля
	TRect nFldRect;				//	Размер и положение поля в мировых координатах

public:
	CField ();
	virtual ~CField ();

	void Init ( TRect nRect );	//	Инициализация поля (с заданием его положения и размера)
	void Draw ();				//	Рисование поля

	TRect *GetRect ();			//	Возвращает размер и положение поля
};

#endif // AFX_FIELD_H
