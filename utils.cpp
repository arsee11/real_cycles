#include "mycylinder.h"
#include "utils.h"
#include <math.h>

std::tuple<PositionInfo, MyCylinder *> createTube(real_t x0, real_t y0, real_t x1, real_t y1, real_t left_radius, real_t right_radius)
{
    real_t k = (y1-y0)/(x1-x0); //zhi xian xie lv
    real_t len = sqrt( (y1-y0)*(y1-y0) + (x1-x0)*(x1-x0)); //gou gu ding li
    MyCylinder* tube = new MyCylinder(left_radius, len, right_radius, MyCylinder::X);
    real_t angle = atan(k);
    real_t x = x1 - len/2.f * cos(angle);
    real_t y = y1 - len/2.f * sin(angle);

    return std::make_tuple(PositionInfo(x, y, 0, 0, 0, angle), tube);
}
