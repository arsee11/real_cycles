#ifndef MYCONVEXHULLBODY_H
#define MYCONVEXHULLBODY_H

#include "myrigidbody.h"



class MyConvexHullBody:public MyRigidBody
{
public:
    MyConvexHullBody(const PositionInfo& origin, real_t mass, const Vex* vexs, int size_vexs);
    MyConvexHullBody(const Vex vexs[], int size_vexs);

    // MyPhysicsBody interface
public:
    void render(const BodyTransInfo &info);

};

#endif // MYCONVEXHULLBODY_H
