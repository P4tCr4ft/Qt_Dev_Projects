/**
  *@file IndicatorLight.cpp
  * Class to create Indicator Light widgets which display
  * status information of the connected radar hardware
  *
*/

#include "IndicatorLight.h"

IndicatorLight::IndicatorLight(QString _name, STATE initial_state, QWidget *parent) :
    QLineEdit(parent),
    name(_name),
    state(initial_state)
{
    this->setFixedWidth(110);
    this->setText(name);
    this->setStyleSheet("text-color:black");
    this->setAlignment(Qt::AlignCenter);
    setColor(state);
}

IndicatorLight::~IndicatorLight(){
}


void IndicatorLight::setState(STATE new_state){
    state = new_state;
    setColor(state);
}

IndicatorLight::STATE IndicatorLight::getState() const{
    return state;
}

void IndicatorLight::setColor(STATE state){
    switch(state){
    case STATE::GOOD:
        this->setStyleSheet("background-color:green; color:black"); break;
    case STATE::WARNING:
        this->setStyleSheet("background-color:orange; color:black"); break;
    case STATE::BAD:
        this->setStyleSheet("background-color:red; color:black"); break;
    case STATE::NEUTRAL:
        this->setStyleSheet("background-color:lightgrey; color:black"); break;
    }
}



