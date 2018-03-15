#ifndef PEDAL_H
#define PEDAL_H

#include "mycompoundbody.h"



class Pedal : public MyCompoundBody
{
public:
    Pedal(const PositionInfo& origin, real_t mass);

};

#endif // PEDAL_H
