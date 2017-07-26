#ifndef FRAME_H
#define FRAME_H

#include "framefrontpart.h"
#include "framesteadyrearpart.h"
#include "mydiscretedynamicsworld.h"
#include "utils.h"

struct NullShoxAdapter
{
    template<class FrontPart, class RearPart>
    void setupPoint(FrontPart* f, RearPart* r){}

    void remove(){}
};

struct NullLinkerAdapter
{
    template<class FrontPart, class RearPart>
    void setupPoint(FrontPart* f, RearPart* r){}

    void remove(){}
};

template<class FrontPart, class RearPart, class LinkerAdapter=NullLinkerAdapter, class ShoxAdapter=NullShoxAdapter>
class Frame
{
public:
    typedef typename FrontPart::Param front_param_t;
    typedef typename RearPart::Param rear_param_t;

public:
    Frame(const PositionInfo& origin, real_t WB, real_t CSL)
        :_origin(origin)
        ,_WB(WB)
        ,_CSL(CSL)
        ,_BBDrop(10.f)
    {}

    ~Frame()
    {
        if(_front != nullptr)
            delete _front;

        if(_rear != nullptr)
            delete _rear;        
    }

    void create(MyDynamicsWorld* world
                , const front_param_t& fp
                , const rear_param_t& rp
                , LinkerAdapter* ladpt=nullptr
                , ShoxAdapter* sadpt=nullptr)
    {
        _front = new FrameFrontPart(_origin, fp);
        _rear = new FrameSteadyRearPart(PositionInfo(0,0,0), rp);


        _front->create();
        //_front->physics_body()->setAngularVelocity(btVector3(0.f, 100.f, 0.f));
        _front->attach2World(world);

        PositionInfo bb_origin = _front->getBBPosition();
        bb_origin = _front->toWorldPosition(bb_origin);
        const Cube& cube = _rear->cube();
        real_t roll = atan( _BBDrop/_CSL);
        real_t x = bb_origin.x - (cube.len()/2.f + _CSL-cube.len()*cos(roll));
        real_t y = bb_origin.y + (cube.len()/2.f*tan(roll)+cube.height()/2.f)*cos(roll);
        _rear->origin(PositionInfo(x, y, _origin.z, 0.f, 0.f, -roll));
        _rear->create();
        _rear->attach2World(world);

        if(ladpt != nullptr)
            ladpt->setupPoint(_front, _rear);

        if( sadpt != nullptr)
            sadpt->setupPoint(_front, _rear);

        if(ladpt != nullptr)
            ladpt->setupLinker(world, _front, _rear);

        if(sadpt != nullptr)
            sadpt->setupShox(world, _front, _rear);
    }

    PositionInfo getForkSetupLocalPosition()const {
        PositionInfo oht =  _front->getHTPosition();
        oht.x += HTL()/2.f * cos( torads(HTA()) );
        oht.y -= HTL()/2.f * sin( torads(HTA()) );
        PositionInfo o =_front->origin();
        oht.yaw = o.yaw;
        oht.pitch = o.pitch;
        oht.roll = o.roll;
        return oht;
    }
    PositionInfo getForkSetupWorldPosition(){ return _front->toWorldPosition(getForkSetupLocalPosition()); }

    PositionInfo getWheelSetupLocalPosition()const{
        return _rear->getWheelSetupLocalPosition();
    }
    PositionInfo getWheelSetupWorldPosition()const{
        return _rear->toWorldPosition( getWheelSetupLocalPosition() );
    }

    real_t HTL()const { return _front->HTL(); }
    real_t HTA()const { return _front->HTA(); }
    btRigidBody* front_body()const { return _front-> physics_body(); }
    btRigidBody* wheel_setup_body()const { return _rear->physics_body(); }

private:
    FrontPart* _front=nullptr;
    RearPart* _rear=nullptr;
    PositionInfo _origin;
    real_t _WB;
    real_t _CSL;
    real_t _BBDrop;
};

#endif // FRAME_H
