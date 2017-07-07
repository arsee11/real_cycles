#include "mybox.h"
#include "mydiscretedynamicsworld.h"
#include <QGL>
#include <QDebug>
#include <GL/gl.h>

MyBox::MyBox(real_t l, real_t w, real_t h, const PositionInfo& origin, btScalar mass)
     :MyPhysicsBody(origin)
     ,_len(l)
    ,_width(w)
    ,_height(h)
    ,_cube (l/FACTOR, w/FACTOR, h/FACTOR)
{
    btBoxShape* shape = new btBoxShape(btVector3(l/2.f, h/2.f, w/2.f));
    createPhysicsBody(shape, mass);
}

MyBox::MyBox(real_t l, real_t w, real_t h)
    :_len(l)
    ,_width(w)
    ,_height(h)
    ,_cube (l/FACTOR, w/FACTOR, h/FACTOR)
{
    _shape = new btBoxShape(btVector3(l/2.f, h/2.f, w/2.f));
}

void MyBox::render(const BodyTransInfo& i)
{
    glPushMatrix();
    glTranslatef(i.x/FACTOR, i.y/FACTOR, i.z/FACTOR);
    glRotatef(i.degrees(), i.axis_x, i.axis_y, i.axis_z);
    _cube.draw();
    /*glColor3f(_color.r/255.f, _color.g/255.f, _color.b/255.f );
    static int indices[36] = {
        0,1,2,
        3,2,1,
        4,0,6,
        6,0,2,
        5,1,4,
        4,1,0,
        7,3,1,
        7,1,5,
        5,4,7,
        7,4,6,
        7,2,3,
        7,6,2};

    btVector3 halfExtent(_len/2/FACTOR, _height/2/FACTOR, _width/2/FACTOR);
    btVector3 vertices[8]={
        btVector3(halfExtent[0],halfExtent[1],halfExtent[2]),
        btVector3(-halfExtent[0],halfExtent[1],halfExtent[2]),
        btVector3(halfExtent[0],-halfExtent[1],halfExtent[2]),
        btVector3(-halfExtent[0],-halfExtent[1],halfExtent[2]),
        btVector3(halfExtent[0],halfExtent[1],-halfExtent[2]),
        btVector3(-halfExtent[0],halfExtent[1],-halfExtent[2]),
        btVector3(halfExtent[0],-halfExtent[1],-halfExtent[2]),
        btVector3(-halfExtent[0],-halfExtent[1],-halfExtent[2])
    };

    glBegin (GL_TRIANGLES);
    int si=36;
    for (int i=0;i<si;i+=3)
    {
        const btVector3& v1 = vertices[indices[i]];;
        const btVector3& v2 = vertices[indices[i+1]];
        const btVector3& v3 = vertices[indices[i+2]];
        btVector3 normal = (v3-v1).cross(v2-v1);
        normal.normalize ();
        glNormal3f(normal.getX(),normal.getY(),normal.getZ());
        glVertex3f (v1.x(), v1.y(), v1.z());
        glVertex3f (v2.x(), v2.y(), v2.z());
        glVertex3f (v3.x(), v3.y(), v3.z());
    }*/
    glEnd();
    glPopMatrix();


}

void MyBox::color(int r, int g, int b)
{
    for(int i=0; i<6; i++)
        color((Face)i, Color(r,g,b));

    _color = Color(r, g,b);
}
