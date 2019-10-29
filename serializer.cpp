#include "serializer.h"



Serializer::Serializer()
{

}
QByteArray Serializer::serializeData(int camIpNum, cv::Mat frame, qint64 timestamp)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray,QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_13);


    stream << camIpNum
           << frame
           << timestamp;

    return byteArray;
}

QDataStream &operator<<(QDataStream &out, const cv::Mat &image)
{
    out << image.type();
    out << image.rows;
    out << image.cols;
    const size_t data_size = static_cast<size_t>(image.cols )* static_cast<size_t>(image.rows) * image.elemSize();
    QByteArray data = QByteArray::fromRawData( reinterpret_cast<const char*>(image.ptr()), static_cast<int>(data_size));
    out << data;
    return out;
}
