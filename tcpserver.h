#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <tcpstreamsender.h>
#include <QThread>
class TCPserver: public QTcpServer
{
    Q_OBJECT
public:
    TCPserver();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    TCPStreamSender * tcp_stream_sender;
signals:
    void getData(QByteArray data);
    void sendDataCmd(QThread::Priority priority);
    void clientDisconnected();
public slots:
    void dataReady(QByteArray data);
    void getDatacmd();
    void socketClosed();

};

#endif // TCPSERVER_H
