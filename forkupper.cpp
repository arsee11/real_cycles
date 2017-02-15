#include "forkupper.h"
#include "mybox.h"
#include "mycylinder.h"

#include <GL/gl.h>

ForkUpper::ForkUpper(real_t mass, real_t  travel, real_t width, real_t steer_len)
    :MyCompoundBody(mass)
{
    real_t cmass = mass/4;
    real_t crown_height = 4.f;
    _len = width+8.f;
    _width = 4.f;
    _height =  crown_height + travel + steer_len;

    _left_tube = new MyCylinder(1.8f, travel, 1.8f);
    _left_tube->color(0,255,0);
    addBody( cmass, _left_tube, -(width/2.f+1.8f), -(_height/2.f-travel/2.f), 0.f);

    _right_tube = new MyCylinder(1.8f, travel, 1.8f);
    _right_tube->color(0, 255, 0);
   addBody(cmass,  _right_tube,  width/2.f+1.8f, -(_height/2.f-travel/2.f), 0.f);

    _crown = new MyBox(width+8.f, crown_height, crown_height);
    _crown->color(255,0,0);
    addBody(cmass,_crown, 0.f, (travel+crown_height/2.f)-_height/2.f, 0.f);

    _streer = new MyCylinder(1.5f, steer_len, 1.5f);
    _streer->color(0, 0, 255);
    addBody(cmass,_streer, 0.f, _height/2.f-steer_len/2.f, 0.f);
}

