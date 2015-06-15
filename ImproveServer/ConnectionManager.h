#pragma once

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>

class QTcpServer;

class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionManager(quint16 port = 33333);
    ~ConnectionManager();

private slots:
    void newUser();
    void slotReadClient();
    void clientDisconnected();
private:
    QTcpServer *tcpServer;
    QMap<int,QTcpSocket *> SClients;
};
