#ifndef STEM_H
#define STEM_H

#include "mycylinder.h"

class Stem : public MyCylinder
{
public:
    Stem(const PositionInfo& origin, real_t mass, real_t len, real_t up_sweep);
};

#endif // STEM_H
