#include "innerlinker.h"
#include "mybox.h"



InnerLinker::InnerLinker(const PositionInfo &origin, real_t mass, real_t len, real_t left_width,real_t right_width)
    :Linker(origin, mass, len, left_width, right_width)
{
    calcCube();

    real_t cmass = mass/3.f;
    _left = new MyBox(2.f, this->_left_width, _cube.height() );
    _left->color(0,0,255);
    real_t x = -((_len-4.f)/2.f);
    addBody(cmass, _left, x, 0, 0);

    _right = new MyBox(2.f, this->_right_width, _cube.height() );
    _right->color(0,0,255);
     x = (_len-4.f)/2.f;
    addBody(cmass, _right, x, 0, 0);

    _center = new MyBox(_len-4.f, 3.f, _cube.height() );
    _center->color(0,0,255);
    addBody(cmass,_center, 0, 0, 0);

    this->createSelf();
}

void InnerLinker::calcCube()
{
    _cube.height(2.f);
    _cube.width( _left_width>_right_width?_left_width:_right_width);
    _cube.len(_len);
}
