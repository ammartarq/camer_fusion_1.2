#ifndef SERIALIZER_H
#define SERIALIZER_H
#include<QByteArray>
#include<QDataStream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/registry.hpp>

class Serializer
{
public:
    Serializer();
    QByteArray serializeData(int camIpNum, cv::Mat frame, qint64 timestamp);
};
QDataStream & operator<<(QDataStream &out, const cv::Mat& mat);
#endif // SERIALIZER_H
