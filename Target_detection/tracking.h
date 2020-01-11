#ifndef TRACKING_H
#define TRACKING_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <math.h>
#include<QTimer>
#include<QImage>
#include<iostream>
#include<string>
#include<QFileDialog>

using namespace cv;
using namespace std;


namespace Ui {
class Tracking;
}

class Tracking : public QWidget
{
    Q_OBJECT

public:
    explicit Tracking(QWidget *parent = 0);
    void dealvideo();
    void openVideo();
    void readFrame();
    void closeVideo();
    ~Tracking();

private:
    Ui::Tracking *ui;
    int smin ;
    int vmin ;
    int vmax ;
    int bins ;
    QImage Mat2QImage(Mat cvImg);
};

#endif // TRACKING_H
