#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poly2.h"

FooMainWindow::FooMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
//    ninjaObj(new Ninja),
//    monsterObj(new Monster)
{
    ui->setupUi(this);
    Ninja n;
    Monster m;

    poly2 *ninPtr = &n;
    poly2 *monPtr = &m;
}

FooMainWindow::~FooMainWindow()
{
    delete ui;
}

//void FooMainWindow::talkShouter(QString x){
//    ui->lineEdit->setText(x);
//}

void FooMainWindow::on_btnNinja_clicked()
{
//    ninjaObj.setAttackPower(25);


}

void FooMainWindow::on_btnMonster_clicked()
{
//    monsterObj.setAttackPower(55);


//    ui->lineEdit->setText();
}