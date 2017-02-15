#ifndef MYCOMPOUNDBODY_H
#define MYCOMPOUNDBODY_H

#include "mydiscretedynamicsworld.h"
#include "myphysicsbody.h"
#include <vector>

class MyCompoundBody : public MyPhysicsBody
{
protected:
    struct ChildBody{
        ChildBody(){}
        ChildBody(const PositionInfo& t, MyPhysicsBody* b, real_t m)
            :trans(t), body(b), mass(m)
        {}
        PositionInfo trans;
        MyPhysicsBody* body=nullptr;
        real_t mass = 0.f;
    };

    //ChildBody* getBody(MyPhysicsBody* b);

public:
    MyCompoundBody(const PositionInfo& origin, real_t mass);
    MyCompoundBody(real_t mass);
    virtual ~MyCompoundBody();
    void create(const PositionInfo& origin){
         _origin = origin;
         createSelf();
    }

    // MyPhysicsBody interface
public:
    //coordinat base the compound body's origin
     void addBody(real_t mass, MyPhysicsBody* body, real_t x=0, real_t y=0, real_t z=0, real_t yaw=0, real_t pitch=0, real_t roll=0l){
        addBody(body, PositionInfo(x, y, z, yaw, pitch, roll), mass);
    }

    void addBody(MyPhysicsBody* body, const PositionInfo& origin, real_t mass=0.f){
        _bodies.push_back(new ChildBody(origin, body, mass) );
        body->origin(origin);
        btTransform t( btQuaternion(origin.yaw, origin.pitch, origin.roll), btVector3(origin.x, origin.y, origin.z) );
        static_cast<btCompoundShape*>(_shape)->addChildShape(t, body->shape() );
    }

    void render(const BodyTransInfo &info)override;

protected:
    std::vector<ChildBody*> _bodies;
    std::vector<real_t> _masses_bodies;
    void createSelf();
    real_t _mass;
};

#endif // MYCOMPOUNDBODY_H
