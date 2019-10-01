#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt framework
#include <QMainWindow>
#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QMetaType>
#include <QGroupBox>
#include <QMap>
//Internal header
#include "streamcapture.h"

// std headers
#include <vector>
#include <string>

constexpr int camNum = 4;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void receiveFrame(QImage frame, int camNum);


private:
    Ui::MainWindow *ui;
    StreamCapture *captureThread[camNum];
    QMap<int, QLabel*> m_displayCamera;

};

#endif // MAINWINDOW_H
