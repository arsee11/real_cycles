#include "mybox.h"
#include "mycylinder.h"
#include "mydiscretedynamicsworld.h"
#include "shox.h"

HalfShoxPart::HalfShoxPart(const PositionInfo &origin, real_t mass, real_t radius, real_t len, real_t setup_width, bool is_left)
    :MyCompoundBody(origin, mass)
    ,_setup_width(setup_width)
{
    MyCylinder *c = new MyCylinder(radius, len-1, radius, MyCylinder::X);
    real_t bw = 1.f;
    MyBox* b = new MyBox(2.f, bw, 2.f);

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

    addBody(mass-0.01f, c, xc, 0.f, 0.f, origin.yaw, origin.pitch, origin.roll);
    addBody(0.01f, b, xb, 0.f, 0.f , origin.yaw, origin.pitch, origin.roll);

    real_t l = (_setup_width - bw)/2.f;
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

    createSelf();
}

Shox::Shox(const PositionInfo &origin, real_t mass, real_t len, real_t travel)
    :_origin(origin)
    ,_len(len)
    ,_mass(mass)
    ,_travel(travel)
{
    _right_len = (_len-_travel-4)+1.f;
    _left_len = (_travel+4.f)+1.f;
    createLeftPart();
    createRightPart();
    makeLink();
}

void Shox::attach2World(MyDiscreteDynamicsWorld *world){
    if(_left != nullptr)
        _left->attach2World(world);

    if(_right != nullptr)
        _right->attach2World(world);

   if(_link != nullptr)
       world->theWorld()->addConstraint(_link, true);
}

void Shox::origin(const PositionInfo &o)
{
    _origin = o;
    PositionInfo lo( _origin.x-(_len-_left_len)/2.f, _origin.y, _origin.z, _origin.yaw, _origin.pitch, _origin.roll);
    _left->origin(lo);

    PositionInfo ro( _origin.x +(_len-_right_len)/2.f, _origin.y, _origin.z, _origin.yaw, _origin.pitch, _origin.roll);
    _right->origin(ro);
}

void Shox::createLeftPart()
{
    real_t m = _mass *(LEFT_MASS_FACTOR/(LEFT_MASS_FACTOR+RIGHT_MASS_FACTOR));
    PositionInfo origin( _origin.x-(_len-_left_len)/2.f, _origin.y, _origin.z);
    _left = new HalfShoxPart(origin, m, 1.5f, _left_len, setupWidth() );
    //_left->physics_body()->setAngularVelocity(btVector3(0, 100, 10));
    _left->color(255, 100, 0);
}

void Shox::createRightPart()
{
    real_t m = _mass *(RIGHT_MASS_FACTOR/(LEFT_MASS_FACTOR+RIGHT_MASS_FACTOR));
    PositionInfo origin( _origin.x +(_len-_right_len)/2.f, _origin.y, _origin.z);
    _right = new HalfShoxPart(origin, m, 2.5f, _right_len, setupWidth(), false);
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
    _link->setLimit(0, -_travel, 0);
    _link->setLimit(1, 0, 0);
    _link->setLimit(2, 0, 0);
    _link->setLimit(3, 0, 0);
    _link->setLimit(4, 0, 0);
    _link->setLimit(5, 0, 0);
    _link->enableSpring(0, true);
    _link->setStiffness(0, 450);
    _link->setDamping(0, 10);
    _link->setEquilibriumPoint();

    //_link = new btFixedConstraint(*(_left->physics_body()), *(_right->physics_body()), localA, localB);

}

void Shox::setup(MyDiscreteDynamicsWorld *world
                 , HalfShoxPart *part, const PositionInfo &part_point
                 , MyPhysicsBody *body_out, const PositionInfo &point_out
                 , MyPhysicsBody *body_in, const PositionInfo &point_in)
{
    {
        btTransform localA, localB;
        localA.setIdentity();
        localA.setOrigin( btVector3(part_point.x, part_point.y, part_point.z) );
        localB.setIdentity();
        localB.setOrigin(btVector3(point_out.x, point_out.y, point_out.z));
        btGeneric6DofConstraint* c1 =  new btGeneric6DofConstraint(
                    *(part->physics_body()), *(body_out->physics_body()), localA, localB, false);

        c1->setLimit(0,0,0);
        c1->setLimit(1,0,0);
        c1->setLimit(2,0,0);
        c1->setLimit(3,0,0);
        c1->setLimit(4,0,0);
        c1->setLimit(5, 1, -1);
        world->theWorld()->addConstraint(c1);


        btScalar z  = part_point.z;
        btVector3 part_point1(part_point.x, part_point.y, -z);
        localA.setIdentity();
        localA.setOrigin( part_point1 );
        localB.setIdentity();
        localB.setOrigin(btVector3(point_in.x, point_in.y, point_in.z));
        btGeneric6DofConstraint* c2 =  new btGeneric6DofConstraint(
                    *(part->physics_body()), *(body_in->physics_body()), localA, localB, false);

        c2->setLimit(5, 1, -1);
        world->theWorld()->addConstraint(c2);

    }
}
