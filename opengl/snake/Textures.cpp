
#include "bitmap.h"

// Load BMP textures
bool loadTexture(const char *filename, GLuint *texture)
{
    BITMAPINFO *info; /* Bitmap information */
    GLubyte* data = LoadDIBitmap(filename, &info);

    if(!data)
        return false;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  {Texture does NOT blend with object background}

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 
            info->bmiHeader.biHeight, 
            info->bmiHeader.biWidth, GL_RGB, GL_UNSIGNED_BYTE, data);
//  glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);  // Use when not wanting mipmaps to be built by openGL
    return true;
}

