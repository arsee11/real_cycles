#include "mybox.h"
#include "mycylinder.h"
#include "pedal.h"

Pedal::Pedal(const PositionInfo& origin, real_t mass)
    :MyCompoundBody(origin, mass)
{
    real_t L= 10.f, W=10.f, H=2.f, l=2.f;
    real_t x=0.f, y=0.f, z=0.f;

    //pedal plane
    MyBox* plane = new MyBox(W, L-l, H);
    z = l/2.f;
    addBody(mass*4/5, plane, x, y, z);

    //pedal stem
    MyCylinder* stem = new MyCylinder(H/2.f, l, H/2.f, MyCylinder::Z);
    z = -(L/2.f-l/2.f);
    addBody(mass*4/5, stem, x, y, z);

    create(origin);
}
