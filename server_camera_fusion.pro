#-------------------------------------------------
#
# Project created by QtCreator 2019-09-24T14:14:59
#
#-------------------------------------------------

QT       += core
QT       -= gui
QT       += network


#Adding targets files for the embedded board
INSTALLS        = target
target.files    = server_camera_fusion
target.path     = /home/pi
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
CONFIG   += console
CONFIG   -= app_bundle


SOURCES += \
        circularbuffer.cpp \
        main.cpp \
        mainwindow.cpp \
        serializer.cpp \
        streamcapture.cpp \
        tcpserver.cpp \
        tcpstreamsender.cpp

HEADERS += \
        circularbuffer.h \
        mainwindow.h \
        serializer.h \
        streamcapture.h \
        tcpserver.h \
        tcpstreamsender.h

FORMS += \
        mainwindow.ui

unix{
INCLUDEPATH += -L /home/ammar/raspi/opencv-arm/include/opencv4
LIBS += -L /home/ammar/raspi/opencv-arm/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio

}



