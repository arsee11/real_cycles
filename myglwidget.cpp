
#include "myglwidget.h"
#include <GL/glu.h>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include "myrigidbody.h"

void MyGLWidget::onTimeout()
{
   _simulator.doSimulation();
   _bodies_state = _simulator.getBodiesState();
   this->update();

}


void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        _simulator.controller()->turn(true);
    else if(event->key() == Qt::Key_Right)
        _simulator.controller()->turn(false);
    else if(event->key() == Qt::Key_H)
        _simulator.controller()->holdbar(0);
    else if(event->key() == Qt::Key_L)
        _simulator.controller()->lean(false);
    else if(event->key() == Qt::Key_K)
        _simulator.controller()->lean(true);

}

void MyGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        _simulator.controller()->endTurnning();
}

void MyGLWidget::initializeGL()
{
    _simulator.init();

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    _timer->start(1/30.f*1000);

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.f ,0.f ,0.f,1.f);
    glColor3f(1.f, 0.f, 0.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0.6, 0, 0,0,0, 0, 1,0);
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
}
