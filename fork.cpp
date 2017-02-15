#include "fork.h"
#include "forkbottom.h"
#include "forkupper.h"


Fork::Fork(const PositionInfo &origin, real_t mass, real_t travel, real_t len, real_t steer_len, real_t axis)
{
    real_t bottom_tube_radius = 2.8f;
    real_t up_tube_radius = 1.8f;
    real_t crown_height = 4.f;

    _forku = new ForkUpper(mass/2.f, travel
                                     ,axis+2*(bottom_tube_radius-up_tube_radius), steer_len);
    real_t l, w, h;
    std::tie(l,w,h) = _forku->getLWH();
    real_t yu = origin.y + h/2.f;
    _forku->create(PositionInfo(origin.x, yu, origin.z));
    //_forku->physics_body()->setAngularVelocity(btVector3(0, 5, 0));

    real_t blen = len - travel - crown_height;
    _forkb = new ForkBottom(mass/2.f, blen, axis);
    std::tie(l,w,h) = _forkb->getLWH();
    real_t yb = origin.y-h/2.f;
    _forkb->create(PositionInfo(origin.x, yb, origin.z));

    btTransform localA, localB;
    localA.setIdentity();
    localA.setOrigin( btVector3(0.f,  -yu,  0.f) );
    localB.setIdentity();
    localB.setOrigin(btVector3(0.f, -yb, 0.f));
    _contraint =  new btGeneric6DofSpring2Constraint(
                *(_forku->physics_body()), *(_forkb->physics_body()), localA, localB);

    _contraint->setLimit(0, 0, 0);
    _contraint->setLimit(1, 0, travel);
    _contraint->setLimit(2, 0, 0);
    _contraint->setLimit(3, 0, 0);
    _contraint->setLimit(4, 0, 0);
    _contraint->setLimit(5, 0, 0);
    _contraint->enableSpring(1, true);
    _contraint->setStiffness(1, 100.f);
    _contraint->setDamping(1, 2.f);
}

void Fork::attach2world(MyDiscreteDynamicsWorld *world)
{
    _forkb->attach2World(world);
    _forku->attach2World(world);
    world->theWorld()->addConstraint(_contraint, true);
}
