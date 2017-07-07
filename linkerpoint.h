#ifndef LINKERPOINT_H
#define LINKERPOINT_H

#include "mybox.h"
#include "utils.h"

class LinkerPoint
{
public:
    struct Param{
        Param(real_t xi, real_t yi, real_t widthi)
            :x(xi)
            ,y(yi)
            ,width(widthi)
        {
        }

        Param(real_t xi, real_t yi, real_t widthi, bool is_ini)
            :x(xi)
            ,y(yi)
            ,width(widthi)
            ,is_in(is_ini)
        {
        }

        real_t x, y, width;
        bool is_in=true;
    };

public:
    virtual ~LinkerPoint(){}

    virtual Param getParam()=0;

protected:
    PositionInfo _link_pos;
};

class FrontBBPoint:public LinkerPoint
{
public:
    template< class FrontPart>
    PositionInfo setup(FrontPart* p){
        Param pr = getParam();
        _link_pos  = p->setupLinkPoint(pr.x, pr.y, FrontPart::BASE_BB);
        return _link_pos;
   }
};

class FrontSeatPoint:public LinkerPoint
{
public:
    template< class FrontPart>
    PositionInfo setup(FrontPart* p){
        Param pr = getParam();
         _link_pos  = p->setupLinkPoint(pr.x, pr.y, FrontPart::BASE_SEAT);
        return _link_pos;
   }
};

class FrontBottomPoint:public LinkerPoint
{
public:
    template< class FrontPart>
    PositionInfo setup(FrontPart* p){
        Param pr = getParam();
         _link_pos = p->setupLinkPoint(pr.x, pr.y, FrontPart::BASE_BOTTOM);
        return _link_pos;
   }
};

class RearBottomPoint:public LinkerPoint
{
public:
    template< class RearPart>
    PositionInfo setup(RearPart* p){
        Param pr = getParam();
        pr.width = p->tyre_width();
        _link_pos = p->setupLinkPoint(pr.x, pr.y, RearPart::BASE_BOTTOM);
        return _link_pos;
   }
};

class RearUpPoint:public LinkerPoint
{
public:
    template< class RearPart>
    PositionInfo setup(RearPart* p){
        Param pr = getParam();
        pr.width = p->tyre_width();
        _link_pos = p->setupLinkPoint(pr.x, pr.y, RearPart::BASE_TOP);
        return _link_pos;
   }
};

class RearTopExtenPoint:public LinkerPoint
{
public:
    template< class RearPart>
    PositionInfo setup(RearPart* p){
        Param pr = getParam();
         _link_pos  = p->setupLinkPoint(pr.x+1, pr.y, RearPart::BASE_TOP_EXTEN);

        PositionInfo pos(_link_pos.x + cos(_link_pos.roll)*(pr.x/2.f)-1.f
                         ,_link_pos.y + sin(_link_pos.roll)*(pr.x/2.f)
                         ,pr.width/2.f
                         ,0.f, 0.f, _link_pos.roll);
        return _link_pos;
   }
};

#endif // LINKERPOINT_H
