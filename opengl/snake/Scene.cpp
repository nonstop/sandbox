#include "StdAfx.h"
#include "Scene.h"

CScene::CScene ()
{
}	

CScene::~CScene ()
{
}

void CScene::Init ()
{
	nAnimSteps		= 20;
	nCurStep		= 0;

	TRect nRect;
	nRect.nLeft		= -10;
	nRect.nTop		= -10;
	nRect.nWidth	= 20;
	nRect.nHeight	= 20;

	nField.Init ( nRect );
	nGrid.Init ( nField.GetRect (), 8, 8 );
	nApple.Init ( &nGrid );
	nDrct = sdRight;
	nSnake.Init ( &nGrid );
}

void CScene::Draw (  )
{
	glPushMatrix ();

	nField.Draw ();
	nGrid.Draw ();
	nApple.Draw ();
	nSnake.Draw ( nCurStep, nAnimSteps  );

	glPopMatrix ();
}

void CScene::Timer ()
{
	if (nCurStep < nAnimSteps)
	{
		nCurStep++;
	}
	else
	{
		nCurStep = 0;
		nSnake.ChangePos ();
		nSnake.SetDirection ( nDrct );
		if (nSnake.CheckPos ( nSnake.GetTarget (), nApple.GetPos () ) == ecApple)
		{
			nSnake.AddElement ();
			do
			{
				nApple.SetCoords ();
			}while ( !CheckApplePos () );
		}
//		if (nSnake.CheckPos ( nSnake.GetTarget (), nApple.GetCoords () ) == ecSelf)
//			std::cout << "Own tail eaten" << std::endl;
	}
}

bool CScene::CheckApplePos ()
{
	for (unsigned short i=0; i<nSnake.GetSnakeLength()-1; i++)
	{
		TGrCoords *pUCrds = nSnake.GetPos (i);		//	Координаты звена
		TGrCoords *pACrds = nApple.GetPos ();		//	Координаты яблока

		if ( (pUCrds->X == pACrds->X)&&
			(pUCrds->Y == pACrds->Y) )
			return false;
	}

	return true;
}

void CScene::SetSnakeDirection ( snDirection drct )
{
	if (drct != nSnake.GetDirection () )
	{
		if ((nSnake.GetDirection () == sdLeft) && (drct == sdRight))
			return;
		if ((nSnake.GetDirection () == sdRight) && (drct == sdLeft))
			return;
		if ((nSnake.GetDirection () == sdUp) && (drct == sdDown))
			return;
		if ((nSnake.GetDirection () == sdDown) && (drct == sdUp))
			return;

		nDrct = drct;
	}
}

