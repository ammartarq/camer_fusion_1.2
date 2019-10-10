#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt framework
#include <QMainWindow>
#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QMap>
#include <QList>
#include <QtAlgorithms>
//Internal header
#include "streamcapture.h"
#include "circularbuffer.h"

// std headers
#include <vector>
#include <string>

constexpr int CAM_NUM = 4;
constexpr int BUFFER_SIZE = 25;
constexpr int INIT_FRAME_WIDTH = 800;
constexpr int INIT_FRAME_HEIGHT = 600;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    static int const EXIT_CODE_REBOOT;
    void labelGenerator(int camNum);

private slots:
    void slotReboot();
    void receiveFrame(QImage frame, const int camNum);
    void warningMassage(QString, const int);
    void setAllCaptureThread();

private:
    Ui::MainWindow *ui_;
    StreamCapture *capture_thread_[CAM_NUM];
    QThread *worker_;
    QList<QLabel*> all_label_;
    CircularBuffer<QImage> buffer_;
    QMap<QImage, int> set;


};
#include"circularbuffer.cpp"

#endif // MAINWINDOW_H
