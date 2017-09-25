#include "mybox.h"
#include "mydynamicsworld.h"
#include "myglwidget.h"
#include "myground.h"
#include <QApplication>
#include <QDebug>

void callback(const bodies_state_t&)
{
    qDebug()<<"callback";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGLWidget w;
    w.show();
/*
    MyDiscreteDynamicsWorld w(callback);
    MyGround* g = new MyGround(900, 1000, 2, btVector3(0, -90, 0));
    g->color(MyBox::UP, Color(0,200,0));
    //g->physics_body()->setRestitution(1.f);
    g->physics_body()->setFriction(3.f);
    g->attach2Wolrd(&w);
    for(int i=0; i<1000; i++)
        w.doSimulation();
*/
/*
    btDefaultCollisionConfiguration* _collision_conf = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* _collision_dispatcher = new	btCollisionDispatcher(_collision_conf);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btDbvtBroadphase*_broadphase = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* _constraint_solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* _the_world = new btDiscreteDynamicsWorld(_collision_dispatcher, _broadphase, _constraint_solver, _collision_conf);
    for(int i=0; i<1000; i++)
        _the_world->stepSimulation(1/60.f);

*/
    return a.exec();
}
