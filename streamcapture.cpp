#include "streamcapture.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QString>
#include <string>
#include <QDebug>

StreamCapture::StreamCapture(std::string camIp, const int camNum): QThread (), cam_ip_(camIp), cam_ip_num_(camNum)
{
    cap_ = new cv::VideoCapture(cam_ip_);
}
void StreamCapture::run()
{
    connectCam();
    while(1)
    {   mtx_.lock();
        *cap_ >> frame_;
        if (frame_.empty())
        {
            break;
        }
        converted_frame_= convertFrame(frame_);
        mtx_.unlock();
        emit sendFrame(converted_frame_, cam_ip_num_);
    }
}

bool StreamCapture::connectCam()
{
    bool res = cap_->open(cam_ip_);
    if (!cap_->isOpened())
    {
        qDebug()<< "Error opening video stream";
    }
    if(frame_width_ != -1 && frame_hight_!= -1)
    {
        cap_->set(cv:: CAP_PROP_FRAME_WIDTH , frame_width_);
        cap_->set(cv:: CAP_PROP_FRAME_HEIGHT, frame_width_);
    }
    return  res;
}
bool StreamCapture::disconnectCam()
{

    if(cap_->isOpened())
    {
        cap_->release();
        return true;
    }
    return false;
}
bool StreamCapture::isCamConnected()
{
    return cap_->isOpened();
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
        return QImage();
    }
}

int StreamCapture::getFrameWidth()
{
    return static_cast<int>(cap_->get(cv::CAP_PROP_FRAME_WIDTH));
}

int StreamCapture::getFrameHeight()
{
    return static_cast<int>(cap_->get(cv::CAP_PROP_FRAME_HEIGHT));
}
