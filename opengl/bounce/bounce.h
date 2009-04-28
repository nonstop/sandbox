#ifndef BOUNCE_H
#define BOUNCE_H

#include <GL/gl.h>

enum BounceImageLists {
    IL_GRID = 1,
    IL_PARTICLE,
    IL_BACKGROUND};

// координаты узла сетки
struct Vertex { GLfloat x, y, z; };

// все узлы в относительных единицах
struct Junc { unsigned short x, y, z; };

struct Color { GLfloat red, green, blue, alpha; };


#endif /* BOUNCE_H */

