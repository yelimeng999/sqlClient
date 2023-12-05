#include "sqlClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sqlClient w;
    w.show();
    return a.exec();
}
