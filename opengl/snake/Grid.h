#if !defined(AFX_GRID_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_GRID_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Globals.h"

class CGrid
{
private:
	TRect *pGrRect;				//	������ � ��������� ����� � ������� �����������
	unsigned short nX;			//	����� ����� �� ��� �
	unsigned short nY;			//	����� ����� �� ��� �
	float nXLen;				//	����� ���� �� ��� �
	float nYLen;				//	����� ���� �� ��� �
public:
	CGrid ();
	virtual ~CGrid ();

	void Init ( TRect *nRect, unsigned short kx, unsigned short ky );
	void Draw ();

	unsigned short GetXLength ();	//	��������� ����� ����� �� �
	unsigned short GetYLength ();	//	��������� ����� ���� �� �
	float GetXStep ();				//	��������� ����� ���� �� �
	float GetYStep ();				//	��������� ����� ���� �� �

									//	���������� ������� ���������� �� ����������� �����
	void GetCoords ( TCoords *pcrds, TGrCoords *pgrCrds );
};

#endif // AFX_GRID_H
