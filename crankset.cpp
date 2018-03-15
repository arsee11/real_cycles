#include "crankset.h"
#include "mybox.h"
#include "mycylinder.h"


Crankset::Crankset(real_t length, real_t bb, real_t teeth, real_t mass
                   ,const PositionInfo& origin
)
    :MyCompoundBody(origin, mass)
{
    _bb_len = bb;
    real_t mbb = mass/3;
    real_t mcr = mass/3;
    real_t mleg = mass/3;
    createBB(bb, mbb);
    createChainRing(teeth, mcr);
    createLeg(length, mleg);
    create(origin);
}

real_t bb_raduis = 3.f;
void Crankset::createChainRing(real_t teeth, real_t mass)
{
    _ring = new MyCylinder(7.f, 1.f, 7.f, MyCylinder::Z);
    real_t x=0.f, y=0.f, z=_bb_len/2.f+0.5f;
    this->addBody(_ring, PositionInfo(x,y,z), mass);
}

void Crankset::createLeg(real_t length, real_t mass)
{
    real_t x=0.f, y=0.f, z=0.f;
    real_t l = length+bb_raduis/2.f+1;//leg len + bb_raduis+padal setup
    _left_leg = new MyBox(l, 2.f, 3.f);
    x=-l/2.f + bb_raduis;
    z=-(_bb_len/2.f + 2.f/1.f);
    this->addBody(_left_leg, PositionInfo(x,y,z), mass/2.f);

    _right_leg = new MyBox(l, 2.f, 3.f);
    x=-x;
    z=-z;
    this->addBody(_right_leg, PositionInfo(x,y,z), mass/2.f);
}

void Crankset::createBB(real_t bb, real_t mass)
{
    _bb = new MyCylinder(bb_raduis, bb, bb_raduis, MyCylinder::Z);
    real_t x=0.f, y=0.f, z=0.f;
    this->addBody(_bb, PositionInfo(x,y,z), mass);
}
