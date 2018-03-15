///cyclessimulator.h
///

#ifndef CYCLESSIMULATOR_H
#define CYCLESSIMULATOR_H

#include "mydynamicsworld.h"
#include "controller.h"

class CyclesSimulator
{
public:
    void doSimulation()
    {
        if(_world!= nullptr)
            _world->doSimulation(30);
    }

    void init();
    const bodies_state_t& getBodiesState()const{ return _bodies_state; }
    Controller* controller(){ return _controller; }
protected:
    void onWorldStateChanged(const bodies_state_t &states);
    void peekDynamicsWorld(MyDynamicsWorld *world, real_t time_step)
    {
        world->clearForces();
        world->applyGravity();
        if(_controller != nullptr)
            _controller->doControl(time_step);
    }

private:
    MyDynamicsWorld* _world=nullptr;
    Controller* _controller=nullptr;
    bodies_state_t _bodies_state;
    //aceTrack* _current_track=nullptr;
};

#endif // CYCLESSIMULATOR_H
