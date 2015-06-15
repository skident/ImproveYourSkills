#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTcpSocket>

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QTextEdit>

#include <QMainWindow>

class ConnectionManager : public QMainWindow
{
    Q_OBJECT

private:
    QWidget*        pMainWidget;
    QVBoxLayout*    pLayMain;
    QHBoxLayout*    pLayConnection;
    QHBoxLayout*    pLayClearSend;

    QPushButton*    pButConnect;
    QPushButton*    pButDisconnect;
    QPushButton*    pButSend;
    QPushButton*    pButClearAll;
    QTextBrowser*   pTextLog;
    QTextEdit*      pTextSendData;
    QLabel*         pLblLog;
    QLabel*         pLblSend;

    QTcpSocket*     pSocket;

public:
    explicit ConnectionManager();


signals:

public slots:
    void doConnect();
    void doDisconnect();
    void sendData();
    void receiveData();
    void clearAll();

private:


};


#endif // CONNECTIONMANAGER_H
