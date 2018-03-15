#ifndef BIKE_H
#define BIKE_H

#include <memory>

class Handlebar;

class Bike
{
public:
    virtual Handlebar* getHandlebar()=0;
};


////////////////////////////////////////////////////
///@ BikeT
template<class Frame
         ,class Fork
         ,class Wheel
         ,class Stem
         ,class HandleBar
 >
class BikeT : public Bike
{
    typedef std::unique_ptr<Frame> frame_ptr_t;
    typedef std::unique_ptr<Fork> fork_ptr_t;
    typedef std::unique_ptr<Wheel> wheel_ptr_t;
    typedef std::unique_ptr<Stem> stem_ptr_t;
    typedef std::unique_ptr<HandleBar> bar_ptr_t;

public:
    BikeT(){

    }

    ///own these instance, will delete them when disconstruct
    BikeT(Frame* frame, Fork* fork, Wheel* rear, Wheel* front
         ,Stem* stem, HandleBar* bar){

        setup(frame);
        setup(fork);
        setup(rear, front);
        setup(stem);
        setup(bar);
    }

    void setup(Frame* f){
        _frame = frame_ptr_t(f);
    }

    void setup(Fork* f){
       _fork = fork_ptr_t(f);
    }

    void setup(Wheel* rear, Wheel* front){
        _rear_wheel = wheel_ptr_t(rear);
        _front_wheel = wheel_ptr_t(front);
    }

    void setup(Stem* s){
        _stem = stem_ptr_t(s);
    }

    void setup(HandleBar* bar){
        _bar = bar_ptr_t(bar);
    }

    HandleBar* getHandlebar()override{ return _bar.get(); }

private:
    frame_ptr_t _frame;
    fork_ptr_t _fork;
    wheel_ptr_t _rear_wheel, _front_wheel;
    stem_ptr_t _stem;
    bar_ptr_t _bar;
};

#endif // BIKE_H
