#-------------------------------------------------
#
# Project created by QtCreator 2019-09-24T14:14:59
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Camera_fusion_1
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

CONFIG += c++11

SOURCES += \
        circularbuffer.cpp \
        main.cpp \
        mainwindow.cpp \
        streamcapture.cpp \
        streamconvert.cpp

HEADERS += \
        circularbuffer.h \
        mainwindow.h \
        streamcapture.h \
        streamconvert.h

FORMS += \
        mainwindow.ui

unix{
INCLUDEPATH += -L/usr/local/include/opencv2
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio

}
win32{
INCLUDEPATH += D:\programs\openCVQ\opencv\build\include
LIBS += D:\programs\openCVQ_Build\bin\libopencv_core411.dll
LIBS += D:\programs\openCVQ_Build\bin\libopencv_videoio411.dll
LIBS += D:\programs\openCVQ_Build\bin\libopencv_highgui411.dll
LIBS += D:\programs\openCVQ_Build\bin\libopencv_imgcodecs411.dll
LIBS += D:\programs\openCVQ_Build\bin\libopencv_imgproc411.dll
LIBS += D:\programs\openCVQ_Build\bin\libopencv_features2d411.dll
LIBS += D:\programs\openCVQ_Build\bin\libopencv_calib3d411.dll

}


#Adding targets files for the embedded board
# install
#INSTALLS        = target
#target.files    = $$[QT_INSTALL_EXAMPLES]/widgets/layouts/flowlayout
#target.path     = /home/pi



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc


