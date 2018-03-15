#ifndef CRANKSET_H
#define CRANKSET_H

#include "mycompoundbody.h"

class MyCylinder;
class MyBox;

class Crankset : public MyCompoundBody
{
public:
    Crankset(real_t length, real_t bb, real_t teeth, real_t mass
             ,const PositionInfo& origin=PositionInfo(0,0,0)
    );

private:
    void createChainRing(real_t teeth, real_t mass);
    void createLeg(real_t length, real_t mass);
    void createBB(real_t bb, real_t mass);

private:
    MyCylinder* _ring=nullptr;
    MyCylinder* _bb=nullptr;
    MyBox* _left_leg=nullptr, *_right_leg=nullptr;
    real_t _bb_len=0.f;
};

#endif // CRANKSET_H
