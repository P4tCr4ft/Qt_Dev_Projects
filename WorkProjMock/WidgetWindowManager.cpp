/**
  *@file WidgetWindowManager.cpp
  * Management class to create and handle display characteristics
  * of radar output display widgets
*/

#include "WidgetWindowManager.h"
#include "Gui.h"
#include "RadarBurstSignalPowerViewInfo.h"
#include "RadarBurstRangeDopplerViewInfo.h"
#include "RadarBurstPPIViewInfo.h"
#include "RadarDataSelectList.h"
#include <controller/ihardwarecontroller.h>
#include <QMdiArea>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QDockWidget>
#include <QSettings>

#include <view/viewfactory.h>

using namespace dcap;

namespace trex {

WidgetWindowManager::WidgetWindowManager(const dcap::IHardwareControllerPtr &controller, QMdiArea *_mdiArea, QSettings &_settings) :
    QObject(_mdiArea),
    controller(controller),
    mdiArea(_mdiArea),
    mSettings(_settings)
{

/// moving Iview RadarBurstSignalPowerView object creation to RadarBurstSignalPowerView class

    QMdiSubWindow* w1 = new QMdiSubWindow();
    QMdiSubWindow* w2 = new QMdiSubWindow();
    QMdiSubWindow* w3 = new QMdiSubWindow();


    // the view name used as the key for the ViewFactory, this is the same as RadarBurstSignalPowerViewInfo::getName()
    auto &viewFactory = dcap::ViewFactory::getInstance();
    // use IView type instead of QWidget, to get write and read config

    QString viewName = RadarBurstSignalPowerViewInfo().getName();
    dcap::IView *window1View = viewFactory.createView(
                viewName, this->controller, MultiSystemIds(), MultiChannelIds(), w1);
    setupSubWindow(w1, viewName, viewName, window1View);
    subWindows.insert(w1);
    subViews.insert(window1View);

    viewName = RadarBurstRangeDopplerViewInfo().getName();
    dcap::IView *window2View = viewFactory.createView(
                viewName, this->controller, MultiSystemIds(), MultiChannelIds(), w2);
    setupSubWindow(w2, viewName, viewName, window2View);
    subWindows.insert(w2);
    subViews.insert(window2View);

    viewName = RadarBurstPPIViewInfo().getName();
    dcap::IView *window3View = viewFactory.createView(
                viewName, this->controller, MultiSystemIds(), MultiChannelIds(), w3);
    setupSubWindow(w3, viewName, viewName, window3View);
    subWindows.insert(w3);
    subViews.insert(window3View);

    // HACK for the beamformed views
    QMdiSubWindow* w4 = new QMdiSubWindow();
    viewName = RadarBurstSignalPowerViewInfo().getName();
    QString displayViewName = QString("Beamformed - %1").arg(viewName);
    dcap::IView *window4View = viewFactory.createView(
                viewName, this->controller, dcap::SingleSystemId(500), dcap::SingleChannelId(500), w4);
    setupSubWindow(w4, displayViewName, displayViewName, window4View);
    subWindows.insert(w4);
    subViews.insert(window4View);

    // HACK for the beamformed views
    QMdiSubWindow* w5 = new QMdiSubWindow();
    viewName = RadarBurstRangeDopplerViewInfo().getName();
    displayViewName = QString("Beamformed - %1").arg(viewName);
    dcap::IView *window5View = viewFactory.createView(
                viewName, this->controller, dcap::SingleSystemId(500), dcap::SingleChannelId(500), w5);
    setupSubWindow(w5, displayViewName, displayViewName, window5View);
    subWindows.insert(w5);
    subViews.insert(window5View);
}

WidgetWindowManager::~WidgetWindowManager(){
}

void WidgetWindowManager::setupSubWindow(
        QMdiSubWindow *subwin, QString objName, QString windowTitle, QWidget *widgetObj){
    subwin->setObjectName(objName);
    subwin->setWindowTitle(windowTitle);
    subwin->setAttribute(Qt::WA_DeleteOnClose);
    subwin->setWidget(widgetObj);
    connect(widgetObj, &QObject::destroyed, this, &WidgetWindowManager::onViewDestroyed);
    connect(subwin, &QObject::destroyed, this, &WidgetWindowManager::onSubWindowDestroyed);

}

void WidgetWindowManager::setupmdiArea(){
    mdiArea->closeAllSubWindows();
    for (auto subWindow : subWindows){
        mdiArea->addSubWindow(subWindow);
    }
}

void WidgetWindowManager::setupCascade(){
    current_layout = LAYOUT::LAYOUT_CASCADE;
    mdiArea->setViewMode(QMdiArea::SubWindowView);
    mdiArea->cascadeSubWindows();
    mdiArea->show();
}

void WidgetWindowManager::setupTiled(){
    current_layout = LAYOUT::LAYOUT_TILED;
    mdiArea->setViewMode(QMdiArea::SubWindowView);
    mdiArea->tileSubWindows();
    mdiArea->show();
}

void WidgetWindowManager::setupTabbed(){
    current_layout = LAYOUT::LAYOUT_TABBED;
    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->show();
}

void WidgetWindowManager::writeConfiguration(QSettings &settings){

    int layoutNum = static_cast<std::int32_t>(current_layout);
    settings.setValue("WindowLayout", QVariant(layoutNum));

    switch(current_layout){
    case LAYOUT::LAYOUT_CASCADE:
    case LAYOUT::LAYOUT_TILED:
        for (dcap::IView *subView : subViews){
            settings.beginGroup(subView->objectName());
            settings.setValue("ViewGeometry", subView->saveGeometry());
            settings.endGroup();
        }

        for (QMdiSubWindow *subWindow : subWindows){
            settings.beginGroup(subWindow->objectName());
            settings.setValue("WindowGeometry", subWindow->saveGeometry());
            settings.endGroup();
        }
    case LAYOUT::LAYOUT_TABBED:
        break; // do nothing

    }

    for (auto view : subViews)
        view->writeConfiguration(settings);
}

void WidgetWindowManager::readConfiguration(QSettings &settings){

    int layoutNum = static_cast<std::int32_t>(LAYOUT::LAYOUT_TILED);
    layoutNum = settings.value(QString("WindowLayout"), QVariant(layoutNum)).toInt();

    current_layout = static_cast<LAYOUT>(layoutNum);

    switch(current_layout){
    case LAYOUT::LAYOUT_CASCADE:
    case LAYOUT::LAYOUT_TILED:
        for (dcap::IView *subView : subViews){
            settings.beginGroup(subView->objectName());
            subView->restoreGeometry(settings.value("ViewGeometry").toByteArray());
            settings.endGroup();
        }
        for (QMdiSubWindow *subWindow : subWindows){
            settings.beginGroup(subWindow->objectName());
            subWindow->restoreGeometry(settings.value("WindowGeometry").toByteArray());
            settings.endGroup();
        }
        break;
    case LAYOUT::LAYOUT_TABBED:
        setupTabbed();
        break;

    }

    for (auto view : subViews)
        view->readConfiguration(settings);

}

std::set<IView *> WidgetWindowManager::getViews() const
{
    return std::set<IView*>(this->subViews.begin(), this->subViews.end());
}

void WidgetWindowManager::onViewDestroyed(QObject *obj)
{
    IView* v = static_cast<IView*>(obj);
    this->subViews.erase(v);
}

void WidgetWindowManager::onSubWindowDestroyed(QObject *obj)
{
    QMdiSubWindow* v = static_cast<QMdiSubWindow*>(obj);
    this->subWindows.erase(v);
}

}




