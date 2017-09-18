#ifndef POLY2_H
#define POLY2_H

#include <QObject>

// for similarity to bucky tutorial's sake I prob
// should have called this Enemy instead of poly2...

class poly2 : public QObject
{
    Q_OBJECT
public:
    explicit poly2(QObject *parent = nullptr);

    void setterninTalk(QString x){ninjaTalk = x;}
    QString getterninTalk(){return ninjaTalk;}

    void settermonTalk(QString x){monsterTalk = x;}
    QString gettermonTalk(){return monsterTalk;}

    void setAttackPower(QString a);

//    void talkShouter(QString x);

signals:

public slots:

private:
    QString ninjaTalk;// = "I am a Ninga, Ninja Chop! - ";
    QString monsterTalk;// = "I am a Monster, get in ma belleeeeh! - ";
    QString attackPower;

};

class Ninja : public poly2{
public:
    void attack();
};

class Monster : public poly2{
public:
    void attack();
};

#endif // POLY2_H
