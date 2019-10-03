#include "streamcapture.h"
#include "streamcapture.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QString>
#include <string>
#include <QDebug>
#include "opencv2/videoio/registry.hpp"

StreamCapture::StreamCapture(std::string camIp, const int camNum): QThread (), cam_ip_(camIp),cam_ip_num_(camNum), abort_sig_(false)
{

}
StreamCapture::~StreamCapture()
{
    disconnectCam();
    quit();
    wait();
}
void StreamCapture::run()
{

    connectCam();

    while(isCamConnected() && abort_sig_== false){
        cap_ >> frame_;
        if (frame_.empty())
        {
            break;
        }
        cv::waitKey(1);
        converted_frame_= convertFrame(frame_);
        emit sendFrame(converted_frame_, cam_ip_num_);
    }
    if(abort_sig_)
    {
        disconnectCam();
    }

    
}

void StreamCapture::abortSig(bool abort)
{
    abort_sig_=abort;
}

void StreamCapture::connectCam()
{
    if(!cap_.open(cam_ip_))
    {
        abortSig(true);
        emit warningMassage("Connection failed", cam_ip_num_);
    }

}
bool StreamCapture::disconnectCam()
{
    if(cap_.isOpened())
    {
        cap_.release();
        return true;
    }
    return false;
}
bool StreamCapture::isCamConnected()
{
    return cap_.isOpened();
}
QImage StreamCapture::convertFrame(const cv::Mat &mat)
{
    if(mat.type()==CV_8UC3)
    {
        const uchar *qImageBuffer = const_cast<uchar*>(mat.data);
        QImage img(qImageBuffer, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage."<<mat.type();

    }
}

int StreamCapture::getFrameWidth()
{
    return static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_WIDTH));
}

int StreamCapture::getFrameHeight()
{
    return static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_HEIGHT));
}
