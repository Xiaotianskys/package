#ifndef ACTUALOPERATION_H
#define ACTUALOPERATION_H
//#define numb 47

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <QPushButton>
#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QLabel>
#include <QTextBrowser>

using namespace cv;
using namespace std;
using namespace cv::face;

namespace Ui {
class ActualOperation;
}

class ActualOperation : public QWidget
{
    Q_OBJECT

public:
    explicit ActualOperation(QWidget *parent = 0);
    void detectactualsite();
    ~ActualOperation();

private:
    Ui::ActualOperation *ui;
    int numb;
};

#endif // ACTUALOPERATION_H
