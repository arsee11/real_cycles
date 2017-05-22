#ifndef FORKADAPTER_H
#define FORKADAPTER_H

class DiscreteDynamicsWorld;

template<class Frame, class Fork>
class ForkAdapter
{
public:
    ForkAdapter(Frame* fr, Fork* fk);
    void setup(DiscreteDynamicsWorld* world);
};

#endif // FORKADAPTER_H
