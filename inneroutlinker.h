#ifndef INNEROUTLINKER_H
#define INNEROUTLINKER_H

#include "linker.h"

//left side is inner, right side is out
class InnerOutLinker : public Linker
{
public:
    InnerOutLinker(const PositionInfo& origin, real_t mass
                ,real_t len
                ,real_t left_width
                ,real_t right_width
    );

private:
    MyRigidBody* _left=nullptr;
    MyRigidBody* _right_out=nullptr;
    MyRigidBody* _right_in=nullptr;
};

#endif // INNEROUTLINKER_H
