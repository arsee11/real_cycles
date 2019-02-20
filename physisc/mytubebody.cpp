#include "mytubebody.h"
#include "cylinder.h"
#include "ring.h"
#include "mydynamicsworld.h"
#include "myconvexhullbody.h"

#include <GL/gl.h>
#include <memory>
#include <tuple>
#include <BulletCollision/CollisionShapes/btConvexPolyhedron.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

MyTubeBody::MyTubeBody(real_t out_radius_top, real_t in_radius_top
                       , real_t out_radius_bottom, real_t in_radius_bottom
                       , real_t len, const PositionInfo &origin, real_t mass)
    :MyCompoundBody(origin, mass)
    ,_outr_t(out_radius_top),_inr_t(in_radius_top)
    ,_outr_b(out_radius_bottom),_inr_b(in_radius_bottom)
    ,_len(len)
{
    int slices = 60;
    real_t a = 2*MY_PI / slices;
    Vex  slicev[8];
    Vex v1;
    v1.x = _inr_b * sin( a/2 );
    v1.y = - _len/2;
    v1.z = (_outr_b - _inr_b)/2;
    Vex v2( -v1.x, v1.y, v1.z);
    slicev[0] = v1;
    slicev[1] = v2;

    Vex v3;
    v3.x = _outr_b * sin( a/2 );
    v3.y = - _len/2;
    v3.z = -(_outr_b - _inr_b)/2;
    Vex v4( -v3.x, v3.y, v3.z);
    slicev[2] = v3;
    slicev[3] = v4;

    Vex v5;
    v5.x = _inr_t * sin( a/2 );
    v5.y = _len/2;
    v5.z = (_outr_t - _inr_t)/2;
    Vex v6( -v5.x, v5.y, v5.z);
    slicev[4] = v5;
    slicev[5] = v6;

    Vex v7;
    v7.x = _outr_t * sin( a/2 );
    v7.y =  _len/2;
    v7.z = -(_outr_b - _inr_b)/2;
    Vex v8( -v7.x, v7.y, v7.z);
    slicev[6] = v7;
    slicev[7] = v8;

    Vex vs[36];
    for (int i=0;i<36;i+=3)
    {
       vs[i] = slicev[ BOX_INDICES[i]];
    }
    for(int i=0; i<slices; i++)
    {
        MyConvexHullBody *h = new MyConvexHullBody(vs, 36);
        real_t x = (_inr_b+(_outr_b-_inr_b)/2.f) * cos( 2*MY_PI/slices * i);
        real_t y = 0.f;
        real_t z = (_inr_b+(_outr_b-_inr_b)/2.f) * sin( 2*MY_PI/slices * i);
        real_t yaw = MY_PI/2.f - 2*MY_PI/slices * i;
        addBody(h, origin, mass/slices);
    }
}

int MyTubeBody::buildVertexs(Vex** vexs)
{

}

void MyTubeBody::render(const BodyTransInfo &info)
{
    glColor3f(_color.r/255.f, _color.g/255.f, _color.b/255.f);
    glPushMatrix();

    glTranslatef(info.x/FACTOR, info.y/FACTOR, info.z/FACTOR);
    glRotatef(info.degrees(), info.axis_x, info.axis_y, info.axis_z);

    /*RingY r_top(_outr_t/FACTOR, _inr_t/FACTOR,_len/2.f/FACTOR);
    CylinderY c_out(_outr_t/FACTOR, _outr_b/FACTOR, _len/FACTOR);
    CylinderY c_in(_inr_t/FACTOR, _inr_b/FACTOR, _len/FACTOR);
    RingY r_bottom(_outr_b/FACTOR, _inr_b/FACTOR,-_len/2.f/FACTOR);
    r_top.draw();
    c_out.draw();
    c_in.draw();
    r_bottom.draw();
    */
    if (_shape->isConvex())
    {
        const btConvexPolyhedron *poly = _shape->isPolyhedral() ? ((btPolyhedralConvexShape*) _shape)->getConvexPolyhedron() : 0;
        if (poly)
        {
            int i;
            glBegin (GL_TRIANGLES);
            for (i=0;i<poly->m_faces.size();i++)
            {
                btVector3 centroid(0,0,0);
                int numVerts = poly->m_faces[i].m_indices.size();
                if (numVerts>2)
                {
                    btVector3 v1 = poly->m_vertices[poly->m_faces[i].m_indices[0]];
                    for (int v=0;v<poly->m_faces[i].m_indices.size()-2;v++)
                    {

                        btVector3 v2 = poly->m_vertices[poly->m_faces[i].m_indices[v+1]];
                        btVector3 v3 = poly->m_vertices[poly->m_faces[i].m_indices[v+2]];
                        btVector3 normal = (v3-v1).cross(v2-v1);
                        normal.normalize ();
                        glNormal3f(normal.getX(),normal.getY(),normal.getZ());
                        glVertex3f (v1.x()/FACTOR, v1.y()/FACTOR, v1.z()/FACTOR);
                        glVertex3f (v2.x()/FACTOR, v2.y()/FACTOR, v2.z()/FACTOR);
                        glVertex3f (v3.x()/FACTOR, v3.y()/FACTOR, v3.z()/FACTOR);
                    }
                }
            }
            glEnd ();
        } else
        {
            float red=0.1;
            std::auto_ptr<btShapeHull> hull( new btShapeHull( (btConvexShape*)_shape) );
            hull->buildHull(_shape->getMargin());
            if (hull->numTriangles () > 0)
            {
                int index = 0;
                const unsigned int* idx = hull->getIndexPointer();
                const btVector3* vtx = hull->getVertexPointer();

                glBegin (GL_TRIANGLES);

                for (int i = 0; i < hull->numTriangles (); i++)
                {
                    int i1 = index++;
                    int i2 = index++;
                    int i3 = index++;
                    btAssert(i1 < hull->numIndices () &&
                        i2 < hull->numIndices () &&
                        i3 < hull->numIndices ());

                    int index1 = idx[i1];
                    int index2 = idx[i2];
                    int index3 = idx[i3];
                    btAssert(index1 < hull->numVertices () &&
                        index2 < hull->numVertices () &&
                        index3 < hull->numVertices ());

                    btVector3 v1 = vtx[index1];
                    btVector3 v2 = vtx[index2];
                    btVector3 v3 = vtx[index3];
                    btVector3 normal = (v3-v1).cross(v2-v1);
                    normal.normalize ();
                    glNormal3f(normal.getX(),normal.getY(),normal.getZ());
                   // glVertex3f (v1.x(), v1.y(), v1.z());
                    //glVertex3f (v2.x(), v2.y(), v2.z());
                   // glVertex3f (v3.x(), v3.y(), v3.z());
                    red += 0.05;
                    glColor3f(red, 0,0);
                    glVertex3f (v1.x()/FACTOR, v1.y()/FACTOR, v1.z()/FACTOR);
                    glVertex3f (v2.x()/FACTOR, v2.y()/FACTOR, v2.z()/FACTOR);
                    glVertex3f (v3.x()/FACTOR, v3.y()/FACTOR, v3.z()/FACTOR);

                }
                glEnd ();

            }
        }

    }

    glPopMatrix();
}
