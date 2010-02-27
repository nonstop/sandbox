#ifndef GIEL_BASIC_UNIT_H
#define GIEL_BASIC_UNIT_H

enum BasicUnitRotation {BUR_NONE, BUR_LEFT, BUR_DOWN, BUR_RIGHT};

typedef struct BasicUnit
{
    int isOdd;
    int isCurrent;
    enum BasicUnitRotation rot;
    struct BasicUnit* prev;
    struct BasicUnit* next;
} BasicUnit;

void basic_unit_init_imagelist();

void appendBasicUnits(BasicUnit* tail, int count);
void freeBasicUnits(BasicUnit* units);
void drawBasicUnits(BasicUnit* units);

void base_unit_turn_left(BasicUnit* unit);
void base_unit_turn_right(BasicUnit* unit);


#endif /* GIEL_BASIC_UNIT_H */

