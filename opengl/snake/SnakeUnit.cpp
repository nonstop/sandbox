#include "StdAfx.h"
#include "SnakeUnit.h"

CGrid *CSnakeUnit::pGrid = 0;
float CSnakeUnit::nWidth = 0;
float CSnakeUnit::nHeight = 0;

CSnakeUnit::CSnakeUnit ()
{
}

CSnakeUnit::~CSnakeUnit ()
{
}

void CSnakeUnit::Init ( elType type, elMoveState drct, unsigned short x, unsigned short y )
{
	nType		= type;
	nDrct		= drct;
	nGrCrds.X	= x;
	nGrCrds.Y	= y;
}

void CSnakeUnit::Draw ( unsigned short animStep, unsigned short steps, TGrCoords target )
{
	glPushMatrix ();
	
	TCoords crCurrent, crFinish;
	TGrCoords grCrds;
	grCrds.X = nGrCrds.X;
	grCrds.Y = nGrCrds.Y;
//	ѕолучаем координаты последнего пройденного узла
	pGrid->GetCoords ( &crCurrent, &grCrds );
//	ѕолучаем конечного узла
	pGrid->GetCoords ( &crFinish, &target );
//	ѕреобразовываем текущие координаты в соответствии с номером кадра
	crCurrent.X = crCurrent.X + (animStep*(crFinish.X - crCurrent.X)/steps);
	crCurrent.Y = crCurrent.Y + (animStep*(crFinish.Y - crCurrent.Y)/steps);

	glTranslatef ( crCurrent.X, crCurrent.Y, crCurrent.Z );

	glCallList ( IL_SNAKEBODY );

	glPopMatrix ();
}

void CSnakeUnit::DrawHead ( )
{
	glPushMatrix ();


	switch (nDrct)
	{
	case(edUp):
//		glCallList (SnakeHeadUp);
		break;
	case(edDown):
//		glCallList (SnakeHeadDown);
		break;
	case(edRight):
//		glCallList (SnakeHeadRight);
		break;
	case(edLeft):
//		glCallList (SnakeHeadLeft);
		break;
	}
	glPopMatrix ();
}

void CSnakeUnit::DrawBody ( )
{
	glPushMatrix ();
	switch (nDrct)
	{
	case(edUp):
//		glCallList (SnakeBodyUp);
		break;
	case(edDown):
//		glCallList (SnakeBodyDown);
		break;
	case(edRight):
//		glCallList (SnakeBodyRight);
		break;
	case(edLeft):
//		glCallList (SnakeBodyLeft);
		break;
	case(edLeftUp):
//		glCallList (SnakeBodyLeftUp);
		break;
	case(edLeftDn):
//		glCallList (SnakeBodyLeftDown);
		break;
	case(edRightUp):
//		glCallList (SnakeBodyRightUp);
		break;
	case(edRightDn):
//		glCallList (SnakeBodyRightDown);
		break;
	}
	glPopMatrix ();
}

void CSnakeUnit::DrawTail ( )
{
	glPushMatrix ();
	switch (nDrct)
	{
	case(edUp):
//		glCallList (SnakeTailUp);
		break;
	case(edLeftUp):
//		glCallList (SnakeTailUp);
		break;
	case(edRightUp):
//		glCallList (SnakeTailUp);
		break;
	case(edDown):
//		glCallList (SnakeTailDown);
		break;
	case(edLeftDn):
//		glCallList (SnakeTailDown);
		break;
	case(edRightDn):
//		glCallList (SnakeTailDown);
		break;
	case(edRight):
//		glCallList (SnakeTailRight);
		break;
	case(edLeft):
//		glCallList (SnakeTailLeft);
		break;
	}
	glPopMatrix ();

}

