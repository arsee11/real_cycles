#include "mybox.h"
#include "mycylinder.h"
#include "mydiscretedynamicsworld.h"
#include "shox.h"
#include "configer.h"

HalfShoxPart::HalfShoxPart(const PositionInfo &origin, real_t mass, real_t radius, real_t len)
    :MyCompoundBody(origin, mass)
    ,_len(len)
{
    MyCylinder *c = new MyCylinder(radius, len, radius, MyCylinder::X);
    real_t bw = 1.f;
    /*MyBox* b = new MyBox(2.f, bw, 2.f);

    real_t xc;
    real_t xb;
    if(is_left )
    {
      xc = 1.f;
      xb = -(len/2.f);
      c->color(255, 100, 0);
      b->color(255, 150, 0);
    }
    else
    {
      xc = -1.f;
      xb = (len/2.f);
      c->color(150, 150, 150);
      b->color(150, 150, 150);
    }
    */

    addBody(mass, c, 0, 0.f, 0.f, origin.yaw, origin.pitch, origin.roll);
    //addBody(0.01f, b, xb, 0.f, 0.f , origin.yaw, origin.pitch, origin.roll);

    /*real_t l = (_setup_width - bw)/2.f;
    //out
    MyCylinder * setup_p = new MyCylinder(0.5f, l, 0.5f, MyCylinder::Z);
    real_t xs = xb;
    real_t zs = l/2.f+bw/2.f;
    addBody(0.001f, setup_p, xs, 0, zs);
    _setup_pos_out.x = xs;
    _setup_pos_out.y = 0;
    _setup_pos_out.z = _setup_width/2.f;

    //in
    setup_p = new MyCylinder(0.5f, l, 0.5f, MyCylinder::Z);
    addBody(0.001f, setup_p, xs, 0, -zs);
    _setup_pos_in.x = xs;
    _setup_pos_in.y = 0;
    _setup_pos_in.z = -_setup_width/2.f;
    */
    createSelf();
}

Shox::Shox(const PositionInfo &origin, real_t mass, real_t len, real_t travel)
    :_origin(origin)
    ,_len(len)
    ,_mass(mass)
    ,_travel(travel)
{
    _right_len = (_len-_travel-4);
    _left_len = (_travel+4.f);
    createLeftPart();
    createRightPart();
    makeLink();
}

void Shox::attach2World(MyDynamicsWorld *world){
    if(_left != nullptr)
        _left->attach2World(world);

    if(_right != nullptr)
        _right->attach2World(world);

   if(_link != nullptr)
       world->theWorld()->addConstraint(_link, true);
}

void Shox::moveTo(const PositionInfo &o)
{
    _origin = o;
    real_t lx = _origin.x - (_len-_left_len)/2.f*cos(_origin.roll);
    real_t ly = _origin.y - (_len-_left_len)/2.f*sin(_origin.roll);
    PositionInfo lo( lx, ly, _origin.z, _origin.yaw, _origin.pitch, _origin.roll);
    _left->origin(lo);

    real_t rx = _origin.x + (_len-_right_len)/2.f*cos(_origin.roll);
    real_t ry = _origin.y + (_len-_right_len)/2.f*sin(_origin.roll);
    PositionInfo ro( rx, ry, _origin.z, _origin.yaw, _origin.pitch, _origin.roll);
    _right->origin(ro);
}

void Shox::createLeftPart()
{
    real_t m = _mass *(LEFT_MASS_FACTOR/(LEFT_MASS_FACTOR+RIGHT_MASS_FACTOR));
    PositionInfo origin( _origin.x-(_len-_left_len)/2.f, _origin.y, _origin.z);
    _left = new HalfShoxPart(origin, m, 1.5f, _left_len );
    //_left->physics_body()->setAngularVelocity(btVector3(0, 100, 10));
    _left->color(255, 100, 0);
}

void Shox::createRightPart()
{
    real_t m = _mass *(RIGHT_MASS_FACTOR/(LEFT_MASS_FACTOR+RIGHT_MASS_FACTOR));
    PositionInfo origin( _origin.x +(_len-_right_len)/2.f, _origin.y, _origin.z);
    _right = new HalfShoxPart(origin, m, 2.5f, _right_len);
    //_right->physics_body()->applyCentralImpulse(btVector3(-100, 0,0));
    _right->color(100,100,100);
}


void Shox::makeLink()
{
    btTransform localA, localB;
    localA.setIdentity();
    localA.setOrigin( btVector3(_left_len/2.f, 0, 0) );
    localB.setIdentity();
    localB.setOrigin( btVector3( -(_right_len/2.f), 0, 0));
    _link =  new btGeneric6DofSpring2Constraint(
                *(_left->physics_body()), *(_right->physics_body()), localA, localB);

    //_link->setBreakingImpulseThreshold(100000000.f);
    _link->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
    _link->setLimit(0, -_travel, 0);
    _link->setLimit(1, 0, 0);
    _link->setLimit(2, 0, 0);
    _link->setLimit(3, 0, 0);
    _link->setLimit(4, 0, 0);
    _link->setLimit(5, 0, 0);
    _link->enableSpring(0, true);
    _link->setStiffness(0, 600);
    _link->setDamping(0, 300);
    _link->setEquilibriumPoint();

    //_link = new btFixedConstraint(*(_left->physics_body()), *(_right->physics_body()), localA, localB);

}

void Shox::setup(MyDynamicsWorld *world
                 , HalfShoxPart *part, const PositionInfo &part_point
                 , MyRigidBody *body, const PositionInfo &body_point)
{

    btVector3 axis_this(0.f, 0.f, 1.f);
    btVector3 axis_body(0.f, 0.f, 1.f);
    btVector3 pivot_this(part_point.x, part_point.y, part_point.z);
    btVector3 pivot_body( body_point.x, body_point.y, body_point.z );
    btHingeConstraint*  hinge = new btHingeConstraint(*(part->physics_body()), *(body->physics_body())
                                                  , pivot_this, pivot_body, axis_this, axis_body);

    hinge->setOverrideNumSolverIterations(PhysicsConfiger::NumSolverIterations);
    world->theWorld()->addConstraint(hinge);

}
