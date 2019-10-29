#include "tcpstreamsender.h"

TCPStreamSender::TCPStreamSender(qintptr socketID, QObject *parent):
QThread(parent), socket_id_(socketID)
{

}
void TCPStreamSender::run()
{
    socket_ = new QTcpSocket(this);
    if (!socket_->setSocketDescriptor(socket_id_))
    {
        emit error(socket_->error());
        return;
    }
    if (socket_->state() == QTcpSocket::ConnectedState)
    {
        socket_->write(data_);
    }
    else
    {
        emit socketClosed();
        socket_->deleteLater();
        exit(0);
    }
}
void TCPStreamSender::getData(QByteArray data)
{
    data_=data;
}
