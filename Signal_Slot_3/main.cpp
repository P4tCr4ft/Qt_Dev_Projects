// C++ is lexical, so needs Message.h
// before Window.h, so can determine
// Message type needed in Window.h

#include "Message.h"
#include "Window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window w1;
    QStringList headers;
    headers << "Subject: Hi Slots"
            << "From: blah@blah";
    QString body = "This is a test\n";
    Message message(body, headers);
    w1.setMessage(message);

    Window w2;
    QObject::connect(&w1, SIGNAL(messageSent(Message)),
                     &w2, SLOT(setMessage(Message)));
    QObject::connect(&w2, SIGNAL(messageSent(Message)),
                     &w1, SLOT(setMessage(Message)));

    w1.show();
    w2.show();

    return a.exec();
}
