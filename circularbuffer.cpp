#include "circularbuffer.h"
#include <iostream>


template<class T>
CircularBuffer<T>::CircularBuffer(const int size): max_size_(size), pos_(0)
{
    buffer_.reserve(max_size_);
}
template<class T>
void CircularBuffer<T>::addFrame(T &item)
{
    QMutexLocker locker1(&buffer_mutex_);
    if(!isFull())
    {
        buffer_.push_back(item);
    }
    else
    {
        buffer_[pos_] = item;
        pos_ = (pos_ + 1) % max_size_;
    }
}
template<class T>
T CircularBuffer<T>::getFrame()
{
    QMutexLocker locker2(&buffer_mutex_);
    T data;
    if(isEmpty())
    {
        return T();
    }
    else {
        data = buffer_[pos_];
        return data;
    }

}

template<class T>
void CircularBuffer<T>::reset()
{
    buffer_.clear();
}

template<class T>
bool CircularBuffer<T>::isEmpty() const
{
    return buffer_.size() == 0;
}

template<class T>
bool CircularBuffer<T>::isFull() const
{
    return buffer_.size() == max_size_;
}

template<class T>
int  CircularBuffer<T>::getFreeCapacity() const
{
    return  max_size_ - buffer_.size();
}

template<class T>
int  CircularBuffer<T>::getSize() const
{
    return buffer_.size() ;
}
/*template<class T>
void CircularBuffer<T>::getContent() const
{
    for(auto &i:buffer_)
    {
        std::cout<<i<<std::endl;
    }
}*/

template class CircularBuffer<QImage>;
