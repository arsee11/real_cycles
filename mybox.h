#ifndef MYBOX_H
#define MYBOX_H

#include "myrigidbody.h"
#include "cube.h"

class MyBox: public MyRigidBody
{
public:
    enum Face{
        LEFT,
        UP,
        OUT,
        RIGHT,
        DWON,
        IN
    };

public:
    MyBox(real_t l, real_t w, real_t h, const PositionInfo& origin, btScalar mass);

    //ony init shape
    MyBox(real_t l, real_t w, real_t h);

    // MyPysicsBody interface
public:
    void render(const BodyTransInfo& );

    void color(int r, int g, int b)override;
    void color(Face face,  const Color& c){ _cube.color(face, c); }
    Cube cube() const override{ return Cube(_len, _width, _height);}


private:
      real_t _len=0.f, _width=0.f, _height=0.f;
      Cube _cube;
};

#endif // MYBOX_H
