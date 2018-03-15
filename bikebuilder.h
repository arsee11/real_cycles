#ifndef BIKEBUILDER_H
#define BIKEBUILDER_H

#include "bansheerune.h"
#include "bike.h"
#include "forkadapter.h"
#include "frame.h"
#include "framefrontpart.h"
#include "framesteadyrearpart.h"
#include "handlebaradapter.h"
#include "normalshoxadapter.h"
#include "shox.h"
#include "twolinkeradapter.h"
#include "wheeladapter.h"

class BikeBuilder
{
public:
    static Bike* build(MyDynamicsWorld* world/*, FrameArgs, ForkArgs, WheelArgs, StemArgs, HandleBarArgs*/);

    typedef TwoLinkerAdapter<BansheeRune::front_point1, BansheeRune::front_point2
            ,BansheeRune::rear_point1, BansheeRune::rear_point2
            ,BansheeRune::linker1, BansheeRune::linker2
            > banshee_rune_linker_adapter_t;

    typedef NormalShoxAdapter<BansheeRune::front_shox_point
            ,BansheeRune::rear_shox_point
            ,Shox
            > bashee_rune_shox_adapter_t;

    template<class FrontPart, class RearPart, class Shox/*=NoShox*/
             ,class LinkerAdapter=NullLinkerAdapter
             ,class ShoxAdapter=NullShoxAdapter
    >
    static auto buildFrame(MyDynamicsWorld* world)->decltype(new Frame<FrontPart, RearPart, LinkerAdapter, ShoxAdapter>){

        typedef Frame<FrontPart, RearPart, LinkerAdapter, ShoxAdapter>  frame_t;
        frame_t *f = new frame_t(PositionInfo(-250, 40, -80), 114.2, 43);
        typename frame_t::front_param_t fp = {3.f ,12.f, 65.f, 60.f, 43.f, 74.5f, 42.f, 34.f, 72.f, 59.f};
        typename frame_t::rear_param_t rp = {1.f, 38.f, 38.f, 23.f, 15.f, 8.f};
        LinkerAdapter* ls = new LinkerAdapter(6.f, 7.f);
        ShoxAdapter* ss = new ShoxAdapter( new Shox(PositionInfo(0.f, 0.f, 0.f), 0.5f, 22.0f, 5.5f) );
        f->create(world, fp, rp, ls, ss);
        return f;
    }

    template<class Frame
             ,class Fork
             ,class Wheel
             ,class Stem
             ,class HandleBar
     >
    static auto build(MyDynamicsWorld* world, Frame* f/*, Frok* fork, Wheel*rear, Wheel* front, Stem* s, HandleBar* bar*/)->decltype(new BikeT<Frame, Fork, Wheel, Stem, HandleBar>){

        Fork* fork = new Fork(PositionInfo(50, 0, -40, torads(90)), 2.0, 16, 70, 20, 10);
        fork->attach2world(world);

        ForkAdapter<Frame, Fork> fa(f, fork);
        fa.setup(world);

        HandleBar* bar = new HandleBar(PositionInfo(0,0, -40), 0.3f,  76.0f, 3.18f, 2.f, 5.f, 8.f);
        bar->attach2World(world);

        Stem* stem = new Stem(PositionInfo(0,0, -40, torads(-90)), 0.2f, 6.f, 15.f);
        stem->attach2World(world);

        HandlebarAdapter<Fork, Stem, Handlebar> ha(fork, stem, bar);
        ha.setup(world);

        Wheel* rear_wheel = new Wheel(PositionInfo(0, 0, -40), 3, 26, 2.35, 12, 1.2);
        rear_wheel->attach2World(world);
        rear_wheel->physics_body()->setFriction(3.f);
        rear_wheel->physics_body()->setAngularVelocity(btVector3(0, 0, -20));

        WheelAdapter<Frame, Wheel> rwa(f, rear_wheel);
        rwa.setup(world);

        Wheel* front_wheel = new Wheel(PositionInfo(0, 0, -40), 2.5, 26, 2.35, 10, 1.5);
        front_wheel->attach2World(world);
        front_wheel->physics_body()->setAngularVelocity(btVector3(0, 0, -20));

        WheelAdapter<Fork, Wheel> fwa(fork, front_wheel);
        fwa.setup(world);

        typedef  BikeT<Frame, Fork, Wheel, Stem, HandleBar> bike_t;
        return new bike_t(f, fork, rear_wheel, front_wheel, stem, bar);
    }
};

#endif // BIKEBUILDER_H
