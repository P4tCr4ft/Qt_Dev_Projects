#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <poly2.h>

namespace Ui {
class MainWindow;
}

class FooMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FooMainWindow(QWidget *parent = 0);
    ~FooMainWindow();

//    void setterninTalk(QString x){ninjaTalk = x;}
//    QString getterninTalk(){return ninjaTalk;}

//    void settermonTalk(QString x){monsterTalk = x;}
//    QString gettermonTalk(){return monsterTalk;}

//    void talkShouter(QString x="default");

private slots:
    void on_btnNinja_clicked();

    void on_btnMonster_clicked();

private:
    Ui::MainWindow *ui;

//    poly2 ninjaObj;
//    poly2 monsterObj;

//    QString ninjaTalk;// = "I am a Ninga, Ninja Chop! - ";
//    QString monsterTalk;// = "I am a Monster, get in ma belleeeeh! - ";
};

#endif // MAINWINDOW_H
