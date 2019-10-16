#include "circularbuffer.h"

template<class T>
CircularBuffer<T>::CircularBuffer(int size): max_size_(size), pos_(0)
{
    buffer_.reserve(max_size_);
    timestamp_.reserve(max_size_);
    map_frame_timestamp_.reserve(max_size_);
}
template<class T>
void CircularBuffer<T>::addFrame(qint64 & time, T &item)
{
    QMutexLocker locker1(&buffer_mutex_);
    if(!isFull())
    {
        timestamp_.push_back(time);
        buffer_.push_back(item);
        map_frame_timestamp_.insert(time, item);
        if(map_frame_timestamp_.size()==max_size_)
        {
            map_frame_timestamp_.erase(map_frame_timestamp_.begin());
        }
    }
    else
    {
        timestamp_[pos_]=time;
        buffer_[pos_] = item;
        map_frame_timestamp_.insert(timestamp_[pos_], buffer_[pos_]);
        if(map_frame_timestamp_.size()==max_size_)
        {
            map_frame_timestamp_.erase(map_frame_timestamp_.begin());
        }
        pos_ = (pos_ + 1) % max_size_;
    }
}
template<class T>
T CircularBuffer<T>::getFrame(qint64 ts)
{
    QMutexLocker locker2(&buffer_mutex_);
    T data;
    if(timestamp_.isEmpty())
    {
        return T();
    }
    else {
        if(map_frame_timestamp_.contains(ts)){
            data = map_frame_timestamp_[ts];
            return data;
        }
        else {
            qDebug()<<"No frame found related to the given timestamp";
            return T();
        }
    }

}

template<class T>
bool CircularBuffer<T>::isFull() const
{
    return buffer_.size()&&timestamp_.size() == max_size_;
}
template<class T>
void CircularBuffer<T>::reset()
{
    buffer_.clear();
    timestamp_.clear();
}

template class CircularBuffer<QImage>;
