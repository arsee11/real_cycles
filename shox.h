#ifndef SHOX_H
#define SHOX_H

#include "mycompoundbody.h"


class HalfShoxPart:public MyCompoundBody
{
public:
    HalfShoxPart(const PositionInfo& origin, real_t mass, real_t radius, real_t len);

    /// @return setup_pos_out
    PositionInfo getSetupPos(bool is_left){
        if(is_left)
        {
            return PositionInfo( -(_len/2.f), 0.f, 0.f);
        }

         return PositionInfo( _len/2.f, 0.f, 0.f);
    }

private:
    real_t _len;
};


class Shox
{
     static real_t constexpr LEFT_MASS_FACTOR = 3.f;
     static real_t constexpr RIGHT_MASS_FACTOR = 5.f;

public:
    Shox(const PositionInfo& moveTo, real_t mass, real_t len, real_t travel);
    ~Shox(){
        if(_left != nullptr)
            delete _left;

        if(_right != nullptr)
            delete _right;

        if(_link != nullptr)
            delete _link;
    }

    void attach2World(MyDiscreteDynamicsWorld* world);

    //adjusting apis
    void setDamping(real_t val);
    void setSpring(real_t val);

    void moveTo(const PositionInfo& o);

    real_t length(){ return _len; }

    inline void setupLeft(MyDiscreteDynamicsWorld* world
                          , MyPhysicsBody* body, const PositionInfo& body_point)
    {
        PositionInfo part_point = _left->getSetupPos(true);
         setup(world, _left, part_point, body, body_point);
    }

    inline void setupRight(MyDiscreteDynamicsWorld* world
                           , MyPhysicsBody* body, const PositionInfo& body_point)
    {
        PositionInfo part_point = _right->getSetupPos(false);
        setup(world, _right, part_point, body, body_point);
    }

private:
    void createLeftPart();
    void createRightPart();
    void makeLink();

    void setup(MyDiscreteDynamicsWorld* world
               , HalfShoxPart* part,const PositionInfo& part_point
               , MyPhysicsBody* body, const PositionInfo& body_point);

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
