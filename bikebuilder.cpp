///bikebuilder.cpp
///


#include "bikebuilder.h"
#include "fork.h"
#include "handlebar.h"
#include "stem.h"
#include "wheel.h"

#include <type_traits>

Bike* BikeBuilder::build(MyDynamicsWorld* world/*, FrameArgs, ForkArgs, WheelArgs, StemArgs, HandleBarArgs*/)
{
    typedef Frame<FrameFrontPart, FrameSteadyRearPart, banshee_rune_linker_adapter_t, bashee_rune_shox_adapter_t>  frame_t;
    auto frame = buildFrame<FrameFrontPart, FrameSteadyRearPart
            ,Shox, banshee_rune_linker_adapter_t
            ,bashee_rune_shox_adapter_t>(world);

    //typedef std::result_of(*frame)::type frame_t;

    return build<frame_t, Fork, Wheel, Stem, Handlebar>(world, frame);
}

