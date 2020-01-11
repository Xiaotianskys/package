#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->collectface,&QPushButton::clicked,this,&Widget::openwincolface);
    connect(ui->gecsv,&QPushButton::clicked,this,&Widget::openwingecsv);
    connect(ui->training_it,&QPushButton::clicked,this,&Widget::openwintrain);
    connect(ui->identify,&QPushButton::clicked,this,&Widget::openwindetect);
    connect(ui->file,&QPushButton::clicked,this,&Widget::openwindealfile);
    connect(ui->actualsite,&QPushButton::clicked,this,&Widget::openwinactualopreate);
}

void Widget::openwincolface()
{
    CL_F->show();
}

void Widget::openwingecsv()
{
    G_CSV->show();
}

void Widget::openwindetect()
{
    DE_F->show();
}

void Widget::openwintrain()
{
    T_ing->show();
}

void Widget::openwindealfile()
{
    DEL_F->show();
}

void Widget::openwinactualopreate()
{
    AC_OP->show();
}

Widget::~Widget()
{
    delete ui;
}
