#include "detect.h"
#include "ui_detect.h"

Detect::Detect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Detect)
{
    ui->setupUi(this);
    numb = 50;
    connect(ui->pushButton,&QPushButton::clicked,this,&Detect::detectingface);
}

void Detect::detectingface()
{
    QString num_str = ui->lineEdit->text();
    numb = num_str.toInt();
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
    string line, classlabel, number;
    vector<string> names;
    char separator = ';';
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, number, separator);
        getline(liness, classlabel);
        if (!classlabel.empty()) {
            names.push_back(classlabel);
        }
    }

    VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "could not open camera..." << endl;
    }
    Mat frame;
    namedWindow("face-recognition", CV_WINDOW_AUTOSIZE);
    vector<Rect> faces;
    Mat dst;
    while (capture.read(frame))
    {
        flip(frame, frame, 1);
        faceDetector.detectMultiScale(frame, faces, 1.1, 8, 0, Size(40, 40), Size(300, 300));
        for (int i = 0; i < faces.size(); i++) {
            int flag = 0;
            Mat roi = frame(faces[i]);
            if(roi.cols<80||roi.rows<80)
            {
                flag = 1;
            }
            cvtColor(roi, dst, COLOR_BGR2GRAY);
            Mat testSample;
            cv::resize(dst, testSample, Size(92,112));
            if(flag == 1)
            {
                Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
                filter2D(testSample, testSample, testSample.depth(), kernel);
                cv::resize(testSample, testSample, Size(92,112));
            }
            int label = model->predict(testSample);
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
            string name;
            name = names[(label<1000)?(label-1):(label-1001+numb)];
            putText(frame, name, faces[i].tl(), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 2, 8);
        }

        imshow("face-recognition", frame);
        char c = waitKey(10);
        if (c == 27) {
            break;
        }
    }
    capture.release();
}

Detect::~Detect()
{
    delete ui;
}
