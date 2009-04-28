#include "StdAfx.h"
#include "SnakeClass.h"
#include "Textures.h"

CSnake::CSnake ()
{ 
}

CSnake::~CSnake ()
{
	for (int i=0; i<m_elems.size()-1; i++)
	{
		delete m_elems[i];
	}
}

void CSnake::InitDraw ()
{
	loadTexture ( "img/shark.bmp", &texSnakeBody );

	glNewList ( IL_SNAKEBODY, GL_COMPILE );

	glBegin ( GL_QUADS );
	glTexCoord2f	( 1.0, 1.0 );
	glVertex3f		( -CSnakeUnit::nWidth/2, -CSnakeUnit::nHeight/2, 0.0 );
	glTexCoord2f	( 0.0, 1.0 ); 
	glVertex3f		( -CSnakeUnit::nWidth/2, CSnakeUnit::nHeight/2, 0.0 );
	glTexCoord2f	( 0.0, 0.0 ); 
	glVertex3f		( CSnakeUnit::nWidth/2, CSnakeUnit::nHeight/2, 0.0 );
	glTexCoord2f	( 1.0, 0.0 ); 
	glVertex3f		( CSnakeUnit::nWidth/2, -CSnakeUnit::nHeight/2, 0.0 );
	glEnd ();

	glEndList ();
}

void CSnake::Init ( CGrid *pgrid )
{
	pGrid			= pgrid;
	nSnakeLength	= 6;
	m_drct			= sdRight;
	nTarget.X		= 6;
	nTarget.Y		= 3;
	InitElems ();
	InitDraw ();
}

void CSnake::Draw ( unsigned short animStep, unsigned short steps )
{
	glPushMatrix ();

	glColor4f ( 1.0, 1.0, 1.0, 0.0 );
	glBindTexture ( GL_TEXTURE_2D, texSnakeBody );
	glEnable ( GL_TEXTURE_2D );
//	glEnable ( GL_BLEND );

//	Пунктом назначения для каждого звена змеи являются координаты следующего узла грида
//	т.е. узла, который прошло предыдущее звено змеи
	m_elems[0]->Draw ( animStep, steps, nTarget );
	for (int i=1; i<m_elems.size()-1; i++)
	{
		TGrCoords grCoords;
		grCoords.X = m_elems[i-1]->nGrCrds.X;
		grCoords.Y = m_elems[i-1]->nGrCrds.Y;

		m_elems[i]->Draw ( animStep, steps, grCoords );
	}

//	glDisable ( GL_BLEND );
	glDisable ( GL_TEXTURE_2D );

	glPopMatrix ();
}

void CSnake::SetDirection ( snDirection drct )
{
	m_drct = drct;

	nTarget.X = m_elems[0]->nGrCrds.X;
	nTarget.Y = m_elems[0]->nGrCrds.Y;

	switch (m_drct)
	{
	case sdLeft:
		nTarget.X = m_elems[0]->nGrCrds.X - 1;
		break;
	case sdRight:
		nTarget.X = m_elems[0]->nGrCrds.X + 1;
		break;
	case sdUp:
		nTarget.Y =m_elems[0]->nGrCrds.Y + 1;
		break;
	case sdDown:
		nTarget.Y = m_elems[0]->nGrCrds.Y - 1;
		break;
	}
}

snDirection CSnake::GetDirection ()
{
	return m_drct;
}

void CSnake::SetMoveStates ()
{
	for (int i=1; i<m_elems.size()-1; i++ )
	{
		if ( m_elems[i-1]->nGrCrds.Y == m_elems[i+1]->nGrCrds.Y )
			if (m_elems[i-1]->nGrCrds.X > m_elems[i+1]->nGrCrds.X)
				m_elems[i]->nDrct = edRight;
			else
				m_elems[i]->nDrct = edLeft;
		if ( m_elems[i-1]->nGrCrds.X == m_elems[i+1]->nGrCrds.X )
			if (m_elems[i-1]->nGrCrds.Y > m_elems[i+1]->nGrCrds.Y)
				m_elems[i]->nDrct = edUp;
			else
				m_elems[i]->nDrct = edDown;

		if (( m_elems[i-1]->nGrCrds.X > m_elems[i+1]->nGrCrds.X ) &&
			( m_elems[i-1]->nGrCrds.Y > m_elems[i+1]->nGrCrds.Y ))
			m_elems[i]->nDrct = edLeftUp;
		if (( m_elems[i-1]->nGrCrds.X > m_elems[i+1]->nGrCrds.X ) &&
			( m_elems[i-1]->nGrCrds.Y < m_elems[i+1]->nGrCrds.Y ))
			m_elems[i]->nDrct = edLeftDn;
		if (( m_elems[i-1]->nGrCrds.X < m_elems[i+1]->nGrCrds.X ) &&
			( m_elems[i-1]->nGrCrds.Y > m_elems[i+1]->nGrCrds.Y ))
			m_elems[i]->nDrct = edRightUp;
		if (( m_elems[i-1]->nGrCrds.X < m_elems[i+1]->nGrCrds.X ) &&
			( m_elems[i-1]->nGrCrds.Y < m_elems[i+1]->nGrCrds.Y ))
			m_elems[i]->nDrct = edRightDn;
	}
}

void CSnake::ChangePos ()
{
	for (int i=m_elems.size()-1; i>0; i--)
	{
		m_elems[i]->nGrCrds.X = m_elems[i-1]->nGrCrds.X;
		m_elems[i]->nGrCrds.Y = m_elems[i-1]->nGrCrds.Y;
	}

	switch (m_drct)
	{
	case sdLeft:
		m_elems[0]->nDrct = edLeft;
		m_elems[0]->nGrCrds.X--;
		break;
	case sdRight:
		m_elems[0]->nDrct = edRight;
		m_elems[0]->nGrCrds.X++;
		break;
	case sdUp:
		m_elems[0]->nDrct = edUp;
		m_elems[0]->nGrCrds.Y++;
		break;
	case sdDown:
		m_elems[0]->nDrct = edDown;
		m_elems[0]->nGrCrds.Y--;
		break;
	}

	SetMoveStates ();

	for (int i=0;i<m_elems.size()-1; i++ )
	{
		if ((m_elems[i]->nGrCrds.X > pGrid->GetXLength() ) && (m_elems[0]->nDrct == edRight))
			m_elems[i]->nGrCrds.X = 0; 
		if ((m_elems[i]->nGrCrds.X < 0) && (m_elems[0]->nDrct == edLeft))
			m_elems[i]->nGrCrds.X = pGrid->GetXLength(); 
		if ((m_elems[i]->nGrCrds.Y > pGrid->GetYLength()) && (m_elems[0]->nDrct == edUp))
			m_elems[i]->nGrCrds.Y = 0; 
		if ((m_elems[i]->nGrCrds.Y < 0) && (m_elems[0]->nDrct == edDown))
			m_elems[i]->nGrCrds.Y = pGrid->GetXLength(); 
	}
}

//	Проверка
elCollis CSnake::CheckPos ( TGrCoords *target, TGrCoords *appleCrds )
{
	if ((target->X == appleCrds->X) && (target->Y == appleCrds->Y))
		return ecApple;

	for (int i=1; i< m_elems.size()-1; i++)
	{
		if ((target->X == m_elems[i]->nGrCrds.X) && (target->Y == m_elems[i]->nGrCrds.Y))
			return ecSelf;
	}

	return ecNone;
}

TGrCoords *CSnake::GetPos ( unsigned short unit )
{
	return &m_elems[unit]->nGrCrds;
}

void CSnake::InitElems ()
{
	while (!m_elems.empty ())
	{
		delete m_elems[m_elems.size()-1];
		m_elems.pop_back ();
	}

//	У всех звеньев зиейки одинаковая ширина и высота, а также они все на одной сетке
	CSnakeUnit::nWidth = pGrid->GetXStep ();
	CSnakeUnit::nHeight = pGrid->GetYStep ();
	CSnakeUnit::pGrid = pGrid;

	for (int i=0; i<nSnakeLength-1; i++)
	{
		CSnakeUnit *el = new CSnakeUnit;
		el->Init ( etBody, edRight, nSnakeLength-i-1, 3 );
		m_elems.push_back(el);
	}

	m_elems[0]->nType = etHead;
	m_elems[m_elems.size()-2]->nType = etTail;
	m_elems[m_elems.size()-1]->nType = etTail;
}

unsigned short CSnake::GetSnakeLength ()
{
	return nSnakeLength;
}

void CSnake::AddElement ()
{
// добавляется еще одтг элемент - хвост
	CSnakeUnit *el = new CSnakeUnit;
	el->Init ( etTail, edRight, m_elems[m_elems.size()-1]->nGrCrds.X, m_elems[m_elems.size()-1]->nGrCrds.Y );

	m_elems.push_back (el);
// бывший хвост становится туловом
	m_elems[m_elems.size()-3]->nType = etBody;

	nSnakeLength = m_elems.size();
}

TGrCoords *CSnake::GetTarget ()
{
	return &nTarget;
}

