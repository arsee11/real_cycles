#ifndef CYLINDER_H
#define CYLINDER_H

#include "utils.h"
#include "cycles.h"
#include <math.h>

enum CylinderT
{
    CYLINDER_X,
    CYLINDER_Y,
    CYLINDER_Z,
};

template<enum CylinderT>
struct XYZ;

template<>
struct XYZ<CYLINDER_X>
{
    static real_t x(real_t radius, real_t height, real_t angle)
    {
        return -height/2.f;
    }

    static real_t y(real_t radius, real_t height, real_t angle)
    {
        return radius * sin(angle);
    }

    static real_t z(real_t radius, real_t height, real_t angle)
    {
        return radius * cos(angle);
    }

    static real_t x2(real_t radius, real_t height, real_t angle)
    {
        return -x(radius, height, angle);
    }

    static real_t y2(real_t radius, real_t height, real_t angle)
    {
        return y(radius, height, angle);
    }

    static real_t z2(real_t radius, real_t height, real_t angle)
    {
        return z(radius, height, angle);
    }
};

template<>
struct XYZ<CYLINDER_Y>
{
    static real_t x(real_t radius, real_t height, real_t angle)
    {
        return radius * cos(angle);
    }

    static real_t y(real_t radius, real_t height, real_t angle)
    {
        return -height/2.f;
    }

    static real_t z(real_t radius, real_t height, real_t angle)
    {
        return radius * sin(angle);
    }

    static real_t x2(real_t radius, real_t height, real_t angle)
    {
        return x(radius, height, angle);
    }

    static real_t y2(real_t radius, real_t height, real_t angle)
    {
        return -y(radius, height, angle);
    }

    static real_t z2(real_t radius, real_t height, real_t angle)
    {
        return z(radius, height, angle);
    }
};

template<>
struct XYZ<CYLINDER_Z>
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
        return -height/2.f;
    }

    static real_t x2(real_t radius, real_t height, real_t angle)
    {
        return x(radius, height, angle);
    }

    static real_t y2(real_t radius, real_t height, real_t angle)
    {
        return y(radius, height, angle);
    }

    static real_t z2(real_t radius, real_t height, real_t angle)
    {
        return -z(radius, height, angle);
    }
};


template< class XYZ>
class Cylinder
{
public:
    Cylinder(real_t radius1, real_t radius2, real_t height)
        :_radius1(radius1)
        ,_radius2(radius2)
        ,_height(height)
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
            vexs[i] = Vex(XYZ::x(_radius1, _height, angle)
                ,XYZ::y(_radius1, _height, angle)
                ,XYZ::z(_radius1, _height, angle)
            );
            i++;
           vexs[i] = Vex(XYZ::x2(_radius2, _height, angle)
               , XYZ::y2(_radius2, _height, angle)
               ,XYZ::z2(_radius2, _height, angle)
            );
            i++;
            angle += a;
        }
    }

protected:
    real_t _radius1;
    real_t _radius2;
    real_t _height;


};

typedef Cylinder<XYZ<CYLINDER_X> > CylinderX;
typedef Cylinder<XYZ<CYLINDER_Y> > CylinderY;
typedef Cylinder<XYZ<CYLINDER_Z> > CylinderZ;

void ring_draw(real_t out_radius, real_t in_radius);

#endif // CYLINDER_H
