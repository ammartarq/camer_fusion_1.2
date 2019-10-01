#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Camera"));
    for(int i =0; i<camNum; ++i)
    {
        captureThread[i]= new StreamCapture("rtp://192.168.1.1:5"+std::to_string(1+i)+"000", 1+i);
        if(captureThread[i]->isCamConnected()){
            connect(captureThread[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame, Qt::QueuedConnection);
            captureThread[i]->start();
        }
    }


}

MainWindow::~MainWindow()
{ 
    delete ui;
}
void MainWindow::receiveFrame(QImage frame, const int camNum)
{

    switch(camNum)
    {
    case 1:
        ui->label_1->setPixmap(QPixmap::fromImage(frame));
        break;
    case 2:
        ui->label_2->setPixmap(QPixmap::fromImage(frame));
        break;
    case 3:
        ui->label_3->setPixmap(QPixmap::fromImage(frame));
        break;
    case 4:
        ui->label_4->setPixmap(QPixmap::fromImage(frame));
        break;
    default:
        qDebug()<< "unkonwn camera number!";

    }
}


