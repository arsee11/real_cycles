#include "mycylinder.h"
#include "stem.h"


Stem::Stem(const PositionInfo& pos, real_t mass, real_t len, real_t raise)
    :MyCompoundBody(mass)
    ,_len(len)
    ,_raise(raise)
{
    real_t radius =2.5f;
    _stem = new MyCylinder(radius, len, radius, MyCylinder::AroundType::X);
    _stem->color(255, 0, 0);
    real_t x =0.f;
    real_t y = 0.f;
    real_t z =  0.f;
    addBody(mass, _stem, x, y, z, 0.f, 0.f, torads(raise));
    create(pos);
}

PositionInfo Stem::getLeftSetupLocalPosition() const
{
    PositionInfo o = this->origin();
    real_t rraise = torads(_raise);
    real_t len = _len * cos( torads(rraise) );
    real_t x = -len/2.f;
    real_t y = -sin( rraise)* _len/2.f;
    real_t z = 0;
    return PositionInfo(x, y, z, o.yaw, o.pitch, o.roll);
}

PositionInfo Stem::getRightSetupLocalPosition() const
{
    PositionInfo pos = getLeftSetupLocalPosition();
    pos.x = -pos.x;
    pos.y = -pos.y;
    return pos;
}

PositionInfo Stem::getRightSetupWorldPosition() const
{
    return this->toWorldPosition( getRightSetupLocalPosition() );
}
