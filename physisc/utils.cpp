#include "utils.h"
#include <math.h>
#include <LinearMath/btVector3.h>



std::tuple<real_t, real_t, real_t, real_t> calcPoint_x2y2(real_t x1, real_t y1, real_t k, real_t b2, real_t n)
{
    real_t a = 1+k;
    real_t b = -2*x1 + 2*k*b;
    real_t c = pow(x1, 2) + pow(b, 2) + pow(y1, 2) - 2*k*y1*x1 - 2*b*y1 - pow(n, 2);
    real_t x2 = (-b + pow(  pow(b, 2)-4*a*c, 0.5 ) ) /2*a;
    real_t y2 = k*x2 + b;

    real_t x22 = (-b - pow(  pow(b, 2)-4*a*c, 0.5 ) ) /2*a;
    real_t y22 = k*x22 + b;

    return std::make_tuple(x2, y2, x22, y22);
}

real_t Vex::distance(const Vex &another) const
{
     return btVector3(this->x, this->y, this->z).distance( btVector3(another.x, another.y, another.z));
}
