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
#include "forkadapter.h"
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

    _world->setGravity(0.f, -10.f, 0.f);
    MyGround* g = new MyGround(900, 1000, 2, PositionInfo(0, -90, 0));
    g->color(MyBox::UP, Color(0,200,0));
    //g->physics_body()->setRestitution(1.f);
    g->physics_body()->setFriction(3.f);
    g->attach2World(_world);

    typedef TwoLinkerAdapter<BansheeRune::front_point1, BansheeRune::front_point2
            ,BansheeRune::rear_point1, BansheeRune::rear_point2
            ,BansheeRune::linker1, BansheeRune::linker2
            > banshee_rune_linker_adapter_t;

    typedef NormalShoxAdapter<BansheeRune::front_shox_point
            ,BansheeRune::rear_shox_point
            ,Shox
            > bashee_rune_shox_adapter_t;

    typedef Frame<FrameFrontPart, FrameSteadyRearPart, banshee_rune_linker_adapter_t, bashee_rune_shox_adapter_t>  frame_t;
    frame_t *f = new frame_t(PositionInfo(0,0, -40), 114.2, 43);
    frame_t::front_param_t fp = {3.f ,12.f, 65.f, 60.f, 43.f, 74.5f, 42.f, 34.f, 72.f, 59.f};
    frame_t::rear_param_t rp = {1.f, 37.f, 41.f, 23.f, 15.f, 8.f};
    banshee_rune_linker_adapter_t* ls = new banshee_rune_linker_adapter_t(6.f, 7.f);
    bashee_rune_shox_adapter_t* ss = new bashee_rune_shox_adapter_t( new Shox(PositionInfo(0.f, 0.f, 0.f), 0.5f, 22.0f, 5.5f) );
    f->create(_world, fp, rp, ls, ss);

    Fork* fork = new Fork(PositionInfo(50, 0, -40, torads(90), -torads((90-66))), 2.0, 16, 70, 20, 10);
    fork->attach2world(_world);

    ForkAdapter<frame_t, Fork> fa(f, fork);
    fa.setup(_world);

    //WorkShop::setupFrame();
    //WorkShop::setupFork();
    //WorkShop::setupWheels();

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
    //glRotatef(90, 0, 1, 0);
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
