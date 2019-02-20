#ifndef MYHINGECONTRAINT_H
#define MYHINGECONTRAINT_H

#include "mydynamicsworld.h"
#include "myrigidbody.h"
#include "configer.h"

class MyHingeContraint
{

public:
    MyHingeContraint(MyRigidBody* bodyA, MyRigidBody* bodyB
                     ,const PositionInfo& posA, const PositionInfo& posB
                     ,bool useReferenceFrameA = false)
    {

        btTransform localA, localB;
        localA.setIdentity();
        localA.setOrigin( btVector3(posA.x,  posA.y,  posA.z) );
        localA.setRotation(btQuaternion(0, 0, 0));
        localB.setIdentity();
        localB.setOrigin(btVector3(posB.x,  posB.y,  posB.z));
        localB.setRotation(btQuaternion(-posB.yaw, 0, 0));
        _contraint = new btHingeConstraint(*(bodyA->physics_body()), *(bodyB->physics_body())
                                           ,localA, localB, useReferenceFrameA);

        _contraint->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
        _contraint->enableAngularMotor(true, -2, 20);
    }

    void attach2World(MyDynamicsWorld* world){
        assert(_contraint);
        world->theWorld()->addConstraint(_contraint);
    }

private:
    btHingeConstraint* _contraint=nullptr;
};

#endif //MYHINGECONTRAINT_H
