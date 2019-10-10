#ifndef STREAMCONVERT_H
#define STREAMCONVERT_H
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <QDebug>


class StreamConvert
{
public:

    StreamConvert();
    ~StreamConvert();
    QImage convertFrame(const cv::Mat &mat);

private:

    const uchar *q_image_buffer;

};

#endif // STREAMCONVERT_H
