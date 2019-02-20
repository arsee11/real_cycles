#ifndef MYCYLINDER_H
#define MYCYLINDER_H

#include "myrigidbody.h"



class MyCylinder : public MyRigidBody
{
public:
    enum AroundType{
        X,
        Y,
        Z
    };

public:
    MyCylinder(real_t base_radius, real_t height, real_t top_radius, const PositionInfo& origin, real_t mass=0.f, AroundType type=AroundType::Y);
    MyCylinder(real_t base_radius, real_t height, real_t top_radius, AroundType type=AroundType::Y);

    real_t height(){ return _height; }

private:
    real_t _base_radius=0.f;
    real_t _height=0.f;
    real_t _top_radius=0.f;
    real_t _mass=0.f;
    AroundType _around_type;

    // MyPhysicsBody interface
public:
    void render(const BodyTransInfo &info);
};

#endif // MYCYLINDER_H
