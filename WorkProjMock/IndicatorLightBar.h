/**
  *@file IndicatorLightBar.h
  * Class to create a containing area widget called Indicator Light Bar,
  * containing and displaying the individual Indicator Light widgets
  *
*/

#ifndef INDICATORLIGHTBAR_H
#define INDICATORLIGHTBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include "IndicatorLight.h"

class IndicatorLightBar : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief IndicatorLightBar
     * @param parent is the parent class of IndicatorLightBar class
     */
    explicit IndicatorLightBar(QWidget *parent = 0);

    /**
     * @brief addLight creates a new instance of IndicatorLight
     * and adds that object to the IndicatorLightBar containing area layout
     * to display the new light
     * @param name is the hardware related name of the IndicatorLight object
     * @param initial_state is proposed initial state of hardware item
     */
    void addLight(QString name, IndicatorLight::STATE initial_state);

    /**
     * @brief setLightState is used to change the indicator light state(status/color)
     * to required new state
     * @param name is the hardware related name of the IndicatorLight object
     * @param new_state is the passed in required new state
     */
    void setLightState(QString name, IndicatorLight::STATE new_state);

    /**
     * @brief getLightState returns current indicator light state
     * @param name is name of IndicatorLight object
     * @return state
     */
    IndicatorLight::STATE getLightState(QString name);

signals:

public slots:

private:
    /**
     * @brief layout used to display individual indicator lights in a row
     */
    QHBoxLayout *layout;

    /**
     * @brief light_map structure used to map IndicatorLight objects to it's name
     */
    std::map<QString, IndicatorLight*> light_map;

};

#endif // INDICATORLIGHTBAR_H
