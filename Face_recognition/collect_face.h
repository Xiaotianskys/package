#ifndef COLLECT_FACE_H
#define COLLECT_FACE_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <string>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

using namespace cv;
using namespace std;

namespace Ui {
class Collect_Face;
}

class Collect_Face : public QWidget
{
    Q_OBJECT

public:
    explicit Collect_Face(QWidget *parent = 0);
    void dealvideo();
    ~Collect_Face();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Collect_Face *ui;
    string haar_face_datapath;
};

#endif // COLLECT_FACE_H
