#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt framework
#include <QMainWindow>
#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QMap>
#include <QHash>
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
    void receiveFrame(const int camNum, QImage frame, qint64 ts);
    void warningMassage(QString, const int);
    void setAllCaptureThread();

private:
    Ui::MainWindow *ui_;
    StreamCapture *capture_thread_[CAM_NUM];
    QThread *worker_;
    QList<QLabel*> all_label_;

    QList<CircularBuffer<QImage>*> buffers_;
    QHash<int, CircularBuffer<QImage>> map_;


};
#include"circularbuffer.cpp"


#endif // MAINWINDOW_H
