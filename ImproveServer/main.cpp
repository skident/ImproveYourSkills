#include <QCoreApplication>
#include "ConnectionManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConnectionManager mgr;

    return a.exec();
}
