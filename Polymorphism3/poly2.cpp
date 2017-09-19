#include "poly2.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

poly2::poly2(QObject *parent) : QObject(parent)
{

}

//void poly2::talkShouter(QString x){
//    ui
//}

void poly2::setAttackPower(QString a){
    attackPower = a;
}

void Ninja::attack(){
//    poly2.setterninTalk("I am a Ninja, Ninja chop!");
    this->setterninTalk("I am a Ninja, Ninja chop!");
    this->setAttackPower("45");

}

void Monster::attack(){
//    poly2.settermonTalk("I am a Monster, get in maaah beelleeeeh!");
    this->settermonTalk("I am a Monster, get in maaah beelleeeeh!");
    this->setAttackPower("95");
}
