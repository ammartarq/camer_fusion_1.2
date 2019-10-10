#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <cstddef>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include<QMutexLocker>
#include<QSemaphore>
#include<QVector>
#include<QVectorIterator>
#include<QImage>



template <class T> class CircularBuffer
{
public:

    CircularBuffer(const int size);
    void addFrame(T &item);
    T getFrame();
    void reset();
    bool isEmpty() const;
    bool isFull() const;
    int  getFreeCapacity() const;
    int  getSize() const;
    //test void getContent() const;
private:


    QVector<T> buffer_;
    int  max_size_;
    QMutex buffer_mutex_;
    int pos_;

};


#endif // CIRCULARBUFFER_H
