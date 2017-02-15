#ifndef TWOLINKERSETUP_H
#define TWOLINKERSETUP_H

#include "mydiscretedynamicsworld.h"
#include "utils.h"
#include <memory>

template<class FrontPoint1, class FrontPoint2
         , class RearPoint1, class RearPoint2
         , class Linker1, class Linker2
>
class TwoLinkerSetup
{
public:
    TwoLinkerSetup(real_t len1, real_t len2)
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
    void setupLinker(MyDiscreteDynamicsWorld *world, FrontPart* f, RearPart* r)
    {
        PositionInfo wfpos1 = f->toWorldPosition(_fpos1);
        PositionInfo wfpos2 = f->toWorldPosition(_fpos2);
        real_t rw1 = abs(_rpos1.z*2);
        real_t fw1 = abs(_fpos1.z*2);
        real_t x=wfpos1.x - (_len1/2);
        real_t y = wfpos1.y;
        real_t z = wfpos1.z - fw1/2;
        PositionInfo o(x, y, z);
        _l1 = std::auto_ptr<Linker1>(new Linker1(o, 0.1f, _len1+2, rw1, fw1));
        _l1->makeLeftLink(world, r, _rpos1);
        _l1->makeRightLink(world, f, _fpos1);
        _l1->attach2World(world);

        real_t rw2 = abs(_rpos2.z*2);
        real_t fw2 = abs(_fpos2.z*2);
        x=wfpos2.x - _len2/2;
        y = wfpos2.y;
        z =  wfpos2.z - fw2/2;;
        o = PositionInfo(x, y, z);
        _l2 = std::auto_ptr<Linker2>(new Linker2(o, 0.1f, _len2+2, rw2, fw2));
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
