#ifndef CRANKSETADAPTER_H
#define CRANKSETADAPTER_H

#include <mydynamicsworld.h>
#include <myhingeconstraint.h>


template<class Frame, class Pedal, class Crankset>
class CranksetAdapter
{
public:
    CranksetAdapter(Frame* f, Pedal* p, Crankset* c)
        :_frame(fork)
        ,_pedal(stem)
        ,_crankset(bar)
    {}

    void setup(MyDynamicsWorld* world);

private:
    Frame* _frame;
    Pedal* _pedal;
    Crankset* _crankset;
};

template<class Frame, class Pedal, class Crankset>
void  CranksetAdapter<Frame, Pedal, Crankset>::setup(MyDynamicsWorld* world){

    PositionInfo wfkpos = _frame->getBBWorldPosition();
    real_t x = wfkpos.x+ l/2.f * cos( torads(raise) );
    real_t y = wfkpos.y + l/2.f * sin( torads(raise) )-2;
    real_t z = wfkpos.z;
    _crankset->origin( PositionInfo(x, y, z) );

    PositionInfo posck = _crankset->getSetup2FrameLocalPostion();
    PositionInfo posf = _frame->getBBLocalPosition();
    MyHingeContraint c(_frame, _crankset, posf, posck, true);
    c.attach2World(world);

    PositionInfo wposck = _crankset->getSetup2PedalWorldPostion();
    PositionInfo posp = _pedal->getSetupLocalPosition();
    _pedal->origin( PositionInfo(x, y, z));
    posck = _crankset->getSetup2PedalLocalPostion();
    MyHingeContraint c2(_crankset, _pedal, possk, posp, true);
    c2.attach2World(world);

}

#endif // CRANKSETADAPTER_H
