#ifndef MYTUBEBODY_H
#define MYTUBEBODY_H

#include "mycompoundbody.h"
#include <tuple>

class MyTubeBody : public MyCompoundBody
{
public:
    MyTubeBody(real_t out_radius, real_t in_radius, real_t len, const PositionInfo& origin, real_t mass)
        :MyTubeBody(out_radius, in_radius, out_radius, in_radius, len, origin, mass)
    {}

    MyTubeBody(real_t out_radius, real_t in_radius, real_t len);

    MyTubeBody(real_t out_radius_top, real_t in_radius_top
        ,real_t out_radius_bottom, real_t in_radius_bottom
        ,real_t len, const PositionInfo& origin, real_t mass);

    MyTubeBody(real_t out_radius_top, real_t in_radius_top
        ,real_t out_radius_bottom, real_t in_radius_bottom
        ,real_t len);

public:
    void render(const BodyTransInfo &info);

private:
    real_t _outr_t, _inr_t, _outr_b, _inr_b, _len;
    int buildVertexs(Vex **vexs);
};

#endif // MYTUBEBODY_H
