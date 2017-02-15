#ifndef INNERLINKER_H
#define INNERLINKER_H

#include "linker.h"



class InnerLinker : public Linker
{
public:
    InnerLinker(const PositionInfo& origin, real_t mass
                ,real_t len
                ,real_t left_width
                ,real_t right_width
                );

    virtual void makeLeftLink(MyDiscreteDynamicsWorld* world, MyPhysicsBody* body, const PositionInfo&body_point);
    virtual void makeRightLink(MyDiscreteDynamicsWorld* world, MyPhysicsBody* body, const PositionInfo &body_point);


private:
    MyPhysicsBody* _left=nullptr;
    MyPhysicsBody* _right=nullptr;
    MyPhysicsBody* _center=nullptr;

    void calcCube();
};

#endif // INNERLINKER_H
