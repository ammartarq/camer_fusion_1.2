#ifndef STREAMCAPTURE_H
#define STREAMCAPTURE_H

//Qt framework
#include <QObject>
#include <QSharedPointer>
#include <QImage>
#include <QDebug>
#include <QThread>
#include <QTime>

//Opencv
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

//STD framework
#include <string>
#include <mutex>

class StreamCapture: public QThread
{
    Q_OBJECT

public:
    StreamCapture(std::string CamIp, int camNum);

    int getFrameWidth();
    int getFrameHeight();
    bool connectCam();
    bool disconnectCam();
    bool isCamConnected();
    QImage convertFrame(const cv::Mat &mat);


private:
    cv::VideoCapture *cap_;
    cv::Mat frame_;
    QImage converted_frame_;
    std::string cam_ip_;
    std::mutex mtx_;

    int cam_ip_num_;
    int frame_width_;
    int frame_hight_;
    int capture_time_;

protected:
    void run();
signals:
    void sendFrame(QImage convertedFrame, int camNum);

};

#endif // STREAMCAPTURE_H
