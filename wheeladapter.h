#ifndef WHEELADAPTER_H
#define WHEELADAPTER_H

#include "mydiscretedynamicsworld.h"
#include "utils.h"
#include <assert.h>
#include "configer.h"

template<class Base,  class Wheel>
class WheelAdapter
{
public:
    WheelAdapter(Base* base, Wheel* wheel)
        :_base(base)
        ,_wheel(wheel)
    {}

    void setup(MyDynamicsWorld* world);

private:
    Base* _base=nullptr;
    Wheel* _wheel=nullptr;
};

template<class Base,  class Wheel>
void WheelAdapter<Base, Wheel>::setup(MyDynamicsWorld *world){
    assert(_wheel);
    assert(_base);
    PositionInfo wbpos = _base->getWheelSetupWorldPosition();
    _wheel->moveTo(wbpos);

    PositionInfo wpos = _wheel->getSetupLocalPosition();
    PositionInfo bpos = _base->getWheelSetupLocalPosition();

   btTransform localA, localB;
    localA.setIdentity();
    localA.setOrigin( btVector3(wpos.x,  wpos.y,  wpos.z) );
    localA.setRotation(btQuaternion(0, 0, 0));
    localB.setIdentity();
    localB.setOrigin(btVector3(bpos.x,  bpos.y,  bpos.z));
    localB.setRotation(btQuaternion(-bpos.yaw, 0, 0));
    btHingeConstraint*  hinge = new btHingeConstraint(*(_wheel->physics_body()), *(_base->wheel_setup_body())
                                                      , localA, localB);

    hinge->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
    hinge->enableAngularMotor(true, -2, 20);
    world->theWorld()->addConstraint(hinge);

}

#endif // WHEELADAPTER_H
