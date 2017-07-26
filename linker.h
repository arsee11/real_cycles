#ifndef LINKER_H
#define LINKER_H

#include "mybox.h"
#include "mycompoundbody.h"



class Linker : public  MyCompoundBody
{
public:
    Linker(const PositionInfo& origin, real_t mass
           ,real_t len
           ,real_t left_width
           ,real_t right_width
    );

    const Cube& cube()const override{ return _cube;}

    virtual void makeLeftLink(MyDynamicsWorld* world, MyRigidBody* body, const PositionInfo&body_point);
    virtual void makeRightLink(MyDynamicsWorld* world, MyRigidBody* body, const PositionInfo &body_point);

protected:
    real_t _len;
    real_t _left_width;
    real_t _right_width;

    Cube _cube;

protected:
    void makeLink(MyDynamicsWorld *world, const PositionInfo& this_point, MyRigidBody *body, const PositionInfo &body_point);
};

#endif // LINKER_H
