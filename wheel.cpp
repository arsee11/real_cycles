#include "wheel.h"
#include "mycylinder.h"


Wheel::Wheel(const PositionInfo &pos, real_t mass, real_t size_inch, real_t width_inch, real_t axis_len, real_t axis_diameter)
    :MyCompoundBody(mass)
    ,_size_inch(size_inch)
    ,_width_inch(width_inch)
    ,_axis_len(axis_len)
    ,_axis_diameter(axis_diameter)
{
    _width_cm = width_inch*2.54;
    _size_cm = size_inch*2.54;
    _wheel = new MyCylinder(_size_cm/2.f, _width_cm, _size_cm/2.f, MyCylinder::AroundType::Z);
    _wheel->color(0, 255, 0);
    this->addBody(mass*0.8, _wheel);

    real_t axis_radius=_axis_diameter/2.f;
    real_t w = (_axis_len-_width_cm)/2.f;
    _axis_body_in = new MyCylinder(axis_radius, w, axis_radius, MyCylinder::AroundType::Z);
    _axis_body_in->color(255,0,0);
    this->addBody(mass*0.1, _axis_body_in, 0, 0, -(_width_cm/2.f+w/2.f));

    _axis_body_out = new MyCylinder(axis_radius, w, axis_radius, MyCylinder::AroundType::Z);
    _axis_body_out->color(255,0,0);
    this->addBody(mass*0.1, _axis_body_out, 0, 0,  _width_cm/2.f+w/2.f);

    this->create(pos);
}
