#ifndef GIEL_H
#define GIEL_H

typedef struct Globals__
{
    struct BasicUnit* head;
    struct BasicUnit* currentUnit;
    int width, height;
    int rotateX, rotateY, rotateZ;
} Globals;

#endif /* GIEL_H */

