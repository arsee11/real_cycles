#include "controller.h"
#include "handlebar.h"
#include "mydynamicsworld.h"
#include "myrigidbody.h"
#include <QDebug>

void Controller::doControl(real_t timestep)
{
    qDebug()<<"timestep:"<<timestep;
    auto i = _control_list.begin();
    for(; i != _control_list.end();)
    {
        if( (*i)->isEnd())
        {
            i = _control_list.erase(i);
            continue;
        }

        (*i)->exec(timestep);
        ++i;
    }
}

void Controller::turn(bool isleft)
{
    Handlebar* bar = _bike->getHandlebar();
    auto action = [bar, isleft]{
        real_t n = (isleft ? 200.f : -200.f);
        Vex t(0.f, n, 0.f);
        bar->applyTorque(t);
    };

    addControl(action, _turn_ticket);
}

void Controller::endTurnning()
{
    for(auto i : _control_list)
    {
        if( i->ticket() == _turn_ticket)
            i->end();
    }
 }

void Controller::holdbar(real_t direction)
{
    Handlebar* bar = _bike->getHandlebar();
    auto action = [this, bar, direction]{
        Vex v = bar->getAngularVelocity();
        Vex v1={0.f, 0.f, 0.f };
        real_t vd = v.y - v1.y;
        if(vd > 0.f || vd < 0.f)
        {
            real_t a = vd / 0.033;
            real_t f = 100.f*a;
            bar->applyTorque( Vex(0.f, -f, 0.f) );
        }
    };

    addControl(action, _hold_ticket);
}



void Controller::pump(bool ispush)
{

}

void Controller::endPump(bool ispush)
{

}

void Controller::lean(bool isleft)
{
    Handlebar* bar = _bike->getHandlebar();
    auto action = [this, bar, isleft]{
        Vex leftp, rightp;
        std::tie(leftp, rightp) = bar->getControlPoint();
        real_t f = 10;
        if(isleft)
        {
            bar->applyForce(Vex(0, -f, 0), leftp);
            bar->applyForce(Vex(0, f, 0), rightp);
        }
        else
        {
            bar->applyForce(Vex(0, f, 0), leftp);
            bar->applyForce(Vex(0, -f, 0), rightp);
        }
    };

    addControl(action, _hold_ticket);
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


