#ifndef STEM_H
#define STEM_H

#include "mycompoundbody.h"


class MyCylinder;

class Stem : public MyCompoundBody
{
public:
    Stem(const PositionInfo& pos, real_t mass, real_t len, real_t raise);

    PositionInfo getLeftSetupLocalPosition()const;
    PositionInfo getRightSetupLocalPosition()const;
    PositionInfo getRightSetupWorldPosition()const;

    real_t len(){ return _len;}
    real_t raise(){ return _raise; }
    void moveTo(const PositionInfo& pos){ this->origin(pos); }

private:
    real_t _len;
    real_t _raise;
    MyCylinder* _stem=nullptr;
};

#endif // STEM_H
