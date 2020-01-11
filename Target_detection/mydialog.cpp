#include "mydialog.h"
#include "ui_mydialog.h"
#include    <QMessageBox>

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    g_DrawingBox=false;
    drawline = false;
    Thecount=0;
    precolor=0;
    all=0;
    g_box=Rect(-1,-1,0,0);
    p1=Point(0,280);
    p2=Point(400,280);
    man1 = imread("man1.png");
    man2 = imread("man2.png");
    man3 = imread("man3.png");
    if(man1.empty())
        printf("cound not load the man1...\n");
    if(man2.empty())
        printf("cound not load the man2...\n");
    if(man3.empty())
        printf("cound not load the man3...\n");
    cvtColor(man1, man1, COLOR_BGR2GRAY);
    cvtColor(man2, man2, COLOR_BGR2GRAY);
    cvtColor(man3, man3, COLOR_BGR2GRAY);
    kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    pMOG2 = createBackgroundSubtractorMOG2();

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MyDialog::readFrame);
    connect(ui->open,&QPushButton::clicked,this,&MyDialog::openVideo);
    connect(ui->close,&QPushButton::clicked,this,&MyDialog::closeVideo);
}
void MyDialog::openVideo()
{
    capture=NULL;
    //QString path=QFileDialog::getOpenFileName(this,"open""../");

    QString path = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files(*.avi *.mp4)"));

    if(path.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    } else {
        string Path=path.toStdString();
         capture.open(Path);
         if(!capture.isOpened())
         {
             cout<<"Cound not open the Video..."<<endl;
         }
         timer->start(30);
         framescount=(int)capture.get(CAP_PROP_FRAME_COUNT);
    }



}

void MyDialog::readFrame()
{
    capture>>frame;
    cv::resize(frame, frame, Size(round(frame.cols*0.6), round(frame.rows*0.6)));
    pMOG2->apply(frame, bsmaskMOG2);
    QString p1xstr=ui->p1x->text();
    QString p2xstr=ui->p2x->text();
    QString p1ystr=ui->p1y->text();
    QString p2ystr=ui->p2y->text();
    int p1xx=p1xstr.toInt();
    int p1yy=p1ystr.toInt();
    int p2yy=p2ystr.toInt();
    int p2xx=p2xstr.toInt();
    p1.x=p1xx;
    p1.y=p1yy;
    p2.x=p2xx;
    p2.y=p2yy;
    DrawLine(frame, p1,p2);
    morphologyEx(bsmaskMOG2, bsmaskMOG2, MORPH_OPEN, kernel, Point(-1, -1));
    threshold(bsmaskMOG2, threshimg, 200, 255, THRESH_BINARY);

    findContours(threshimg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contours.size(); i++)
    {
        double length,alllength;
        length = arcLength(contours[i],1);
        alllength = frame.cols + frame.rows;
        if (length > alllength) {
            double match1, match2, match3;
            match1 = matchShapes(threshimg, man1, CONTOURS_MATCH_I1, 0);
            match2 = matchShapes(threshimg, man2, CONTOURS_MATCH_I1, 0);
            match3 = matchShapes(threshimg, man3, CONTOURS_MATCH_I1, 0);
            if (match1 < 0.1 || match2 < 0.1 || match3 < 0.1)
            {
                RotatedRect box;
                box = minAreaRect(contours[i]);
                Point2f vertex[4];
                Point center;
                box.points(vertex);
                center.x = round((vertex[0].x + vertex[2].x + vertex[3].x + vertex[1].x) / 4);
                center.y = round((vertex[1].y + vertex[2].y + vertex[3].y + vertex[0].y) / 4);
                for (int p = 0; p < 4; p++)
                {
                    line(frame, vertex[p], vertex[(p + 1) % 4], Scalar(0, 0, 255), 2, 8, 0);
                }
                circle(frame, center, 6, Scalar(0, 255, 0), 6, 8, 0);
            }
        }
    }
    //imshow("MOG2", threshimg);
    LineIterator it(frame, p1, p2, 8);
    all = 0;
    for (int j = 0; j < it.count; ++j, ++it)
    {
        if (precolor == 0 && (int)(*it)[1] == 255)
        {
            Thecount++;
            //precolor = 0;
        }
        all = all + (int)(*it)[1];
        if ((int)(*it)[1] == 255)
        {
            precolor = 255;
            break;
        }
    }
    if (all == 0)
    {
        precolor = 0;
    }
    stringstream ss;
    string str;
    string str1="The Count: ";
    ss << Thecount;
    ss >> str;
    str = str1 + str;
    putText(frame, str, Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
    QImage img=Mat2QImage(frame);
    ui->window->setPixmap(QPixmap::fromImage(img));

    current_pos=(int)capture.get(CAP_PROP_POS_FRAMES);
        if(current_pos==framescount)
        {
            capture.set(CAP_PROP_POS_FRAMES,1);
        }
}

void MyDialog::closeVideo()
{
    timer->stop();
    capture.release();
    this->close();
}
void MyDialog::DrawLine(Mat &img, Point p1,Point p2)
{
    line(img, p1, p2, Scalar(0, 0, 255), 3, 8);
    //rectangle(img, box.tl(), box.br(), Scalar(0, 0, 255));
}

QImage MyDialog::Mat2QImage(Mat cvImg)
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
MyDialog::~MyDialog()
{
    delete ui;
}
