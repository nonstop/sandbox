#include "StdAfx.h"
#include "Field.h"
#include "Textures.h"

CField::CField ()
{
}

CField::~CField ()
{
	if (glIsList (IL_BACKGROUND) == GL_TRUE)
		glDeleteLists ( IL_BACKGROUND, 1 );
}

void CField::Init ( TRect nRect )
{
	nFldRect = nRect;
	
	loadTexture ( "img/bgr1.bmp", &texBackground );

// Imagelist for background
	glNewList ( IL_BACKGROUND, GL_COMPILE );

	glColor4f ( 1.0, 1.0, 1.0, 0.0 );
	glBindTexture ( GL_TEXTURE_2D, texBackground );
	glEnable ( GL_TEXTURE_2D );

	glBegin ( GL_QUADS );
	glTexCoord2f	( 0.0, 0.0 ); 
	glVertex3f		( nFldRect.nLeft, nFldRect.nTop, 0.0 );
	glTexCoord2f	( 0.0, 1.0 ); 
	glVertex3f		( nFldRect.nLeft, nFldRect.nTop + nFldRect.nHeight, 0.0 );
	glTexCoord2f	( 1.0, 1.0 ); 
	glVertex3f		( nFldRect.nLeft + nFldRect.nWidth, nFldRect.nTop + nFldRect.nHeight, 0.0 );
	glTexCoord2f	( 1.0, 0.0 ); 
	glVertex3f		( nFldRect.nLeft + nFldRect.nWidth, nFldRect.nTop, 0.0 );
	glEnd ();

	glDisable ( GL_TEXTURE_2D );

	glEndList ();
}

TRect *CField::GetRect ()
{
	return &nFldRect;
}

void CField::Draw ()
{
	glCallList ( IL_BACKGROUND );
}
