#include "fork.h"
#include "configer.h"

Fork::Fork(const PositionInfo &origin, real_t mass, real_t travel, real_t len, real_t steer_len, real_t axle)
    :_len(len)
    ,_steer_len(steer_len)
    ,_origin(origin)
{
    real_t bottom_tube_radius = 2.8f;
    real_t up_tube_radius = 1.8f;
    _forku = new ForkUpper(mass/2.f, travel
                                     ,axle+2*(bottom_tube_radius-up_tube_radius), steer_len);

    real_t ulen = _forku->getLen();   
    real_t blen = len - ulen;
    _forkb = new ForkBottom(mass/2.f, blen, axle);

    PositionInfo posu, posb;
    std::tie(posu, posb) = calcPos(origin);
    _forku->create(posu);
    _forkb->create(posb);

    btTransform localA, localB;
    localA.setIdentity();
    localA.setOrigin( btVector3(0.f,  -ulen/2.f,  0.f) );
    localB.setIdentity();
    localB.setOrigin(btVector3(0.f, blen/2.f, 0.f));
    _constraint =  new btGeneric6DofSpring2Constraint(
                *(_forku->physics_body()), *(_forkb->physics_body()), localA, localB);

    _constraint->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
    _constraint->setLimit(0, 0, 0);
    _constraint->setLimit(1, 0, travel);
    _constraint->setLimit(2, 0, 0);
    _constraint->setLimit(3, 0, 0);
    _constraint->setLimit(4, 0, 0);
    _constraint->setLimit(5, 0, 0);
    _constraint->enableSpring(1, true);
    _constraint->setStiffness(1, 100.f);
    _constraint->setDamping(1, 40.f);
}

void Fork::attach2world(MyDynamicsWorld *world)
{
    _forkb->attach2World(world);
    _forku->attach2World(world);
    world->theWorld()->addConstraint(_constraint, true);
}

///@return first upper position, second bottom postion
std::tuple<PositionInfo, PositionInfo> Fork::calcPos(const PositionInfo& pos)
{
    real_t xu = pos.x;
    real_t yu = pos.y + _len/4.f;
    real_t zu = pos.z;

    real_t xz_projection = _len/4.f * sin(pos.pitch);
    xu = pos.x + xz_projection * sin(pos.yaw);
    yu = pos.y + _len/4.f*cos(pos.pitch);
    zu = pos.z + xz_projection * cos(pos.yaw);

    real_t xb = pos.x;
    real_t yb = pos.y-_len/4.f;
    real_t zb = pos.z;

    xb = pos.x - xz_projection * sin(pos.yaw);
    yb = pos.y - _len/4.f*cos(pos.pitch);
    zb = pos.z - xz_projection * cos(pos.yaw);

    return std::make_tuple( PositionInfo(xu, yu, zu, pos.yaw, pos.pitch, pos.roll)
                           , PositionInfo(xb, yb, zb, pos.yaw, pos.pitch, pos.roll)
                );
}

void Fork::moveTo(const PositionInfo &pos)
{
    PositionInfo posu, posb;
    std::tie(posu, posb) = calcPos(pos);
    _forku->origin(posu);
    _forkb->origin(posb);
    _origin = pos;
}

PositionInfo Fork::getSetupLocalPosition()const
{
        real_t x=0.f, y=0.f, z=0.f;
        PositionInfo o = _forku->getCrownOrigin();
        y += o.y + 2+0.5;
        return PositionInfo(x, y, z, o.yaw, o.pitch, o.roll);
}

PositionInfo Fork::getSteerTubeTopLocalPosition() const
{
    PositionInfo o = _forku->origin();
    real_t x=0.f, y=0.f, z=0.f;
    y += _forku->getLen()/2.f;
    return PositionInfo(x, y, z, o.yaw, o.pitch, o.roll);
}



PositionInfo Fork::getWheelSetupLocalPosition() const
{
    PositionInfo o = _forkb->origin();
    real_t x=0.f, y=0.f, z=0.f;
    y -= _forkb->getLen()/2.f;
    return PositionInfo(x, y, z, o.yaw, o.pitch, o.roll);
}



