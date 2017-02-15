#ifndef FRAME_H
#define FRAME_H

#include "framefrontpart.h"
#include "framesteadyrearpart.h"
#include "mydiscretedynamicsworld.h"
#include "utils.h"

struct NullShoxSetup
{
    template<class FrontPart, class RearPart>
    void setupPoint(FrontPart* f, RearPart* r){}

    void remove(){}
};

struct NullLinkerSetup
{
    template<class FrontPart, class RearPart>
    void setupPoint(FrontPart* f, RearPart* r){}

    void remove(){}
};

template<class FrontPart, class RearPart, class LinkerSetup=NullLinkerSetup, class ShoxSetup=NullShoxSetup>
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
    {}

    ~Frame()
    {
        if(_front != nullptr)
            delete _front;

        if(_rear != nullptr)
            delete _rear;        
    }

    void create(MyDiscreteDynamicsWorld* world, const front_param_t& fp, const rear_param_t& rp, LinkerSetup* lsetup=nullptr, ShoxSetup* ssetup=nullptr)
    {
        _front = new FrameFrontPart(_origin, fp);
        _rear = new FrameSteadyRearPart(PositionInfo(0,0,0), rp);
        if(lsetup != nullptr)
            lsetup->setupPoint(_front, _rear);

        if( ssetup != nullptr)
            ssetup->setupPoint(_front, _rear);

        _front->create();
        //_front->physics_body()->setAngularVelocity(btVector3(0.f, 100.f, 0.f));
        _front->attach2World(world);

        PositionInfo bb_origin = _front->getBBPosition();
        bb_origin = _front->toWorldPosition(bb_origin);
        const Cube& cube = _rear->cube();
        real_t x = bb_origin.x - (cube.len()/2.f + _CSL-cube.len());
        real_t y = bb_origin.y + cube.height()/2.f;
        _rear->origin(PositionInfo(x, y, _origin.z));
        _rear->create();
        _rear->attach2World(world);

        if(lsetup != nullptr)
            lsetup->setupLinker(world, _front, _rear);

        if(ssetup != nullptr)
            ssetup->setupShox(world, _front, _rear);
    }

    //Head tube world postion
    PositionInfo getHTPosition(){
        PositionInfo pos = _front->getHTPosition();
        return _front->toWorldPosition(pos);
    }

private:
    FrontPart* _front=nullptr;
    RearPart* _rear=nullptr;
    PositionInfo _origin;
    real_t _WB;
    real_t _CSL;
};

#endif // FRAME_H
