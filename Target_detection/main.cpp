#include "mainwindow.h"
#include <QApplication>
#include "tool.h"
#include "cartest.h"
#include "realtimedetection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    tool t;
    t.hide();
    CarTest c;
    c.hide();
    RealTimeDetection r;
    r.hide();


    return a.exec();
}
