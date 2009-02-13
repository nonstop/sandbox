#ifndef BOUNCE_H
#define BOUNCE_H

#include <vector>

// координаты узла сетки
struct Vertex { GLfloat x, y, z; };

// все узлы в относительных единицах
struct Junc { unsigned short x, y, z; };
typedef std::vector<Junc> Juncs;

struct Color { GLfloat red, green, blue; };


#endif /* BOUNCE_H */

