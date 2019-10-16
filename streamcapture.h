#ifndef STREAMCAPTURE_H
#define STREAMCAPTURE_H

//Qt framework
#include <QObject>
#include <QImage>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include <QDateTime>
#include <QtGlobal>
//Opencv
//Opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/registry.hpp>
//Local headers
#include"streamconvert.h"




class StreamCapture: public QThread
{
    Q_OBJECT

public:
    StreamCapture(std::string CamIp, int camNum);
    ~StreamCapture()override;

    void connectCam();
    bool disconnectCam();
    bool isCamConnected();
    void abortSig(bool abort);
    int getFrameWidth()const;
    int getFrameHeight()const;
    void setFrameheight(int h);
    void setFrameWidth(int w);
    qint64 getTimestamp()const;
private:
    cv::VideoCapture cap_;
    cv::Mat frame_;
    QImage converted_frame_;
    QMutex mtx;
    StreamConvert convert_;

    std::string cam_ip_;
    int cam_ip_num_;
    int frame_width_;
    int frame_hight_;
    bool abort_sig_;

protected:
    void run()override;
signals:
    void sendFrame(int camNum, QImage  convertedFrame, qint64 ts);
    void warningMassage(QString, const int);
    void sendTimestamp(double ts);



};

#endif // STREAMCAPTURE_H
