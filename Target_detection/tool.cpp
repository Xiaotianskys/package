#include "tool.h"
#include "ui_tool.h"
#include "cartest.h"
#include "ui_cartest.h"
#include "realtimedetection.h"
#include "ui_realtimedetection.h"
#include "mydialog.h"
#include "ui_mydialog.h"
#include "tracking.h"
#include "ui_tracking.h"

tool::tool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tool)
{
    ui->setupUi(this);
    setWindowTitle(tr("工具"));
}

tool::~tool()
{
    delete ui;
}

void tool::on_pushButton_clicked()
{
    car->show();
}

void tool::on_pushButton_2_clicked()
{
    car1->show();
}

void tool::on_pushButton_3_clicked()
{
    count->show();
}

void tool::on_pushButton_4_clicked()
{
    trackAnything->show();
}
