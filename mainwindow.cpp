#include "mainwindow.h"
#include "ui_mainwindow.h"



int const MainWindow::EXIT_CODE_REBOOT = -123456789;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_1->setText("Connecting to camera...");
    ui->label_2->setText("Connecting to camera...");
    ui->label_3->setText("Connecting to camera...");
    ui->label_4->setText("Connecting to camera...");
    setWindowTitle(tr("Camera"));
    connect( ui->actionRestart, SIGNAL (triggered()),this, SLOT (slotReboot()));

    worker = new QThread();
    connect(worker, &QThread::started, this, &MainWindow::setAllCapturethread, Qt::QueuedConnection);
    worker->start();
}

MainWindow::~MainWindow()
{ 
    worker->quit();
    worker->wait();
    delete worker;
    delete ui;

}
//Slots::
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

void MainWindow::setAllCapturethread()
{
    for(int i =0; i<camNum; ++i)
    {
        captureThread[i]= new StreamCapture("rtp://192.168.1.1:5"+std::to_string(1+i)+"000", 1+i);
        connect(captureThread[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame, Qt::QueuedConnection);
        connect(captureThread[i], &StreamCapture::warningMassage, this, &MainWindow::warningMassage, Qt::QueuedConnection);
        connect(captureThread[i], &StreamCapture::finished, captureThread[i], &StreamCapture::deleteLater, Qt::QueuedConnection);
    }
    for(int i =0; i<camNum; ++i)
    {
        captureThread[i]->start();
    }

}

void MainWindow::warningMassage(QString msg, const int camNum)
{
    switch(camNum)
    {
    case 1:
        ui->label_1->setText(msg);
        break;
    case 2:
        ui->label_2->setText(msg);
        break;
    case 3:
        ui->label_3->setText(msg);
        break;
    case 4:
        ui->label_4->setText(msg);
        break;
    default:
        qDebug()<< "unkonwn camera number!";
    }

}
void MainWindow::slotReboot()
{
    qDebug() << "Performing application reboot...";

    for(int i =0; i<camNum; ++i)
    {
        disconnect(captureThread[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame);
        captureThread[i]->abortSig(true);
        captureThread[i]->quit();
        captureThread[i]->wait();

    }

    qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}

