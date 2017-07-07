#ifndef NORMALSHOXSETUP_H
#define NORMALSHOXSETUP_H

#include "mybox.h"
#include "mydiscretedynamicsworld.h"

#include <memory>

template<class FrontPoint , class RearPoint
         ,class Shox
>
class NormalShoxAdapter
{
public:
    NormalShoxAdapter(Shox* shox)
        :_shox(std::auto_ptr<Shox>(shox))
    {
        _fpoint = std::auto_ptr<FrontPoint>(new FrontPoint());
        _rpoint = std::auto_ptr<RearPoint>(new RearPoint());
    }

    template<class FrontPart, class RearPart>
    void setupPoint(FrontPart* f, RearPart* r)
    {
        _rpos = _rpoint->setup(r);
        PositionInfo wrpos = r->toWorldPosition(_rpos);
        //shox line y=kx+b
        real_t k = _shox_roll;
        real_t b= wrpos.y;
        real_t y1 = _shox->length()*sin(k)+b;
        real_t x1= wrpos.x + _shox->length()*cos(k);
        _wfpos = PositionInfo(x1, y1, wrpos.z);
    }

    template<class FrontPart, class RearPart>
    void setupShox(MyDiscreteDynamicsWorld *world, FrontPart* f, RearPart* r)
    {
        real_t slen = _shox->length();
        real_t x=_wfpos.x - (slen/2)*cos(_shox_roll);
        real_t y = _wfpos.y-(slen/2)*sin(_shox_roll);
        real_t z = _wfpos.z;
        PositionInfo o(x, y, z, 0, 0, _shox_roll);
        _shox->moveTo(o);
        _shox->setupLeft( world, r, _rpos);
        PositionInfo fpos  = f->toLocalPosition(_wfpos);
        _shox->setupRight( world, f, fpos );
        _shox->attach2World(world);
    }

private:
    /// dian pian
/*    template<class Part>
    MyBox* setSpacer(MyDiscreteDynamicsWorld *world, Part* p, const PositionInfo& pos, bool is_out)
    {
        PositionInfo ppos(pos.x, pos.y, is_out?pos.z:-pos.z, pos.yaw, pos.pitch, pos.roll);
        real_t sw = _shox->setupPointWidth();
        real_t pw = std::fabs(ppos.z*2);
        real_t dw = (pw-sw)/2;
        PositionInfo wpos = p->toWorldPosition(ppos);
        real_t dz = is_out ? -dw/2 : dw/2;
        PositionInfo dpos(wpos.x, wpos.y, wpos.z+dz, 0.f, 0.f, ppos.roll);
        MyBox* d = new MyBox(1.f, dw, 1.f, dpos, 0.01f);
        d->color(255, 0,0);
        d->attach2World(world);

        btTransform fa, fb;
        fa.setIdentity();
        fa.setOrigin( btVector3(ppos.x, ppos.y, ppos.z) );
        fb.setIdentity();
        fb.setOrigin( btVector3(0,0, -dz) );
        btFixedConstraint* c = new btFixedConstraint(*(p->physics_body()), *(d->physics_body()), fa, fb);
        world->theWorld()->addConstraint(c);
        return d;
    }
*/
private:
    PositionInfo _rpos;
    PositionInfo _wfpos;
    std::auto_ptr<FrontPoint> _fpoint;
    std::auto_ptr<RearPoint> _rpoint;
    std::auto_ptr<Shox> _shox;
    real_t _shox_roll = torads(25);
};

#endif // NORMALSHOXSETUP_H
