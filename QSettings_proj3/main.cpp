#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    a.setOrganizationName("MyOrg");
//    a.setOrganizationDomain("MyDomain");
//    a.setApplicationName("MyAppName");

    MainWindow w;
    w.show();

    return a.exec();
}
