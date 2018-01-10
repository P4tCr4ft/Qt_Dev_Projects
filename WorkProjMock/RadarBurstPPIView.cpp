//------------------------------------------------------------------------------
// Copyright (c) DST, 2017
//
// Project:                 EA EP Testbed
// Classification:          Unclassified
// Intellectual Property:   DST
//
//------------------------------------------------------------------------------
// $Id: RadarBurstPPIView.cpp 4504 2017-11-21 04:19:01Z triplets $
//------------------------------------------------------------------------------
//
/**
 *@file RadarBurstPPIView.cpp
 * View for RadarBurstModelData
*/

#include "RadarBurstPPIView.h"
#include "RadarBurstPPIViewInfo.h"

#include "model/RadarBurstDataReader.h"

#include <qimage.h>
#include <qpixmap.h>
#include <qlayout.h>
#include <complex>
#include <qwt_scale_engine.h>
#include <qwt_plot_rasteritem.h>
#include <qwt_polar_plot.h>
#include <qwt_polar_grid.h>

namespace trex {

class RadarBurstPPIPlot : public QwtPolarPlot{
public:
    RadarBurstPPIPlot(QWidget* parent = 0) :
        QwtPolarPlot(parent)
    {
        setPlotBackground( Qt::black );

        setScale( QwtPolar::Azimuth, 0, 360, 15);
        setScale( QwtPolar::Radius, 0, 100, 20);

        m_grid = new QwtPolarGrid();

        m_grid->setPen(QPen(Qt::white));
        m_grid->setAxisPen(QwtPolar::AxisAzimuth, QPen(Qt::red));

        m_grid->showAxis(QwtPolar::AxisAzimuth, true);
        m_grid->showAxis(QwtPolar::AxisRight, true);
        m_grid->showAxis(QwtPolar::AxisLeft, true);
        m_grid->showGrid(QwtPolar::Azimuth, true);
        m_grid->showGrid(QwtPolar::Radius, true);

        for (int scaleId = 0; scaleId < QwtPolar::ScaleCount; scaleId++) {
             m_grid->showGrid(scaleId);
        }

        m_grid->attach(this);
    }

    QwtPolarGrid *m_grid;
};

RadarBurstPPIView::RadarBurstPPIView():
    dcap::AbstractView(std::shared_ptr<dcap::IViewInfo>(new RadarBurstPPIViewInfo()))
{
    if(this->layout() != NULL){
        delete this->layout();
    }
    dataConsumer = NULL;

    m_layout = new QHBoxLayout();
    selectListGroupBox = new QGroupBox("Select List Layout");
    m_plot = new RadarBurstPPIPlot(this);

    m_layout->addWidget(m_plot);
    m_layout->addWidget(selectListGroupBox);
    m_layout->setStretch(0,100);
    this->setLayout(m_layout);

}

RadarBurstPPIView::~RadarBurstPPIView()
{

    if (dataConsumer != NULL && dataConsumerThread.isRunning()) {
        dataConsumerThread.quit();
        dataConsumerThread.wait();
    }

    delete m_plot;

}

QSize RadarBurstPPIView::sizeHint() const
{
    return QSize(300,100);
}

void RadarBurstPPIView::writeConfiguration(QSettings &/*settings*/)
{
    // TODO
}

void RadarBurstPPIView::readConfiguration(QSettings &/*settings*/)
{
    // TODO
}

void RadarBurstPPIView::handleResults(const std::map<dcap::SingleChannelId, sRadarBurstCurves_t*> *result){
    m_plot_curves.push_back(result);
    m_burst_counter += 1;
    m_burst_list->addItem(QString("Burst %1").arg(m_burst_counter));
    m_burst_list->setCurrentIndex(m_burst_list->count()-1);
}

bool RadarBurstPPIView::createView()
{
    this->logMessage("createView", dcap::LogLevel::INFO_VERBOSE);
    // TODO create the widgets

    m_burst_list = new QComboBox(this);
    typedef void (QComboBox::*IndexChangedFcn)(int);
    connect(m_burst_list, (IndexChangedFcn)&QComboBox::currentIndexChanged, this, &RadarBurstPPIView::updateBurst);


    m_chan_list = new QListWidget(this);
    m_chan_list->setSelectionMode(QListWidget::SelectionMode::SingleSelection);
    connect(m_chan_list, &QListWidget::itemSelectionChanged, this, &RadarBurstPPIView::updateChannel);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_burst_list);
    layout->addWidget(m_chan_list);
    selectListGroupBox->setLayout(layout);
    return true;
}

bool RadarBurstPPIView::viewAvailable(const std::vector<std::shared_ptr<dcap::ICapabilityData> > &capabilities, const std::vector<std::shared_ptr<dcap::IModelData> > &modelData)
{
    static_cast<void>(capabilities);

    this->logMessage("viewAvailable", dcap::LogLevel::INFO_VERBOSE);

    // loads in the radar burst and channel data
    for(auto d: modelData){
        auto dId = (d)->getID();
        if(dId == TrexModelDataIds::RadarBurstId){
            auto radarBurstData = std::dynamic_pointer_cast<RadarBurstModelData>(d);
            auto cId = radarBurstData->getChannel();
            if(radarBurstData)
                this->burstData[cId] = radarBurstData;
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

    // TODO read in the data and start displaying it

    for (auto channel : this->channelData) {

        auto *item = new QListWidgetItem(controller->getChannelName(systemId.toSingleID(), channel.first));
        m_chan_list->addItem(item);
        m_channel_map[item] = channel.first;
    }

    // setup radar data consumer thread
    dataConsumer = new RadarBurstDataConsumer(this->channelData, this->burstData);
    dataConsumer->moveToThread(&dataConsumerThread);

    connect(&dataConsumerThread, &QThread::finished, dataConsumer, &RadarBurstDataConsumer::deleteLater);
    connect(this, &RadarBurstPPIView::operate, dataConsumer, &RadarBurstDataConsumer::doDataConsume);
    connect(dataConsumer, &RadarBurstDataConsumer::resultReady, this, &RadarBurstPPIView::handleResults);

    dataConsumerThread.start();
    emit operate();

    return true;
}

void RadarBurstPPIView::updateBurst(int){
    updatePlot();
}

void  RadarBurstPPIView::updateChannel(){
    updatePlot();
}

void RadarBurstPPIView::updatePlot() {

    this->logMessage("updating plot ...", dcap::LogLevel::INFO_VERBOSE);

    m_plot->detachItems(QwtPlotItem::Rtti_PlotItem, false);

    m_plot->replot();

}

bool RadarBurstPPIView::viewUnavailable()
{
    this->logMessage("viewUnavailable", dcap::LogLevel::INFO_VERBOSE);

    // stops all feeders...
    if (dataConsumer) {
        dataConsumerThread.quit();
        dataConsumerThread.wait();
    }

    // resets our radar bursts data and channel data
    this->channelData.clear();
    this->burstData.clear();

    return true;
}


}
