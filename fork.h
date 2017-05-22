#ifndef FORK_H
#define FORK_H

#include "utils.h"

class ForkBottom;
class ForkUpper;
class btGeneric6DofSpring2Constraint;
class MyDiscreteDynamicsWorld;

class Fork
{
public:
    Fork(const PositionInfo& origin, real_t mass, real_t travel, real_t len, real_t steer_len, real_t axis);
    void attach2world(MyDiscreteDynamicsWorld* world);

    PositionInfo getSetupPoint();

private:
    ForkBottom* _forkb=nullptr;
    ForkUpper* _forku = nullptr;
    btGeneric6DofSpring2Constraint* _contraint=nullptr;
};

#endif // FORK_H
