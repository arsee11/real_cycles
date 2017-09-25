#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "utils.h"
#include <functional>
#include <memory>
#include <list>

class MyDynamicsWorld;

class Bike;

class Controller
{
    class ControlState{
    public:
        ControlState(std::function<void()> a, uint32_t ticket)
            :_action(a)
            ,_ticket(ticket)
        {}

        void exec(real_t timestep){
             _action();
            _exec_long += timestep;
        }

        time_t howLong(){ return _end_time - _begin_time; }

        bool isEnd(){
            if(_end_time > 0)
                return howLong() < _exec_long;
            else
                return false;
        }

     private:
        std::function<void()> _action;
        time_t _begin_time=0; ///time stamp millseconds
        time_t _end_time=0;    ///time stamp millseconds
        time_t _exec_long=0;   ///millseconds
        uint32_t _ticket;           ///indentify
    };

    typedef std::list< std::shared_ptr<ControlState> > control_state_list_t;

public:
    Controller(Bike* bike)
        :_bike(bike)
    {}

    void doControl( real_t timestep);

    void turn(bool isleft);
     void endTurnning();

    void holdbar(real_t angle);

    void pump(bool ispush);
    void endPump(bool ispush);

    void lean(bool isieft);
    void endLean(bool isieft);

    void step(real_t torque);
    void endStep();

    void load(real_t offset);

private:
    Bike* _bike=nullptr;
    control_state_list_t _control_state_list;
    uint32_t _turn_ticket=0;
};

#endif // CONTROLLER_H
