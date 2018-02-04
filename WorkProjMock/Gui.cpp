//------------------------------------------------------------------------------
// Copyright (c) DST, 2017
//
// Project:                 EA EP Testbed
// Classification:          Unclassified
// Intellectual Property:   DST
//
//------------------------------------------------------------------------------
// $Id: Gui.cpp 4487 2017-10-25 04:08:01Z triplets $
//------------------------------------------------------------------------------
//
/**
 *@file Gui.cpp
 * Main GUI for the EA EP Testbed
*/

#include "Gui.h"
#include "RadarBurstSignalPowerView.h"
#include "WidgetWindowManager.h"


#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
//#include <QTextEdit>
#include <QLineEdit>
#include <QStatusBar>
#include <QSettings>

#include <view/logview.h>
#include <view/viewfactory.h>
#include <controller/filefactory.h>
#include <controller/filecapability.h>

using namespace dcap;

namespace trex {

Gui::Gui(const dcap::IHardwareControllerPtr &controller, QSettings &settings, QWidget *parent) :
    QMainWindow(parent),
    mSettings(settings)
{
    this->controller = controller;
    this->model = controller->getModel();

    // initialises the logger
    this->logger = LogModelData::getLogger(model);

    this->logMessage("Creating TREX GUI", LogLevel::INFO);

    // Set the window title bar
    setWindowTitle(controller->getName());

    this->createLayout();
    this->createActions();
    this->createMenus();
    this->createTasks();

    managerObj = new WidgetWindowManager(controller, this->mdiArea, mSettings);
    managerObj->setupmdiArea();

    // put load config settings here
    readConfiguration(mSettings);

    // TODO create a thread that will handle all the slots from the model and controller to not tie up the main GUI thread
    // set all slots to be directed to this
}

Gui::~Gui()
{
    // saves the current configuration
    writeConfiguration(mSettings);
}

void Gui::logMessage(QString message, dcap::LogLevel logLevel, dcap::SingleSystemId systemId, dcap::SingleChannelId channelId)
{
    std::shared_ptr<dcap::LogMessage> lm(new LogMessage(message,systemId,channelId,logLevel,"GUI"));
    this->logger->addLogMessage(lm);
}

void Gui::onOpen()
{
    this->logMessage("onOpen()");

    FileFactory &ff = FileFactory::getInstance();

    // Get the filters
    QStringList filterList = ff.getNameFilters();
    QString filters        = "All Files (*.*)";
    for (auto f = filterList.begin(); f != filterList.end(); ++f) {
        filters += ";;" + *f;
    }

    QString dataDirectory = QString();
    QString fileName = QFileDialog::getOpenFileName(this, "Open File To Playback",
            dataDirectory, filters);
    if (fileName.isNull()) {
        this->logMessage("No File Selected");
        return;
    }

    this->logMessage("Loading file " + fileName, LogLevel::INFO);
    auto fileLoaders = ff.createFileLoaders(fileName, this->controller);
    if (fileLoaders.size() == 0) {
        this->logMessage("No File Loader Found");
        return;
    }

    // FIXME we can currently only process the first
    if (fileLoaders.size() > 1) {
        this->logMessage("GUI can only handle one loaded file system at a time, the first one will be loaded",
                LogLevel::WARNING);
    }

//    for(auto fileLoader = fileLoaders.begin(); fileLoader != fileLoaders.end(); fileLoader++){
//        (*fileLoader)->initialise();
//    }

    IFileLoaderPtr &loader = fileLoaders[0];
    this->logMessage("FileLoader: " + loader->getName(), LogLevel::INFO);

    // If we already got a file system loaded, remove it so that the new one can be put in
    auto oldSys = this->controller->getSystem(loader->getSystem());
    if (oldSys) {
        this->controller->removeSystem(oldSys);
    }

    // Create the file system
    FileSystemPtr fileSystem(new FileSystem(loader));
    this->controller->addSystem(fileSystem);

    // FIXME A hack to test
    auto fileCapability = std::dynamic_pointer_cast<FileCapability>(
            fileSystem->getCapability(SingleCapabilityId(
                            CONTROLLER_CAPABILITY_FILE_PLAYBACK), SingleChannelId::NA));

    if (fileCapability) {
        logMessage("Starting File Playback", LogLevel::INFO);
        fileCapability->setPlaybackRate(100);
        fileCapability->play();
        //            usleep(5e5);
        //            fileCapability->pause();
    } else {
        logMessage("No File Capability, unable to start file playback", LogLevel::ERROR);
    }

    // updates our views and tasks to use the file system
    this->updateSystemId(fileSystem->getID());

    // removes the old file system if it is there and updates
    if(this->fileSystem){
        this->controller->removeSystem(this->fileSystem);
    }
    this->fileSystem = fileSystem;
}

void Gui::onClose()
{
    this->logMessage("onClose()");
}

// new slots for window view options
void Gui::onCascade()
{
    this->logMessage("onCascade()");
    this->managerObj->setupCascade();
}

void Gui::onTiled()
{
    this->logMessage("onTiled()");
    managerObj->setupTiled();
}

void Gui::onTabbed()
{
    this->logMessage("onTabbed()");
    managerObj->setupTabbed();
}

void Gui::onOptions()
{
    this->logMessage("onOptions()");
}

void Gui::onImport()
{
    this->logMessage("onImport()");
}

void Gui::onExport()
{
    this->logMessage("onExport()");
}

void Gui::onExit()
{
    this->logMessage("onExit()");
    QWidget::close();
}

void Gui::onAbout()
{
    this->logMessage("onAbout()");
    QMessageBox::about(this, tr("About T-Rex"),
                       tr("<center><big><b>T-Rex (Transmit Receive Experiments)</b></big></center>"
                       "<p>T-Rex provides control and capability for experimental radar systems"
                       "<hr><center><u>Developed by MRS Group, NSID, DST</u></center>"
                       "<br>Please report bugs and suggestions to:<blockquote><address>"
                       "<a href=\"mailto:David.Roberts@dst.defence.gov.au\">David Roberts (david.roberts@dst.defence.gov.au)</a>"
                       "<br><br>Ph: +61 8 7389 4880"
                       "<br><br><u>or via post:</u>"
                       "<br><br>DST Edinburgh<br>PO Box 1500"
                       "<br>Edinburgh SA 5111<br>AUSTRALIA</address></blockquote>" ));
}

void Gui::createLayout()
{
    this->logMessage("createLayout()");

    // Create the MDI area
    this->mdiArea = new QMdiArea(this);
    this->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->mdiArea->setViewMode(QMdiArea::SubWindowView);

    //connect(this->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(manageWindowsMenu()));

    // Set the MDI area as the central widget
    setCentralWidget(this->mdiArea);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

//    // Create the signal mapper for the windows menu
//    windowMenuMapper = new QSignalMapper(this);
//    connect(windowMenuMapper, SIGNAL(mapped(QWidget *)), this, SLOT(setActiveSubWindow(QWidget *)));

//    // Ensure the alternative MDI area is null
//    secondaryMdiArea = NULL;
//    secondaryMdiAreaSize = QSize(1500, 1000);
//    secondaryMdiAreaPosition = QPoint(50, 50);

//    // Set up the subwindow mapper
//    switchSubWindowMapper = new QSignalMapper(this);
//    connect(switchSubWindowMapper, SIGNAL(mapped(QWidget *)), this, SLOT(switchMdiArea(QWidget *)));

    // creates a dock widget for the log view
    QDockWidget *logDockWidget = new QDockWidget("Log");
    logDockWidget->setObjectName("logDockWidget");
    logDockWidget->setWidget(LogViewCreator().createView(this->controller, MultiSystemIds(), MultiChannelIds(), logDockWidget));
    logDockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, logDockWidget);

    // creates a dock widget for viewing the model
    QDockWidget *modelDockWidget = new QDockWidget("Model View");
    modelDockWidget->setObjectName("modelDockWidget");
    modelDockWidget->setWidget(ViewFactory::getInstance().createView("Model View", this->controller, MultiSystemIds(), MultiChannelIds(), modelDockWidget));
    modelDockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, modelDockWidget);

    // creates a dock widget for viewing the capabilities
    QDockWidget *capabilityDockWidget = new QDockWidget("Capability View");
    capabilityDockWidget->setObjectName("capabilityDockWidget");
    capabilityDockWidget->setWidget(ViewFactory::getInstance().createView("Capability View", this->controller, MultiSystemIds(), MultiChannelIds(), capabilityDockWidget));
//    capabilityDockWidget->setWidget(CapabilityViewCreator().createView(this->controller, MultiSystemIds(), MultiChannelIds(), capabilityDockWidget));
    capabilityDockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, capabilityDockWidget);

    // create hardware status indicator lights in a display bar
    indLightBarObj = new IndicatorLightBar(this);

    indLightBarObj->addLight("HardwareOne", IndicatorLight::STATE::GOOD);
    indLightBarObj->addLight("HardwareTwo", IndicatorLight::STATE::WARNING);
    indLightBarObj->addLight("HardwareThree", IndicatorLight::STATE::BAD);

    QDockWidget *indicatorLightBar = new QDockWidget("Indicator Light Bar");
    indicatorLightBar->setObjectName("IndicatorLightBarDockWidget");
    indicatorLightBar->setFixedWidth(500);
    indicatorLightBar->setFixedHeight(50);
    indicatorLightBar->setWidget(indLightBarObj);
    indicatorLightBar->setAllowedAreas(Qt::TopDockWidgetArea | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::TopDockWidgetArea, indicatorLightBar);
}


void Gui::createActions()
{
    logMessage("createActions()");

    // File menu actions
    this->actionOpen = new QAction(QIcon(":/images/open"), "&Open File...", this);
    this->actionOpen->setStatusTip("Open a file");
    this->actionOpen->setShortcut(QKeySequence("Ctrl+O"));
    connect(this->actionOpen, &QAction::triggered, this, &Gui::onOpen);

    this->actionClose = new QAction(QIcon(":/images/close"), "&Close File", this);
    this->actionClose->setStatusTip("Close the currently open file");
    connect(this->actionClose, &QAction::triggered, this, &Gui::onClose);

    // use /images/open for now ...
    this->actionWindowView = new QAction(QIcon(":/images/open"), "&Cascade View", this);
    this->actionWindowView->setStatusTip("Select view mode for windows");
    // possibility of using slot from some other newly created class here,
    // ie &ControlClass::onCascade ...
    connect(this->actionWindowView, &QAction::triggered, this, &Gui::onCascade);

    this->actionWindowView2 = new QAction(QIcon(":/images/open"), "&Tiled View", this);
    this->actionWindowView2->setStatusTip("Select view mode for windows");
    // possibility of using slot from some other newly created class here,
    // ie &ControlClass::onView ... connect to onOptions just for now ...
    connect(this->actionWindowView2, &QAction::triggered, this, &Gui::onTiled);

    this->actionWindowView3 = new QAction(QIcon(":/images/open"), "&Tabbed View", this);
    this->actionWindowView3->setStatusTip("Select view mode for windows");
    // possibility of using slot from some other newly created class here,
    // ie &ControlClass::onView ... connect to onOptions just for now ...
    connect(this->actionWindowView3, &QAction::triggered, this, &Gui::onTabbed);

    this->actionOptions = new QAction(QIcon(":/images/options"), "O&ptions...", this);
    this->actionOptions->setStatusTip("Launch the options dialog");
    connect(this->actionOptions, &QAction::triggered, this, &Gui::onOptions);

    this->actionImport = new QAction(QIcon(":/images/import"), "&Import Settings", this);
    this->actionImport->setStatusTip("Import the settings from a file");
    connect(this->actionImport, &QAction::triggered, this, &Gui::onImport);

    this->actionExport = new QAction(QIcon(":/images/export"), "&Export Settings", this);
    this->actionExport->setStatusTip("Export the current settings to a file");
    connect(this->actionExport, &QAction::triggered, this, &Gui::onExport);

    this->actionExit = new QAction(QIcon(":/images/exit"), "&Exit", this);
    this->actionExit->setStatusTip("Exit the application");
    connect(this->actionExit, &QAction::triggered, this, &Gui::onExit);

    // Help menu actions
    this->actionAbout = new QAction("&About", this);
    this->actionAbout->setStatusTip("Open the about dialog");
    connect(this->actionAbout, &QAction::triggered, this, &Gui::onAbout);
}

void Gui::createMenus()
{
    logMessage("createMenus()");

    // The menu bar
    QMenuBar *menubar = menuBar();

    // The file menu
    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(this->actionOpen);
    fileMenu->addAction(this->actionClose);
//    fileMenu->addAction(this->actionTestWndView);
    fileMenu->addSeparator();
    fileMenu->addAction(this->actionImport);
    fileMenu->addAction(this->actionExport);
    fileMenu->addSeparator();
    fileMenu->addAction(this->actionOptions);
    fileMenu->addSeparator();
    fileMenu->addAction(this->actionExit);

    // A separator
    menubar->addSeparator();

    // Add menu for selecting view of widget windows
    QMenu *viewMenu = menubar->addMenu("&View");
    viewMenu->addAction(this->actionWindowView);
    viewMenu->addAction(this->actionWindowView2);
    viewMenu->addAction(this->actionWindowView3);

    // A separator
    menubar->addSeparator();

    // Help menu
    QMenu *helpMenu = menubar->addMenu("&Help");
    helpMenu->addAction(this->actionAbout);
}

void Gui::createRadarSystem()
{
    logMessage("createRadarSystem()");
    // there can only be a single radar system, scan through all systems that have a radar capability
    // TODO
}

void Gui::createTasks()
{
    logMessage("createTasks()");

    logMessage("Creating Beamforming Task");
    // TODO use the task factory
    this->beamformTask = std::make_shared<RadarBurstBeamformTask>();
    this->beamformTask->setController(this->controller);
    this->beamformTask->create(dcap::MultiSystemIds(), dcap::MultiSystemIds(), dcap::MultiChannelIds());
    this->tasks.insert(this->beamformTask);

//    // starts all tasks
//    for(auto task : this->tasks){
//        task->start();
//    }
}

void Gui::updateSystemId(const SingleSystemId &systemId)
{
    // gets the channels with this system
    auto channelsId = this->controller->getChannelIDs(systemId);

    // updates our tasks
    for(auto task : this->tasks){
        task->setSystemChannel(systemId,systemId,channelsId);
        task->start();
    }

    // updates our views
    auto views = this->managerObj->getViews();
    for(auto view : views){
        view->setSystemChannel(systemId, channelsId);
    }
}

void Gui::writeConfiguration(QSettings &settings){
    logMessage("writeConfiguration()");

    settings.beginGroup("GuiWindow");
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("State", saveState());
    settings.endGroup();

    // saves the configuration of our widgets
    managerObj->writeConfiguration(mSettings);
}

void Gui::readConfiguration(QSettings &settings){
    logMessage("loadConfiguration()");

    settings.beginGroup("GuiWindow");
    restoreGeometry(settings.value("Geometry").toByteArray());
    restoreState(settings.value("State").toByteArray());
    settings.endGroup();

    // loads the configuration of our widgets
    managerObj->readConfiguration(mSettings);
}

}
