#include <QApplication>
#include "ConnectionManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConnectionManager mgr;
    mgr.show();


    return a.exec();
}
