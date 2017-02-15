#include "cube.h"
#include "forkupper.h"
#include "forkbottom.h"
#include "mybox.h"
#include "mycylinder.h"
#include "myglwidget.h"
#include "myground.h"
#include "framefrontpart.h"
#include "framesteadyrearpart.h"
#include "innerlinker.h"
#include "shox.h"
#include "ring.h"
#include "cylinder.h"
#include "fork.h"
#include "frame.h"
#include "twolinkersetup.h"
#include "bansheerune.h"
#include "inneroutlinker.h"
#include "normalshoxsetup.h"
#include "myconvexhullbody.h"
#include "mytubebody.h"
#include <GL/glu.h>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QDebug>


void MyGLWidget::onWorldStateChanged(const bodies_state_t& states)
{
     _bodies_state = states;
    this->update();
}

void MyGLWidget::onTimeout()
{
    if(_world!= nullptr)
        _world->doSimulation();
}

void MyGLWidget::initializeGL()
{
    _world = new MyDiscreteDynamicsWorld(std::bind(&MyGLWidget::onWorldStateChanged, this, std::placeholders::_1));

    _world->setGravity(0.f, 0.f, 0.f);
    MyGround* g = new MyGround(900, 1000, 2, PositionInfo(0, -90, 0));
    g->color(MyBox::UP, Color(0,200,0));
    //g->physics_body()->setRestitution(1.f);
    g->physics_body()->setFriction(3.f);
    //g->attach2World(_world);


    /*
    ///wheels
    MyPhysicsBody* wheel_b = new MyCylinder(40,10,40, PositionInfo(45, 0.f, -100.f), 3.0f, MyCylinder::AroundType::Z);
    wheel_b->color(255, 255, 0);
    wheel_b->attach2World(_world);

    MyPhysicsBody* box1 = new MyBox(15,10,15, PositionInfo(45, 0.f, -90.f), 1.0f);
    box1->attach2World(_world);

    {
        btTransform localA, localB;
        localA.setIdentity();
        localA.setOrigin( btVector3(0.f,  0.f,  5.f) );
        localB.setIdentity();
        localB.setOrigin(btVector3(0.f, 0.f, -5.f));
        btFixedConstraint* fc = new btFixedConstraint(*(wheel_b->physics_body()), *(box1->physics_body()), localA, localB);
        _world->theWorld()->addConstraint(fc);
    }

    MyPhysicsBody* wheel_s = new MyCylinder(30,6,30, PositionInfo(-45, 0.f, -102.f), 2.0f, MyCylinder::AroundType::Z);
    wheel_s->color(0, 255, 150);
    wheel_s->attach2World(_world);

    MyPhysicsBody* box2 = new MyBox(15,10,15, PositionInfo(-45, 0.f, -99.f), 1.0f);
    box2->attach2World(_world);

    {
        btTransform localA, localB;
        localA.setIdentity();
        localA.setOrigin( btVector3(0.f,  0.f,  3.f) );
        localB.setIdentity();
        localB.setOrigin(btVector3(0.f, 0.f, -5.f));
        btFixedConstraint* fc = new btFixedConstraint(*(wheel_s->physics_body()), *(box2->physics_body()), localA, localB);
        _world->theWorld()->addConstraint(fc);
    }

    MyBox*  frame = new MyBox(220.f, 40.f, 180.f, PositionInfo(0.f, 1.f, -135.f), 0.f);
    frame->color(0,0,255);
     frame->attach2World(_world);

     {
        btTransform localA, localB;
        localA.setIdentity();
        localA.setOrigin( btVector3(45.f,  -1.f,  20.f) );
        localB.setIdentity();
        localB.setOrigin(btVector3(0.f, 0.f, -5.f));
        btGeneric6DofSpring2Constraint* _6dof_wb =  new btGeneric6DofSpring2Constraint(
                    *(frame->physics_body()), *(wheel_b->physics_body()), localA, localB);

        _6dof_wb->setLimit(0, 0, 0);
        _6dof_wb->setLimit(1, 0, 0);
        _6dof_wb->setLimit(2, 1, 0);
        _6dof_wb->setLimit(3, 0, 0);
        _6dof_wb->setLimit(4, 0, 0);
        _6dof_wb->setLimit(5, 1, -1);
       _world->theWorld()->addConstraint(_6dof_wb);
     }

   {
       btTransform localA, localB;
       localA.setIdentity();
       localA.setOrigin( btVector3(-45.f, -1.f, 20.f) );
       localB.setIdentity();
       localB.setOrigin(btVector3(0.f,  0.f,  -3.f));
       btGeneric6DofSpring2Constraint* _6dof_ws =  new btGeneric6DofSpring2Constraint(
                   *(frame->physics_body()), *(wheel_s->physics_body()), localA, localB);

       _6dof_ws->setLimit(0, 0, 0);
       _6dof_ws->setLimit(1, 0, 0);
       _6dof_ws->setLimit(2, 0, 0);
       _6dof_ws->setLimit(3, 0, 0);
       _6dof_ws->setLimit(4, 0, 0);
       _6dof_ws->setLimit(5, 1, -1);
       _6dof_ws->enableMotor(5, true);
       _6dof_ws->setTargetVelocity(5,-10.f);
       _6dof_ws->setMaxMotorForce(5,100.f);
      _world->theWorld()->addConstraint(_6dof_ws);
     }

     {
        btVector3	axisA(0,0,1);
         btVector3	axisB(0,0,1);
         btGearConstraint* gear = new btGearConstraint(*(wheel_b->physics_body()),*(wheel_s->physics_body()), axisA,axisB, 30.f/40.f);
         _world->theWorld()->addConstraint(gear);
    }
    ///wheels///
     */


     /*MyCylinder* _left_leg = new MyCylinder(1.5f, 10.f, 1.5f, btVector3(-7.f, 0, -10.f), 1.f, MyCylinder::Y);
     _left_leg->color(255, 0, 0);
     _left_leg->physics_body()->setAngularVelocity(btVector3(0, 0, 5));
     _left_leg->attach2World(_world);
    */

    /*real_t z = -10.f;
    FrameFrontPart* f = new FrameFrontPart(PositionInfo(0,0.f, z), 3.f ,12.f, 65.f, 60.f, 43.f, 74.5f, 42.f, 34.f, 72.f, 59.f); //bashee rune size M
    //FrameFrontPart* f = new FrameFrontPart(PositionInfo(0,0.f,0), 4.f ,12.5f, 63.f, 60.f,40.f, 72.f,40.f, 34.6f,70.f, 61.4f, 60.f, 20.f); //bashee lenged size M
    f->setupUpLinkPoint(0, 25, 4, FrameFrontPart::BASE_SEAT);
    f->setupBottomLinkPoint(4, 4, 4, FrameFrontPart::BASE_BB);
    f->setupShoxLinkPoint(35, 6, 4, FrameFrontPart::BASE_BOTTOM);
    f->create();
    f->attach2World(_world);

    FrameSteadyRearPart* r = new FrameSteadyRearPart(PositionInfo(0,0,0), 1.f, 37.f, 41.f, 23.f, 15, 10); //bashee rune size M
    r->setupBottomLinkPoint(0, 5);
    r->setupUpLinkPoint(0, 5);
    r->setupShoxLinkPoint(13, 0, 4);
    r->create();
    real_t CSL = 43.f;
    PositionInfo bb_origin = f->worldOrigin4BB();
    const Cube& cube = r->cube();
    real_t x = bb_origin.x - (cube.len()/2.f + CSL-cube.len());

    real_t y = bb_origin.y + cube.height()/2.f;
    r->origin(PositionInfo(x, y,z));
    r->attach2World(_world);
    */

    typedef TwoLinkerSetup<BansheeRune::front_point1, BansheeRune::front_point2
            ,BansheeRune::rear_point1, BansheeRune::rear_point2
            ,BansheeRune::linker1, BansheeRune::linker2
            > banshee_rune_linker_setup_t;

    typedef NormalShoxSetup<BansheeRune::front_shox_point
            ,BansheeRune::rear_shox_point
            ,Shox
            > bashee_rune_shox_setup_t;

    /*typedef Frame<FrameFrontPart, FrameSteadyRearPart, banshee_rune_linker_setup_t, bashee_rune_shox_setup_t>  frame_t;
    frame_t *f = new frame_t(PositionInfo(0,0, 0), 114.2, 43);
    frame_t::front_param_t fp = {3.f ,12.f, 65.f, 60.f, 43.f, 74.5f, 42.f, 34.f, 72.f, 59.f};
    frame_t::rear_param_t rp = {1.f, 37.f, 41.f, 23.f, 15.f, 8.f};
    banshee_rune_linker_setup_t* ls = new banshee_rune_linker_setup_t(6.f, 7.f);
    bashee_rune_shox_setup_t* ss = new bashee_rune_shox_setup_t( new Shox(PositionInfo(0.f, 0.f, 0.f), 0.5f, 22.0f, 5.5f) );
    f->create(_world, fp, rp, ls, ss);

    /*
     Linker* l = new InnerLinker(btVector3(4, -10, -10), 0.1f, 10.f, 6.f, 6.f);
     l->attach2World(_world);
     l->makeLeftLink(_world, r, btVector3(30,8,0), btVector3(0,0,1));
     l->makeRightLink(_world, f, btVector3(-21,-10,0), btVector3(0,0,1));

     Linker* l2 = new InnerLinker(btVector3(8, -23, -10), 0.1f, 10.f, 6.f, 6.f);
     l2->attach2World(_world);
     l2->makeLeftLink(_world, r, btVector3(30,-5,0), btVector3(0,0,1));
     l2->makeRightLink(_world, f, btVector3(-17,-23,0), btVector3(0,0,1));
   */

    MyPhysicsBody* box = new MyBox(5,5,14, PositionInfo(0, 30,-30), 20.0f);
    box->color(255,0,0);
    box->physics_body()->setLinearVelocity(btVector3(0,-10,0));
    //box->attach2World(_world);

     Vex vexs[]={{15,5,10},{-15,5,10},{15,-5,10},{-15,-5,10}
        ,{15,5,-10},{-15,5,-10},{15,-5,-10},{-15,-5,-10}
    };

    MyConvexHullBody * chb = new MyConvexHullBody(PositionInfo(0,10,-10), 1, vexs, 8);
   chb->color(255,0,0);
    //chb->attach2World(_world);
    MyTubeBody* mtb = new MyTubeBody(55, 45, 15, PositionInfo(0,0,0), 1);
    mtb->attach2World(_world);

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    _timer->start(1);

    glEnable(GL_DEPTH_TEST);
     //   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.f ,0.f ,0.f,1.f);
    glColor3f(1.f, 0.f, 0.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0.6, 0, 0,0,0, 0, 1,0);

   // glMatrixMode(GL_PROJECTION);
    //glOrtho(-100, 100, -100, 100, -100, 200);
    //glFrustum(-100, 100, -100, 100, 0.1, 200);
}

void MyGLWidget::resizeGL(int w, int h)
{
    h = h>0?h:1.f;
    int l = w>h?h:w;

    glViewport(0, 0, l, l);
    glMatrixMode(GL_PROJECTION);//选择投影矩阵
    glLoadIdentity();//重置选择好的投影矩阵
    gluPerspective(100, (GLfloat)w/(GLfloat)h,0.1, 10.0f);//建立透视投影矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

extern void tube_draw(real_t out_radius, real_t in_radius, real_t len);


void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -0.5f);
    glRotatef(40, 0, 1, 0);
    for(auto i : _bodies_state)
    {
            i.body->render(i);
    }

        //x axis
        glBegin(GL_LINES);
            glColor3f(255,255,0);
            glVertex3f(1, 0, 0);
            glVertex3f(-1, 0, 0);
         glEnd();

         //y axis
         glBegin(GL_LINES);
             glColor3f(0, 255,255);
             glVertex3f(0, 1, 0);
             glVertex3f(0, -1, 0);
          glEnd();

          //z axis
          glBegin(GL_LINES);
              glColor3f(255, 0,255);
              glVertex3f(0, 0, 1);
              glVertex3f(0, 0, -1);
           glEnd();

       //tube_draw(0.15, 0.07, 0.3);


}
