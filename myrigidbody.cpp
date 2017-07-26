#include "myrigidbody.h"
#include "mydiscretedynamicsworld.h"

uint MyRigidBody::id_counter=0;

void MyRigidBody::attach2World(MyDynamicsWorld *world){
    //world->addCollisionShape( _shape);
    world->addRigidBody(this);
}

void MyRigidBody::origin(const PositionInfo &origin)
{
    _origin = origin;
    btTransform trans( btQuaternion(origin.yaw, origin.pitch, origin.roll)
                       , btVector3(origin.x, origin.y, origin.z));

    btDefaultMotionState *m = new btDefaultMotionState(trans);
    if(_body != nullptr)
        _body->setMotionState(m);
}

PositionInfo MyRigidBody::toWorldPosition(const PositionInfo &origin) const{
    PositionInfo thiso = this->origin();
    real_t len = origin.y;
    real_t xz_projection = len * sin(thiso.pitch);
    real_t x = thiso.x + xz_projection * sin(thiso.yaw)+origin.x;
    real_t y = thiso.y + len*cos(thiso.pitch);
    real_t z = thiso.z + xz_projection * cos(thiso.yaw)+origin.z;
    return PositionInfo(x, y, z);
    //real_t x = thiso.x + origin.x;
    //real_t y = thiso.y + origin.y;
    //real_t z = thiso.z + origin.z;
    return PositionInfo(x, y, z, thiso.yaw, thiso.pitch, thiso.roll);
}

PositionInfo MyRigidBody::toLocalPosition(const PositionInfo &origin) const
{
    PositionInfo thiso = this->origin();
    real_t x = origin.x - thiso.x;
    real_t y = origin.y - thiso.y;
    real_t z = origin.z - thiso.z;
    return PositionInfo(x, y, z);
}

void MyRigidBody::createPhysicsBody(btCollisionShape *shape, real_t mass)
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
    _body->setUserPointer(this);
}
