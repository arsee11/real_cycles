#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "utils.h"
#include <functional>
#include <memory>
#include <list>
#include "bike.h"

class MyDynamicsWorld;

class Controller
{
    class Control{
    public:
        Control(std::function<void()> f, uint32_t ticket)
            :_action(f)
            ,_ticket(ticket)
        {}

        ///@param timestep second
        void exec(real_t timestep){
            _action();
            _exec_long += timestep*1000;
        }

        uint32_t ticket(){ return _ticket; }

        void begin(){_begin_time = 0; }
        void end(){ _end_time = 1; }

        time_t howLong(){ return _end_time - _begin_time; }

        bool isEnd(){
            if(_end_time > 0)
                return howLong() < _exec_long;
            else
                return false;
        }

     private:
        std::function<void()> _action;
        time_t _begin_time=0;   ///time stamp millseconds
        time_t _end_time=0;     ///time stamp millseconds
        time_t _exec_long=0;    ///millseconds
        uint32_t _ticket;       ///indentify
    };

    typedef std::list< std::shared_ptr<Control> > control_list_t;

public:
    Controller(Bike* bike)
        :_bike(bike)
    {}

    ///@param timestep second
    void doControl(real_t timestep);

    void turn(bool isleft);
    void endTurnning();


    ///@param direction 与正前方向的夹角，0-正前，负数- 偏左，正数-偏右.
    void holdbar(real_t direction);

    void pump(bool ispush);
    void endPump(bool ispush);

    void lean(bool isleft);
    void endLean(bool isleft);

    void step(real_t torque);
    void endStep();

    void load(real_t offset);

    void addControl(std::function<void()> f, int ticket)
    {
        std::shared_ptr<Control>  cst (new Control( f, ticket) );
        cst->begin();
        _control_list.push_back(cst);
    }

private:
    Bike* _bike=nullptr;
    control_list_t _control_list;
    uint32_t _turn_ticket=0;
    uint32_t _hold_ticket=1;
};

#endif // CONTROLLER_H
