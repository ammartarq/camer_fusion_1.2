#ifndef STREAMCAPTURE_H
#define STREAMCAPTURE_H

//Qt framework
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QMutex>
#include <QDateTime>
#include <QtGlobal>
//Opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/registry.hpp>
//Local headers
#include"serializer.h"



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
    QMutex mtx;
    std::string cam_ip_;
    Serializer data_in_bytes_;

    int cam_ip_num_;
    int frame_width_;
    int frame_hight_;
    bool abort_sig_;

protected:
    void run()override;
signals:
    void sendFrame(QByteArray array);
    void warningMassage(QString, const int);
    void sendTimestamp(double ts);
    void startTcpStreamWriting();



};

#endif // STREAMCAPTURE_H
