#ifndef WINDOW_H
#define WINDOW_H

//#include "Message.h"
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include "Message.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

signals:
    void messageSent(const Message &message);

public slots:
    void setMessage(const Message &message);

private slots:
    void sendMessage();

private:
    Ui::Window *ui;
    Message thisMessage;
    QTextEdit *editor;
};

#endif // WINDOW_H
