#if !defined(AFX_SNAKEUNIT_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_SNAKEUNIT_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#include "Grid.h"
#include "Globals.h"

class CSnakeUnit
{
public:
	static CGrid	*pGrid;				//	�������� � �����
	elType			nType;				//	��� �����
	elMoveState		nDrct;				//	��������� �������� (��� ����� ���������)
	TGrCoords		nGrCrds;			//	��������� ����� � �����
	static float	nWidth, nHeight;	//	������ � ������ ����������� �����
public:
	CSnakeUnit ();
	virtual ~CSnakeUnit ();
										//	������������� ����� ������
	void Init ( elType type, elMoveState drct, unsigned short x, unsigned short y );
										//	��������� �����
	void Draw ( unsigned short animStep, unsigned short steps, TGrCoords target );
	void DrawHead ();
	void DrawBody ();
	void DrawTail ();
};

#endif	//	AFX_SNAKEUNIT_H