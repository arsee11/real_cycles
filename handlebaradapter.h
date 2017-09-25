#ifndef HANDLERBARADAPTER_H
#define HANDLERBARADAPTER_H

#include "mydynamicsworld.h"
#include "configer.h"


template<class Fork, class Stem, class Bar>
class HandlebarAdapter
{
public:
    HandlebarAdapter(Fork* fork, Stem* stem, Bar* bar)
        :_fork(fork)
        ,_stem(stem)
        ,_bar(bar)
    {}

    void setup(MyDynamicsWorld* world);

private:
    Fork* _fork;
    Stem* _stem;
    Bar* _bar;
};

template<class Fork, class Stem, class Bar>
void  HandlebarAdapter<Fork, Stem, Bar>::setup(MyDynamicsWorld* world){

    PositionInfo wfkpos = _fork->getSteerTubeTopWorldPosition();
    real_t l=_stem->len();
    real_t raise = _stem->raise();
    real_t x = wfkpos.x+ l/2.f * cos( torads(raise) );
    real_t y = wfkpos.y + l/2.f * sin( torads(raise) )-2;
    real_t z = wfkpos.z;
    _stem->moveTo( PositionInfo(x, y, z) );

    PositionInfo spos = _stem->getLeftSetupLocalPosition();
    PositionInfo fkpos = _fork->getSteerTubeTopLocalPosition();
    btTransform localA, localB;
     localA.setIdentity();
     localA.setOrigin( btVector3(fkpos.x,  fkpos.y-2,  fkpos.z) );
     localA.setRotation(btQuaternion(-fkpos.yaw, 0, 0));
     localB.setIdentity();
     localB.setOrigin(btVector3(spos.x,  spos.y,  spos.z));
     localB.setRotation(btQuaternion(0, 0, 0));

     btFixedConstraint* constraint =  new btFixedConstraint(
                 *(_fork->upper_body()), *(_stem->physics_body()), localA, localB);

     constraint->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
     world->theWorld()->addConstraint(constraint, true);

     PositionInfo wsrpos =_stem->getRightSetupWorldPosition();
     PositionInfo bpos = _bar->getCenterLocalPosition();
     x = wsrpos.x-3;
     y = wsrpos.y-bpos.y;
     _bar->moveTo( PositionInfo(x, y, z, torads(90)) );
     bpos = _bar->getCenterLocalPosition();

     PositionInfo srpos =_stem->getRightSetupLocalPosition();
     localA.setIdentity();
     localA.setOrigin( btVector3(srpos.x,  srpos.y,  srpos.z) );
     localA.setRotation(btQuaternion(-srpos.yaw, -srpos.pitch, -srpos.roll));
     localB.setIdentity();
     localB.setOrigin(btVector3(bpos.x,  bpos.y,  bpos.z));
     localB.setRotation(btQuaternion(-bpos.yaw, -bpos.pitch,- bpos.roll));
     constraint =  new btFixedConstraint(
                 *(_stem->physics_body()), *(_bar->physics_body()), localA, localB);

     constraint->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
     world->theWorld()->addConstraint(constraint, true);
}

#endif // HANDLERBARADAPTER_H
