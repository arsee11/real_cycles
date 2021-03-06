#include "forkbottom.h"
#include "mybox.h"
#include "mycylinder.h"


ForkBottom::ForkBottom(real_t mass, real_t len, real_t axle)
    :MyCompoundBody(mass)
{
    _x = axle + 2.8f*4.f;
    _z = 2.8f *2.f;
    _y = len;

    real_t cmass = mass/3.f;

    //fork legs
     _left_leg = new MyCylinder(2.8f, len, 2.8f);
     _left_leg->color(255, 0, 0);
     addBody(cmass, _left_leg, -(axle/2.f+2.8f),  0.f , 0.f);

     _right_leg = new MyCylinder(2.8f, len, 2.8f);
     _right_leg->color(255, 0, 0);
     addBody(cmass, _right_leg, axle/2.f+2.8f, 0.f, 0.f);

     //_legs_linker = new MyBox(axle, 4.f, linker_height);
     //_legs_linker->color(0,0,255);
     //addBody(cmass,  _legs_linker, 0.f, len/2.f, 0.f);
}
