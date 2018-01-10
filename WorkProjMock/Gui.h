/**
 *@file Gui.h
 * Main GUI for the EA EP Testbed
*/

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include <controller/ihardwarecontroller.h>
#include <controller/filesystem.h>
#include <model/imodel.h>
#include <model/logmodeldata.h>

#include "WidgetWindowManager.h"
#include "IndicatorLight.h"
#include "IndicatorLightBar.h"
#include "task/RadarBurstBeamformTask.h"

class QMdiArea;

namespace trex {

class Gui : public QMainWindow
{
    Q_OBJECT
public:
    explicit Gui(const dcap::IHardwareControllerPtr &controller, QSettings &settings, QWidget *parent = 0);
    virtual ~Gui();

public slots:
    /**
     * Helper function to log messages to the LogModelData.
     *
     * Logs a new message to the logger; this does not display it.
     * @param message the message to log.
     * @param logLevel the severity level of the logged information.
     * @param systemId the system ID.
     * @param channelId the channels this log refers to.
     */
    void logMessage(QString message,
                    dcap::LogLevel logLevel = dcap::LogLevel::INFO_VERBOSE,
                    dcap::SingleSystemId systemId = dcap::SingleSystemId::NA,
                    dcap::SingleChannelId channelId = dcap::SingleChannelId::NA);

protected slots:
    /// Opens a file dialog to select a file to load in
    void onOpen();
    /// Closes all open files
    void onClose();
    // New slots for window view options
    void onCascade();
    void onTiled();
    void onTabbed();
    /// Open the options dialog
    void onOptions();
    /// Imports configuration options
    void onImport();
    /// Exports configuration options
    void onExport();
    /// Exits the GUI
    void onExit();
    /// Displays a about dialog
    void onAbout();

private:
    /// The controller used to communicate with the hardware
    dcap::IHardwareControllerPtr controller;

    /// the model used to store the data
    dcap::IModelPtr model;

    /// The logger
    dcap::LogModelDataPtr logger;

    /// The main MDI area for widgets / views
    QMdiArea *mdiArea;

//    QStatusBar *statusBar;

    //@{ File menu actions
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionWindowView;
    QAction *actionWindowView2;
    QAction *actionWindowView3;
    QAction *actionOptions;
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionExit;
    //@}

    //@{ Help menu actions
    QAction *actionAbout;
    //@}

    //Indicator Light Bar object
    IndicatorLightBar *indLightBarObj;

    // widget window manager object
    WidgetWindowManager *managerObj;

    // file location for save state config file
    QSettings &mSettings;

    /// the file system that we are currently displaying
    dcap::FileSystemPtr fileSystem;

    std::shared_ptr<RadarBurstBeamformTask> beamformTask;

    /// collection of all the tasks that are running on our data
    std::set<dcap::ITaskPtr> tasks;

    /// Creates the initial GUI frame layout
    void createLayout();

    /// Creates the actions for menu and toolbar buttons
    void createActions();

    /// Creates the menus
    void createMenus();

    /// Scans the currently installed radar systems in the controller and actives only a single one to work with the GUI
    void createRadarSystem();

    /// Creates the tasks that we want to use and creates a viewable widget to control them
    void createTasks();

    /**
     * Updates all views and tasks to use the new system ID.
     *
     * @param id the new system ID
     */
    void updateSystemId(const dcap::SingleSystemId &systemId);

    /// save config function to save state of gui mainwindow
    void writeConfiguration(QSettings &settings);

    /// load config function to load saved state of gui mainwindow
    void readConfiguration(QSettings &settings);
};

}

#endif // GUI_H
