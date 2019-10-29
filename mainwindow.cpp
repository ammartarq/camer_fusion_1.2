#include "mainwindow.h"
#include "ui_mainwindow.h"

int const MainWindow::EXIT_CODE_REBOOT = -123456789;
MainWindow::MainWindow()
{
    server_=new TCPserver();
    connect(this,&MainWindow::dataToClient, server_,&TCPserver::dataReady,Qt::QueuedConnection);
    setAllCaptureThread();

}

MainWindow::~MainWindow()
{ 
    
    for(int i =0; i<CAM_NUM; ++i)
    {
        disconnect(capture_thread_[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame);
        capture_thread_[i]->abortSig(true);
        capture_thread_[i]->quit();
        capture_thread_[i]->wait();
        delete capture_thread_[i];
    }
    

    qDeleteAll(buffers_.begin(),buffers_.end());
    buffers_.clear();
}

//Slots::
void MainWindow::receiveFrame(QByteArray data)
{
   emit dataToClient(data);

}
void MainWindow::warningMassage(QString msg, const int camNum)
{

}
void MainWindow::setAllCaptureThread()
{
    for(int i =0; i<CAM_NUM; ++i)
    {
        capture_thread_[i]= new StreamCapture("rtp://192.168.1.1:5"+std::to_string(1+i)+"000", i);
        connect(capture_thread_[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame, Qt::QueuedConnection);
        connect(capture_thread_[i], &StreamCapture::startTcpStreamWriting, server_, &TCPserver::getDatacmd, Qt::QueuedConnection);
        connect(capture_thread_[i], &StreamCapture::warningMassage, this, &MainWindow::warningMassage, Qt::QueuedConnection);
    }
    for(int i =0; i<CAM_NUM; ++i)
    {
        capture_thread_[i]->start();
    }
    
}

void MainWindow::slotReboot()
{
    qDebug() << "Performing application reboot...";
    qDeleteAll(buffers_.begin(),buffers_.end());
    buffers_.clear();
    
    for(int i =0; i<CAM_NUM; ++i)
    {
        disconnect(capture_thread_[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame);
        if(capture_thread_[i]->isRunning())
        {
            capture_thread_[i]->abortSig(true);
            capture_thread_[i]->wait();
            capture_thread_[i]->quit();
        }
        
    }
    
    qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}


