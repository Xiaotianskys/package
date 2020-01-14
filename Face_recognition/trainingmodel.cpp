#include "trainingmodel.h"
#include "ui_trainingmodel.h"

TrainingModel::TrainingModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingModel)
{
    ui->setupUi(this);
    connect(ui->trianing,&QPushButton::clicked,this,&TrainingModel::face_traning);
}

void TrainingModel::face_traning()
{
    QString Filename = QFileDialog::getOpenFileName(this, "打开文件", "./collectface/image.csv", "Csv(*.csv)");
    if(Filename.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("你没有选择文件"));
    }
    else
    {
        //读取.csv文件
        string filename=Filename.toStdString();
        ifstream file(filename.c_str(), ifstream::in);
        if (!file) {
            cout << "could not load file correctly...\n" << endl;
        }
        string line, path, classlabel;
        vector<Mat> images;
        vector<int> labels;
        char separator = ';';
        //把图片和标签存在不同的容器中
        while (getline(file, line)) {
            stringstream liness(line);
            getline(liness, path, separator);
            getline(liness, classlabel);
            if (!path.empty() && !classlabel.empty()) {
                //cout << "path: " << path << endl;
                images.push_back(imread(path, 0));
                labels.push_back(atoi(classlabel.c_str()));
            }
        }
        //read_csv(Path,images,labels);
        if (images.size() < 1 || labels.size() < 1) {
            cout << "invalid image path..." << endl;
        }

        //train it.
        //通过.csv文件进行训练
        Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
        string result = "Training";
        QString Result = QString::fromStdString(result);
        ui->textBrowser->clear();
        ui->textBrowser->setText(Result);
        //cout<<"Training"<<endl;
        model->train(images, labels);
        model->save("FACE_DETECT.xml");
        result = "SUCCFUL";
        Result = QString::fromStdString(result);
        ui->textBrowser->clear();
        ui->textBrowser->setText(Result);
        //cout<<"SUCCFUL"<<endl;
    }
}

TrainingModel::~TrainingModel()
{
    delete ui;
}
