#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <iostream>
#include<QTimer>
#include<QImage>
#include<QFileDialog>

using namespace cv;
using namespace std;


namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    void openVideo();
    void readFrame();
    void closeVideo();
    ~MyDialog();

private:
    Ui::MyDialog *ui;
    QImage Mat2QImage(Mat cvImg);
    void DrawLine(Mat &img,Point p1,Point p2);
    cv::Rect g_box;
    bool g_DrawingBox;
    cv::Point p1,p2;
    int Thecount;
    int precolor;
    QTimer *timer;
    int all;
    Mat frame;
    Mat man1, man2, man3;
    Mat bsmaskMOG2;
    Mat threshimg;
    VideoCapture capture;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat kernel;
    Ptr<BackgroundSubtractor> pMOG2;
    bool drawline;
    int framescount;
    int current_pos;
};

#endif // MYDIALOG_H
