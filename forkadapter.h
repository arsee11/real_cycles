#ifndef FORKADAPTER_H
#define FORKADAPTER_H

#include "utils.h"
#include <btBulletDynamicsCommon.h>
#include "mydynamicsworld.h"
#include "configer.h"

class DiscreteDynamicsWorld;

template<class Frame, class Fork>
class ForkAdapter
{
public:
    ForkAdapter(Frame* fr, Fork* fk)
        :_frame(fr)
        ,_fork(fk)
    {
    }

    void setup(MyDynamicsWorld* world)
    {
        PositionInfo frpos = _frame->getForkSetupLocalPosition();
        PositionInfo wfrpos = _frame->getForkSetupWorldPosition();

        PositionInfo wfkpos = _fork->getSetupWorldPosition();
        PositionInfo fko = _fork->origin();

        real_t hta = _frame->HTA();

        real_t l = Vex(wfkpos.x, wfkpos.y, wfkpos.z).distance(Vex(fko.x, fko.y, fko.z));
        real_t x = wfrpos.x + l * cos( torads(hta) );
        real_t y = wfrpos.y - l * sin( torads(hta) );
        real_t z = wfrpos.z;

        PositionInfo pos(x, y, z, torads(90), -torads(90-hta));
        _fork->moveTo(pos);
        PositionInfo fkpos = _fork->getSetupLocalPosition();




        btTransform localA, localB;
         localA.setIdentity();
         localA.setOrigin( btVector3(frpos.x,  frpos.y,  frpos.z) );
         localB.setIdentity();
         localB.setOrigin(btVector3(fkpos.x,  fkpos.y,  fkpos.z));
         localB.setRotation( btQuaternion(-fkpos.yaw, 0, fkpos.pitch));
         btGeneric6DofConstraint* constraint =  new btGeneric6DofConstraint(
                     *(_frame->front_body()), *(_fork->upper_body()), localA, localB, true);       

         /*btVector3 axis_frame(0.f, 1.f, 0.f);
         btVector3 axis_fork(0.f, 1.f, 0.f);
         btVector3 pivot_frame(frpos.x, frpos.y, frpos.z);
         btVector3 pivot_fork( fkpos.x, fkpos.y, fkpos.z );
         btHingeConstraint*  hinge = new btHingeConstraint(*(_frame->front_body()), *(_fork->upper_body())
                                                          , pivot_frame, pivot_fork, axis_frame, axis_fork);

         btHingeConstraint*  hinge = new btHingeConstraint(*(_frame->front_body()), *(_fork->upper_body())
                                                           , localA, localB);
         world->theWorld()->addConstraint(hinge, true);
        */
         constraint->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
         world->theWorld()->addConstraint(constraint, true);

         real_t htl = _frame->HTL();
         localA.setIdentity();
         localA.setOrigin( btVector3(frpos.x-htl*cos(torads(hta)),  frpos.y+htl*sin(torads(hta)),  frpos.z) );
         localA.setRotation( btQuaternion(frpos.yaw, frpos.pitch, frpos.roll));
         localB.setIdentity();
         localB.setOrigin(btVector3(fkpos.x,  fkpos.y+htl,  fkpos.z));
         localB.setRotation( btQuaternion(-fkpos.yaw, 0, fkpos.pitch));
         constraint =  new btGeneric6DofConstraint(
                     *(_frame->front_body()), *(_fork->upper_body()), localA, localB, true);

        constraint->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
        constraint->setAngularLowerLimit(btVector3(0,0,0));
        constraint->setAngularUpperLimit(btVector3(0,0,0));
        world->theWorld()->addConstraint(constraint, true);
    }

private:
    Frame*  _frame=nullptr;
    Fork* _fork=nullptr;
};

#endif // FORKADAPTER_H
