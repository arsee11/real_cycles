#ifndef FORKBOTTOM_H
#define FORKBOTTOM_H

#include "mycompoundbody.h"

class MyCylinder;
class MyBox;

class ForkBottom : public MyCompoundBody
{
public:
    ForkBottom(real_t mass, real_t len, real_t axis);

    ///return len width height of effective cube
    std::tuple<real_t, real_t, real_t> getLWH(){ return std::make_tuple(_len, _width, _height); }

private:
    MyCylinder* _left_leg=nullptr, *_right_leg=nullptr;
    MyBox* _legs_linker=nullptr;

    real_t _len, _width, _height;
};

#endif // FORKBOTTOM_H
