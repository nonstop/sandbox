#ifndef GIEL_BASIC_UNIT_H
#define GIEL_BASIC_UNIT_H

enum BasicUnitRotation {BUR_NONE, BUR_RIGHT, BUR_LEFT};

typedef struct BasicUnit
{
    int isOdd;
    int isCurrent;
    enum BasicUnitRotation rot;
    struct BasicUnit* next;
} BasicUnit;

void basic_unit_init_imagelist();

void appendBasicUnits(struct BasicUnit* tail, int count);
void freeBasicUnits(struct BasicUnit* units);
void drawBasicUnits(struct BasicUnit* units);



#endif /* GIEL_BASIC_UNIT_H */

