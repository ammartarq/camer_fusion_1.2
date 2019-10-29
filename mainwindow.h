#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt framework
#include <QObject>
#include <QMap>
#include <QList>
#include <QtAlgorithms>
//local headers
#include "streamcapture.h"
#include "circularbuffer.h"
#include "tcpserver.h"
// std headers
#include <vector>
#include <string>


constexpr int CAM_NUM = 4;
constexpr int BUFFER_SIZE = 25;
constexpr int INIT_FRAME_WIDTH = 800;
constexpr int INIT_FRAME_HEIGHT = 600;


class MainWindow: public QObject
{
    Q_OBJECT

public:
    explicit MainWindow();
    virtual ~MainWindow();
    void setAllCaptureThread();
    static int const EXIT_CODE_REBOOT;

private slots:
    void slotReboot();
    void receiveFrame(QByteArray);
    void warningMassage(QString, const int);


private:
    StreamCapture *capture_thread_[CAM_NUM];
    TCPserver *server_;
    QList<CircularBuffer<QByteArray>*> buffers_;
signals:
     void dataToClient(QByteArray);

};



#endif // MAINWINDOW_H
