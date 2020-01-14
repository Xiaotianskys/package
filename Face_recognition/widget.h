#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "collect_face.h"
#include "ge__csv.h"
#include "trainingmodel.h"
#include "detect.h"
#include "deal_file.h"
#include "actualoperation.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void openwincolface();      //收集人脸数据
    void openwingecsv();        //生成.csv文件便于训练
    void openwintrain();        //训练窗口，开始训练
    void openwindetect();       //检测窗口，开始试识别
    void openwindealfile();     //通过实景图片生成调用路径，生成检测文件，方便进行实景识别
    void openwinactualopreate();        //试识别成功后，打开检测文件进行实景识别
    ~Widget();

private:
    Ui::Widget *ui;
    Collect_Face *CL_F = new Collect_Face;
    Ge__CSV *G_CSV = new Ge__CSV;
    TrainingModel *T_ing = new TrainingModel;
    Detect *DE_F = new Detect;
    Deal_File *DEL_F = new Deal_File;
    ActualOperation *AC_OP = new ActualOperation;
};

#endif // WIDGET_H
