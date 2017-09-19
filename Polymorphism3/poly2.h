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

//    void setterninTalk(QString x){ninjaTalk = x;}
//    QString getterninTalk(){return ninjaTalk;}

//    void settermonTalk(QString x){monsterTalk = x;}
//    QString gettermonTalk(){return monsterTalk;}

    void setAttackPower(QString a){attackPower = a;}
    QString getterAttackPower(){return attackPower;}

signals:

public slots:

private:
//    QString ninjaTalk;
//    QString monsterTalk;
    QString attackPower;

};

class Ninja : public poly2{
public:
    void setterninTalk(QString x){ninjaTalk = x;}
    QString getterninTalk(){return ninjaTalk;}

    void attack();

private:
    QString ninjaTalk;

};

class Monster : public poly2{
public:
    void settermonTalk(QString x){monsterTalk = x;}
    QString gettermonTalk(){return monsterTalk;}

    void attack();

private:
    QString monsterTalk;

};

#endif // POLY2_H
