#ifndef SHOX_H
#define SHOX_H

#include "mycompoundbody.h"


class HalfShoxPart:public MyCompoundBody
{
public:
    HalfShoxPart(const PositionInfo& origin, real_t mass, real_t radius, real_t len, real_t setup_width=4.f, bool is_left = true);

    /// @return setup_pos_out
    PositionInfo getSetupPos(){ return _setup_pos_out;  }

private:
    real_t _setup_width;
    PositionInfo _setup_pos_out, _setup_pos_in;
};


class Shox
{
     static real_t constexpr LEFT_MASS_FACTOR = 3.f;
     static real_t constexpr RIGHT_MASS_FACTOR = 5.f;

public:
    Shox(const PositionInfo& origin, real_t mass, real_t len, real_t travel);
    ~Shox(){
        if(_left != nullptr)
            delete _left;

        if(_right != nullptr)
            delete _right;

        if(_link != nullptr)
            delete _link;
    }

    void attach2World(MyDiscreteDynamicsWorld* world);
    void origin(const PositionInfo& o);

    real_t setupWidth(){ return 4.f; }
    real_t length(){ return _len; }

    inline void setupLeft(MyDiscreteDynamicsWorld* world
                          , MyPhysicsBody* body_out, const PositionInfo& point_out
                          , MyPhysicsBody* body_in, const PositionInfo& point_in)
    {
        PositionInfo part_point = _left->getSetupPos();
         setup(world, _left, part_point, body_out, point_out, body_in, point_in);
    }
    inline void setupRight(MyDiscreteDynamicsWorld* world
                           , MyPhysicsBody* body_out, const PositionInfo& point_out
                           , MyPhysicsBody* body_in, const PositionInfo& point_in)
    {
        PositionInfo part_point = _right->getSetupPos();
        setup(world, _right, part_point, body_out, point_out, body_in, point_in);
    }

private:
    void createLeftPart();
    void createRightPart();
    void makeLink();

    void setup(MyDiscreteDynamicsWorld* world
               , HalfShoxPart* part,const PositionInfo& part_point
               , MyPhysicsBody* body_out, const PositionInfo& point_out
               , MyPhysicsBody* body_in, const PositionInfo& point_in);

    PositionInfo _origin;
    real_t _mass=0.f;
    real_t _len;
    real_t _travel;

    real_t _right_len, _left_len;

    HalfShoxPart* _left = nullptr;
    HalfShoxPart* _right=nullptr;
    btGeneric6DofSpring2Constraint* _link=nullptr;
};

#endif // SHOX_H
