//------------------------------------------------------------------------------
// Copyright (c) DST, 2017
//
// Project:                 EA EP Testbed
// Classification:          Unclassified
// Intellectual Property:   DST
//
//------------------------------------------------------------------------------
// $Id: RadarBurstSignalPowerView.cpp 4521 2017-12-19 06:19:43Z triplets $
//------------------------------------------------------------------------------
//
/**
 *@file RadarBurstSignalPowerView.cpp
 * View for RadarBurstModelData
*/

#include "RadarBurstSignalPowerView.h"
#include "RadarBurstSignalPowerViewInfo.h"

#include "model/RadarBurstDataReader.h"

#include <qlayout.h>
#include <complex>
#include <qwt_scale_engine.h>

#include <QEvent>

// only required for signals to connect
using namespace dcap;

namespace trex {

RadarBurstSignalPowerView::RadarBurstSignalPowerView():
    dcap::AbstractView(std::shared_ptr<dcap::IViewInfo>(new RadarBurstSignalPowerViewInfo()))
{
    if(this->layout() != NULL){
        delete this->layout();
    }
    dataConsumer = NULL;

    m_layout = new QHBoxLayout();
    selectListGroupBox = new QGroupBox("Select List Layout");
    m_plot = new QwtPlot(this->getInfo()->getName(), this);
    m_plot->setAxisTitle(QwtPlot::xBottom, "Time");
    m_plot->setAxisTitle(QwtPlot::yLeft, "Amplitude");

    m_magnifier = new QwtPlotMagnifier(m_plot->canvas());
    m_magnifier->setAxisEnabled(QwtPlot::yLeft, false);
    double wheelFactor = 1.1;
    m_magnifier->setWheelFactor(wheelFactor);
    m_zoomer = new QwtPlotZoomer(m_plot->canvas());
    m_panner = new QwtPlotPanner(m_plot->canvas());
    m_panner->setMouseButton(Qt::MiddleButton);

    m_legend = new QwtLegend();
    m_plot->insertLegend(m_legend, QwtPlot::BottomLegend);


    m_layout->addWidget(m_plot);
    m_layout->addWidget(selectListGroupBox);
    m_layout->setStretch(0,100);
    this->setLayout(m_layout);

}

RadarBurstSignalPowerView::~RadarBurstSignalPowerView()
{

    if (dataConsumer != NULL && dataConsumerThread.isRunning()) {
        dataConsumerThread.quit();
        dataConsumerThread.wait();
    }

    delete m_plot;

}

QColor RadarBurstSignalPowerView::GetColor(float v, float vmin, float vmax){
    float r = 1.0, g = 1.0, b = 1.0; // white
    float dv;

    if (v < vmin)
       v = vmin;
    if (v > vmax)
       v = vmax;
    dv = vmax - vmin;

    if (v < (vmin + 0.25 * dv)) {
       r = 0;
       g = 4 * (v - vmin) / dv;
    } else if (v < (vmin + 0.5 * dv)) {
       r = 0;
       b = 1 + 4 * (vmin + 0.25 * dv - v) / dv;
    } else if (v < (vmin + 0.75 * dv)) {
       r = 4 * (v - vmin - 0.5 * dv) / dv;
       b = 0;
    } else {
       g = 1 + 4 * (vmin + 0.75 * dv - v) / dv;
       b = 0;
    }

    return QColor(r*255,g*255,b*255);

}

QSize RadarBurstSignalPowerView::sizeHint() const
{
    return QSize(300,100);
}

void RadarBurstSignalPowerView::writeConfiguration(QSettings &settings)
{
    settings.beginGroup("RadarBurstPowerSignalView");
    settings.setValue("SelectedModeREAL",  QVariant(m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::REAL]));
    settings.setValue("SelectedModeIMAG",  QVariant(m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::IMAG]));
    settings.setValue("SelectedModeAMP",   QVariant(m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::AMP]));
    settings.setValue("SelectedModePHASE", QVariant(m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::PHASE]));
    settings.endGroup();
    // TODO
}

void RadarBurstSignalPowerView::readConfiguration(QSettings &settings)
{
    settings.beginGroup("RadarBurstPowerSignalView");
//    bool active;
//    // REAL
//    active = settings.value("SelectedModeREAL",  QVariant(true)).toBool();
//    m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::REAL]  = active;
//    m_mode_list->listItems[RadarDataSelectList::VIEWMODE::REAL]->setSelected(active);
//    //IMAG
//    active = settings.value("SelectedModeIMAG",  QVariant(false)).toBool();
//    m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::IMAG]  = active;
//    m_mode_list->listItems[RadarDataSelectList::VIEWMODE::IMAG]->setSelected(active);
//    //AMPLITUDE
//    active = settings.value("SelectedModeAMP",   QVariant(false)).toBool();
//    m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::AMP]   = active;
//    m_mode_list->listItems[RadarDataSelectList::VIEWMODE::AMP]->setSelected(active);
//    //PHASE
//    active = settings.value("SelectedModePHASE", QVariant(false)).toBool();
//    m_mode_list->activeModes[RadarDataSelectList::VIEWMODE::PHASE] = active;
//    m_mode_list->listItems[RadarDataSelectList::VIEWMODE::PHASE]->setSelected(active);
    settings.endGroup();

}

void RadarBurstSignalPowerView::handleResults(const std::map<dcap::SingleChannelId, sRadarBurstCurves_t*> *result){
    m_plot_curves.push_back(result);
    m_burst_counter += 1;
    m_burst_list->addItem(QString("Burst %1").arg(m_burst_counter));
    m_burst_list->setCurrentIndex(m_burst_list->count()-1);
}

bool RadarBurstSignalPowerView::createView()
{
    this->logMessage("createView", dcap::LogLevel::INFO_VERBOSE);
    // TODO create the widgets

    m_burst_list = new QComboBox(this);

    m_mode_list = new RadarDataSelectList("View Modes", RadarDataSelectList::VIEWMODE::REAL, this);
    connect(m_mode_list, &RadarDataSelectList::updated, this, &RadarBurstSignalPowerView::updateMode);


    m_chan_list = new QListWidget(this);
    m_chan_list->setSelectionMode(QListWidget::SelectionMode::MultiSelection);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_burst_list);
    layout->addWidget(m_mode_list);
    layout->addWidget(m_chan_list);
    selectListGroupBox->setLayout(layout);
    return true;
}

bool RadarBurstSignalPowerView::viewAvailable(const std::vector<std::shared_ptr<dcap::ICapabilityData> > &capabilities, const std::vector<std::shared_ptr<dcap::IModelData> > &modelData)
{
    static_cast<void>(capabilities);

    this->logMessage("viewAvailable", dcap::LogLevel::INFO_VERBOSE);

    // loads in the radar burst and channel data
    for(auto d: modelData){
        auto dId = (d)->getID();
        if(dId == TrexModelDataIds::RadarBurstId){
            auto radarBurstData = std::dynamic_pointer_cast<RadarBurstModelData>(d);
            auto cId = radarBurstData->getChannel();
            if(radarBurstData){
                this->burstData[cId] = radarBurstData;
                // connects the state changed
                connect(radarBurstData->asQObject(),
                        SIGNAL(stateChange(const dcap::ModelDataState, const dcap::ModelDataState)),
                        this,
                        SLOT(dataStateChanged(const dcap::ModelDataState, const dcap::ModelDataState)));
            }
            else {
                // should never happen
                this->logMessage("Bad dynamic_pointer_cast<RadarBurstModelData>", dcap::LogLevel::WARNING);
            }
        } else if(dId == dcap::SingleChannelId(MODEL_DATA_CHANNEL_SPECS)){
            auto channelData = std::dynamic_pointer_cast<dcap::ChannelSpecsData>(d);
            auto cId = channelData->getChannel();
            if(channelData) {
                this->channelData[cId] = channelData;
            } else {
                // should never happen
                this->logMessage("Bad dynamic_pointer_cast<ChannelSpecsData>", dcap::LogLevel::WARNING);
            }
        }
    }

    // verify we got the data we require for the view
    if(this->channelData.size() == 0 || this->burstData.size() != this->channelData.size()){
        QString message = QString("Missing channel specs data (size=%1) or radar burst data (size=%2)").arg(this->channelData.size()).arg(this->burstData.size());
        this->logMessage(message, dcap::LogLevel::ERROR);
        this->channelData.clear();
        this->burstData.clear();

        return false;
    }


    int i = 0;
    for (auto channel : this->channelData) {

        auto *item = new QListWidgetItem(controller->getChannelName(systemId.toSingleID(), channel.first));
        m_chan_list->addItem(item);
        item->setForeground(GetColor(i+1, 0, 16));
        i++;
        m_channel_map[item] = channel.first;
    }

    // setup radar data consumer thread
    dataConsumer = new RadarBurstDataConsumer(this->channelData, this->burstData);
    dataConsumer->moveToThread(&dataConsumerThread);

    connect(&dataConsumerThread, &QThread::finished, dataConsumer, &RadarBurstDataConsumer::deleteLater);
    connect(this, &RadarBurstSignalPowerView::operate, dataConsumer, &RadarBurstDataConsumer::doDataConsume);
    connect(dataConsumer, &RadarBurstDataConsumer::resultReady, this, &RadarBurstSignalPowerView::handleResults);

    typedef void (QComboBox::*IndexChangedFcn)(int);
    connect(m_burst_list, (IndexChangedFcn)&QComboBox::currentIndexChanged, this, &RadarBurstSignalPowerView::updateBurst);
    connect(m_chan_list, &QListWidget::itemSelectionChanged, this, &RadarBurstSignalPowerView::updateChannel);

    dataConsumerThread.start();
    emit operate();

    return true;
}

void RadarBurstSignalPowerView::updateBurst(int){
    updatePlot();
}

void RadarBurstSignalPowerView::updateMode(){
    updatePlot();
    if(m_update_zoom != true && m_zoom_base == true){
        m_zoomer->setZoomBase();
        m_update_zoom = true;
    } else {
        m_update_zoom = true;
    }
}

void  RadarBurstSignalPowerView::updateChannel(){

    updatePlot();
    if(m_zoom_base != true && m_update_zoom == true){
        m_zoomer->setZoomBase();
        m_zoom_base = true;
    } else {
        m_zoom_base = true;
    }
}


void RadarBurstSignalPowerView::dataStateChanged(const dcap::ModelDataState oldState, const dcap::ModelDataState newState)
{
    static_cast<void>(oldState);

    QObject* obj = sender();
    RadarBurstModelData *data = qobject_cast<RadarBurstModelData*>(obj);
    if(data != NULL){
        QString state = (newState == ModelDataState::OK) ? "OK" : (newState == ModelDataState::OK_PAUSED ? "OK_PAUSED" : "UNKNOWN");
        this->logMessage(QString("%1[%2] new state: %3").arg(data->getName()).arg(data->getChannel().toString()).arg(state),LogLevel::INFO_VERBOSE);
    }
    // TODO

}

void RadarBurstSignalPowerView::updatePlot() {

    this->logMessage("updating plot ...", dcap::LogLevel::INFO_VERBOSE);

    m_plot->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    if (m_plot_curves.size() == 0) return;

    CurveMapPtr curve_map = m_plot_curves.at(m_burst_list->currentIndex());

    for (int i = 0; i < m_chan_list->count(); i++) {

        auto *item = m_chan_list->item(i);
        auto cId = m_channel_map.at(item);

        if (item->isSelected()) {
            auto m_curve = curve_map->at(cId);

            for (auto mode : m_mode_list->activeModes) {
                if (mode.second)
                    switch (mode.first) {
                    case RadarDataSelectList::VIEWMODE::REAL:
                        if (m_curve->real_samples)
                            m_curve->real_samples->setPen(GetColor(i+1, 0, 16));
                            m_curve->real_samples->attach(m_plot);
                        break;
                    case RadarDataSelectList::VIEWMODE::IMAG:
                        if (m_curve->imag_samples)
                            m_curve->imag_samples->setPen(GetColor(i+1, 0, 16), 2.0, Qt::DashDotDotLine);
                            m_curve->imag_samples->attach(m_plot);
                        break;
                    case RadarDataSelectList::VIEWMODE::AMP:
                        if (m_curve->ampl_samples)
                            m_curve->ampl_samples->setPen(GetColor(i+1, 0, 16), 2.0, Qt::DashDotLine);
                            m_curve->ampl_samples->attach(m_plot);
                        break;
                    case RadarDataSelectList::VIEWMODE::PHASE:
                        if (m_curve->phase_samples)
                            m_curve->phase_samples->setPen(GetColor(i+1, 0, 16), 2.0, Qt::DashLine);
                            m_curve->phase_samples->attach(m_plot);
                        break;
                    }
            }
        }
    }

    m_plot->replot();

}

bool RadarBurstSignalPowerView::viewUnavailable()
{
    this->logMessage("viewUnavailable", dcap::LogLevel::INFO_VERBOSE);

    // stops all feeders...
    if (dataConsumer) {
        dataConsumerThread.quit();
        dataConsumerThread.wait();

        disconnect(&dataConsumerThread, &QThread::finished, dataConsumer, &RadarBurstDataConsumer::deleteLater);
        disconnect(this, &RadarBurstSignalPowerView::operate, dataConsumer, &RadarBurstDataConsumer::doDataConsume);
        disconnect(dataConsumer, &RadarBurstDataConsumer::resultReady, this, &RadarBurstSignalPowerView::handleResults);

        //TODO: RE-ENABLE
        //delete dataConsumer;

    }

    // disconnects our signals
    for(auto d : this->burstData) {
        RadarBurstModelDataPtr md = d.second;
        disconnect(&(*md),
                    &RadarBurstModelData::stateChange,
                    this,
                    &RadarBurstSignalPowerView::dataStateChanged);
    }

    // resets our radar bursts data and channel data
    this->channelData.clear();
    this->burstData.clear();

    typedef void (QComboBox::*IndexChangedFcn)(int);
    disconnect(m_burst_list, (IndexChangedFcn)&QComboBox::currentIndexChanged, this, &RadarBurstSignalPowerView::updateBurst);
    try {
        while(m_burst_list->count() > 0)
            m_burst_list->removeItem(0);
    } catch (std::exception err) {
        this->logMessage(QString("Could not clear burst list: %1").arg(err.what()), LogLevel::ERROR);
    }

    m_channel_map.clear();

    disconnect(m_chan_list, &QListWidget::itemSelectionChanged, this, &RadarBurstSignalPowerView::updateChannel);
    try {
        while (m_chan_list->count() > 0) {
            QListWidgetItem *item = m_chan_list->takeItem(0);
            delete item;
        }
    } catch (std::exception exc) {
        this->logMessage(QString("Could not clear channel list: %1").arg(exc.what()), LogLevel::ERROR);
    }

    // clear accumulated curves
    m_plot->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    for (CurveMapPtr curve_map : m_plot_curves) {
        for (auto channel : *curve_map) {
            if (channel.second->real_samples)
                delete channel.second->real_samples;
            if (channel.second->imag_samples)
                delete channel.second->imag_samples;
            if (channel.second->ampl_samples)
                delete channel.second->ampl_samples;
            if (channel.second->phase_samples)
                delete channel.second->phase_samples;
        }
        delete curve_map;
    }
    m_plot_curves.clear();
    m_burst_counter = 0;
    m_zoom_base = false;
    m_update_zoom = false;



    return true;
}


}
