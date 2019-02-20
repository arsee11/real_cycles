#include "myconvexhullbody.h"
#include <mydynamicsworld.h>
#include <QDebug>
#include <memory>
#include <GL/gl.h>
#include <BulletCollision/CollisionShapes/btConvexPolyhedron.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

MyConvexHullBody::MyConvexHullBody(const PositionInfo &origin, real_t mass, const Vex vexs[], int size_vexs)
    :MyRigidBody(origin)
{
    btConvexHullShape *shape = new btConvexHullShape();
     for(int i=0; i<size_vexs; i++)
    {
        const Vex& v = vexs[i];
       shape->addPoint(btVector3(v.x, v.y, v.z));
    }

    shape->initializePolyhedralFeatures();
    this->createPhysicsBody(shape, mass);
}

MyConvexHullBody::MyConvexHullBody(const Vex vexs[], int size_vexs)
{
    btConvexHullShape *shape = new btConvexHullShape();
    for(int i=0; i<size_vexs; i++)
    {
        const Vex& v = vexs[i];
        shape->addPoint(btVector3(v.x, v.y, v.z));
    }
    _shape = shape;
}

void MyConvexHullBody::render(const BodyTransInfo &info)
{
    glColor3f(_color.r/255.f, _color.g/255.f, _color.b/255.f);
    glPushMatrix();

    glTranslatef(info.x/FACTOR, info.y/FACTOR, info.z/FACTOR);
    glRotatef(info.degrees(), info.axis_x, info.axis_y, info.axis_z);

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
                    glVertex3f (v1.x(), v1.y(), v1.z());
                    glVertex3f (v2.x(), v2.y(), v2.z());
                    glVertex3f (v3.x(), v3.y(), v3.z());

                }
                glEnd ();

            }
        }
    }

    glPopMatrix();
}
