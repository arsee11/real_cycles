#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "cyclessimulator.h"
#include <functional>

#include <QOpenGLWidget>
#include <QTimer>



class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(){
        this->showMaximized();
    }

    ~MyGLWidget(){}

signals:

public slots:
    void onTimeout();

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    QTimer* _timer;


    bodies_state_t _bodies_state;
    CyclesSimulator _simulator;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MYGLWIDGET_H
