#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H


#include<QMutexLocker>
#include<QVector>
#include<QHash>
#include<QtGlobal>
#include<QDebug>

template <class T> class CircularBuffer

{

public:

    CircularBuffer(const int size);
    //~CircularBuffer();
    void addFrame(qint64 &ts, T &item);
    T getFrame(qint64 ts);
    void reset();
    bool isFull() const;

private:

    QVector<T> buffer_;
    QVector<qint64> timestamp_;
    QHash<qint64, T>map_frame_timestamp_;
    QMutex buffer_mutex_;

    int max_size_;
    int pos_;



};
#include"circularbuffer.cpp"
#endif // CIRCULARBUFFER_H
