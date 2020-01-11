#include "cartest.h"
#include "ui_cartest.h"
#include <QIcon>
#include <QMessageBox>

CarTest::CarTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarTest)
{
    ui->setupUi(this);
    setWindowTitle(tr("视频识别"));

    confidenceTreshold=0.3;
    modelCofiguration="yolov2-tiny.cfg";
    modelBinary="yolov2-tiny.weights";
    net=readNetFromDarknet(modelCofiguration,modelBinary);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);
    if (net.empty())
    {
        printf("Could not load net...\n");
    }
    ifstream classNamesFile("coco.names");
    if (classNamesFile.is_open())
    {
        string className = "";
        while (std::getline(classNamesFile, className))
            classNamesVec.push_back(className);
    }
    timer = new QTimer(this);
    ui->progressBar->setValue(0);
    connect(timer,&QTimer::timeout,this,&CarTest::readFrame);
    connect(ui->opennew,&QPushButton::clicked,this,&CarTest::dealVideo);
    connect(ui->opentreated,&QPushButton::clicked,this,&CarTest::openVideo);
    connect(ui->close,&QPushButton::clicked,this,&CarTest::closeVideo);
}
QImage CarTest::Mat2QImage(Mat cvImg)
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



void CarTest::dealVideo()
{
    //QString path=QFileDialog::getOpenFileName(this,"open""../");
    QString path = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files(*.avi *.mp4)"));

    if(path.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    } else {
        string Path=path.toStdString();
         VideoCapture capture(Path);
         double fps=capture.get(CAP_PROP_FPS);
         Size size((int)capture.get(CAP_PROP_FRAME_WIDTH),
                 (int)capture.get(CAP_PROP_FRAME_HEIGHT));
         VideoWriter writer;
         writer.open("man.avi",CV_FOURCC('M','J','P','G'),fps,size);
         int allframes=(int)capture.get(CAP_PROP_FRAME_COUNT);
         //int tmpw=(int)capture.get(CAP_PROP_FRAME_WIDTH);
         //int tmph=(int)capture.get(CAP_PROP_FRAME_HEIGHT);
         int current_pos=0;
         ui->progressBar->setMinimum(0);//最小值
         ui->progressBar->setMaximum(allframes);//最大值
         ui->progressBar->setValue(current_pos); //当前值
         Mat frame;
         while (capture.read(frame))
         {
            // int Weight = frame.cols;
            // int Height = frame.rows;
             //resize(frame, frame, Size(Weight*0.2, Height*0.2));
             if(frame.empty()) break;
             Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
             net.setInput(inputBlob, "data");
             // 检测
             Mat detectionMat = net.forward("detection_out");
             vector<double> layersTimings;
             double freq = getTickFrequency() / 1000;
             double time = net.getPerfProfile(layersTimings) / freq;
             ostringstream ss;
             ss << "detection time: " << time << " ms";
             putText(frame, ss.str(), Point(20, 20), 0, 0.5, Scalar(0, 0, 255));

             // 输出结果
             for (int i = 0; i < detectionMat.rows; i++)
             {
                 const int probability_index = 5;
                 const int probability_size = detectionMat.cols - probability_index;
                 float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
                 size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
                 float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
                 if (confidence > confidenceTreshold)
                 {
                     float x = detectionMat.at<float>(i, 0);
                     float y = detectionMat.at<float>(i, 1);
                     float width = detectionMat.at<float>(i, 2);
                     float height = detectionMat.at<float>(i, 3);
                     int xLeftBottom = static_cast<int>((x - width / 2) * frame.cols);
                     int yLeftBottom = static_cast<int>((y - height / 2) * frame.rows);
                     int xRightTop = static_cast<int>((x + width / 2) * frame.cols);
                     int yRightTop = static_cast<int>((y + height / 2) * frame.rows);
                     Rect object(xLeftBottom, yLeftBottom,
                         xRightTop - xLeftBottom,
                         yRightTop - yLeftBottom);
                     rectangle(frame, object, Scalar(0, 0, 255), 2, 8);
                     if (objectClass < classNamesVec.size())
                     {
                         ss.str("");
                         ss << confidence;
                         String conf(ss.str());
                         String label = String(classNamesVec[objectClass]) + ": " + conf;
                         int baseLine = 0;
                         Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                         rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom),
                             Size(labelSize.width, labelSize.height + baseLine)),
                             Scalar(255, 255, 255), CV_FILLED);
                         putText(frame, label, Point(xLeftBottom, yLeftBottom + labelSize.height),
                             FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
                     }
                 }
             }
             current_pos=(int)capture.get(CAP_PROP_POS_FRAMES);
             ui->progressBar->setValue((current_pos));
             writer<<frame;
             waitKey(1);
         }
         capture.release();
    }



}

void CarTest::openVideo()
{
    cap=NULL;
    cap.open("man.avi");
    if(!cap.isOpened())
    {
        cout<<"Cound not open the Video..."<<endl;
    }
    timer->start(40);
    frames=(int)cap.get(CAP_PROP_FRAME_COUNT);
}

void CarTest::readFrame()
{
    cap>>frame;
    QImage img= Mat2QImage(frame);
    ui->window->setPixmap(QPixmap::fromImage(img));
    current_pos=(int)cap.get(CAP_PROP_POS_FRAMES);
    if(current_pos==frames)
    {
        cap.set(CAP_PROP_POS_FRAMES,1);
    }
}
void CarTest::closeVideo()
{
    timer->stop();
    cap.release();
    this->close();
}

CarTest::~CarTest()
{
    delete ui;
}
