#ifndef PEDAL_H
#define PEDAL_H

#include "mycompoundbody.h"



class Pedal : public MyCompoundBody
{
public:
    Pedal(const PositionInfo& origin, real_t mass);
    real_t len(){ return 10.f; }
    real_t width(){ return 10.f; }
    real_t height(){ return 2.f; }
};

#endif // PEDAL_H
