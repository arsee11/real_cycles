#ifndef MYPYSICSBODY_H
#define MYPYSICSBODY_H

#include "cube.h"
#include <btBulletDynamicsCommon.h>

const real_t FACTOR = 100.f;

class MyDiscreteDynamicsWorld;
class BodyTransInfo;

class  MyPhysicsBody
{
public:
    MyPhysicsBody(const PositionInfo& origin=PositionInfo())
        :_origin(origin)
    {
        _id = id_counter++;
    }

    virtual ~MyPhysicsBody(){}

    void attach2World(MyDiscreteDynamicsWorld* world);

    void origin(const PositionInfo& origin);
    PositionInfo origin()const{ return _origin;  }

    virtual void color(int r, int g, int b){ _color.r = r; _color.g = g; _color.b = b; }
    int id(){ return _id;}
    btRigidBody* physics_body(){ return _body; }
    btCollisionShape* shape(){ return _shape; }
    virtual const Cube& cube()const{ return Cube(); }

    PositionInfo toWorldPosition(const PositionInfo& origin) const{
        PositionInfo thiso = this->origin();
        return PositionInfo(thiso.x+origin.x, thiso.y+origin.y, thiso.z+origin.z);
    }

    virtual void addBody( MyPhysicsBody* body, real_t x=0, real_t y=0, real_t z=0, real_t yaw=0, real_t pitch=0, real_t roll=0){}
    virtual void addBody(MyPhysicsBody* body, const btTransform& trans = btTransform(btQuaternion(0,0,0))){}
    virtual void render(const BodyTransInfo& info) = 0;

protected:
    void createPhysicsBody( btCollisionShape* shape, real_t mass)
    {
        _shape = shape;
        btTransform trans;
        trans.setIdentity();
        trans.setOrigin(btVector3(_origin.x, _origin.y, _origin.z));
        trans.setRotation( btQuaternion(_origin.yaw, _origin.pitch, _origin.roll));
        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);
        btVector3 localInertia(0,0,0);
        if (isDynamic)
            _shape->calculateLocalInertia(mass,localInertia);

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(trans);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,_shape,localInertia);
        _body = new btRigidBody(rbInfo);
        _body->setUserIndex(_id);
    }

protected:   
    btCollisionShape* _shape = nullptr;
    btRigidBody* _body = nullptr;
    int _id=-1;
    PositionInfo _origin;
    Color _color;

    static uint id_counter;

};


#endif // MYPYSICSBODY_H
