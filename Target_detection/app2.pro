#-------------------------------------------------
#
# Project created by QtCreator 2018-11-07T20:26:12
#
#-------------------------------------------------

QT       += core gui

RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tool.cpp \
    cartest.cpp \
    realtimedetection.cpp \
    mydialog.cpp \
    tracking.cpp

HEADERS += \
        mainwindow.h \
    tool.h \
    cartest.h \
    realtimedetection.h \
    mydialog.h \
    tracking.h

FORMS += \
        mainwindow.ui \
    tool.ui \
    cartest.ui \
    realtimedetection.ui \
    mydialog.ui \
    tracking.ui

RESOURCES += \
    res.qrc


INCLUDEPATH+= C:\Users\dlgker\Desktop\install\include
 C:\Users\dlgker\Desktop\install\include\opencv
 C:\Users\dlgker\Desktop\install\include\opencv2
#不加d表示是release模式
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_aruco343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_bgsegm343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_bioinspired343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_calib3d343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_ccalib343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_core343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_datasets343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_dnn_objdetect343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_dnn343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_dpm343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_face343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_features2d343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_flann343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_fuzzy343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_hfs343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_highgui343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_img_hash343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_imgcodecs343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_imgproc343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_line_descriptor343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_ml343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_objdetect343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_optflow343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_phase_unwrapping343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_photo343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_plot343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_reg343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_rgbd343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_saliency343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_shape343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_stereo343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_stitching343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_structured_light343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_superres343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_surface_matching343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_text343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_tracking343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_video343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_videoio343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_videostab343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_xfeatures2d343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_ximgproc343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_xobjdetect343.lib
LIBS        += C:\Users\dlgker\Desktop\install\x64\vc15\lib\opencv_xphoto343.lib
