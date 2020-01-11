#ifndef GE__CSV_H
#define GE__CSV_H

#include <QWidget>
#include <iostream>
#include <QProcess>
#include <QString>
#include <string>

using namespace std;

namespace Ui {
class Ge__CSV;
}

class Ge__CSV : public QWidget
{
    Q_OBJECT

public:
    explicit Ge__CSV(QWidget *parent = 0);
    void callexe();
    ~Ge__CSV();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ge__CSV *ui;
};

#endif // GE__CSV_H
