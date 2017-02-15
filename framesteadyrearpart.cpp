#include "framesteadyrearpart.h"
#include "mybox.h"
#include "shox.h"

FrameSteadyRearPart::FrameSteadyRearPart(const PositionInfo& origin, real_t mass, real_t bl, real_t ll, real_t rl, real_t axis, real_t tyre_width)
    :MyCompoundBody(origin, mass)
    ,_bl(bl)
    ,_ll(ll)
    ,_rl(rl)
    ,_axis(axis)
    ,_tyre_width(tyre_width)
{
    calcGeometry();
    createLeft();
    createBottom();
    createRight();  
}

std::tuple<PositionInfo, MyBox*, MyBox*>
FrameSteadyRearPart::setupLinkPoint(real_t x, real_t y, real_t width, PointBase base, bool is_in)
{
    real_t x0, y0;
    real_t z0 =  is_in ? width/2.f+0.5f : width/2.f;
    if(base == BASE_TOP)
    {
        PositionInfo o = _lt_out->origin();
        x0 = o.x + _ll/2.f*cos(o.roll);
        y0 = o.y + _ll/2.f*sin(o.roll);
        return setupLinkPoint_i(x, -y, PositionInfo(x0, y0,z0), is_in);
    }

    if( base == BASE_BOTTOM)
    {
        PositionInfo o = _bt_out->origin();
        x0 = o.x + _bl/2.f*cos(o.roll);
        y0 = o.y;
        return setupLinkPoint_i(x, y, PositionInfo(x0, y0,z0), is_in);
    }

    if(base == BASE_TOP_EXTEN)
    {
        PositionInfo o = _lt_out->origin();
         x0 = o.x + _ll/2.f*cos(o.roll);
         y0 = o.y + _ll/2.f*sin(o.roll);;
         y = x*sin(o.roll);
         x = x*cos(o.roll);
         return setupLinkPoint_i(x, y, PositionInfo(x0, y0,z0, 0, 0, o.roll), is_in);
    }
    return std::make_tuple(PositionInfo(), nullptr, nullptr);
}

///@return link out pos, link in pos, out linker, in linker
std::tuple<PositionInfo, MyBox*, MyBox*>
FrameSteadyRearPart::setupLinkPoint_i(real_t x, real_t y, const PositionInfo& origin, bool is_in)
{
    real_t x0 = origin.x;
    real_t y0 = origin.y;
    real_t z0 =  origin.z;

    real_t roll = 0.f;
    if(origin.roll > 0.f)
        roll = origin.roll;
    else
    {
        if(x>0.f)
            roll = atan(y/x);
    }

    real_t x1 = x0 + x/2.f;
    real_t y1 = y0 + y/2.f;

    PositionInfo link_pos_out(x1, y1, z0, origin.yaw, origin.pitch, roll);
    if( abs(x) >0.f)
    {
        if(is_in)
        {
             MyBox* linker_out = new MyBox(x, 1.f, 3.f);
             this->addBody(linker_out, link_pos_out, 0.05f );
             PositionInfo link_pos_in(x1, y1, -z0, 0.f, 0.f, roll);
             MyBox* linker_in = new MyBox(x, 1.f, 3.f);
             this->addBody(linker_in, link_pos_in, 0.05f );
             return std::make_tuple(link_pos_out,  linker_out, linker_in);
        }
        else
        {
            MyBox* linker = new MyBox(x, z0*2.f, 3.f);
            this->addBody(linker, PositionInfo(x1, y1, 0.f), 0.05f );
            return std::make_tuple(link_pos_out,  linker, nullptr);
        }
    }

    return std::make_tuple(link_pos_out,  nullptr, nullptr);
}

void FrameSteadyRearPart::calcGeometry()
{
    _TOPA = acos( (_ll*_ll + _rl*_rl - _bl*_bl) /(2*_ll*_rl) ); //yu xian ding li
    _LEFTA = acos( (_ll*_ll + _bl*_bl - _rl*_rl) /(2*_ll*_bl) ); //yu xian ding li
    _RIGHTA = acos( (_bl*_bl + _rl*_rl - _ll*_ll) /(2*_bl*_rl) ); //yu xian ding li

    if(_RIGHTA > MY_PI/2.f)
    {
        _rectangle_l = _ll * cos( _LEFTA );
        _rectangle_diagonal = _ll;
    }
    else
    {
        _rectangle_l = _bl;
        _rectangle_diagonal = _bl/cos(_LEFTA);
    }

    _rectangle_w = _rectangle_diagonal * sin( _LEFTA);
}

void FrameSteadyRearPart::createBottom()
{
    _bt_out = new MyBox(_bl, 2.f, 3.f);
    _bt_out->color(255, 255, 0);
    _bt_in = new MyBox(_bl, 2.f, 3.f);
    _bt_in->color(255, 255, 0);

    real_t x = -(_rectangle_l/2.f - _bl/2.f);
    real_t y = -(_rectangle_w/2.f);
    real_t yaw = asin( (_axis/2.f-_tyre_width/2.f) / _bl);
    real_t z = _tyre_width/2.f + 2.f/2+ _bl/2.f * sin(yaw);

    addBody(0.3f,_bt_out, x, y, z, yaw);
    addBody(0.3f,_bt_in, x, y, -z, -yaw);
}

void FrameSteadyRearPart::createLeft()
{
    _lt_out = new MyBox(_ll, 2.f, 3.f);
    _lt_out->color(0, 255, 0);

    _lt_in = new MyBox(_ll, 2.f, 3.f);
    _lt_in->color(0, 255, 0);

    real_t x = 0.f - (_rectangle_diagonal/2.f-_ll/2.f)*cos(_LEFTA);
    real_t y = 0.f - (_rectangle_diagonal/2.f-_ll/2.f)*sin(_LEFTA);;
    real_t yaw = asin( (_axis/2.f-_tyre_width/2.f) / _ll);
    real_t z = _tyre_width/2.f + 2.f/2+_ll/2.f * sin(yaw);
    real_t roll = _LEFTA;
    addBody(0.3f,_lt_out, x, y, z, yaw, 0, roll);
    addBody(0.3f,_lt_in, x, y, -z, -yaw, 0, roll);
}

void FrameSteadyRearPart::createRight()
{
    _rt_out = new MyBox(_rl, 1.5f, 2.f);
    _rt_out->color(0, 255, 255);

    _rt_in = new MyBox(_rl, 1.5f, 2.f);
    _rt_in->color(0, 255, 255);

    real_t x = _bt_out->origin().x + _bl/2.f - _rl/2.f*cos(_RIGHTA);
    real_t y = _bt_out->origin().y + _rl/2.f*sin(_RIGHTA);
    real_t z = _tyre_width/2.f +1.5f/2.f;
    real_t roll = _TOPA+_LEFTA;
    addBody(0.3f,_rt_out, x, y, z, 0, 0, roll);
    addBody(0.3f,_rt_in, x, y, -z, 0, 0, roll);
}
