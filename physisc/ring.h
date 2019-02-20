#ifndef RING_H
#define RING_H

#include "utils.h"
#include "cycles.h"
#include <math.h>

enum RingT
{
    RING_X,
    RING_Y,
    RING_Z,
};

template<enum RingT>
struct XYZR;

template<>
struct XYZR<RING_X>
{
    static real_t x(real_t radius, real_t height, real_t angle)
    {
        return height;
    }

    static real_t y(real_t radius, real_t height, real_t angle)
    {
        return radius * sin(angle);
    }

    static real_t z(real_t radius, real_t height, real_t angle)
    {
        return radius * cos(angle);
    }
};

template<>
struct XYZR<RING_Y>
{
    static real_t x(real_t radius, real_t height, real_t angle)
    {
        return radius * cos(angle);
    }

    static real_t y(real_t radius, real_t height, real_t angle)
    {
        return height;
    }

    static real_t z(real_t radius, real_t height, real_t angle)
    {
        return radius * sin(angle);
    }
};

template<>
struct XYZR<RING_Z>
{
    static real_t x(real_t radius, real_t height, real_t angle)
    {
        return radius * cos(angle);
    }

    static real_t y(real_t radius, real_t height, real_t angle)
    {
        return radius * sin(angle);
    }

    static real_t z(real_t radius, real_t height, real_t angle)
    {
        return height;
    }
};

template< class XYZ>
class Ring
{
public:
    Ring(real_t out_radius, real_t in_radius, real_t offset)
        :_out_radius(out_radius)
        ,_in_radius(in_radius)
        ,_offset(offset)
    {
    }
    void draw()
    {
        int constexpr slices = 60;
        Vex vexs[slices*2];
        build(vexs, slices);
        cycle_draw(vexs,  slices);
    }

    //sizeof vex >=slices*2
    void build(Vex vexs[], int slices)
    {
        real_t a= 2*MY_PI/slices;
         real_t angle=0.f;
        for( int i=0; i<slices*2; )
        {
            vexs[i] = Vex(XYZ::x(_in_radius,  _offset, angle)
                ,XYZ::y(_in_radius,  _offset, angle)
                ,XYZ::z(_in_radius,  _offset, angle)
            );
            i++;
           vexs[i] = Vex(XYZ::x(_out_radius,  _offset, angle)
               , XYZ::y(_out_radius,  _offset, angle)
               ,XYZ::z(_out_radius,  _offset, angle)
            );
            i++;
            angle += a;
        }
    }

protected:
    real_t _out_radius;
    real_t _in_radius;
    real_t _offset;
};

typedef Ring<XYZR<RING_X> > RingX;
typedef Ring<XYZR<RING_Y> > RingY;
typedef Ring<XYZR<RING_Z> > RingZ;

#endif // RING_H
