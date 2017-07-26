#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "mydiscretedynamicsworld.h"
#include <functional>

#include <QOpenGLWidget>


class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyGLWidget(){
        this->showMaximized();
    }

    void onWorldStateChanged(const bodies_state_t &states);
signals:

public slots:
    void onTimeout();

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    QTimer* _timer;
    MyDynamicsWorld* _world=nullptr;

    bodies_state_t _bodies_state;
    void createFork();
};

#endif // MYGLWIDGET_H
