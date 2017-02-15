#include "cylinder.h"
#include <GL/gl.h>
#include <QDebug>

#include "ring.h"

void tube_draw(real_t out_radius, real_t in_radius, real_t len)
{
    CylinderY c_out(out_radius, out_radius, len);
    CylinderY c_in(in_radius, in_radius, len);
    RingY r_top(out_radius, in_radius,len/2.f);
    RingY r_bottom(out_radius, in_radius,-len/2.f);

    glColor3f(1,0,0);
    c_out.draw();
    glColor3f(0,1,0);
    c_in.draw();
    glColor3f(0,0,1);
    r_top.draw();
    glColor3f(0,1,1);
   r_bottom.draw();
}

