///cyclessimulator.cpp
///

#include "cyclessimulator.h"
#include "pumptrack.h"
#include <functional>
#include "bike.h"
#include "bikebuilder.h"
#include "handlebar.h"
#include <QDebug>

#include "crankset.h"
#include "pedal.h"

using namespace std::placeholders;

//Bike* mtb;
//void CyclesSimulator::init()
//{
//    _world = new MyDynamicsWorld(std::bind(&CyclesSimulator::onWorldStateChanged, this, std::placeholders::_1));
//    _world->setPreStepDelegate( std::bind( &CyclesSimulator::peekDynamicsWorld, this, _1, _2) );
//    _world->setGravity(0.f, PhysicsConfiger::Gravity, 0.f);

//    PumpTrack* g = new PumpTrack(PositionInfo(0, -90, 0));
//    //g->setRestitution(1.f);
//    g->setFriction(3.f);
//    g->attach2World(_world);

//    mtb = BikeBuilder::build(_world);
//    _controller = new Controller(mtb);
//}

void CyclesSimulator::init()
{
    _world = new MyDynamicsWorld(std::bind(&CyclesSimulator::onWorldStateChanged, this, std::placeholders::_1));
    _world->setPreStepDelegate( std::bind( &CyclesSimulator::peekDynamicsWorld, this, _1, _2) );
    _world->setGravity(0.f, PhysicsConfiger::Gravity, 0.f);

    Crankset* cs = new Crankset(17, 8.3, 32, 0.8, PositionInfo(0,0,-10));
    //cs->physics_body()->setAngularVelocity(btVector3(2, 0, 0));
    cs->attach2World(_world);

    Pedal* p = new Pedal(PositionInfo(0,0, -10), 0.350);
    //p->physics_body()->setAngularVelocity(btVector3(2, 0, 0));
    p->attach2World(_world);
}

void CyclesSimulator::onWorldStateChanged(const bodies_state_t& states)
{
//    Handlebar* bar = mtb->getHandlebar();
//    //Vex v = bar->getTotalTorque();
//    Vex v = bar->getAngularVelocity();
//    qDebug()<<"angular v of bar(x,y,z):"<< v.x<<","<<v.y<<","<<v.z;

    //bar->physics_body()->translate(btVector3(-1,0,0));
    /*BodyTransInfo trans = bar->getMotionPosition();
    trans.angle += MY_PI/4.f;
    bar->physics_body()->getMotionState()->setWorldTransform(
         btTransform(
            btQuaternion(trans.axis_x, trans.axis_y, trans.axis_z, trans.angle)
            ,btVector3(trans.x, trans.y, trans.z)));
    */
    _bodies_state = states;
}








