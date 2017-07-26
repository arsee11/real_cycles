#ifndef PUMPTRACK_H
#define PUMPTRACK_H

#include "myrigidbody.h"



class PumpTrack: public MyRigidBody
{
public:
    PumpTrack(const PositionInfo& origin);

    // MyPhysicsBody interface
public:
    void render(const BodyTransInfo &info);
};

#endif // PUMPTRACK_H
