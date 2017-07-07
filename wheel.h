#ifndef WHEEL_H
#define WHEEL_H

#include "mycompoundbody.h"


class MyCylinder;

class Wheel : public MyCompoundBody
{
public:
    Wheel(const PositionInfo &pos, real_t mass, real_t size_inch, real_t width_inch, real_t axis_len, real_t axis_diameter);
    PositionInfo getSetupLocalPosition() const{
        return PositionInfo(0, 0, 0);
    }

    void moveTo(const PositionInfo& pos){ this->origin(pos); }

private:
    real_t _size_inch, _size_cm;
    real_t _width_inch, _width_cm;
    real_t _axis_len;
    real_t _axis_diameter;

    MyCylinder* _wheel=nullptr;
    MyCylinder* _axis_body_out=nullptr;
    MyCylinder* _axis_body_in=nullptr;
};

#endif // WHEEL_H
