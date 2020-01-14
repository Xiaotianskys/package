#include "collect_face.h"
#include "ui_collect_face.h"

Collect_Face::Collect_Face(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Collect_Face)
{
    ui->setupUi(this);
    haar_face_datapath = "haarcascade_frontalface_alt.xml";
    connect(ui->collect,&QPushButton::clicked,this,&Collect_Face::dealvideo);
}

Collect_Face::~Collect_Face()
{
    delete ui;
}


//通过本地摄像头收集人脸
void Collect_Face::dealvideo()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Video"), "collectface");
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    }
    else
    {
        string Path=path.toStdString();
        //打开摄像头
        VideoCapture capture(0);
        if (!capture.isOpened()) {
            cout << "could not open camera..." << endl;
        }
        Size S = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
        //int fps = capture.get(CV_CAP_PROP_FPS);

        CascadeClassifier faceDetector;
        faceDetector.load(haar_face_datapath);

        Mat frame;
        namedWindow("camera-demo", CV_WINDOW_AUTOSIZE);
        vector<Rect> faces;
        int count = 0;
        int kcount = 0;
        while (capture.read(frame)) {
            flip(frame, frame, 1);
            //人脸检测
            faceDetector.detectMultiScale(frame, faces, 1.1, 8, 0, Size(80, 100), Size(380, 400));
            //把检测的人脸收集进入文件夹中，以便后续的训练
            for (int i = 0; i < faces.size(); i++) {
                if (count % 5 == 0) {
                    Mat dst;
                    //将人脸图像转化为标准尺寸
                    cv::resize(frame(faces[i]), dst, Size(92, 112));
					//每隔5帧，收集一张图片
                    string pathofimage= Path+"/"+format("face_%d.jpg",count/5);
                    //cout<<pathofimage<<endl;
                    kcount++;
                    imwrite(pathofimage, dst);
                }
                rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);
            }
            imshow("camera-demo", frame);
            char c = waitKey(10);
            if (c == 27) {
                break;
            }
            count++;
        }
        string result;
        result = "You have collected " + to_string(kcount) + " face picture";
        QString Result = QString::fromStdString(result);
        ui->textBrowser->clear();
        ui->textBrowser->setText(Result);
        capture.release();
    }
}


//通过本地文件收集人脸
void Collect_Face::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Video"), "collectface");
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    }
    else
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), "./FaceVideo", tr("Video Files(*.avi *.mp4)"));
        if(filename == 0){
            QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
        }
        else
        {
            string Path=path.toStdString();
            string Filename = filename.toStdString();
			//读取文件
            VideoCapture capture(Filename);
            if (!capture.isOpened()) {
                cout << "could not open camera..." << endl;
            }
            Size S = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
            //int fps = capture.get(CV_CAP_PROP_FPS);
			
			//加载人脸检测文件
            CascadeClassifier faceDetector;
            faceDetector.load(haar_face_datapath);

            Mat frame;
            namedWindow("camera-demo", CV_WINDOW_AUTOSIZE);
            vector<Rect> faces;
            int count = 0;
            int kcount = 0;
            while (capture.read(frame)) {
                flip(frame, frame, 1);
                faceDetector.detectMultiScale(frame, faces, 1.1, 8, 0, Size(60, 80), Size(380, 400));
                for (int i = 0; i < faces.size(); i++) {
                    if (count % 5 == 0) {
                        Mat dst;
						//将人脸图像转化为标准尺寸
                        cv::resize(frame(faces[i]), dst, Size(92, 112));
						//每隔5帧，收集一张图片
                        string pathofimage= Path+"/"+format("Face_%d.jpg",count/5);
                        kcount++;
                        //cout<<pathofimage<<endl;
                        imwrite(pathofimage, dst);
                    }
                    rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);
                }
                imshow("camera-demo", frame);
                char c = waitKey(10);
                if (c == 27) {
                    break;
                }
                count++;
            }
            string result;
            result = "You have collected " + to_string(kcount) + " face picture";
            QString Result = QString::fromStdString(result);
            ui->textBrowser->clear();
            ui->textBrowser->setText(Result);
            capture.release();
        }
    }
}
