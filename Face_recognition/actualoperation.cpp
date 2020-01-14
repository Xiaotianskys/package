#include "actualoperation.h"
#include "ui_actualoperation.h"

ActualOperation::ActualOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActualOperation)
{
    ui->setupUi(this);
    numb = 50;
    connect(ui->actualdetect,&QPushButton::clicked,this,&ActualOperation::detectactualsite);
}

void ActualOperation::detectactualsite()
{
    QString num_str = ui->lineEdit->text();
    numb = num_str.toInt();
    //"E:/The Program/Picture/image.csv"
    QString path = QFileDialog::getOpenFileName(this, "打开文件", "./Picture", "Csv(*.csv)");
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    }
    else
    {
         //加载训练生成文件
         string Path=path.toStdString();
         string haar_face_datapath = "./haarcascade_frontalface_alt.xml";
         CascadeClassifier faceDetector;
         faceDetector.load(haar_face_datapath);
         Ptr<LBPHFaceRecognizer> model = Algorithm::load<LBPHFaceRecognizer>("FACE_DETECT.xml");
         //model->read("FACE_DETECT.xml");
         string filename = "./collectface/map.txt";
         ifstream file(filename.c_str(), ifstream::in);
         if (!file) {
             cout << "could not load file correctly...\n" << endl;
         }
         //将人名和分数统计起来便于后面的课程人数统计
         string line, classlabel, number;
         vector<string> names;
         //scores用来记录分数
         vector<int> scores;
         char separator = ';';
         while (getline(file, line)) {
             stringstream liness(line);
             getline(liness, number, separator);
             getline(liness, classlabel);
             if (!classlabel.empty()) {
                 names.push_back(classlabel);
                 if(names.size()>numb)
                 {
                     int a=0;
                     scores.push_back(a);
                 }
             }
         }
         file.close();
         ifstream files(Path.c_str(), ifstream::in);
         if (!files) {
             cout << "could not load file correctly...\n" << endl;
         }

         //读取图片
         string paths, lines;
         vector<Mat> images;
         while (getline(files, lines)) {
             stringstream liness(lines);
             getline(liness, paths, separator);
             if (!paths.empty()) {
                 //cout << "path: " << path << endl;
                 images.push_back(imread(paths));
             }
         }
         files.close();
         if (images.size() < 1 ) {
             cout << "invalid image path..." << endl;
         }
         Mat frame;
         namedWindow("face-recognition", CV_WINDOW_AUTOSIZE);
         vector<Rect> faces;
         Mat dst;
         string result;
         for (size_t k = 0; k < images.size(); k++)
         {
             //flip(frame, frame, 1);
             frame = images[k];
             //对40*40到300*300之间的人像进行检测
             faceDetector.detectMultiScale(frame, faces, 1.1, 8, 0, Size(40, 40), Size(300, 300));
             for (int i = 0; i < faces.size(); i++)
             {
                 result = "";
                 int flag = 0;
                 Mat roi = frame(faces[i]);
                 //对小于80*80的图像进行标记
                 if(roi.cols<80||roi.rows<80)
                 {
                     flag = 1;
                 }
                 cvtColor(roi, dst, COLOR_BGR2GRAY);
                 Mat testSample;
                 //resize到标准图像大小
                 cv::resize(dst, testSample, Size(92,112));
                 //对之间标记的图像进行图像锐化处理
                 if(flag == 1)
                 {
                     Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
                     filter2D(testSample, testSample, testSample.depth(), kernel);
                     cv::resize(testSample, testSample, Size(92,112));
                 }
                 //开始检测
                 int label = model->predict(testSample);
                 //图片上标记
                 rectangle(frame, faces[i], Scalar(255, 0, 0), 4, 8, 0);
                 string name;
                 name = names[(label<1000)?(label-1):(label-1001+numb)];
                 putText(frame, name, faces[i].tl(), FONT_HERSHEY_PLAIN, 4.0, Scalar(0, 0, 255), 4, 8);
                 if(((label<1000)?(label):(label-1000+numb))>numb)
                 {
                     scores[((label<1000)?(label-1):(label-1001+numb))-numb]++;
                 }
                 //当被检测图片中有5张该同学的人脸即为签到成功
                 for(size_t i=0;i<scores.size();i++)
                 {
                     if(scores[i]>5)
                     {
                         result.append(format("%s signed in successfully",names[i+numb])).append("\n");
                     }
                     else
                     {
                         result.append(format("%s is signing in",names[i+numb])).append("\n");
                     }
                 }
                 QString Result = QString::fromStdString(result);
                 ui->textBrowser->clear();
                 ui->textBrowser->setText(Result);
             }

             //cout<<result<<endl;
             //QString Result = QString::fromStdString(result);
             //ui->label->clear();
             //ui->label->setText(Result);
             cv::resize(frame,frame,Size((int)frame.cols*0.2,(int)frame.rows*0.2));
             imshow("face-recognition", frame);
             char c = waitKey(10);
             if (c == 27) {
                 break;
             }
         }
    }
}

ActualOperation::~ActualOperation()
{
    delete ui;
}
