#ifndef BOUNCE_H
#define BOUNCE_H

struct Vertex        // для хранения координат узлов сетки
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Juncs        // для хранения указателей на узлы сетки
{
    unsigned short x;
    unsigned short y;
    unsigned short z;
};

#endif /* BOUNCE_H */

