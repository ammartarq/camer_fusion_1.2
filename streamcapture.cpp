#include "streamcapture.h"


//bugs=> when disconnecting the camera during its operation, the isOpend() function deosnt detect the disconnnection.


StreamCapture::StreamCapture(std::string camIp, const int camNum): QThread (), cam_ip_(camIp),cam_ip_num_(camNum), abort_sig_(false)
{

}
StreamCapture::~StreamCapture()
{

}
void StreamCapture::run()
{

    connectCam();

    while(isCamConnected() &&( abort_sig_== false)){
        QMutexLocker locker(&mtx);
        cap_ >> frame_;
        if (frame_.empty())
        {
            break;
        }
        converted_frame_= convert_.convertFrame(frame_);
        emit sendFrame(converted_frame_, cam_ip_num_);
    }
    if(!isCamConnected())
    {
        emit warningMassage("Check camera connection!", cam_ip_num_);
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
    cap_.open(cam_ip_);

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
void StreamCapture::setFrameWidth(int w)
{
    cap_.set(cv::CAP_PROP_FRAME_WIDTH, w);
}
int StreamCapture::getFrameWidth()const
{
    return static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_WIDTH));
}
void StreamCapture::setFrameheight(int h)
{
    cap_.set(cv::CAP_PROP_FRAME_HEIGHT, h);
}

int StreamCapture::getFrameHeight()const
{
    return static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_HEIGHT));
}
