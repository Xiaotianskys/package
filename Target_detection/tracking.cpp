#include "tracking.h"
#include "ui_tracking.h"
#include    <QFileDialog>
#include    <QMessageBox>

Tracking::Tracking(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tracking)
{
    ui->setupUi(this);
    setWindowTitle(tr("未知物体追踪"));
    smin = 15;
    vmin = 40;
    vmax = 256;
    bins = 16;
    connect(ui->open,&QPushButton::clicked,this,&Tracking::dealvideo);
}

QImage Tracking::Mat2QImage(Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)
    {
        cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg=QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888
                    );
    }
    else if(cvImg.channels()==1)
    {
        qImg=QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8
                    );
    }
    else
    {
        qImg=QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    return qImg;
}

void Tracking::dealvideo()
{
    //QString filter="wmv文件(*.wmv);;mp4文件(*.mp4);;所有文件(*.*)";
    //QString path=QFileDialog::getOpenFileName(this,"open""../");
    QString path = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files(*.avi *.mp4)"));

    if(path.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    } else {

        string Path=path.toStdString();
        VideoCapture capture;
        capture.open(Path);
        if (!capture.isOpened())
        {
            cout << "could not find video data file..." << endl;
            //return -1;
        }
        namedWindow("CAMShift Tracking", CV_WINDOW_AUTOSIZE);
        namedWindow("ROI Histogram", CV_WINDOW_AUTOSIZE);

        bool firstRead = true;
        float hrange[] = { 0,180 };
        const float* hranges = hrange;
        Rect selection;
        Mat frame,hsv,hue,mask,hist,backprojection;
        Mat drawImg = Mat::zeros(300, 300, CV_8UC3);

        while (capture.read(frame)) {
            cv::resize(frame, frame, Size(frame.cols*0.6, frame.rows*0.6));
            if (firstRead) {
                Rect2d first = selectROI("CAMShift Tracking", frame);
                selection.x = first.x;
                selection.y = first.y;
                selection.width = first.width;
                selection.height = first.height;
                printf("ROI.x=%d,ROI.y=%d,ROI.width=%d,ROI.height=%d", selection.x, selection.y, selection.width, selection.height);
            }
            //convert to HSV
            cvtColor(frame, hsv, COLOR_BGR2HSV);
            inRange(hsv, Scalar(0, smin, vmin), Scalar(180, vmax, vmax), mask);
            hue = Mat(hsv.size(), hsv.depth());
            int channels[] = { 0,0 };
            mixChannels(&hsv, 1, &hue, 1, channels, 1);

            if (firstRead) {
                //calculate histogram
                Mat roi(hue, selection);
                Mat maskroi(mask, selection);
                calcHist(&roi, 1, 0, maskroi, hist, 1, &bins, &hranges);

                //show histogram
                int binw = drawImg.cols / bins;
                Mat colorIndex = Mat(1, bins, CV_8UC3);
                for (int i = 0; i < bins; i++)
                {
                    colorIndex.at<Vec3b>(0, i) = Vec3b(saturate_cast<uchar>(i * 180 / bins), 255, 255);
                }
                cvtColor(colorIndex, colorIndex, COLOR_HSV2BGR);
                for (int i = 0; i < bins; i++) {
                    int val = saturate_cast<int>(hist.at<float>(i)*drawImg.rows / 255);
                    rectangle(drawImg, Point(i*binw, drawImg.rows), Point((i + 1)*binw, drawImg.rows - val), Scalar(colorIndex.at<Vec3b>(0, i)), -1, 8, 0);
                }
            }

            //back projection
            calcBackProject(&hue, 1, 0, hist, backprojection, &hranges);

            //CAMShift tracking
            backprojection &= mask;
            RotatedRect trackBox = CamShift(backprojection, selection, TermCriteria((TermCriteria::COUNT | TermCriteria::EPS),10,1));

            //draw location on frame
            ellipse(frame, trackBox, Scalar(0, 0, 255), 3, 8);

            if (firstRead) {
                firstRead = false;
            }
            imshow("CAMShift Tracking", frame);
            imshow("ROI Histogram", drawImg);
            char c = waitKey(33);//ESC
            if (c == 27) {
                break;
            }
        }
        capture.release();


    }



}

Tracking::~Tracking()
{
    delete ui;
}
