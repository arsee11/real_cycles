#include "mydynamicsworld.h"
#include "myrigidbody.h"
#include <exception>
#include <QDebug>

struct Quaternion
{
    real_t x,y,z,w;
};

MyDynamicsWorld::MyDynamicsWorld(BodisStateDelegate deletgate)
    :_bodies_state_delegate(deletgate)
{
    init();
}

MyDynamicsWorld::~MyDynamicsWorld()
{
    uninit();
}

void MyDynamicsWorld::stopSimulation()
{
    _is_stop = true;
}

void MyDynamicsWorld::addRigidBody(MyRigidBody *body){
    btRigidBody* btbody = static_cast<btRigidBody*>(body->getRawBody());
    theWorld()->addRigidBody(btbody);
    _rigid_body_list.push_back(body);
}

void MyDynamicsWorld::doSimulation(real_t framerate)
{
    _is_stop = false;
    assert(_the_world );

    _the_world->stepSimulation(1.f/framerate, 1.f, 1.f/framerate);
    bodies_state_t states;
    for (int j=_the_world->getNumCollisionObjects()-1; j>=0 ;j--)
    {
        btCollisionObject* obj = _the_world->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);

        btTransform trans;
        if (body && body->getMotionState())
            body->getMotionState()->getWorldTransform(trans);
        else
            trans = obj->getWorldTransform();

        real_t ax = trans.getRotation().getAxis().getX();
        real_t ay = trans.getRotation().getAxis().getY();
        real_t az = trans.getRotation().getAxis().getZ();
        real_t ag = trans.getRotation().getAngle();
       //qDebug()<<"world pos object =         "<<j <<"(x,y,z):"<<real_t(trans.getOrigin().getX())<<","<<real_t(trans.getOrigin().getY())<<","<<real_t(trans.getOrigin().getZ());
       // qDebug()<<"world rotation object = "<<j <<"(x,y,z,angle):"<<ax<<","<<ay<<"," <<az<<","<<ag;

        void* ptr = body->getUserPointer();
        BodyTransInfo pos= { static_cast<MyRigidBody*>(body->getUserPointer())
                        , trans.getOrigin().getX()
                        , trans.getOrigin().getY()
                        , trans.getOrigin().getZ()
                        , ax ,ay ,az,ag};

        states.push_back(pos);
    }

    if(_bodies_state_delegate != nullptr)
        _bodies_state_delegate(states);

}

bool MyDynamicsWorld::init()
{
        ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
        _collision_conf = new btDefaultCollisionConfiguration();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        _collision_dispatcher = new	btCollisionDispatcher(_collision_conf);

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        _broadphase = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        _constraint_solver = new btSequentialImpulseConstraintSolver;

        _the_world = new btDiscreteDynamicsWorld(_collision_dispatcher, _broadphase, _constraint_solver, _collision_conf);
        _the_world->setInternalTickCallback(&MyDynamicsWorld::preTickCallback, this, true);

        return true;
}

void MyDynamicsWorld::uninit()
{
    if(_the_world != nullptr)
        delete _the_world;

    if(_constraint_solver != nullptr)
        delete _constraint_solver;

    if(_broadphase != nullptr)
        delete _broadphase;

    if(_collision_dispatcher != nullptr)
        delete _collision_dispatcher;

    if(_collision_conf != nullptr)
        delete _collision_conf;

    /*for (int j=0; j<_collision_shapes.size(); j++)
    {
        btCollisionShape* shape = _collision_shapes[j];
        _collision_shapes[j] = 0;
        delete shape;
    }
    _collision_shapes.clear();
    */
}

void MyDynamicsWorld::preTickCallback(btDynamicsWorld *world, btScalar time_step)
{
    MyDynamicsWorld *me = static_cast<MyDynamicsWorld*>(world->getWorldUserInfo());
    assert(me);
    if(me->_prestep_delegate != nullptr)
        me->_prestep_delegate(me, time_step);
}
