#ifndef HANDLEBAR_H
#define HANDLEBAR_H

#include "mycompoundbody.h"

class MyCylinder;

class Handlebar : public MyCompoundBody
{
public:
    Handlebar(const PositionInfo& pos, real_t mass, real_t len, real_t clamp
              , real_t rasie, real_t back_sweep, real_t up_sweep);

    PositionInfo getCenterLocalPosition()const;
    void moveTo(const PositionInfo& pos){ this->origin(pos); }
    real_t raise(){ return _raise;}

private:
    MyCylinder* _bar_center=nullptr;
    MyCylinder* _bar_rasie_left=nullptr;
    MyCylinder* _bar_rasie_rigth=nullptr;
    MyCylinder* _bar_left=nullptr;
    MyCylinder* _bar_right=nullptr;

    real_t _len;
    real_t _clamp;
    real_t _raise;
    real_t _center_len = 10.f;
    real_t _rasie_len;
    void createBarCenter(real_t mass, real_t back_sweep, real_t up_sweep);
    void createBarSide(real_t mass, real_t back_sweep, real_t up_sweep);
    void createBarRasie(real_t mass);
};

#endif // HANDLEBAR_H
