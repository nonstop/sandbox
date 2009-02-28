#include <stdlib.h>
#include <ctime>
#include "StdAfx.h"
#include "Apple.h"
#include "Textures.h"

CApple::CApple ()
{
}

CApple::~CApple ()
{
	if (glIsList ( IL_APPLE ) == GL_TRUE)
		glDeleteLists ( IL_APPLE, 1 );
}

void CApple::Init ( CGrid *pgrid )
{
	pGrid = pgrid;

	nWidth	= pGrid->GetXStep ();
	nHeight = pGrid->GetYStep ();

	srand ( time (NULL) );

	SetCoords ();

	loadTexture ( "img/apple.bmp", &texApple );

// Imagelist for background
	glNewList ( IL_APPLE, GL_COMPILE );

	glColor4f ( 1.0, 1.0, 1.0, 0.0 );
	glBindTexture ( GL_TEXTURE_2D, texApple );
	glEnable ( GL_TEXTURE_2D );
//	glEnable ( GL_BLEND );

	glBegin ( GL_QUADS );
	glTexCoord2f	( 0.0, 0.0 ); 
	glVertex3f		( -nWidth/2, -nHeight/2, 0.0 );
	glTexCoord2f	( 0.0, 1.0 ); 
	glVertex3f		( -nWidth/2, nHeight/2, 0.0 );
	glTexCoord2f	( 1.0, 1.0 ); 
	glVertex3f		( nWidth/2, nHeight/2, 0.0 );
	glTexCoord2f	( 1.0, 0.0 ); 
	glVertex3f		( nWidth/2, -nHeight/2, 0.0 );
	glEnd ();

//	glDisable ( GL_BLEND );
	glDisable ( GL_TEXTURE_2D );

	glEndList ();
}

void CApple::Draw ()
{
	glPushMatrix ();

	TCoords crds;
	pGrid->GetCoords ( &crds, &nGrCoords );

	glTranslatef ( crds.X, crds.Y, crds.Z );

	glCallList ( IL_APPLE );

	glPopMatrix ();
}

TGrCoords *CApple::GetPos ()
{
	return &nGrCoords;
}

void CApple::SetCoords ()
{
	nGrCoords.X = rand () % (pGrid->GetXLength () - 2) + 1;
	nGrCoords.Y = rand () % (pGrid->GetYLength () - 2) + 1;
}
