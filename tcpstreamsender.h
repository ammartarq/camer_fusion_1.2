#ifndef TCPSTREAMSENDER_H
#define TCPSTREAMSENDER_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>

class TCPStreamSender: public QThread
{
    Q_OBJECT
public:
    explicit TCPStreamSender(qintptr socketID, QObject * parnet);
    void run();
private:
    QTcpSocket * socket_;
    qintptr socket_id_;
    QByteArray data_;
public slots:
    void getData(QByteArray data);

signals:
    void error(QTcpSocket::SocketError socketerror);
    void socketClosed();

};

#endif // TCPSTREAMSENDER_H
