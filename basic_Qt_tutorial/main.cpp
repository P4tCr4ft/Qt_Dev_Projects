#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FooWidget w;
    w.show();

    w.nameSetter();

    return a.exec();

// code must be inside loop so above a.exec()
//    w.nameSetter();
}
