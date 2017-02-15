#ifndef FORKUPPER_H
#define FORKUPPER_H

#include "mycompoundbody.h"

class MyCylinder;
class MyBox;

class ForkUpper : public MyCompoundBody
{
public:
    ForkUpper(real_t mass, real_t travel, real_t width, real_t steer_len);

    ///return len width height of effective cube
    std::tuple<real_t, real_t, real_t> getLWH(){ return std::make_tuple(_len, _width, _height); }

private:
    MyCylinder* _left_tube=nullptr, *_right_tube=nullptr;
    MyBox* _crown=nullptr;
    MyCylinder* _streer=nullptr;

    real_t _len, _width, _height;

};

#endif // FORKUPPER_H
