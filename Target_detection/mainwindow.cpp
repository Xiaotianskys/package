#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tool.h"
#include "ui_tool.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QPushButton>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Argus"));
    ui->passwordbox->setEchoMode(QLineEdit::Password);
    setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //获取文本框中的信息
    QString strU = ui->usernamebox ->text();
    QString strP = ui->passwordbox->text();

    if(strU==NULL)
        QMessageBox::warning(NULL,"warning","帐号不能为空");
    else if(strP==NULL)
        QMessageBox::warning(NULL,"warning","密码不能为空");
    else if(strU =="admin" && strP=="123"){
        QMessageBox::information(NULL, "sucessful", "登陆成功");
        this->hide();
        tools->show();
    }
    else
        QMessageBox::critical(NULL, "fail", "登陆失败");
}
