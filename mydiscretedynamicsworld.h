#ifndef MYDISCRETEDYNAMICSWORLD_H
#define MYDISCRETEDYNAMICSWORLD_H

#include <btBulletDynamicsCommon.h>
#include <functional>
#include <vector>
#include <map>
#include "utils.h"

class MyPhysicsBody;


struct BodyTransInfo
{
    BodyTransInfo(){}
    BodyTransInfo(MyPhysicsBody* b, real_t ix, real_t iy, real_t iz, real_t iaxis_x, real_t iaxis_y, real_t iaxis_z, real_t iangle)
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
    MyPhysicsBody* body=nullptr;
    real_t x=0;
    real_t y=0;
    real_t z=0;
    real_t axis_x=0;
    real_t axis_y=0;
    real_t axis_z=0;
    real_t angle=0;
};

typedef std::vector<BodyTransInfo> bodies_state_t;


class MyDiscreteDynamicsWorld
{
public:
    typedef std::function<void(const bodies_state_t&)> bodies_state_delegate;

public:
    MyDiscreteDynamicsWorld(bodies_state_delegate deletgate);
    ~MyDiscreteDynamicsWorld();

    btDiscreteDynamicsWorld* theWorld(){ return _the_world; }

    void setGravity(real_t x, real_t y, real_t z){ _the_world->setGravity(btVector3(x, y, z)); }
    void addCollisionShape( btCollisionShape* shape){ _collision_shapes.push_back(shape);}
    void doSimulation();
    void stopSimulation();
    void addBody(int id, MyPhysicsBody* body){ _bodies[id] = body;}

private:
    bool init();
    void uninit();

private:
    btDefaultCollisionConfiguration* _collision_conf = nullptr;
    btCollisionDispatcher* _collision_dispatcher = nullptr;
    btBroadphaseInterface* _broadphase = nullptr;
    btSequentialImpulseConstraintSolver* _constraint_solver = nullptr;
    btDiscreteDynamicsWorld* _the_world = nullptr;

    btAlignedObjectArray<btCollisionShape*> _collision_shapes;
    std::map<int, MyPhysicsBody*> _bodies;

    bool _is_stop = false;
    bodies_state_delegate _bodies_state_delegate = nullptr;
};

#endif // MYDISCRETEDYNAMICSWORLD_H
