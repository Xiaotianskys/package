#ifndef TRAININGMODEL_H
#define TRAININGMODEL_H

#include <QWidget>
#include <QPushButton>
#include <iostream>
#include <string>
#include <QString>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <QFileDialog>
#include <QMessageBox>

using namespace cv;
using namespace cv::face;
using namespace std;

namespace Ui {
class TrainingModel;
}

class TrainingModel : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingModel(QWidget *parent = 0);
    void face_traning();
    ~TrainingModel();

private:
    Ui::TrainingModel *ui;
};

#endif // TRAININGMODEL_H
