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
	GLuint		texApple;			//	�������� ������
	TGrCoords	nGrCoords;			//	��������� ������ � ����������� �����
	CGrid		*pGrid;				//	��������� �� �����
	float		nWidth, nHeight;	//	������ � ������ ������

public:
	CApple ();
	virtual ~CApple ();

	void Init ( CGrid *pgrid );		//	������������� ������ (� ��������� � �����)
	void Draw ();					//	��������� ������

	TGrCoords *GetPos ();			//	���������� ���������� ������
	void SetCoords ();				//	������������� ������ (random)
};

#endif // AFX_APPLE_H
