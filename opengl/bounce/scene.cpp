#include "stdafx.h"

#include "scene.h"

#include "textures.h"

TScene::TScene ()
{
	nParticles = 150;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
}

TScene::~TScene ()
{
	if (glIsList ( IL_GRID ) == GL_TRUE)
		glDeleteLists ( IL_GRID, 1 );
	if (glIsList ( IL_PARTICLE ) == GL_TRUE)
		glDeleteLists ( IL_PARTICLE, 1 );

	for (int i=0; i<particles.size(); i++)
		delete particles[i];
}

void TScene::init ()
{
	loadTexture ( "particle.bmp", &texParticle );
//	loadTexture ( "human_cursor.bmp", &texParticle );
//	loadTexture ( "orc_cursor.bmp", &texParticle );
	loadTexture ( "background.bmp", &texBackground );

	nGrid.init ( 40.0, 10.0, 40.0 );

	for (int i=0; i<nParticles; i++)
	{
		TParticle *ptcl = new TParticle ( &nGrid );

		do
		{
			ptcl->setTrace ();
		} while ( !checkParticlePos (i) );

		particles.push_back ( ptcl );
	}

// Imagelist for particle
	glNewList ( IL_PARTICLE, GL_COMPILE );
	
	glPushMatrix ();

//	glColor4f ( 0.5f, 0.5f, 0.5f, 1.0 );
//	glColor4f ( 0.5f, 0.5f, 0.0f, 1.0 );
	glBindTexture ( GL_TEXTURE_2D, texParticle );
	glEnable(GL_TEXTURE_2D);

	glEnable ( GL_BLEND );

//	glScalef ( 2.5, 2.5, 2.5 );
	glBegin ( GL_QUADS );
	glTexCoord2f ( 0.0, 0.0 );	glVertex3f ( -0.8f, -0.9f, 0 );
	glTexCoord2f ( 1.0, 0.0 );	glVertex3f ( +0.8f, -0.9f, 0 );
	glTexCoord2f ( 1.0, 1.0 );	glVertex3f ( +0.8f, +0.9f, 0 );
	glTexCoord2f ( 0.0, 1.0 );	glVertex3f ( -0.8f, +0.9f, 0 );
	glEnd ();

	glDisable ( GL_BLEND );
	glDisable ( GL_TEXTURE_2D );

	glEndList ();

// Imagelist for background
	glNewList ( IL_BACKGROUND, GL_COMPILE );

	glColor4f ( 1.0, 1.0, 1.0, 0.0 );
	glBindTexture ( GL_TEXTURE_2D, texBackground );
	glEnable ( GL_TEXTURE_2D );

	glPushMatrix ();

	glTranslatef ( -10, -5, -10 );

	glRotatef ( 45.0, 0.0, 1.0, 0.0 );
	glScalef ( 10.0, 10.0, 10.0 );

	glBegin(GL_QUADS);
	glTexCoord2f	( 0.0, 0.0 ); 
	glVertex3f		( -4.0, -4.9f, -1.0 );
	glTexCoord2f	( 1.0, 0.0 ); 
	glVertex3f		( 4.0, -4.9f, -1.0 );
	glTexCoord2f	( 1.0, 1.0 ); 
	glVertex3f		( 3.0, 1.9f, -1.0 );
	glTexCoord2f	( 0.0, 1.0 ); 
	glVertex3f		( -3.0, 1.9f, -1.0 );
	glEnd();

	glPopMatrix ();

	glDisable ( GL_TEXTURE_2D );

	glEndList ();
}

void TScene::update ()
{
	for (int i=0; i<nParticles; i++)
	{
		particles[i]->update ();
	}

	return;
}

void TScene::setAngles ( GLfloat ang_x, GLfloat ang_y, GLfloat ang_z )
{
	angle_x = ang_x;
	angle_y = ang_y;
	angle_z = ang_z;
}

void TScene::getAngles ( GLfloat *ang_x, GLfloat *ang_y, GLfloat *ang_z )
{
	*ang_x = angle_x;
	*ang_y = angle_y;
	*ang_z = angle_z;
}

void TScene::draw ()
{
	glCallList ( IL_BACKGROUND );

	glPushMatrix ();

	glRotatef ( angle_x, 1.0, 0.0, 0.0 );
	glRotatef ( angle_y, 0.0, 1.0, 0.0 );
	glRotatef ( angle_z, 0.0, 0.0, 1.0 );

	glTranslatef ( -17, -5, -17 );
//	nGrid.draw ();

	GLint width;
	glGetIntegerv( GL_LINE_WIDTH, &width);

	glLineWidth(2);	

	for (int i=0; i<nParticles; i++)
	{
		particles[i]->setAngles ( -angle_x, -angle_y, -angle_z );
		particles[i]->drawTail ();
		particles[i]->drawParticle ();
	}

	glLineWidth(width);

	glPopMatrix ();

}


bool TScene::checkParticlePos ( unsigned short n)
{
	for (int i=0; i<particles.size(); i++)
	{
		if ( (particles[n] == particles[i]) && (i!=n) )
			return false;
	}

	return true;
}
