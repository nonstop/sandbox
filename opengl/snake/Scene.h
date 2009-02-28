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
	CField		nField;			//	���� ��� ����
	CGrid		nGrid;			//	���� � ������� ������ � ���� ������������
	CApple		nApple;			//	������
	CSnake		nSnake;			//	����
	snDirection nDrct;			//	����������� �������� ����

	unsigned short nAnimSteps;	//	����� ������
	unsigned short nCurStep;	//	����� �������� �����

public:
	CScene ();
	virtual ~CScene ();

	void Init ();				//	������������� �����
	void Draw ();				//	��������� �����
	void Timer ();				//	��������� ��������� (�������� ��������)
								//	������� ����������� �������� ������
	void SetSnakeDirection ( snDirection drct );
	bool CheckApplePos ();		//	�������� ��������� ������ (����� ��� �� ��������� �� ������) true - ��� ��
};

#endif // AFX_SCENE_H
