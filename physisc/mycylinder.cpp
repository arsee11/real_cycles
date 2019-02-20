#include "mycylinder.h"
#include "mydynamicsworld.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QDebug>
#include "cylinder.h"

MyCylinder::MyCylinder(real_t base_radius, real_t height, real_t top_radius, const PositionInfo& origin, real_t mass, AroundType type)
    :MyRigidBody(origin)
    ,_base_radius(base_radius)
    ,_height(height)
    ,_top_radius(top_radius)
    ,_mass(mass)
    ,_around_type(type)
{
    btCollisionShape* shape;
    if(type == AroundType::X)
        shape = new btCylinderShapeX(btVector3(height/2.f, base_radius,  top_radius));
    else  if(type == AroundType::Z)
        shape = new btCylinderShapeZ(btVector3(base_radius, top_radius,height/2.f));
    else
        shape = new btCylinderShape(btVector3( base_radius, height/2.f, top_radius));

    createPhysicsBody(shape, mass);
}

MyCylinder::MyCylinder(real_t base_radius, real_t height, real_t top_radius, AroundType type)
    :_base_radius(base_radius)
    ,_height(height)
    ,_top_radius(top_radius)
    ,_around_type(type)
{
    if(type == AroundType::X)
        _shape = new btCylinderShapeX(btVector3(height/2.f, base_radius,  top_radius));
    else  if(type == AroundType::Z)
        _shape = new btCylinderShapeZ(btVector3(base_radius, top_radius,height/2.f));
    else
        _shape = new btCylinderShape(btVector3( base_radius, height/2.f, top_radius));
}


void MyCylinder::render(const BodyTransInfo &info)
{
    glColor3f(_color.r/255.f, _color.g/255.f, _color.b/255.f);
    glPushMatrix();

    glTranslatef(info.x/FACTOR, info.y/FACTOR, info.z/FACTOR);
    glRotatef(info.degrees(), info.axis_x, info.axis_y, info.axis_z);
    if(_around_type == AroundType::X)
    {
        CylinderX c(_base_radius/FACTOR, _top_radius/FACTOR, _height/FACTOR);
        c.draw();
    }
    else if(_around_type == AroundType::Y)
    {
        CylinderY c(_base_radius/FACTOR, _top_radius/FACTOR, _height/FACTOR);
        c.draw();
    }
    else
    {
        CylinderZ c(_base_radius/FACTOR, _top_radius/FACTOR, _height/FACTOR);
        c.draw();
    }   

    glPopMatrix();
}
