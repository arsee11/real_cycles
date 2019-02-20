#ifndef CUBE_H
#define CUBE_H

#include "utils.h"

class Cube
{
public:
    Cube(){}
    Cube(real_t l);
    Cube(real_t l, real_t w, real_t h);

    void len(real_t val){ _len = val; }
    void width(real_t val){ _width = val; }
    void height(real_t val){ _height = val; }
    real_t len()const{ return _len; }
    real_t width()const{ return _width; }
    real_t height()const{ return _height; }

    //@param face 0-5, left up out right down in
    void color(int face,  const Color& color);

    void draw(real_t x=0.f, real_t y=0.f, real_t z=0.f);

private:
    real_t _len=0.f, _width=0.f, _height=0.f;
    Color _colors[6];
};

#endif // CUBE_H
