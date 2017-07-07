#ifndef FRAMEFRONTPART_H
#define FRAMEFRONTPART_H

#include "mycompoundbody.h"

class MyCylinder;
class MyBox;
class Shox;


class FrameFrontPart : public MyCompoundBody
{
public:
    enum PointBase{
        BASE_TOP,
        BASE_BB,
        BASE_SEAT,
        BASE_BOTTOM
    };


    struct Param
    {
        real_t mass;
        real_t HTL;            //head tube length
        real_t HTA;            //head tube angle degrees
        real_t ETT;             //effective top tube
        real_t STL;             //seat tube length
        real_t STA;             //seat tube angle degrees
        real_t REACH;	    //reach
        real_t BBH;		   //BB height
        real_t SOH;		   //stand over height
        real_t STACK;		   //STACK
        real_t ASTA;           //actual seat tube angle degrees
        real_t ASTL;           //actual seat tube lenght

    };

public:
    FrameFrontPart(const PositionInfo&origin ,const Param& param)
        :FrameFrontPart(origin,param.mass, param.HTL, param.HTA,param.ETT
                        ,param.STL, param.STA, param.REACH, param.BBH, param.SOH, param.STACK
                        ,param.ASTA, param.ASTL)
    {
    }

    FrameFrontPart(const PositionInfo&origin //Geometry center position
                   , real_t mass                     //mass
                   , real_t HTL                         //head tube length
                   , real_t HTA                         //head tube angle degrees
                   , real_t ETT                         //effective top tube
                   , real_t STL                         //seat tube length
                   , real_t STA                         //effective seat tube angle degrees
                   , real_t REACH			//reach
                   , real_t BBH				//BB height
                   , real_t SOH				//stand over height
                   , real_t STACK			//STACK
                   , real_t ASTA =0.f    //actual seat tube angle degrees
                   ,real_t ASTL=0.f     //actual seat tube lenght
    );

    ///@param x, 当 base == BASE_BB 从右边为正; base==BASE_SEAT 右边为正; \n
    ///          base == BASE_BOTTOM BB原点为0点，向右为正; BASE_TOP seat tube 右边为0点; \n
    ///@param y, 当 base == BASE_BB 由BB原点为0点，向上为正; base==BASE_SEAT 由seat tube顶点向下; \n
    ///          base == BASE_BOTTOM 上边为正; base==BASE_TOP 下边为正
    ///@return link  position
   PositionInfo setupLinkPoint(real_t x, real_t y, PointBase base);

    void create(){ this->createSelf();}

    //BB position base on frame
    PositionInfo getBBPosition()const;

    //head tube position base on frame
    PositionInfo getHTPosition()const;

    real_t HTL()const { return _HTL; }
    real_t HTA()const { return _HTA; }

private:
    void createHeadTube();
    void createSeatTube();
    void createTopTube();
    void createBottomTube();
    void createBB();



    real_t _HTL;            //head tube length
    real_t _HTA;            //head tube angle degrees
    real_t _ETT;             //effective top tube
    real_t _STL;             //seat tube length
    real_t _STA;             //seat tube angle degrees
    real_t _ASTA;           //actual seat tube angle degrees
    real_t _ASTL;           //actual seat tube lenght
    real_t _REACH;	    //reach
    real_t _BBH;		   //BB height
    real_t _SOH;		   //stand over height
    real_t _STACK;		   //STACK

    real_t _rectangle_l, _rectangle_w;

    real_t _ht_top_r = 3.f, _ht_bottom_r=3.f;
    real_t _st_r = 2.f;
    real_t _tt_r = 2.f;
    real_t _bt_r = 3.f;
    real_t _bb_r = 2.f;
    real_t _bb_mass = 0.2f;
    real_t _ht_mass = 0.2f;
    real_t  _bb_len=7.3f;

    MyCylinder* _ht=nullptr;
    MyCylinder* _st=nullptr;
    MyCylinder* _tt=nullptr;
    MyCylinder* _bt=nullptr;
    MyCylinder* _bb=nullptr;
    MyCylinder* _st_bb_t=nullptr;
};

#endif // FRAMEFRONTPART_H
