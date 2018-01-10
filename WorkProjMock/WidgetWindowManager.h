/**
  *@file WidgetWindowManager.h
  * Management class to create and handle display characteristics
  * of radar output display widgets
*/


#ifndef WIDGETWINDOWMANAGER_H
#define WIDGETWINDOWMANAGER_H

#include <QObject>
#include <QMdiSubWindow>
#include <QStatusBar>
#include <QLineEdit>
#include <QHBoxLayout>

#include <controller/ihardwarecontroller.h>
#include "view/iviewcreator.h"

namespace trex {

/**
 * @brief The WidgetWindowManager class
 *
 * This class sets up a containing area, creates subwindow widgets to display
 * radar output plots, and manages how these widgets are arranged and displayed
 * within the containing area. It aslo handles saving the state and geometry of
 * the display widgets between application sessions.
 *
*/
class WidgetWindowManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief WidgetWindowManager
     * @param controller is the controller used to communicate with the hardware
     * @param _mdiArea is the containing area for display widgets
     * @param _settings are used to store and load state and geometry info for containing area and display widgets
     */
    explicit WidgetWindowManager(const dcap::IHardwareControllerPtr &controller, QMdiArea *_mdiArea, QSettings &_settings);
    ~WidgetWindowManager();

    /**
     * @brief The LAYOUT enum
     * enumerator used to dictate state saving behaviour of display widgets according to 3 options
     */
    enum class LAYOUT : std::int32_t{LAYOUT_CASCADE, LAYOUT_TILED, LAYOUT_TABBED};

    /**
     * @brief setupSubWindow function adds name & title to subwindow, and sets the view widget for subwindow
     * @param subwin is the subwindow
     * @param objName is the name of subwindow object
     * @param windowTitle is the title displayed for subwindow
     * @param windowWidget is the view widget displayed in the subwindow
     */
    void setupSubWindow(QMdiSubWindow *subwin, QString objName, QString windowTitle, QWidget *windowWidget);

    /**
     * @brief setupmdiArea function adds the created subwindows to the mdiArea containing area
     */
    void setupmdiArea();

    /**
     * @brief setupCascade function cascades the subwindows across the containing area
     */
    void setupCascade();

    /**
     * @brief setupTiled function displays subwindows as tiles within containing area
     */
    void setupTiled();

    /**
     * @brief setupTabbed function displays subwindows as tabbed tiles within containing area
     */
    void setupTabbed();

    /**
     * @brief writeConfiguration saves the geometry info to a file of view widgets and subwindows
     * for cascade and tiled display options, when the application is exited.
     */
    void writeConfiguration(QSettings &settings);

    /**
     * @brief readConfiguration loads the geometry info from file of view widgets and subwindows
     * for cascade and tiled display options, and sets tabbed mode if saved, when
     * application is started.
     */
    void readConfiguration(QSettings &settings);

    /**
     * @return all views managed
     */
    std::set<dcap::IView *> getViews() const;

signals:

private slots:
    void onViewDestroyed(QObject *obj);
    void onSubWindowDestroyed(QObject *obj);

private:
    dcap::IHardwareControllerPtr controller;

    QMdiArea *mdiArea;

    QSettings &mSettings;

    std::set<QMdiSubWindow*> subWindows;

    std::set<dcap::IView*> subViews;

    LAYOUT current_layout = LAYOUT::LAYOUT_TILED;


};

}

#endif // WIDGETWINDOWMANAGER_H
