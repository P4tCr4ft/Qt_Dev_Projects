/**
  *@file IndicatorLight.h
  * Class to create Indicator Light widgets which display
  * status information of the connected radar hardware
  *
*/

#ifndef INDICATORLIGHT_H
#define INDICATORLIGHT_H

#include <QWidget>
#include <QLineEdit>

class IndicatorLight : public QLineEdit
{
    Q_OBJECT
public:
    /**
     * @brief The STATE enum
     * enumerator used to dictate state/color of Indicator Light widget
     * which reflects the corresponding status of the associated hardware
     */
    enum class STATE : std::int32_t{GOOD, WARNING, BAD, NEUTRAL};

    /**
     * @brief IndicatorLight
     * @param name is the hardware related name of the IndicatorLight object
     * @param _initialState is proposed initial state of hardware item
     * @param parent is parent class of IndicatorLight class
     */
    explicit IndicatorLight(QString name, STATE initial_state, QWidget *parent = 0);
    ~IndicatorLight();

    /**
     * @brief setState is used to change the indicator light state(status/color) to required new state
     * @param new_state is the passed in required new state
     */
    void setState(STATE new_state);

    /**
     * @brief getState returns current indicator light state
     * @return state
     */
    STATE getState() const;

    /**
     * @brief setColor sets background color of indicator light according to passed in state
     * @param state is the hardware status
     */
    void setColor(STATE state);

signals:

public slots:

private:

    QString name;
    STATE state;

};

#endif // INDICATORLIGHT_H
