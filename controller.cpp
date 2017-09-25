#include "controller.h"
#include "handlebar.h"
#include "mydynamicsworld.h"
#include "myrigidbody.h"
#include <QDebug>

void Controller::doControl(real_t timestep)
{
    for(auto c : _control_state_list)
        c->exec();
}

void Controller::turn(bool isleft)
{
    Handlebar* bar = _bike->handlebar();
    auto action = [bar]{
        real_t n = (isleft ? 20.f : -20.f);
        Vex t(0.f, n, 0.f);
        bar->applyTorque(t);
    };
    std::shared_ptr<ControlState>  cst (new ControlState( action, _turn_ticket) );
    cst->begin();
    _control_state_list.push_back(cst);
}

void Controller::endTurnning()
{
    for(auto i : _control_state_list)
    {
        if( i->ticket() == _turn_ticket)
            i->end();
    }
}

void Controller::holdbar(real_t angle)
{

}

void Controller::pump(bool ispush)
{

}

void Controller::endPump(bool ispush)
{

}

void Controller::lean(bool isieft)
{

}

void Controller::endLean(bool isieft)
{

}

void Controller::step(real_t torque)
{

}

void Controller::endStep()
{

}

void Controller::load(real_t offset)
{

}


