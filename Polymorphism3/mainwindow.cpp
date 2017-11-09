#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poly2.h"

FooMainWindow::FooMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    // note can only use new bellow with pointer object
    // note can only use new bellow with pointer object
    ninjaObj(new Ninja),
    monsterObj(new Monster)
{
    ui->setupUi(this);

    for(int i; i < 10; i++){

        ui->comboBox->addItem("Item " + QString::number(i));

    }
}

FooMainWindow::~FooMainWindow()
{
    delete ui;
}

void FooMainWindow::on_btnNinja_clicked()
{
    ninjaObj->attack();
    sumString = ninjaObj->getterninTalk() + ninjaObj->getterAttackPower();
    ui->lineEdit->setText(sumString);
}

void FooMainWindow::on_btnMonster_clicked()
{
    monsterObj->attack();
    sumString = monsterObj->gettermonTalk() + monsterObj->getterAttackPower();
    ui->lineEdit->setText(sumString);
}

void FooMainWindow::on_comboBox_activated(const QString &arg1)
{
//    ui->comboBox->set
}

void FooMainWindow::on_checkBox_clicked()
{
    ui->checkBox->setText("Checked");
}
