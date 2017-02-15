#ifndef UTILS_H
#define UTILS_H

#include <tuple>

typedef float real_t;

struct Color{
    Color(){}
    Color(int ir, int ig, int ib):r(ir),g(ig),b(ib){}
    int r=255;
    int g=255;
    int b=255;
};

struct Vex
{
    Vex(){}
    Vex(real_t ix, real_t iy, real_t iz)
        :x(ix),y(iy),z(iz)
    {}

    real_t x=0, y=0, z=0;
};

struct PositionInfo
{
    PositionInfo(){}
    PositionInfo(real_t ix, real_t iy, real_t iz, real_t iyaw=0.f,  real_t ipitch=0.f,real_t iroll=0.f)
        :x(ix)
        ,y(iy)
        ,z(iz)
        ,yaw(iyaw)
        ,pitch(ipitch)
        ,roll(iroll)
    {}

    real_t x=0;
    real_t y=0;
    real_t z=0;
    real_t yaw=0;
    real_t pitch=0;
    real_t roll=0;
};


real_t constexpr MY_PI = 3.141592653;
 int constexpr BOX_INDICES[36] = {
        0,1,2,
        3,2,1,
        4,0,6,
        6,0,2,
        5,1,4,
        4,1,0,
        7,3,1,
        7,1,5,
        5,4,7,
        7,4,6,
        7,2,3,
        7,6,2};

inline real_t todegrees(real_t rads){ return rads/MY_PI *180.0;}
inline real_t torads(int degrees){ return degrees/180.0 * MY_PI; }

class MyCylinder;

std::tuple<PositionInfo, MyCylinder*> createTube(real_t x0, real_t y0, real_t x1, real_t y1, real_t left_radius, real_t right_radius);

#endif // UTILS_H
