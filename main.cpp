#include "mybox.h"
#include "mydynamicsworld.h"
#include "myglwidget.h"
#include <myground.h>
#include <QApplication>
#include <QDebug>

void callback(const bodies_state_t&)
{
    qDebug()<<"callback";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGLWidget w;
    w.show();
    return a.exec();
}
