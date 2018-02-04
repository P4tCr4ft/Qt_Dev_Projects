/**
  *@file RadarDataSelectList.h
  * QWidget providing list of radar burst data view modes
  * for selection for plot display
*/

#ifndef RADARDATASELECTLIST_H
#define RADARDATASELECTLIST_H

#include <QWidget>
#include <QListWidget>
#include <pviewer/QMultiComboBox.h>

/**
 * @brief The RadarDataSelectList class
 *
 * QWidget extending QMultiComboBox to provide selectable list
 * of radar burst data view modes, and enables multiple modes
 * to be selected and displayed on the plot simultaneously
 */
class RadarDataSelectList : public QMultiComboBox
{
    Q_OBJECT

public:
    /**
     * @brief The VIEWMODE enum
     * enumerator used to map active radar burst data mode
     */
    enum class VIEWMODE : std::int8_t {REAL, IMAG, AMP, PHASE};

    /**
     * @brief RadarDataSelectList
     * @param name is Qstring describing name of list
     * @param initial_mode is initial default data mode for display
     * @param parent is parent class of instance of this class
     */
    explicit RadarDataSelectList(QString name, VIEWMODE initial_mode, QWidget *parent = 0);
    ~RadarDataSelectList();


    std::map<VIEWMODE, QListWidgetItem*> listItems;
    std::map<VIEWMODE, bool> activeModes;

signals:
    void updated();

public slots:
    void updateMode(QListWidgetItem *item);

private:

    QString name;
    VIEWMODE mode;

    std::map<QString, VIEWMODE> modeMap;

};

#endif // RADARDATASELECTLIST_H
