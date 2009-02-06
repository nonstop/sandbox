#ifndef BOUNCE_H
#define BOUNCE_H

struct TVertex		// для хранения координат узлов сетки
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct TJuncs		// для хранения указателей на узлы сетки
{
    unsigned short x;
    unsigned short y;
    unsigned short z;
};

#endif /* BOUNCE_H */

