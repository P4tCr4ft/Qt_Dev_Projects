/**
  *@file IndicatorLightBar.cpp
  * Class to create a containing area widget called Indicator Light Bar,
  * containing and displaying the individual Indicator Light widgets
  *
*/

#include "IndicatorLightBar.h"
#include <QGridLayout>

IndicatorLightBar::IndicatorLightBar(QWidget *parent) :
    QWidget(parent),
    layout(new QHBoxLayout())
{
}

void IndicatorLightBar::addLight(QString name, IndicatorLight::STATE initial_state){
    IndicatorLight *newLight = new IndicatorLight(name, initial_state, this);
    light_map[name] = newLight;
    layout->addWidget(newLight, 0, Qt::AlignLeft);
    this->setLayout(layout);
}

void IndicatorLightBar::setLightState(QString name, IndicatorLight::STATE new_state){
    light_map[name]->setState(new_state);
}

IndicatorLight::STATE IndicatorLightBar::getLightState(QString name){
    return light_map[name]->getState();
}
