#include "myphysicsbody.h"
#include "mydiscretedynamicsworld.h"

uint MyPhysicsBody::id_counter=0;

void MyPhysicsBody::attach2World(MyDiscreteDynamicsWorld *world){
    world->addCollisionShape( _shape);
    world->theWorld()->addRigidBody(_body);
    world->addBody(_id, this);
}

void MyPhysicsBody::origin(const PositionInfo &origin)
{
    _origin = origin;
    btTransform trans( btQuaternion(origin.yaw, origin.pitch, origin.roll)
                       , btVector3(origin.x, origin.y, origin.z));

    btDefaultMotionState *m = new btDefaultMotionState(trans);
    if(_body != nullptr)
        _body->setMotionState(m);
}
