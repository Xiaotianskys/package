#-------------------------------------------------
#
# Project created by QtCreator 2019-04-14T08:29:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    collect_face.cpp \
    ge__csv.cpp \
    trainingmodel.cpp \
    detect.cpp \
    deal_file.cpp \
    actualoperation.cpp

HEADERS += \
        widget.h \
    collect_face.h \
    ge__csv.h \
    trainingmodel.h \
    detect.h \
    deal_file.h \
    actualoperation.h

FORMS += \
        widget.ui \
    collect_face.ui \
    ge__csv.ui \
    trainingmodel.ui \
    detect.ui \
    deal_file.ui \
    actualoperation.ui

CONFIG +=C++11

INCLUDEPATH+= .\newbuild\include
 .\newbuild\include\opencv
 .\newbuild\include\opencv2

#不加d表示是release模式

LIBS += .\newbuild\x64\vc15\lib\opencv_aruco341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_bgsegm341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_bioinspired341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_calib3d341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_ccalib341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_core341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_datasets341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_dnn341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_dnn_objdetect341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_dpm341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_face341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_features2d341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_flann341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_fuzzy341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_hfs341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_highgui341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_imgcodecs341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_imgproc341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_img_hash341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_line_descriptor341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_ml341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_objdetect341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_optflow341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_phase_unwrapping341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_photo341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_plot341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_reg341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_rgbd341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_saliency341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_shape341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_stereo341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_structured_light341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_superres341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_surface_matching341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_text341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_tracking341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_video341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_videoio341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_videostab341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_ximgproc341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_xobjdetect341.lib
LIBS += .\newbuild\x64\vc15\lib\opencv_xphoto341.lib

RESOURCES += \
    logo.qrc
RC_ICONS = logo.ico
