#if !defined(AFX_GLOBALS_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_GLOBALS_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ��� ������������ - ������, ���� � ����, �����
enum elCollis { ecNone, ecApple, ecSelf, ecBonus };
// ��� ����� - ������, ������, �����
enum elType { etHead, etTail, etBody };
// ��� ����������� ����� - ������, �����, �����, ����, ��������
enum elMoveState { edLeft, edRight, edUp, edDown, edLeftUp, edLeftDn, edRightUp, edRightDn };
// ��� ����������� �������� ������
enum snDirection { sdLeft, sdRight, sdUp, sdDown };

//	��������� � ������ ����
struct TRect
{
	short nLeft;
	short nTop;
	short nWidth;
	short nHeight;
};

//	���� �����
struct TGrCoords
{
	short X;
	short Y;
};

//	������� ���������� X, Y, Z
struct TCoords
{
	float X;
	float Y;
	float Z;
};

#endif // AFX_GLOBALS_H
