#include "ConnectionManager.h"

#include <algorithm>

ConnectionManager::ConnectionManager(quint16 port)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newUser()));

    if (!tcpServer->listen(QHostAddress::Any, port))
    {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    }
    else
    {
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        qDebug() << QString::fromUtf8("Server has been started!");
    }
}

ConnectionManager::~ConnectionManager()
{
    qDebug() << "Destr";

    foreach(int i,SClients.keys())
    {
        QTextStream os(SClients[i]);
        os.setAutoDetectUnicode(true);
        os << QDateTime::currentDateTime().toString() << "\n";
        SClients[i]->close();
        SClients.remove(i);
    }
    tcpServer->close();
    qDebug() << QString::fromUtf8("Server has been stopped!");
}


void ConnectionManager::newUser()
{
    QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
    qDebug() << "New connection! " << clientSocket;

    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(clientSocket, SIGNAL(readyRead()),this, SLOT(slotReadClient()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void ConnectionManager::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QString sReceivedData = clientSocket->readAll();

    qDebug() << "Received data from client " << clientSocket;
    qDebug() << sReceivedData;

    std::reverse(sReceivedData.begin(), sReceivedData.end());

    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    os << sReceivedData;
}

void ConnectionManager::clientDisconnected()
{
    qDebug() << "Disconnected";

    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    clientSocket->close();

    int idusersocs=clientSocket->socketDescriptor();
    SClients.remove(idusersocs);
}
