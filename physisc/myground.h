#ifndef MYGROUND_H
#define MYGROUND_H

#include "mybox.h"

class MyGround : public MyBox
{
public:
    MyGround(real_t l, real_t w, real_t h, const PositionInfo& origin)
        :MyBox(l, w, h, origin, 0.f)
    {}

 };
#endif // MYGROUND_H
