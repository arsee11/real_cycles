#include "framefrontpart.h"
#include "mybox.h"
#include "mycylinder.h"
#include "shox.h"
#include <math.h>
#include <tuple>

static std::tuple<PositionInfo, MyCylinder *> createTube(real_t x0, real_t y0, real_t x1, real_t y1, real_t left_radius, real_t right_radius)
{
    real_t k = (y1-y0)/(x1-x0); //zhi xian xie lv
    real_t len = sqrt( (y1-y0)*(y1-y0) + (x1-x0)*(x1-x0)); //gou gu ding li
    MyCylinder* tube = new MyCylinder(left_radius, len, right_radius, MyCylinder::X);
    real_t angle = atan(k);
    real_t x = x1 - len/2.f * cos(angle);
    real_t y = y1 - len/2.f * sin(angle);

    return std::make_tuple(PositionInfo(x, y, 0, 0, 0, angle), tube);
}

FrameFrontPart::FrameFrontPart(const PositionInfo &origin, real_t mass
	,real_t HTL, real_t HTA, real_t ETT, real_t STL, real_t STA
    ,real_t REACH, real_t BBH, real_t SOH, real_t STACK , real_t ASTA, real_t ASTL
)
    :MyCompoundBody(origin, mass)
    ,_HTL   (HTL)
    ,_HTA    (HTA)
    ,_ETT    (ETT)
    ,_STL     (STL)
    ,_STA     (STA)
    ,_REACH	(REACH)
    ,_BBH	    (BBH)
    ,_SOH	     (SOH)
    ,_STACK	 (STACK)
    ,_ASTA (ASTA)
    ,_ASTL(ASTL)
{
    _rectangle_l = _ETT + cos(torads(_HTA))*_HTL;
    _rectangle_w = _STACK;
    createHeadTube();
    createBB();
    createSeatTube();
    createTopTube();
    createBottomTube();
}

void FrameFrontPart::createHeadTube()   
{
    _ht = new MyCylinder(_ht_bottom_r, _HTL, _ht_top_r, MyCylinder::AroundType::Y);
    _ht->color(0, 255, 0);
    real_t htar = torads(_HTA);
    real_t ht_x = _rectangle_l/2.f - (_HTL/2.f)*cos( htar);
    real_t ht_y = _rectangle_w/2.f - _HTL/2.f*sin( htar );
    real_t roll =  MY_PI/2.f - htar;
    addBody(_ht_mass, _ht, ht_x, ht_y, 0.f, 0.f, 0.f, roll);
}


void FrameFrontPart::createSeatTube()
{
     real_t x;
    real_t y;
    real_t roll;
    real_t star = torads(_STA);
    if(-0.00000001f<_ASTA && _ASTA< 0.00000001)
    {
         _st = new MyCylinder(_st_r, _STL, _st_r, MyCylinder::AroundType::Y);
        x = _bb->origin().x - _STL/2.f * cos(star);
        y = _bb->origin().y + _STL/2.f * sin(star);
        roll = MY_PI/2.f - star;
    }
    else
    {
        _st = new MyCylinder(_st_r, _ASTL, _st_r, MyCylinder::AroundType::Y);
        real_t astar = torads(_ASTA);
        real_t x_stl_top = -(_rectangle_l/2.f - _STL * cos(star));
        real_t y_stl_top = _STL * sin(star) - _rectangle_w/2.f;
        x = x_stl_top + _ASTL/2.f * cos(astar);
        y = y_stl_top  - _ASTL/2.f * sin(astar);
        roll = MY_PI/2.f - astar;

        //bb 到 actual seat tube 的 tube
        real_t x0 = _bb->origin().x;
        real_t y0 = _bb->origin().y;
        real_t x1 = x + _ASTL/2.f* cos( astar);
        real_t y1 =y  -  _ASTL/2.f* sin(astar);
        PositionInfo pos;
        std::tie(pos, _st_bb_t) = createTube(x0, y0, x1, y1, _bb_r, _bb_r);
        _st_bb_t->color(0, 255, 0);
         addBody( _st_bb_t, pos);
    }
    _st->color(0, 255, 0);
    addBody(0.f, _st, x, y, 0, 0, 0, roll);
}

void FrameFrontPart::createTopTube()
{
    real_t star;
    if(-0.00000001f<_ASTA && _ASTA< 0.00000001)
        star = torads(_STA);
    else
        star = torads(_ASTA);

    real_t ttl_tmp = sqrt( _REACH*_REACH + (_STACK-_SOH+_BBH)*(_STACK-_SOH+_BBH) ); //gou gu ding li
    real_t angle_tt = acos( _REACH/ttl_tmp);
    real_t angle_tt_st = MY_PI - angle_tt - star;
    real_t ttl = _ETT/sin(angle_tt_st) * sin(star); //zheng xian ding li
    _tt = new MyCylinder(_tt_r, ttl, _tt_r, MyCylinder::AroundType::X);
    _tt->color(0, 255, 255);

    real_t x = _ETT/2.f - ttl/2.f*cos(angle_tt)  ;
    real_t y = _STACK/2.f - ttl/2.f*sin(angle_tt) - _tt_r;
    real_t z = 0.f;
    real_t roll = angle_tt;
    addBody(0.f, _tt, x, y, z, 0, 0, roll);
}

void FrameFrontPart::createBottomTube()
{
    real_t star = torads(_STA);
    real_t x0 = _bb->origin().x;
    real_t y0 = _bb->origin().y;
    real_t htar = torads(_HTA);
    real_t x1 = _ht->origin().x + (_HTL/2.f-_ht_bottom_r*2.f)* cos( htar);
    real_t y1 = _ht->origin().y  -  (_HTL/2.f-_bt_r*2.f)* sin(htar);
    PositionInfo pos;
    std::tie(pos, _bt) = createTube(x0, y0, x1, y1, _bt_r, _bt_r );
    _bt->color(0, 255, 255);
    addBody(_bt, pos, 0.f);
}

void FrameFrontPart::createBB()
{
    _bb = new MyCylinder(_bb_r, _bb_len, _bt_r, MyCylinder::AroundType::Z);
    _bb->color(255, 255, 0);
    real_t offset = _rectangle_w / tan(torads(_STA));
    real_t bb_x = -(_rectangle_l/2.f -offset);
    real_t bb_y = -(_rectangle_w/2.f);
    addBody(_bb_mass, _bb,  bb_x, bb_y);
}

///@return link out pos
PositionInfo FrameFrontPart::setupLinkPoint(real_t x, real_t y, PointBase base)
{
    real_t x0 ;
    real_t y0 ;
    real_t x1;
    real_t y1;
    PositionInfo origin;
    if(base == PointBase::BASE_BB)
    {
        PositionInfo origins = _st->origin();
        int xs0 = origins.x + (_STL/2.f)*cos(torads(_STA));
        origin = _bb->origin();
        x0 = origin.x;
        y0 = origin.y;
        x1 = x0-2;
        y1 = y0+y;
    }
    else if(base == PointBase::BASE_SEAT)
    {
        origin = _st->origin();
        x0 = origin.x + (y-_STL/2.f)*cos(torads(_STA));
        y0 = origin.y- (y-_STL/2.f)*sin(torads(_STA));
        x1 = x0+x;
        y1 = y0 ;

    }
    else if(base == PointBase::BASE_TOP)
    {
        origin = _tt->origin();
        x0 = origin.x + (x-_tt->height()/2.f)*cos(origin.roll);
        y0 = origin.y+ (x-_tt->height()/2.f)*sin(origin.roll);
        x1= x0;
        y1= y0 - y;
    }
    else if(base == PointBase::BASE_BOTTOM)
    {
        origin = _bt->origin();
        x0 = origin.x + (x-_bt->height()/2.f)*cos(origin.roll);
        y0 = origin.y+ (x-_bt->height()/2.f)*sin(origin.roll);
        x1= x0;
        y1= y0 + y;       
    }
    else
         return PositionInfo();

   return PositionInfo(x1,  y1, 0);
}

PositionInfo FrameFrontPart::getBBPosition() const
{
    return _bb->origin();
}

PositionInfo FrameFrontPart::getHTPosition() const
{
    return _ht->origin();
}


