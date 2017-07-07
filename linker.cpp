#include "linker.h"
#include "mybox.h"
#include "configer.h"

Linker::Linker(const PositionInfo &origin, real_t mass, real_t len, real_t left_width, real_t right_width)
   :/*MyBox(len, left_width, 2.f, origin, mass)*/MyCompoundBody(origin, mass)
   ,_len(len)
   ,_left_width(left_width)
   ,_right_width(right_width)
{

}

void Linker::makeLink(MyDiscreteDynamicsWorld *world, const PositionInfo&this_point, MyPhysicsBody *body, const PositionInfo &body_point)
{
    btVector3 axis_this(0.f, 0.f, 1.f);
    btVector3 axis_body(0.f, 0.f, 1.f);
    btVector3 pivot_this(this_point.x, this_point.y, this_point.z);
    btVector3 pivot_body( body_point.x, body_point.y, body_point.z );
    btHingeConstraint*  hinge = new btHingeConstraint(*(this->physics_body()), *(body->physics_body())
                                                     , pivot_this, pivot_body, axis_this, axis_body);

    //hinge->setBreakingImpulseThreshold(5.f);
    hinge->setOverrideNumSolverIterations(PhysicsConfiger::OverrideNumSolverIterations);
    world->theWorld()->addConstraint(hinge);
}


void Linker::makeLeftLink(MyDiscreteDynamicsWorld *world, MyPhysicsBody *body, const PositionInfo &body_point)
{
    PositionInfo anchor1( -(_len/2.f), 0.f, 0.f );
    PositionInfo body_point1 = body_point;
    makeLink(world, anchor1, body, body_point1);    
}

void Linker::makeRightLink(MyDiscreteDynamicsWorld *world, MyPhysicsBody *body, const PositionInfo &body_point)
{
    PositionInfo anchor1( _len/2.f, 0.f, 0.f );
    PositionInfo body_point1 = body_point;
    makeLink(world, anchor1, body, body_point1);    
}
