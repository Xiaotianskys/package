#ifndef CARTEST_H
#define CARTEST_H

#include <QWidget>
#include<QTimer>
#include<QImage>
#include<iostream>
#include<string>
#include<QFileDialog>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace cv::dnn;

namespace Ui {
class CarTest;
}

class CarTest : public QWidget
{
    Q_OBJECT

public:
    explicit CarTest(QWidget *parent = 0);
    void openVideo();
    void dealVideo();
    void readFrame();
    void closeVideo();
    ~CarTest();

private:
    Ui::CarTest *ui;
    QImage Mat2QImage(Mat cvImg);
    double confidenceTreshold;
    string modelCofiguration;
    string modelBinary;
    dnn::Net net;
    vector<string> classNamesVec;
    VideoCapture cap;
    QTimer *timer;
    Mat frame;
    int frames;
    int current_pos;
};

#endif // CARTEST_H
