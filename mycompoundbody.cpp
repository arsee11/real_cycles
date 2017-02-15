#include "mycompoundbody.h"
#include <GL/gl.h>
#include <algorithm>

/*MyCompoundBody::ChildBody* MyCompoundBody::getBody(MyPhysicsBody *b)
{
    auto i = std::find_if(_bodies.begin(), _bodies.end()
                          , [b](ChildBody* cb){return b == cb->body;});
    if( i != _bodies.end())
        return (*i);

    return nullptr;
}
*/
MyCompoundBody::MyCompoundBody(const PositionInfo &origin, real_t mass)
    :MyPhysicsBody(origin)
    ,_mass(mass)
{
    this->_shape = new btCompoundShape();
}

MyCompoundBody::MyCompoundBody(real_t mass)
    :MyCompoundBody(PositionInfo(), mass)
{

}

MyCompoundBody::~MyCompoundBody()
{
    for(auto i : _bodies)
        delete i;

    _bodies.clear();
}

void MyCompoundBody::createSelf()
{
    if(_bodies.size() ==0)
        return;

    real_t* masses = new real_t[ _bodies.size()];
    for(size_t i=0; i<_bodies.size(); i++)
            masses[i] = _bodies[i]->mass;

    btTransform p;
    btVector3 localInertia(0,0,0);
    bool isDynamic = (_mass != 0.f);
    btCompoundShape* shape = static_cast<btCompoundShape*>(_shape);
    if (isDynamic)
        shape->calculatePrincipalAxisTransform(masses, p, localInertia);

    delete[] masses;
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(_origin.x, _origin.y, _origin.z));
    trans.setRotation(btQuaternion(_origin.yaw, _origin.pitch, _origin.roll));

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(trans);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(5.f,myMotionState,_shape,localInertia);
    _body = new btRigidBody(rbInfo);
    _body->setUserIndex(_id);
}

void MyCompoundBody::render(const BodyTransInfo &info)
{
    glColor3f(_color.r/255.f, _color.g/255.f, _color.b/255.f);
    glPushMatrix();
    glTranslatef(info.x/FACTOR, info.y/FACTOR, info.z/FACTOR);
    glRotatef(info.degrees(), info.axis_x, info.axis_y, info.axis_z);
    for(auto b : _bodies)
    {
        glPushMatrix();
        glTranslatef(b->trans.x/FACTOR, b->trans.y/FACTOR, b->trans.z/FACTOR);
        glRotatef(todegrees(b->trans.pitch), 1, 0, 0);
        glRotatef(todegrees(b->trans.yaw), 0, 1, 0);
        glRotatef(todegrees(b->trans.roll), 0, 0, 1);
        b->body->render(BodyTransInfo());
        glPopMatrix();
    }
    glPopMatrix();
}
