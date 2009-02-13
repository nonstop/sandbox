#ifndef BOUNCE_H
#define BOUNCE_H

#include <GL/gl.h>

#define IL_GRID			1
#define IL_PARTICLE		2
#define IL_BACKGROUND	3

// координаты узла сетки
struct Vertex { GLfloat x, y, z; };

// все узлы в относительных единицах
struct Junc { unsigned short x, y, z; };

struct Color { GLfloat red, green, blue; };


#endif /* BOUNCE_H */

