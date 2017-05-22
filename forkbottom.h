#ifndef FORKBOTTOM_H
#define FORKBOTTOM_H

#include "mycompoundbody.h"

class MyCylinder;
class MyBox;

class ForkBottom : public MyCompoundBody
{
public:
    ForkBottom(real_t mass, real_t len, real_t axis);

    real_t getLen(){ return _y;}

private:
    MyCylinder* _left_leg=nullptr, *_right_leg=nullptr;
    MyBox* _legs_linker=nullptr;

    real_t _x, _z, _y;
};

#endif // FORKBOTTOM_H
