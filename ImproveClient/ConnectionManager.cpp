#include "ConnectionManager.h"

#include <QAbstractSocket>
#include <QDebug>
#include <QTcpSocket>

// my first commit

ConnectionManager::ConnectionManager()
    : pMainWidget(nullptr)
    , pLayMain(nullptr)
    , pLayConnection(nullptr)
    , pLayButConnection(nullptr)
    , pLayClearSend(nullptr)
    , pButConnect(nullptr)
    , pButDisconnect(nullptr)
    , pButSend(nullptr)
    , pButClearAll(nullptr)
    , pTextLog(nullptr)
    , pTextSendData(nullptr)
    , pEditHost(nullptr)
    , pEditPort(nullptr)
    , pLblLog(nullptr)
    , pLblSend(nullptr)
    , pLblHost(nullptr)
    , pLblPort(nullptr)
    , pSocket(nullptr)
{
    pMainWidget     = new QWidget();
    pLayMain        = new QVBoxLayout();
    pLayConnection  = new QVBoxLayout();
    pLayButConnection  = new QHBoxLayout();
    pLayClearSend   = new QHBoxLayout();

    pButConnect     = new QPushButton("Connect");
    pButDisconnect  = new QPushButton("Disconnect");
    pButSend        = new QPushButton("Send");
    pButClearAll    = new QPushButton("Clear all");

    pTextLog        = new QTextBrowser();
    pTextSendData   = new QTextEdit();
    pEditHost       = new QLineEdit("10.20.8.70");
    pEditPort       = new QLineEdit("33333");

    pLblLog         = new QLabel("Received/Send data");
    pLblSend        = new QLabel("Send");
    pLblHost        = new QLabel("Host:");
    pLblPort        = new QLabel("Port:");

    pLayButConnection->addWidget(pButConnect);
    pLayButConnection->addWidget(pButDisconnect);

    pLayConnection->addWidget(pLblHost);
    pLayConnection->addWidget(pEditHost);
    pLayConnection->addWidget(pLblPort);
    pLayConnection->addWidget(pEditPort);
    pLayConnection->addLayout(pLayButConnection);

    pLayClearSend->addWidget(pButClearAll);
    pLayClearSend->addWidget(pButSend);

    pButDisconnect->setEnabled(false);
    pButSend->setEnabled(false);

    pLayMain->addLayout(pLayConnection);
    pLayMain->addWidget(pLblLog);
    pLayMain->addWidget(pTextLog);
    pLayMain->addWidget(pLblSend);
    pLayMain->addWidget(pTextSendData);
    pLayMain->addLayout(pLayClearSend);

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

    QString sHost = pEditHost->text();
    QString sPort = pEditPort->text();

    if (sHost.isEmpty() || sPort.isEmpty())
    {
        qDebug() << "Invalid connection parameters";
        pTextLog->append("Invalid connection parameters");
        return;
    }

    // this is not blocking call
    pSocket->connectToHost(sHost, sPort.toInt());

    // we need to wait...
    if(!pSocket->waitForConnected(5000))
    {
        qDebug() << "Error: " << pSocket->errorString();
        pTextLog->append(QString("Error: ") + pSocket->errorString());
        return;
    }

    pTextLog->append("Connected to server");

    pEditHost->setEnabled(false);
    pEditPort->setEnabled(false);
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

    pTextLog->append("Disconnected from server");

    pEditHost->setEnabled(true);
    pEditPort->setEnabled(true);
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

