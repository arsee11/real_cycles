#ifndef FORKUPPER_H
#define FORKUPPER_H

#include "mycompoundbody.h"

class MyCylinder;
class MyBox;

class ForkUpper : public MyCompoundBody
{
public:
    ForkUpper(real_t mass, real_t travel, real_t width, real_t steer_len);

    ///@return lenght of this
    real_t getLen(){ return _y; }

    PositionInfo getCrownOrigin();

private:
    MyCylinder* _left_tube=nullptr, *_right_tube=nullptr;
    MyBox* _crown=nullptr;
    MyCylinder* _streer=nullptr;

    real_t _x, _z, _y;

};

#endif // FORKUPPER_H
