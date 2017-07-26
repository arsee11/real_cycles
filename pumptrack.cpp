#include "pumptrack.h"
#include "mydiscretedynamicsworld.h"
#include <BulletCollision/CollisionShapes/btConcaveShape.h>
#include <BulletCollision/CollisionShapes/btTriangleCallback.h>
#include <QGL>
#include <functional>

class GlDrawcallback : public btTriangleCallback
{

public:

    bool	m_wireframe;

    GlDrawcallback()
        :m_wireframe(false)
    {
    }

    virtual void processTriangle(btVector3* triangle,int partId, int triangleIndex)
    {

        (void)triangleIndex;
        (void)partId;


        if (m_wireframe)
        {
            glBegin(GL_LINES);
            glColor3f(1, 0, 0);
            glVertex3d(triangle[0].getX()/FACTOR, triangle[0].getY()/FACTOR, triangle[0].getZ()/FACTOR);
            glVertex3d(triangle[1].getX()/FACTOR, triangle[1].getY()/FACTOR, triangle[1].getZ()/FACTOR);
            glColor3f(0, 1, 0);
            glVertex3d(triangle[2].getX()/FACTOR, triangle[2].getY()/FACTOR, triangle[2].getZ()/FACTOR);
            glVertex3d(triangle[1].getX()/FACTOR, triangle[1].getY()/FACTOR, triangle[1].getZ()/FACTOR);
            glColor3f(0, 0, 1);
            glVertex3d(triangle[2].getX()/FACTOR, triangle[2].getY()/FACTOR, triangle[2].getZ()/FACTOR);
            glVertex3d(triangle[0].getX()/FACTOR, triangle[0].getY()/FACTOR, triangle[0].getZ()/FACTOR);
            glEnd();
        } else
        {
            glBegin(GL_TRIANGLES);
            //glColor3f(1, 1, 1);


            glVertex3d(triangle[0].getX()/FACTOR, triangle[0].getY()/FACTOR, triangle[0].getZ()/FACTOR);
            glVertex3d(triangle[1].getX()/FACTOR, triangle[1].getY()/FACTOR, triangle[1].getZ()/FACTOR);
            glVertex3d(triangle[2].getX()/FACTOR, triangle[2].getY()/FACTOR, triangle[2].getZ()/FACTOR);

            glVertex3d(triangle[2].getX()/FACTOR, triangle[2].getY()/FACTOR, triangle[2].getZ()/FACTOR);
            glVertex3d(triangle[1].getX()/FACTOR, triangle[1].getY()/FACTOR, triangle[1].getZ()/FACTOR);
            glVertex3d(triangle[0].getX()/FACTOR, triangle[0].getY()/FACTOR, triangle[0].getZ()/FACTOR);
            glEnd();
        }
    }
};



static btVector3*	gGroundVertices=0;
static int*	gGroundIndices=0;
static btBvhTriangleMeshShape* trimeshShape =0;
static btRigidBody* staticBody = 0;
static float waveheight = 5.f;

const float TRIANGLE_SIZE=8.f;


static real_t ysinx(real_t x, real_t A, real_t w)
{
   return A*sin(w*x);
}

typedef std::function<real_t(real_t)> yfunctor_delegate;

using namespace std::placeholders;
yfunctor_delegate yfouctor = std::bind(ysinx, _1, 20, 0.15);

static btCollisionShape* buildTriangleMeshShape()
{
    int i;
    int j;

    const int NUM_VERTS_X = 100;
    const int NUM_VERTS_Y = 30;
    const int totalVerts = NUM_VERTS_X*NUM_VERTS_Y;
    const int totalTriangles = 2*(NUM_VERTS_X-1)*(NUM_VERTS_Y-1);

    gGroundVertices = new btVector3[totalVerts];
    gGroundIndices = new int[totalTriangles*3];

    int u_start_x = 20;
    int u_start_y = 10;
    int u_radius = NUM_VERTS_X*0.5f;
    int u_deep = 5;

    for ( i=0;i<NUM_VERTS_X;i++)
    {
        for (j=0;j<NUM_VERTS_Y;j++)
        {
            real_t x = (i-NUM_VERTS_X*0.5f)*TRIANGLE_SIZE;
            real_t y = yfouctor(i);
            real_t z = (j-NUM_VERTS_Y*0.5f)*TRIANGLE_SIZE;
            gGroundVertices[i+j*NUM_VERTS_X].setValue(x, y, z);
        }
    }

    int vertStride = sizeof(btVector3);
    int indexStride = 3*sizeof(int);

    int index=0;
    for ( i=0;i<NUM_VERTS_X-1;i++)
    {
        for (int j=0;j<NUM_VERTS_Y-1;j++)
        {
            gGroundIndices[index++] = j*NUM_VERTS_X+i;
            gGroundIndices[index++] = j*NUM_VERTS_X+i+1;
            gGroundIndices[index++] = (j+1)*NUM_VERTS_X+i+1;

            gGroundIndices[index++] = j*NUM_VERTS_X+i;
            gGroundIndices[index++] = (j+1)*NUM_VERTS_X+i+1;
            gGroundIndices[index++] = (j+1)*NUM_VERTS_X+i;
        }
    }

    btTriangleIndexVertexArray* indexVertexArrays = new btTriangleIndexVertexArray(totalTriangles,
        gGroundIndices,
        indexStride,
        totalVerts,(btScalar*) &gGroundVertices[0].x(),vertStride);

    bool useQuantizedAabbCompression = true;

    btCollisionShape* groundShape = new btBvhTriangleMeshShape(indexVertexArrays,useQuantizedAabbCompression);
    groundShape->setMargin(0.5);

    return groundShape;
}


PumpTrack::PumpTrack(const PositionInfo &origin)
    :MyRigidBody(origin)
{
    btCollisionShape* shape = buildTriangleMeshShape();
    createPhysicsBody(shape, 0);
}

void PumpTrack::render(const BodyTransInfo &info)
{
    glPushMatrix();
    glTranslatef(info.x/FACTOR, info.y/FACTOR, info.z/FACTOR);

    glColor3f(_color.r/255.f, _color.g/255.f, _color.b/255.f );
    if (_shape->getShapeType() == TRIANGLE_MESH_SHAPE_PROXYTYPE)
    {
        btConcaveShape* concaveMesh = (btConcaveShape*) _shape;

        GlDrawcallback drawCallback;
        drawCallback.m_wireframe = true;

        btVector3 aabbMin(0,0,0),aabbMax(0,0,0);
        //m_dynamicsWorld->getBroadphase()->getBroadphaseAabb(aabbMin,aabbMax);

        aabbMin-=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);
        aabbMax+=btVector3(BT_LARGE_FLOAT,BT_LARGE_FLOAT,BT_LARGE_FLOAT);

        concaveMesh->processAllTriangles(&drawCallback,aabbMin,aabbMax);

    }
    glPopMatrix();
}
