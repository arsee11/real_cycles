#ifndef FRAMEREARPART_H
#define FRAMEREARPART_H

#include "mybox.h"
#include "mycompoundbody.h"


class Shox;

//for steady rear triangle, such as VVP
class FrameSteadyRearPart : public MyCompoundBody
{
public:
    struct Param{
        real_t mass;
        real_t bl;
        real_t ll;      ///left tube length;
        real_t rl;
        real_t axle;
        real_t tyre_width;

    };

    enum PointBase{
        BASE_TOP,                ///the top angle
        BASE_BOTTOM,        ///the bottom angle
        BASE_TOP_EXTEN     /// the top extension line
    };

public:
    FrameSteadyRearPart(const PositionInfo& origin, const Param& p)
        :FrameSteadyRearPart(origin, p.mass, p.bl, p.ll, p.rl, p.axle, p.tyre_width)
    {
    }

    FrameSteadyRearPart(const PositionInfo& origin, real_t mass
                        , real_t bl      //bottom tube length
                        , real_t ll       //left tube length
                        , real_t rl    //right tube length
                        , real_t axis //axis length
                        , real_t tyre_width // tyre width
    );

    void create(){ this->createSelf();}
    Cube cube()const override{ return Cube(_rectangle_l, _axis, _rectangle_w); }

    PositionInfo setupLinkPoint(real_t x, real_t y, PointBase base);

    real_t tyre_width(){ return _tyre_width; }

    PositionInfo getWheelSetupLocalPosition()const{
        PositionInfo o = this->origin();
        real_t x= _bt_in->origin().x - _bl/2.f, y= _bt_in->origin().y, z=0.f;
        return PositionInfo(x, y, z, o.yaw, o.pitch, o.roll);
    }

    PositionInfo toWorldPosition(const PositionInfo &origin) const{
        PositionInfo thiso = this->origin();
        real_t len = pow( pow(origin.x, 2)+pow( origin.y, 2), 0.5 );
        real_t absy = absf(origin.y), absx=absf(origin.x);
        real_t tmp = absy/absx;
        real_t a = atan( tmp );
        real_t x=0.f, y=0.f;
        if( origin.x>0 && origin.y>0)
        {
            real_t a1 = a- (-thiso.roll);
            x = len * cos( a1 );
            y = len* sin(a1);
        }
        else if(origin.x>0 && origin.y<0)
        {
            real_t a1 = a+ (-thiso.roll);
            x = len * cos(a1);
            y =- len* sin(a1);
        }
        else if(origin.x<0 && origin.y<0)
        {
            real_t a1 = a - (-thiso.roll);
            x = -len * cos(a1);
            y = -len* sin(a1);

        }
        x = thiso.x + x;
        y=thiso.y+y;
        real_t z = thiso.z;
        return PositionInfo(x, y, z);
     }
private:
    void createBottom();
    void createLeft();
    void createRight();
    void calcGeometry();
    PositionInfo setupLinkPoint_i(real_t x, real_t y, const PositionInfo &origin, bool is_in);


private:
    real_t _bl;
    real_t _LEFTA;
    real_t _RIGHTA;
    real_t _TOPA;
    real_t _ll; // left tube length;
    real_t _rl;
    real_t _tyre_width;
    real_t _axis;
    real_t _rectangle_l;
    real_t _rectangle_w;
    real_t _rectangle_diagonal;

    MyBox* _bt_out=nullptr;  //bottom tube outer
    MyBox* _lt_out =nullptr;
    MyBox* _rt_out = nullptr;

    MyBox* _bt_in=nullptr;  //bottom tube inner
    MyBox* _lt_in =nullptr;
    MyBox* _rt_in = nullptr;

    MyBox* _b_link_point_out = nullptr;
    MyBox* _b_link_point_in= nullptr;
    PositionInfo _b_link_pos_out;
    PositionInfo _b_link_pos_in;

    MyBox* _u_link_point_out = nullptr;
    MyBox* _u_link_point_in= nullptr;
    PositionInfo _u_link_pos_out;
    PositionInfo _u_link_pos_in;

};

#endif // FRAMEREARPART_H
