#include "StdAfx.h"
#include "Grid.h"

CGrid::CGrid ()
{
}

CGrid::~CGrid ()
{
}

void CGrid::Init ( TRect *pRect, unsigned short kx, unsigned short ky )
{
	pGrRect = pRect;
	nX = kx;
	nY = ky;

	nXLen = float(pGrRect->nWidth)/nX;
	nYLen = float(pGrRect->nHeight)/nY;
}

unsigned short CGrid::GetXLength ()
{
	return nX;
}

unsigned short CGrid::GetYLength ()
{
	return nY;
}

float CGrid::GetXStep ()
{
	return nXLen;
}

float CGrid::GetYStep ()
{
	return nYLen;
}

void CGrid::GetCoords ( TCoords *pcrds, TGrCoords *pgrCrds )
{
	pcrds->X = pGrRect->nLeft + (pgrCrds->X)*nXLen;
	pcrds->Y = pGrRect->nTop + (pgrCrds->Y)*nYLen;
	pcrds->Z = 0.01;
}

void CGrid::Draw ()
{
	glColor3f ( 0.0, 1.0, 0.0 );

	glPushMatrix ();

	glBegin ( GL_LINES );
//	Вертикальные линии
	for (int i=0; i<=nX; i++)
	{
		glVertex3f ( pGrRect->nLeft + nXLen*i, pGrRect->nTop, 0.01 );
		glVertex3f ( pGrRect->nLeft + nXLen*i, pGrRect->nTop + pGrRect->nHeight, 0.01 );
	}
//	Горизонтальные линии
	for (int i=0; i<=nY; i++)
	{
		glVertex3f ( pGrRect->nLeft, pGrRect->nTop + nYLen*i, 0.01 );
		glVertex3f ( pGrRect->nLeft + pGrRect->nWidth, pGrRect->nTop + nYLen*i, 0.01 );
	}
	glEnd ();

	glPopMatrix ();
}
