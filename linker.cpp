#include "linker.h"
#include "mybox.h"

Linker::Linker(const PositionInfo &origin, real_t mass, real_t len, real_t left_width, real_t right_width)
   :/*MyBox(len, left_width, 2.f, origin, mass)*/MyCompoundBody(origin, mass)
   ,_len(len)
   ,_left_width(left_width)
   ,_right_width(right_width)
{

}

void Linker::makeLink(MyDiscreteDynamicsWorld *world, const PositionInfo&this_point, MyPhysicsBody *body, const PositionInfo &body_point)
{
    btTransform localA, localB;
    localA.setIdentity();
    localA.setOrigin( btVector3(this_point.x, this_point.y, this_point.z) );
    localB.setIdentity();
    localB.setOrigin(btVector3(body_point.x, body_point.y, body_point.z));
    btGeneric6DofSpring2Constraint* c =  new btGeneric6DofSpring2Constraint(
                *(this->physics_body()), *(body->physics_body()), localA, localB);

    c->setLimit(0, 0, 0);
    c->setLimit(1, 0, 0);
    c->setLimit(2, 0, 0);
    c->setLimit(3, 0, 0);
    c->setLimit(4, 0, 0);
    c->setLimit(5, MY_PI, -MY_PI);
    //c->enableMotor(5, true);
    //c->setTargetVelocity(5, 10);
    //c->setMaxMotorForce(5, 100);

    world->theWorld()->addConstraint(c);
}


void Linker::makeLeftLink(MyDiscreteDynamicsWorld *world, MyPhysicsBody *body, const PositionInfo &body_point)
{
    PositionInfo anchor1( -(_len/2.f-1.f), 0, _left_width/2.f );
    PositionInfo body_point1 = body_point;
    makeLink(world, anchor1, body, body_point1);

    PositionInfo anchor2( -(_len/2.f-1.f), 0, -_left_width/2.f );
    PositionInfo body_point2(body_point.x, body_point.y, -body_point.z);
    makeLink(world, anchor2, body, body_point2);
}

void Linker::makeRightLink(MyDiscreteDynamicsWorld *world, MyPhysicsBody *body, const PositionInfo &body_point)
{
    PositionInfo anchor1( _len/2.f-1.f, 0, _right_width/2.f );
    PositionInfo body_point1 = body_point;
    makeLink(world, anchor1, body, body_point1);

    PositionInfo anchor2( _len/2.f-1.f, 0, -_right_width/2.f );
    PositionInfo body_point2(body_point.x, body_point.y, -body_point.z);
    makeLink(world, anchor2, body, body_point2);
}
