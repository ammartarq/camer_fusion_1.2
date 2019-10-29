#include "tcpserver.h"

TCPserver::TCPserver()
{
    QHostAddress host("192.168.1.5");
    quint16 port = 5555;
    if(!this->listen(host, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }

}
void TCPserver::incomingConnection(qintptr socket)
{
    tcp_stream_sender = new TCPStreamSender(socket, this);
    connect(tcp_stream_sender, &TCPStreamSender::socketClosed, this, &TCPserver::socketClosed, Qt::DirectConnection);
    connect(this, &TCPserver::getData, tcp_stream_sender, &TCPStreamSender::getData, Qt::DirectConnection);
    connect(this, &TCPserver::sendDataCmd, tcp_stream_sender, &TCPStreamSender::start, Qt::QueuedConnection);
}
void TCPserver::dataReady(QByteArray data)
{
    emit getData(data);
}
void TCPserver::socketClosed()
{
    emit clientDisconnected();
}
void TCPserver::getDatacmd()
{
    emit sendDataCmd(QThread::InheritPriority);
}
