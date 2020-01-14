#include "widget.h"
#include <QApplication>

/*项目为基于 OpenCV 人脸识别的课程签到系统
 *采用人脸识别 LBPH 算法进行人脸识别。
 *采用间隔照片处理（高像素），与图像锐化的创新型技术。
 *整个项目分别有人脸数据采集，人脸识别测试，现实人脸识别签到接口。
 *能够对感兴趣的到课学生进行一次性签到。
 *产品适用于中小型教室的签到。（例如重邮四教的所有教室）
 * 注：实地取景签到至少15张图片以上
 */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
