#include "handlebar.h"
#include "mycylinder.h"

Handlebar::Handlebar(const PositionInfo& pos, real_t mass, real_t len, real_t clamp, real_t raise, real_t back_sweep, real_t up_sweep)
    :MyCompoundBody(mass)
    ,_len(len)
    ,_clamp(clamp)
    ,_raise(raise)
{
    //real_t real_rasie_len;
    //real_t real_side_len;
    createBarCenter(mass/3.f, back_sweep, up_sweep);
    createBarRasie(mass/3.f);
    createBarSide(mass/3.f, back_sweep, up_sweep);
    create(pos);
}

PositionInfo Handlebar::getCenterLocalPosition() const
{
    PositionInfo o = this->origin();
    PositionInfo co = _bar_center->origin();
    co.yaw = o.yaw;
    co.pitch = o.pitch;
    co.roll = o.roll;
    return co;
}

std::tuple<Vex, Vex> Handlebar::getControlPoint()
{
    Vex left(0,0, -_len/2.f);
    Vex right(0,0, _len/2.f);
    return std::make_tuple(left, right);
}

void Handlebar::createBarCenter(real_t mass, real_t back_sweep, real_t up_sweep)
{
    real_t radius = _clamp/2.f;
    _bar_center = new MyCylinder(radius, _center_len, radius, MyCylinder::AroundType::X);
    _bar_center->color(0, 255, 0);
    real_t x = 0.f;
    real_t y = -( ( _raise + _clamp + (_len-_center_len)/2.f*sin(torads(up_sweep)) )/2.f );
    real_t z =  ( (_len-_center_len)/2.f*sin(torads(back_sweep))+_clamp )/2.f;
    addBody(mass, _bar_center, x, y, z);
}

void Handlebar::createBarRasie(real_t mass)
{
     real_t radius = _clamp/2.f;
     real_t up_sweep = torads(25.f);
     real_t len = _raise / sin( up_sweep );
    _bar_rasie_left = new MyCylinder(radius, len, radius, MyCylinder::AroundType::X);
    _bar_rasie_left->color(0, 0, 255);
    real_t x = -(_center_len/2.f+len/2.f);
    real_t y = _bar_center->origin().y + _raise/2.f;
    real_t z =  _bar_center->origin().z;
    addBody(mass/2.f, _bar_rasie_left, x, y, z, 0.f, 0.f, -up_sweep);

   _bar_rasie_rigth = new MyCylinder(radius, len, radius, MyCylinder::AroundType::X);
   _bar_rasie_rigth->color(0, 0, 255);
   x = -x;
   addBody(mass/2.f, _bar_rasie_rigth, x, y, z, 0.f, 0.f, up_sweep);
   _rasie_len = len;
}

void Handlebar::createBarSide(real_t mass, real_t back_sweep, real_t up_sweep)
{
    real_t len = (_len - _center_len-_rasie_len)/2.f;
     real_t radius = _clamp/2.f;
    _bar_left = new MyCylinder(radius, len, 2.f, MyCylinder::AroundType::X);
    _bar_left->color(255, 0, 0);
    real_t x = _bar_rasie_left->origin().x - _rasie_len/2.f- len/2.f;
    int val = len*sin(torads(up_sweep));
    real_t y = _bar_rasie_left->origin().y + _raise/2.f + len/2.f*sin(torads(up_sweep));
    real_t z =  _bar_rasie_left->origin().z - len/2.f*sin(torads(back_sweep));
    addBody(mass/2.f, _bar_left, x, y, z, -torads(back_sweep), 0.f, -torads(up_sweep));

   _bar_right = new MyCylinder(2.f, len, radius, MyCylinder::AroundType::X);
   _bar_right->color(255, 0, 0);
   x = -x;
   addBody(mass/2.f, _bar_right, x, y, z, torads(back_sweep), 0.f, torads(up_sweep));

}


