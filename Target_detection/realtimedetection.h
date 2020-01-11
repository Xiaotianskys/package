#ifndef REALTIMEDETECTION_H
#define REALTIMEDETECTION_H

#include <QWidget>
#include<QTimer>
#include<QImage>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<QFileDialog>

using namespace cv;
using namespace std;
using namespace cv::dnn;

namespace Ui {
class RealTimeDetection;
}

class RealTimeDetection : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeDetection(QWidget *parent = 0);
    void openVideo();
    void readFrame();
    void closeVideo();
    ~RealTimeDetection();

private:
    Ui::RealTimeDetection *ui;
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

#endif // REALTIMEDETECTION_H
