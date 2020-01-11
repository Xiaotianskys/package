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
    void openwincolface();
    void openwingecsv();
    void openwintrain();
    void openwindetect();
    void openwindealfile();
    void openwinactualopreate();
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
