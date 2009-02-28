#if !defined(AFX_GLOBALS_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_)
#define AFX_GLOBALS_H__BA57674A_D467_415E_9B86_9232E1C5467F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// тип столкновения - яблоко, сама в себя, бонус
enum elCollis { ecNone, ecApple, ecSelf, ecBonus };
// тип звена - голова, тулово, хвост
enum elType { etHead, etTail, etBody };
// тип направления звена - вперед, назад, вверх, вниз, повороты
enum elMoveState { edLeft, edRight, edUp, edDown, edLeftUp, edLeftDn, edRightUp, edRightDn };
// тип направления движения змейки
enum snDirection { sdLeft, sdRight, sdUp, sdDown };

//	положение и размер поля
struct TRect
{
	short nLeft;
	short nTop;
	short nWidth;
	short nHeight;
};

//	узлы сетки
struct TGrCoords
{
	short X;
	short Y;
};

//	мировые координаты X, Y, Z
struct TCoords
{
	float X;
	float Y;
	float Z;
};

#endif // AFX_GLOBALS_H
