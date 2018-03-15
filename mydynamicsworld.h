#ifndef MYDYNAMICSWORLD_H
#define MYDYNAMICSWORLD_H

#include <btBulletDynamicsCommon.h>
#include <functional>
#include <vector>
#include <map>
#include "utils.h"

class MyRigidBody;


struct BodyTransInfo
{
    BodyTransInfo(){}
    BodyTransInfo(MyRigidBody* b, real_t ix, real_t iy, real_t iz, real_t iaxis_x, real_t iaxis_y, real_t iaxis_z, real_t iangle)
        :body(b)
        ,x(ix)
        ,y(iy)
        ,z(iz)
        ,axis_x(iaxis_x)
        ,axis_y(iaxis_y)
        ,axis_z(iaxis_z)
        ,angle(iangle)
    {}

    real_t degrees()const{ return todegrees(angle);}
    MyRigidBody* body=nullptr;
    real_t x=0;
    real_t y=0;
    real_t z=0;
    real_t axis_x=0;
    real_t axis_y=0;
    real_t axis_z=0;
    real_t angle=0;
};

typedef std::vector<BodyTransInfo> bodies_state_t;


class MyDynamicsWorld
{
public:
    typedef std::function<void(const bodies_state_t&)> BodisStateDelegate;
    typedef std::function<void(MyDynamicsWorld *world, real_t timeStep)> PreStepDelegate;

public:
    MyDynamicsWorld(BodisStateDelegate deletgate);
    ~MyDynamicsWorld();

    void setPreStepDelegate(PreStepDelegate delegate){ _prestep_delegate = delegate; }
    void setGravity(real_t x, real_t y, real_t z){ _the_world->setGravity(btVector3(x, y, z)); }
    void applyGravity(){ _the_world->applyGravity(); }
    void clearForces(){_the_world->clearForces();}
    //void addCollisionShape( btCollisionShape* shape){ _collision_shapes.push_back(shape);}
    void doSimulation(real_t framerate);
    void stopSimulation();

    ///the world dose not own the body
    void addRigidBody(MyRigidBody* body);

    btDiscreteDynamicsWorld* theWorld(){ return _the_world; }
    std::vector<MyRigidBody*> getRigidBodies(){ return _rigid_body_list; }

private:
    bool init();
    void uninit();
    static void preTickCallback(btDynamicsWorld *world, btScalar timeStep);

private:
    btDefaultCollisionConfiguration* _collision_conf = nullptr;
    btCollisionDispatcher* _collision_dispatcher = nullptr;
    btBroadphaseInterface* _broadphase = nullptr;
    btSequentialImpulseConstraintSolver* _constraint_solver = nullptr;
    btDiscreteDynamicsWorld* _the_world = nullptr;

    //btAlignedObjectArray<btCollisionShape*> _collision_shapes;
    std::vector<MyRigidBody*> _rigid_body_list;

    bool _is_stop = false;
    BodisStateDelegate _bodies_state_delegate = nullptr;
    PreStepDelegate _prestep_delegate=nullptr;
};

#endif // MYDYNAMICSWORLD_H
