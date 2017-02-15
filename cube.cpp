#include "cube.h"
#include <GL/gl.h>
#include <exception>

Cube::Cube(real_t l, real_t w, real_t h)
    :_len(l)
    ,_width(w)
    ,_height(h)
{
    //draw();
}

void Cube::color(int face, const Color &c)
{
    if( face <0 || face > 5)
        throw std::exception();

    _colors[face] = c;
}

Cube::Cube(real_t l)
    :_len(l)
    ,_width(l)
    ,_height(l)
{
    //draw();
}

void Cube::draw( real_t x, real_t y, real_t z)
{
    real_t ll = _len/2;
    real_t hh = _height/2;
    real_t ww = _width/2;
    real_t Ax = x-ll, Ay=y+hh, Az=z+ww;
    real_t Bx=Ax, By=Ay,Bz=z-ww;
    real_t Cx=Ax, Cy=y-hh, Cz=Bz;
    real_t Dx=Ax, Dy=Cy, Dz=Az;
    real_t Ex=x+ll, Ey=Ay, Ez=Az;
    real_t Fx=Ex, Fy=Ey, Fz=Bz;
    real_t Gx=Ex, Gy=Cy, Gz=Fz;
    real_t Hx=Ex, Hy=Dy, Hz=Ez;
    glBegin(GL_QUADS);
    //glBegin(GL_LINES);
    //left
    glColor3f(_colors[0].r/255.f,  _colors[0].g/255.f, _colors[0].b/255.f);
    glVertex3f(Ax, Ay, Az);
    glVertex3f(Bx, By, Bz);
    glVertex3f(Cx, Cy, Cz);
    glVertex3f(Dx, Dy, Dz);

    //up
    glColor3f(_colors[1].r/255.f,  _colors[1].g/255.f, _colors[1].b/255.f);
    glVertex3f(Ax, Ay, Az);
    glVertex3f(Ex, Ey, Ez);
    glVertex3f(Fx, Fy, Fz);
    glVertex3f(Bx, By, Bz);

    //out
    glColor3f(_colors[2].r/255.f,  _colors[2].g/255.f, _colors[2].b/255.f);
    glVertex3f(Ax, Ay, Az);
    glVertex3f(Dx, Dy, Dz);
    glVertex3f(Hx, Hy, Hz);
    glVertex3f(Ex, Ey, Ez);

    //right
    glColor3f(_colors[3].r/255.f,  _colors[3].g/255.f, _colors[3].b/255.f);
    glVertex3f(Ex, Ey, Ez);
    glVertex3f(Hx, Hy, Hz);
    glVertex3f(Gx, Gy, Gz);
    glVertex3f(Fx, Fy, Fz);

    //down
    glColor3f(_colors[4].r/255.f,  _colors[4].g/255.f, _colors[4].b/255.f);
    glVertex3f(Dx, Dy, Dz);
    glVertex3f(Cx, Cy, Cz);
    glVertex3f(Gx, Gy, Gz);
    glVertex3f(Hx, Hy, Hz);

    //in
    glColor3f(_colors[5].r/255.f,  _colors[5].g/255.f, _colors[5].b/255.f);
    glVertex3f(Bx, By, Bz);
    glVertex3f(Fx, Fy, Fz);
    glVertex3f(Gx, Gy, Gz);
    glVertex3f(Cx, Cy, Cz);

    glEnd();
}
