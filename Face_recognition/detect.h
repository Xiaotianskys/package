#ifndef DETECT_H
#define DETECT_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <QPushButton>
#include <iostream>
#include <QString>
//#define numb 47

using namespace cv;
using namespace std;
using namespace cv::face;

namespace Ui {
class Detect;
}

class Detect : public QWidget
{
    Q_OBJECT

public:
    explicit Detect(QWidget *parent = 0);
    void detectingface();
    ~Detect();

private:
    Ui::Detect *ui;
    int numb;
};

#endif // DETECT_H
