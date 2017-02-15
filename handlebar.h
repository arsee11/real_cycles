#ifndef HANDLEBAR_H
#define HANDLEBAR_H

#include "mycompoundbody.h"



class Handlebar : public MyCompoundBody
{
public:
    Handlebar(const PositionInfo& origin, real_t mass, real_t len, real_t clamp
              , real_t rasie=0.f, real_t back_sweep=0.f, real_t up_sweep=0.f);
};

#endif // HANDLEBAR_H
