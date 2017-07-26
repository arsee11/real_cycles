#ifndef CRANKSET_H
#define CRANKSET_H

#include "mycompoundbody.h"



class Crankset : public MyCompoundBody
{
public:
    Crankset(real_t length, real_t bbwidth, real_t mass);
};

#endif // CRANKSET_H
