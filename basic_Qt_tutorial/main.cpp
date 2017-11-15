#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FooWidget w;
    w.show();


    // If you want nameSetter to take a ref as an
    // arg, then it needs to be passed an object,
    // ie, have to create blah first.
    // But if nameSetter just takes a QString, can
    // pass it a string literal (lower one below)

    QString blah = "Stevo...ref the Unit";
    w.nameSetter(blah);
//    w.nameSetter("Stevo...the Unit");

    return a.exec();

// code must be inside loop so above a.exec()
//    w.nameSetter();
}
