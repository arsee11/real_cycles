#ifndef FORK_H
#define FORK_H

#include "forkbottom.h"
#include "forkupper.h"
#include "utils.h"

class btGeneric6DofSpring2Constraint;
class MyDiscreteDynamicsWorld;
class btRigidBody;

class Fork
{
public:
    Fork(const PositionInfo& origin, real_t mass, real_t travel, real_t len, real_t steer_len, real_t axle);
    void attach2world(MyDiscreteDynamicsWorld* world);

    //adjusting apis
    void setDamping(real_t val);
    void setSpring(real_t val);

    //position apis
    void moveTo(const PositionInfo& pos);
    void moveTo(PositionInfo&& pos){ moveTo(pos); }
    PositionInfo getSetupLocalPosition()const;
    PositionInfo getSetupWorldPosition() const {
        return _forku->toWorldPosition( getSetupLocalPosition() );
    }
    PositionInfo getSteerTubeTopLocalPosition() const;
    PositionInfo getSteerTubeTopWorldPosition() const {
        return _forku->toWorldPosition( getSteerTubeTopLocalPosition() );
    }
    PositionInfo getWheelSetupLocalPosition()const;
    PositionInfo getWheelSetupWorldPosition()const{
        return _forkb->toWorldPosition( getWheelSetupLocalPosition() );
    }
    PositionInfo origin()const{ return _origin; }

    //attributes apis
    real_t length()const{ return _len; }
    real_t steerLength()const{ return _steer_len; }
    btRigidBody* upper_body()const { return _forku-> physics_body(); }
    btRigidBody* wheel_setup_body()const{ return _forkb->physics_body(); }

private:
    ForkBottom* _forkb=nullptr;
    ForkUpper* _forku = nullptr;
    btGeneric6DofSpring2Constraint* _constraint=nullptr;
    real_t _len = 0;
    real_t _steer_len=0;
    PositionInfo _origin;

private:
    std::tuple<PositionInfo, PositionInfo> calcPos(const PositionInfo &pos);
};

#endif // FORK_H
