#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include "cartest.h"
#include "realtimedetection.h"
#include "mydialog.h"
#include "tracking.h"

namespace Ui {
class tool;
}

class tool : public QWidget
{
    Q_OBJECT

public:
    explicit tool(QWidget *parent = 0);
    ~tool();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::tool *ui;
    CarTest *car = new CarTest;
    RealTimeDetection *car1 = new RealTimeDetection;
    MyDialog *count = new MyDialog;
    Tracking *trackAnything = new Tracking;
};

#endif // TOOL_H
