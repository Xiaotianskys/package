#ifndef DEAL_FILE_H
#define DEAL_FILE_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QFile>

namespace Ui {
class Deal_File;
}

class Deal_File : public QWidget
{
    Q_OBJECT

public:
    explicit Deal_File(QWidget *parent = 0);
    ~Deal_File();

private slots:
    void on_readfile_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Deal_File *ui;
};

#endif // DEAL_FILE_H
