#include "mainwindow.h"
#include "ui_mainwindow.h"



int const MainWindow::EXIT_CODE_REBOOT = -123456789;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui_(new Ui::MainWindow), buffer_(BUFFER_SIZE)
{

    ui_->setupUi(this);
    setWindowTitle(tr("Camera"));
    connect( ui_->actionRestart, SIGNAL (triggered()),this, SLOT (slotReboot()));
    worker_ = new QThread();
    connect(worker_, &QThread::started, this, [this]{labelGenerator(CAM_NUM);});
    connect(worker_, &QThread::started, this, &MainWindow::setAllCaptureThread, Qt::QueuedConnection);
    worker_->start();
    
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
    
    qDeleteAll(all_label_.begin(),all_label_.end());
    all_label_.clear();
    worker_->quit();
    worker_->wait();
    delete worker_;
    delete ui_;
    
}
void MainWindow::labelGenerator(int CAM_NUM)
{
    for (int i = 0; i < CAM_NUM; ++i){
        all_label_ << new QLabel(this);
    }
    
    
    for (int i = 0; i < CAM_NUM; ++i)
    {
        all_label_.at(i)->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        all_label_.at(i)->setFrameStyle(QFrame::Panel | QFrame::Raised);
        all_label_.at(i)->setText(QString("Connecting to camera %1").arg(i+1));
        all_label_.at(i)->setMinimumSize(INIT_FRAME_WIDTH,INIT_FRAME_HEIGHT);
        ui_->horizontalLayout_2->addWidget((all_label_.at(i)));
    }
}

//Slots::
void MainWindow::receiveFrame(QImage frame, const int camNum)
{
    //qDebug()<<frame.sizeInBytes();
     buffer_.addFrame(frame);
     set.insert(frame, camNum);
    (all_label_.at(camNum))->setPixmap(QPixmap::fromImage(buffer_.getFrame()));

    
}
void MainWindow::warningMassage(QString msg, const int camNum)
{
    all_label_.at(camNum)->setText(msg);
}

void MainWindow::setAllCaptureThread()
{
    for(int i =0; i<CAM_NUM; ++i)
    {
        capture_thread_[i]= new StreamCapture("rtp://192.168.1.1:5"+std::to_string(1+i)+"000", i);
        connect(capture_thread_[i], &StreamCapture::sendFrame, this, &MainWindow::receiveFrame, Qt::QueuedConnection);
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
    qDeleteAll(all_label_.begin(),all_label_.end());
    all_label_.clear();
    
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


