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
	TUnits			m_elems;		//	������ ������
	unsigned short	nSnakeLength;	//	����� ������ - ���������� �������
	TGrCoords		nTarget;		//	��������� �� ����������� �������� ����� �����
	snDirection		m_drct;			//	����������� �������� ������
	CGrid			*pGrid;			//	��������� �� �����, �� ������� ��������
	GLuint			texSnakeBody;	//	����� ������
public:
	CSnake ();
	virtual ~CSnake ();

	void Init ( CGrid *pgrid );				//	������������� � ��������� � �����
	void InitElems ();						//	������������� �������
	void AddElement ();						//	���������� ������ �����
	void InitDraw ();						//	������������ ������� �����������
											//	���������
	void Draw (  unsigned short animStep, unsigned short steps );
	void ChangePos ();						//	��������� ������� (��� ���������� ���������� ���� �����)
	void SetMoveStates ();					//	����������� ��������� �� ��� ������
	void SetDirection ( snDirection drct );	//	������� ����������� �������� ������
	snDirection GetDirection ();			//	���������� ����������� ��������
	TGrCoords *GetTarget ();				//	���������� ��������� �� ����. �������� ���� �����
											//	��������� �� ������������
	elCollis CheckPos ( TGrCoords *target, TGrCoords *appleCrds );
											//	���������� ��������� �� ����� ����� ������
	TGrCoords *GetPos ( unsigned short unit );
	unsigned short GetSnakeLength ();		//	���������� ����� ������� � ������
};


#endif
