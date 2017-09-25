#ifndef TWOLINKERSETUP_H
#define TWOLINKERSETUP_H

#include "mydynamicsworld.h"
#include "utils.h"
#include <memory>

template<class FrontPoint1, class FrontPoint2
         , class RearPoint1, class RearPoint2
         , class Linker1, class Linker2
>
class TwoLinkerAdapter
{
public:
    TwoLinkerAdapter(real_t len1, real_t len2)
        :_len1(len1)
        ,_len2(len2)
    {}

    template<class FrontPart, class RearPart>
    void setupPoint(FrontPart* f, RearPart* r)
    {
        _fpos1 = FrontPoint1().setup(f);
        _fpos2 = FrontPoint2().setup(f);
        _rpos1 = RearPoint1().setup(r);
        _rpos2 = RearPoint2().setup(r);
    }

    template<class FrontPart, class RearPart>
    void setupLinker(MyDynamicsWorld *world, FrontPart* f, RearPart* r)
    {
        PositionInfo wfpos1 = f->toWorldPosition(_fpos1);
        PositionInfo wrpos1 = r->toWorldPosition(_rpos1);
        real_t absx = absf(wfpos1.x-wrpos1.x);
        real_t absy = absf(wfpos1.y-wrpos1.y);
         _len1 =pow( pow(absx, 2)+pow(absy, 2), 0.5 );
         real_t roll=0;
         if(absy>0)
            roll = atan(absy/absx);

        real_t x=wfpos1.x - (_len1/2)*cos(roll);
        real_t y = wfpos1.y+(_len1/2)*sin(-roll);
        real_t fw1 = FrontPoint1().getParam().width;
        real_t z = f->origin().z;

        real_t rw1 = r->tyre_width();
        PositionInfo o(x, y, z, 0.f, 0.f, roll);
        _l1 = std::auto_ptr<Linker1>(new Linker1(o, 0.1f, _len1, rw1, fw1));
        _l1->makeLeftLink(world, r, _rpos1);
        _l1->makeRightLink(world, f, _fpos1);
        _l1->attach2World(world);

        PositionInfo wfpos2 = f->toWorldPosition(_fpos2);
        PositionInfo wrpos2 = r->toWorldPosition(_rpos2);
        absx = absf(wfpos2.x-wrpos2.x);
        absy = absf(wfpos2.y-wrpos2.y);
        _len2 =pow( pow(absx, 2)+pow(absy, 2), 0.5 );
        roll = atan(absy/absx);
        x=wfpos2.x - _len2/2*cos(roll);
        y = wfpos2.y+_len2/2*sin(roll);
        real_t fw2 = FrontPoint2().getParam().width;

        real_t rw2 = r->tyre_width();
        o = PositionInfo(x, y, z, 0.f, 0.f, -roll);
        _l2 = std::auto_ptr<Linker2>(new Linker2(o, 0.1f, _len2, rw2, fw2));
        _l2->makeLeftLink(world, r, _rpos2);
        _l2->makeRightLink(world, f, _fpos2);
        _l2->attach2World(world);
    }

    void remove(){}

private:
    real_t _len1, _len2;
    PositionInfo _fpos1 ;
    PositionInfo _fpos2 ;
    PositionInfo _rpos1;
    PositionInfo _rpos2 ;
    std::auto_ptr<Linker1> _l1;
    std::auto_ptr<Linker2> _l2;
};

#endif // TWOLINKERSETUP_H
