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
    PositionInfo _link_pos_out;
    MyBox* _linker_out=nullptr;
    MyBox* _linker_in=nullptr;
};

class FrontBBPoint:public LinkerPoint
{
public:
    template< class FrontPart>
    PositionInfo setup(FrontPart* p){
        Param pr = getParam();
        std::tie(_link_pos_out, _linker_out, _linker_in)
                = p->setupLinkPoint(pr.x, pr.y, pr.width, FrontPart::BASE_BB, pr.is_in);

        PositionInfo pos = _link_pos_out;
        pos.z = pr.width/2;
        return pos;
   }
};

class FrontSeatPoint:public LinkerPoint
{
public:
    template< class FrontPart>
    PositionInfo setup(FrontPart* p){
        Param pr = getParam();
        std::tie(_link_pos_out, _linker_out, _linker_in)
                = p->setupLinkPoint(pr.x, pr.y, pr.width, FrontPart::BASE_SEAT, pr.is_in);

        PositionInfo pos = _link_pos_out;
        pos.z = pr.width/2;
        return pos;
   }
};

class FrontBottomPoint:public LinkerPoint
{
public:
    template< class FrontPart>
    PositionInfo setup(FrontPart* p){
        Param pr = getParam();
        std::tie(_link_pos_out, _linker_out, _linker_in)
                = p->setupLinkPoint(pr.x, pr.y, pr.width, FrontPart::BASE_BOTTOM, pr.is_in);

        PositionInfo pos = _link_pos_out;
        pos.z = pr.width/2;
        return pos;
   }
};

class RearBottomPoint:public LinkerPoint
{
public:
    template< class RearPart>
    PositionInfo setup(RearPart* p){
        Param pr = getParam();
         pr.width = p->tyre_width();
        std::tie(_link_pos_out, _linker_out, _linker_in)
                = p->setupLinkPoint(pr.x, pr.y, pr.width, RearPart::BASE_BOTTOM, pr.is_in);

        PositionInfo pos = _link_pos_out;
        pos.z = pr.width/2;
        return pos;
   }
};

class RearUpPoint:public LinkerPoint
{
public:
    template< class RearPart>
    PositionInfo setup(RearPart* p){
        Param pr = getParam();
        pr.width = p->tyre_width();
        std::tie(_link_pos_out, _linker_out, _linker_in)
                = p->setupLinkPoint(pr.x, pr.y, pr.width, RearPart::BASE_TOP, pr.is_in);

        PositionInfo pos = _link_pos_out;
        pos.z = pr.width/2.f;
        return pos;
   }
};

class RearTopExtenPoint:public LinkerPoint
{
public:
    template< class RearPart>
    PositionInfo setup(RearPart* p){
        Param pr = getParam();
        std::tie(_link_pos_out, _linker_out, _linker_in)
                = p->setupLinkPoint(pr.x+1, pr.y, pr.width, RearPart::BASE_TOP_EXTEN, pr.is_in);

        PositionInfo pos(_link_pos_out.x + cos(_link_pos_out.roll)*(pr.x/2.f)-1.f
                         ,_link_pos_out.y + sin(_link_pos_out.roll)*(pr.x/2.f)
                         ,pr.width/2.f
                         ,0.f, 0.f, _link_pos_out.roll);
        return pos;
   }
};

#endif // LINKERPOINT_H
