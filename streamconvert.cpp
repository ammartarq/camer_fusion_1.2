#include "streamconvert.h"

StreamConvert::StreamConvert()
{

}

StreamConvert::~StreamConvert()
{
  
}

QImage StreamConvert::convertFrame(const cv::Mat &mat)
{
    if(mat.type()==CV_8UC3)
    {
        q_image_buffer = const_cast<uchar*>(mat.data);
        QImage img(q_image_buffer, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
    }
    return QImage();
}
