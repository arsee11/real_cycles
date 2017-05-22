#include "fork.h"
#include "forkbottom.h"
#include "forkupper.h"


Fork::Fork(const PositionInfo &origin, real_t mass, real_t travel, real_t len, real_t steer_len, real_t axis)
{
    real_t bottom_tube_radius = 2.8f;
    real_t up_tube_radius = 1.8f;
    _forku = new ForkUpper(mass/2.f, travel
                                     ,axis+2*(bottom_tube_radius-up_tube_radius), steer_len);

    real_t ulen = _forku->getLen();
    real_t xu = origin.x;
    real_t yu = origin.y + len/4.f;
    real_t zu = origin.z;


    real_t xz_projection = len/4.f * sin(origin.pitch);
    xu = origin.x + xz_projection * sin(origin.yaw);
    yu = origin.y + len/4.f*cos(origin.pitch);
    zu = origin.z + xz_projection * cos(origin.yaw);
    _forku->create(PositionInfo(xu, yu, zu, origin.yaw, origin.pitch, origin.roll));
    //_forku->physics_body()->setAngularVelocity(btVector3(0, 5, 0));

    real_t blen = len - ulen;
    _forkb = new ForkBottom(mass/2.f, blen, axis);
    real_t xb = origin.x;
    real_t yb = origin.y-len/4.f;
    real_t zb = origin.z;

    xb = origin.x - xz_projection * sin(origin.yaw);
    yb = origin.y - len/4.f*cos(origin.pitch);
    zb = origin.z - xz_projection * cos(origin.yaw);
    _forkb->create(PositionInfo(xb, yb, zb, origin.yaw, origin.pitch, origin.roll));

   btTransform localA, localB;
    localA.setIdentity();
    localA.setOrigin( btVector3(0.f,  -ulen/2.f,  0.f) );
    localB.setIdentity();
    localB.setOrigin(btVector3(0.f, blen/2.f, 0.f));
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
