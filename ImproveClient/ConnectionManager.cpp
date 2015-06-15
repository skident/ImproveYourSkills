#include "ConnectionManager.h"

#include <QAbstractSocket>
#include <QDebug>
#include <QTcpSocket>


ConnectionManager::ConnectionManager()
    : pMainWidget(nullptr)
    , pLayMain(nullptr)
    , pLayConnection(nullptr)
    , pLayClearSend(nullptr)
    , pButConnect(nullptr)
    , pButDisconnect(nullptr)
    , pButSend(nullptr)
    , pButClearAll(nullptr)
    , pTextLog(nullptr)
    , pTextSendData(nullptr)
    , pLblLog(nullptr)
    , pLblSend(nullptr)
    , pSocket(nullptr)
{
    pMainWidget     = new QWidget();
    pLayMain        = new QVBoxLayout();
    pLayConnection  = new QHBoxLayout();
    pLayClearSend   = new QHBoxLayout();

    pButConnect     = new QPushButton("Connect");
    pButDisconnect  = new QPushButton("Disconnect");
    pButSend        = new QPushButton("Send");
    pButClearAll    = new QPushButton("Clear all");

    pTextLog        = new QTextBrowser();
    pTextSendData   = new QTextEdit();
    pLblLog         = new QLabel("Received/Send data");
    pLblSend        = new QLabel("Send");

    pLayConnection->addWidget(pButConnect);
    pLayConnection->addWidget(pButDisconnect);

    pLayClearSend->addWidget(pButClearAll);
    pLayClearSend->addWidget(pButSend);

    pButDisconnect->setEnabled(false);
    pButSend->setEnabled(false);

    pLayMain->addWidget(pLblLog);
    pLayMain->addWidget(pTextLog);
    pLayMain->addWidget(pLblSend);
    pLayMain->addWidget(pTextSendData);
    pLayMain->addLayout(pLayClearSend);
    pLayMain->addLayout(pLayConnection);

    pMainWidget->setLayout(pLayMain);
    setCentralWidget(pMainWidget);

    pSocket = new QTcpSocket(this);

    connect(pButConnect,    SIGNAL(clicked(bool)),  this, SLOT(doConnect()));
    connect(pButDisconnect, SIGNAL(clicked(bool)),  this, SLOT(doDisconnect()));
    connect(pSocket,        SIGNAL(disconnected()), this, SLOT(doDisconnect()));
    connect(pButSend,       SIGNAL(clicked(bool)),  this, SLOT(sendData()));
    connect(pSocket,        SIGNAL(readyRead()),    this, SLOT(receiveData()));
    connect(pButClearAll,   SIGNAL(clicked(bool)),  this, SLOT(clearAll()));
}

void ConnectionManager::doConnect()
{
    qDebug() << "connecting...";

    // this is not blocking call
    pSocket->connectToHost("192.168.1.101", 33333);

    // we need to wait...
    if(!pSocket->waitForConnected(5000))
    {
        qDebug() << "Error: " << pSocket->errorString();
    }

    pButSend->setEnabled(true);
    pButDisconnect->setEnabled(true);
    pButConnect->setEnabled(false);
}

void ConnectionManager::doDisconnect()
{
    qDebug() << "Disconnecting...";
    if (pSocket)
    {
        pSocket->disconnect();
        pSocket->close();
    }

    pButSend->setEnabled(false);
    pButDisconnect->setEnabled(false);
    pButConnect->setEnabled(true);
}

void ConnectionManager::sendData()
{
    QString sSendData = pTextSendData->toPlainText();
    if (!sSendData.isEmpty())
    {
        pSocket->write(sSendData.toStdString().c_str());
        pTextLog->append(QString("Sent: ") + sSendData);
    }
    pTextSendData->clear();
}

void ConnectionManager::receiveData()
{
    qDebug() << "reading...";

    // read the data from the socket
    QByteArray data = pSocket->readAll();
    qDebug() << data;
    pTextLog->append(QString("Received: ") + data);
}


void ConnectionManager::clearAll()
{
    pTextLog->clear();
    pTextSendData->clear();
}

