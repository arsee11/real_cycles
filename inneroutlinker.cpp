#include "inneroutlinker.h"

InnerOutLinker::InnerOutLinker(const PositionInfo &origin, real_t mass, real_t len, real_t left_width,real_t right_width)
    :Linker(origin, mass, len, left_width, right_width)
{
    real_t left_len = 2.f;
    real_t h = 2.f;
    real_t cmass = mass/3.f;
    _left = new MyBox(left_len, this->_left_width, h );
    _left->color(0,0,255);
    real_t x = -((len-left_len)/2.f);
    addBody(cmass, _left, x, 0, 0);

    real_t w = 1.f;
    _right_out= new MyBox(len-left_len, w, h);
    _right_out->color(0,0,255);
     x = (left_len)/2.f;
     real_t  z= this->_right_width/2.f + w/2.f;
    addBody(cmass, _right_out, x, 0, z);

    _right_in = new MyBox(len-left_len, w, h );
    _right_in->color(0,0,255);
    addBody(cmass,_right_in, x, 0, -z);

    this->createSelf();
}


