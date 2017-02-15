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

void InnerLinker::makeLeftLink(MyDiscreteDynamicsWorld *world, MyPhysicsBody *body, const PositionInfo &body_point)
{
    PositionInfo anchor1( -(_len/2.f-1.f), 0, _left_width/2.f );
    PositionInfo body_point1 = body_point;
    makeLink(world, anchor1, body, body_point1);

    PositionInfo anchor2( -(_len/2.f-1.f), 0, -_left_width/2.f );
    PositionInfo body_point2(body_point.x, body_point.y, -body_point.z);
    makeLink(world, anchor2, body, body_point2);
}

void InnerLinker::makeRightLink(MyDiscreteDynamicsWorld *world, MyPhysicsBody *body, const PositionInfo &body_point)
{
    PositionInfo anchor1( _len/2.f-1.f, 0, _right_width/2.f );
    PositionInfo body_point1 = body_point;
    makeLink(world, anchor1, body, body_point1);

    PositionInfo anchor2( _len/2.f-1.f, 0, -_right_width/2.f );
    PositionInfo body_point2(body_point.x, body_point.y, -body_point.z);
    makeLink(world, anchor2, body, body_point2);
}


void InnerLinker::calcCube()
{
    _cube.height(2.f);
    _cube.width( _left_width>_right_width?_left_width:_right_width);
    _cube.len(_len);
}
