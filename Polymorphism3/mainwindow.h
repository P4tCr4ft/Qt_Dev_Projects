#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "poly2.h"

namespace Ui {
class MainWindow;
}

class FooMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FooMainWindow(QWidget *parent = 0);
    ~FooMainWindow();

private slots:
    void on_btnNinja_clicked();

    void on_btnMonster_clicked();

private:
    Ui::MainWindow *ui;

    Ninja *ninjaObj;
    Monster *monsterObj;

    QString sumString;

};

#endif // MAINWINDOW_H
